//
//  Copyright © 2022-2023 MSDK team. All rights reserved.
//

#ifndef MSDK_MACROS_H
#define MSDK_MACROS_H


#include <set>
#include <map>
#include <list>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <cwchar>
#include <iostream>

#ifdef _WIN32
#define MSDK_DEPRECATED(_version)
#else
#define MSDK_DEPRECATED(_version) __attribute__((deprecated(_version)))
#endif


// 匿名化SDK开关
#define MSDK_ANONYMOUS 0

#ifdef __cplusplus
#define NS_MSDK_BEGIN namespace GCloud \
        {\
            namespace MSDK \
            {
#define NS_MSDK_END }}
#define USING_NS_MSDK using namespace GCloud::MSDK;
#else
#define NS_MSDK_BEGIN
    #define NS_MSDK_END
    #define USING_NS_MSDK
#endif


#ifdef __cplusplus
#define NS_MSDK_SPACE_NO_STL_BEGIN namespace GCloud \
                {\
                    namespace MSDKSpace \
                    {\
                        namespace NoSTL \
                        {
#define NS_MSDK_SPACE_NO_STL_END }}}
#define USING_NS_MSDK_SPACE_NO_STL using namespace GCloud::MSDKSpace::NoSTL;
#else
#define NS_MSDK_SPACE_NO_STL_BEGIN
    #define NS_MSDK_SPACE_NO_STL_END
    #define USING_NS_MSDK_SPACE_NO_STL
#endif


#define MSDK_UUID_KEY_NAME "itop_uuid"
#define MSDK_CONFIG_DEFAULT_GAME_ID "11"
#define MSDK_SEQ_ID_PRIMARY_KEY_NAME "itop_seq_id_primary_key"


#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#if defined(GCLOUD_MSDK_WINDOWS)
#undef MSDK_PLATFORM_WINDOWS
    #define MSDK_PLATFORM_WINDOWS 1
#else
#undef MSDK_PLATFORM_WINDOWS
#define MSDK_PLATFORM_WINDOWS 0
#endif

#if defined(GCLOUD_MSDK_MAC)
#undef MSDK_PLATFORM_MAC
    #define MSDK_PLATFORM_MAC 1
#else
#undef MSDK_PLATFORM_MAC
#define MSDK_PLATFORM_MAC 0
#endif

//适配 UE4 以及 Cocos 系统定义
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_MAC) || defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID)
#undef  MSDK_ENGINE_UE4
    #define MSDK_ENGINE_UE4 1

    #if PLATFORM_WINDOWS || PLATFORM_MAC
        #if MSDK_PLATFORM_WINDOWS || MSDK_PLATFORM_MAC
            #define MSDK_ENGINE_UE4_SIMULATE_LOGIN 0
        #else
            #define MSDK_ENGINE_UE4_SIMULATE_LOGIN 1
        #endif
    #else
        #define MSDK_ENGINE_UE4_SIMULATE_LOGIN 0
    #endif

    #if PLATFORM_WINDOWS
        #define MSDK_ENGINE_UE4_PLATFORM_WINDOWS 1
    #else
        #define MSDK_ENGINE_UE4_PLATFORM_WINDOWS 0
    #endif

    #if PLATFORM_MAC
        #define MSDK_ENGINE_UE4_PLATFORM_MAC 1
    #else
        #define MSDK_ENGINE_UE4_PLATFORM_MAC 0
    #endif
#else
#undef  MSDK_ENGINE_UE4
#define MSDK_ENGINE_UE4 0
#define MSDK_ENGINE_UE4_SIMULATE_LOGIN 0
#define MSDK_ENGINE_UE4_PLATFORM_WINDOWS 0
#define MSDK_ENGINE_UE4_PLATFORM_MAC 0
#endif

////UE4 windows 游客登录需要做dll 函数导出的特殊处理
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    #if MSDK_ENGINE_UE4_PLATFORM_MAC
        #define MSDK_EXPORT_UE __attribute__ ((visibility ("default")))
    #else
        #ifdef MSDK_CORE
            #define MSDK_EXPORT_UE __declspec(dllexport)
        #else
            #define MSDK_EXPORT_UE __declspec(dllimport)
        #endif
    #endif

    #define MSDK_EXPORT
    #define MSDK_HIDDEN
#else
    #define MSDK_EXPORT_UE
    #if __GNUC__ >= 4
            #if defined(__APPLE__)
                #if MSDK_ENGINE_UE4
                    #ifndef MSDKPIXCORE_API
                        #define MSDK_EXPORT MSDKCORE_API
                        #define MSDK_HIDDEN MSDKCORE_API
                    #else
                        #define MSDK_EXPORT MSDKPIXCORE_API
                        #define MSDK_HIDDEN MSDKPIXCORE_API
                    #endif
                #else
                    #define MSDK_EXPORT
                    #define MSDK_HIDDEN
                #endif
            #else
                #define MSDK_EXPORT __attribute__ ((visibility ("default")))
                #define MSDK_HIDDEN  __attribute__ ((visibility ("hidden")))
            #endif
    #else
        #define MSDK_EXPORT
        #define MSDK_HIDDEN
    #endif
#endif


#if MSDK_PLATFORM_WINDOWS
#define MSDK_VERSION "5.30.100.2614"
#define MSDK_CUR_OS 5
#define HAVE_STRUCT_TIMESPEC 1
#else
#ifdef ANDROID
#define MSDK_VERSION "5.30.100.2614"
#define MSDK_CUR_OS 1
#define JNI_VERSION JNI_VERSION_1_4
#endif
#ifdef __APPLE__
#define MSDK_CUR_OS 2
        #define MSDK_VERSION "5.30.100.2614"
#endif
#endif


#define MINIMUM_JSON_LEN 2 // 最小的 json 串长度为 {}
#define EMPTY_STRING  ""
#define DEFAULT_GAME_ID "11"
#define CHANNEL_GUEST_ID 3
#define MSDK_TDM_SCRID 2003 // TDM scrID，渠道上报来源

#if MSDK_PLATFORM_WINDOWS
#define DEFAULT_REFRESH_INTERVAL 4*60 //自动刷新token，默认时间间隔
#else
#define DEFAULT_REFRESH_INTERVAL 30*60 //自动刷新token，默认时间间隔
#endif // MSDK_PLATFORM_WINDOWS

// ini 配置
#define LABEL_SDK_URL                       "MSDK_URL"
#define LABEL_GAME_ID                       "MSDK_GAME_ID"
#define LABEL_SDK_KEY                       "MSDK_SDK_KEY"
#define LABEL_MSDK_DEBUG                    "MSDK_DEBUG"
#define LABEL_DEBUG_CHANNEL                 "MSDK_DEBUG_CHANNEL"
#define LABEL_HTTP_TIMEOUT                  "MSDK_HTTP_TIMEOUT"
#define LABEL_LOGIN_OVERTIME                "MSDK_LOGIN_OVERTIME"
#define LABEL_HTTP_DNS                      "MSDK_HTTPDNS_ENABLE"
#define LABEL_IPV6_ENABLE                   "MSDK_IPV6_ENABLE"
#define LABEL_REFRESH_INTERVAL              "MSDK_REFRESH_INTERVAL"
#define LABEL_UPDATE_CONFIG_INTERVAL        "MSDK_UPDATE_CONFIG_INTERVAL"
#define LABEL_GCLOUD_REMOTE_CONFIG_ENABLE   "MSDK_GCLOUD_REMOTE_CONFIG_ENABLE"
#define LABEL_GCLOUD_LOG_ENABLE             "MSDK_GCLOUD_LOG_ENABLE"

#define LABEL_ACCOUNT_URL                   "MSDK_ACCOUNT_URL"
#define LABEL_ACCOUNT_SDK_KEY               "MSDK_ACCOUNT_SDK_KEY"
#define LABEL_ACCOUNT_APP_ID                "MSDK_ACCOUNT_APP_ID"

#define LABEL_ENCRYPT_STORAGE               "MSDK_ENCRYPT_STORAGE"
#define LABEL_DEVICE_INFO                   "MSDK_DEVICE_INFO"
#define LABEL_DEVICE_INFO_CONFIG            "MSDK_DEVICE_INFO_CONFIG"
#define LABEL_DEVICE_INFO_NOTICE            "MSDK_DEVICE_INFO_NOTICE"
#define LABEL_MIGRA_GUEST_FROMV3_ENABLE     "MSDK_MIGRA_GUEST_FROMV3_ENABLE"
#define LABEL_MIGRA_GUEST_FROM_ITOP1_ENABLE "MSDK_MIGRA_GUEST_FROM_ITOP1_ENABLE"

#define LABEL_UPDATE_USER_ID_LOGIN_LOGOUT   "CRASH_UPDATE_USER_ID"
#define LABEL_CRASH_REPORT_ENABLE           "CRASH_REPORT_ENABLE"
#define LABEL_CRASH_REPORT_CHANNEL          "CRASH_REPORT_CHANNEL"
#define LABEL_JSON_LOG_ENABLE               "MSDK_JSON_LOG_ENABLE"
#define LABEL_CONFIG_LOG_ENABLE             "MSDK_CONFIG_LOG_ENABLE"
#define LABEL_AUTOLOGIN_NOT_PLUGIN_CHANNEL  "MSDK_AUTOLOGIN_NOT_PLUGIN_CHANNEL"
#define LABEL_LIFECYCLE_SCHEME              "MSDK_LIFECYCLE_SCHEME"
#define LABEL_GUEST_FROM_SDCARD_ENABLE      "MSDK_GUEST_FROM_SDCARD_ENABLE"
#define LABEL_TDM_COLLECT_ENABLE            "TDM_COLLECT_ENABLE"


#ifdef __APPLE__
#define LABEL_KEYCHAIN_ENABLE               "MSDK_KEYCHAIN_ENABLE"
#endif

// 删除单个指针和删除多个指针
#define SAFE_DELETE(ptr) \
    do                   \
    {                    \
        if (ptr != NULL) \
        {                \
            delete ptr;  \
            ptr = NULL;  \
        }                \
    } while (0)

#define SAFE_DELETE_ARR(ptr) \
    do                       \
    {                        \
        if (ptr != NULL)     \
        {                    \
            delete[] ptr;    \
            ptr = NULL;      \
        }                    \
    } while (0)

// 分配内存和释放内存
#define SAFE_MALLOC(num, type) (type *) calloc((num) , sizeof(type))
#define SAFE_FREE(ptr)   \
    do                   \
    {                    \
        if (ptr != NULL) \
        {                \
            free(ptr);   \
            ptr = NULL;  \
        }                \
    } while (0)


#endif //MSDK_MACROS_H
