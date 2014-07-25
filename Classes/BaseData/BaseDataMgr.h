//
//  BaseDataMgr.h
//  
//
//  Created by MaLiang on 13-8-29.
//
//

#ifndef __football__BaseDataMgr__
#define __football__BaseDataMgr__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

//#define GRABBALL_CD 0.5 //抢断cd

class BaseDataMgr : public Ref
{
public:
    BaseDataMgr();
    ~BaseDataMgr();
    
    static BaseDataMgr* GetBaseDataMgr();
    static void PurgeBaseDataMgr();
    static BaseDataMgr* G_PBaseDataMgr;
    
    bool init();
    void Update( float dt );
    

};

#endif /* defined(__football__BaseDataMgr__) */
