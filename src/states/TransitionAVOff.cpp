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

#include "TransitionAVOff.h"

bool TransitionAVOff::mIsObjectRegistered = TransitionAVOff::RegisterObject();

bool TransitionAVOff::Activate()
{
    MSG_INFO("Entered in Transition AV Off State!");

    if(!stateReference::GetInstance().notifyTransitionStateListeners("AVOffState"))
    {
        MSG_DEBUG("Error Notifying Transition AV Off State Subscribers");
    }

    return true;
}

bool TransitionAVOff::Deactivate()
{
    MSG_INFO("Exiting Transition AV Off State");
    return true;
}
