#include "SceneTest.h"
#include "ResourceManager.h"
#include "Tools.h"
#include "Sprite.h"
#include "tinyxml/tinyxml.h"

SceneTest SceneTest::m_SceneTest;

void SceneTest::init(GLFWwindow& window)
{
    std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
    std::cout << "tinyxml version: " << TIXML_MAJOR_VERSION << "." << TIXML_MINOR_VERSION << std::endl;
    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION_MAJOR) << "." << glewGetString(GLEW_VERSION_MINOR) << "." << glewGetString(GLEW_VERSION_MICRO) << std::endl;
    std::cout << "GLM version: " << GLM_VERSION_MESSAGE << std::endl;
    std::cout << "SOIL version: unknown" << std::endl;
    std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;

    this->window = &window;
    glfwSetWindowTitle(&window, "Test scene");

    projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    ResourceManager::loadShader("../shaders/spriteTest.vert", "../shaders/spriteTest.frag", nullptr, "sprite");
    ResourceManager::getShader("sprite").SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::getShader("sprite").SetMatrix4("view", view);
    ResourceManager::loadImage("../textures/testPlayer.png", "player");
    ResourceManager::loadTexture("../textures/testPlayer.png", GL_TRUE, "player");

    sprite = new Sprite("sprite");
    sprite->setTexture(ResourceManager::getTexture("block"));
}

void SceneTest::processInput(GLboolean keys[], GLboolean bt[])
{

}

void SceneTest::update(float deltaTime)
{ 
}

void SceneTest::render()
{
    sprite->draw();
}

void SceneTest::cleanup()
{
    delete sprite;
}

void SceneTest::pause()
{
}

void SceneTest::resume()
{
}
