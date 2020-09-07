#include "Level.h"
#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

Level::Level()
{
    Texture texture;
    texture.loadTextureFromImage(ResourceManager::getImage("sprite"));
    sprite = new Sprite("sprite");
    sprite->setShader(ResourceManager::getShader("sprite"));
    sprite->setTexture(texture);
    sprite->setPosition(100, 100);
    sprite->setSize(64, 128);
    sprite->setColor(1.0f, 0.0f, 0.0f);

    cam = new Camera(sprite->getPosition());
    cam->setOffset(32, 64);
}

Level::~Level()
{
    cleanup();
}

void Level::setMap(std::string _map)
{
    map.loadFromXML(_map);
}

void Level::setMap(Map _map)
{
    map = _map;
}

void Level::update(float delta)
{
    cam->update();
    cam->setPosition(sprite->getPosition());
    ResourceManager::getShader("sprite").SetMatrix4("view", cam->getMatrixView(), GL_TRUE);
}

void Level::draw()
{
    map.draw();
    sprite->draw();
}

void Level::cleanup()
{
    delete cam;
    delete sprite;
}