#pragma once 
#include <GL/glew.h>

class Texture2D
{
public:
    GLuint ID;
    GLuint width, height;
    GLuint internal_format;
    GLuint image_fromat;
    GLuint wrap_s;
    GLuint wrap_t;
    GLuint filter_min;
    GLuint filter_max;

    Texture2D();

    void generate(GLuint width, GLuint height, unsigned char* data);
    void bind() const;
};