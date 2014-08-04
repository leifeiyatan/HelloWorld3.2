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
#include "MapNode.h"
GamePlayLayer::GamePlayLayer()
{
}

GamePlayLayer::~GamePlayLayer()
{
    UnitMgr::getInterface() -> clearUnitsAll();
    
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("p1wTest.ExportJson");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("p1w.plist");
    Director::getInstance() -> getTextureCache() -> removeTextureForKey( "p1w.png" );
    
    
    log("%s\n", Director::getInstance() -> getTextureCache()->getCachedTextureInfo().c_str());
    log("%s\n", SpriteFrameCache::getInstance()->getCachedSpriteFrameInfo().c_str());
}

bool GamePlayLayer::init()
{
    //地图布局
    LayoutMap();
    
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
    Unit* player = UnitMgr::getInterface() -> getUnitByTypeAndID(UnitType_Player, 10);
    
    Vec2 tmp_pos = m_pMapNode -> convertToWorldSpace( player -> getPosition() );
    m_pMapNode -> MapMove( tmp_pos );
}

void GamePlayLayer::LayoutMap()
{
    Size visSize = Director::getInstance() -> getVisibleSize();
    
    auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("isometric_grass_and_water.tmx"));
    m_pMapNode = MapNode::createWithXML(str->getCString(),"");
    m_pMapNode -> setAnchorPoint( Point(0.5f,0.5f) );
    m_pMapNode -> setScale( 2 );
    m_pMapNode -> setPosition( Point( visSize.width / 2,visSize.height / 2 - 500) );
    addChild( m_pMapNode );
    
    m_pMapNode -> drawDebugMesh();
}

void GamePlayLayer::LayoutUnit()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("p1w.png","p1w.plist","p1wTest.ExportJson" );
    
    //        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("p1w.plist");
    //ArmatureDataManager::getInstance()->addArmatureFileInfo("p1w.png","p1w.plist","p1wTest.ExportJson" );
    
    Label* abc = Label::createWithSystemFont("O", "Arial", 24);
    abc -> setPosition( Point(0,0) );
    addChild( abc,5 );
    
    Label* pla = Label::createWithSystemFont("A", "Arial", 24);
    Vec2 vec(0,0);
    //Vec2 unitPos = m_pMapNode -> MapCoordiConvertPos( vec );
    pla -> setPosition( Vec2(800,800) );
    m_pMapNode -> addChild( pla );
    
    LivingData* data = new LivingData();
    data -> setLivingID( 1 );
    data -> setSpeed( 5 );
    data -> setAttackValue( 10 );
    
    LivingUnit* unit = LivingUnit::create( data );
//    unit -> setPosition( Point (480,320) );
    unit -> setTag( 10 );
    unit -> setUnitType( UnitType_Player );
    unit -> AttackCallBackFun = std::bind(&GamePlayLayer::Attacks, this, std::placeholders::_1,std::placeholders::_2);
//    addChild( unit );
//    
//    
//    LivingData* data2 = new LivingData();
//    data2 -> setLivingID( 2 );
//    data2 -> setSpeed( 5 );
//    
//    LivingUnit* unit2 = LivingUnit::create( data2 );
//    unit2 -> setPosition( Point (600,320) );
//    unit2 -> setTag( 20 );
//    unit2 -> setUnitType( UnitType_NPC );
//    addChild( unit2 );
//
//    LivingUnit* unit3 = LivingUnit::create( data );
//    unit3 -> setPosition( Point (800,600) );
//    unit3 -> setTag( 30 );
//    unit3 -> setUnitType( UnitType_NPC );
//    addChild( unit3 );
    
//    UnitMgr::getUnitMgr() -> addUnit( unit );
//    UnitMgr::getUnitMgr() -> addUnit( unit2 );

    unit -> setTag( 10 );
    unit -> setUnitType( UnitType_Player );
    unit -> AttackCallBackFun = std::bind(&GamePlayLayer::Attacks, this, std::placeholders::_1,std::placeholders::_2);
    unit -> playWalkAnim();
    addUnitForMap( unit,Vec2(0,0) );
    
    unit -> setScale( 0.5 );
    
    
    
    
    
//    LivingData* data2 = new LivingData();
//    data2 -> setLivingID( 2 );
//    data2 -> setSpeed( 5 );
//    
//    LivingUnit* unit2 = LivingUnit::create( data2 );
//    unit2 -> setPosition( Point (600,320) );
//    unit2 -> setTag( 20 );
//    unit2 -> setUnitType( UnitType_NPC );
//    addChild( unit2 );
//
//    LivingUnit* unit3 = LivingUnit::create( data );
//    unit3 -> setPosition( Point (800,600) );
//    unit3 -> setTag( 30 );
//    unit3 -> setUnitType( UnitType_NPC );
//    addChild( unit3 );
    
    
//    UnitMgr::getUnitMgr() -> addUnit( unit2 );

//    UnitMgr::getUnitMgr() -> addUnit( unit3 );
    

    log("%s\n", Director::getInstance() -> getTextureCache()->getCachedTextureInfo().c_str());
    log("%s\n", SpriteFrameCache::getInstance()->getCachedSpriteFrameInfo().c_str());

}

void GamePlayLayer::addUnitForMap( Unit* unit,Vec2 tileCoord )
{
    Point unitPos = m_pMapNode -> MapCoordiConvertPos( tileCoord );
    unit -> setPosition( unitPos );
    m_pMapNode -> addChild( unit );
    UnitMgr::getInterface() -> addUnit( unit );
}

void GamePlayLayer::Attacks( LivingUnit* AttUnit, LivingUnit* UAttUnit )
{
    int DamageValue = AttUnit -> getCurLivingData() -> getAttackValue();
    UAttUnit -> hurt( DamageValue );
}

bool GamePlayLayer::onTouchBegan(Touch* touch, Event* event)
{
    Point touchPos = touch -> getLocation();
    LivingUnit* unit = static_cast<LivingUnit*>( UnitMgr::getInterface() -> getUnitByTypeAndID(UnitType_Player, 10) );
    
    Point MapPos = m_pMapNode -> PosConvertMapCoodi( touchPos );
    unit -> setNextPos( m_pMapNode -> MapCoordiConvertPos( MapPos ) );
    unit -> move();
    //unit -> attack( (LivingUnit*)getChildByTag(20) );
    
    

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

