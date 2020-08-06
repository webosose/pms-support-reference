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

#include "RebootState.h"
#include "pmscore/NyxUtil.h"

bool RebootState::mIsObjectRegistered = RebootState::RegisterObject();

bool RebootState::Activate()
{
    MSG_INFO("Entered in Reboot State!");

    if(!stateReference::GetInstance().notifyStateListeners("RebootState"))
    {
        MSG_DEBUG("Error Notifying RebootState Subscribers");
    }

    system("reboot");

    return true;
}

bool RebootState::Deactivate()
{
    MSG_INFO("Exiting Reboot State");
    return true;
}
