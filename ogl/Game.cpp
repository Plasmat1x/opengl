#include "Game.h"
#include "ResourceManager.h"

Game::Game(GLuint width, GLuint height)
    :state(GAME_ACTIVE), width(width), height(height), keys(), m_buttons()
{
}

Game::~Game()
{
}

void Game::init()
{
}

void Game::processInput(GLfloat dt)
{
}

void Game::update(GLfloat dt)
{
}

void Game::render()
{
}
