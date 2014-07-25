//
//  GameSeneMgr.cpp
//  football
//
//  Created by MaLiang on 13-8-27.
//
//

#include "GameSeneMgr.h"

//GameSceneMgr* G_PGameSceneMgr = NULL;

GameSceneMgr::GameSceneMgr()
{
    
}

GameSceneMgr::~GameSceneMgr()
{
    
}

//GameSceneMgr* GameSceneMgr::GetGameSceneMgr()
//{
//    if( NULL == G_PGameSceneMgr )
//    {
//        G_PGameSceneMgr = new GameSceneMgr();
//    }
//    return G_PGameSceneMgr;
//}

Scene* GameSceneMgr::initScene( GameScene_tag Tag )
{
    Scene* scene = NULL;
    int i = Tag;
    switch ( i )
    {
        case GameScene_Play:
        {
            scene = GamePlayScene::create();
            GamePlayScene *PlayScene = (GamePlayScene*)scene;
            PlayScene -> initLayer();
        }
            break;
        case GameScene_menu:
        {
            scene = CCTransitionZoomFlipX::create(1, CCScene::create());
            
        }
            break;
    }
    
    scene -> setTag( Tag );
    return scene;
}

Scene* GameSceneMgr::getRunScene( GameScene_tag Tag )
{
    Scene* scene = CCDirector::getInstance() -> getRunningScene();
    
    //如果所取得场景 不是认定场景
    if( scene -> getTag() != Tag )
    {
        scene = NULL;
    }
    
    return scene;
}