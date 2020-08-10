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

#include "DiagnosticModeState.h"

bool DiagnosticModeState::mIsObjectRegistered = DiagnosticModeState::RegisterObject();

bool DiagnosticModeState::Activate()
{
    MSG_INFO("Entered in DiagnosticMode State!");
    if(!stateReference::GetInstance().notifyStateListeners("DiagnosticModeState"))
    {
        MSG_DEBUG("Error Notifying DiagnosticModeState Subscribers");
    }

    return true;
}

bool DiagnosticModeState::Deactivate()
{
    MSG_INFO("Exiting DiagnosticMode State");
    return true;
}
