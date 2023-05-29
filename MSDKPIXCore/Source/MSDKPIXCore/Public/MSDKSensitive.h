///*
/*!
 * @Header MSDKSensitive.h
 * @Author MikeFu
 * @Version 1.0.0
 * @Date 2021/9/9
 * @Abstract 文件功能的声明
 *
 * @Module iTOP
 *
 */

#ifndef MSDKSensitive_h
#define MSDKSensitive_h

#include <stdio.h>
#include "MSDKDefine.h"

#define MSDK_ANDORID_ID_KEY         "AndroidID"
#define MSDK_WIFI_MAC_ADDRESS_KEY   "WiFiMacAddress"
#define MSDK_IMEI_KEY               "Imei"
#define MSDK_APN_KEY                "Apn"


NS_MSDK_BEGIN

class MSDK_EXPORT MSDKSensitive
{
public:
    // 设置是否允许收集敏感信息总开关
    MSDK_EXPORT_UE static void SetCouldCollectSensitiveInfo(bool couldCollect);
    // 以json形式设置敏感信息字段至各个组件SDK，目前支持{"AndroidID":"xxx","WiFiMacAddress":"xxx","Imei":"xxx"}
    MSDK_EXPORT_UE static void SetSensitiveInfo(const String &jsonInfo);
    // 以json形式设置敏感信息单字段开关，优先级小于总开关，目前支持设置AndroidID、Apn、Imei，参数示例{"AndroidID":true,"Apn":true,"Imei":false}
    MSDK_EXPORT_UE static void SetCollectSensitiveInfo(const String &jsonInfo);
};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

class MSDK_EXPORT MSDKSensitive
{
public:
    // 设置是否允许收集敏感信息总开关
    MSDK_EXPORT_UE static void SetCouldCollectSensitiveInfo(bool couldCollect);
    // 以json形式设置敏感信息字段至各个组件SDK，目前支持{"AndroidID":"xxx","WiFiMacAddress":"xxx","Imei":"xxx"}
    MSDK_EXPORT_UE static void SetSensitiveInfo(const String &jsonInfo);
    // 以json形式设置敏感信息单字段开关，优先级小于总开关，目前支持设置AndroidID、APN、Imei，参数示例{"AndroidID":true,"Apn":true,"Imei":false}
    MSDK_EXPORT_UE static void SetCollectSensitiveInfo(const String &jsonInfo);
};

NS_MSDK_SPACE_NO_STL_END

#endif /* MSDKSensitive_h */
