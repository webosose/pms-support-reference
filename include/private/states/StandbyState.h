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

#ifndef STANDBY_STATE_H
#define STANDBY_STATE_H

#include <functional>

#include "FSM.h"
#include "pmscore/log.h"
#include "pmscore/StateManager.h"

class StandbyState : public FSM::CFSMState {
public:
    bool Activate();
    bool Deactivate();

    static FSM::CFSMObject* CreateObject()
    {
        return new StandbyState;
    }

    static bool RegisterObject()
    {
       MSG_DEBUG2(LOG_CONTEXT_DEBUG, "Registering statemachine_StandbyState");
       StateManager::getFSMInstance()->Register("StandbyState", StandbyState::CreateObject);
       return true;
    }

    ~StandbyState()
    {
        delete mpLog;
        mpLog = nullptr;
    }
private:
    StandbyState() : mpLog(new Logger(LOG_CONTEXT_DEBUG))
    {
    }

    static bool mIsObjectRegistered;
    const Logger* mpLog;
};

#endif //STANDBY_STATE_H
