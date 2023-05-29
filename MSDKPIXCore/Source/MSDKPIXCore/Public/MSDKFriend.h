/*!
 * @Module MSDK
 *
 * @Header  MSDKFriend.h
 * @Author  developer
 * @Date 2018/3/20
 * @Abstract
 * 关系链模块接口声明
 * 1、SendMessage ：发送消息给好友
 * 2、Share ：分享消息
 * 3、AddFriend ：添加好友
 * 4、QueryFriend ： 获取好友关系链
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_Friend_H
#define MSDK_Friend_H


#include <stdio.h>
#include <iostream>
#include "MSDKMacros.h"
#include "MSDKDefine.h"
#include "MSDKSingleton.h"
#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif
NS_MSDK_BEGIN

typedef enum MSDK_EXPORT MSDKFriendReqType
{
    kMSDKFriendReqTypeText = 10000,           //文字分享
    kMSDKFriendReqTypeLink,                   //链接分享
    kMSDKFriendReqTypeIMG,                    //图片分享
    kMSDKFriendReqTypeInvite,                 //应用邀请
    kMSDKFriendReqTypeMusic,                  //音乐分享
    kMSDKFriendReqTypeVideo,                  //视频分享
    kMSDKFriendReqTypeMiniApp,                //小程序分享
    kMSDKFriendReqTypePullUpMiniApp,          //小程序拉起
    kMSDKFriendReqTypeArk,                    //ARK分享
    kMSDKFriendReqTypeOpenBusinessView,       //业务功能拉起
    kMSDKFriendReqTypeWXGameLine,             //
    kMSDKFriendReqTypeWXChannelShareVideo,    //分享至视频号
    kMSDKFriendReqTypeWXStateText,            //分享文本至WX状态
    kMSDKFriendReqTypeWXStatePhoto,           //分享图片至WX状态
    kMSDKFriendReqTypeWXStateMusicVideo,      //分享音乐视频至WX状态
    kMSDKFriendReqTypeWXChannelStartLive,      //视频号直播
    kMSDKFriendReqTypeWithCommonShare,        //通用分享，目前支持小世界
    kMSDKFriendReqTypeWXNativeGamePage,       // 原生分享

    kMSDKFriendReqTypeTextSilent = 20000,     //文字分享（静默）
    kMSDKFriendReqTypeLinkSilent,             //链接分享 (静默)
    kMSDKFriendReqTypeIMGSilent,              //图片分享 （静默）
    kMSDKFriendReqTypeInviteSilent,           //应用邀请 (静默）
    kMSDKFriendReqTypeMusicSilent,            //音乐分享 (静默)
    kMSDKFriendReqTypeVideoSilent,            //视频分享 (静默)
    kMSDKFriendReqTypeMiniAppSilent,          //小程序分享 (静默)
} MSDKFriendReqType;

// 个人信息类
// 修改需谨慎，LBS 模块附近玩家信息继承了该类
class MSDKPersonInfo
{
public:
    std::string openid;       // 用户标识
    std::string userName;     // 昵称
    int gender;               // 性别1男2女,用户未填则默认0
    std::string pictureUrl;   //
    std::string country;      // 国家
    std::string province;     // 省份
    std::string city;         // 城市
    std::string language;     // 语言

AutoParser("com.itop.gcloud.msdk.api.friend.MSDKPersonInfo",
           A(pictureUrl, "picture_url"), A(userName, "user_name"),
           O(gender, openid, language, country, province, city));

};

class MSDK_EXPORT MSDKFriendRet : public MSDKBaseRet
{
public:
    MSDKFriendRet()
    {
    }

    MSDKFriendRet(int retCode) : MSDKBaseRet(retCode)
    {

    }

    std::vector<MSDKPersonInfo> friendInfoList;


AutoParser("com.itop.gcloud.msdk.api.friend.MSDKFriendRet",
           A(friendInfoList, "lists"), A(extraJson, "extinfo"),
           A(thirdCode, "ret"), A(thirdMsg, "msg"),
           O(retCode, retMsg, methodNameID));

};

class MSDK_EXPORT MSDKFriendObserver
{
public:
    virtual ~MSDKFriendObserver() {};

    virtual void OnDeliverMessageNotify(const MSDKBaseRet &baseRet) {};

    virtual void OnQueryFriendNotify(const MSDKFriendRet &friendRet) {};
};

class MSDK_EXPORT MSDKFriend
{
private :
    static void BaseRetObserver(const InnerBaseRet &baseRet, const char *seqID)
    {
        MSDKBaseRet *pRet = new MSDKBaseRet();
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet start");
        MSDKCompatManager::compatConvert(*pRet, baseRet);
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet finish then will notify user");
        if (mFriendObserver)
        {
#if MSDK_ENGINE_UE4
            AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 friend BaseRetObserver");
                mFriendObserver->OnDeliverMessageNotify(*pRet);
                delete pRet;
            });
#else
            mFriendObserver->OnDeliverMessageNotify(*pRet);
            delete pRet;
#endif
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "friend observer is null");
            delete pRet;
        }
    }

    static void FriendRetObserver(const InnerFriendRet &friendRet, const char *seqID)
    {
        MSDKFriendRet *pRet = new MSDKFriendRet();
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerFriendRet to MSDKFriendRet start");
        MSDKCompatManager::compatConvert(*pRet, friendRet);
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerFriendRet to MSDKFriendRet finish then will notify user");
        if (mFriendObserver)
        {
#if MSDK_ENGINE_UE4
            AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 FriendRetObserver");
                mFriendObserver->OnQueryFriendNotify(*pRet);
                delete pRet;
            });
#else
            mFriendObserver->OnQueryFriendNotify(*pRet);
            delete pRet;
#endif
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "friend observer is null");
            delete pRet;
        }
    }

    static MSDKFriendObserver *mFriendObserver;

    ~MSDKFriend();

    static MSDKBaseParams ReportPRV(MethodName nameID, const MSDKFriendReqInfo &reqInfo, const String &channel);

	static void SetPRVFriendObserver(
            typename T<InnerBaseRet>::InnerRetCallback baseRetObserver,
            typename T<InnerFriendRet>::InnerRetCallback pushRetObserver);

public:

#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
	MSDK_EXPORT_UE static void SetFriendObserver(MSDKFriendObserver *friendObserver);
#else
	static void SetFriendObserver(MSDKFriendObserver *friendObserver)
    {
        if (!friendObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKFriendObserver cant not be NULL");
        }
        else
        {
            mFriendObserver = friendObserver;
            SetPRVFriendObserver(BaseRetObserver, FriendRetObserver);
        }
    }
#endif

    /**
    * 发送消息到会话
    *
    * ！！Facebook 将不再支持发送消息到 Messenger，请项目组谨慎使用。Facebook 相关文档见 https://developers.facebook.com/docs/messenger-platform/changelog/#20190610.
    *
    * @param reqInfo 消息结构体，包含需要发送的内容
    * @param channel 渠道信息，比如“Facebook”
    */
	MSDK_EXPORT_UE static void SendMessage(const MSDKFriendReqInfo &reqInfo, const String &channel = "");


    /**
     * 分享
     *
     * @param reqInfo 消息结构体，包含需要分享的内容
     * @param channel 渠道信息，比如“Facebook”
     */
	MSDK_EXPORT_UE static void Share(const MSDKFriendReqInfo &reqInfo, const String &channel = "");


    /**
     * 获取好友列表
     * @param page  拉取第几页好友
     * @param count 每页好友的数量
     * @param isInGame 是否是游戏内好友
     *                 true：游戏内好友
     *                 false：非游戏内好友
     * @param channel 渠道信息
     * @param subChannel 用于复杂渠道的子渠道标识
     * @param extraJson    扩展字段
     */
	MSDK_EXPORT_UE static void QueryFriends(int page = 0, int count = 0, bool isInGame = true, const String channel = ""
            , const String subChannel = "", const String &extraJson = "");

    /**
     * 添加好友
     *
     * @param reqInfo 消息结构体，包含需要添加的好友的个人信息
     * @param channel 渠道信息，仅支持
     */
	MSDK_EXPORT_UE static void AddFriend(const MSDKFriendReqInfo &reqInfo, const String &channel  = "");

};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

