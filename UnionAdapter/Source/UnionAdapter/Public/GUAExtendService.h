//
//  GUAWebViewService.h
//  GUASample
//
//  Created by tafflin on 2022/6/9.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

class GUA_EXTERN GUAExtendResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult; 
public:
    GUAExtendResult()
    {
    }

    // Mark the callback of which channel
    std::string channel;
    // Mark the callback of which method name in the extend plug-in
    std::string extend_method_name;
};

class GUA_EXTERN GUAExtendObserver
{
public:
    virtual ~GUAExtendObserver() {};

    virtual void OnExtendNotify(const GUAExtendResult &extend_ret) {};
};

class GUA_EXTERN GUAExtendService
{
public:
	/**
	* @brief Set extend observer
	*
	* @param extend_observer	[required]GUAExtendObserver
	*/
    static void SetExtendObserver(GUAExtendObserver *extend_observer);

	/**
	* @brief Invoke method with json
	*
	* @param channel			[required] channel name, such as "Facebook", "Twitter" etc
	* @param extend_method_name	[required] target methond name
	* @param extra_json			[required] extra params with json format
	*/
    static std::string Invoke(
		const std::string &channel, 
		const std::string &extend_method_name, 
		const std::string &params_json);
};

GUA_NAMESPACE_END
