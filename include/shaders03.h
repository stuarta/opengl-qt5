#ifndef _SHADER_H
#define _SHADER_H
const char *vs_source =
    //"#version 100\n"  // OpenGL ES 2.0
    //"#version 120\n"  // OpenGL 2.1
    "attribute vec2 coord2d;                  "
    "attribute vec3 v_color;                  "
    "varying vec3 f_color;                    "
    "void main(void) {                        "
    "  gl_Position = vec4(coord2d, 0.0, 1.0); "
    "  f_color = v_color;                     "
    "}";

const char *fs_source =
    //"#version 100\n"  // OpenGL ES 2.0
    //"#version 120\n"  // OpenGL 2.1
    "varying highp vec3 f_color;    "
    "void main(void) {        "
    "  gl_FragColor = vec4(f_color.r, f_color.g, f_color.b, 1.0); "
    "}";

GLfloat triangle_vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
};

GLfloat triangle_colors[] = {
    1.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 0.0, 0.0,
};

#endif
