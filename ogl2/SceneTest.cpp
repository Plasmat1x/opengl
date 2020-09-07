#include "SceneTest.h"
#include "ResourceManager.h"
#include "Tools.h"


SceneTest SceneTest::m_SceneTest;

void SceneTest::init(GLFWwindow& window)
{
    //--info--
    std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
    std::cout << "tinyxml version: " << TIXML_MAJOR_VERSION << "." << TIXML_MINOR_VERSION << std::endl;
    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION_MAJOR) << "." << glewGetString(GLEW_VERSION_MINOR) << "." << glewGetString(GLEW_VERSION_MICRO) << std::endl;
    std::cout << "GLM version: " << GLM_VERSION_MESSAGE << std::endl;
    std::cout << "SOIL version: unknown" << std::endl;
    std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << std::endl;

    this->window = &window;
    glfwSetWindowTitle(&window, "Test scene");
    //--shader load and setup--
    ResourceManager::loadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::getShader("sprite").use();
    ResourceManager::getShader("sprite").SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::getShader("sprite").SetMatrix4("view", view);
    //--Image load--
    ResourceManager::loadImage("../textures/testPlayer.png", "sprite");

    level = new Level();
    level->setMap("../levels/testLevel.tmx");
}

void SceneTest::processInput(GLboolean keys[], GLboolean bt[])
{
    if (keys[GLFW_KEY_D])
    {
        level->sprite->setPosition(level->sprite->getPosition().x + 6, level->sprite->getPosition().y);
    }

    if (keys[GLFW_KEY_A])
    {
        level->sprite->setPosition(level->sprite->getPosition().x - 6, level->sprite->getPosition().y);
    }

    if (keys[GLFW_KEY_S])
    {
        level->sprite->setPosition(level->sprite->getPosition().x, level->sprite->getPosition().y + 6);
    }

    if (keys[GLFW_KEY_W])
    {
        level->sprite->setPosition(level->sprite->getPosition().x, level->sprite->getPosition().y - 6);
    }
}

void SceneTest::update(float deltaTime)
{ 
    level->update(deltaTime);   
}

void SceneTest::render()
{
    level->draw();
}

void SceneTest::cleanup()
{
    delete level;
}

void SceneTest::pause()
{

}

void SceneTest::resume()
{
}
