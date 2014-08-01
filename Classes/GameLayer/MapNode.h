//
//  GameMapLayer.h
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-30.
//
//

#ifndef __HelloWorld3_2__GameMapLayer__
#define __HelloWorld3_2__GameMapLayer__
#include "cocos2d.h"
#include "CCFastTMXTiledMap.h"
#include "CCFastTMXLayer.h"
using namespace cocos2d;

class MapNode : public Node
{
public:
    MapNode();
    virtual ~MapNode();
    
    bool init();
    
    Vec2 MapCoordiConvertPos( Vec2 &tileCoord);
    Vec2 PosConvertMapCoodi( Vec2 &Pos);
    
    FastTMXTiledMap* m_pMap;
    
    CREATE_FUNC( MapNode );
    //cocos2d::experimental::FastTMXTiledMap* m_pMap;
};

#endif /* defined(__HelloWorld3_2__GameMapLayer__) */
