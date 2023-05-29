//
//  GCloudAppDelegate.m
//  GCloudSample_Index
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//
#include "GCloudAppDelegate.h"


GCloudAppDelegate& GCloudAppDelegate::GetInstance()
{
    static GCloudAppDelegate instance;
    return instance;
}

GCloudAppDelegate::GCloudAppDelegate()
{
}

#if defined(PLATFORM_IOS) && PLATFORM_IOS

#else

void GCloudAppDelegate::Initialize()
{
}

#endif

