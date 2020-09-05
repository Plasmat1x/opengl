#include "Level.h"
#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "tinyxml/tinyxml.h"

Level::Level()
{

}

Level::~Level()
{

}

void Level::setMap(std::string _map)
{
    map.loadFromXML(_map);
}

void Level::setMap(Map& _map)
{
    map = _map;
}

void Level::draw()
{
    map.draw();
}

void Level::cleanup()
{

}