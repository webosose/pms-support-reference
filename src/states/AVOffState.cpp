// @@@LICENSE
//
//      Copyright (c) 2020 LG Electronics, Inc.
//
// Confidential computer software. Valid license from LG required for
// possession, use or copying. Consistent with FAR 12.211 and 12.212,
// Commercial Computer Software, Computer Software Documentation, and
// Technical Data for Commercial Items are licensed to the U.S. Government
// under vendor's standard commercial license.
//
// LICENSE@@@

#include "AVOffState.h"

bool AVOffState::mIsObjectRegistered = AVOffState::RegisterObject();

bool AVOffState::Activate()
{
    MSG_INFO("Entered in AVOff State!");
    if(!stateReference::GetInstance().notifyStateListeners("AVOffState"))
    {
        MSG_DEBUG("Error Notifying AVOffState Subscribers");
    }

    return true;
}

bool AVOffState::Deactivate()
{
    MSG_INFO("Exiting AVOff State");
    return true;
}
