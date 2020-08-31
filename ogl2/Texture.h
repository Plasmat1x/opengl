#pragma once
#include <gl/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

#include "Image.h"

class Texture
{
public:
    GLuint ID;
    GLuint internal_format;
    GLuint image_format;
    GLuint wrap_s;
    GLuint wrap_t;
    GLuint filter_min;
    GLuint filter_max; 
    int width;
    int height;

    int nrComponents;  

    bool mipmap;
    bool smooth;
    bool repeated;
    
    Texture();
    ~Texture();

    void loadTextureFromFile(const GLchar* fileName);
    void loadTextureFromImage(Image image);

    void generate(int width, int height, unsigned char* data);
    void generateFromImage(Image image);
    void bind() const;
};

