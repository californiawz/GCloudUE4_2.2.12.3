//
//  MSDKFriendService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/06/08.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "GUAFriendService.h"
#include "MSDKFriend.h"
#include "GUAErrorCode.h"
#include "MSDKStructUtility.h"
#include "MSDKDefine.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

class MSDKFriendObserver : public GCloud::MSDKSpace::NoSTL::MSDKFriendObserver
{
public:
    static MSDKFriendObserver Instance;
    GUAFriendObserver* friend_observer_;
public:
    MSDKFriendObserver() :friend_observer_(nullptr){

    }

    void OnDeliverMessageNotify(const GCloud::MSDKSpace::NoSTL::MSDKBaseRet &msdk_base_ret)
    {
        GUABaseResult gua_base_ret;
        MSDKStructUtility::ConvertBaseRetToGUA(msdk_base_ret, gua_base_ret);

		if (MSDKFriendObserver::Instance.friend_observer_ != nullptr) 
		{
			MSDKFriendObserver::Instance.friend_observer_->OnBaseResultNotify(gua_base_ret);
		}
		else
		{
			LOG_DEBUG("MSDKFriendObserver::Instance.friend_observer_ is nullptr");
		}
      
    }

    void OnQueryFriendNotify(const GCloud::MSDKSpace::NoSTL::MSDKFriendRet &msdk_friend_ret)
    {
		GUAFriendResult gua_friend_ret;
		MSDKStructUtility::ConvertFriendRetToGUA(msdk_friend_ret, gua_friend_ret);

		if (MSDKFriendObserver::Instance.friend_observer_ != nullptr) 
		{
			MSDKFriendObserver::Instance.friend_observer_->OnQueryFriendNotify(gua_friend_ret);
		}
		else
		{
			LOG_DEBUG("MSDKFriendObserver::Instance.friend_observer_ is nullptr");
		}

    }
};

MSDKFriendObserver MSDKFriendObserver::Instance;

void GUAFriendService::SetFriendObserver(GUAFriendObserver *observer)
{
	MSDKFriendObserver::Instance.friend_observer_ = observer;
#if PLATFORM_IOS || PLATFORM_ANDROID
	GCloud::MSDKSpace::NoSTL::MSDKFriend::SetFriendObserver(&MSDKFriendObserver::Instance);
#endif
}

void GUAFriendService::SendMessage(const GUAFriendReqInfo &req_info, const std::string &channel) 
{
	GCloud::MSDKSpace::NoSTL::MSDKFriendReqInfo req;
	MSDKStructUtility::ConvertFriendReqToMSDK(req_info, req);
	GCloud::MSDKSpace::NoSTL::MSDKFriend::SendMessage(req, channel.c_str());
}

void GUAFriendService::Share(const GUAFriendReqInfo &req_info, const std::string &channel) 
{
	GCloud::MSDKSpace::NoSTL::MSDKFriendReqInfo req;
	MSDKStructUtility::ConvertFriendReqToMSDK(req_info, req);
	GCloud::MSDKSpace::NoSTL::MSDKFriend::Share(req, channel.c_str());
}

void GUAFriendService::QueryFriends(int page, int count, bool is_in_game,const std::string &channel, const std::string &sub_channel, const std::string &extra_json) 
{
	GCloud::MSDKSpace::NoSTL::MSDKFriend::QueryFriends(page,count,is_in_game,channel.c_str(),extra_json.c_str());
}

void GUAFriendService::AddFriend(const GUAFriendReqInfo &req_info, const std::string &channel) 
{
    GCloud::MSDKSpace::NoSTL::MSDKFriendReqInfo req;
    MSDKStructUtility::ConvertFriendReqToMSDK(req_info, req);
    GCloud::MSDKSpace::NoSTL::MSDKFriend::AddFriend(req, channel);
}
GUA_NAMESPACE_END