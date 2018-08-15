#include "window.h"

#include <QPainter>
#include <QMatrix4x4>
#include <QOpenGLFunctions>

#include "../include/shaders03.h"

mWindow::mWindow()
{
}

mWindow::mWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    // If we are given a parent, it could be for a specific screen
    // in a multi screen setup, so configure ourself to be in the
    // correct location
    setGeometry(parent->frameGeometry());
}

mWindow::~mWindow()
{
    delete m_program;
    glDeleteBuffers(1, &m_vbo_triangle);
    glDeleteBuffers(1, &m_vbo_triangle_colors);

}

void mWindow::initializeGL()
{
    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vs_source);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs_source);
    m_program->link();
    m_attribute_coord2d = m_program->attributeLocation("coord2d");
    m_attribute_v_color = m_program->attributeLocation("v_color");
    // VBO Handling
    glGenBuffers(1, &m_vbo_triangle);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &m_vbo_triangle_colors);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_triangle_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);
}

void mWindow::resizeGL(int width, int height)
{
    // Currently we are not handling width/height changes
    (void)width;
    (void)height;
}

void mWindow::paintGL()
{
//    glClearColor(.4f, .7f, .1f, 0.5f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    glEnableVertexAttribArray(m_attribute_v_color);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_triangle_colors);
    glVertexAttribPointer(m_attribute_v_color, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(m_attribute_coord2d);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_triangle);
    glVertexAttribPointer(m_attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(m_attribute_coord2d);
    glDisableVertexAttribArray(m_attribute_v_color);
    m_program->release();
}

