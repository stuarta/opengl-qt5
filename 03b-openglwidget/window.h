#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class Window : public QOpenGLWidget, protected QOpenGLFunctions
{
//    Q_OBJECT
public:
    Window();
    ~Window();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

private:
    QOpenGLShaderProgram *m_program;
    GLint m_attribute_coord2d, m_attribute_v_color;
    GLuint m_vbo_triangle, m_vbo_triangle_colors;
};

#endif //WINDOW_H
