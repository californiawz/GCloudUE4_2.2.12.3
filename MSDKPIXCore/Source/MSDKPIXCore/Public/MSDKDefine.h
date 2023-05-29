/*!
 * @Module MSDK
 *
 * @Header  MSDKPDefine.h
 * @Author  developer
 * @Date 2018/03/20
 * @Abstract
 * 1. 除了 MSDKBaseRet 是提供给外部使用到，所有 MSDK 库内部使用的结构体声明都在这里
 * 2. 内部统计打点的功能实现
 * 3. 回调管理中心
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_DEFINE_H
#define MSDK_DEFINE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <ostream>

#include "MSDKLog.h"
#include "MSDKError.h"
#include "MSDKMacros.h"
#include "MSDKSingleton.h"
#include "MSDKCompatLayer.h"


NS_MSDK_BEGIN


typedef enum MSDK_EXPORT MethodName
{
    kMethodNameUndefine                 = 000,
    kMethodNameMSDKInit                 = 101,

    kMethodNameAutoLogin                = 111,
    kMethodNameLogin                    = 112,
    kMethodNameBind                     = 113,
    kMethodNameGetLoginRet              = 114,
    kMethodNameSwitchUser               = 115,
    kMethodNameQueryUserInfo            = 116,
    kMethodNameLogout                   = 117,
    kMethodNameLoginWithConfirmCode     = 118,
    kMethodNameWakeUp                   = 119,
    KMethodNameScheme                   = 120,
    kMethodNameResetGuest               = 121,
    //MSDK_LOGIN_QRCODE = 122  Unity Editor/Windows 扫码登录占用
    kMethodNameLoginUI                  = 123,
    kMethodNameConnect                  = 124,
    kMethodNameUnConnect                = 125,
    kMethodNameGetConnectRet            = 126,
    kMethodNameBindUI                   = 127,
    kMethodNameCanBind                  = 128,
#if MSDK_PLATFORM_WINDOWS
	kMethodNameQrCode 					= 129,
	kMethodNameRefreshToken 			= 130,
#endif // MSDK_PLATFORM_WINDOWS
    kMethodNameCheckUniversalLink       = 131,
    
    kMethodNameCheckAndLogin             = 132, // A 模式
    kMethodNameCheck                     = 133, // B 模式
    kMethodNameBindWithConfirmCode       = 134, // B 模式
    kMethodNameConsoleRefreshToken       = 135, // GCLOUD_MSDK_CONSOLE，刷新Token接口
    kMethodNamePermissionAuth           = 136,
    kMethodNameChannelPermissionAuth     = 137,

    kMethodNameShareToWall              = 211,
    kMethodNameSendMessageToFriend      = 212,
    kMethodNameQueryFriend              = 213,
    kMethodNameAddFriend                = 214,

    kMethodNameCreateGroup              = 311,
    kMethodNameBindGroup                = 312,
    kMethodNameGetGroupList             = 313,
    kMethodNameGetGroupState            = 314,
    kMethodNameJoinGroup                = 315,
    kMethodNameUnbindGroup              = 316,
    kMethodNameRemindToBindGroup        = 317,
    kMethodNameSendMessageToGroup       = 318,
    kMethodNameGetGroupRelation         = 319,

    kMethodNameCloseWebViewURL          = 411,
    kMethodNameGetEncodeURL             = 412,
    kMethodNameWebViewJsCall            = 413,
    kMethodNameWebViewJsShare           = 414,
    kMethodNameWebViewJsSendMessage     = 415,
    kMethodNameWebViewEmbedProgress     = 416,


    kMethodNameRegisterPush             = 511,
    kMethodNameUnregisterPush           = 512,
    kMethodNameSetTagForPush            = 513,
    kMethodNameDeleteTagForPush         = 514,
    kMethodNameAddLocalNotify           = 515,
    kMethodNameClearLocalNotify         = 516,
    kMethodNameNotifyCallback           = 517,
    kMethodNameNotifyShow               = 518,
    kMethodNameNotifyClick              = 519,
    kMethodNameSetAccountPush           = 520,
    kMethodNameDeleteAccountPush        = 521,




    kMethodNameLoadNoticeData           = 611,

    kMethodNameSetupGame                = 711,
    kMethodNameShowGameLeaderBoard      = 712,
    kMethodNameSetScore                 = 713,
    kMethodNameShowGameAchievement      = 714,
    kMethodNameUnlockGameAchieve        = 715,
    
    KMethodNameToolsOpenDeepLink        = 911,
    KMethodNameToolsConvertShortUrl     = 912,
    KMethodNameToolsGetFreeFlowInfo     = 913,

    kMethodNameCrashExtraData           = 1011,
    kMethodNameCrashExtraMessage        = 1012,

    kMethodNameExtend                   = 1111,

    kMethodNameLBSGetLocation           = 1211,
    kMethodNameLBSClearLocation         = 1212,
    kMethodNameLBSGetNearby             = 1213,
    kMethodNameLBSGetIPInfo             = 1214,

    
    kMethodNameAccountVerifyCode        = 1311,
    kMethodNameAccountResetPassword     = 1312,
    kMethodNameAccountModify            = 1313,
    kMethodNameAccountLoginWithCode     = 1314,
    kMethodNameAccountGetRegisterStatus    = 1315,
    kMethodNameAccountGetVerifyCodeStatus = 1316,
    kMethodNameAccountGetReceiveEmail   = 1317,
    kMethodNameAccountVerifyPassword    = 1318,

}MethodName;


typedef enum ObserverID
{
    kObserverIDLoginRet               = 101,
    kObserverIDLoginBaseRet           = 102,
    kObserverIDRealName               = 106,
    kObserverIDWakeUp                 = 107,
    kObserverIDLogoutPlugin           = 108,
    kObserverIDLoginPlugin            = 109,
    kObserverIDConnectRet             = 110,
    kObserverIDCanBindRet             = 111,

#if MSDK_PLATFORM_WINDOWS
	kObserverIDQrCodeRet			  = 112,
	kObserverIDRefreshToken 		  = 113,
#endif // MSDK_PLATFORM_WINDOWS
    kObserverIDCheckAndLogin          = 114, //
    kObserverIDCheck                  = 115, //
    kObserverIDBindWithConfirmCode    = 116, //


    kObserverIDDeliverMessage         = 201,
    kObserverIDQueryFriend            = 202,

    kObserverIDGroupRet               = 301,

    kObserverIDWebViewRet             = 401,
    kObserverIDWebViewJsShare         = 402,
    kObserverIDWebViewToolBarShare    = 403,
    kObserverIDInnerShareCallback     = 404,    //use for android

    kObserverIDPushBaseRet            = 501,
    kObserverIDPushNotifyCallback     = 502,

    kObserverIDLoadNoticeData         = 601,

    kObserverIDGameBaseRet            = 701,
    kObserverIDSendModuleEvent        = 801,
    
    kObserverIDToolsRet               = 901,
    kObserverIDToolsFreeFlowRet       = 902,

    kObserverIDExtendRet              = 1101,

    kObserverIDLBSLocationRet         = 1201,
    kObserverIDLBSRelationRet         = 1202,
    kObserverIDLBSIPInfoRet           = 1203,
    kObserverIDLBSBaseRet             = 1204,
    kObserverIDLBSPluginSucRet        = 1205,

    kObserverIDAccountRet             = 1301,

}ObserverID;



class MSDK_EXPORT MSDKBaseRet
{
public:
    // 标记是从哪个方法过来
    int methodNameID;
    // MSDK 返回码，详情可参考 MSDKError.h
    int retCode;
    // MSDK 描述信息
    std::string retMsg;
    // 第三方渠道返回码
    int thirdCode;
    // 第三方渠道描述信息
    std::string thirdMsg;
    // 扩展字段，保留
    std::string extraJson;

    // 构造函数对外使用，必须包含在外部调用，否则会 crash
    MSDKBaseRet() : retCode(MSDKError::UNKNOWN), thirdCode(-1), thirdMsg("")
    {
        methodNameID = kMethodNameUndefine;
    }

    // 构造函数对外使用，必须包含在外部调用，否则会 crash
    MSDKBaseRet(int code) : retCode(code), thirdCode(-1), thirdMsg("")
    {
        methodNameID = kMethodNameUndefine;
    }

    // 构造函数对外使用，必须包含在外部调用，否则会 crash
    MSDKBaseRet(int code, int tCode, std::string tMsg)
            : retCode(code), thirdCode(tCode), thirdMsg(tMsg)
    {
        methodNameID = kMethodNameUndefine;
    }

	AutoParser("com.itop.gcloud.msdk.api.MSDKRet", A(thirdCode, "ret"), A(thirdMsg, "msg"),
           O(methodNameID, retCode, retMsg, extraJson));

};


/**
 * 基础结构类
 */
