#include "Animation.h"
#include "AnimationManager.h"

void Animation::playAnimation(std::string name, float deltaTime, Sprite &sprite)
{
    sprite.setTextureRect(AnimationManager::getAnimation(name)[(int)currentFrame]);

    currentFrame += (deltaTime * speed);

    if (currentFrame > AnimationManager::getAnimation(name).size())
    {     
        currentFrame -= AnimationManager::getAnimation(name).size();
    }
}

void Animation::_playAnimation(std::string name, float deltaTime, Sprite& sprite)
{
    
}

void Animation::setSpeedAnimation(float speed)
{
    this->speed = speed;
}
/*
code part for animation 
if (currentFrame > AnimationManager::getAnimation(name).size())
    {
        reverse = true;
    }

    if (currentFrame < 1)
    {
        reverse = false;
    }

    switch ((int)currentFrame)
    {
    case 0:
        reverCF = 0;
        break;
    case 1:
        reverCF = 1;
        break;
    case 2:
        reverCF = 2;
        break;
    case 3:
        reverCF = 3;
        break;
    case 4:
        reverCF = 4;
        break;
    case 5:
        reverCF = 5;
        break;
    }

    sprite.setTextureRect(AnimationManager::getAnimation(name)[reverCF]);

    if (!reverse)
    {
        currentFrame += (deltaTime * speed);
    }
    else
    {
        currentFrame -= (deltaTime * speed);
    }
*/