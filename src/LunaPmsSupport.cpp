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

#include <errno.h>
#include <fstream>
#include <sys/inotify.h>
#include <sys/time.h>
#include <signal.h>
#include <string>

#include "LunaPmsSupport.h"
#include "pmscore/LunaInterfaceCommon.h"
#include "pmscore/NyxUtil.h"

const char* const LunaPmsSupport::kPmsInterfaceName = "LunaInterfacePMSSupport";
const char* const LunaPmsSupport::kPmsLogContext = "LogContext";
const char* const LunaPmsSupport::kPmsTimeOut = "TimeOut";
const char* const LunaPmsSupport::kPmsGarageModeTimeOut = "GarageModeTimeOut";
const char* const LunaPmsSupport::kPmsGarageSSID = "GarageSSID";

const char* LunaPmsSupport::mpLogContext = "";

bool LunaPmsSupport::mIsTransitionState = false;
int LunaPmsSupport::mpLogTimeOutSec = 0;
int LunaPmsSupport::miGarageModeTimeoutSec = 0;
std::string LunaPmsSupport::pendEvent = "";
std::string LunaPmsSupport::msGarageSSID = "";

#define CALLBACK_BIND(function) (std::bind1st(std::mem_fun(function), this))
#define TIMER_CHECK_TIMEOUT      3
#define NOTIFY_WITH_ALARM        0
#define kPmsMsgCategorySupport  (kPmsMsgCategoryOffset * 2)

/**
 * Register with the factory object
 */
bool LunaPmsSupport::mIsObjRegistered = LunaPmsSupport::RegisterObject();

enum PowerManagerServiceConsts {
    MAX_TIME_FORMAT_SIZE = 9,
    MAX_PARAMS_SIZE = 100
};

LunaPmsSupport::LunaPmsSupport(PmsConfig* pConfig, LSHandle *pLsHandle) :
    LunaInterfaceBase(pConfig, pLsHandle)
{
    std::string logContext, timeContext;

    mpConfig = pConfig;

    PmsErrorCode_t err = kPmsSuccess;
    const char* logCtxt = LOG_CONTEXT_DEBUG; //default logging context

    err = mpConfig->GetString(kPmsInterfaceName,
    kPmsLogContext, &logContext);

    if(err == kPmsSuccess)
    logCtxt = logContext.c_str();

    mpLogContext = logCtxt;

    mpConfig->GetString(kPmsInterfaceName,
    kPmsTimeOut, &timeContext);
    mpLogTimeOutSec = convertTimetoSec(timeContext);
    timeContext.clear();

    mpConfig->GetString(kPmsInterfaceName,
    kPmsGarageModeTimeOut, &timeContext);
    miGarageModeTimeoutSec = convertTimetoSec(timeContext);

    mpConfig->GetString(kPmsInterfaceName,
    kPmsGarageSSID, &msGarageSSID);

    mpLog = new Logger(logCtxt);

    // register the IPC methods and notification callbacks with Client
    RegisterIpc(pLsHandle);
}

void LunaPmsSupport::RegisterIpc(LSHandle *pLsHandle)
{
    PMSLunaCategoryContext *pCxt = PMSLunaCategoryContext::Instance();
    pCxt->AddLunaCategoryContext(kPmsMsgCategorySupport, this);
}

PmsErrorCode_t LunaPmsSupport::Start()
{
    MSG_DEBUG("[%s]", __PRETTY_FUNCTION__);
    LSError lserror;
    LSErrorInit(&lserror);
    mLoopContext = LSGmainGetContext(mpLsHandle, &lserror);
    if(!mLoopContext)
    {
        LSErrorPrint(&lserror, stderr);
        LSErrorFree(&lserror);
        return kPmsErrUnknown;
    }

    stateReference::GetInstance().registerListener(this);

    return IpcInterfaceBase::Start();
}

PmsErrorCode_t LunaPmsSupport::Stop()
{
    MSG_DEBUG("[%s]", __PRETTY_FUNCTION__);
    stateReference::GetInstance().unregisterListener(this);

    return IpcInterfaceBase::Stop();
}

inline
int LunaPmsSupport::convertTimetoSec(std::string& in_time)
{
    std::string HH (in_time.begin(),   in_time.begin()+2);
    std::string MM (in_time.begin()+3, in_time.begin()+5);
    std::string SS (in_time.begin()+6, in_time.begin()+8);

    int res = (atoi(HH.c_str()) * 60 * 60) + (atoi(MM.c_str()) * 60) + atoi(SS.c_str());
    return res;
}

gboolean LunaPmsSupport::timerFired(gpointer data)
{
    int reason = GPOINTER_TO_INT(data);
    switch(reason) {
        case REASON_TRANSITION_TIMEOUT:
            stateReference::GetInstance().processEvent("ACK");
            break;
        case REASON_GARAGEMODE_TIMEOUT:
            stateReference::GetInstance().processEvent("garagetimeout");
            break;
        case REASON_GARAGEEXIT_TIMEOUT:
            stateReference::GetInstance().processEvent("poweroff");
            break;
        default:
            stateReference::GetInstance().processEvent(pendEvent);
    }
    return G_SOURCE_REMOVE;
}

