#include "AnimationManager.h"

std::map<std::string, std::vector<glm::vec4>> AnimationManager::animations;

std::vector<glm::vec4> AnimationManager::addAnimation(std::vector<glm::vec4> frames, std::string name)
{
    animations[name] = frames;
    return animations[name];
}

std::vector<glm::vec4> AnimationManager::getAnimation(std::string name)
{
    return animations[name];
}

std::vector<glm::vec4> AnimationManager::addFrames(int countFrames, glm::vec4 textureRect, GLboolean mirrored)
{
    std::vector<glm::vec4> frames;
    frames.clear();

    for (int i = 0; i < countFrames; i++)
    {
        if (mirrored)
        {
            frames.push_back(glm::vec4(textureRect.x * i + textureRect.x, textureRect.y, -(textureRect.z), textureRect.w));
        }
        else
        { 
            frames.push_back(glm::vec4(textureRect.x * i, textureRect.y, textureRect.z, textureRect.w));
        }
    }

    return frames;
}

void AnimationManager::cleanup()
{
    animations.clear();
}
