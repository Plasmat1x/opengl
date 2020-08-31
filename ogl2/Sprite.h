#pragma once
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Shader.h"
#include "Texture.h"

struct Vertice
{
    glm::vec2 position;
    glm::vec2 textureCoord;
    glm::vec3 color;
};

class Sprite
{
public:
///<summary>
/// <para>DEFAULT WORKED INIT</para>
/// <para>Sprite* sprite;</para>
/// <para>sprite = new Sprite();</para>
/// <para>sprite->setTexture(ResourceManager::getTexture("block"));</para>
/// <para>sprite->setPosition(glm::vec2(0, 0));</para>
/// <para>sprite->setSize(glm::vec2(64, 64));</para>
/// <para>sprite->setTextureRect(glm::vec4(0, 0, 64, 64));</para>
/// <para>sprite->setColor(glm::vec3(1.0f));</para>
///</summary>
    Sprite();
    Sprite(std::string _shader);

    ~Sprite();

    void init();

    //сетеры
    void setPosition(glm::vec2 position);
    void setPosition(GLint x, GLint y);
    void setSize(glm::vec2 size);
    void setSize(GLint w, GLint h);
    void setColor(glm::vec3 color);
    void setColor(GLfloat r, GLfloat g, GLfloat b);
    void setScale(GLfloat scale);
    void setScale(GLfloat wScale, GLfloat hScale);
    void setShader(Shader shader);
    void setTextureRect(glm::vec4 params);
    void setTextureRect(GLint x, GLint y, GLint w, GLint h);
    void setRotation(GLfloat rotation);
    void setTexture(Texture texture);
    void setAlpha(GLfloat alpha);
    void setAlpha(int alpha);
    //гетеры
    Texture& getTexture();
    Shader getShader();
    glm::vec2 getScale();
    glm::vec3 getColor();
    glm::vec2 getSize();
    glm::vec2 getPosition();
    GLfloat getRotation();
    GLfloat getAlpha();

    void draw();
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

    bool textured;
};

