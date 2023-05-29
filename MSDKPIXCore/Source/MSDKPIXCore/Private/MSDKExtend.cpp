//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKExtend.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

void MSDKExtend::SetExtendObserver(MSDKExtendObserver *extendObserver) {}

String MSDKExtend::Invoke(const String& channel, const String& extendMethodName, const String& paramsJson) { return ""; }

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKExtend::SetExtendObserver(MSDKExtendObserver *extendObserver) {}

String MSDKExtend::Invoke(const String& channel, const String& extendMethodName, const String& paramsJson) { return ""; }

NS_MSDK_SPACE_NO_STL_END

#endif




