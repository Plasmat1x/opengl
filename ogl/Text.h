#pragma once
#include <gl/glew.h>

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"

class Text
{
public:

    Text();
    ~Text();

    void load(std::string font, GLuint size);

    void init();
    void setShader(Shader shader);
    void setText(std::string text);
    void setPosition(glm::vec2 position);
    void setPosition(glm::vec2 position, GLfloat xoffset, GLfloat yoffset);
    void setColor(glm::vec3 color);
    void setSize(GLuint size);
    void setScale(glm::vec2 scale);

    glm::vec2 getSize();

    void draw();

private:

    struct Character {
        GLuint ID;
        glm::ivec2 size;
        glm::ivec2 bearing;
        GLuint advance;
    };

    FT_Library ft;
    FT_Face face;
    Character character;

    GLfloat x;
    GLfloat y;

    std::map<GLchar, Character> characters;
    std::string text;
    
    GLuint size;
    glm::vec2 _size;
    glm::vec2 scale;
    glm::vec2 position;
    glm::vec3 color;

    Shader shader;

    GLuint VAO;
    GLuint VBO;

    void initModel();
    void bindGlyphs();
};