typedef enum MSDK_EXPORT MSDKFriendReqType
{
    kMSDKFriendReqTypeText = MSDK::kMSDKFriendReqTypeText,
    kMSDKFriendReqTypeLink = MSDK::kMSDKFriendReqTypeLink,
    kMSDKFriendReqTypeIMG = MSDK::kMSDKFriendReqTypeIMG,
    kMSDKFriendReqTypeInvite = MSDK::kMSDKFriendReqTypeInvite,
    kMSDKFriendReqTypeMusic = MSDK::kMSDKFriendReqTypeMusic,
    kMSDKFriendReqTypeVideo = MSDK::kMSDKFriendReqTypeVideo,
    kMSDKFriendReqTypeMiniApp = MSDK::kMSDKFriendReqTypeMiniApp,
    kMSDKFriendReqTypePullUpMiniApp = MSDK::kMSDKFriendReqTypePullUpMiniApp,
    kMSDKFriendReqTypeArk = MSDK::kMSDKFriendReqTypeArk,
    kMSDKFriendReqTypeOpenBusinessView = MSDK::kMSDKFriendReqTypeOpenBusinessView,
    kMSDKFriendReqTypeWXGameLine = MSDK::kMSDKFriendReqTypeWXGameLine,
    kMSDKFriendReqTypeWXChannelShareVideo = MSDK::kMSDKFriendReqTypeWXChannelShareVideo,
    kMSDKFriendReqTypeWXStateText = MSDK::kMSDKFriendReqTypeWXStateText,
    kMSDKFriendReqTypeWXStatePhoto = MSDK::kMSDKFriendReqTypeWXStatePhoto,
    kMSDKFriendReqTypeWXStateMusicVideo = MSDK::kMSDKFriendReqTypeWXStateMusicVideo,
    kMSDKFriendReqTypeWXChannelStartLive = MSDK::kMSDKFriendReqTypeWXChannelStartLive,
    kMSDKFriendReqTypeWithCommonShare = MSDK::kMSDKFriendReqTypeWithCommonShare,
    kMSDKFriendReqTypeWXNativeGamePage = MSDK::kMSDKFriendReqTypeWXNativeGamePage,
    kMSDKFriendReqTypeTextSilent = MSDK::kMSDKFriendReqTypeTextSilent,
    kMSDKFriendReqTypeLinkSilent = MSDK::kMSDKFriendReqTypeLinkSilent,
    kMSDKFriendReqTypeIMGSilent = MSDK::kMSDKFriendReqTypeIMGSilent,
    kMSDKFriendReqTypeInviteSilent = MSDK::kMSDKFriendReqTypeInviteSilent,
    kMSDKFriendReqTypeMusicSilent = MSDK::kMSDKFriendReqTypeMusicSilent,
    kMSDKFriendReqTypeVideoSilent = MSDK::kMSDKFriendReqTypeVideoSilent,
    kMSDKFriendReqTypeMiniAppSilent = MSDK::kMSDKFriendReqTypeMiniAppSilent
}MSDKFriendReqType;

