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


#ifndef AVOFF_STATE_H
#define AVOFF_STATE_H

#include <string>

#include "FSM.h"
#include "pmscore/log.h"
#include "pmscore/StateManager.h"

class AVOffState : public FSM::CFSMState {
public:
    bool Activate();
    bool Deactivate();
    static FSM::CFSMObject * CreateObject()
    {
        return new AVOffState;
    }

    static bool RegisterObject()
    {
        MSG_DEBUG2(LOG_CONTEXT_DEBUG, "Registering statemachine_AVOffState");
        StateManager::getFSMInstance()->Register("AVOffState", AVOffState::CreateObject);
        return true;
    }

    ~AVOffState()
    {
        delete mpLog;
        mpLog = nullptr;
    }

private:
    AVOffState() : mpLog(new Logger(LOG_CONTEXT_DEBUG))
    {
    }
    static bool mIsObjectRegistered;
    const Logger* mpLog;
};
#endif //AVOFF_STATE_H
