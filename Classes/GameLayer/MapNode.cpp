//
//  GameMapLayer.cpp
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-30.
//
//

#include "MapNode.h"



MapNode::MapNode()
:m_pMap( nullptr )
{
    
}

MapNode::~MapNode()
{
    
}

bool MapNode::init()
{
    auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("isometric_grass_and_water.tmx"));
    m_pMap = FastTMXTiledMap::createWithXML(str->getCString(),"");
    m_pMap -> setAnchorPoint( Point(0.5f,0.5f) );
    //m_pMap -> setScale( 3 );

    addChild( m_pMap );
    
    
    return true;
}


Vec2 MapNode::MapCoordiConvertPos( Vec2 &tileCoord )
{
    FastTMXLayer* pLayer = m_pMap -> getLayer("background");
    //pLayer->getp
    Vec2 pos = pLayer-> getPositionAt( tileCoord );
    return pos;
}

Vec2 MapNode::PosConvertMapCoodi( Vec2 &Pos )
{
    // Tilemap position must be subtracted, in case the tilemap position is not at 0,0 due to scrolling
    Size Contentsize = m_pMap -> getContentSize();
    Size mapSize = m_pMap->getMapSize();
    Size tileSize = m_pMap->getTileSize();
    //tileSize.width *= m_pMap->getScale();
    //tileSize.height *= m_pMap->getScale();

    float halfMapWidth = mapSize.width * 0.5f;
    float mapHeight = mapSize.height;
    float tileWidth = tileSize.width;
    float tileHeight = tileSize.height;
    
    Pos = m_pMap -> convertToNodeSpace( Pos );
    
    Point tilePosDiv = Point(Pos.x / tileWidth, Pos.y / tileHeight);
    
    //tilemap 坐标系相反
    float inverseTileY = mapHeight - tilePosDiv.y;

    
    float posX = (int)(inverseTileY + tilePosDiv.x - halfMapWidth);
    float posY = (int)(inverseTileY - tilePosDiv.x + halfMapWidth);
    

    posX = MAX(0, posX);
    posX = MIN(mapSize.width - 1, posX);
    posY = MAX(0, posY);
    posY = MIN(mapSize.height - 1, posY);
    
    Vec2 Coordi = Point(posX, posY);
    
    CCLOG("touch at (%.0f, %.0f) is at tileCoord (%i, %i)", Pos.x, Pos.y, (int)Coordi.x, (int)Coordi.y);
    
    return Coordi;
}

