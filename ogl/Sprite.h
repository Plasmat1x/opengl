#pragma once
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Shader.h"
#include "Texture.h"

class Sprite
{
public:

    Sprite();
    ~Sprite();

    void init();

    void setPosition(glm::vec2 position);
    void setSize(glm::vec2 size);
    void setColor(glm::vec3 color);
    void setScale(GLfloat scale);
    void setScale(GLfloat wScale, GLfloat hScale);
    void setShader(Shader shader);
    void setTextureRect(glm::vec4 params);
    void setRotation(GLfloat rotation);
    void setTexture(Texture texture);
    void setAlpha(GLfloat alpha);
    void setAlpha(int alpha);

    Texture& getTexture();
    Shader getShader();
    glm::vec2 getScale();
    glm::vec3 getColor();
    glm::vec2 getSize();
    glm::vec2 getPosition();
    GLfloat getRotation();
    GLfloat getAlpha();

    void draw();

    void initModel();
private:

    glm::vec2 position;
    glm::vec2 size;
    glm::vec3 color;
    glm::vec2 scale;
    GLfloat rotation;
    GLfloat alpha;

    glm::vec2 v0;
    glm::vec2 v1;
    glm::vec2 v2;
    glm::vec2 v3;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    std::vector<GLfloat> vertices;
    std::vector<GLint> indices;

    Shader shader;
    Texture texture;

    //GLfloat normalize(GLfloat value, GLfloat minValue, GLfloat maxValue);
};

