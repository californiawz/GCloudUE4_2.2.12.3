//
//  MSDKNoticeService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/06/24.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "GUANoticeService.h"
#include "MSDKNotice.h"
#include "MSDKStructUtility.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

class MSDKNoticeObserver : public GCloud::MSDKSpace::NoSTL::MSDKNoticeObserver
{
public:
    static MSDKNoticeObserver Instance;
    GUANoticeObserver* notice_observer_;
public:
    MSDKNoticeObserver() : notice_observer_(nullptr){

    }

    void OnLoadNoticeData(const GCloud::MSDKSpace::NoSTL::MSDKNoticeRet &msdk_notice_ret)
    {
		GUANoticeResult gua_notice_result;
		MSDKStructUtility::ConvertNoticeRetToGUA(msdk_notice_ret, gua_notice_result);

		if (MSDKNoticeObserver::Instance.notice_observer_ != nullptr) 
		{
			MSDKNoticeObserver::Instance.notice_observer_->OnLoadNoticeData(gua_notice_result);
		}
		else
		{
			LOG_DEBUG("MSDKNoticeObserver::Instance.notice_observer_ is nullptr");
		}

    }
};

MSDKNoticeObserver MSDKNoticeObserver::Instance;

void GUANoticeService::SetNoticeObserver(GUANoticeObserver *observer)
{
	MSDKNoticeObserver::Instance.notice_observer_ = observer;
	GCloud::MSDKSpace::NoSTL::MSDKNotice::SetNoticeObserver(&MSDKNoticeObserver::Instance);
}

std::string GUANoticeService::LoadNoticeData(
	const std::string &notice_group, 
	const std::string &language, 
	const std::string &region,
	const std::string &partition, 
	const std::string &extra_json)
{
#if PLATFORM_IOS || PLATFORM_ANDROID || MSDK_PLATFORM_WINDOWS
    return GCloud::MSDKSpace::NoSTL::MSDKNotice::LoadNoticeData(notice_group, language, atoi(region.c_str()), partition, extra_json);
#endif
	return "";
}

GUA_NAMESPACE_END