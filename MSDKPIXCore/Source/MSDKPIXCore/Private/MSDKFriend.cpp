//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKFriend.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

void MSDKFriend::SetFriendObserver(MSDKFriendObserver *friendObserver) {}

void MSDKFriend::SendMessage(const MSDKFriendReqInfo &reqInfo, const String &channel) {}

void MSDKFriend::Share(const MSDKFriendReqInfo &reqInfo, const String &channel) {}

void MSDKFriend::QueryFriends(int page, int count, bool isInGame, const String channel, const String subChannel, const String &extraJson) {}
			
void MSDKFriend::AddFriend(const MSDKFriendReqInfo &reqInfo, const String &channel) {}

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKFriend::SetFriendObserver(MSDKFriendObserver *friendObserver) {}

void MSDKFriend::SendMessage(const MSDKFriendReqInfo &reqInfo, const String &channel) {}

void MSDKFriend::Share(const MSDKFriendReqInfo &reqInfo, const String &channel) {}

void MSDKFriend::QueryFriends(int page, int count, bool isInGame, const String channel, const String subChannel, const String &extraJson) {}

void MSDKFriend::AddFriend(const MSDKFriendReqInfo &reqInfo, const String &channel) {}
NS_MSDK_SPACE_NO_STL_END

#endif