class MSDK_EXPORT InnerBaseRet
{
public:

    // 标记是从哪个方法过来
    int methodNameID;

    // MSDK 返回码，详情可参考 MSDKError.h
    int retCode;
    
    // MSDK 描述信息
    String retMsg;
    
    // 第三方渠道返回码
    int thirdCode;
    
    // 第三方渠道描述信息
    String thirdMsg;
    
    // 扩展字段，保留
    String extraJson;

    // 构造函数
	MSDK_EXPORT_UE InnerBaseRet();

    InnerBaseRet(int retCode);

    InnerBaseRet(int retCode, int methodID);

    InnerBaseRet(int retCode, int thirdCode, String thirdMsg);

    InnerBaseRet(int retCode, String retMsg, int thirdCode, String thirdMsg);

    AutoParser("com.itop.gcloud.msdk.api.MSDKRet", A(thirdCode, "ret"), A(thirdMsg, "msg"), O(methodNameID, retCode, retMsg, extraJson));


};


//typedef enum MSDKLoginScene
//{ // 1-自动登录, 2-定时检查登录, 3-刷新第三方登录态
//    kMSDKLoginSceneAuto = 1,
//    kMSDKLoginSceneTimeCheck = 2,
//    kMSDKLoginSceneWakeupWithToken = 3
//}MSDKLoginScene;

// v5.12 版本之后兼容 V3 的 scenes，中控需要使用次值
typedef enum MSDKLoginScene
{ // 1-自动登录, 2-定时检查登录, 3-刷新第三方登录态
    kMSDKLoginSceneLogin = 1,
    kMSDKLoginSceneAuto = 2,
    kMSDKLoginSceneTimeCheck = 3,
    kMSDKLoginSceneWakeupWithToken = 4
}MSDKLoginScene;

#if MSDK_PLATFORM_WINDOWS
// PC 二维码结果类
class InnerQrCodeRet : public InnerBaseRet
{
public:
	// 渠道ID
	int channelID;

	// 渠道名
	String channel;

	// 二维码信息
	String qrCodeUrl;

	// 构造函数
	InnerQrCodeRet() : InnerBaseRet()
	{
		channelID = 0;
	}

	InnerQrCodeRet(int retCode) : InnerBaseRet(retCode)
	{
		channelID = 0;
	}
};
#endif // MSDK_PLATFORM_WINDOWS


// MSDK 登录结果类
class InnerLoginRet : public InnerBaseRet
{

public:
    // 用户 ID
    String openID;

    // 用户 凭证
    String token;

    // 过期时间
    int64_t tokenExpire;

    // 是否首次登陆，未知-1，否0，是1
    int firstLogin;

    // 首次注册的分发渠道
    String regChannelDis;

    // 昵称
    String userName;

    // 性别(int) 0未定义,1男, 2女
    int gender;

    // 出生日期(1987-2-23 11:33:33)
    String birthdate;

    // 头像链接
    String pictureUrl;

    // pf 值
    String pf;

    // pf key
    String pfKey;

    // 是否需要实名认证
    bool realNameAuth;

    // 渠道ID
    int channelID;

    // 渠道名
    String channel;

    // 额外的渠道信息
    String channelInfo;
    
    // 确认码，绑定失败后返回
    String confirmCode;
    
    // 确认码过期时间戳
    int64_t confirmCodeExpireTime;
    
    //绑定信息(JSON 数据，数组类型)
    String bindList;
    
    //-- 以下字段仅限内部使用 --//
    // 第三方用户 ID(实名认证需要用，不在 MSDKLoginRet 中对外暴露)
    String channelOpenID;
    
    // 健康安平中心字段
    String healthGameExt;
    
    // 后台 seq 字段
    String seqID;

    // 构造函数
    InnerLoginRet(): InnerBaseRet()
    {
        tokenExpire = 0;
        gender = 0;
        firstLogin = 0;
        channelID = 0;
        confirmCodeExpireTime = 0;
        realNameAuth = false;
        confirmCodeExpireTime = 0;
    }

    InnerLoginRet(int retCode) : InnerBaseRet(retCode)
    {
        tokenExpire = 0;
        gender = 0;
        firstLogin = 0;
        channelID = 0;
        confirmCodeExpireTime = 0;
        realNameAuth = false;
        confirmCodeExpireTime = 0;
    }


    void resetLoginRet(){
        MSDKPIX_LOG_DEBUG("", "reset login result");
        confirmCodeExpireTime = 0;
        openID = "";
        token = "";
        tokenExpire = -1;
        firstLogin = -1;
        regChannelDis = "";
        userName = "";
        gender = 0;
        birthdate = "";
        pictureUrl = "";
        pf = "";
        pfKey = "";
        realNameAuth = false;
        confirmCodeExpireTime = 0;
        channelID = -1;
        channel = "";
        channelInfo = "";
        channelOpenID = "";
        healthGameExt = "";
        seqID = "";
        methodNameID = -1;
        retCode = 1; // MSDKError::NO_ASSIGN == 1 没有赋值
        retMsg = "";
        thirdCode = -1;
        thirdMsg = "";
        extraJson = "";
    }

    AutoParser("com.itop.gcloud.msdk.api.login.MSDKLoginRet",
               A(thirdCode, "ret"), A(thirdMsg, "msg"),
               A(openID, "openid"), A(tokenExpire, "token_expire_time"),
               A(firstLogin, "first"), A(regChannelDis, "reg_channel_dis"), A(userName, "user_name"),
               A(pictureUrl, "picture_url"), A(realNameAuth, "need_name_auth"),A(channelInfo, "channel_info"),
               A(channelOpenID, "uid"), A(healthGameExt, "health_game_ext"), A(seqID, "seq"), A(pfKey, "pf_key"), A(bindList, "bind_list"),
               A(confirmCode,"confirm_code"), A(confirmCodeExpireTime, "confirm_code_expire_time"), A(channelID, "channelid"),
               O(retCode, retMsg, extraJson, token, gender, birthdate, pf, pfKey, channelID, channel, methodNameID));

};


class InnerConnectRet : public InnerLoginRet
{
public:
    // 主账号的openid
    String mainOpenID;

    InnerConnectRet() : InnerLoginRet() {}

    InnerConnectRet(int retCode) : InnerLoginRet(retCode) {}

    InnerConnectRet(const InnerLoginRet &loginRet)
    {
        copy(loginRet);
    }

    void copy(const InnerLoginRet &loginRet)
    {
        thirdCode = loginRet.thirdCode;
        thirdMsg = loginRet.thirdMsg;
        methodNameID = loginRet.methodNameID;
        retCode = loginRet.retCode;
        retMsg = loginRet.retMsg;
        extraJson = loginRet.extraJson;

        openID = loginRet.openID;
        token = loginRet.token;
        tokenExpire = loginRet.tokenExpire;
        firstLogin = loginRet.firstLogin;
        regChannelDis = loginRet.regChannelDis;
        userName = loginRet.userName;
        gender = loginRet.gender;
        birthdate = loginRet.birthdate;
        pictureUrl = loginRet.pictureUrl;
        pf = loginRet.pf;
        pfKey = loginRet.pfKey;
        realNameAuth = loginRet.realNameAuth;
        channelID = loginRet.channelID;
        channel = loginRet.channel;
        channelInfo = loginRet.channelInfo;
        confirmCode = loginRet.confirmCode;
        confirmCodeExpireTime = loginRet.confirmCodeExpireTime;
        bindList = loginRet.bindList;
        channelOpenID = loginRet.channelOpenID;
        healthGameExt = loginRet.healthGameExt;
        seqID = loginRet.seqID;
    }


    void resetConnectRet()
    {
        MSDKPIX_LOG_DEBUG("", "reset connect result");
        resetLoginRet();
        mainOpenID = "";
    }
	

