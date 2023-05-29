//
//  GCloudCoreAppDelegate.m
//  GCloudSample_Index
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//
#include "GCloudCoreAppDelegate.h"


GCloudCoreAppDelegate& GCloudCoreAppDelegate::GetInstance()
{
    static GCloudCoreAppDelegate instance;
    return instance;
}

GCloudCoreAppDelegate::GCloudCoreAppDelegate()
{
    InitializeOpenUrl();
}

#if defined(PLATFORM_IOS) && PLATFORM_IOS

#else

void GCloudCoreAppDelegate::Initialize()
{
}
void GCloudCoreAppDelegate::InitializeOpenUrl()
{
}

#endif

