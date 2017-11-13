// @@@LICENSE
//
//      Copyright (c) 2018 LG Electronics, Inc.
//
// Confidential computer software. Valid license from LG required for
// possession, use or copying. Consistent with FAR 12.211 and 12.212,
// Commercial Computer Software, Computer Software Documentation, and
// Technical Data for Commercial Items are licensed to the U.S. Government
// under vendor's standard commercial license.
//
// LICENSE@@@

#include "TransitionReboot.h"

bool TransitionReboot::mIsObjectRegistered = TransitionReboot::RegisterObject();

bool TransitionReboot::Activate()
{
    MSG_INFO("Entered in Transition Reboot State!");

    if(!stateReference::GetInstance().notifyTransitionStateListeners("RebootState"))
    {
        MSG_DEBUG("Error Notifying Transition Reboot State Subscribers");
    }

    return true;
}

bool TransitionReboot::Deactivate()
{
    MSG_INFO("Exiting Transition Reboot State");
    return true;
}
