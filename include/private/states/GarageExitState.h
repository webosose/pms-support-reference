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


#ifndef GARAGEEXIT_STATE_H
#define GARAGEEXIT_STATE_H

#include <string>

#include "FSM.h"
#include "pmscore/log.h"
#include "pmscore/StateManager.h"

class GarageExitState : public FSM::CFSMState {
public:
    bool Activate();
    bool Deactivate();
    static FSM::CFSMObject * CreateObject()
    {
        return new GarageExitState;
    }

    static bool RegisterObject()
    {
        MSG_DEBUG2(LOG_CONTEXT_DEBUG, "Registering statemachine_GarageExitState");
        StateManager::getFSMInstance()->Register("GarageExitState", GarageExitState::CreateObject);
        return true;
    }

    ~GarageExitState()
    {
        delete mpLog;
        mpLog = nullptr;
    }

private:
    GarageExitState() : mpLog(new Logger(LOG_CONTEXT_DEBUG))
    {
    }

    static bool mIsObjectRegistered;
    const Logger* mpLog;
};

#endif //GARAGEEXIT_STATE_H
