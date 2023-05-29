//
//  IReportService.h
//  GCloudPluginManager
//
//  Created by cedar on 2018/8/3.
//  Copyright © 2018年 tdatamaster. All rights reserved.
//

#ifndef IReportService_h
#define IReportService_h

#include <stdlib.h>
#include "string.h"
#include "DeviceInfoDefine.h"

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/IPluginManager.h"

GCLOUD_PLUGIN_NAMESPACE

#define GCLOUDCORE_REPORT_ENV_TEST         0x01
#define GCLOUDCORE_REPORT_ENV_RELEASE      0x02

#define GCLOUDCORE_REPORT_INTERFACE_INFO   0x01
#define GCLOUDCORE_REPORT_QUALITY_INFO     0x02

#if defined(_WIN32) || defined(_WIN64)
typedef long long int64_t;
#endif

#define TDM_PLUGIN_SAFE_MALLOC(num, type) (type *) calloc((num) , sizeof(type))
#define TDM_PLUGIN_SAFE_FREE(ptr)   \
    do                   \
    {                    \
        if (ptr != NULL) \
        {                \
            free(ptr);   \
            ptr = NULL;  \
        }                \
    } while (0)

enum GCLoudCoreEventKeys
{
    kIntKeyAccountType = 100000,
    kIntKeyDataType = 100001,
    kIntKeyInterfaceDataType = 100002,
    
    kIntKeyResultCode = 100100,
    kIntKeyErrorCode,
    KIntKeySecondErrorCode,
    KIntKeyMethodType,
    KIntKeySessionID,
    KIntKeyDuration,
    
    KStrKeyGCloudVersion = 110000,
    KStrKeyGCloudCoreVersion,
    KStrKeyAccountID,
    
    KStrKeyComponentName = 110100,
    KStrKeyComponentVersion,
    KStrKeyMethodName,
    KStrKeyMethodParams,
    KStrKeyResultData,
    KStrKeyErrorMsg,
    KStrKeySecondErrorMsg,
};

#define TDM_REPORT_STANDARD_MODE 0
#define TDM_REPORT_SIMPLE_MODE 1

class IEvent
{
public:
    virtual ~IEvent(){}
    
public:
    virtual void Add(const char* key, const char* value, const int valueLen) = 0;
    virtual void Add(int key, const char* value, const int valueLen) = 0;
    virtual void Add(int key, int64_t value) = 0;
    
public:
    virtual void Report() = 0;
#if defined(__APPLE__) || defined(__ANDROID__)
    virtual void Report(int mode) = 0;
#endif
};


class IReportService : public IPluginService
{
protected:
    ~IReportService(){}
    
public:
    virtual IEvent* CreateEvent(int srcID, const char* eventName) = 0;
    virtual void DestroyEvent(GCloud::Plugin::IEvent** ppEvent) = 0;
    virtual void ReportBinary(int srcID, const char * eventName, const char* data, int len) = 0;
    virtual const char* GetSessionID() = 0;
    virtual const char* GetTDMUID() = 0;

    // 检查当前 TDM 版本是否支持设备信息采集功能
    bool CheckSupportCollectDeviceInfo(GCloud::Plugin::IPluginManager* pluginManager)
    {
        if(NULL == pluginManager)
        {
            return false;
        }
        GCloud::Plugin::IPlugin* plugin = (GCloud::Plugin::IPlugin*)pluginManager->GetPluginByName(PLUGIN_NAME_TDM);
        if(NULL == plugin)
        {
            return false;
        }

        const char* tdmVersion = plugin->GetVersion();

        if(NULL == tdmVersion || strlen(tdmVersion) <= 0)
        {
            return false;
        }

        int curMajorVersion = -1;
        int curFeatureVersion = -1;

        const int supportMajorVersion = 1;
        const int supportFeatureVersion = 6;

        int count = 0;
        int start = 0;

        for(int i = 0; i < strlen(tdmVersion); i++)
        {
            if(tdmVersion[i] == '.')
            {
                int tempLen = i - start;
                if(tempLen > 0)
                {
                    char* tempVersion = TDM_PLUGIN_SAFE_MALLOC(tempLen+1, char);
                    strncpy(tempVersion, tdmVersion+start, tempLen);
                    if(count == 0)
                    {
                        curMajorVersion = atoi(tempVersion);
                    }
                    else if(count == 1)
                    {
                        curFeatureVersion = atoi(tempVersion);
                    }
                    else if(count == 2){}
                    else
                    {
                        TDM_PLUGIN_SAFE_FREE(tempVersion);
                        return false;
                    }
                    TDM_PLUGIN_SAFE_FREE(tempVersion);
                }
                count++;
                // jump the separator .
                start = i+1;
            }
        }

        if(count != 3)
        {
            return false;
        }

        return (supportMajorVersion < curMajorVersion || (supportMajorVersion == curMajorVersion && supportFeatureVersion <= curFeatureVersion));
    }
    // 某些需要异步获取的字段需要先注册回调，回调通知该字段获取成功后再通过获取设备信息接口获取
    virtual void AddDeviceInfoObserver(IDeviceInfoObserver *pObserver, const char *deviceInfoName = COLLECT_DEVICE_INFO_ALL_STRING) = 0;

    // deviceInfoName 为需要获取的设备信息名称，建议通过宏定义的值进行获取
    virtual DeviceInfoStatus GetDeviceInfo(const char* deviceInfoName, int64_t* deviceInfoValue) = 0;
    virtual DeviceInfoStatus GetDeviceInfo(const char* deviceInfoName, bool* deviceInfoValue) = 0;
    /*
     * 该方法支持单个字段的获取，也支持批量获取全部采集字段
     * 如果 deviceInfoName 为 null，那么 deviceInfoValue 将返回全部采集字段的值，此时 deviceInfoValue 为 Json 结构，示例 [{"name":"AndroidID","value":"123456","status":0},{"name":"Brand","value":"Xiaomi","status":0}]
     */
    virtual DeviceInfoStatus GetDeviceInfo(const char* deviceInfoName, char** deviceInfoValue, size_t valueLen) = 0;
    // 获取 String 类型设备信息所需的 value 长度
    virtual DeviceInfoStatus GetDeviceInfoValueLen(const char* deviceInfoName, size_t* valueLen) = 0;
    
    virtual DeviceInfoStatus SetDeviceInfo(const char* deviceInfoName, const int64_t deviceInfoValue) = 0;
    virtual DeviceInfoStatus SetDeviceInfo(const char* deviceInfoName, const bool deviceInfoValue) = 0;
    virtual DeviceInfoStatus SetDeviceInfo(const char* deviceInfoName, const char* deviceInfoValue) = 0;
    virtual void EnableReport(bool enable) = 0;
    // 开启，关闭设备信息采集，true，开启；false，关闭
    virtual void EnableDeviceInfo(bool enable) = 0;
};

//Inner use only
class ICoreReportService : public IPluginService
{
protected:
    ~ICoreReportService(){}
    
public:
    virtual IEvent* CreateEvent(int env, int srcID, const char* eventName) = 0;
    virtual void DestroyEvent(GCloud::Plugin::IEvent** ppEvent) = 0;
};


GCLOUD_PLUGIN_NAMESPACE_END


#endif /* IReportService_h */
