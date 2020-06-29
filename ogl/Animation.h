#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Sprite.h"

class Animation
{
public:
    void playAnimation(std::string name, float deltaTime, Sprite &sprite);
    void _playAnimation(std::string name, float deltaTime, Sprite &sprite);

    void setSpeedAnimation(float speed);

private:

    float speed = 5.0f;
    float currentFrame = 0;
    bool reverse = false;

    int reverCF = 0;

};

