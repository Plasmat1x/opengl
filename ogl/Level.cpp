#include "..\ogl2\Level.h"
#include "..\ogl2\Level.h"
#include "Level.h"
#include <fstream>
#include <sstream>


Level::Level()
{
}


Level::~Level()
{
    for (Entity* objects : levelObjects)
    {
        delete objects;
    }
    this->levelObjects.clear();
    this->levelData.clear();
}

void Level::setMap(std::string map)
{
}

void Level::setMap(Map& map)
{
}

void Level::loadFromFile(const GLchar* file)
{
    this->levelData.clear();
    GLuint tileCode;

    Level level;

    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
    }
    if (tileData.size() > 0)
    {
        this->levelData = tileData;
        init(tileData);
    }
    else
    {
        std::cout << "cant load level" << std::endl;
    }
}

void Level::update(float deltaTime)
{
    for (Entity* objects : levelObjects)
    {
        objects->update(deltaTime);
    }
}

void Level::draw()
{
    for (Entity* objects : levelObjects)
    {
        objects->draw();
    }
}

void Level::setUnitSize(glm::vec2 size)
{
    this->unitSize = size;
}

void Level::init(std::vector<std::vector<GLuint>> levelData)
{
    this->levelObjects.clear();
    this->levelSize.x = levelData[0].size() * unitSize.x;
    this->levelSize.y = levelData.size() * unitSize.y;

    GLuint width = levelData[0].size();
    GLuint height = levelData.size();

    for (GLuint y = 0; y < height; ++y)
    {
        for (GLuint x = 0; x < width; ++x)
        {
            if (levelData[y][x] == 1)
            {
                Entity* _object;
                _object = new Entity(glm::vec2(this->unitSize.x * x, this->unitSize.y * y), this->unitSize, "block");
                _object->sprite.setTextureRect(glm::vec4(0,0,128, 128));
                levelObjects.push_back(_object);
            }
            else if (levelData[y][x] > 1)
            {
                Entity* _object;
                _object = new Entity(glm::vec2(this->unitSize.x * x, this->unitSize.y * y), this->unitSize, "block");
                _object->sprite.setTextureRect(glm::vec4(128, 0, 128, 128));
                this->levelObjects.push_back(_object);
            }
        }
    }
}
