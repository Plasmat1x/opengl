#include "SceneTest.h"
#include "ResourceManager.h"
#include "Tools.h"
#include "Sprite.h"
#include "tinyxml/tinyxml.h"

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

    //--sprite setup--
    Texture texture;
    texture.loadTextureFromImage(ResourceManager::getImage("sprite"));
    sprite = new Sprite("sprite");
    sprite->setShader(ResourceManager::getShader("sprite"));
    sprite->setTexture(texture);
    sprite->setPosition(100, 100);
    sprite->setSize(64, 128);
    sprite->setTextureRect(0, 0, 64, 128);
    sprite->setColor(1.0f, 1.0f, 1.0f);
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
