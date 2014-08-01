//
//  GamePlayLayer.h
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-22.
//
//

#ifndef __HelloWorld3_2__GamePlayLayer__
#define __HelloWorld3_2__GamePlayLayer__

#include "cocos2d.h"
USING_NS_CC;

#include "CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;

class Unit;
class LivingUnit;
class MapNode;

class GamePlayLayer : public Layer
{
public:
    GamePlayLayer();
    virtual ~GamePlayLayer();
    
    virtual bool init();
    void update(float delta);
    
    void LayoutMap();
    void LayoutUnit();
    void addUnitForMap( Unit* unit,Vec2 tileCoord );
    
    void Attacks( LivingUnit* AttUnit, LivingUnit* UAttUnit );
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    
    MapNode* m_pMapNode;
    CREATE_FUNC( GamePlayLayer );
    
    //void menuCloseCallback(Ref* pSender);
};

#endif /* defined(__HelloWorld3_2__GamePlayLayer__) */
