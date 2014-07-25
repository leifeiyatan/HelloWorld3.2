//
//  GameSeneMgr.h
//
//
//  Created by MaLiang on 13-8-27.
//
//

#ifndef __football__GameSeneMgr__
#define __football__GameSeneMgr__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

#include "GamePlayScene.h"

typedef enum
{
    GameScene_None,
    GameScene_menu,
    GameScene_Play, //游戏场景
}GameScene_tag;

class GameSceneMgr
{
public:
    GameSceneMgr();
    ~GameSceneMgr();
    
    //初始化场景 根据标示
    static Scene* initScene( GameScene_tag Tag );
    //获取运行场景
    static Scene* getRunScene( GameScene_tag Tag );
    
//    static GameSceneMgr* GetGameSceneMgr();
//    static GameSceneMgr* G_PGameSceneMgr;
};

#define GET_GAMESCENE(iTag) GameSceneMgr::getRunScene(iTag)
#define GET_GAMELAYER ((GamePlayScene*)GET_GAMESCENE(GameScene_Play)) -> getPlayLayer()

#endif /* defined(__football__GameSeneMgr__) */
