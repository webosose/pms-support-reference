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

#ifndef LUNA_PMS_SUPPORT_H
#define LUNA_PMS_SUPPORT_H

#include <unordered_set>
#include <glib.h>

#include "pmscore/log.h"
#include "pmscore/LunaInterfaceBase.h"
#include "pmscore/PmsLuna2Utils.h"
#include "pmscore/StateEventListners.h"
#include "pmscore/StateManager.h"
#include "pmscore/timersource.h"

class LunaPmsSupport : public LunaInterfaceBase, public StateEventListners
{
public:

    /**
     * The object name string. This is initialized in .cpp file
     */
    static const char* const kPmsInterfaceName;
    static const char* const kPmsLogContext;
    static const char* const kPmsTimeOut;
    static const char* const kPmsGarageModeTimeOut;
    static const char* const kPmsGarageSSID;

    /*
     * Object Creator of Luna Service Handler
     */
    static LunaPmsSupport* CreateObject(PmsConfig* pConfig, LSHandle* pLsHandle)
    {
        return new LunaPmsSupport(pConfig, pLsHandle);
    }

    virtual ~LunaPmsSupport( )
    {
        UnregisterIpc();
    }

    GTimerSource *sTimerCheck = nullptr;

    PmsErrorCode_t Start();
    PmsErrorCode_t Stop();
    //To Handle Fixed State and Transition State
    bool handleStateChange(const std::string& statename);
    bool handleTransitionState(const std::string& processing);

    bool setAlarm(int timeout, int timeoutreason=0);
    bool clearAlarm();
    static gboolean timerFired(gpointer);

    static bool networkConnMgrStatusHandler(LSHandle *sh, LSMessage *message, void *categoryContext);
    bool networkConnMgrStatusHandlerCb(LSHandle *sh, LSMessage *message, void *categoryContext);

private:
    typedef enum {
        REASON_DEFAULT,
        REASON_TRANSITION_TIMEOUT,
        REASON_GARAGEMODE_TIMEOUT,
        REASON_GARAGEEXIT_TIMEOUT,
        REASON_INVALID
    }TIMEOUTREASON;
 
    /**
     * Constructor of LUNA State handler
     */
    LunaPmsSupport(PmsConfig* pConfig, LSHandle *pLsHandle);
    bool handleEvent(const std::string& event);
    int convertTimetoSec(std::string& in_time);

    GMainContext *mLoopContext = nullptr;

    /**
    * @brief Register the CreateObject() method of the LunaInterfaceCall class with the Interface
    * Object factory. This registration happens automatically when the Pms library is loaded
    */
    static bool RegisterObject()
    {
      return (sLunaInterfaceFactory::GetInstance().Register(LunaPmsSupport::kPmsInterfaceName, &LunaPmsSupport::CreateObject));
    }

    /**
     * Register with the client methods and also with the LUNA BUS for the LUNA commands
     */
    void RegisterIpc(LSHandle *pLsHandle);
    bool handleTransitionGarageState();

    PmsConfig* mpConfig;
    Logger* mpLog;

    /**
     * @var Used to Check if the registration operation to the object factory has
     * succeeded. This variable is assigned to the method Register()
     */
    static bool mIsObjRegistered;
    static bool mIsTransitionState;
    static std::string pendEvent;

    static const char* mpLogContext;
    static int mpLogTimeOutSec;
    static int miGarageModeTimeoutSec;
    static std::string msGarageSSID;
};

#endif //LUNA_PMS_SUPPORT_H
