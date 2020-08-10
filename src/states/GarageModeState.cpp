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

#include "GarageModeState.h"

bool GarageModeState::mIsObjectRegistered = GarageModeState::RegisterObject();

bool GarageModeState::Activate()
{
    MSG_INFO("Entered in GarageMode State!");
    if(!stateReference::GetInstance().notifyStateListeners("GarageModeState"))
    {
        MSG_DEBUG("Error Notifying GarageModeState Subscribers");
    }

    stateReference::GetInstance().processEvent("garage");

    return true;
}

bool GarageModeState::Deactivate()
{
    MSG_INFO("Exiting GarageMode State");
    return true;
}
