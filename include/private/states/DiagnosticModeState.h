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


#ifndef DIAGNOSTIC_MODE_STATE_H
#define DIAGNOSTIC_MODE_STATE_H

#include <string>

#include "FSM.h"
#include "pmscore/log.h"
#include "pmscore/StateManager.h"

class DiagnosticModeState : public FSM::CFSMState {
public:
    bool Activate();
    bool Deactivate();
    static FSM::CFSMObject * CreateObject()
    {
        return new DiagnosticModeState;
    }

    static bool RegisterObject()
    {
        MSG_DEBUG2(LOG_CONTEXT_DEBUG, "Registering statemachine_DiagnosticModeState");
        StateManager::getFSMInstance()->Register("DiagnosticModeState", DiagnosticModeState::CreateObject);
        return true;
    }

    ~DiagnosticModeState()
    {
        delete mpLog;
        mpLog = nullptr;
    }

private:
    DiagnosticModeState() : mpLog(new Logger(LOG_CONTEXT_DEBUG))
    {
    }

    static bool mIsObjectRegistered;
    const Logger* mpLog;
};

#endif //DIAGNOSTIC_MODE_STATE_H
