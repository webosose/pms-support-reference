// @@@LICENSE
//
//      Copyright (c) 2017-2020 LG Electronics, Inc.
//
// Confidential computer software. Valid license from LG required for
// possession, use or copying. Consistent with FAR 12.211 and 12.212,
// Commercial Computer Software, Computer Software Documentation, and
// Technical Data for Commercial Items are licensed to the U.S. Government
// under vendor's standard commercial license.
//
// LICENSE@@@

#include "StandbyState.h"
#include <pbnjson.hpp>

bool StandbyState::mIsObjectRegistered = StandbyState::RegisterObject();

bool StandbyState::Activate()
{
    MSG_INFO("Entered in Standby State!");

    if(!stateReference::GetInstance().notifyStateListeners("StandbyState"))
    {
        MSG_DEBUG("Error Notifying StandbyState Subscribers");
    }

    return true;
}

bool StandbyState::Deactivate() {
    MSG_INFO("Exiting StandBy State");
    return true;
}


