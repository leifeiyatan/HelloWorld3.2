//
//  UnitMgr.cpp
//  football
//
//  Created by 马良 on 14-4-15.
//
//

#include "UnitMgr.h"


static UnitMgr *s_SharedUnitMgr = NULL;

UnitMgr::UnitMgr()
{
    
}

UnitMgr* UnitMgr::getInterface()
{
    if (!s_SharedUnitMgr)
    {
        s_SharedUnitMgr = new UnitMgr();
        s_SharedUnitMgr->init();
    }
    
    return s_SharedUnitMgr;
}
void UnitMgr::purgeUnitMgr()
{
    s_SharedUnitMgr -> clearUnitsAll();
    CC_SAFE_DELETE( s_SharedUnitMgr );
}

bool UnitMgr::init()
{
    bool bRet = true;
    
    initUnits();
    
    return  bRet;
}

void UnitMgr::initUnits()
{
    int arrCount = sizeof(m_pUnitArr) / sizeof(m_pUnitArr[0]);
    for (int i = 0; i < arrCount; i++)
    {
        m_pUnitArr[i].clear();
    }
}

void UnitMgr::clearUnitsAll()
{
    int arrCount = sizeof(m_pUnitArr) / sizeof(m_pUnitArr[0]);
    for (int i = 0; i < arrCount; i++)
    {
        m_pUnitArr[i].clear();
    }
}

void UnitMgr::clearUnitsByType( _UnitType type )
{
    CCAssert( type > UnitType_None && type < unitType_count, "unittype error" );
    
    m_pUnitArr[type].clear();
}


void UnitMgr::addUnit( Unit* pUnit )
{
    CCAssert( nullptr != pUnit, "param 1 = NULL" );
    int UnitType = pUnit -> getUnitType();
    
    CCAssert( UnitType > UnitType_None && UnitType < unitType_count, "unittype error" );
    
    int ID_key = pUnit -> getTag();
    
    m_pUnitArr[UnitType].insert( ID_key,pUnit );
}

void UnitMgr::removeUnit( Unit* pUnit )
{
    CCAssert( nullptr != pUnit, "param 1 = NULL" );
    int UnitType = pUnit -> getUnitType();
    
    CCAssert( UnitType > UnitType_None && UnitType < unitType_count, "unittype error" );
    
    int ID_key = pUnit -> getTag();
    
    m_pUnitArr[UnitType].erase( ID_key );
}

Map<int, Unit*>* UnitMgr::getUnitsByType( _UnitType type )
{
    CCAssert( type > UnitType_None && type < unitType_count, "param 1 error" );

    return &m_pUnitArr[type];
}

Unit* UnitMgr::getUnitByTypeAndID( _UnitType type, int ID )
{
    Map<ID_key, Unit*>* Units = getUnitsByType( type );
    
    Unit* pUnit = nullptr;
    
    pUnit = static_cast<Unit*>( Units -> at( ID ) );
    
    return pUnit;
    
//    Map<int, Unit*>::iterator it = Units -> begin();
//    for( ; it != Units -> end(); ++it )
//    {
//        pUnit = static_cast<Unit*>( (it -> second) );
//        if (pUnit -> getTag() == UnitTag )
//        {
//            break;
//        }
//    }

}
