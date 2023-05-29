//
//  GUAReportService.h
//  GUASample
//
//  Created by weiqiangluo on 2022/5/9.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

// device level
typedef enum GUADeviceLevelError {
    UNKOWN_ERROR = -1001,
    
    // parse error
    PARSE_ERROR_LEVEL_NUM = -10001,
    
    JUDGE_ERROR_OPTS = -10030,
    JUDGE_ERROR_DEF_LEVELS_NULL = -10031,

} GUADeviceLevelError;

class GUA_EXTERN GUADeviceLevelResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    int device_level = 0;
};

class GUA_EXTERN GUADeviceLevelObserver
{
public:
    virtual ~GUADeviceLevelObserver() {};
    
    virtual void OnDeviceLevelNotify(const GUADeviceLevelResult &device_level_result) {};
};

class GUA_EXTERN GUAReportService
{
public:
    //Common API Start
    /**
     * @brief init Report
     * @param channel         [required] channel
     */
    static bool InitReport(const std::string &channel);
    
    /**
     * @brief Report events by kv maps
     *
     * @param event_name         [required] event name
     * @param params             [required] key-value events params
     * @param specific_channel   [optional] specific channel
     * @param is_real_time       [optional] real time report
     * @param extra_json         [optional] extra params with json format
     */
    static void ReportEvent(
        const std::string &event_name,
        std::map<std::string, std::string> &params,
        const std::string &specific_channel = GUA_DEFAULT_EMPTY_STRING,
        bool is_real_time = true,
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief get instance id
     *
     * @param channel         [required] channel name
     */
    static std::string GetInstanceID(const std::string &channel);
    
    // Common API End
    
    // INTLSDK API Start
    /**
     * @brief [INTLSDK Only] Report revenue by kv maps
     *
     * @param event_name         [required] event name
     * @param params             [required] key-value events params
     * @param currency           [required] currency
     * @param revenue_value      [required] revenue value
     * @param specific_channel   [optional] specific channel
     * @param extra_json         [optional] extra params with json format
     */
    static void ReportRevenue(
        const std::string &event_name,
        std::map<std::string, std::string> &params,
        const std::string &currency,
        const std::string &revenue_value,
        const std::string &specific_channel = GUA_DEFAULT_EMPTY_STRING,
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    

    /**
     * @brief [INTLSDK Only] Report binary format datas
     *
     * @param event_name         [required] event name
     * @param data               [required] datas in binary format
     * @param len                [required] the data lenght
     * @param specific_channel   [optional] specific channel
     */
    static void ReportBinary(
        const char *event_name,
        const char *data,
        int len,
        const std::string &specific_channel = GUA_DEFAULT_EMPTY_STRING);

    /**
     * @brief [INTLSDK Only] Flush cached INTL events
     */
    static void FlushINTLEvents();
    
    /**
     * @brief [INTLSDK Only] Start traceRoute
     *
     * @param id         [required] traceRoute id
     */
    static void StartTraceRoute(const std::string &id);
    
    /**
     * @brief [INTLSDK Only] Stop traceRoute
     */
    static std::string StopTraceRoute();

	/**
	 * @brief [INTLSDK Only] Start a data collection session. Before calling this method, nothing will be collected.
	 * Multiple calls of this method with the same session_name will be ignored, and current session
	 * will be marked as closed if you pass a different session_name.
	 *
	 * @param session_name [required]  session name
     * @param extra_json   [optional] extra params with json format
	 */
	static void MarkSessionLoad(
        const char *session_name,
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

    /**
     * @brief [INTLSDK Only] Set extra params for current collection session.
     *
     * @param extra_json [required] extra params with json format
     */
    static void SetSessionExtraParam(const std::string &extra_json);
    
	/**
	 * @brief [INTLSDK Only] Mark current collection session as load completed. You can use this method to report the load time of a session.
	 * Only the first call will be accepted during the same session.
	 */
	static void ReportSessionLoadDuration();

	/**
	 * @brief [INTLSDK Only] Stop the current data collection session. After calling this method, nothing will be collected.
	 */
	static void MarkSessionClosed();

	/**
	 * @brief [INTLSDK Only] You may want to call this method in every tick of the game loop. Through the reported delta seconds between each frame,
	 * we can monitor the fps of the game. If no session is started by calling [MarkSessionLoad], this method does nothing.
	 *
	 * @param delta_seconds  [required] The delta time between each frame, in seconds.
	 */
	static void PostFrameTimeInSession(float delta_seconds);

	/**
	 * @brief [INTLSDK Only] Collect the network latency. You should implement the calculation of network latency yourself and report it to the SDK
	 * by calling this method.
	 *
	 * @param latency_ms  [required] The network latency, in milliseconds.
	 */
	static void PostNetworkLatencyInSession(int latency_ms);

	/**
	 * @brief [INTLSDK Only] 
	 */
	static void RestartAnalytics();

	/**
	 * @brief [INTLSDK Only] 
	 */
	static void StopAnalytics();

    /**
     * @brief [INTLSDK Only] During a collection session, you may want to tag some data for some specific purpose. In this situation, you
     * can use this method to add a tag for the collecting data. If no session is started by calling [MarkSessionLoad],
     * this method does nothing.
     *
     * @param tag_name [required]  A tag for filtering data
     */
    static void AddSessionTag(const char *tag_name);

    /**
     * @brief [INTLSDK Only] Remove the last added tag for the collecting data. When a session is closed by calling [MarkSessionClosed],
     * all added tags will be automatically removed as well.
     * @param tag_name [required]  A tag for filtering data
     */
    static void RemoveSessionTag(const char *tag_name);

	/**
     * @brief [INTLSDK Only] Report each step of a custom event
     * @param event_name    [required] event name defined by user
     * @param step          [required] step index
     * @param step_name     [required] step name
     * @param result        [required] whether the step is success or failed
     * @param error_code    [required] the error code of this step, if it failed
     * @param extra_params  [required] custom params
     */
	static void ReportCustomEventStep(
        const std::string &event_name,
        unsigned int step,
        const std::string &step_name,
        bool result,
        int error_code,
        const std::map<std::string, std::string> &extra_params);

	/**
	 * @brief [INTLSDK Only] Report each step of login event, event name is [Login]
	 * @param step step     [required] index
	 * @param step_name     [required] step name
	 * @param result        [required] whether is success or failed
	 * @param error_code    [required] the error code of this step, if it failed
	 * @param extra_params  [required] custom params
	 */
    static void ReportLoginStep(
        unsigned int step,
        const std::string &step_name,
        bool result,
        int error_code,
        const std::map<std::string, std::string> &extra_params);

    /**
     * @brief [INTLSDK Only] Report each step of payment event, event name is [Pay]
     * @param step          [required] step index
     * @param step_name     [required] step name
     * @param result        [required] whether the step is success or failed
     * @param error_code    [required] the error code of this step, if it failed
     * @param extra_params  [required] custom params
     */
    static void ReportPayStep(
        unsigned int step,
        const std::string &step_name,
        bool result,
        int error_code,
        const std::map<std::string, std::string> &extra_params);

    /**
     * @brief [INTLSDK Only] Get the device level of this device
     * @return device level of this device, if return negtive number, means error occured
     */
    static int GetDeviceLevel();

    /**
     * @brief [INTLSDK Only] Get the latest device level config file and judge the device level
     */
     static void QueryDeviceLevel();

    /**
     * @brief [INTLSDK Only] After QueryDeviceLevel, the result will dispatched to observer
     * @param device_level_observer  [required] observer
     */
    static void SetDeviceLevelObserver(GUADeviceLevelObserver *device_level_observer);

    /**
     * @brief [INTLSDK Only] Set device level by game
     * @param level  [required] device level
     */
    static void SetDeviceLevel(int level);

    /**
     * @brief [INTLSDK Only] Get the device info
     * @param extra_json [required] extra params with json format
     */
    static std::string GetDeviceInfo(const std::string &extra_json);

    /**
     * @brief [INTLSDK Only] Set collection to stop
     */
    static void CollectionStop();

    /**
     * @brief [INTLSDK Only] Set collection to resume
     */
    static void CollectionResume();

#if GUA_OS_IOS
    /**
     * @brief [INTLSDK Only] The request for user authorization to access app-related data
     */
    static void RequestTrackingAuthorization();
#endif
    // INTLSDK API End
    // MSDK API Start

    /**
     * @brief [MSDK Only] Set push token
     * 
     * @param push_token    [required] push token
     */
    static void SetPushToken(const std::string &push_token);
    // MSDK API End
};

GUA_NAMESPACE_END
