#include <QApplication>
#include <QDesktopWidget>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // QDesktopWidget allows us to get the multi screen data
    QDesktopWidget *m_desktop = app.desktop();

    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);

    // Basic multi screen information
    qInfo() << "System has" << m_desktop->screenCount() << "screens";
    for (int i = 0; i < m_desktop->screenCount(); i++) {
        qInfo() << "Geometry:" << m_desktop->screenGeometry(i);
    }

    // Pick a random screen from those available
    int m_targetscreen = rand() % m_desktop->screenCount();

    // Set the window up
    Window window(m_desktop->screen(m_targetscreen));
    window.setFormat(format);
    window.resize(QSize(800, 600));
    //Qt::WindowFullScreen works with QOpenGLWidget, but not QOpenGLWindow
    //window.setWindowState(Qt::WindowFullScreen);
    window.show();

    return app.exec();
}
