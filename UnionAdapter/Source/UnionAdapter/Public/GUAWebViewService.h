//
//  GUAWebViewService.h
//  GUASample
//
//  Created by tafflin on 2022/6/9.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

class GUA_EXTERN GUAWebViewRet : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    /** 100：Close, 101:Native be called from js, 102：js calls the share interface、103：js call sendMessage、104：Embedded browser loading progress */
    int msg_type;
    
    /** js calls the parameters carried by native */
    std::string msg_json_data;

    // [MSDK Only]
    /** Embedded browser loading progress */
    float embed_progress;
	
	// [MSDK Only]
    /** The URL corresponding to the loading progress of the embedded browser */
    std::string embed_url;
};

class GUA_EXTERN GUAWebViewObserver
{
public:
    virtual ~GUAWebViewObserver() {};
    virtual void OnWebViewOptNotify(const GUAWebViewRet &webview_ret) {};
};

class GUA_EXTERN GUAWebViewService
{
// Common API
public:
    /**
	* @brief set WebView module observers
	*
	* @param webview_observer [required] object implements from WebViewObserver
	*/
    static void SetWebViewObserver(GUAWebViewObserver *webView_observer);

	/**
	* @brief open webview with url
	*
	* @param url                          [required] the target page url
	* @param screen_orientation           [optional] Screen orientation mode: 1: default 2: vertical screen 3: horizontal screen
	* @param full_screen_enable           [optional] Whether to open in full screen hide title bar and toolbar
	* @param encrypt_enable               [optional] when set true URL will append auth data
	* @param system_browser_enable        [optional] Whether to open with system browser
	* @param extra_json                   [optional] extra params with json format, default is "{}"
	*/
    static void OpenUrl(
		const std::string &url,
		int screen_orientation = 1,
		bool full_screen_enable = false,
		bool encrypt_enable = true,
		bool system_browser_enable = false,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

    /**
    * @brief Add encrypted ticket
	*
    * @param url [required] URL that requires encrypted ticket
    */
    static std::string GetEncodeUrl(const std::string &url);

    /**
    * @brief JS call
	*
    * @param jsonJsPara json [required] format data
    */
    static void CallJS(const std::string &json_js_params);
// Common API End

// MSDK API
public:
    /**
	*  @brief [MSDK Only] Open AMS Marketing Campaign Center
	*
	*  @param game_name						[required] Abbreviation of service code, each service is different, and each service is allocated by the system when accessing the AMS platform
	*  @param act_channel_id				[required] The ID of the activity channel, which can be obtained by each business by logging in to the [Intermediate Entertainment AMS] management terminal.
	*  @param zone_id						[required] User area server information
	*  @param platform_id					[required] Platform ID: iOS (0), Android (1)
	*  @param partition_id					[required] zone id
	*  @param role_id						[required] role ID
	*  @param screen_type					[optional] Screen Orientation: 1 Landscape and Portrait 2 Portrait 3 Landscape
	*  @param  extra_json					[optional] extra params with json format, default is "{}"
	*/
    static void OpenAmsCenter(
		const std::string &game_name, 
		const std::string &act_channel_id, 
		const std::string &zone_id,
		const std::string &platform_id,
		const std::string &partition_id,
		const std::string &role_id,
		int screen_type = 1,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
    * @brief [MSDK Only] Open the game data authorization page
    *
    * @param url				[required] game data authorization page URL link
    * @param screenType			[optional] screen Orientation: 1 Landscape and Portrait 2 Portrait 3 Landscape
    * @param isFullScreen		[optional] whether to open in full screen
    * @param extraJson			[optional] extra params with json format, default is "{}"
    */
    static void OpenGameDataAuthCenter(
		const std::string &url,
		int screen_type = 1,
		bool full_screen_enable = false,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

    
    /**
    * @brief [MSDK Only] Close the embedded browser, the built-in browser is not currently supported
    */
    static void Close();

	/**
    * @brief [MSDK Only] open the delete account page
	*   
	* @param url				[required] game data authorization page URL link
    * @param screenType			[optional] screen Orientation: 1 Landscape and Portrait 2 Portrait 3 Landscape
    * @param isFullScreen		[optional] whether to open in full screen
    * @param extraJson			[optional] extra params with json format, default is "{}"
    */
   static void OpenDeleteAccountUrl(
		const std::string &url,
		int screen_type = 1,
		bool full_screen_enable = false,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

// MSDK API End
};

GUA_NAMESPACE_END
