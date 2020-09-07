 #pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <map>

#include "Sprite.h"
#include "Texture.h"
#include "Map.h"
#include "Camera.h"

class Level
{
public:
    Level();
    ~Level();

    void setMap(std::string map);
    void setMap(Map map);
    Map getMap();

    void update(float delta);
    void draw();
    void cleanup();

    Camera* cam;

    Sprite* sprite;

private:
    Map map;

    std::vector<Object> objects;
};

