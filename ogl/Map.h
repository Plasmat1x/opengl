#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Entity.h"
#include "Sprite.h"

enum TileType
{
    empty,
    block,
    oneway
};

class Map
{
public:

    /*
    enum TileType
    {
        empty,
        block,
        oneway,
        platform
    };
    */

    std::vector<std::vector<TileType>> tiles;
    std::vector<Sprite*> sprites;
    glm::ivec2 mapUnits;
    glm::vec2 tileSize;
    glm::vec2 mapSize;
    glm::vec3 mapPosition;

    Map();
    ~Map();

    glm::ivec2 getMapAtPoint(glm::vec2 point);
    int getMapTileYAtPoint(float y);
    int getMapTileXAtPoint(float x);
    glm::vec2 getMapTilePosition(int tileIndexX, int tileIndexY);
    glm::vec2 getMapTilePosition(glm::ivec2 tileCoords);

    TileType getTile(int x, int y);
    bool isObstacle(int x, int y);
    bool isGround(int x, int y);
    bool isOneWay(int x, int y);
    bool isEmpty(int x, int y);

    void loadFromFile(const GLchar* file);
    void update(float deltaTime);
    void draw();
    void setUnitSize(glm::vec2 size);

private:
    void init(std::vector<std::vector<GLuint>> levelData);
};

