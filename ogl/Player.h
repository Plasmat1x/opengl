#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <cmath>

#include "Texture.h"
#include "Entity.h"
#include "Animation.h"
#include "MovingObject.h"
#include "Tools.h"

class Player :
    public Entity , public MovingObject
{
public:

    enum State
    {
        IDLE,
        RUN,
        JUMP,
        FALL,
        WALL
    };

    enum KeyInput
    {
        NPK,
        LEFT,
        RIGHT,
        DOWN,
        UP,
        count
    };

    enum Direction
    {
        _LEFT,
        _RIGHT
    };

    glm::vec4 collisionModel;
    glm::vec2 collisionModelSize;
    float collisionModelSize_in;

    GLboolean mInputs[5];
    GLboolean mPrevInputs[5];

    State currentState;
    Direction direction;
    KeyInput curInput;
    KeyInput prevInput;

    Animation animation_idle;
    Animation animation_run;
    Animation animation_jump;
    Animation animation_fall;
    Animation animation_wall;

    float speedAnim = 7.0f;
    glm::vec2 speed;

    Player(glm::vec2 position, glm::vec2 size, std::string texture);
    ~Player();

    void update(float deltaTime);
    void characterUpdate(float deltaTime);
    void updatePrevInput(float deltaTime);
    void setupCollisionModel(glm::vec2 size);
    void draw();
    
    bool released(KeyInput key);
    bool keyState(KeyInput key);
    bool pressed(KeyInput key);

private:
};

