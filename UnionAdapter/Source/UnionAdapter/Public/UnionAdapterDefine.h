//
//  GUASDK.h
//  INTLSample
//
//  Created by weiqiangluo on 2022/5/10.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once
#include <string>
#include <vector>
#include <map>


#ifndef GUA_NAMESPACE  // GUA_NAMESPACE
#define GUA_NAMESPACE GUA
#define GUA_NAMESPACE_BEGIN namespace GUA_NAMESPACE {
#define GUA_NAMESPACE_END }
#endif

#if PLATFORM_WINDOWS || PLATFORM_PS4 || PLATFORM_XBOXONE
    #define GUA_EXTERN  __declspec(dllexport)
#elif __GNUC__ >= 4 // Android iOS Mac Switch
    #define GUA_EXTERN __attribute__ ((visibility ("default")))
#else
    #define GUA_EXTERN
#endif

// Target OS
#if defined(_WIN32) || defined(_WIN64)
    #ifdef _XBOX_ONE
        #define GUA_OS_XBOXONE 1
    #else
        #define GUA_OS_WINDOWS 1
    #endif
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IOS || TARGET_OS_IPHONE
        #define GUA_OS_IOS 1
    #else
        #define GUA_OS_MAC 1
    #endif
#elif defined(__ORBIS__)
    #define GUA_OS_PS4 1
#elif defined(__PROSPERO__)
    #define GUA_OS_PS5 1
#elif defined(NN_BUILD_TARGET_PLATFORM_NX)
    #define GUA_OS_SWITCH 1
#elif defined(ANDROID)
    #define GUA_OS_ANDROID 1
#endif

#if !defined(GUA_OS_WINDOWS)
#define GUA_OS_WINDOWS 0
#endif

#if !defined(GUA_OS_MAC)
#define GUA_OS_MAC 0
#endif

#if !defined(GUA_OS_XBOXONE)
#define GUA_OS_XBOXONE 0
#endif

#if !defined(GUA_OS_PS4)
#define GUA_OS_PS4 0
#endif

#if !defined(GUA_OS_PS5)
#define GUA_OS_PS5 0
#endif

#if !defined(GUA_OS_SWITCH)
#define GUA_OS_SWITCH 0
#endif

#if !defined(GUA_OS_IOS)
#define GUA_OS_IOS 0
#endif

#if !defined(GUA_OS_ANDROID)
#define GUA_OS_ANDROID 0
#endif

// Game Engine
#if PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_IOS || PLATFORM_ANDROID || PLATFORM_XBOXONE || PLATFORM_PS4 || PLATFORM_SWITCH
#define GUA_GAME_ENGINE_UE 1
#else
#define GUA_GAME_ENGINE_UE 0
#endif

#define GUA_DEFAULT_JSON_STRING "{}"
#define GUA_DEFAULT_EMPTY_STRING ""

#define GUA_CHANNEL_INTL			"INTL"
#define GUA_CHANNEL_GUEST			"Guest"
#define GUA_CHANNEL_CUSTOM_ACCOUNT	"CustomAccount"
#define GUA_CHANNEL_FACEBOOK		 "Facebook"
#define GUA_CHANNEL_GAME_CENTER		 "GameCenter"
#define GUA_CHANNEL_GOOGLE			 "Google"
#define GUA_CHANNEL_APPLE			 "Apple"
#define GUA_CHANNEL_LINE			"Line"
#define GUA_CHANNEL_TWITTER			 "Twitter"
#define GUA_CHANNEL_PLAYFAB			 "PlayFab"
#define GUA_CHANNEL_FIRBASE			 "Firebase"
#define GUA_CHANNEL_ADJUST			 "Adjust"
#define GUA_CHANNEL_APPSFLYER		 "AppsFlyer"
#define GUA_CHANNEL_BUGLY			 "Bugly"
#define GUA_CHANNEL_GARENA			 "Garena"
#define GUA_CHANNEL_SYSTEM			 "System"
#define GUA_CHANNEL_STEAM			 "Steam"
#define GUA_CHANNEL_EPIC			 "Epic"
#define GUA_CHANNEL_IEG_PASSPORT	 "IEGPassport"
#define GUA_CHANNEL_EGAME			"EGame"
#define GUA_CHANNEL_VK				"VK"
#define GUA_CHANNEL_GAME_FRIENDS	 "GameFriends"
#define GUA_CHANNEL_BEE_TALK		 "BeeTalk"
#define GUA_CHANNEL_QQ				 "QQ"
#define GUA_CHANNEL_WECHAT			 "WeChat"
#define GUA_CHANNEL_DMM				 "Dmm"
#define GUA_CHANNEL_DISCORD			 "Discord"
#define GUA_CHANNEL_SQUARE_ENIX		 "SquareEnix"
#define GUA_CHANNEL_SUPERCELL		 "Supercell"

GUA_NAMESPACE_BEGIN

