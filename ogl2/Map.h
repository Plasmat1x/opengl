#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <glm/glm.hpp>

struct TileData
{
    int index;
    glm::vec2 position;
    glm::vec2 size;
};

class Map
{
public:
    Map();
    ~Map();

    bool loadFromFile(std::string filePath);
    bool loadFromXML(std::string filePath);
    std::vector<TileData> getMapData();

private:

    std::vector<TileData> mapData;

};