bool LunaPmsSupport::setAlarm(int timeout,int timeoutreason)
{
    /*gtimer for timeout alarms*/
    sTimerCheck = g_timer_source_new_seconds(timeout);
    g_source_set_callback((GSource *)sTimerCheck,(GSourceFunc)timerFired, GINT_TO_POINTER(timeoutreason), NULL);
    g_source_attach((GSource *)sTimerCheck, mLoopContext);
    g_source_unref((GSource*)sTimerCheck);  //TODO: revisit this line

    return true;
}

bool LunaPmsSupport::clearAlarm()
{
    if(sTimerCheck && !g_source_is_destroyed((GSource*)sTimerCheck))
    {
        g_source_destroy ((GSource*)sTimerCheck);
        sTimerCheck = NULL;
        return true;
    }
    return false;
}


bool LunaPmsSupport::handleTransitionState(const std::string& nextState)
{
    MSG_DEBUG("Transition State Notification Reached Successfully!!");
    mIsTransitionState = true;

    if(nextState == "GarageModeState")
    {
        handleTransitionGarageState();
    }

    return true;
}

bool LunaPmsSupport::handleStateChange(const std::string& statename)
{
    MSG_DEBUG("State Change Notification Reached LunaPmsSupport Successfully!! State: %s", statename.c_str());
    mIsTransitionState = false;
    clearAlarm();

    if(statename == "StandbyState")
    {
        //check swupdatedone flag file
        FILE *flagFile = fopen("/var/swupdatedone", "rb");
        std::string event  = "poweron";
        if(flagFile)
        {
            event = "swupdate";
            //Todo: Do we need to publish power on reason for subcribers after power on
        }
        pendEvent = event;
        setAlarm(0);
    }
    else if(statename == "AVOffState")
    {
        pendEvent = "garage";
        setAlarm(0);
    }
    else if(statename == "GarageModeState")
    {
        setAlarm(miGarageModeTimeoutSec, REASON_GARAGEMODE_TIMEOUT);  //No need to clear alarm
    }
    else if(statename == "GarageExitState")
    {
        setAlarm(mpLogTimeOutSec, REASON_GARAGEEXIT_TIMEOUT);
        //TODO: Is time for garage Exit is also 3sec ?
        //TODO: clearAlarm if reboot(ota) event came befoere timeout, Maybe not require. anyhow system rebooted.
    }

    return true;
}

bool LunaPmsSupport::handleEvent(const std::string& event)
{
    if(!mIsTransitionState)
    {
        return stateReference::GetInstance().processEvent(event);
    }
    return false;
}

bool LunaPmsSupport::networkConnMgrStatusHandler(LSHandle *sh, LSMessage *message, void *categoryContext)
{
    PMSLunaCategoryContext *pCxt = PMSLunaCategoryContext::Instance();
    LunaPmsSupport *pThis = (LunaPmsSupport *)(pCxt->GetLunaCategoryContext(kPmsMsgCategorySupport));

    return pThis->networkConnMgrStatusHandlerCb(sh, message, categoryContext);
}

bool LunaPmsSupport::networkConnMgrStatusHandlerCb(LSHandle *sh, LSMessage *message, void *categoryContext)
{
    if (mIsTransitionState && sh != NULL && message != NULL)
    {
        LS::Message request(message);
        pbnjson::JValue responseObj;

        if (!LSUtils::parsePayload(request.getPayload(), responseObj)) {
            MSG_DEBUG("Parsing failed!!");
            return false;
        }

        clearAlarm();

        bool retValue = responseObj["returnValue"].asBool();
        pbnjson::JValue wifiObj = responseObj["wifi"];
        if(msGarageSSID.empty() || (retValue && wifiObj.isObject() && (wifiObj["state"].asString() == "connected") && (wifiObj["ssid"].asString() == msGarageSSID)))
        {
            stateReference::GetInstance().processEvent("ACK");
        }
        else
        {
            stateReference::GetInstance().processEvent("NACK");
        }
    }
    return true;
}

bool LunaPmsSupport::handleTransitionGarageState()
{
    LSError lserror;
    LSErrorInit(&lserror);
    LSMessageToken token = LSMESSAGE_TOKEN_INVALID;
    bool bResult = LSCallOneReply(mpLsHandle,
                                  "luna://com.webos.service.connectionmanager/getStatus",
                                  "{}",
                                  LunaPmsSupport::networkConnMgrStatusHandler,
                                  NULL,
                                  &token,
                                  &lserror );
    if (!bResult)
    {
        MSG_DEBUG("LSCallOneReply --> connectionmanager failed.");
        LSErrorPrint(&lserror, stderr);
        LSErrorFree(&lserror);
        return false;
    }

    //TODO: LSCallOneReply --> vehicle service for BatteryStatus

    setAlarm(mpLogTimeOutSec, REASON_TRANSITION_TIMEOUT);

    return true;
}
