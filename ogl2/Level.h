 #pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <map>

#include "Sprite.h"
#include "Texture.h"

struct Object
{
    glm::vec2 size;
    glm::vec2 position;
    Sprite* sprite;
};

struct Layer
{
    float opacity;
    std::vector<Sprite*> tiles;
};

class Level
{
public:

    bool loadFromFile();
    bool loadFromXML(std::string Path);

    void draw();

    void cleanup();

private:

    int width; 
    int height;
    int tileWidth;
    int tileHeight;
    int firstTileID;

    Texture tileSet;

    std::vector<Layer> mapData;

};

