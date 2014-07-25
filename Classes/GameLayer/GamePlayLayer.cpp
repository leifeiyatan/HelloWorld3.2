//
//  GamePlayLayer.cpp
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-22.
//
//

#include "GamePlayLayer.h"
#include "LivingUnit.h"
#include "UnitMgr.h"
GamePlayLayer::GamePlayLayer()
{
}

GamePlayLayer::~GamePlayLayer()
{
    UnitMgr::getUnitMgr() -> clearUnitsAll();
    
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("p1wTest.ExportJson");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("p1w.plist");
    Director::getInstance() -> getTextureCache() -> removeTextureForKey( "p1w.png" );
    
    
    log("%s\n", Director::getInstance() -> getTextureCache()->getCachedTextureInfo().c_str());
    log("%s\n", SpriteFrameCache::getInstance()->getCachedSpriteFrameInfo().c_str());
}

bool GamePlayLayer::init()
{
    //单位布局
    LayoutUnit();
    
    EventDispatcher* event = Director::getInstance() -> getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener -> setSwallowTouches( true );
    listener -> onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
    listener -> onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
    event -> addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

void GamePlayLayer::update(float delta)
{
    
}

void GamePlayLayer::LayoutUnit()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("p1w.png","p1w.plist","p1wTest.ExportJson" );
    
    //        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("p1w.plist");
    //ArmatureDataManager::getInstance()->addArmatureFileInfo("p1w.png","p1w.plist","p1wTest.ExportJson" );
    
    Label* pla = Label::createWithSystemFont("0", "Arial", 24);
    pla -> setPosition( Point(480,320) );
    addChild( pla );
    
    LivingUnit* unit = LivingUnit::createByDirection( State::Unit_State_Walk, Direction::Unit_Direction_LEFTUP );
    unit -> setPosition( Point (0,0) );
    unit -> setTag( 10 );
    unit -> setUnitType( UnitType_Player );
    addChild( unit );
    
    LivingUnit* unit2 = LivingUnit::createByDirection( State::Unit_State_Walk, Direction::Unit_Direction_LEFTUP );
    unit2 -> setPosition( Point (480,320) );
    unit2 -> setTag( 20 );
    unit2 -> setUnitType( UnitType_NPC );
    addChild( unit2 );
    
    LivingUnit* unit3 = LivingUnit::createByDirection( State::Unit_State_Walk, Direction::Unit_Direction_LEFTUP );
    unit3 -> setPosition( Point (800,600) );
    unit3 -> setTag( 30 );
    unit3 -> setUnitType( UnitType_NPC );
    addChild( unit3 );
    
    UnitMgr::getUnitMgr() -> addUnit( unit );
    UnitMgr::getUnitMgr() -> addUnit( unit2 );
    UnitMgr::getUnitMgr() -> addUnit( unit3 );
    

    log("%s\n", Director::getInstance() -> getTextureCache()->getCachedTextureInfo().c_str());
    log("%s\n", SpriteFrameCache::getInstance()->getCachedSpriteFrameInfo().c_str());
    
    log("branch1");

}

//void GamePlayLayer::menuCloseCallback(Ref* pSender)
//{
//
//}


bool GamePlayLayer::onTouchBegan(Touch* touch, Event* event)
{
    Point touchPos = touch -> getLocation();
    LivingUnit* unit = static_cast<LivingUnit*>( UnitMgr::getUnitMgr() -> getUnitByTypeAndID(UnitType_Player, 10) );
    unit -> setNextPos( touchPos );
    unit -> move();
    return true;
}

void GamePlayLayer::onTouchEnded(Touch* touch, Event* event)
{
    //Map<ID_key,Unit*>* m = UnitMgr::getUnitMgr() -> getUnitsByType( UnitType_NPC );
    
//    UnitMgr::getUnitMgr() -> clearUnitsAll();
//    removeChildByTag( 10 );
//    removeChildByTag( 20 );
//    removeChildByTag( 30 );
    

//    Director::getInstance() -> replaceScene( Scene::create() );
}

