//
//  LivingUnit.h
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-17.
//
//

#ifndef __HelloWorld3_2__LivingUnit__
#define __HelloWorld3_2__LivingUnit__

#include "Unit.h"

#include "CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;

#include"LivingData.h"

enum class State
{
    Unit_State_None,
    Unit_State_Stand,  //站立
    Unit_State_Walk,   //走路
    Unit_State_Runing, //跑步
    Unit_State_Attack, //攻击
    Unit_State_hurt, //受伤
    //UNIT_STATE_AI      //自动
};

enum class Direction
{
    Unit_Direction_RIGHT = 1,
    Unit_Direction_RIGHTDOWN = 2,
    Unit_Direction_DOWN = 3,
    Unit_Direction_LEFTDOWN = 4,
    Unit_Direction_LEFT = 5,
    Unit_Direction_LEFTUP = 6,
    Unit_Direction_UP = 7,
    Unit_Direction_RIGHTUP = 8,
    Unit_Direction_COUNT = 8
};

#define DIR_REGION_REF 30 //角度方向 区间 参考值

class LivingUnit : public Unit
{
public:
    LivingUnit( LivingData* data );
    virtual ~LivingUnit();
    
    virtual bool init();
    
    void initActionSeq();
    
    void stand();
    void move();
    void moveStop();
    void attack( LivingUnit* Targetunit );
    void hurt( int DamageValue /*LivingUnit* Srcunit*/ );
    
    //动画
    virtual void playStandAnim();
    virtual void playWalkAnim();
    virtual void playAttackAnim();
    virtual void playHurtAnim();
    
    //结束事件
    virtual void AnimCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
    //攻击动画贞事件
    virtual void AttackFrameEvent( Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex );
    std::function<void(LivingUnit*,LivingUnit*)> AttackCallBackFun;
    
    //判断方向
    Direction JudgeDirection(Point startPos, Point EndPos);
   
    
    CC_SYNTHESIZE(State, m_sState, State);
    CC_SYNTHESIZE(Direction,m_dDirection,Direction);
    CC_SYNTHESIZE(Point, m_pNextPos,NextPos);
    CC_SYNTHESIZE(Armature*, m_pArmature, Armature);
    CC_SYNTHESIZE(LivingUnit*, m_pTargetUnit, TargetUnit);   //攻击
    CC_SYNTHESIZE(LivingUnit*, m_pSrcUnit, SrcUnit);         //被攻击
    CC_SYNTHESIZE(LivingData*, m_pCurLivingData, CurLivingData);
    static LivingUnit* create( LivingData* data );
};

#endif /* defined(__HelloWorld3_2__LivingUnit__) */
