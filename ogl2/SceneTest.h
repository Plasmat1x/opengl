#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "Sprite.h"

class SceneTest : public Scene
{
public:

    void init(GLFWwindow &window);

    void processInput(GLboolean keys[], GLboolean bt[]);
    void update(float deltaTime);
    void render();

    void cleanup();

    void pause();
    void resume();

    static SceneTest* instance() { return &m_SceneTest; }

protected:
    SceneTest() {}

private:
    static SceneTest m_SceneTest;

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    Sprite* sprite;
};

