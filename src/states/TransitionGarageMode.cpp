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

#include "TransitionGarageMode.h"
#include <pbnjson.hpp>

bool TransitionGarageMode::mIsObjectRegistered = TransitionGarageMode::RegisterObject();

bool TransitionGarageMode::Activate()
{
    MSG_INFO("Entered in Transition GarageMode State!");

    if(!stateReference::GetInstance().notifyTransitionStateListeners("GarageModeState"))
    {
        MSG_DEBUG("Error Notifying Transition GarageMode State Subscribers");
    }

    return true;
}

bool TransitionGarageMode::Deactivate()
{
    MSG_INFO("Exiting Transition GarageMode State");
    return true;
}