#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL/SOIL.h>

#include <vector>

#include "shader.h"

#include <iostream>
#include <string>

enum object_Direction {
    IDLE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class GameObject
{
public:
    glm::vec2 position;
    glm::vec2 size;

    GameObject();
    ~GameObject();
    
    void Init(const char* path, std::string fileName, glm::mat4 projection);
    void Init(int x, int y, const char* path, Shader& sh);
    void Init(int x, int y, const char* path, std::string fileName, glm::mat4 projection);
    void Init(int x, int y, int w, int h, const char* path, std::string fileName, glm::mat4 projection);

    void Update(float dt);
    void Draw();
    void Input(object_Direction dir, float dt);

    void setColor(float r, float g, float b, float a);
    void setOrigin();
    void setTexture();
    void setPosition(int x, int y);
    void setSize(int w, int h);
    void setScale(float scale);
    void setShader(std::string fileName, glm::mat4 projection);

    glm::vec2 getPosition();
    float getScale();
    glm::vec2 getSize();
    glm::vec4 getColor();
    Shader getShader();
    int getTexture();
    void getOrigin();//!

    GLuint loadTexture(char const* path);

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint CBO;

    //glm::vec2 position;
    //glm::vec2 size;
    glm::vec4 color;

    std::vector<GLfloat> vertices;
    std::vector<GLint> indices;

    Shader shader;
    GLuint textureID;

    GLfloat _ms = 40.0f;
    glm::mat4 model;

    int width;
    int height;
    int nrComponents;

    float scale;

    object_Direction dir;

    typedef struct {
        GLfloat coord;
        GLfloat textureCoord;
    }Vertex;

    void InitModel();
};

#endif
