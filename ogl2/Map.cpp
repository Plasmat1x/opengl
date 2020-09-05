#include "Map.h"

//#include "tinyxml/tinyxml.h"
#include "ResourceManager.h"


Map::Map()
{
}


Map::~Map()
{
    cleanup();
}

/// <summary>
///   <para>use for load from XML</para>
/// </summary>
bool Map::loadFromXML(std::string filePath)
{
    TiXmlDocument mapFile(filePath.data());

    if (!mapFile.LoadFile())
    {
        std::cout << "Error load map: " << filePath << std::endl;
        return false;
    }

    // map conteiner
    TiXmlElement* tmap;
    tmap = mapFile.FirstChildElement("map");
    size.x = atoi(tmap->Attribute("width"));
    size.y = atoi(tmap->Attribute("height"));
    tileSize.x = atoi(tmap->Attribute("tilewidth"));
    tileSize.y = atoi(tmap->Attribute("tileheight"));

    // tileset
    TiXmlElement* ttilesetElement;
    ttilesetElement = tmap->FirstChildElement("tileset");
    firstTileID = atoi(ttilesetElement->Attribute("firstgid"));

    // source
    TiXmlElement* timage;
    timage = ttilesetElement->FirstChildElement("image");
    std::string imageSource = timage->Attribute("source");
    Image image;
    
    if (!image.loadImageFromFile(imageSource))
    {
        std::cout << "Error map can't load image from " << imageSource << std::endl;
        return false;
    }
    mapTileset.smooth = false;
    mapTileset.generateFromImage(image);
    tilesetCR.x = mapTileset.width / tileSize.x;
    tilesetCR.y = mapTileset.height / tileSize.y;
    
    for (int y = 0; y < tilesetCR.y; y++)
    {
        for (int x = 0; x < tilesetCR.x; x++)
        {
            glm::ivec4 rect;
            rect.x = x * tileSize.x;
            rect.z = tileSize.x;
            rect.y = y * tileSize.y;
            rect.w = tileSize.y;

            subRects.push_back(rect);
        }
    }

    // layers

    TiXmlElement* layerElement;
    layerElement = tmap->FirstChildElement("layer");
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

        // layer container <data>
        TiXmlElement* layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Warning no layer information found." << std::endl;
        }

        TiXmlElement* tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL)
        {
            // may create problem with no tile zone on map (need draw empty tile);
            std::cout << "Error no tile" << std::endl;
            return false;
        }

        glm::ivec2 pos(0);
        while (tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            if (subRectToUse >= 0)
            {
                Sprite* sprite;
                sprite = new Sprite("sprite");
                sprite->setTexture(mapTileset);
                sprite->setTextureRect(subRects[subRectToUse]);
                sprite->setSize(tileSize);
                sprite->setPosition(glm::vec2(pos.x * tileSize.x, pos.y * tileSize.y));
                sprite->setAlpha(layer.opacity);

                layer.tiles.push_back(sprite);
            }
            tileElement = tileElement->NextSiblingElement("tile");

            pos.x++;
            if (pos.x >= size.x)
            {
                pos.x = 0;
                pos.y++;
                if (pos.y >= size.y)
                    pos.y = 0;
            }
        }
        layers.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }

    TiXmlElement* objectGroupElement;

    if (tmap->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = tmap->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            // Контейнер <object>
            TiXmlElement* objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement)
            {
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                Sprite* sprite;
                sprite = new Sprite("sprite");
                sprite->setTexture(mapTileset);
                sprite->setTextureRect(glm::vec4(0, 0, 0, 0));
                sprite->setPosition(x, y);
                sprite->setSize(tileSize);

                if (objectElement->Attribute("width") != NULL)
                {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                }
                else
                {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].z;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].w;
                    sprite->setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                // Экземпляр объекта
                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                glm::ivec4 objectRect;
                objectRect.y = y;
                objectRect.x = x;
                objectRect.w = height;
                objectRect.z = width;
                object.rect = objectRect;

                // "Переменные" объекта
                TiXmlElement* properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    TiXmlElement* prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while (prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                // Пихаем объект в вектор
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "Warning object layers not found" << std::endl;
    }

    return true;
}

glm::ivec2 Map::getTileSize()
{
    return tileSize;
}

std::vector<Layer> Map::getMapData()
{
    return layers;
}

std::vector<Object> Map::getObjects()
{
    return objects;
}

void Map::draw()
{
    for (auto layer : layers)
    {
        for (auto* tile : layer.tiles)
        {
            tile->draw();
        }
    }
}

void Map::cleanup()
{
    for (auto layer : layers)
    {
        for (auto* tile : layer.tiles)
        {
            delete tile;
        }
    }
}

int Object::GetPropertyInt(std::string name)
{
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name)
{
    return properties[name];
}
