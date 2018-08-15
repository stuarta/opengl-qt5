#include <QApplication>
#include <QDesktopWidget>
#include <QX11Info>

#include "window.h"

#include <va/va.h>
#include <va/va_glx.h>
#include <va/va_wayland.h>

#include <wayland-client.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // QDesktopWidget allows us to get the multi screen data
    QDesktopWidget  *m_desktop = app.desktop();
    VADisplay       m_va_display;
    // Check Qt Platform Abstraction report
    qInfo() << "Qt Platform reports platform name = " << app.platformName();
    // Connect to wayland
    struct wl_display *m_wl_display = wl_display_connect(NULL);
    if (m_wl_display != NULL) {
        qInfo() << "Successfully connected to wayland";
        // libva get wayland context for vaapi
        m_va_display = vaGetDisplayWl(m_wl_display);
    } else {
        qInfo() << "Failed to get wayland connection, falling back to X11";
        Display *m_x_display = QX11Info::display();
        m_va_display = vaGetDisplayGLX(m_x_display);
    } 

    // Init VAAPI
    VAStatus va_status;
    int major_ver, minor_ver;
    va_status = vaInitialize(m_va_display, &major_ver, &minor_ver);
    if (va_status != VA_STATUS_SUCCESS)
    {
        qInfo() << vaErrorStr(va_status);
    }
    qInfo() << "Is VA display valid? " << vaDisplayIsValid(m_va_display);
    qInfo() << "VAAPI Vendor = " << vaQueryVendorString(m_va_display);

    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);

    // Basic multi screen information
    qInfo() << "Is Virtual Desktop?" << m_desktop->isVirtualDesktop();
    qInfo() << "System has" << m_desktop->screenCount() << "screens, v_width"
            << m_desktop->width() << ",v_height" << m_desktop->height();
    for (int i = 0; i < m_desktop->screenCount(); i++) {
        qInfo() << "Geometry:" << m_desktop->screenGeometry(i);
    }

    // Pick a random screen from those available
    int m_targetscreen = rand() % m_desktop->screenCount();

    // Set the window up
    mWindow window(m_desktop->screen(m_targetscreen));
    window.setFormat(format);
    window.resize(QSize(800, 600));
    //Qt::WindowFullScreen works with QOpenGLWidget, but not QOpenGLWindow
    //window.setWindowState(Qt::WindowFullScreen);
    window.show();

    return app.exec();
}
