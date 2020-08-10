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

#include "GarageExitState.h"

bool GarageExitState::mIsObjectRegistered = GarageExitState::RegisterObject();

bool GarageExitState::Activate()
{
    MSG_INFO("Entered in GarageExit State!");
    if(!stateReference::GetInstance().notifyStateListeners("GarageExitState"))
    {
        MSG_DEBUG("Error Notifying GarageExitState Subscribers");
    }

    return true;
}

bool GarageExitState::Deactivate()
{
    MSG_INFO("Exiting GarageExit State");
    return true;
}
