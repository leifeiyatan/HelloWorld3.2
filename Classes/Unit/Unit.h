//
//  Unit.h
//  HelloWorld3.2
//
//  Created by 马良 on 14-7-17.
//
//

#ifndef __HelloWorld3_2__Unit__
#define __HelloWorld3_2__Unit__

#include "cocos2d.h"
using namespace cocos2d;

enum _UnitType
{
    UnitType_None = -1,
    UnitType_Player,
    UnitType_NPC,
    unitType_count,
};

class Unit : public Node
{
public:
    Unit();
    virtual ~Unit();
    
    CC_SYNTHESIZE(int, m_iUnitType, UnitType);
};

#endif /* defined(__HelloWorld3_2__Unit__) */
