//
//  LivingUnit.cpp
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-17.
//
//

#include "LivingUnit.h"

LivingUnit::LivingUnit( LivingData* data )
:m_sState( State::Unit_State_Stand )
,m_dDirection( Direction::Unit_Direction_DOWN )
,m_pArmature( nullptr )
,m_pTargetUnit( nullptr )
,m_pSrcUnit( nullptr )
,AttackCallBackFun( nullptr )
,m_pCurLivingData( data )
{

}

LivingUnit::~LivingUnit()
{
    
}

LivingUnit* LivingUnit::create( LivingData* data )
{
    LivingUnit* unit = new LivingUnit( data );
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
    
    stand();
    
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

    log("LivingUnit-ID %d Move: startPos(%f,%f) -> EndPos(%f,%f) angle = %d\n Direction = %d",
        m_pCurLivingData -> getLivingID(),startPos.x,startPos.y,EndPos.x,EndPos.y,angle,DiractionIndex);
    
    return dir;
}

void LivingUnit::stand()
{
    playStandAnim();
    setState( State::Unit_State_Stand );
    
    log( "LivingUnit-ID %d stand",m_pCurLivingData -> getLivingID() );
}

void LivingUnit::move()
{
    Direction dir = JudgeDirection( getPosition(),m_pNextPos );
    setDirection( dir );
 
    stopAllActions();
    float duration = m_pNextPos.distance( getPosition() ) / ( 22.36f * m_pCurLivingData -> getSpeed() );
    
    MoveTo* MoveAction = MoveTo::create( duration, m_pNextPos );
    CallFunc* moveCallback = CallFunc::create(CC_CALLBACK_0(LivingUnit::moveStop,this));
    
    Sequence* MoveSeq = Sequence::create(MoveAction, moveCallback, NULL);
    
    runAction( MoveSeq );
    
    playWalkAnim();
    
    setState( State::Unit_State_Walk );
    
    //log( "LivingUnit-ID %d moveing... LivingUnit Move duration = %d",m_pCurLivingData -> getLivingID(),(int)duration );
}

void LivingUnit::moveStop()
{
    stand();
    
    //log( "LivingUnit-ID %d move stop",m_pCurLivingData -> getLivingID() );
}

void LivingUnit::attack( LivingUnit* Targetunit  )
{
    Direction dir = JudgeDirection( getPosition(),m_pNextPos );
    setDirection( dir );
    
    setTargetUnit( Targetunit );
    
    playAttackAnim();
    
    setState( State::Unit_State_Attack );
    
    //log( "LivingUnit-ID %d attack!",m_pCurLivingData -> getLivingID() );
}

void LivingUnit::hurt( int DamageValue /*LivingUnit* Srcunit*/ )
{
    Direction dir = JudgeDirection( getPosition(),m_pNextPos );
    setDirection( dir );
    
    //setSrcUnit( Srcunit );
    m_pCurLivingData -> setCurHP( m_pCurLivingData -> getCurHP() - DamageValue );
    
    playHurtAnim();
    
    setState( State::Unit_State_hurt );
    
    //log( "LivingUnit-ID %d hurt Damage Valua = %d",m_pCurLivingData -> getLivingID(),DamageValue );
}

void LivingUnit::playStandAnim()
{
    //log( "play LivingUnit-ID %d AnimName ---- %s",m_pCurLivingData -> getLivingID(),"stand" );
}

void LivingUnit::playWalkAnim()
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
    
    std::string MovementID =  m_pArmature -> getAnimation() -> getCurrentMovementID();
    
    if( strcmp(MovementID.c_str(), animch) != 0 )
    {
        m_pArmature->getAnimation()->play( animch );
        //log( "play LivingUnit-ID %d AnimName ---- %s",m_pCurLivingData -> getLivingID(), animch );
    }
    
}
void LivingUnit::playAttackAnim()
{
    //加载ccs动画文件
    if( nullptr == m_pArmature )
    {
        m_pArmature = Armature::create("p1wTest");
        m_pArmature->setScale( 2 );
        addChild(m_pArmature);
    }
    
    m_pArmature->getAnimation()->setMovementEventCallFunc(std::bind(&LivingUnit::AnimCallBack,this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    //Armature *armature, MovementEventType movementType, const std::string& movementID
    m_pArmature->getAnimation()->setFrameEventCallFunc(std::bind(&LivingUnit::AttackFrameEvent,this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    
    //播放第一个动画
    //armature->getAnimation()->playWithIndex(0);
    
    char animch[32];
    sprintf( animch,"walk%d", m_dDirection );
    
    std::string MovementID =  m_pArmature -> getAnimation() -> getCurrentMovementID();
    
    if( strcmp(MovementID.c_str(), animch) != 0 )
    {
        m_pArmature->getAnimation()->play( animch,-1,0 );
        //log( "play LivingUnit-ID %d AnimName ---- %s",m_pCurLivingData -> getLivingID(),animch );
    }
    
}

void LivingUnit::playHurtAnim()
{
    //加载ccs动画文件
    if( nullptr == m_pArmature )
    {
        m_pArmature = Armature::create("p1wTest");
        m_pArmature->setScale( 2 );
        addChild(m_pArmature);
    }
    
    m_pArmature->getAnimation()->setMovementEventCallFunc(std::bind(&LivingUnit::AnimCallBack,this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    
    //播放第一个动画
    //armature->getAnimation()->playWithIndex(0);
    
    char animch[32];
    sprintf( animch,"walk%d", m_dDirection );
    
    std::string MovementID =  m_pArmature -> getAnimation() -> getCurrentMovementID();
    
    if( strcmp(MovementID.c_str(), animch) != 0 )
    {
        m_pArmature->getAnimation()->play( animch,-1,0 );
        //log( "play LivingUnit-ID %d AnimName ---- %s",m_pCurLivingData -> getLivingID(),"Hert" );
    }
}

void LivingUnit::AttackFrameEvent( Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex )
{
    CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), frameEventName.c_str(), currentFrameIndex);
    
    AttackCallBackFun( this,getTargetUnit() );
    //m_pTargetUnit -> hurt( this );
}


void LivingUnit::AnimCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if( movementType != LOOP_COMPLETE )
    {
        CCLOG("AnimName = %s, EventType = %d", movementID.c_str(), (int)movementType);
    }
    if( movementType == COMPLETE )
    {
        stand();
    }
}

