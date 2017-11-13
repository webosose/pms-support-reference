// @@@LICENSE
//
//      Copyright (c) 2017-2018 LG Electronics, Inc.
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
    MSG_INFO("Entered in PowerOff State!");
    if(!stateReference::GetInstance().notifyStateListeners("PowerOffState"))
    {
        MSG_DEBUG("Error Notifying PowerOffState Subscribers");
    }

    // TODO: Decide later, if any specific reasons to pass to nyx for reference
    NyxUtil::getInstance().shutdown("shutdown");
    return true;
}

bool PowerOffState::Deactivate()
{
    MSG_INFO("Exiting PowerOff State");
    return true;
}
