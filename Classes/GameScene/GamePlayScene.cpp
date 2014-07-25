//
//  GamePlayScene.cpp
//  football
//
//  Created by MaLiang on 13-8-13.
//
//

#include "GamePlayScene.h"
#include "GameSeneMgr.h"
GamePlayScene::GamePlayScene():
m_pGamePlayLayer( nullptr )
{
    
}

GamePlayScene::~GamePlayScene()
{
    
}

//CCScene* GamePlayScene::PlayScene()
//{
//    CCScene* scene = new GamePlayScene()
//}

bool GamePlayScene::initLayer()
{
    bool b = false;
    do {
        
        //加载游戏层
        m_pGamePlayLayer = GamePlayLayer::create();
        addChild( m_pGamePlayLayer );
        
        //开启游戏场景刷新
        schedule(  schedule_selector ( GamePlayScene::update ) );
        
        b = true;
    } while ( 0 );
    
    return b;
}

void GamePlayScene::callback(Ref* obj)
{
    //CCDirector::sharedDirector() -> replaceScene( GameSceneMgr::initScene( GameScene_menu ) );
}

void GamePlayScene::update(float delta)
{
    if( NULL != m_pGamePlayLayer )
    {
        //游戏层刷新
        m_pGamePlayLayer -> update(delta);
    }
}

GamePlayLayer* GamePlayScene::getPlayLayer()
{
    return m_pGamePlayLayer;
}