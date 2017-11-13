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

#include "TransitionPowerOff.h"

bool TransitionPowerOff::mIsObjectRegistered = TransitionPowerOff::RegisterObject();

bool TransitionPowerOff::Activate()
{
    MSG_INFO("Entered in Transition PowerOff State!");

    if(!stateReference::GetInstance().notifyTransitionStateListeners("PowerOffState"))
    {
        MSG_DEBUG("Error Notifying Transition Power Off State Subscribers");
    }

    return true;
}

bool TransitionPowerOff::Deactivate()
{
    MSG_INFO("Exiting Transition PowerOff State");
    return true;
}
