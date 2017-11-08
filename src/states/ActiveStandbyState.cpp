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

#include "ActiveStandbyState.h"

bool ActiveStandbyState::mIsObjectRegistered = ActiveStandbyState::RegisterObject();

bool ActiveStandbyState::Activate()
{
    if(!stateReference::GetInstance().notifyStateListeners("ActiveStandbyState"))
    {
        MSG_DEBUG("Error entering Active StandBy State!");
        return false;
    }
    else
    {
        MSG_DEBUG("Entered in Active StandBy State!");
    }
    return true;
}

bool ActiveStandbyState::Deactivate() {
    MSG_INFO("Exiting Active StandBy State");
    return true;
}
