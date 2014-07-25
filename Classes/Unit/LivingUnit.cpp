//
//  LivingUnit.cpp
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-17.
//
//

#include "LivingUnit.h"

LivingUnit::LivingUnit( State sta, Direction dic )
:m_sState(sta)
,m_dDirection( dic )
,m_pArmature( nullptr )
{
    
}

LivingUnit::~LivingUnit()
{
    
}

LivingUnit* LivingUnit::createByDirection( State sta, Direction dic )
{
    LivingUnit* unit = new LivingUnit( sta,dic );
    if( unit && unit -> init() )
    {
        unit -> autorelease();
        return unit;
    }
    else
    {
        CC_SAFE_DELETE( unit );
        return nullptr;
    }
    
}

bool LivingUnit::init()
{
    bool bRet = Unit::init();
    
    playWalk();
    
    return bRet;
}

Direction LivingUnit::JudgeDirection(Point startPos, Point EndPos)
{
    //斜边向量
    Vec2 HyVec = EndPos - startPos;
    //横边向量
    Vec2 RowVec( 1, 0 );
    //求弧度
    float radians = Vec2::angle(HyVec, RowVec);
    int angle = (int)CC_RADIANS_TO_DEGREES( radians );
    
    //角度归一 (鼠标向上 或 向下 角度 归一到 顺时针360读)
    if( HyVec.y < 0 )
    {
        angle = 360 - angle;
    }
    
    //角度归一到逆时针（debug 下次动作按逆时针）
    angle = 360 - angle;
    
    //计算 余数判断 属于那个方向 区间
    int mod = angle % 45;
    int DiractionIndex = angle / 45;
    
    if( mod > DIR_REGION_REF )
    {
        DiractionIndex += 1;
    }
    
    //动作从1开始（debug 下次从0开始）
    DiractionIndex += 1;
    
    //超过 360度范围
    if( DiractionIndex > (int)Direction::Unit_Direction_COUNT )
    {
        DiractionIndex = (int)Direction::Unit_Direction_RIGHT;
    }
    
    Direction dir = (Direction)DiractionIndex;

    log("LivingUnit Move: startPos(%f,%f) -> EndPos(%f,%f) angle = %d\n Direction = %d",
        startPos.x,startPos.y,EndPos.x,EndPos.y,angle,DiractionIndex);
    
    return dir;
}

void LivingUnit::move()
{
    Direction dir = JudgeDirection( getPosition(),m_pNextPos );
    setDirection( dir );
 
    stopAllActions();
    
    MoveTo* MoveAction = MoveTo::create(2, m_pNextPos);
    runAction( MoveAction );
    
    
    playWalk();
    
    setState( State::Unit_State_Walk );
}

void LivingUnit::moveStop()
{
    playStand();
    
    setState( State::Unit_State_Stand );
}

void LivingUnit::playStand()
{
    
}

void LivingUnit::playWalk()
{
    //加载ccs动画文件
    if( nullptr == m_pArmature )
    {
        m_pArmature = Armature::create("p1wTest");
        m_pArmature->setScale( 2 );
        addChild(m_pArmature);
    }
    //播放第一个动画
    //armature->getAnimation()->playWithIndex(0);
    
    char animch[32];
    sprintf( animch,"walk%d", m_dDirection );
    m_pArmature->getAnimation()->play( animch );
    
}