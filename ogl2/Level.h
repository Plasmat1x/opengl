 #pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <map>

#include "Sprite.h"
#include "Texture.h"
#include "Map.h"

class Level
{
public:
    Level();
    ~Level();

    void setMap(std::string map);
    void setMap(Map& map);

    void draw();
    void cleanup();

private:
    Map map;

    std::vector<Object> objects;
};

