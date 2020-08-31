#include "Level.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "tinyxml/tinyxml.h"
#include "Image.h"

bool Level::loadFromFile()
{
    return false;
}

bool Level::loadFromXML(std::string Path)
{
    TiXmlDocument levelFile(Path.data());

    if (!levelFile.LoadFile())
    {
        std::cout << "Loading level: " << Path.data() << " failed" << std::endl;
        return false;
    }

    TiXmlElement* map;

    map = levelFile.FirstChildElement("map");
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    TiXmlElement* tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(map->Attribute("firstgid"));

    TiXmlElement* image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    Image img;

    if (!img.loadImageFromFile(imagepath))
    {
        std::cout << "Failed to load map tileset" << std::endl;
        return false;
    }

    tileSet.loadTextureFromImage(img);
    tileSet.smooth = false;

    int columns = tileSet.width / tileWidth;
    int rows = tileSet.height / tileHeight;

    std::vector<glm::vec4> subrects;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            glm::vec4 rect;

            rect.y = y * tileHeight;
            rect.w = tileHeight;
            rect.x = x * tileWidth;
            rect.z = tileWidth;

            subrects.push_back(rect);
        }
    }

    TiXmlElement* layerElement;
    layerElement->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;
        
        if (layerElement->Attribute("opacity") != NULL)
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;
        }

        TiXmlElement* layerDataElement;
        layerDataElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "No layer information" << std::endl;
        }

        TiXmlElement* tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        //
        //
        //
        //
        //!!!!!!
        if (tileElement == NULL)
        {
            std::cout << "No tile info" << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            if (subRectToUse >= 0)
            {
                Sprite *sprite;
                sprite = new Sprite();
                sprite->setTexture(tileSet);
                sprite->setTextureRect(subrects[subRectToUse]);
                sprite->setPosition(glm::vec2(x * tileWidth, y * tileHeight));
                sprite->setAlpha(layer.opacity);

                layer.tiles.push_back(sprite);
            }
        }

    }

    

    return false;
}

void Level::cleanup()
{
}
