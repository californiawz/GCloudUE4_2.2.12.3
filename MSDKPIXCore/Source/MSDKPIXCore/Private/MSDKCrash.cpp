//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKCrash.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

void MSDKCrash::SetCrashObserver(MSDKCrashObserver *crashObserver) {}

void MSDKCrash::ReportExceptionPRV(int type, const String &exceptionName, const String &exceptionMsg, const String &exceptionStack, Vector<KVPair> &extInfo) {}

void MSDKCrash::LogInfo(int level, const String &tag, const String &log) {}

void MSDKCrash::SetUserValue(const String &key, const String &value) {}

void MSDKCrash::SetUserId(const String &userId) {}
	
void MSDKCrash::CloseCrashReport() {}

NS_MSDK_END


NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKCrash::SetCrashObserver(MSDKCrashObserver *crashObserver) {}

void MSDKCrash::LogInfo(int level, const String &tag, const String &log) {}

void MSDKCrash::SetUserValue(const String &key, const String &value) {}

void MSDKCrash::SetUserId(const String &userId) {}

void MSDKCrash::CloseCrashReport() {}

NS_MSDK_SPACE_NO_STL_END

#endif