	AutoParser("com.itop.gcloud.msdk.api.login.MSDKConnectRet",
           A(thirdCode, "ret"), A(thirdMsg, "msg"),
           A(openID, "openid"), A(tokenExpire, "token_expire_time"),
           A(firstLogin, "first"), A(regChannelDis, "reg_channel_dis"), A(userName, "user_name"),
           A(pictureUrl, "picture_url"), A(realNameAuth, "need_name_auth"),A(channelInfo, "channel_info"),
           A(channelOpenID, "uid"), A(healthGameExt, "health_game_ext"), A(seqID, "seq"), A(pfKey, "pf_key"), A(bindList, "bind_list"),
           A(confirmCode,"confirm_code"), A(confirmCodeExpireTime, "confirm_code_expire_time"), A(channelID, "channelid"),
           O(retCode, retMsg, extraJson, token, gender, birthdate, pf, pfKey, channelID, channel, methodNameID, mainOpenID));

};

// 插件成功登录or异账号，回调参数
class InnerLoginPluginRet
{
public:

    // 【必填】方法ID，
    int methodNameID;

    // 【必填】渠道 ID
    int channelID;

    // 【必填】渠道名
    std::string channel;

    // 【必填】后台协议 channel_info 节点数据。
    std::string pluginData;

    // [选填] 渠道用户openID，异账号处理时必填
    std::string channelOpenID;

    // [不用填] 登录请求携带 seqID，插件登录忽略此字段
    std::string seqID;

    // 扩展字段，保留
    std::string extraJson;

    InnerLoginPluginRet();

    InnerLoginPluginRet(const InnerLoginPluginRet &ret, std::string seqID);


    AutoParser("com.itop.gcloud.msdk.api.login.MSDKLoginPluginInfo", O(methodNameID, channelID, channel,
        pluginData, channelOpenID, seqID, extraJson));

};

class MSDKFriendReqInfo
{
public:
    /**必选，类型：后台静默或者是拉起应用*/
    int type;

    /**用户，可以是 id 或者是 openid，比如静默分享时需要指定分享给指定的用户*/
    String user;

    /**必填，标题*/
    String title;

    /**选填，概述，简单描述分享内容*/
    String desc;

    /**选填，图片， 可以是本地地址或者是URL，建议使用本地地址*/
    String imagePath;

    /**选填，缩略图，一般就是游戏的 icon，可以是 icon 的本地地址或者是icon URL，建议使用本地地址*/
    String thumbPath;

    /**选填，多媒体地址（音乐或者视频源），本地地址，只支持本地地址*/
    /**分享至视频号必填，多媒体地址（音乐或者视频源），iOS填视频资源PHAsset localIdentifier，Android填视频资源本地路径*/
    /**分享至视频号视频规格：尺寸在1:3-3:1，size不能超过450M，时长不超过30分钟*/
    String mediaPath;

    /**选填，分享链接，可以是图片链接、音乐链接、视频链接或者跳转链接等等*/
    String link;

    /** 选填，扩展字段*/
    String extraJson;

    MSDKFriendReqInfo() : type(-1) {}

    String toString();

AutoParser("com.itop.gcloud.msdk.api.friend.MSDKFriendReqInfo",
           O(type, title, desc, user, imagePath, thumbPath, mediaPath, link, extraJson));

};

class InnerPersonInfo
{
public:
    String openid;      // 用户标识
    String userName;   // 昵称
    int gender;         // 性别1男2女,用户未填则默认0
    String pictureUrl; //
    String country;     // 国家
    String province;     // 省份
    String city;        // 城市
    String language;    // 语言

AutoParser("com.itop.gcloud.msdk.api.friend.MSDKPersonInfo",
           A(pictureUrl, "picture_url"), A(userName, "user_name"),
           O(openid, language, country, province, city, gender));

};

class InnerFriendRet : public InnerBaseRet
{
public:
    InnerFriendRet();


    InnerFriendRet(int code) ;

    Vector<InnerPersonInfo> friendInfoList;

    String extra;

AutoParser("com.itop.gcloud.msdk.api.friend.MSDKFriendRet",
           A(friendInfoList, "lists"), A(extra, "extinfo"),
           A(thirdCode, "ret"), A(thirdMsg, "msg"),
           A(extraJson, "extra"),
           O(retCode, retMsg, methodNameID));

};



class InnerWebViewReqInfo
{
public:
    InnerWebViewReqInfo();

    /**必填，网页地址*/
    String url;

    /**选填，屏幕方向 1 默认 2 竖屏 3 横屏*/
    int screenType;

    /**选填，是否用浏览器打开，默认为 false*/
    bool isBrowser;

    /**是否全屏*/
    bool isFullScreen;

    /**是否使用默认携带 URL encode 参数*/
    bool isUseURLEncode;

    /**选填，json 扩展参数*/
    String extraJson;

AutoParser("com.itop.gcloud.msdk.api.webview.MSDKWebViewReqInfo",
           O(url, screenType, isBrowser, isFullScreen, extraJson, isUseURLEncode));


};

class InnerWebViewRet : public InnerBaseRet
{
public:

    /** 100：关闭, 101:js 调用Native, 102：js 调用friend 接口 */
    int msgType;
    
    /** js 调用 native 时，携带的数据*/
    String msgJsonData;
    
    /** 嵌入式浏览器的加载进度 */
    float embedProgress;

    /** 嵌入式浏览器加载进度对应的 URL*/
    String embedUrl;
    
    InnerWebViewRet();
    InnerWebViewRet(int code);

AutoParser("com.itop.gcloud.msdk.api.webview.MSDKWebViewRet",
           A(thirdCode, "ret"),
           A(thirdMsg, "msg"),
           A(extraJson, "extra"),
           O(retCode, retMsg, methodNameID, msgType, msgJsonData, embedProgress, embedUrl));

};

class InnerCrashRet : public InnerBaseRet
{
public:
    char *data;
    int maxDataLen;
    int *dataLen;
    InnerCrashRet();

    AutoParser("com.itop.gcloud.msdk.api.crash.MSDKCrashRet",
               A(thirdCode, "ret"), A(thirdMsg, "msg"),
               A(extraJson, "extra"), O(retCode, retMsg, methodNameID),
               O(methodNameID));

};


typedef enum GroupHandleType
{
    kGroupHandleTypeInPlugin,
    kGroupHandleTypeInCoreKit,
} GroupHandleType;


class InnerGroupInfo
{
public:
    /**必填，群 id*/
    String groupID;
    /**必填，群名称*/
    String groupName;
    /**选填，扩展字段*/
    String extraJson;

AutoParser("com.itop.gcloud.msdk.api.group.MSDKGroupInfo", A(groupID, "groupid"),
           A(groupName, "group_name"), O(extraJson))

};

class InnerGroupRet : public InnerBaseRet
{
public:
    /**
     * 1、查询群用户和群的关
     */
    int status;

    /**工会ID*/
    String groupID;

    /**工会名称*/
    String groupName;

    /**拉取群信息需要用的，用于发送群消息*/
    String groupOpenID;
    
    /**选填，获取会长建群列表时*/
    Vector<InnerGroupInfo> groupInfo;

    InnerGroupRet();

    InnerGroupRet(int retCode);

    InnerGroupRet(int retCode, int thirdCode, String thirdMsg);

    AutoParser("com.itop.gcloud.msdk.api.group.MSDKGroupRet",
            A(groupInfo, "group_list"), A(retCode,"ret"), A(retMsg,"msg"), A(groupID,"groupid"), A(groupName,"group_name"),
            O(status, thirdMsg, thirdCode, extraJson, methodNameID, groupOpenID));


};

class InnerUnionInfo
{
public:
    /**必填，公会 id*/
    String unionID;
    /**选填，公会名称*/
    String unionName;
    /**选填，区服 id*/
    String zoneID;
    /**选填，用户区服 id，会长可能转让给非本区服的人，所以公会区服不一定是用户区服。与公会区服一样时可不填 */
    String userZoneID;
    /**选填，角色 id*/
    String roleID;
    /**选填，角色名称，作为群昵称显示*/
    String roleName;
    /**选填，公会会长的 openid*/
    String leaderID;
    /**选填，公会会长的角色 id */
    String leaderRoleID;
    /**选填，会长区服信息,会长可能转让给非本区服的人，与公会区服一样时可不填。 id */
    String leaderZoneID;
    /**选填，0公会(或不填),1队伍，2赛事 */
    String type;
    /**选填，测试环境使用：游戏大区ID，但是测试环境有很多虚拟的 */
    String areaID;
    /**选填，小区服 id，暂时无用*/
    String partitionID;
    /**选填，（新增，可以不填）新增修改群名片功能，全不填为不修改群名片；任一有内容为需要修改；样式规则：【YYYY】ZZZZ,ZZZZ指用户的游戏内昵称*/
    String userLabel;
    /**选填，玩家昵称*/
    String nickName;
    /**选填，扩展字段*/
    String extraJson;

