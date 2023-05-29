//
//  GCloudAppDelegate.m
//  GCloudSample_Index
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//

#if defined(PLATFORM_IOS) && PLATFORM_IOS

#include "GCloudAppDelegate.h"
#import <Foundation/Foundation.h>
#include "Misc/CoreDelegates.h"
#import "IOSAppDelegate.h"


static GCloudAppDelegate& s_gcloudAppDelegate =  GCloudAppDelegate::GetInstance();

void GCloudAppDelegate::Initialize()
{
    // Trigger GCloud SDK last now that everything is setup
    dispatch_sync(dispatch_get_main_queue(), ^
                   {
                       NSLog(@"initialize gcloud in main queue");
                       //ABase::INetwork::GetInstance();
                   });
}

#endif


