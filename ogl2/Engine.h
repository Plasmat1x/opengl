#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <exception>
#include <array>
#include <cmath>

#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

static GLboolean keys[1024];
static GLboolean m_bt[11];
static GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
static glm::vec2 c_position;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void error_callback(int error, const char* description);

class Engine
{
public:
    GLuint SCR_WIDTH = 800;
    GLuint SCR_HEIGHT = 600;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    const int TICKS_PER_SECOND = 60;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;
    int loops;
    float interpolation;

    Engine();
    ~Engine();

    void run();

private:
    GLFWwindow* window;

    void init();
    void setupWindow(GLuint scrWidth, GLuint scrHeight);

    void update(float dt);

    void processInput();
    void render();

    float timer();

    void cleanup();
};