    AutoParser("com.itop.gcloud.msdk.api.group.MSDKUnionInfo",
               O(unionID, unionName, zoneID, userZoneID, roleID, roleName, leaderID, leaderRoleID, leaderZoneID, type, areaID, partitionID, nickName, userLabel, extraJson));

};


class InnerNoticePictureInfo
{
public:
    String noticePicUrl;
    String noticePicHashcode;
    String noticePicTitle;
    String noticePicSize;
    int screenDir; //0-未知 1-竖向 2-横向


AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticePictureInfo", A(noticePicUrl, "pic_url"),
           A(noticePicHashcode, "pic_hash"), A(noticePicTitle, "pic_title"),
           A(noticePicSize, "pic_size"), A(screenDir, "pic_dir"));

};


class InnerNoticeTextInfo
{
public:
    String noticeTitle;
    String noticeContent;
    String noticeRedirectUrl;

AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeTextInfo", A(noticeTitle, "notice_title"),
           A(noticeContent, "notice_content"), A(noticeRedirectUrl, "notice_redirect_url"));

};

class InnerNoticeInfo
{
public:
    int noticeID;
    int noticeType;//公告类型，1000~1999表示登录前公告;2000~2999表示登录后公告
    String noticeGroup; //公告分组，游戏自定义使用
    int beginTime;
    int endTime;
    int updateTime;
    int order;

    int contentType;//1-文本，2-图片，3-网页
    String language; //语言类型

    InnerNoticeTextInfo textInfo;
    Vector<InnerNoticePictureInfo> picUrlList;
    String webUrl;//网页公告链接
    String extraJson;

    InnerNoticeInfo();

AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeInfo", A(noticeID, "notice_id"),
           A(noticeType, "notice_type"), A(noticeGroup, "notice_group"),
           A(beginTime, "start_time"), A(endTime, "end_time"), A(updateTime, "update_time"),
           A(contentType, "content_type"), A(textInfo, "notice_text_obj"),
           A(picUrlList, "notice_pic_list"), A(webUrl, "notice_web_url"),
           A(extraJson, "extra_data"), O(order, language));

};

class InnerNoticeRet : public InnerBaseRet
{
public:
    String reqID;
    Vector<InnerNoticeInfo> noticeInfoList;

    InnerNoticeRet();

    InnerNoticeRet(int retCode, int thirdCode, String thirdMsg);

AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeRet", A(thirdCode, "ret"),
           A(thirdMsg, "msg"), A(noticeInfoList, "notice_list"),
           O(retCode, retMsg, methodNameID, extraJson, reqID));

};


// Config 模块结构体只有个内部使用，不需要定义对应的 InnerConfigRet 结构体
class MSDKConfigRet : public InnerBaseRet
{
public:
    MSDKConfigRet() {}
    std::string cfgVersion;//云控版本，用于调试
    std::string cfgSign;   //所有的 key value 对的 md5
    std::map<std::string, std::string> cfg;

AutoParser("com.itop.gcloud.msdk.api.config.MSDKConfigRet", A(thirdCode, "ret"),
           A(thirdMsg, "msg"), A(extraJson, "extra"), A(cfg, "conf"),
           A(cfgSign, "conf_sig"), A(cfgVersion, "conf_version"), O(retCode, retMsg));

};

#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
class InnerLocalNotification
{
public:
	int type;
	int actionType;
	int iconType;
	int lights;
	int ring;
	int vibrate;
	int styleID;
    int64_t builderID;
	String content;
	String customContent;
	String activity;
	String packageDownloadUrl;
	String packageName;
	String iconRes;
	String date;
	String hour;
	String intent;
	String min;
	String title;
	String url;
	String ringRaw;
	String smallIcon;
	MSDK_EXPORT_UE InnerLocalNotification();
};
#else
#ifdef __APPLE__
class InnerLocalNotification
{
public:
    /*!
     *  推送重复发送周期。 1-分钟，2-小时，3-天，4-星期，5-月，6-年，默认是0代表不重复。
     *  如果设置此属性, 那么调度池不会用完释放改推送！需要手动删除通知对象
     */
    int repeatType;
    /*!本地推送触发的时间*/
    int64_t fireTime;
    /** 角标 */
    int badge;
    /** 推送的内容 */
    String alertBody;
    /** 替换弹框的按钮文字内容（默认为"启动"）*/
    String alertAction;
    /** 自定义参数，可以用来标识推送和增加附加信息 */
    Vector<KVPair> userInfo;

    InnerLocalNotification();

AutoParser("com.itop.gcloud.msdk.api.push.MSDKLocalNotification", O(repeatType, fireTime,badge, alertBody,alertAction,userInfo));

} ;
#elif ANDROID

class MSDK_EXPORT InnerLocalNotification
{
public:
    int type;
    int actionType;
    int iconType;
    int lights;
    int ring;
    int vibrate;
    int styleID;
    int64_t builderID;
    String content;
    String customContent;
    String activity;
    String packageDownloadUrl;
    String packageName;
    String iconRes;
    String date;
    String hour;
    String intent;
    String min;
    String title;
    String url;
    String ringRaw;
    String smallIcon;

    InnerLocalNotification();

AutoParser("com.itop.gcloud.msdk.api.push.MSDKLocalNotification",
           O(type, actionType, iconType, lights, ring, vibrate,
             styleID, builderID, content, customContent, activity,
             packageDownloadUrl, packageName, iconRes, date, hour,
             intent, min, title, url, ringRaw, smallIcon));
};

#endif

#endif


class InnerPushRet : public InnerBaseRet
{
public:
    InnerPushRet();

    InnerPushRet(int code);

    int type;
    String notification;

AutoParser("com.itop.gcloud.msdk.api.push.MSDKPushRet",
           A(thirdCode, "ret"), A(thirdMsg, "msg"),
           /*A(extraJson, "extra"),*/ A(type, "type"), A(notification, "notification"),
           O(retCode, retMsg, methodNameID,extraJson));

};

class InnerToolsRet : public InnerBaseRet
{
public:
    String link;
    
    // 构造函数
    InnerToolsRet() : InnerBaseRet(){};
    InnerToolsRet(int retcode) : InnerBaseRet(retcode){};

    AutoParser("com.itop.gcloud.msdk.api.tools.MSDKToolsRet",
            A(thirdCode, "ret"), A(thirdMsg, "msg"), A(link, "deeplink"),
            O(retCode, retMsg,methodNameID, extraJson));

};

class InnerToolsFreeFlowInfo
{
public:
    //全部免流IP列表
    String ipAll;
    //中国联通的免流IP列表
    String ipUnicom;
    //中国电信的免流IP列表
    String ipTelecom;
    //中国移动的免流IP列表
    String ipMobile;
    //其它运营商的免流IP列表
    String ipOther;
    //2: 解析之后的IP
    String ipConnect;
    //1:免流，0:不免
    int isFree;
    //1: 中国联通，2: 中国电信，3:中国移动，99:其它
    int ccType;
   
    InnerToolsFreeFlowInfo();

    AutoParser("com.itop.gcloud.msdk.api.tools.InnerToolsFreeFlowInfo",
        A(ipAll,"ip_all"),
        A(ipUnicom,"ip_cn_unicom"),
        A(ipTelecom,"ip_cn_telecom"),
        A(ipMobile,"ip_cn_mobile"),
        A(ipOther,"ip_other"),
        A(isFree,"is_free"),
        A(ccType,"cc_type"),
        O(ipConnect));

};

class InnerToolsFreeFlowRet : public InnerBaseRet
{
public:
    InnerToolsFreeFlowInfo freeFlowInfo;

