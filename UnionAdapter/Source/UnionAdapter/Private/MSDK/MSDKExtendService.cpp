//
//  MSDKExtendService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/06/24.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "GUAExtendService.h"
#include "MSDKExtend.h"
#include "MSDKStructUtility.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

class MSDKExtendObserver : public GCloud::MSDKSpace::NoSTL::MSDKExtendObserver
{
public:
	static MSDKExtendObserver Instance;
	GUAExtendObserver* extend_observer_;
public:
	MSDKExtendObserver() :extend_observer_(nullptr) {}

	void OnExtendNotify(const GCloud::MSDKSpace::NoSTL::MSDKExtendRet &msdk_extend_ret)
	{
		GUAExtendResult gua_extend_ret;
		MSDKStructUtility::ConvertExtendRetToGUA(msdk_extend_ret, gua_extend_ret);

		if (MSDKExtendObserver::Instance.extend_observer_ != nullptr) 
		{
			MSDKExtendObserver::Instance.extend_observer_->OnExtendNotify(gua_extend_ret);
		}
		else
		{
            LOG_DEBUG("MSDKExtendObserver::Instance.extend_observer_ is nullptr");
		}

	}
};

MSDKExtendObserver MSDKExtendObserver::Instance;

void GUAExtendService::SetExtendObserver(GUAExtendObserver *observer)
{
	MSDKExtendObserver::Instance.extend_observer_ = observer;
#if PLATFORM_IOS || PLATFORM_ANDROID
	GCloud::MSDKSpace::NoSTL::MSDKExtend::SetExtendObserver(&MSDKExtendObserver::Instance);
#endif
}

std::string GUAExtendService::Invoke(
	const std::string& channel, 
	const std::string& extend_method_name, 
	const std::string& params_json)
{
    return GCloud::MSDKSpace::NoSTL::MSDKExtend::Invoke(channel, extend_method_name, params_json);
}

GUA_NAMESPACE_END