// 个人信息类
// 修改需谨慎，LBS 模块附近玩家信息继承了该类
class MSDKPersonInfo
{
public:
    String openid;       // 用户标识
    String userName;     // 昵称
    int gender;               // 性别1男2女,用户未填则默认0
    String pictureUrl;   //
    String country;      // 国家
    String province;     // 省份
    String city;         // 城市
    String language;     // 语言
    
    MSDKPersonInfo(const MSDK::MSDKPersonInfo &personInfo) {
        openid = personInfo.openid;
        userName = personInfo.userName;
        gender = personInfo.gender;
        pictureUrl = personInfo.pictureUrl;
        country = personInfo.country;
        province = personInfo.province;
        city = personInfo.city;
        language = personInfo.language;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.friend.MSDKPersonInfo",
               A(pictureUrl, "picture_url"), A(userName, "user_name"),
               O(gender, openid, language, country, province, city));
    
};

class MSDK_EXPORT MSDKFriendRet : public MSDKBaseRet
{
public:
    MSDKFriendRet()
    {
    }
    
    MSDKFriendRet(int retCode) : MSDKBaseRet(retCode)
    {
        
    }
    
    Vector<MSDKPersonInfo> friendInfoList;
    
    MSDKFriendRet(const MSDK::MSDKFriendRet &friendRet) : MSDKBaseRet(friendRet) {
        std::vector<MSDK::MSDKPersonInfo>::const_iterator it;
        for (it = friendRet.friendInfoList.begin(); it != friendRet.friendInfoList.end(); ++it) {
            friendInfoList.push_back(*it);
        }
    }
    