    AutoParser("com.itop.gcloud.msdk.api.tools.InnerToolsFreeFlowRet",
        A(thirdCode, "ret"),
        A(thirdMsg, "msg"),
        A(extraJson, "extra"),
        A(freeFlowInfo, "freeflow_info"),
        O(retCode, retMsg,methodNameID));

    InnerToolsFreeFlowRet();
    InnerToolsFreeFlowRet(int retCode);
};

class InnerCanBindRet : public InnerBaseRet
{
public:
    // 标记是否可绑定
    bool canBind;
    // 标记是否在自建账号是否有 uid，据此选择注册还是登录自建账号
    bool isRegister;

    InnerCanBindRet() : InnerBaseRet()
    {
        canBind = false;
        isRegister = false;
    }
    InnerCanBindRet(int code) : InnerBaseRet(code)
    {
        canBind = false;
        isRegister = false;
    }


        AutoParser("com.itop.gcloud.msdk.api.login.MSDKCanBindRet",
                   A(thirdCode, "ret"),
                   A(thirdMsg, "msg"),
                   A(canBind, "can_bind"),
                   A(isRegister, "is_register"));


};

class InnerExtendRet : public InnerBaseRet
{
public:
    //标记使用哪个渠道的Extend功能
    String channel;
    //标记Extend插件中的方法名
    String extendMethodName;

    InnerExtendRet();
    InnerExtendRet(int code);

AutoParser("com.itop.gcloud.msdk.api.extend.MSDKExtendRet",
           A(thirdCode, "ret"),
           A(thirdMsg, "msg"),
           A(extraJson, "extra"),
           A(extendMethodName, "extend_method_name"),
           O(retCode, retMsg, methodNameID, channel));

};

// 插件返回位置信息
class InnerLBSLocationPluginRet
{
public:
    // 纬度
    double latitude;
    // 经度
    double longitude;

    String attribute;

    // 基站信息
    String cells;

    // WIFI 信息
    String wifis;

    String seqID;

    int methodNameID;

    String extraJson;

    InnerLBSLocationPluginRet(){}
    InnerLBSLocationPluginRet(int ID): methodNameID(ID){}

    AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSLocationPluginInfo",
               A(extraJson, "extraJson"),
               O(latitude, longitude, attribute, cells, wifis, seqID, methodNameID));

};

// 获取位置回调游戏信息
class InnerLBSLocationRet : public InnerBaseRet
{
public:
    // 纬度
    double latitude;
    // 经度
    double longitude;

    InnerLBSLocationRet(): InnerBaseRet(),latitude(0.0), longitude(0.0) {}
    InnerLBSLocationRet(int code): InnerBaseRet(code), latitude(0.0), longitude(0.0) {}
    InnerLBSLocationRet(int code, int methodID): InnerBaseRet(code, methodID), latitude(0.0), longitude(0.0) {}

AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSLocationRet",
           A(thirdCode, "ret"), A(thirdMsg, "msg"),
           O(longitude, latitude, retCode, retMsg, methodNameID, extraJson));

};

class InnerLBSPersonInfo : public InnerPersonInfo
{
public:
    // 该附近用户距离当前用户的距离
    double distance;
    // 是否为好友，-1 未知，0 否，1 是
    int isFriend;
    // 设置位置的时间戳
    int64_t timestamp;

    InnerLBSPersonInfo(){}

        AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSPersonInfo",
                   A(openid, "gopenid"),
                   A(pictureUrl, "figureurl"),
                   A(userName, "nickName"),
                   O(distance, isFriend, timestamp, language, country, province, city, gender));

};

class InnerLBSRelationRet : public InnerBaseRet
{
public:
    // 是否降级处理
    String isLost;

    // 附近的人列表
    Vector<InnerLBSPersonInfo> personList;

    InnerLBSRelationRet(): InnerBaseRet(){}
    InnerLBSRelationRet(int code): InnerBaseRet(code){}
    InnerLBSRelationRet(int code, int methodID): InnerBaseRet(code, methodID){}

        AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSRelationRet",
                   A(personList, "lists"), A(isLost, "is_lost"),
                   A(thirdCode, "ret"), A(thirdMsg, "msg"),
                   O(retCode, retMsg, methodNameID, extraJson));

};

class InnerLBSIPInfoRet : public InnerBaseRet
{
public:
    // 国家
    String country;
    int countryCode;

    // Province
    String province;
    int provinceCode;

    // City
    String city;
    int cityCode;

    // 时间戳
    int64_t  timestamp;

    // is_query_by_request_header
    bool isByHeader;

    InnerLBSIPInfoRet(): InnerBaseRet()
    {
        timestamp = 0;
        isByHeader = false;
    }
    InnerLBSIPInfoRet(int code): InnerBaseRet(code)
    {
        timestamp = 0;
        isByHeader = false;
    }
    InnerLBSIPInfoRet(int code, int methodID): InnerBaseRet(code, methodID)
    {
        timestamp = 0;
        isByHeader = false;
    }

AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSIPInfoRet",
           A(isByHeader, "is_query_by_request_header"),
           A(thirdCode, "ret"), A(thirdMsg, "msg"),
           A(countryCode, "country_no"), A(provinceCode, "province_no"), A(cityCode, "city_no"),
           O(country,province, city, timestamp, retCode, retMsg, methodNameID, extraJson));

};


class MSDKBaseParams
{
public:
    MethodName methodID;
    std::string seqID;
    std::string channel;
    std::string subChannel;
    std::string extraJson;
    static std::string createSequenceID();

public:
    MSDKBaseParams(): methodID(kMethodNameUndefine), seqID("") {}
    MSDKBaseParams(MethodName methodID, const std::string &seqID, std::string channel = "", std::string subChannel = "");
    MSDKBaseParams(MethodName methodID, const std::string &seqID, std::string channel, std::string subChannel, std::string extra);
    MSDKBaseParams(const MSDKBaseParams &params);
    ~MSDKBaseParams(){};

AutoParser("com.itop.gcloud.msdk.api.MSDKBaseParams",
        O(methodID, seqID, channel, subChannel, extraJson));


};

// 登录模块传参
class MSDKLoginParams : public MSDKBaseParams
{
public:
	std::string permissions;
#if MSDK_PLATFORM_WINDOWS
	std::string preCode;
	std::string channelOpenID;
#endif // MSDK_PLATFORM_WINDOWS

	MSDKLoginParams();
	MSDKLoginParams(const MSDKBaseParams &baseParams, const std::string permission);

	MSDKLoginParams *clone()
	{
		MSDKLoginParams *loginParams = new MSDKLoginParams();
		loginParams->seqID = seqID;
		loginParams->methodID = methodID;
		loginParams->channel = channel;
		loginParams->subChannel = subChannel;
		loginParams->extraJson = extraJson;
		loginParams->permissions = permissions;
#if MSDK_PLATFORM_WINDOWS
		loginParams->preCode = preCode;
		loginParams->channelOpenID = channelOpenID;
#endif // MSDK_PLATFORM_WINDOWS
		return loginParams;
	}

AutoParser("com.itop.gcloud.msdk.api.login.MSDKLoginParams",
           O(methodID, seqID, channel, subChannel, permissions, extraJson));

};

class MSDKAccountParams : public MSDKBaseParams
{
    public:
    std::string account;
    std::string password;
    std::string areaCode;
    std::string langType;
    int accountType;
    int accountPlatType;
    std::string accountModify;
    int accountTypeModify;
    std::string areaCodeModify;
    int verifyCodeModify;
    int verifyCode;
    int isNeedVerify;
    int codeType;
    int isRegister;
    int isSetPassword;
    int isReceiveEmail;
    int verifyCodeExpireTime;
    int verifyType;
    std::string oldPassword;

    MSDKAccountParams();

    MSDKAccountParams(MethodName methodID, const std::string &seqID, const std::string& channel, const std::string& extra);
    MSDKAccountParams(const MSDKAccountParams &params);
    MSDKAccountParams *clone()
    {
        MSDKAccountParams *accountParams = new MSDKAccountParams();
        accountParams->seqID = seqID;
        accountParams->methodID = methodID;
        accountParams->channel = channel;
        accountParams->account = account;
        accountParams->extraJson = extraJson;
        return accountParams;
    }

    AutoParser("com.itop.gcloud.msdk.api.account.MSDKAccountParams",
        O(methodID, seqID, channel, subChannel, extraJson, account, password, areaCode, langType, accountType, accountPlatType,
                accountModify, accountTypeModify, verifyCodeModify, verifyCode, isNeedVerify, isRegister, isSetPassword, isReceiveEmail, verifyCodeExpireTime,
                verifyType, oldPassword));

};


