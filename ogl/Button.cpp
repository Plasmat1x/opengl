#include "Button.h"



Button::Button(glm::vec2 position, glm::vec2 size, std::string texture) :
    Entity(position, size, texture),
    curState(RELEASE),
    prevState(RELEASE),
    state(IDLE),
    signal(false),
    focus(false)
{
    this->position = position;
    this->size = size;
}

Button::~Button()
{

}

bool Button::AABB(glm::vec2 pos)
{
    if (this->position.x                                               < pos.x &&
        this->position.x + this->size.x * this->sprite.getScale().x    > pos.x &&
        this->position.y                                               < pos.y &&
        this->position.y + this->size.y * this->sprite.getScale().y    > pos.y)
    {
        state = HOVER;
        focus = true;
        return true;
    }
    else
    {
        state = IDLE;
        changeState(IDLE);
        focus = false;
        return false;
    }
}

void Button::action()
{
    changeState(PRESS);
    state = PRESS;
}

void Button::endAction()
{
    changeState(RELEASE);
    state = RELEASE;
}

void Button::pressButton()
{ 
    signal = false;
    if (focus && curState == PRESS)
    {
        signal = true;
    }    
}

void Button::clickButton()
{
    signal = false;
    if (focus && prevState == PRESS && curState == RELEASE && !signal)
    {
        signal = true;
    }
}

void Button::update(float deltaTime)
{
    switch (state)
    {
    case IDLE:
        sprite.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
        text.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
        break;
    case HOVER:
        sprite.setColor(glm::vec3(0.8f, 0.8f, 1.0f));
        text.setColor(glm::vec3(0.8f, 0.8f, 1.0f));
        break;
    case PRESS:
        sprite.setColor(glm::vec3(0.8f, 0.8f, 1.0f));
        text.setColor(glm::vec3(0.0f, 0.0f, 1.0f));      
        break;
    case RELEASE:
        sprite.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
        text.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
        break;
    };
}

void Button::changeState(buttonState state)
{
    prevState = curState;
    curState = state;
}

void Button::draw()
{
    this->sprite.setPosition(this->position);
    this->sprite.setSize(this->size);

    text.setScale(sprite.getScale());
    text.setPosition(glm::vec2(
        (sprite.getPosition().x + sprite.getSize().x / 2) - text.getSize().x / 2,
        (sprite.getPosition().y + sprite.getSize().y / 2) - text.getSize().y / 2));

    this->sprite.draw();
    this->text.draw();
}
