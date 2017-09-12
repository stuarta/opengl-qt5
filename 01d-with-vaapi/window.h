#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class mWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
//    Q_OBJECT
public:
    mWindow();
    mWindow(QWidget *parent);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

private:
    QOpenGLShaderProgram *m_program;
    GLint m_attribute_coord2d;
};

#endif //WINDOW_H
