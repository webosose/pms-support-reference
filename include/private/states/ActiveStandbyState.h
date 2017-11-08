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

#ifndef ACTIVE_STANDBY_STATE_H
#define ACTIVE_STANDBY_STATE_H

#include <functional>
#include <luna-service2/lunaservice.hpp>

#include "FSM.h"
#include "pmscore/log.h"
#include "pmscore/Singleton.h"
#include "pmscore/StateManager.h"

class ActiveStandbyState : public FSM::CFSMState {
public:
    bool Activate();
    bool Deactivate();

    static FSM::CFSMObject* CreateObject()
    {
        return new ActiveStandbyState;
    }

    static bool RegisterObject()
    {
       MSG_DEBUG2(LOG_CONTEXT_DEBUG, "Registering statemachine_ActiveStandby");
       StateManager::getFSMInstance()->Register("ActiveStandbyState", ActiveStandbyState::CreateObject);
       return true;
    }

    ~ActiveStandbyState()
    {
        delete mpLog;
        mpLog = nullptr;
    }
private:
    ActiveStandbyState() : mpLog(new Logger(LOG_CONTEXT_DEBUG))
    {
    }
    static bool mIsObjectRegistered;
    const Logger* mpLog;
};

#endif
