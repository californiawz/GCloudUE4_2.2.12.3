//
//  GUAToolsService.h
//  GUASample
//
//  Created by weiqiangluo on 2022/5/9.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

// Common Struct Start
class GUA_EXTERN GUAToolsResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    std::string deep_link_url;   //deepLinkUrl
    std::string short_link_url;   //shortLinkUrl
};
// Common Struct End

// INTLSDK Struct Start
class GUA_EXTERN GUADNSResult : public GUABaseResult
{
public:
    using GUABaseResult::GUABaseResult;
    std::string v4;
    std::string v6;
    std::string host;
};
class GUA_EXTERN GUADetectNetworkResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    // Community broadband latency
    double local_router_time;
    
    // Router delay
    double internet_router_time;
    
    // Internet latency
    double internet_delay;
};

class GUA_EXTERN GUACutoutRect
{
public:
    int top;
    int bottom;
    int left;
    int right;

    GUACutoutRect(int top = 0, int bottom = 0, int left = 0, int right = 0):
        top(top), bottom(bottom), left(left), right(right) {
    }

};

class GUA_EXTERN GUACutoutResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    // Whether the device has a notched display
    bool has_cutout;
    
    // Some devices allow users to fill the gaps of special-shaped screens with black
    bool is_cutout_hidden;
    
    // Screen height
    int screen_height;
    
    // Screen width
    int screen_width;
    
    // Status bar height
    int status_bar_height;
    
    // Special-shaped screen area
    std::vector<GUACutoutRect> cutout_rects;
    
    // Safe area
    GUACutoutRect safe_area;
};
// INTLSDK Struct end

// MSDK Struct Start
class GUA_EXTERN GUAToolsFreeFlowInfo {
public:
    // All free flow IP lists
    std::string ip_all;
    
    // if use free flow return corresponding string in config or return param key
    std::string ip_connect;
    
    //1:free flow，0:non free flow
    int is_free;
    
    //1: WCDMA，2: CDMA，3: CMCC，99: the Others
    int cc_type;
};

class GUA_EXTERN GUAToolsFreeFlowRet : public GUABaseResult {
public:
    GUAToolsFreeFlowInfo free_flow_info;
};
// MSDK Struct End

// Common Observer Start
class GUA_EXTERN GUAToolsObserver
{
public:
    virtual ~GUAToolsObserver(){};

    virtual void OnToolsResultNotify(const GUAToolsResult &tools_ret) {};
    virtual void OnToolsFreeFlowRetNotify(const GUAToolsFreeFlowRet &toolsFreeFlowRet) {};

};
// Common Observer End

// INTLSDK Observer Start
class GUA_EXTERN GUADetectNetworkObserver
{
public:
    virtual ~GUADetectNetworkObserver(){};

    virtual void OnDetectNetworkResultNotify(const GUADetectNetworkResult &detect_network_ret) {};

};

class GUA_EXTERN GUACutoutInfoObserver
{
public:
    virtual void OnCutoutInfoResultNotify(const GUACutoutResult &result) {};

    virtual ~GUACutoutInfoObserver() {};
};

class GUA_EXTERN GUADNSObserver
{
public:
    virtual void OnDNSResultNotify(const GUADNSResult &dns_result) {};
    virtual ~GUADNSObserver() {};
};

// INTLSDK Observer End

class GUA_EXTERN GUAToolsService
{
public:
    //Common API Start
    
    /**
     * @brief Set Tools module observer
     *
     * @param tools_observer	[required] object implements from GUAToolsObserver
     */
    static void SetToolsObserver(GUAToolsObserver *tools_observer);
    
    /**
     * @brief Get result of a third app installed
     *
     * @param channel			[required] channel name, such as "Facebook"
     * @param extra_json		[optional] extra params with json format
	 *
     * @return the result of installation status, true for installed, false for not installed
     */
    static bool IsAppInstalled(
		std::string channel,
		std::string extra_json = GUA_DEFAULT_JSON_STRING);

    /**
     * @brief Open a third app by its deeplink
     * @param link				[required] deeplink has configured for the third party app
     */
    static void OpenDeepLink(std::string link);
    
    /**
     * @brief Convert a long url to a short url
     *
     * @param url			[required] the target URL
     * @param type_mark		[optional] urlTypeMark:url mark typ, support uppercase A-Z letters, default is "A
	 *
     * @return the result
     */
    static bool ConvertShortUrl(
		std::string url, 
		std::string type_mark = "A");
    
    /**
    * @brief Dynamically obtain configuration values.
    *
    * @param key			[required] Configuration key
    * @param defaultVal		[optional] Get the return value after failure, not mandatory
    * @param project		[optional] Config project
	*
    * @return the config value
    */
    static std::string GetConfig(
		const std::string &key, 
		const std::string &default_value, 
		const std::string &project = GUA_DEFAULT_EMPTY_STRING);
    
    /**
    * @brief Dynamically obtain configuration values.
    *
    * @param key       [required] Configuration key
    * @param defaultVal [optional] Get the return value after failure, not mandatory
    * @param project [optional] Config project
	*
    * @return the config value
    */
    static bool GetConfig(
		const std::string &key, 
		const bool default_value, 
		const std::string &project = GUA_DEFAULT_EMPTY_STRING);
    
