//
//  UnitMgr.h
//  football
//
//  Created by 马良 on 14-4-15.
//
//

#ifndef __football__UnitMgr__
#define __football__UnitMgr__

#include "cocos2d.h"
#include "Unit.h"
using namespace cocos2d;

typedef int ID_key;

class UnitMgr
{
public:
    ~UnitMgr(){};
    
    bool init();
    Map<int, Unit*> m_pUnitArr[ unitType_count ];
    void initUnits();
    void clearUnitsAll();
    void clearUnitsByType( _UnitType type );
    
    void addUnit( Unit* pUnit );
    void removeUnit( Unit* pUnit );
    
    
    Map<ID_key, Unit*>* getUnitsByType( _UnitType type );
    Unit* getUnitByTypeAndID( _UnitType type, int ID );
    static UnitMgr* getUnitMgr();
    static void purgeUnitMgr();
private:
    UnitMgr();
};

#endif /* defined(__football__UnitMgr__) */