typedef enum GUA_EXTERN GUAMethodID
{
    kMethodIDUndefine                 = 00000,

    kMethodIDAccountAutoLogin                = 10101,
    kMethodIDAccountLogin                    = 10102,
    kMethodIDAccountBind                     = 10103,
    kMethodIDAccountGetLoginRet              = 10104,
    kMethodIDAccountSwitchUser               = 10105,
    kMethodIDAccountQueryUserInfo            = 10106,
    kMethodIDAccountLogout                   = 10107,
    kMethodIDAccountLoginWithConfirmCode     = 10108,
    kMethodIDAccountWakeUp                   = 10109,
    KMethodIDAccountScheme                   = 10110,
    kMethodIDAccountResetGuest               = 10111,
    kMethodIDAccountQueryCanBind             = 10112,
    kMethodIDAccountQueryActiveUser                     = 10113,
    kMethodIDAccountShowAccountPicker                   = 10114,
    kMethodIDAccountCheckActiveUser                     = 10115,
    kMethodIDAccountNeedRefreshUser                     = 10116,
    kMethodIDAccountRequestVerifyCode                   = 10117,
    kMethodIDAccountResetPassword                       = 10118,
    kMethodIDAccountModifyAccount                       = 10119,
    kMethodIDAccountLoginWithCode                       = 10120,
    kMethodIDAccountQueryRegisterStatus                 = 10121,
    kMethodIDAccountQueryVerifyCodeStatus               = 10122,
    kMethodIDAccountQueryIsReceiveEmail                 = 10123,
    kMethodIDAccountRegister                            = 10124,
    kMethodIDAccountModifyProfile                       = 10125,
    kMethodIDAccountLoginWithMappedChannel              = 10128,
    kMethodIDAccountBuildMapWithLoginChannel            = 10129,
    kMethodIDAccountQueryTokenID                        = 10130,
    kMethodIDAccountUnbind                              = 10132,
    kMethodIDAccountQueryUserNameStatus                 = 10133,
    kMethodIDAccountQueryDataProtectionAcceptance       = 10134,
    kMethodIDAccountModifyDataProtectionAcceptance      = 10135,
    kMethodIDAccountQueryAccountProfile                 = 10136,
    kMethodIDAccountLaunchAccountUI                     = 10137,
    kMethodIDAccountQueryLegalDocuments                 = 10138,
    kMethodIDAccountModifyLegalDocuments                = 10139,
    kMethodIDAccountQueryBindInfo                       = 10140,
    kMethodIDAccountConnect                             = 10141,
    kMethodIDAccountUnconnect                           = 10142,
    kMethodIDAccountGetConnectResult                    = 10143,
    kMethodIDAccountBindUI                              = 10144, 
    KMethodIDAccountRefreshToken                        = 10145,
    kMethodIDAccountQRCode                              = 10146, 
    kMethodIDAccountCheckUL                             = 10147, 
    kMethodIDAccountCheckAndLogin                       = 10148, 
    kMethodIDAccountCheck                               = 10149,
    kMethodIDAccountBindWithConfirmCode                 = 10150,
    kMethodIDAccountPermissionAuth                      = 10151,
    kMethodIDAccountChannelPermissionAuth               = 10152,
	kMethodIDAccountCanBind								= 10153,
	kMethodIDAccountCancelAccountDeletion				= 10154,
    kMethodIDAccountGenerateTransferCode                = 10155,
    kMethodIDAccountQueryTransferCode                   = 10156,
    kMethodIDAccountTransferAccount                     = 10157,
    kMethodIDAccountRevokeChannelToken                  = 10158,

    kMethodIDFriendShare              = 10201,
    kMethodIDFriendSendMessage        = 10202,
    kMethodIDFriendQueryFriends       = 10203,
    kMethodIDFriendAddFriend          = 10204,
    
    kMethodIDWebviewCloseURL          = 10301,
    kMethodIDWebviewGetEncryptUR      = 10302,
    kMethodIDWebviewJSCall            = 10303,
    kMethodIDWebviewJSShare           = 10304,
    kMethodIDWebviewJSSendMessage     = 10305,
    kMethodIDWebviewJSIsAppInstalled  = 10306,
    kMethodIDWebviewToolbarShare      = 10307,
    KMethodIDWebviewEmbeddedProgress  = 10308,
    
    kMethodIDPushRegister             = 10401,
    kMethodIDPushUnregister           = 10402,
    kMethodIDPushSetTag               = 10403,
    kMethodIDPushDeleteTag            = 10404,
    kMethodIDPushAddLocalNotification       = 10405,
    kMethodIDPushClearLocalNotification     = 10406,
    kMethodIDPushNotificationCallback       = 10407,
    kMethodIDPushNotificationShow           = 10408,
    kMethodIDPushNotificationClick          = 10409,
    kMethodIDPushSetAccount                 = 10410,
    kMethodIDPushDeleteAccount              = 10411,
    
    kMethodIDNoticeRequestData              = 10501,
    
    kMethodIDToolsOpenDeepLink              = 10601,
    kMethodIDToolsConvertShortURL           = 10602,
    kMethodIDToolsCutoutInfo                = 10603,
    kMethodIDToolsFreeFlow                  = 10604,
    kMethodIDToolsRecoverGuest              = 10605,
    kMethodIDToolsDetectNetwork             = 10606,
    kMethodIDToolsDNSQueryIPByHost          = 10607,
    
    kMethodIDAnalyticsCrashExtraMessage     = 10701,
    kMethodIDAnalyticsQueryDeviceLevel      = 10702,
    kMethodIDAnalyticsCrashExtraData        = 10703,
    
    kMethodIDExtendInvoke                   = 11301
}GUAMethodID;

class GUA_EXTERN GUABaseResult {
public:

    // flag for entry function
    int32_t method_id = 0;

    // return code, refer to intl_error.h for more details
    int32_t ret_code = -2;

    // return message
    std::string ret_msg;

    // return code for external sdk/platform, or server error
    int32_t third_code = -1;

    //  return message for external sdk/platform, or server error
    std::string third_msg;

    // reserve string ,json format
    std::string extra_json = GUA_DEFAULT_JSON_STRING;

    GUABaseResult(){}
};

class GUA_EXTERN UnionAdapter{
public:
    static void Init();
    static void Restart();
    static void UpdateSDK();
    static void ShutDown();
};

GUA_NAMESPACE_END
