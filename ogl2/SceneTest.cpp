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

    //--sprite setup--
    Texture texture;
    texture.loadTextureFromImage(ResourceManager::getImage("sprite"));
    sprite = new Sprite("sprite");
    sprite->setShader(ResourceManager::getShader("sprite"));
    sprite->setTexture(texture);
    sprite->setPosition(100, 100);
    sprite->setSize(64, 128);

    level.setMap("../levels/testLevel.tmx");

    cam = new Camera(sprite->getPosition());
    cam->setOffset(-400, -300);
}

void SceneTest::processInput(GLboolean keys[], GLboolean bt[])
{
    if (keys[GLFW_KEY_D])
    {
        sprite->setPosition(sprite->getPosition().x + 6, sprite->getPosition().y);
    }

    if (keys[GLFW_KEY_A])
    {
        sprite->setPosition(sprite->getPosition().x - 6, sprite->getPosition().y);
    }

    if (keys[GLFW_KEY_S])
    {
        sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y + 6);
    }

    if (keys[GLFW_KEY_W])
    {
        sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y - 6);
    }
}

void SceneTest::update(float deltaTime)
{ 
    cam->update();
    cam->setPosition(sprite->getPosition());
    ResourceManager::getShader("sprite").SetMatrix4("view", cam->getMatrixView(), GL_TRUE);
}

void SceneTest::render()
{
    level.draw();
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
