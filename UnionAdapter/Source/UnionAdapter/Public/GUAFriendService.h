//
//  GUAFriendService.h
//  GUASample
//
//  Created by weiqiangluo on 2022/5/9.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN
typedef enum GUA_EXTERN GUAFriendReqType
{
    kGUAFriendReqTypeText = 10000,           //text sharing
    kGUAFriendReqTypeLink,                   //link sharing
    kGUAFriendReqTypeIMG,                    //texture sharing
    kGUAFriendReqTypeInvite,                 //app sharing
    kGUAFriendReqTypeMusic,                  //music sharing
    kGUAFriendReqTypeVideo,                  //video sharing
    kGUAFriendReqTypeMiniApp,                //applets sharing
    kGUAFriendReqTypePullUpMiniApp,          //applet pull up
    kGUAFriendReqTypeArk,                    //ARK sharing
    kGUAFriendReqTypeOpenBusinessView,       //Pull up business functions
    kGUAFriendReqTypeWXGameLine,             //Game circle sharing
    kGUAFriendReqTypeWXChannelShareVideo,    //sharing to wxchannel
    kGUAFriendReqTypeWXStateText,            //sharing text to WXState
    kGUAFriendReqTypeWXStatePhoto,           //sharing photo to WXState
    kGUAFriendReqTypeWXStateMusicVideo,      //sharing audio to WXState
    kGUAFriendReqTypeWXChannelStartLive,     //W channel live
    kGUAFriendReqTypeWithCommonShare,        //small world share
    kGUAFriendReqTypeWXNativeGamePage,      // Native Game share

    kGUAFriendReqTypeTextSilent = 20000,     //text sharing（silence）
    kGUAFriendReqTypeLinkSilent,             //link sharing (silence)
    kGUAFriendReqTypeIMGSilent,              //texture sharing （silence）
    kGUAFriendReqTypeInviteSilent,           //application invitation (silence）
    kGUAFriendReqTypeMusicSilent,            //music sharing (silence)
    kGUAFriendReqTypeVideoSilent,            //video sharing (silence)
    kGUAFriendReqTypeMiniAppSilent,          //applets sharing (silence)
} GUAFriendReqType;

class GUA_EXTERN GUAFriendReqInfo
{
public:
    // [required] the type defined in FriendReqType
    int type;

    // [optional] specific user, openid or uid
    std::string user;

    // [required] the title contents
    std::string title;

    // [optional] descriptions for your share contents
    std::string description;

    // [optional] image path, it would be a network image url or local image file path, local image is recommended.
    std::string image_path;

    // [optional] the thumb image path,such as game's icon. It would be a network image url or local image file path, local image is recommended.
    std::string thumb_path;

    // [optional] the media path, video or music, only support the local file path
    std::string media_path;

    // [optional] the link to be shared, such as an image/music/video url or a redirect url
    std::string link;

    // [optional] extra params with json format
    std::string extra_json;

    GUAFriendReqInfo() : type(-1) {}
};

class GUA_EXTERN GUAPersonInfo
{
public:
    // open id
    std::string openid;
    
    // user name
    std::string user_name;
    
    // gender, 0:unknown, 1:man, 2:woman
    int gender = 0;
    
    // user portrait picture url
    std::string picture_url;
    
    // user's country
    std::string country;
    
    // user's province
    std::string province;
    
    // user's city
    std::string city;
    
    // user's language
    std::string language;

    // user's extra json
    std::string extra_json;
};

class GUA_EXTERN GUAFriendResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    std::vector<GUAPersonInfo> friend_info_list;
};

class GUA_EXTERN GUAFriendObserver
{
public:
    virtual ~GUAFriendObserver() {};

    virtual void OnBaseResultNotify(const GUABaseResult &base_ret){};

    virtual void OnQueryFriendNotify(const GUAFriendResult &friend_ret){};
};

class GUA_EXTERN GUAFriendService
{
public:
    /**
     * @brief Set friend module observer
     * @param observer       [required] object implements from FriendObserver
     */
    static void SetFriendObserver(GUAFriendObserver *observer);

	// Common API
    /**
     * @brief Send message to the dialog, such as Line chat
     * @param req_info      [required] message data struct, include the contents
     * @param channel       [optional] the specific channel, the default value is the login channel
     */
    static void SendMessage(const GUAFriendReqInfo &req_info, const std::string &channel = GUA_DEFAULT_EMPTY_STRING);

    /**
     * @brief Share contents to the timeline or zone
     * @param req_info      [required] message data struct, include the contents
     * @param channel       [optional] the specific channel, the default value is the login channel
     */
    static void Share(const GUAFriendReqInfo &req_info, const std::string &channel = GUA_DEFAULT_EMPTY_STRING);
    
    /**
     * @brief Share contents to the timeline or zone
     * @param page          [optional] the page number of the friend list
     * @param count         [optional] count of friends in every page
     * @param is_in_game    [optional] whether the friend is in game or not
     * @param channel       [optional] the specific channel, the default value is the login channel
	 * @param sub_channel   [optional] the specific subchannel
     * @param extra_json    [optional] extra params with json format
     */
    static void QueryFriends(
		int page = 0, 
		int count = 0, 
		bool is_in_game = true,
        const std::string &channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &sub_channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
	// Common API End

	// INTLSDK API
    // INTLSDK API End

	// MSDK API
    /**
     * @brief [MSDK Only] Add friend
     *
     * @param reqInfo   [required] message data struct, containing the personal information of the friend to be added
     * @param channel   [optional] the specific channel
     */
    static void AddFriend(const GUAFriendReqInfo &req_info, const std::string &channel  = GUA_DEFAULT_EMPTY_STRING);
	// MSDK API End
};

GUA_NAMESPACE_END
