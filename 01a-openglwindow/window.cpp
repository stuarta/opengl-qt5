#include "window.h"

#include <QPainter>
#include <QMatrix4x4>
#include <QOpenGLFunctions>

#include "../include/shaders.h"

Window::Window()
{
}

void Window::initializeGL()
{
    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vs_source);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs_source);
    m_program->link();
    m_attribute_coord2d = m_program->attributeLocation("coord2d");
}

void Window::resizeGL(int width, int height)
{
    // Currently we are not handling width/height changes
    (void)width;
    (void)height;
}

void Window::paintGL()
{
//    glClearColor(.4f, .7f, .1f, 0.5f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    glVertexAttribPointer(m_attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, triangle_vertices);
    glEnableVertexAttribArray(m_attribute_coord2d);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(m_attribute_coord2d);
    m_program->release();
}

