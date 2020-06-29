#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <string>

#include "Scene.h"

class SceneManager
{
public:
    static std::vector<Scene*> scenes;

    static void changeScene(GLFWwindow& window, Scene* scene);
    static void addScene(GLFWwindow &window, Scene* scene);

    static void removeScene();
    
    static void cleanup();

private:
    SceneManager() {}
};

