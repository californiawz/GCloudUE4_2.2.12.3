//
//  MSDKToolsService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/06/27.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "GUAToolsService.h"
#include "MSDKTools.h"
#include "MSDKConfig.h"
#include "MSDKStructUtility.h"
#include "GUAErrorCode.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

class MSDKToolsObserver : public GCloud::MSDKSpace::NoSTL::MSDKToolsObserver
{
public:
	static MSDKToolsObserver Instance;
	GUAToolsObserver *tools_observer_;

public:
	MSDKToolsObserver() : tools_observer_(nullptr)
	{
	}

	void OnToolsRetNotify(const GCloud::MSDKSpace::NoSTL::MSDKToolsRet &msdk_tools_ret)
	{
		GUAToolsResult gua_tools_ret;
		MSDKStructUtility::ConvertToolsRetToGUA(msdk_tools_ret, gua_tools_ret);

		if (MSDKToolsObserver::Instance.tools_observer_ != nullptr)
		{
			MSDKToolsObserver::Instance.tools_observer_->OnToolsResultNotify(gua_tools_ret);
		}
		else
		{
			LOG_DEBUG("MSDKToolsObserver::Instance.tools_observer_ is nullptr");
		}

	}

	void OnToolsFreeFlowRetNotify(const GCloud::MSDKSpace::NoSTL::MSDKToolsFreeFlowRet &msdk_tools_free_flow_ret)
	{
		GUAToolsFreeFlowRet gua_tools_free_flow_ret;
		MSDKStructUtility::ConvertToolsFreeFlowRetToGUA(msdk_tools_free_flow_ret, gua_tools_free_flow_ret);

		if (MSDKToolsObserver::Instance.tools_observer_ != nullptr)
		{
			MSDKToolsObserver::Instance.tools_observer_->OnToolsFreeFlowRetNotify(gua_tools_free_flow_ret);
		}
		else
		{
			LOG_DEBUG("MSDKToolsObserver::Instance.tools_observer_ is nullptr");
		}

	}
};

MSDKToolsObserver MSDKToolsObserver::Instance;

void GUAToolsService::SetToolsObserver(GUAToolsObserver *observer)
{
	MSDKToolsObserver::Instance.tools_observer_ = observer;
#if PLATFORM_IOS || PLATFORM_ANDROID
	GCloud::MSDKSpace::NoSTL::MSDKTools::SetToolsObserver(&MSDKToolsObserver::Instance);
#endif
}

bool GUAToolsService::IsAppInstalled(
	std::string channel,
	std::string extra_json)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::IsAppInstall(channel, extra_json);
#else
	return false;
#endif
}

void GUAToolsService::OpenDeepLink(std::string link)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	GCloud::MSDKSpace::NoSTL::MSDKTools::OpenDeepLink(link);
#endif
}

bool GUAToolsService::ConvertShortUrl(
	std::string url,
	std::string type_mark)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::ConvertShortUrl(url, type_mark);
#else
	return false;
#endif
}

std::string GUAToolsService::GetConfig(
	const std::string &key,
	const std::string &default_value,
	const std::string &project)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::GetConfig(key, default_value);
#else
	return "";
#endif
}

bool GUAToolsService::GetConfig(
	const std::string &key,
	const bool default_value,
	const std::string &project)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::GetConfig(key, default_value);
#else	
	return false;
#endif
}

int GUAToolsService::GetConfig(
	const std::string &key,
	const int default_value,
	const std::string &project)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::GetConfig(key, default_value);
#else	
	return -1;
#endif
}

int64_t GUAToolsService::GetConfig(
	const std::string &key,
	const int64_t default_value,
	const std::string &project)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::GetConfig(key, (long)default_value);
#else
	return -1;
#endif
}

bool GUAToolsService::UpdateConfig(
	const std::map<std::string, std::string> &config,
	const std::string &project)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKConfig::UpdateConfig(config);
#else
	return false;
#endif
}

bool GUAToolsService::GetFreeFlowInfo(
	std::string key,
	std::string extraJson)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::GetFreeFlowInfo(key, extraJson);
#else
	LOG_ERROR("GetFreeFlowInfo, function not support");
	return false;
#endif
}

bool GUAToolsService::OpenPrajnaWebView(std::string jsonStr)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::OpenPrajnaWebView(jsonStr);
#else
	return false;
#endif
}

bool GUAToolsService::ReportPrajna(std::string projnaJson)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::ReportPrajna(projnaJson);
#else
	return false;
#endif
}

std::string GUAToolsService::GetRetMsg(int retCode)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::GetRetMsg(retCode);
#else
	return "";
#endif
}


std::string GUAToolsService::GetConfigChannel()
{
	std::string seqID = "";
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::GetConfigChannelID(String(seqID));
#else
	return "";
#endif
}

#if MSDK_PLATFORM_WINDOWS
#else

#if defined(__APPLE__)

bool GUAToolsService::ShowRatingAlert()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	return GCloud::MSDKSpace::NoSTL::MSDKTools::ShowRatingAlert();
#else
	return false;
#endif
}

void ShowAppStoreProductView(std::string appid)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	GCloud::MSDKSpace::NoSTL::MSDKTools::ShowAppStoreProductView(appid);
#endif
}

#endif
#if defined(ANDROID)

std::string GUAToolsService::GetGuestId()
{
	return GCloud::MSDKSpace::NoSTL::MSDKTools::GetGuestId();
}

void GUAToolsService::SetGuestId(std::string guestId)
{
	GCloud::MSDKSpace::NoSTL::MSDKTools::SetGuestId(guestId);
}

#endif
#endif // MSDK_PLATFORM_WINDOWS

// INTLSDK API Start
#if GUA_OS_ANDROID || GUA_OS_IOS
void GUAToolsService::SetDetectNetworkObserver(GUADetectNetworkObserver *observer)
{
	LOG_ERROR("SetDetectNetworkObserver, function not support");
}

void GUAToolsService::StartDetectNetwork(std::string id)
{
	LOG_ERROR("StartDetectNetwork, function not support");
}
#endif

void GUAToolsService::SetDNSObserver(GUADNSObserver *observer)
{
	LOG_ERROR("SetDNSObserver, function not support");
}

std::string GUAToolsService::GetIpByHost(const std::string &host)
{
	LOG_ERROR("GetIpByHost, function not support");
	return "";
}

void GUAToolsService::QueryIpByHost(const std::string &host)
{
	LOG_ERROR("QueryIpByHost, function not support");
}

void GUAToolsService::RemoveHostCache(const std::string &host)
{
	LOG_ERROR("RemoveHostCache, function not support");
}

void GUAToolsService::SetCutoutObserver(GUACutoutInfoObserver *observer)
{
	LOG_ERROR("SetCutoutObserver, function not support");
}

void GUAToolsService::loadCutoutData()
{
	LOG_ERROR("loadCutoutData, function not support");
}

void GUAToolsService::SetDNSRegion(const std::string region)
{
	LOG_ERROR("SetDNSRegion, function not support");
}

GUA_NAMESPACE_END
