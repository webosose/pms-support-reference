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

#include "TransitionGarageExit.h"

bool TransitionGarageExit::mIsObjectRegistered = TransitionGarageExit::RegisterObject();

bool TransitionGarageExit::Activate()
{
    MSG_INFO("Entered in Transition GarageExit State!");

    if(!stateReference::GetInstance().notifyTransitionStateListeners("GarageExitState"))
    {
        MSG_DEBUG("Error Notifying Transition GarageExit State Subscribers");
    }

    return true;
}

bool TransitionGarageExit::Deactivate()
{
    MSG_INFO("Exiting Transition GarageExit State");
    return true;
}