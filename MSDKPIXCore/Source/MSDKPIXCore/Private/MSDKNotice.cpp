//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKNotice.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

void MSDKNotice::SetNoticeObserver(MSDKNoticeObserver *noticeObserver) {}

String MSDKNotice::LoadPRVNoticeData(const String &noticeGroup, const String &language, int region,
                                 const String &partition, const String &extra) { return ""; }

NS_MSDK_END


NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKNotice::SetNoticeObserver(MSDKNoticeObserver *noticeObserver) {}

NS_MSDK_SPACE_NO_STL_END
#endif