class InnerAccountRet : public InnerBaseRet
{
public:

        // 渠道ID
        int channelID;

        // 渠道名
        String channel;

        // 后台 seq 字段
        String seqID;

        String username;

        String uid;

        String token;

        String expiretime;

        int isRegister;

        int isSetPassword;

        int isReceiveEmail;

        int verifyCodeExpireTime;

        // 构造函数
        InnerAccountRet(): InnerBaseRet()
        {
            channelID = 0;
            isRegister = -1;
            isSetPassword = -1;
            isReceiveEmail = 0;
            verifyCodeExpireTime = 0;
        }

        InnerAccountRet(int retCode) : InnerBaseRet(retCode)
        {
            channelID = 0;
            isSetPassword = -1;
            isSetPassword = -1;
            isReceiveEmail = 0;
            verifyCodeExpireTime = 0;
        }

        InnerAccountRet(const InnerAccountRet &ret)
        {
            methodNameID = ret.methodNameID;
            retCode = ret.retCode;
            retMsg = ret.retMsg;
            thirdCode = ret.thirdCode;
            thirdMsg = ret.thirdMsg;
            extraJson = ret.extraJson;

            channelID = ret.channelID;
            channel = ret.channel;
            seqID = ret.seqID;
            username = ret.username;
            uid = ret.uid;
            token = ret.token;
            expiretime = ret.expiretime;
            isRegister = ret.isRegister;
            isSetPassword = ret.isSetPassword;
            isReceiveEmail = ret.isReceiveEmail;
            verifyCodeExpireTime = ret.verifyCodeExpireTime;
        }
    
        void resetAccountRet()
        {
            MSDKPIX_LOG_DEBUG("", "reset account result");
            username = "";
            channelID = 0;
            channel = "";
            seqID = "";
            methodNameID = kMethodNameUndefine;
            retCode = MSDKError::UNKNOWN;
            retMsg = "";
            thirdCode = -1;
            thirdMsg = "";
            extraJson = "";
            token = "";
            uid = "";
            expiretime = "";
            isRegister = -1;
            isSetPassword = -1;
            isReceiveEmail = 0;
            verifyCodeExpireTime = 0;
        }
    

        AutoParser("com.itop.gcloud.msdk.api.account.MSDKAccountRet",
            A(thirdCode, "ret"), A(thirdMsg, "msg"), A(username, "user_name"), A(seqID, "seq"), A(expiretime, "expire"),
            O(retCode, retMsg, channelID, channel, methodNameID, token, uid), A(isRegister, "is_register"), A(isSetPassword, "isset_pwd"), A(isReceiveEmail, "is_receive_email"),
            A(verifyCodeExpireTime, "expire_time"), A(extraJson, "retExtraJson"));

    };





template<typename RetType>
class T
{
public:
    typedef void (*InnerRetCallback)(const RetType &ret, const char *seqID);
};

template<typename RetType>
class MSDKCallBackParams
{
public:
    RetType mRet;
    unsigned int mObserverID;
    String mSeqID;
    MSDKCallBackParams(const RetType &ret, unsigned int observerID, String seqID): mRet(ret), mObserverID(observerID), mSeqID(seqID){};
};

void MSDKInnerObserverHolderDispatch(void (*callback)(int result, void *args), void *context);

template<typename RetType>
class MSDKInnerObserverHolder
{
private :
    static std::map<int, typename T<RetType>::InnerRetCallback> mObserverHolder;
    static std::map<std::string, MSDKCallBackParams<RetType> > mTaskParamsHolder;
    static void cacheTask(std::string mSeqID, MSDKCallBackParams<RetType> taskParams)
    {
        if (mSeqID.empty()){
            MSDKPIX_LOG_DEBUG(mSeqID.c_str(), "cacheTask failed for mSeqID is empty");
            return;
        }
        mTaskParamsHolder.insert(std::make_pair(mSeqID, taskParams));
        MSDKPIX_LOG_DEBUG(mSeqID.c_str(), "mTaskParamsHolder after insert");
    }
    static void commitCacheTask()
    {
        typename std::map<std::string, MSDKCallBackParams<RetType> >::iterator iter;
        for (iter = mTaskParamsHolder.begin(); iter != mTaskParamsHolder.end(); ){
            MSDKCallBackParams<RetType> taskParam = iter->second;
            if(CommitCacheToTaskQueue(taskParam.mRet, taskParam.mObserverID, taskParam.mSeqID)){
                mTaskParamsHolder.erase(iter++);
                MSDKPIX_LOG_DEBUG(taskParam.mSeqID.c_str(), "mTaskParamsHolder size: %lu, after erase", (unsigned long)mTaskParamsHolder.size());
            } else {
                ++iter;
            }
        }
        MSDKPIX_LOG_DEBUG("", "mTaskParamsHolder size: %lu, after commitCacheTask", (unsigned long)mTaskParamsHolder.size());
    }
public:
    static void CacheObserver(const unsigned int mObserverID, typename T<RetType>::InnerRetCallback observer)
    {
        if (mObserverHolder.find(mObserverID) != mObserverHolder.end())
        {
            // 如果已经存在就删除原来的 key，保证 key 对应的 value 是最新
            mObserverHolder.erase(mObserverID);
        }

        mObserverHolder.insert(std::make_pair(mObserverID, observer));
        commitCacheTask();
    }

    static void CommitToTaskQueueBackRet(const RetType &ret, const unsigned int observerID, const String &seqID)
    {
        if (mObserverHolder.find(observerID) != mObserverHolder.end())
        {
            mObserverHolder[observerID](ret, seqID.c_str());
        }
    }
    
    static void CommitToTaskQueue(const RetType &ret, const unsigned int observerID, const String &seqID)
    {
        MSDKCallBackParams<RetType> *params = new MSDKCallBackParams<RetType>(ret, observerID, seqID);
#if MSDK_PLATFORM_WINDOWS
		// windows平台直接回调
		MSDKPIX_LOG_DEBUG(seqID.c_str(), "CallbackOnMainThread observerID:%d", observerID);
		CallbackOnMainThread(-1, params);
#else
        if(mObserverHolder.find(params->mObserverID) == mObserverHolder.end()){ // 当前没有setObserver，缓存回调
            MSDKPIX_LOG_DEBUG(seqID.c_str(), "Cache ObserverID %d", observerID);
            MSDKCallBackParams<RetType> taskParams(params->mRet, params->mObserverID, params->mSeqID);
            cacheTask(params->mSeqID.toString(), taskParams);
            SAFE_DELETE(params);
        } else if (kObserverIDWakeUp == observerID){ //wakeup 回调直接回调
            MSDKPIX_LOG_DEBUG(seqID.c_str(), "CallbackOnMainThread %d", observerID);
            CallbackOnMainThread(-1, params);
        } else {
            MSDKPIX_LOG_DEBUG(seqID.c_str(), "DispatchAsyncMainThread %d", observerID);
            MSDKInnerObserverHolderDispatch(CallbackOnMainThread, params);
        }
#endif
    }
    static bool CommitCacheToTaskQueue(const RetType &ret, const unsigned int observerID, const String &seqID){
        MSDKCallBackParams<RetType> *params = new MSDKCallBackParams<RetType>(ret, observerID, seqID);
        if(mObserverHolder.find(params->mObserverID) != mObserverHolder.end()){
            MSDKPIX_LOG_DEBUG(seqID.c_str(), "DispatchAsyncMainThread %d", observerID);
            MSDKInnerObserverHolderDispatch(CallbackOnMainThread, params);
            return true;
        }
        SAFE_DELETE(params);
        return false;
    }


    static void CallbackOnMainThread(int ret, void *args)
    {
        MSDKCallBackParams<RetType> *params = (MSDKCallBackParams<RetType> *)args;
        
        if (mObserverHolder.find(params->mObserverID) != mObserverHolder.end())
        {
            MSDKPIX_LOG_DEBUG(params->mSeqID.c_str(), "observer address %p of observerID : %d", mObserverHolder[params->mObserverID], params->mObserverID);
            mObserverHolder[params->mObserverID](params->mRet, params->mSeqID.c_str());
        }
        else
        {
            MSDKPIX_LOG_DEBUG(params->mSeqID.c_str(), "can not get inner callback for %u, make sure you have define", params->mObserverID);
        }

        SAFE_DELETE(params);
    }

};

