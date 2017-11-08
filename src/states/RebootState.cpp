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
#include "RebootState.h"

bool RebootState::mIsObjectRegistered = RebootState::RegisterObject();

bool RebootState::Activate()
{
    if(!stateReference::GetInstance().notifyStateListeners("RebootState"))
    {
        MSG_DEBUG("Error entering Reboot State!");
        return false;
    }
    else
    {
        MSG_DEBUG("Entered in Reboot State!");
    }
    NyxUtil::getInstance().reboot("Check");
    return true;
}

bool RebootState::Deactivate()
{
    MSG_INFO("Exiting Reboot State");
    return true;
}
