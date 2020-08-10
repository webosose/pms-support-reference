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

#ifndef TRANSITION_GARAGE_MODE_H
#define TRANSITION_GARAGE_MODE_H

#include <string>

#include "FSM.h"
#include "pmscore/log.h"
#include "pmscore/StateManager.h"

class TransitionGarageMode : public FSM::CFSMState {
public:
    bool Activate();
    bool Deactivate();

    static FSM::CFSMObject * CreateObject()
    {
        return new TransitionGarageMode;
    }

    static bool RegisterObject()
    {
        MSG_DEBUG2(LOG_CONTEXT_DEBUG, "Registering statemachine_TransitionGarageMode");
        StateManager::getFSMInstance()->Register("TransitionGarageMode", TransitionGarageMode::CreateObject);
        return true;
    }

    ~TransitionGarageMode()
    {
        delete mpLog;
        mpLog = nullptr;
    }

private:
    TransitionGarageMode() : mpLog(new Logger(LOG_CONTEXT_DEBUG))
    {
    }

    static bool mIsObjectRegistered;
    const Logger* mpLog;
};
#endif //TRANSITION_GARAGE_MODE_H
