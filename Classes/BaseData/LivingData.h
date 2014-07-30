//
//  LivingDate.h
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-28.
//
//

#ifndef __HelloWorld3_2__LivingDate__
#define __HelloWorld3_2__LivingDate__

#include "cocos2d.h"
using namespace cocos2d;

class LivingData
{
public:
    LivingData();
    virtual ~LivingData();
    
    CC_SYNTHESIZE(int, m_iLivingID, LivingID);
    CC_SYNTHESIZE(int, m_iLivingType, LivingType);
    CC_SYNTHESIZE(__String, m_strName, Name);
    CC_SYNTHESIZE(int, m_iSpeed, Speed);
    CC_SYNTHESIZE(int, m_iCurHP, CurHP);
    CC_SYNTHESIZE(int, m_iTotalHP, TotalHP);
    CC_SYNTHESIZE(int, m_iAttackValue, AttackValue);
    
};

#endif /* defined(__HelloWorld3_2__LivingDate__) */
