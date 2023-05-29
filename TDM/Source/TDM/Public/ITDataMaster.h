//
//  ITDataMaster.h
//  ITDataMaster
//
//  Created by Morris on 16/8/16.
//  Copyright © 2016年 TDataMaster. All rights reserved.
//

#ifndef ITDataMaster_hpp
#define ITDataMaster_hpp

#include "TDataMasterDefines.h"
#include <stdio.h>
#include <map>
#include <string>

#define PUBLIC_API TDM_EXPORT

#define TDM_REPORT_STANDARD_MODE 0
#define TDM_REPORT_SIMPLE_MODE 1

_TDM_Name_Space
{
    class IEventData {
    public:
        virtual PUBLIC_API void Add(const char *key, const char *value, const int valueLen = 0) = 0;
        virtual PUBLIC_API void Add(int key, const char *value, const int valueLen = 0) = 0;
        virtual PUBLIC_API void Add(int key, int64_t value) = 0;
        virtual ~IEventData(){};
    };
    
    class IEventReporter
    {
    public:
        virtual PUBLIC_API void Add(const char* key, const char* value, const int valueLen = 0) = 0;
        [[deprecated("deprecated, use string key-value for instead")]]
        virtual PUBLIC_API void Add(int key, const char* value, const int valueLen = 0) = 0;
        [[deprecated("deprecated, use string key-value for instead")]]
        virtual PUBLIC_API void Add(int key, int64_t value) = 0;
        virtual PUBLIC_API void Report() = 0;
        virtual ~IEventReporter(){};
        virtual PUBLIC_API void Report(int mode) = 0;
        
        virtual PUBLIC_API void Add(const IEventData* data) = 0;
    };
    
    class ITDataMaster
    {
    protected:
        ITDataMaster(){}
        virtual ~ITDataMaster(){}
        
    public:
        static PUBLIC_API ITDataMaster* GetInstance();
        static PUBLIC_API void ReleaseInstance();
        
    public:
        
        virtual const char* GetTDMUID() = 0;
        
        virtual PUBLIC_API bool Initialize(const char* AppId, const char* AppChannel, const char *appKey = NULL) = 0;
        
        virtual PUBLIC_API void EnableReport(bool enable) = 0;
        
        virtual PUBLIC_API void SetLogLevel(LogLevel level) = 0;
        
        virtual PUBLIC_API void ReportBinary(int srcID, const char * eventName, const char* data, int len) = 0;
        
        [[deprecated("deprecated, use PluginReportEvent(int srcID, const char* eventName, const IEventData* eventData) for instead")]]
        virtual PUBLIC_API void PluginReportEvent(int srcID, const char* eventName, const std::map<std::string, std::string>& customData, const std::map<int32_t, int64_t>& intData, const std::map<int32_t, std::string>& strData) = 0;
        
        virtual PUBLIC_API const char* GetSessionID() = 0;
        
        virtual PUBLIC_API const char* GetTDMSDKVersion() = 0;
        
    public:
        virtual PUBLIC_API IEventReporter* CreateEventReporter(int srcId, const char* eventName) = 0;
        
        virtual PUBLIC_API void DestroyEventReporter(IEventReporter*& reporter) = 0;
        
    public:
        virtual PUBLIC_API void SetRouterAddress(bool isTest, const char* url) = 0;
        virtual PUBLIC_API void EnableDeviceInfo(bool enable) = 0;
        virtual PUBLIC_API void ReportLogin(int platform, const char* openid) = 0;
        
        virtual PUBLIC_API TDMDeviceInfoStatus SetDeviceInfo(const char *deviceName, int64_t value) = 0;
        virtual PUBLIC_API TDMDeviceInfoStatus SetDeviceInfo(const char *deviceName, bool value) = 0;
        virtual PUBLIC_API TDMDeviceInfoStatus SetDeviceInfo(const char *deviceName, const char *value) = 0;
        
        virtual PUBLIC_API TDMDeviceInfoStatus GetDeviceInfo(const char *deviceName, bool& info) = 0;
        virtual PUBLIC_API TDMDeviceInfoStatus GetDeviceInfo(const char *deviceName, int64_t& info) = 0;
        virtual PUBLIC_API TDMDeviceInfoStatus GetDeviceInfo(const char *deviceName, char*& info, size_t &length) = 0;
        
    public:
        virtual PUBLIC_API void EnableHTTPProxy(bool enable) = 0;
        
        virtual PUBLIC_API IEventData* CreateEventData() = 0;
        virtual PUBLIC_API void DestroyEventData(IEventData*& reporter) = 0;
        
        virtual PUBLIC_API void ReportASAEvent() = 0;
        virtual PUBLIC_API void PluginReportEvent(int srcID, const char* eventName, const IEventData* eventData) = 0;
        virtual PUBLIC_API void ReportBinary(int srcID, const char *eventName, const char *data, const int len, const char *dstFileName, const bool forceSaveCOS = true) = 0;
        
        virtual PUBLIC_API TDMReportResultCode ReportKVRealTime(int srcID, const char* eventName, const IEventData* eventData, const bool goOffline = true) = 0;
        virtual PUBLIC_API TDMReportResultCode ReportBinRealTime(int srcID, const char* eventName, const char* data, int len, const bool goOffline = true) = 0;
        
    };
}

#endif /* ITDataMaster_h */
