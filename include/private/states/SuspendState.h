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

#ifndef SUSPEND_STATE_H
#define SUSPEND_STATE_H

#include "FSM.h"
#include "pmscore/log.h"
#include "pmscore/StateManager.h"

class SuspendState : public FSM::CFSMState {
public:
    bool Activate();
    bool Deactivate();
    static FSM::CFSMObject * CreateObject()
    {
       return new SuspendState;
    }

    static bool RegisterObject()
    {
        MSG_DEBUG2(LOG_CONTEXT_DEBUG, "Registering statemachine_Suspend");
        StateManager::getFSMInstance()->Register("SuspendState", SuspendState::CreateObject);
        return true;
    }

    ~SuspendState()
    {
        delete mpLog;
        mpLog = nullptr;
    }

private:
    SuspendState() : mpLog(new Logger(LOG_CONTEXT_DEBUG))
    {
    }
    static bool mIsObjectRegistered;
    const Logger* mpLog;
};
#endif
