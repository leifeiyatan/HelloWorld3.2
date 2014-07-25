//
//  BaseDataMgr.cpp
//  football
//
//  Created by MaLiang on 13-8-29.
//
//

#include "BaseDataMgr.h"

BaseDataMgr* BaseDataMgr::G_PBaseDataMgr = NULL;
BaseDataMgr::BaseDataMgr()
{

}

BaseDataMgr::~BaseDataMgr()
{

}

BaseDataMgr* BaseDataMgr::GetBaseDataMgr()
{
    if( NULL == G_PBaseDataMgr )
    {
        G_PBaseDataMgr = new BaseDataMgr();
        G_PBaseDataMgr -> init();
    }
    return G_PBaseDataMgr;
}

void BaseDataMgr::PurgeBaseDataMgr()
{
    Director::getInstance() -> getScheduler() -> unscheduleAllForTarget( G_PBaseDataMgr );
    CC_SAFE_DELETE( G_PBaseDataMgr );
}

bool BaseDataMgr::init()
{
    
    
    return true;
}

void BaseDataMgr::Update( float dt )
{
    
}
