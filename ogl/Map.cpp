#include "Map.h"
#include <fstream>
#include <sstream>

#include "ResourceManager.h"


Map::Map()
{
    mapPosition = glm::vec3(1.0f);
}


Map::~Map()
{
    tiles.clear();
}

glm::ivec2 Map::getMapAtPoint(glm::vec2 point)
{
    return glm::ivec2(
        (int)((point.x - mapPosition.x + tileSize.x * 0.5f) / (float)(tileSize.x)),
        (int)((point.y - mapPosition.y + tileSize.y * 0.5f) / (float)(tileSize.y))
    );
}

int Map::getMapTileYAtPoint(float y)
{
    return (int)((y - mapPosition.y + tileSize.y * 0.5f) / (float)(tileSize.y));
}

int Map::getMapTileXAtPoint(float x)
{
    return (int)((x - mapPosition.x + tileSize.x * 0.5f) / (float)(tileSize.x));
}

glm::vec2 Map::getMapTilePosition(int tileIndexX, int tileIndexY)
{
    return glm::vec2(
        (float)(tileIndexX * tileSize.x) + mapPosition.x,
        (float)(tileIndexY * tileSize.y) + mapPosition.y
    );
}

glm::vec2 Map::getMapTilePosition(glm::ivec2 tileCoords)
{
    return glm::vec2(
        (float)(tileCoords.x * tileSize.x) + mapPosition.x,
        (float)(tileCoords.y * tileSize.y) + mapPosition.y
    );
}


TileType Map::getTile(int x, int y)
{
    if (x < 0 || x >= mapUnits.x
        || y < 0 || y >= mapUnits.y)
        return TileType::block;     
    return tiles[y][x];
}


bool Map::isObstacle(int x, int y)
{
    if (x < 0 || x >= mapUnits.x
        || y < 0 || y >= mapUnits.y)
        return true;
    return (tiles[y][x] == block);
}

bool Map::isGround(int x, int y)
{
    if (x < 0 || x >= mapUnits.x
        || y < 0 || y >= mapUnits.y)
        return false;
    return (tiles[y][x] == oneway || tiles[y][x] == block );
}

bool Map::isOneWay(int x, int y)
{
    if (x < 0 || x >= mapUnits.x
        || y < 0 || y >= mapUnits.y)
        return false;
    return (tiles[y][x] == oneway);
}

bool Map::isEmpty(int x, int y)
{
    if (x < 0 || x >= mapUnits.x
        || y < 0 || y >= mapUnits.y)
        return false;
    return (tiles[y][x] == empty);
}

void Map::loadFromFile(const GLchar* file)
{
    GLuint tileCode = 0;

    std::string line;
    std::fstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;

    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode)
            {
                row.push_back(tileCode);
            }
            tileData.push_back(row);
        }
    }
    if (tileData.size() > 0)
    {
        this->mapSize.x = tileData[0].size() * tileSize.x;
        this->mapSize.y = tileData.size() * tileSize.y;

        this->mapUnits.x = tileData[0].size();
        this->mapUnits.y = tileData.size();

        tiles.resize(mapUnits.y);
        for (int i = 0; i < tileData.size(); i++)
        {
            tiles[i].resize(mapUnits.x);
        }
        init(tileData);
    }
}

void Map::update(float deltaTime)
{

}

void Map::draw()
{
        for (Sprite* tile : sprites)
        {
            if (tile != nullptr)
                tile->draw();
        }
}

void Map::setUnitSize(glm::vec2 size)
{
    this->tileSize = size;
}

void Map::init(std::vector<std::vector<GLuint>> levelData)
{

    for (GLuint y = 0; y < mapUnits.y; y++)
    {
        for (GLuint x = 0; x < mapUnits.x; x++)
        {
            if (levelData[y][x] == 0)
            {
                this->tiles[y][x] = empty;

                Sprite* sprite;
                sprite = new Sprite();
                sprite->setPosition(glm::vec2(x * tileSize.x, y * tileSize.y));
                sprite->setSize(tileSize);
                sprite->setTexture(ResourceManager::getTexture("block"));
                sprite->setTextureRect(glm::vec4(64 * 0, 64 * 0, 64, 64));
                sprite->setColor(glm::vec3(1));
                sprite->setAlpha(10);
                sprites.push_back(sprite);
            }
            else if (levelData[y][x] == 1)
            {
                this->tiles[y][x] = block;

                Sprite* sprite;
                sprite = new Sprite();
                sprite->setPosition(glm::vec2(x * tileSize.x, y * tileSize.y));
                sprite->setSize(tileSize);
                sprite->setTexture(ResourceManager::getTexture("block"));
                sprite->setTextureRect(glm::vec4(64 * 0, 64 * 0, 64, 64));
                sprite->setColor(glm::vec3(0.5f, 1, 0.5f));
                sprite->setAlpha(100);
                sprites.push_back(sprite);

            }
            else if (levelData[y][x] == 2)
            {
                this->tiles[y][x] = oneway;
                
                Sprite* sprite;
                sprite = new Sprite();
                sprite->setPosition(glm::vec2(x * tileSize.x, y * tileSize.y));
                sprite->setSize(tileSize);
                sprite->setTexture(ResourceManager::getTexture("block"));
                sprite->setTextureRect(glm::vec4(64 * 1, 64 * 0, 64, 64));
                sprite->setColor(glm::vec3(0, 0, 1));
                sprite->setAlpha(100);
                sprites.push_back(sprite);
            }
            else if (levelData[y][x] == 3)
            {
                this->tiles[y][x] = block;
                
                Sprite* sprite;
                sprite = new Sprite();
                sprite->setPosition(glm::vec2(x * tileSize.x, y * tileSize.y));
                sprite->setSize(tileSize);
                sprite->setTexture(ResourceManager::getTexture("block"));
                sprite->setTextureRect(glm::vec4(64 * 0, 64 * 1, 64, 64));
                sprite->setColor(glm::vec3(1, 0, 0));
                sprite->setAlpha(100);
                sprites.push_back(sprite);
            }           
        }
    }
}
