//
//  GamePlayScene.h
//  
//
//  Created by MaLiang on 13-8-13.
//
//

#ifndef __football__GamePlayScene__
#define __football__GamePlayScene__

#include <iostream>
#include "cocos2d.h"
#include "GamePlayLayer.h"

using namespace cocos2d;


class GamePlayScene : public Scene
{
public:
    GamePlayScene();
    ~GamePlayScene();
    
    bool initLayer();
    void update(float delta);
    CREATE_FUNC( GamePlayScene );
    
    GamePlayLayer* getPlayLayer();
    
    
    void callback(Ref* obj);
private:
    GamePlayLayer* m_pGamePlayLayer; //游戏层

};

#endif /* defined(__football__GamePlayScene__) */