template<class RetType> std::map<int, typename T<RetType>::InnerRetCallback> MSDKInnerObserverHolder<RetType>::mObserverHolder;
template<class RetType> std::map<std::string, MSDKCallBackParams<RetType> > MSDKInnerObserverHolder<RetType>::mTaskParamsHolder;


#ifdef ANDROID

typedef void (*FuncRunOnUIDelegate)(void *args);

#endif



class MSDK_EXPORT TraceInfo
{
public:
    const char *seqID;      //每次调用的唯一标识
    const char *fileName;   //被跟踪的文件名
    const char *funcName;   //被跟踪的方法名
    int line;               //跟踪日志的行数
    long long tid;          //线程
    long long pid;          //进程
    const char *extraJson;  //扩展字段
};

inline std::ostream& operator << (std::ostream& os, String const& string) {
    os << (std::string)string;
    return os;
}

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

typedef enum MSDK_EXPORT MethodName
{
    kMethodNameUndefine                 = MSDK::kMethodNameUndefine,

    kMethodNameAutoLogin                = MSDK::kMethodNameAutoLogin,
    kMethodNameLogin                    = MSDK::kMethodNameLogin,
    kMethodNameBind                     = MSDK::kMethodNameBind,
    kMethodNameGetLoginRet              = MSDK::kMethodNameGetLoginRet,
    kMethodNameSwitchUser               = MSDK::kMethodNameSwitchUser,
    kMethodNameQueryUserInfo            = MSDK::kMethodNameQueryUserInfo,
    kMethodNameLogout                   = MSDK::kMethodNameLogout,
    kMethodNameLoginWithConfirmCode     = MSDK::kMethodNameLoginWithConfirmCode,
    kMethodNameWakeUp                   = MSDK::kMethodNameWakeUp,
    KMethodNameScheme                   = MSDK::KMethodNameScheme,
    kMethodNameResetGuest               = MSDK::kMethodNameResetGuest,
    //MSDK_LOGIN_QRCODE = 122  Unity Editor/Windows 扫码登录占用
    kMethodNameLoginUI                  = MSDK::kMethodNameLoginUI,
    kMethodNameConnect                  = MSDK::kMethodNameConnect,
    kMethodNameUnConnect                = MSDK::kMethodNameUnConnect,
    kMethodNameGetConnectRet            = MSDK::kMethodNameGetConnectRet,
    kMethodNameBindUI                   = MSDK::kMethodNameBindUI,
    kMethodNameCanBind                  = MSDK::kMethodNameCanBind,
#if MSDK_PLATFORM_WINDOWS
    kMethodNameQrCode                   = MSDK::kMethodNameQrCode,
    kMethodNameRefreshToken             = MSDK::kMethodNameRefreshToken,
#endif // MSDK_PLATFORM_WINDOWS
    kMethodNameCheckUniversalLink       = MSDK::kMethodNameCheckUniversalLink,

    kMethodNameCheckAndLogin             = MSDK::kMethodNameCheckAndLogin, // A 模式
    kMethodNameCheck                     = MSDK::kMethodNameCheck, // B 模式
    kMethodNameBindWithConfirmCode       = MSDK::kMethodNameBindWithConfirmCode, // B 模式
    kMethodNameConsoleRefreshToken       = MSDK::kMethodNameConsoleRefreshToken, // GCLOUD_MSDK_CONSOLE，刷新Token接口
    kMethodNamePermissionAuth            = MSDK::kMethodNamePermissionAuth,
    kMethodNameChannelPermissionAuth     = MSDK::kMethodNameChannelPermissionAuth,

    kMethodNameShareToWall              = MSDK::kMethodNameShareToWall,
    kMethodNameSendMessageToFriend      = MSDK::kMethodNameSendMessageToFriend,
    kMethodNameQueryFriend              = MSDK::kMethodNameQueryFriend,
    kMethodNameAddFriend                = MSDK::kMethodNameAddFriend,

    kMethodNameCreateGroup              = MSDK::kMethodNameCreateGroup,
    kMethodNameBindGroup                = MSDK::kMethodNameBindGroup,
    kMethodNameGetGroupList             = MSDK::kMethodNameGetGroupList,
    kMethodNameGetGroupState            = MSDK::kMethodNameGetGroupState,
    kMethodNameJoinGroup                = MSDK::kMethodNameJoinGroup,
    kMethodNameUnbindGroup              = MSDK::kMethodNameUnbindGroup,
    kMethodNameRemindToBindGroup        = MSDK::kMethodNameRemindToBindGroup,
    kMethodNameSendMessageToGroup       = MSDK::kMethodNameSendMessageToGroup,
    kMethodNameGetGroupRelation         = MSDK::kMethodNameGetGroupRelation,

    kMethodNameCloseWebViewURL          = MSDK::kMethodNameCloseWebViewURL,
    kMethodNameGetEncodeURL             = MSDK::kMethodNameGetEncodeURL,
    kMethodNameWebViewJsCall            = MSDK::kMethodNameWebViewJsCall,
    kMethodNameWebViewJsShare           = MSDK::kMethodNameWebViewJsShare,
    kMethodNameWebViewJsSendMessage     = MSDK::kMethodNameWebViewJsSendMessage,
    kMethodNameWebViewEmbedProgress     = MSDK::kMethodNameWebViewEmbedProgress,


    kMethodNameRegisterPush             = MSDK::kMethodNameRegisterPush,
    kMethodNameUnregisterPush           = MSDK::kMethodNameUnregisterPush,
    kMethodNameSetTagForPush            = MSDK::kMethodNameSetTagForPush,
    kMethodNameDeleteTagForPush         = MSDK::kMethodNameDeleteTagForPush,
    kMethodNameAddLocalNotify           = MSDK::kMethodNameAddLocalNotify,
    kMethodNameClearLocalNotify         = MSDK::kMethodNameClearLocalNotify,
    kMethodNameNotifyCallback           = MSDK::kMethodNameNotifyCallback,
    kMethodNameNotifyShow               = MSDK::kMethodNameNotifyShow,
    kMethodNameNotifyClick              = MSDK::kMethodNameNotifyClick,
    kMethodNameSetAccountPush           = MSDK::kMethodNameSetAccountPush,
    kMethodNameDeleteAccountPush        = MSDK::kMethodNameDeleteAccountPush,




    kMethodNameLoadNoticeData           = MSDK::kMethodNameLoadNoticeData,

    kMethodNameSetupGame                = MSDK::kMethodNameSetupGame,
    kMethodNameShowGameLeaderBoard      = MSDK::kMethodNameShowGameLeaderBoard,
    kMethodNameSetScore                 = MSDK::kMethodNameSetScore,
    kMethodNameShowGameAchievement      = MSDK::kMethodNameShowGameAchievement,
    kMethodNameUnlockGameAchieve        = MSDK::kMethodNameUnlockGameAchieve,

    KMethodNameToolsOpenDeepLink        = MSDK::KMethodNameToolsOpenDeepLink,
    KMethodNameToolsConvertShortUrl     = MSDK::KMethodNameToolsConvertShortUrl,
    KMethodNameToolsGetFreeFlowInfo     = MSDK::KMethodNameToolsGetFreeFlowInfo,

    kMethodNameCrashExtraData           = MSDK::kMethodNameCrashExtraData,
    kMethodNameCrashExtraMessage        = MSDK::kMethodNameCrashExtraMessage,

    kMethodNameExtend                   = MSDK::kMethodNameExtend,

    kMethodNameLBSGetLocation           = MSDK::kMethodNameLBSGetLocation,
    kMethodNameLBSClearLocation         = MSDK::kMethodNameLBSClearLocation,
    kMethodNameLBSGetNearby             = MSDK::kMethodNameLBSGetNearby,
    kMethodNameLBSGetIPInfo             = MSDK::kMethodNameLBSGetIPInfo,


    kMethodNameAccountVerifyCode        = MSDK::kMethodNameAccountVerifyCode,
    kMethodNameAccountResetPassword     = MSDK::kMethodNameAccountResetPassword,
    kMethodNameAccountModify            = MSDK::kMethodNameAccountModify,
    kMethodNameAccountLoginWithCode     = MSDK::kMethodNameAccountLoginWithCode,
    kMethodNameAccountGetRegisterStatus    = MSDK::kMethodNameAccountGetRegisterStatus,
    kMethodNameAccountGetVerifyCodeStatus = MSDK::kMethodNameAccountGetVerifyCodeStatus,
    kMethodNameAccountGetReceiveEmail   = MSDK::kMethodNameAccountGetReceiveEmail,
    kMethodNameAccountVerifyPassword    = MSDK::kMethodNameAccountVerifyPassword,
}MethodName;

