#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <string>

class AnimationManager
{
public:
    static std::map<std::string, std::vector<glm::vec4>> animations;

    static std::vector<glm::vec4> addAnimation(std::vector<glm::vec4> frames, std::string name);
    static std::vector<glm::vec4> getAnimation(std::string name);
    static std::vector<glm::vec4> addFrames(int countFrames, glm::vec4 textureRect, GLboolean mirrored = GL_FALSE);

    static void cleanup();

private:

    AnimationManager() {}

};

