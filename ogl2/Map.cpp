#include "Map.h"

#include "tinyxml/tinyxml.h"


Map::Map()
{
}


Map::~Map()
{
}

/// <summary>
///   <para>use for custom level</para>
/// </summary>
bool Map::loadFromFile(std::string filePath)
{

    return true;
}

/// <summary>
///   <para>use for load from XML</para>
/// </summary>
bool Map::loadFromXML(std::string filePath)
{
    TiXmlDocument mapFile(filePath.data());

    if (!mapFile.LoadFile())
    {

    }
     

    return false;
}

std::vector<TileData> Map::getMapData()
{
    return mapData;
}
