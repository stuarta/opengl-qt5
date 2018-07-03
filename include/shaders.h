#ifndef _SHADER_H
#define _SHADER_H
const char *vs_source =
    //"#version 100\n"  // OpenGL ES 2.0
    //"#version 120\n"  // OpenGL 2.1
    "attribute vec2 coord2d;                  "
    "void main(void) {                        "
    "  gl_Position = vec4(coord2d, 0.0, 1.0); "
    "}";

const char *fs_source =
    //"#version 100\n"  // OpenGL ES 2.0
    //"#version 120\n"  // OpenGL 2.1
    "void main(void) {        "
      "  gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0); "
    "}";

GLfloat triangle_vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
};

#endif