typedef enum ObserverID
{
    kObserverIDLoginRet               = MSDK::kObserverIDLoginRet,
    kObserverIDLoginBaseRet           = MSDK::kObserverIDLoginBaseRet,
    kObserverIDRealName               = MSDK::kObserverIDRealName,
    kObserverIDWakeUp                 = MSDK::kObserverIDWakeUp,
    kObserverIDLogoutPlugin           = MSDK::kObserverIDLogoutPlugin,
    kObserverIDLoginPlugin            = MSDK::kObserverIDLoginPlugin,
    kObserverIDConnectRet             = MSDK::kObserverIDConnectRet,
    kObserverIDCanBindRet             = MSDK::kObserverIDCanBindRet,
    
#if MSDK_PLATFORM_WINDOWS
    kObserverIDQrCodeRet              = MSDK::kObserverIDQrCodeRet,
    kObserverIDRefreshToken           = MSDK::kObserverIDRefreshToken,
#endif // MSDK_PLATFORM_WINDOWS
    kObserverIDCheckAndLogin          = MSDK::kObserverIDCheckAndLogin, //
    kObserverIDCheck                  = MSDK::kObserverIDCheck, //
    kObserverIDBindWithConfirmCode    = MSDK::kObserverIDBindWithConfirmCode, //
    
    
    kObserverIDDeliverMessage         = MSDK::kObserverIDDeliverMessage,
    kObserverIDQueryFriend            = MSDK::kObserverIDQueryFriend,
    
    kObserverIDGroupRet               = MSDK::kObserverIDGroupRet,
    
    kObserverIDWebViewRet             = MSDK::kObserverIDWebViewRet,
    kObserverIDWebViewJsShare         = MSDK::kObserverIDWebViewJsShare,
    kObserverIDWebViewToolBarShare    = MSDK::kObserverIDWebViewToolBarShare,
    kObserverIDInnerShareCallback     = MSDK::kObserverIDInnerShareCallback,    //use for android
    
    kObserverIDPushBaseRet            = MSDK::kObserverIDPushBaseRet,
    kObserverIDPushNotifyCallback     = MSDK::kObserverIDPushNotifyCallback,
    
    kObserverIDLoadNoticeData         = MSDK::kObserverIDLoadNoticeData,
    
    kObserverIDGameBaseRet            = MSDK::kObserverIDGameBaseRet,
    kObserverIDSendModuleEvent        = MSDK::kObserverIDSendModuleEvent,
    
    kObserverIDToolsRet               = MSDK::kObserverIDToolsRet,
    kObserverIDToolsFreeFlowRet       = MSDK::kObserverIDToolsFreeFlowRet,
    
    kObserverIDExtendRet              = MSDK::kObserverIDExtendRet,
    
    kObserverIDLBSLocationRet         = MSDK::kObserverIDLBSLocationRet,
    kObserverIDLBSRelationRet         = MSDK::kObserverIDLBSRelationRet,
    kObserverIDLBSIPInfoRet           = MSDK::kObserverIDLBSIPInfoRet,
    kObserverIDLBSBaseRet             = MSDK::kObserverIDLBSBaseRet,
    kObserverIDLBSPluginSucRet        = MSDK::kObserverIDLBSPluginSucRet,
    
    kObserverIDAccountRet             = MSDK::kObserverIDAccountRet,
    
}ObserverID;

typedef enum GroupHandleType
{
    kGroupHandleTypeInPlugin = MSDK::kGroupHandleTypeInPlugin,
    kGroupHandleTypeInCoreKit = MSDK::kGroupHandleTypeInCoreKit,
} GroupHandleType;

class MSDK_EXPORT MSDKBaseRet
{
public:
    // 标记是从哪个方法过来
    int methodNameID;
    // MSDK 返回码，详情可参考 MSDKError.h
    int retCode;
    // MSDK 描述信息
    String retMsg;
    // 第三方渠道返回码
    int thirdCode;
    // 第三方渠道描述信息
    String thirdMsg;
    // 扩展字段，保留
    String extraJson;
    
    // 构造函数对外使用，必须包含在外部调用，否则会 crash
    MSDKBaseRet() : retCode(MSDKError::UNKNOWN), thirdCode(-1), thirdMsg("")
    {
        methodNameID = kMethodNameUndefine;
    }
    
    // 构造函数对外使用，必须包含在外部调用，否则会 crash
    MSDKBaseRet(int code) : retCode(code), thirdCode(-1), thirdMsg("")
    {
        methodNameID = kMethodNameUndefine;
    }
    
    // 构造函数对外使用，必须包含在外部调用，否则会 crash
    MSDKBaseRet(int code, int tCode, String tMsg)
    : retCode(code), thirdCode(tCode), thirdMsg(tMsg)
    {
        methodNameID = kMethodNameUndefine;
    }
    
    MSDKBaseRet(const MSDK::MSDKBaseRet &baseRet)
    {
        methodNameID = baseRet.methodNameID;
        retCode = baseRet.retCode;
        retMsg = baseRet.retMsg;
        thirdCode = baseRet.thirdCode;
        thirdMsg = baseRet.thirdMsg;
        extraJson = baseRet.extraJson;
    }
    
    MSDK::MSDKBaseRet convert()
    {
        MSDK::MSDKBaseRet baseRet;
        baseRet.methodNameID = methodNameID;
        baseRet.retCode = retCode;
        baseRet.retMsg = retMsg.toString();
        baseRet.thirdCode = thirdCode;
        baseRet.thirdMsg = thirdMsg.toString();
        baseRet.extraJson = extraJson.toString();
        return baseRet;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.MSDKRet", A(thirdCode, "ret"), A(thirdMsg, "msg"),
               O(methodNameID, retCode, retMsg, extraJson));
    
};

using MSDKFriendReqInfo = MSDK::MSDKFriendReqInfo;
using MSDKLoginParams = MSDK::MSDKLoginParams;
using MSDKBaseParams = MSDK::MSDKBaseParams;
using InnerLoginRet = MSDK::InnerLoginRet;
using InnerConnectRet = MSDK::InnerConnectRet;
using InnerAccountRet = MSDK::InnerAccountRet;
using InnerToolsRet = MSDK::InnerToolsRet;
using InnerNoticeRet = MSDK::InnerNoticeRet;
using InnerLBSIPInfoRet = MSDK::InnerLBSIPInfoRet;
using InnerLoginPluginRet = MSDK::InnerLoginPluginRet;
using InnerBaseRet = MSDK::InnerBaseRet;
using InnerCrashRet = MSDK::InnerCrashRet;
using InnerFriendRet = MSDK::InnerFriendRet;
using InnerExtendRet = MSDK::InnerExtendRet;
using InnerUnionInfo = MSDK::InnerUnionInfo;
using InnerWebViewRet = MSDK::InnerWebViewRet;
using InnerGroupRet = MSDK::InnerGroupRet;
using InnerGroupInfo = MSDK::InnerGroupInfo;
using InnerPushRet = MSDK::InnerPushRet;
using InnerLocalNotification = MSDK::InnerLocalNotification;
using InnerWebViewReqInfo = MSDK::InnerWebViewReqInfo;
using InnerLBSLocationPluginRet = MSDK::InnerLBSLocationPluginRet;
using InnerLBSRelationRet = MSDK::InnerLBSRelationRet;
using InnerLBSLocationRet = MSDK::InnerLBSLocationRet;

template<typename RetType>
using MSDKInnerObserverHolder = MSDK::MSDKInnerObserverHolder<RetType>;


NS_MSDK_SPACE_NO_STL_END

#ifdef USING_MSDK_NO_STL
    USING_NS_MSDK_SPACE_NO_STL
#else
    USING_NS_MSDK
#endif

#endif /* MSDK_DEFINE_H */
