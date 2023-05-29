//
//  MSDKWebViewService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/06/24.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "GUAWebViewService.h"
#include "MSDKWebView.h"
#include "MSDKStructUtility.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

class MSDKWebViewObserver : public GCloud::MSDKSpace::NoSTL::MSDKWebViewObserver
{
public:
	static MSDKWebViewObserver Instance;
	GUAWebViewObserver* webview_observer_;
public:
	MSDKWebViewObserver() :webview_observer_(nullptr) {

	}   

    void OnWebViewOptNotify(const GCloud::MSDKSpace::NoSTL::MSDKWebViewRet &msdk_webview_ret)
    {
        GUAWebViewRet gua_webview_ret;
		MSDKStructUtility::ConvertWebViewRetToGUA(msdk_webview_ret, gua_webview_ret);

		if (MSDKWebViewObserver::Instance.webview_observer_ != nullptr) 
		{
			MSDKWebViewObserver::Instance.webview_observer_->OnWebViewOptNotify(gua_webview_ret);
		}
		else
		{
			LOG_DEBUG("MSDKToolsObserver::Instance.tools_observer_ is nullptr");
		}

    }
};

MSDKWebViewObserver MSDKWebViewObserver::Instance;

void GUAWebViewService::SetWebViewObserver(GUAWebViewObserver *observer) {
	MSDKWebViewObserver::Instance.webview_observer_ = observer;
#if PLATFORM_IOS || PLATFORM_ANDROID
	GCloud::MSDKSpace::NoSTL::MSDKWebView::SetWebViewObserver(&MSDKWebViewObserver::Instance);
#endif
}

void GUAWebViewService::OpenUrl(const std::string &url, int screen_orientation, bool full_screen_enable,bool encrypt_enable, bool system_browser_enable, const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKWebView::OpenUrl(url, screen_orientation, full_screen_enable, encrypt_enable, extra_json, system_browser_enable);
}

std::string GUAWebViewService::GetEncodeUrl(const std::string &url) {
#if PLATFORM_IOS || PLATFORM_ANDROID || MSDK_PLATFORM_WINDOWS
	return GCloud::MSDKSpace::NoSTL::MSDKWebView::GetEncodeUrl(url);
#endif
	return "";
}

void GUAWebViewService::CallJS(const std::string &json_js_params) {
	GCloud::MSDKSpace::NoSTL::MSDKWebView::CallJS(json_js_params);
}

void GUAWebViewService::OpenAmsCenter(const std::string &game_name, const std::string &act_channel_id, const std::string &zone_id,
	const std::string &platform_id,
	const std::string &partition_id,
	const std::string &role_id,
	int screen_type,
	const std::string &extra_json) 
{
    GCloud::MSDKSpace::NoSTL::MSDKWebView::OpenAmsCenter(game_name, act_channel_id, zone_id, platform_id, partition_id, role_id, screen_type, extra_json);
}

void GUAWebViewService::OpenGameDataAuthCenter(
	const std::string &url,
	int screen_type,
	bool full_screen_enable,
	const std::string &extra_json) 
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	GCloud::MSDKSpace::NoSTL::MSDKWebView::OpenGameDataAuthCenter(url, screen_type, full_screen_enable, extra_json);
#endif
}

void GUAWebViewService::Close() {
    GCloud::MSDKSpace::NoSTL::MSDKWebView::Close();
}

void GUAWebViewService::OpenDeleteAccountUrl(
	const std::string &url, 
	int screen_type, 
	bool full_screen_enable, 
	const std::string &extra_json)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	GCloud::MSDKSpace::NoSTL::MSDKWebView::OpenDeleteAccountUrl(url, screen_type, full_screen_enable, extra_json);
#endif
}
GUA_NAMESPACE_END

