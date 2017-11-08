// @@@LICENSE
//
//      Copyright (c) 2017 LG Electronics, Inc.
//
// Confidential computer software. Valid license from LG required for
// possession, use or copying. Consistent with FAR 12.211 and 12.212,
// Commercial Computer Software, Computer Software Documentation, and
// Technical Data for Commercial Items are licensed to the U.S. Government
// under vendor's standard commercial license.
//
// LICENSE@@@

#include "pmscore/NyxUtil.h"
#include "PowerOffState.h"

bool PowerOffState::mIsObjectRegistered = PowerOffState::RegisterObject();

bool PowerOffState::Activate()
{
    if(!stateReference::GetInstance().notifyStateListeners("PowerOffState"))
    {
        MSG_DEBUG("Error entering PowerOff State!");
        return false;
    }
    else
    {
        MSG_DEBUG("Entered in PowerOff State!");
    }
    NyxUtil::getInstance().shutdown("Check");
    return true;
}

bool PowerOffState::Deactivate()
{
    MSG_INFO("Exiting PowerOff State");
    return true;
}
