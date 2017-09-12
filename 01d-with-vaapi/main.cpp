#include <QApplication>
#include <QDesktopWidget>
#include <QX11Info>

#include "window.h"

#include <va/va.h>
#include <va/va_glx.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // QDesktopWidget allows us to get the multi screen data
    QDesktopWidget  *m_desktop = app.desktop();
    // QX11Info to get a display reference
    Display         *m_x_display = QX11Info::display();
    // libva get GLX context for vaapi
    void            *m_va_display = vaGetDisplayGLX(m_x_display);

    // Init VAAPI
    VAStatus va_status;
    int major_ver, minor_ver;
    va_status = vaInitialize(m_va_display, &major_ver, &minor_ver);
    if (va_status != VA_STATUS_SUCCESS)
    {
        qInfo() << vaErrorStr(va_status);
    }

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
