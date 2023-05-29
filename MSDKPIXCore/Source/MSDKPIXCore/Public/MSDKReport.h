/*!
 * @Module MSDK
 *
 * @Header  MSDKReport.h
 * @Author  developer
 * @date 2018/6/11
 * @abstract
 * 事件上报接口声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */


#ifndef MSDK_REPORT_HPP
#define MSDK_REPORT_HPP

#include <stdio.h>
#include "MSDKDefine.h"

NS_MSDK_BEGIN

class MSDK_EXPORT MSDKReport
{
private:
    static void ReportEventPRV(const String &eventName, Vector<KVPair> params,
                               const String &spChannel = "",
                               bool isRealTime = true,
                               const String &extraJson = "");
public:
    /**
    * 上报渠道初始化
    * @param channels 渠道上报的渠道，多个渠道用逗号分隔
    */
	MSDK_EXPORT_UE static bool Init(const String &channels);

    /**
    * 上报事件
    * @param eventName 事件
    * @param params 逗号分隔参数
    * @param spChannel 指定渠道，若无可填空字符串。
    * @param isRealTime 是否事实上报
    */
	MSDK_EXPORT_UE static void ReportEvent(const String &eventName, std::map<std::string, std::string> &params, const String &spChannel = "", bool isRealTime = true,const String &extraJson = "")
    {
	    MSDKPIX_LOG_DEBUG("", "eventName:%s, spChannel:%s, isRealTime:%s", eventName.c_str(), spChannel.c_str(), isRealTime ? "true" : "false");
        Vector<KVPair> tmp;
        std::map<std::string, std::string>::iterator it = params.begin();
        for (; it != params.end(); it++)
        {
            KVPair kvPair;
            kvPair.key = (*it).first;
            kvPair.value = (*it).second;
            tmp.push_back(kvPair);
        }

#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else
        ReportEventPRV(eventName, tmp, spChannel, isRealTime, extraJson);
#endif
    }

	MSDK_EXPORT_UE static void SetPushToken(const String &pushToken);

    // 此接口从 V5.16 开始废弃，请使用 getInstanceIDAsync 方法获取 InstanceID，详情请参见 【事件上报模块】 文档
    MSDK_EXPORT_UE static std::string GetInstanceID(const String &channel) MSDK_DEPRECATED("deprecated from V5.16, use getInstanceIDAsync instead in MSDKExtend module");

};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

class MSDK_EXPORT MSDKReport
{
public:
    /**
     * 上报渠道初始化
     * @param channels 渠道上报的渠道，多个渠道用逗号分隔
     */
    MSDK_EXPORT_UE static bool Init(const String &channels);
    
    /**
     * 上报事件
     * @param eventName 事件
     * @param params 逗号分隔参数
     * @param spChannel 指定渠道，若无可填空字符串。
     * @param isRealTime 是否事实上报
     */
    MSDK_EXPORT_UE static void ReportEvent(const String &eventName, const StringMap &params, const String &spChannel = "", bool isRealTime = true,const String &extraJson = "");
    
    MSDK_EXPORT_UE static void SetPushToken(const String &pushToken);
    
    // 此接口从 V5.16 开始废弃，请使用 getInstanceIDAsync 方法获取 InstanceID，详情请参见 【事件上报模块】 文档
    MSDK_EXPORT_UE static String GetInstanceID(const String &channel) MSDK_DEPRECATED("deprecated from V5.16, use getInstanceIDAsync instead in MSDKExtend module");

};

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDK_REPORT_HPP */
