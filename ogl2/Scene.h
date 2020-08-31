#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Scene
{
public:
    glm::vec2 cursorPosition = glm::vec2(0.0f, 0.0f);
    GLFWwindow* window = NULL;

    virtual void init(GLFWwindow &window) = 0;

    virtual void processInput(GLboolean keys[1024], GLboolean bt[11]) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void cleanup() = 0;

protected:

    Scene() {}
};

