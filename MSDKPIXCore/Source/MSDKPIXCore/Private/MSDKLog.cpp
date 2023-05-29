//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKLog.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

MSDKLog::MSDKLog(ILogLevel level, const char *tag, const char *fileName, const char *funcName, int line) {}

MSDKLog::~MSDKLog() {}

void MSDKLog::usingGCloud(bool useGCloudLog) {}

MSDKLog& MSDKLog::logging(const char* seqID, const char *fmt, ...) {return *this;}

NS_MSDK_END
#endif




