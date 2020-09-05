#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <glm/glm.hpp>
#include <tinyxml/tinyxml.h>
#include "Sprite.h"
#include "shader.h"

struct Object
{
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);
    std::string name;
    std::string type;
    glm::ivec4 rect;
    std::map<std::string, std::string> properties;
    Sprite* sprite;
};

struct Layer
{
    float opacity;
    std::vector<Sprite*> tiles;
};

class Map
{
public:
    Map();
    ~Map();

    bool loadFromXML(std::string filePath);

    glm::ivec2 getTileSize();
    std::vector<Layer> getMapData();
    std::vector<Object> getObjects();

    void draw();
    void cleanup();

private:
    int firstTileID;
    glm::ivec2 size;
    glm::ivec2 tileSize;
    glm::ivec2 tilesetCR;
    glm::vec4 drawingBounds;
    Texture mapTileset;
    std::vector<Layer> layers;
    std::vector<glm::ivec4> subRects;
    std::vector<Object> objects;
};

