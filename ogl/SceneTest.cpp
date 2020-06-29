#include "SceneTest.h"
#include "ResourceManager.h"
#include "AnimationManager.h"
#include "Sprite.h"
#include "Text.h"
#include "Tools.h"

//check version
#include "tinyxml/tinyxml.h"

SceneTest SceneTest::m_SceneTest;

void SceneTest::init(GLFWwindow& window)
{

    std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
    std::cout << "tinyxml version: " <<TIXML_MAJOR_VERSION << "." << TIXML_MINOR_VERSION << std::endl;
    std::cout << "GLEW version: " <<GLEW_VERSION_MAJOR << "." << GLEW_VERSION_MINOR << "." << GLEW_VERSION_MICRO << std::endl;
    std::cout << "GLM version: " << GLM_VERSION_MESSAGE << std::endl;
    std::cout << "SOIL version: unknown" << std::endl;
    std::cout << "GL version: " << GL_VERSION << std::endl;

    this->window = &window;
    glfwSetWindowTitle(&window, "Test scene");

    AnimationManager::addAnimation(AnimationManager::addFrames(6, glm::vec4(400, 240 * 0, 400, 240)), "idle");
    AnimationManager::addAnimation(AnimationManager::addFrames(6, glm::vec4(400, 240 * 1, 400, 240)), "run");
    AnimationManager::addAnimation(AnimationManager::addFrames(4, glm::vec4(400, 240 * 2, 400, 240)), "jump");
    AnimationManager::addAnimation(AnimationManager::addFrames(4, glm::vec4(400, 240 * 3, 400, 240)), "fall");
    AnimationManager::addAnimation(AnimationManager::addFrames(6, glm::vec4(400, 240 * 4, 400, 240)), "wall");

    AnimationManager::addAnimation(AnimationManager::addFrames(6, glm::vec4(400, 240 * 0, 400, 240), GL_TRUE), "_idle");
    AnimationManager::addAnimation(AnimationManager::addFrames(6, glm::vec4(400, 240 * 1, 400, 240), GL_TRUE), "_run");
    AnimationManager::addAnimation(AnimationManager::addFrames(4, glm::vec4(400, 240 * 2, 400, 240), GL_TRUE), "_jump");
    AnimationManager::addAnimation(AnimationManager::addFrames(4, glm::vec4(400, 240 * 3, 400, 240), GL_TRUE), "_fall");
    AnimationManager::addAnimation(AnimationManager::addFrames(6, glm::vec4(400, 240 * 4, 400, 240), GL_TRUE), "_wall");
    
    player = new Player(glm::vec2(200, 128), glm::vec2(200,120), "anim");
    player->speed = glm::vec2(200.0f, 300.0f);
    player->animation_idle.setSpeedAnimation(6.0f);
    player->animation_run.setSpeedAnimation(8.0f);
    player->animation_jump.setSpeedAnimation(7.0f);
    player->animation_fall.setSpeedAnimation(7.0f);
    player->animation_wall.setSpeedAnimation(7.0f);
    player->setupCollisionModel(glm::vec2(32, 120));

    /*
    level = new Map();
    level->setUnitSize(glm::vec2(64, 64));
    level->loadFromFile("../levels/one.lvl");
    */

    camera = new Camera(player->getPosition());
    camera->setOffset(-300 - player->collisionModelSize_in, -300);

    player->mMap = new Map();
    player->mMap->setUnitSize(glm::vec2(32, 32));
    player->mMap->loadFromFile("../levels/one.lvl");

}

void SceneTest::processInput(GLboolean keys[], GLboolean bt[])
{
    if (keys[GLFW_KEY_A])
    {
        player->mInputs[(int)player->LEFT] = true;
    }
    if (keys[GLFW_KEY_D])      
    {
        player->mInputs[(int)player->RIGHT] = true;
    }
    if (keys[GLFW_KEY_S])
    {
        player->mInputs[(int)player->DOWN] = true;
    }
    if (keys[GLFW_KEY_W] ) 
    { 
        player->mInputs[(int)player->UP] = true;
    }
    /*
    if (keys[GLFW_KEY_LEFT_ALT]) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
    else 
    {  
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    }
    */
}

void SceneTest::update(float deltaTime)
{ 
    player->update(deltaTime);

    camera->setPosition(player->getPosition());
    camera->update();

    ResourceManager::getShader("sprite").SetMatrix4("view", camera->getMatrixView(), GL_TRUE);
    player->getSprite().setColor(glm::vec3(1));

    /*
    for (auto row : level->arrObjects)
        for (auto tile : row)
            if (tile != nullptr && tile->aabb.overlaps(player->mAABB))
            {
                player->mOnGround = true;
            }

    */
}

void SceneTest::render()
{
    player->mMap->draw();
    //level->draw();
    player->draw();
}

void SceneTest::cleanup()
{
    delete camera;
    delete level;
    delete player;
    delete sprt;
}

void SceneTest::pause()
{
}

void SceneTest::resume()
{
}
