//
//  MSDKCrashService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/06/24.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "GUACrashService.h"
#include "UnionAdapterDefine.h"
#include "MSDKStructUtility.h"
#include "MSDKCrash.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

class MSDKCrashObserver : public GCloud::MSDKSpace::NoSTL::MSDKCrashObserver
{
public:
    static MSDKCrashObserver Instance;
    GUACrashObserver *crahs_observer_;
public:
    MSDKCrashObserver() : crahs_observer_(nullptr) {
    }

    const char* OnCrashExtraMessageNotify()
    {
        if (MSDKCrashObserver::Instance.crahs_observer_ != nullptr) 
        {
            return MSDKCrashObserver::Instance.crahs_observer_->OnCrashExtraMessageNotify();
        }
        else
        {
            LOG_DEBUG("MSDKCrashObserver::Instance.crahs_observer_ is nullptr");
        }
        return GUA_DEFAULT_EMPTY_STRING;
    }

    long OnCrashExtraDataNotify(GCloud::MSDKSpace::NoSTL::MSDKCrashRet &msdk_crash_ret)
    {
        GUACrashRet gua_crash_ret;
        MSDKStructUtility::ConvertCrashRetToGUA(msdk_crash_ret, gua_crash_ret);

        long default_long = 0;
        if (MSDKCrashObserver::Instance.crahs_observer_ != nullptr) 
        {
            return MSDKCrashObserver::Instance.crahs_observer_->OnCrashExtraDataNotify(gua_crash_ret);
        }
        else
        {
            LOG_DEBUG("MSDKCrashObserver::Instance.crahs_observer_ is nullptr");
        }
        return default_long;

    }       
};

MSDKCrashObserver MSDKCrashObserver::Instance;

void GUACrashService::SetCrashObserver(GUACrashObserver *crash_observer)
{    
    MSDKCrashObserver::Instance.crahs_observer_ = crash_observer;
#if PLATFORM_IOS || PLATFORM_ANDROID
    GCloud::MSDKSpace::NoSTL::MSDKCrash::SetCrashObserver(&MSDKCrashObserver::Instance);
#endif
}

void GUACrashService::LogInfo(int level, const std::string &tag, const std::string &log)
{
    GCloud::MSDKSpace::NoSTL::MSDKCrash::LogInfo(level, tag, log);
}

void GUACrashService::SetUserValue(const std::string &key, const std::string &value)
{
    GCloud::MSDKSpace::NoSTL::MSDKCrash::SetUserValue(key, value);
}

void GUACrashService::SetUserId(const std::string &user_id)
{
    GCloud::MSDKSpace::NoSTL::MSDKCrash::SetUserId(user_id);
}

void GUACrashService::ReportException(
    int type,
    const std::string &exception_name,
    const std::string &exception_msg,
    const std::string &exception_stack,
    const std::map<std::string, std::string> &ext_info)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    GCloud::MSDKSpace::NoSTL::MSDKCrash::ReportException(type, exception_name, exception_msg, exception_stack, ext_info);
#endif
}

void GUACrashService::CloseCrashReport()
{
    GCloud::MSDKSpace::NoSTL::MSDKCrash::CloseCrashReport();
}
GUA_NAMESPACE_END