#include "SceneManager.h"

std::vector<Scene*> SceneManager::scenes;

void SceneManager::changeScene(GLFWwindow& window, Scene* scene)
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }

    scenes.push_back(scene);
    scenes.back()->init(window);
}

void SceneManager::removeScene()
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }

    if (!scenes.empty()) {
        scenes.back()->resume();
    }
}

void SceneManager::addScene(GLFWwindow& window, Scene* scene)
{
    while (!scenes.empty()) {
        scenes.back()->pause();
    }
    scenes.push_back(scene);
    scenes.back()->init(window);
}

void SceneManager::cleanup()
{
    while (!scenes.empty()) {
        scenes.back()->cleanup();
        scenes.pop_back();
    }
    scenes.clear();
}