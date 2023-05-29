//
//  MSDKPushService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/06/27.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "GUAPushService.h"
#include "MSDKPush.h"
#include "MSDKStructUtility.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

class MSDKPushObserver : public GCloud::MSDKSpace::NoSTL::MSDKPushObserver
{
public:
    static MSDKPushObserver Instance;
    GUAPushObserver* push_observer_;
public:
    MSDKPushObserver() :push_observer_(nullptr) {

    }

    void OnPushOptNotify(const GCloud::MSDKSpace::NoSTL::MSDKBaseRet &msdk_base_ret)
    {
       	GUABaseResult gua_base_ret;
		MSDKStructUtility::ConvertBaseRetToGUA(msdk_base_ret, gua_base_ret);

		if (MSDKPushObserver::Instance.push_observer_ != nullptr) 
		{
			MSDKPushObserver::Instance.push_observer_->OnPushOptNotify(gua_base_ret);
		}
		else
		{
			LOG_DEBUG("MSDKPushObserver::Instance.push_observer_ is nullptr");
		}

    }

    void OnReceiveNotification(const GCloud::MSDKSpace::NoSTL::MSDKPushRet &msdk_push_ret)
    {
		GUAPushResult gua_push_ret;
		MSDKStructUtility::ConvertPushRetToGUA(msdk_push_ret, gua_push_ret);

		if (MSDKPushObserver::Instance.push_observer_ != nullptr) 
		{
			MSDKPushObserver::Instance.push_observer_->OnReceiveNotification(gua_push_ret);
		}
		else
		{
			LOG_DEBUG("MSDKPushObserver::Instance.push_observer_ is nullptr");
		}

    }
};

MSDKPushObserver MSDKPushObserver::Instance;

void GUAPushService::SetPushObserver(GUAPushObserver *observer) 
{
	MSDKPushObserver::Instance.push_observer_ = observer;
	GCloud::MSDKSpace::NoSTL::MSDKPush::SetPushObserver(&MSDKPushObserver::Instance);
}

void GUAPushService::RegisterPush(
	const std::string &channel, 
	const std::string &account) 
{
    GCloud::MSDKSpace::NoSTL::MSDKPush::RegisterPush(channel, account);
}

void GUAPushService::UnregisterPush(const std::string &channel) 
{
    GCloud::MSDKSpace::NoSTL::MSDKPush::UnregisterPush(channel);
}

void GUAPushService::SetTag(
	const std::string &channel, 
	const std::string &tag) 
{
    GCloud::MSDKSpace::NoSTL::MSDKPush::SetTag(channel, tag);
}

void GUAPushService::DeleteTag(
	const std::string &channel, 
	const std::string &tag) 
{
    GCloud::MSDKSpace::NoSTL::MSDKPush::DeleteTag(channel, tag);
}

void GUAPushService::SetAccount(
	const std::string &channel, 
	const std::string &account) 
{
    GCloud::MSDKSpace::NoSTL::MSDKPush::SetAccount(channel, account);
}

void GUAPushService::DeleteAccount(
	const std::string &channel, 
	const std::string &account) 
{
    GCloud::MSDKSpace::NoSTL::MSDKPush::DeleteAccount(channel, account);
}

void GUAPushService::AddLocalNotification(
	const std::string &channel, 
	const GUALocalNotification &gua_local_notification) 
{
    GCloud::MSDKSpace::NoSTL::MSDKLocalNotification msdk_local_notification;
    MSDKStructUtility::ConvertLocalNotificationToMSDK(gua_local_notification, msdk_local_notification);
#if PLATFORM_IOS || PLATFORM_ANDROID
    GCloud::MSDKSpace::NoSTL::MSDKPush::AddLocalNotification(channel, msdk_local_notification);
#endif
}

void GUAPushService::ClearLocalNotifications(const std::string &channel) 
{
    GCloud::MSDKSpace::NoSTL::MSDKPush::ClearLocalNotifications(channel);
}

#ifdef __APPLE__

void GUAPushService::DeleteLocalNotifications(const std::string &key) 
{
#if PLATFORM_IOS
    GCloud::MSDKSpace::NoSTL::MSDKPush::deleteLocalNotifications(key);
#endif
}

void GUAPushService::AddLocalNotificationAtFront(GUALocalNotification &gua_local_notification){
    GCloud::MSDKSpace::NoSTL::MSDKLocalNotification msdk_local_notification;
    MSDKStructUtility::ConvertLocalNotificationToMSDK(gua_local_notification, msdk_local_notification);
#if PLATFORM_IOS
    GCloud::MSDKSpace::NoSTL::MSDKPush::addLocalNotificationAtFront(msdk_local_notification);
#endif
}

void GUAPushService::CleanBadgeNumber() {
#if PLATFORM_IOS
	GCloud::MSDKSpace::NoSTL::MSDKPush::cleanBadgeNumber();
#endif
}

#endif



GUA_NAMESPACE_END