    AutoParser("com.itop.gcloud.msdk.api.friend.MSDKFriendRet",
               A(friendInfoList, "lists"), A(extraJson, "extinfo"),
               A(thirdCode, "ret"), A(thirdMsg, "msg"),
               O(retCode, retMsg, methodNameID));
    
};

class MSDK_EXPORT MSDKFriendObserver
{
public:
    virtual ~MSDKFriendObserver() {};
    
    virtual void OnDeliverMessageNotify(const MSDKBaseRet &baseRet) {};
    
    virtual void OnQueryFriendNotify(const MSDKFriendRet &friendRet) {};
};

class MSDKFriendObserverAdapter : public MSDK::MSDKFriendObserver
{
public:
    void OnDeliverMessageNotify(const MSDK::MSDKBaseRet &baseRet);
    void OnQueryFriendNotify(const MSDK::MSDKFriendRet &friendRet);
    
    MSDKSpace::NoSTL::MSDKFriendObserver *mObserver = NULL;
};

class MSDK_EXPORT MSDKFriend
{
private:
    static MSDKFriendObserverAdapter mFriendObserverAdapter;
public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    MSDK_EXPORT_UE static void SetFriendObserver(MSDKFriendObserver *friendObserver);
#else
    static void SetFriendObserver(MSDKFriendObserver *friendObserver)
    {
        if (!friendObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKFriendObserver cant not be NULL");
        }
        else
        {
            mFriendObserverAdapter.mObserver = friendObserver;
            MSDK::MSDKFriend::SetFriendObserver(&mFriendObserverAdapter);
        }
    }
#endif

    /**
     * 发送消息到会话
     *
     * ！！Facebook 将不再支持发送消息到 Messenger，请项目组谨慎使用。Facebook 相关文档见 https://developers.facebook.com/docs/messenger-platform/changelog/#20190610.
     *
     * @param reqInfo 消息结构体，包含需要发送的内容
     * @param channel 渠道信息，比如“Facebook”
     */
    MSDK_EXPORT_UE static void SendMessage(const MSDKFriendReqInfo &reqInfo, const String &channel = "");
    
    /**
     * 分享
     *
     * @param reqInfo 消息结构体，包含需要分享的内容
     * @param channel 渠道信息，比如“Facebook”
     */
    MSDK_EXPORT_UE static void Share(const MSDKFriendReqInfo &reqInfo, const String &channel = "");
    
    
    /**
     * 获取好友列表
     * @param page  拉取第几页好友
     * @param count 每页好友的数量
     * @param isInGame 是否是游戏内好友
     *                 true：游戏内好友
     *                 false：非游戏内好友
     * @param channel 渠道信息
     * @param subChannel 用于复杂渠道的子渠道标识
     * @param extraJson    扩展字段
     */
    MSDK_EXPORT_UE static void QueryFriends(int page = 0, int count = 0, bool isInGame = true, const String channel = ""
                                            , const String subChannel = "", const String &extraJson = "");
    
    /**
     * 添加好友
     *
     * @param reqInfo 消息结构体，包含需要添加的好友的个人信息
     * @param channel 渠道信息，仅支持
     */
    MSDK_EXPORT_UE static void AddFriend(const MSDKFriendReqInfo &reqInfo, const String &channel  = "");
};

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDK_Friend_H */
