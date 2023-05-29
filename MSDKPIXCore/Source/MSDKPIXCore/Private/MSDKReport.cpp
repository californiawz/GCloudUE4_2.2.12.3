//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKReport.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

bool MSDKReport::Init(const String &channels) { return false; }

void MSDKReport::SetPushToken(const String &pushToken) {}

std::string MSDKReport::GetInstanceID(const String &channel) { return ""; }

NS_MSDK_END


NS_MSDK_SPACE_NO_STL_BEGIN

bool MSDKReport::Init(const String &channels) { return false; }

void MSDKReport::SetPushToken(const String &pushToken) {}

String MSDKReport::GetInstanceID(const String &channel) { return ""; }

NS_MSDK_SPACE_NO_STL_END

#endif




