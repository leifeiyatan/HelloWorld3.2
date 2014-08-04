//
//  GameMapLayer.cpp
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-30.
//
//

#include "MapNode.h"



MapNode::MapNode()
:m_rcMapMoveLimit(Rect::ZERO)
{
    
}

MapNode::~MapNode()
{
    
}

MapNode* MapNode::createWithXML(const std::string& tmxString, const std::string& resourcePath)
{
    MapNode *ret = new MapNode();
    if (ret->initWithXML(tmxString, resourcePath))
    {
        ret->init();
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


bool MapNode::init()
{
    initMapMoveLimit();
    return true;
}

void MapNode::initMapMoveLimit()
{
    Size visSize = Director::getInstance() -> getVisibleSize();
    m_rcMapMoveLimit.origin.x = visSize.width / 2 - visSize.width / 8;
    m_rcMapMoveLimit.origin.y = visSize.height / 2 - visSize.height / 8;
    m_rcMapMoveLimit.size.width = visSize.width / 4;
    m_rcMapMoveLimit.size.height = visSize.height / 4;
}

Vec2 MapNode::MapCoordiConvertPos( Vec2 &tileCoord )
{
    FastTMXLayer* pLayer = getLayer("background");
    
    //取得的像素坐标为块坐标的 y正中间 x最左边
    Vec2 pos = pLayer-> getPositionAt( tileCoord - Vec2(0, 1) );
    
    Size tileSize = getTileSize();
    
    //tilemap偏移
    //x 位移正中间
//    pos.x += tileSize.width / 2;
    pos.y += tileSize.height / 2;
    return pos;
}

Vec2 MapNode::PosConvertMapCoodi( Vec2 &Pos )
{
    // Tilemap position must be subtracted, in case the tilemap position is not at 0,0 due to scrolling
    Size Contentsize = getContentSize();
    Size mapSize = getMapSize();
    Size tileSize = getTileSize();
    float halfMapWidth = mapSize.width * 0.5f;
    float mapHeight = mapSize.height;
    float tileWidth = tileSize.width;
    float tileHeight = tileSize.height;
    
    //tilemap偏移
    Pos.y -= tileHeight / 2 * getScale();
    
    //不会随放大缩小改变位置
    Pos = convertToNodeSpace( Pos );
    
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

void MapNode::drawDebugMesh()
{
    Size Contentsize = getContentSize();
    Size mapSize = getMapSize();
    Size tileSize = getTileSize();
    
    Vec2 originPos = Vec2( Contentsize.width / 2,Contentsize.height );
    Vec2 overPos = Vec2( Contentsize.width, Contentsize.height / 2 );
    //tilemap偏移
    originPos.y += tileSize.height / 2;
    overPos.y += tileSize.height / 2;
    
    DrawNode* pNode = nullptr;
    pNode = DrawNode::create();
    addChild(pNode);
    for( int i = 0; i < mapSize.width; i ++ )
    {
        
        if ( i != 0 )
        {
            originPos.x -= tileSize.width / 2;
            originPos.y -= tileSize.height / 2;
            overPos.x -= tileSize.width / 2;
            overPos.y -= tileSize.height / 2;
        }

        pNode -> drawSegment(originPos, overPos, 0.5, Color4F::WHITE);
        
    }
    
    originPos = Vec2( Contentsize.width / 2,Contentsize.height );
    overPos = Vec2( 0, Contentsize.height / 2 );
    //tilemap偏移
    originPos.y += tileSize.height / 2;
    overPos.y += tileSize.height / 2;
    
    for( int i = 0; i < mapSize.height; i ++ )
    {
        
        if ( i != 0 )
        {
            originPos.x += tileSize.width / 2;
            originPos.y -= tileSize.height / 2;
            overPos.x += tileSize.width / 2;
            overPos.y -= tileSize.height / 2;
        }
        
        pNode -> drawSegment(originPos, overPos, 0.5, Color4F::WHITE);
    }
//    Vec2 vec[4] = { originPos,overPos,Vec2(Contentsize.width / 2,0),Vec2( 0,Contentsize.height / 2 ) };
//    pNode -> drawPolygon(vec, 4, Color4F::WHITE, 0.5, Color4F::WHITE);
}

void MapNode::MapMove( Vec2 &RefPos )
{
    //CCLOG( "curMapPos MoveBefore x = %d, y = %d", (int)getPosition().x, (int)getPosition().y );
    
    Vec2 tmp_CurPos = getPosition();
    float tmp_DisPosX = 0;
    float tmp_DisPosY = 0;
    
    if( RefPos.x < m_rcMapMoveLimit.getMinX() )
    {
        tmp_DisPosX = m_rcMapMoveLimit.getMinX() - RefPos.x;
    }
    else if( RefPos.x > m_rcMapMoveLimit.getMaxX() )
    {
        tmp_DisPosX = m_rcMapMoveLimit.getMaxX() - RefPos.x;
    }
    
    if( RefPos.y < m_rcMapMoveLimit.getMinY() )
    {
        tmp_DisPosY = m_rcMapMoveLimit.getMinY() - RefPos.y;
    }
    else if( RefPos.y > m_rcMapMoveLimit.getMaxY() )
    {
        tmp_DisPosY = m_rcMapMoveLimit.getMaxY() - RefPos.y;
    }
    
    setPosition( Vec2( tmp_CurPos.x + tmp_DisPosX,tmp_CurPos.y + tmp_DisPosY ) );
    
    //CCLOG( "curMapPos MoveLater x = %d, y = %d", (int)getPosition().x, (int)getPosition().y );
}

