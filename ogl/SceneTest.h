#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "Entity.h"
#include "Button.h"
#include "Player.h"
#include "Level.h"
#include "Camera.h"

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
    glm::mat4 view;
    Map* level;
    Player* player;
    Sprite* sprt;
    Camera* camera;
};

