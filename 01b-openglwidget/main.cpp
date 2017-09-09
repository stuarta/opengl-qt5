#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);

    // Set the window up
    Window window;
    window.setFormat(format);
    window.resize(QSize(800, 600));
    //Qt::WindowFullScreen works with QOpenGLWidget, but not QOpenGLWindow
    //window.setWindowState(Qt::WindowFullScreen);
    window.show();

    return app.exec();
}
