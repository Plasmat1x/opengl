#pragma once
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Shader.h"
#include "Texture.h"
#include "Entity.h"
#include "Text.h"

class Button :
    public Entity
{
public:

    Text text;

    enum buttonState
    {
        IDLE,
        HOVER,
        PRESS,
        RELEASE
    };

    buttonState curState;
    buttonState prevState;
    buttonState state;

    bool signal;
    bool focus;

    Button(glm::vec2 position, glm::vec2 size, std::string texture);
    ~Button();

    bool AABB(glm::vec2 pos);
    void action();
    void endAction();
    void pressButton();
    void clickButton();
    void update(float deltaTime);
    void changeState(buttonState state);
    void draw();
};

/*
if (button->AABB(cursorPosition))
{
    if (bt[GLFW_MOUSE_BUTTON_1])
    {
        button->action();
    }
    else if (!bt[GLFW_MOUSE_BUTTON_1])
    {
        button->endAction();
    }
}


    button = new Button(glm::vec2(500,128), glm::vec2(300,110), "button");
    button->sprite.setScale(1.0f, 1.0f);
    button->text.setText("Color");
    button->text.load("../fonts/arial.ttf", 40);
*/