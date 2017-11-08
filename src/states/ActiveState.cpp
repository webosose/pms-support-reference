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

#include "ActiveState.h"

bool ActiveState::mIsObjectRegistered = ActiveState::RegisterObject();

bool ActiveState::Activate()
{
    if(!stateReference::GetInstance().notifyStateListeners("ActiveState"))
    {
        MSG_DEBUG("Error entering Active State!");
        return false;
    }
    else
    {
        MSG_DEBUG("Entered in Active State!");
    }
    return true;
}

bool ActiveState::Deactivate()
{
    MSG_INFO("Exiting Active State");
    return true;
}
