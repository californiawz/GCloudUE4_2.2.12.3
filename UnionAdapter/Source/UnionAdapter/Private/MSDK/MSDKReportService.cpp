//
//  MSDKReportService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/06/27.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "GUAReportService.h"
#include "MSDKReport.h"
#include "MSDKStructUtility.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

//Common API Start

bool GUAReportService::InitReport(const std::string &channel)
{
    return GCloud::MSDKSpace::NoSTL::MSDKReport::Init(channel);
}

void GUAReportService::ReportEvent(
    const std::string &event_name,
    std::map<std::string,std::string> &params,
    const std::string &specific_channel,
    bool is_real_time,
    const std::string &extra_json)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    GCloud::MSDKSpace::NoSTL::MSDKReport::ReportEvent(event_name, params, specific_channel, is_real_time, extra_json);
#endif
}

std::string GUAReportService::GetInstanceID(const std::string &channel)
{
    return GCloud::MSDKSpace::NoSTL::MSDKReport::GetInstanceID(channel);
}

// Common API End

// MSDK API Start

void GUAReportService::SetPushToken(const std::string &push_token)
{
    GCloud::MSDKSpace::NoSTL::MSDKReport::SetPushToken(push_token);
}

// MSDK API End

// INTLSDK API Start
void GUAReportService::SetDeviceLevelObserver(GUADeviceLevelObserver *device_level_observer)
{
    LOG_ERROR("SetDeviceLevelObserver, function not support");
}

void GUAReportService::ReportRevenue(
    const std::string &event_name,
    std::map<std::string, std::string> &params,
    const std::string &currency,
    const std::string &revenue_value,
    const std::string &specific_channel,
    const std::string &extra_json)
{
    LOG_ERROR("ReportRevenue, function not support");
}

void GUAReportService::ReportBinary(
    const char *event_name,
    const char *data,
    int len,
    const std::string &specific_channel)
{
    LOG_ERROR("ReportBinary, function not support");
}

void GUAReportService::FlushINTLEvents()
{
    LOG_ERROR("FlushINTLEvents, function not support");
}

void GUAReportService::StartTraceRoute(const std::string &id)
{
    LOG_ERROR("StartTraceRoute, function not support");
}

std::string GUAReportService::StopTraceRoute()
{
    LOG_ERROR("StopTraceRoute, function not support");
    return GUA_DEFAULT_EMPTY_STRING;
}

void GUAReportService::MarkSessionLoad(
    const char *session_name, 
    const std::string &extra_json)
{
    LOG_ERROR("MarkSessionLoad, function not support");
}

void GUAReportService::SetSessionExtraParam(const std::string &extra_json)
{
    LOG_ERROR("SetSessionExtraParam, function not support");
}

void GUAReportService::ReportSessionLoadDuration()
{
    LOG_ERROR("ReportSessionLoadDuration, function not support");
}

void GUAReportService::MarkSessionClosed()
{
    LOG_ERROR("GUAReportService, function not support");
}

void GUAReportService::PostFrameTimeInSession(float delta_seconds)
{
    LOG_ERROR("PostFrameTimeInSession, function not support");
}

void GUAReportService::PostNetworkLatencyInSession(int latency_ms)
{
    LOG_ERROR("PostNetworkLatencyInSession, function not support");
}

void GUAReportService::AddSessionTag(const char *tag_name)
{
    LOG_ERROR("AddSessionTag, function not support");
}

void GUAReportService::RemoveSessionTag(const char *tag_name)
{
    LOG_ERROR("RemoveSessionTag, function not support");
}

void GUAReportService::ReportCustomEventStep(
    const std::string &event_name,
    unsigned int step,
    const std::string &step_name,
    bool result,
    int error_code,
    const std::map<std::string, std::string> &extra_params)
{
    LOG_ERROR("ReportCustomEventStep, function not support");
}

void GUAReportService::ReportLoginStep(
    unsigned int step,
    const std::string &step_name,
    bool result,
    int error_code,
    const std::map<std::string, std::string> &extra_params)
{
    LOG_ERROR("ReportLoginStep, function not support");
}

void GUAReportService::ReportPayStep(
    unsigned int step,
    const std::string &step_name,
    bool result,
    int error_code,
    const std::map<std::string, std::string> &extra_params)
{
    LOG_ERROR("ReportPayStep, function not support");
}

int GUAReportService::GetDeviceLevel()
{
    LOG_ERROR("GetDeviceLevel, function not support");
    return 0;
}

void GUAReportService::QueryDeviceLevel()
{
    LOG_ERROR("QueryDeviceLevel, function not support");
}

void GUAReportService::SetDeviceLevel(int level)
{
    LOG_ERROR("SetDeviceLevel, function not support");
}

std::string GUAReportService::GetDeviceInfo(const std::string &extra_json)
{
    LOG_ERROR("GetDeviceInfo, function not support");
    return GUA_DEFAULT_EMPTY_STRING;
}

void GUAReportService::CollectionStop()
{
    LOG_ERROR("CollectionStop, function not support");
}

void GUAReportService::CollectionResume()
{
    LOG_ERROR("CollectionResume, function not support");
}

#if GUA_OS_IOS
void GUAReportService::RequestTrackingAuthorization()
{
    LOG_ERROR("CollectionResume, function not support");
}
#endif

void GUAReportService::RestartAnalytics()
{
    LOG_ERROR("RestartAnalytics, function not support");
}

void GUAReportService::StopAnalytics()
{
    LOG_ERROR("StopAnalytics, function not support");
}
// INTLSDK API End

GUA_NAMESPACE_END