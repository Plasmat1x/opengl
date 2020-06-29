#include "Engine.h"

#include "ResourceManager.h"
#include "AnimationManager.h"
#include "SceneManager.h"
#include "SceneTest.h"

#include "tinyxml/tinyxml.h"

SceneTest* sceneTest;

Engine::Engine()
{

}

Engine::~Engine()
{
    
}

void Engine::run()
{
    init();

    int eleapsedTimeAsMilisecond = glfwGetTime() * 1000;

    unsigned long int next_game_tick = eleapsedTimeAsMilisecond;

    while (!glfwWindowShouldClose(window))
    {
        timer();
        eleapsedTimeAsMilisecond = glfwGetTime() * 1000;
        loops = 0;

        while (eleapsedTimeAsMilisecond > next_game_tick && loops < MAX_FRAMESKIP)
        {

            glfwPollEvents();
            processInput();
            update(deltaTime);

            next_game_tick += SKIP_TICKS;
            loops++;
        }
        interpolation = float(eleapsedTimeAsMilisecond + SKIP_TICKS - next_game_tick / float(SKIP_TICKS));
        render();
    }

    cleanup();
}

void Engine::init()
{
    setupWindow(SCR_WIDTH, SCR_HEIGHT);
    projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    //------------------------------------------------------------------------------//

    ResourceManager::loadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::loadShader("../shaders/text.vert", "../shaders/text.frag", nullptr, "text");

    ResourceManager::loadTexture("../textures/knight.png", GL_TRUE,"knight");
    ResourceManager::loadTexture("../textures/UI/button-bg.png", GL_TRUE,"button");
    ResourceManager::loadTexture("../textures/anim_wip.png", GL_TRUE,"anim");
    ResourceManager::loadTexture("../textures/testTile.png", GL_TRUE,"block");

    ResourceManager::getShader("sprite").use();
    ResourceManager::getShader("sprite").SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);  
    ResourceManager::getShader("sprite").SetMatrix4("view", view);
    
    ResourceManager::getShader("text").use();
    ResourceManager::getShader("text").SetInteger("text", 0);
    ResourceManager::getShader("text").SetMatrix4("projection", projection);
    ResourceManager::getShader("text").SetMatrix4("view", view);

    SceneManager::addScene(*this->window,sceneTest->instance());
}

void Engine::setupWindow(GLuint scrWidth, GLuint scrHeight)
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        std::cout << "GLFW: initialize GLFW error!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);

    window = glfwCreateWindow(scrWidth, scrHeight, "OpenGL - One", nullptr, nullptr);

    if (!window)
    {
        std::cout << "GLFW: create window error!" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowSizeLimits(window, 800, 600, 1280, 1024);
    glfwSetCursor(window, cursor);

    glfwSwapInterval(1);

    GLFWimage images[1];
    images[0].pixels = SOIL_load_image("../textures/icon/rocket.png", &images[0].width, &images[0].height, 0, SOIL_LOAD_RGBA);
    glfwSetWindowIcon(window, 1, images);
    SOIL_free_image_data(images[0].pixels);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW: initialize GLEW error!" << std::endl;
    }

#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
#endif

    glEnable(GL_CULL_FACE);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_ALPHA, GL_ALWAYS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

float Engine::timer()
{
    float currentFrame = glfwGetTime();//return as seconds
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return deltaTime;
}

void Engine::update(float dt)
{
    if (!SceneManager::scenes.empty()) { SceneManager::scenes.back()->update(dt); }        
}

void Engine::processInput()
{
    //example: if (keys[GLFW_KEY_W]) { //code; }
    //if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); } 
    if (!SceneManager::scenes.empty()) 
    { 
        SceneManager::scenes.back()->cursorPosition = c_position;  
        SceneManager::scenes.back()->processInput(keys, m_bt);
    }
}

void Engine::render()
{
    glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!SceneManager::scenes.empty()) { SceneManager::scenes.back()->render(); }

    glfwSwapBuffers(window);
}

void Engine::cleanup()
{
    SceneManager::cleanup();
    ResourceManager::clear();
    AnimationManager::cleanup();

    delete sceneTest;

    glfwSetWindowIcon(window, 0, NULL);
    glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = GL_TRUE;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = GL_FALSE;
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);
    c_position.x = xpos;
    c_position.y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button >= 0 && button < 11)
    { 
        if (action == GLFW_PRESS)
        {
            m_bt[button] = GL_TRUE;
        }
        else if (action == GLFW_RELEASE)
        {
            m_bt[button] = GL_FALSE;
        }
    }
}

void error_callback(int error, const char* description)
{
    std::cout << "GLFW error " << error << ": " << description << std::endl;
}
