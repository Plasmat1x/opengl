#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Entity.h"

class Level
{
public:

    enum TileType
    {
        empty,
        block,
        oneway,
        platform
    };

    std::vector<std::vector<GLuint>> levelData;
    std::vector<Entity*> levelObjects;
    glm::vec2 unitSize;
    glm::vec2 levelSize;

    Level();
    ~Level();

    void loadFromFile(const GLchar* file);
    void update(float deltaTime);
    void draw();

    void setUnitSize(glm::vec2 size);

private:
    void init(std::vector<std::vector<GLuint>> levelData);
};