    /**
    * @brief Dynamically obtain configuration values.
    *
    * @param key			[required] Configuration key
    * @param defaultVal		[optional] Get the return value after failure, not mandatory
    * @param project		[optional] Config project
	*
    * @return the config value
    */
    static int GetConfig(
		const std::string &key, 
		const int default_value, 
		const std::string &project = GUA_DEFAULT_EMPTY_STRING);
    
    /**
    * @brief Dynamically obtain configuration values.
    *
    * @param key			[required] Configuration key
    * @param defaultVal		[optional] Get the return value after failure, not mandatory
    * @param project		[optional] Config project
	*
    * @return the config value
    */
    static int64_t GetConfig(
		const std::string &key, 
		const int64_t default_value, 
		const std::string &project = GUA_DEFAULT_EMPTY_STRING);

    /**
    * @brief Dynamically obtain configuration values.
    *
    * @param config			[required] Configuration content
    * @param project		[optional] Config project
	*
    * @return the config value
    */
    static bool UpdateConfig(
		const std::map<std::string, std::string> &config, 
		const std::string &project = GUA_DEFAULT_EMPTY_STRING);
    //Common API End
    
    // INTLSDK API Start
    
#if GUA_OS_ANDROID || GUA_OS_IOS

	/**
	 * @brief [INTLSDK Only] Set Detect network module observer
	 *
	 * @param detectNetwork_observer	[required] object implements from GUADetectNetworkObserver
	 */
    static void SetDetectNetworkObserver(GUADetectNetworkObserver *detectNetwork_observer);

	/**
	 * @brief [INTLSDK Only] Start Detect network module observer
	 *
	 * @param id			[required] target detect network id
	 */
    static void StartDetectNetwork(std::string id);
#endif

	/**
	 * @brief [INTLSDK Only] Set DNS module observer
	 *
	 * @param observer	[required] object implements from GUADNSObserver
	 */
    static void SetDNSObserver(GUADNSObserver* observer);

    /**
    * @brief [INTLSDK Only] Get Ip By Host.
	*
    * @param host		[required] get Ip with host Sync.
    *
    * @return return Ip string with host.
    */
    static std::string GetIpByHost(const std::string &host);

    /**
    * @brief [INTLSDK Only] Query Ip By Host Async.
	*
    * @param host		[required]query Ip with host .
    */
    static void QueryIpByHost(const std::string &host);

    /**
    * @brief [INTLSDK Only] Remove Host Cache for httpDNS
	*
    * @param host			[optional] remove cache based on host, remove all hosts cache when host is empty
    */
    static void RemoveHostCache(const std::string &host = GUA_DEFAULT_EMPTY_STRING);

	/**
	 * @brief [INTLSDK Only] Set Cutout module observer
	 *
	 * @param cutout_observer	[required] object implements from GUACutoutObserver
	 */
    static void SetCutoutObserver(GUACutoutInfoObserver *cutout_observer);
    
    /**
    * @brief [INTLSDK Only] Init Cutout module, only android platform needs to be initialized actively
    */
    static void loadCutoutData();
    
    /**
    * @brief [INTLSDK Only] Set current region for httpDNS
    * @brief Recommand to set region when SDK init
	*
    * @param region			[required]current region based on ISO_3166-1 standard.
    */
    static void SetDNSRegion(const std::string region);


// INTLSDK API End
    
//MSDK API Start
    /**
    * @brief [MSDK Only] Query free flow service info
	*
    * @param key			[required] according to the return of key (original IP), the corresponding value (corresponding SVIP) of the background stream free configuration
    * @param extraJson		[optional] extra params with json format
	*
	* @return get free flow service info result
    */
    static bool GetFreeFlowInfo(
		std::string key, 
		std::string extraJson= GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief [MSDK Only] Used to open WebView for central control
	 *
     * @param jsonStr		[required]WebView config
	 *
     * @return open trigger return true，or return false
     */
    static bool OpenPrajnaWebView(std::string jsonStr);
    
    /**
     * @brief [MSDK Only] Central control reports. Currently, it supports domestic channels, but not overseas channels.
	 *
     * @param projnaJson		[required] projna json
	 * 
	 * return report result
     */
    static bool ReportPrajna(std::string projnaJson);

    /**
     * @brief [MSDK Only] Return according to the error code, default to use the device language
	 *
     * @param retCode		[required] the error code
	 *
     * @return return language 
     */
    static std::string GetRetMsg(int retCode);

    /**
     * @brief [MSDK Only] Get channel package packaging information
	 * 
	 * @return config information
	 */
    static std::string GetConfigChannel();
    
#if GUA_OS_IOS || GUA_OS_MAC
    /**
     * @breif [MSDK Only] Show application rating alert
     */
    static bool ShowRatingAlert();
    
    /**
     * @brief [MSDK Only] Show whether the channel application is installed
	 *
     * @param appid			[required] application id
     */
    static void ShowAppStoreProductView(std::string appid);
#endif

#if GUA_OS_ANDROID
    /**
     * @brief [MSDK Only] Get guest id
	 *
	 * @return guest id
	 */
    static std::string GetGuestId();

	/**
     * @brief [MSDK Only] Set guest id
	 * 
	 * @param guestId		[required] guest id
	 */
    static void SetGuestId(std::string guestId);

#endif
//MSDK API End
};

GUA_NAMESPACE_END
