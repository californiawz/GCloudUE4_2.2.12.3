//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKPush.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

void MSDKPush::SetPushObserver(MSDKPushObserver *pushObserver) {}

void MSDKPush::AddLocalNotificationPRV(const String &channel, const InnerLocalNotification &notification) {}

void MSDKPush::RegisterPush(const String &channel, const String &account) {}

void MSDKPush::UnregisterPush(const String &channel) {}

void MSDKPush::SetTag(const String &channel, const String &tag) {}

void MSDKPush::DeleteTag(const String &channel, const String &tag) {}
    
void MSDKPush::SetAccount(const String &channel, const String &account) {}
    
void MSDKPush::DeleteAccount(const String &channel, const String &account) {}

void MSDKPush::ClearLocalNotifications(const String &channel){}

NS_MSDK_END


NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKPush::SetPushObserver(MSDKPushObserver *pushObserver) {}

void MSDKPush::RegisterPush(const String &channel, const String &account) {}

void MSDKPush::UnregisterPush(const String &channel) {}

void MSDKPush::SetTag(const String &channel, const String &tag) {}

void MSDKPush::DeleteTag(const String &channel, const String &tag) {}

void MSDKPush::SetAccount(const String &channel, const String &account) {}

void MSDKPush::DeleteAccount(const String &channel, const String &account) {}

void MSDKPush::ClearLocalNotifications(const String &channel){}

NS_MSDK_SPACE_NO_STL_END

#endif




