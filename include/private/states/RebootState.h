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

#ifndef REBOOT_STATE_H
#define REBOOT_STATE_H

#include <string>

#include "FSM.h"
#include "pmscore/log.h"
#include "pmscore/StateManager.h"

class RebootState : public FSM::CFSMState {
public:
    bool Activate();
    bool Deactivate();

    static FSM::CFSMObject * CreateObject()
    {
        return new RebootState;
    }

    static bool RegisterObject()
    {
        StateManager::getFSMInstance()->Register("RebootState", RebootState::CreateObject);
        return true;
    }

    ~RebootState()
    {
        delete mpLog;
        mpLog = nullptr;
    }

private:
    RebootState() : mpLog(new Logger(LOG_CONTEXT_DEBUG))
    {
    }
    static bool mIsObjectRegistered;
    const Logger* mpLog;
};
#endif
