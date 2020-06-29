#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:

    GameState state;
    GLboolean keys[1024];
    GLboolean m_buttons[11];
    GLuint width, height;

    Game(GLuint width, GLuint height);
    ~Game();

    void init();
    void processInput(GLfloat dt);
    void update(GLfloat dt);
    void render();

};

