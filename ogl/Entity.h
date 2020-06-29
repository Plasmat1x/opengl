#pragma once

#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Sprite.h"
#include "Tools.h"

class Entity
{
public:
    Sprite sprite;

    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 collisionModel;

    Entity(glm::vec2 position, glm::vec2 size, std::string name);
    ~Entity();

    void init(std::string name);
    void update(GLfloat deltaTime);
    void draw();

    //bool AABB(glm::vec4 rect);
    void setPosition(glm::vec2 position);
    void setSize(glm::vec2 size);
    
    Sprite& getSprite();
    glm::vec2 getPosition();
    glm::vec2 getSize();

private:

};

