//
//  GCloudAppDelegate.m
//  GCloudSample_Index
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//

#if defined(PLATFORM_IOS) && PLATFORM_IOS

#include "GCloudCoreAppDelegate.h"
#import <Foundation/Foundation.h>
#include "Misc/CoreDelegates.h"
#import "IOSAppDelegate.h"
#include "GCloudAppLifecycle.h"
#include <GCloudCore/INetwork.h>

#include "AllLifecycleRegister.h"

static void OnGCloudCoreOpenURL(UIApplication* application, NSURL* url, NSString* sourceApplication, id annotation)
{
    NSLog(@"OnGCloudCoreOpenURL");
    
    [[GCloudAppLifecycle sharedInstance] application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
    
}

static void OnGCloudCoreAppDidBecomeActive()
{
    NSLog(@"OnGCloudCoreAppDidBecomeActive");
    
    dispatch_async(dispatch_get_main_queue(), ^
                   {
                       UIApplication* sharedApp = [UIApplication sharedApplication];
                       [[GCloudAppLifecycle sharedInstance] applicationDidBecomeActive: sharedApp];
                   });
}

static void OnGCloudCoreAppWillResignActive()
{
    NSLog(@"OnGCloudCoreAppWillResignActive");
    
    dispatch_async(dispatch_get_main_queue(), ^
                   {
                       UIApplication* sharedApp = [UIApplication sharedApplication];
                       [[GCloudAppLifecycle sharedInstance] applicationWillResignActive: sharedApp];
                   });
}


static void OnGCloudCoreAppDidEnterBackground()
{
    NSLog(@"OnGCloudCoreAppDidEnterBackground");
    
    dispatch_async(dispatch_get_main_queue(), ^
                   {
                       UIApplication* sharedApp = [UIApplication sharedApplication];
                       [[GCloudAppLifecycle sharedInstance] applicationDidEnterBackground: sharedApp];
                   });
}

static void OnGCloudCoreAppWillEnterForeground()
{
    NSLog(@"OnGCloudCoreAppWillEnterForeground");
    
    dispatch_async(dispatch_get_main_queue(), ^
                   {
                       UIApplication* sharedApp = [UIApplication sharedApplication];
                       [[GCloudAppLifecycle sharedInstance] applicationWillEnterForeground: sharedApp];
                   });
}


static void OnGCloudCoreAppWillTerminate()
{
    NSLog(@"OnGCloudCoreAppWillTerminate");
    
    dispatch_async(dispatch_get_main_queue(), ^
                   {
                       UIApplication* sharedApp = [UIApplication sharedApplication];
                       [[GCloudAppLifecycle sharedInstance] applicationWillTerminate: sharedApp];
                   });
}

static void ApplicationRegisteredForRemoteNotificationsDelegate_Handler(TArray<uint8> inArray)
{
    NSLog(@"ApplicationRegisteredForRemoteNotificationsDelegate_Handler");
    
    const char* data = (char*)inArray.GetData();

    [[GCloudAppLifecycle sharedInstance] application:[UIApplication sharedApplication] didRegisterForRemoteNotificationsWithDeviceToken: [ NSData dataWithBytes: data
                                                                                                          length:inArray.Num()]];
}


static void ApplicationFailedToRegisterForRemoteNotificationsDelegate_Handler(FString inFString)
{
    NSLog(@"ApplicationFailedToRegisterForRemoteNotificationsDelegate_Handler");
    [[GCloudAppLifecycle sharedInstance] application:[UIApplication sharedApplication] didFailToRegisterForRemoteNotificationsWithError: [NSError errorWithDomain: [NSString stringWithUTF8String: TCHAR_TO_ANSI((*inFString))]
                                                                                                             code: 1
                                                                                                         userInfo:nil] ];
}

static void ApplicationReceivedRemoteNotificationDelegate_Handler(FString inFString, int32 inAppState)
{
    NSLog(@"ApplicationReceivedRemoteNotificationDelegate_Handler");
    
    NSString* jsonString = [NSString stringWithUTF8String: TCHAR_TO_UTF8(*inFString)];

    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *err;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                        options:NSJSONReadingMutableContainers
                                                          error:&err];
    if(err)
    {
        //NSLog(@"json deserialization failed：%@",err);
        dic = nil;
    }
    else
    {
        //NSLog(@"ApplicationReceivedRemoteNotificationDelegate_Handler: userInfo: %@", dic);
    }

    [[GCloudAppLifecycle sharedInstance] application:[UIApplication sharedApplication] didReceiveRemoteNotification:dic];
}

static void ApplicationReceivedLocalNotificationDelegate_Handler(FString inFString, int32 inInt, int32 inAppState)
{
    
}

#ifdef ENABLE_BGDOWNLOAD_FOR_UE4_22_OR_LOWER
//UE4.18 - 4.22; need change UE engine source codes
static void ApplicationHandleEventsForBackgroundURLSession_Handler_TwoParam(NSString* identifier, NSDictionary* dict)
{   
    NSLog(@"ApplicationHandleEventsForBackgroundURLSession_Handler");
    [[GCloudAppLifecycle sharedInstance] application:[UIApplication sharedApplication] handleEventsForBackgroundURLSession:identifier completionHandler:[dict objectForKey:@"handler"]];
}
#endif

#ifdef ENABLE_BGDOWNLOAD_FOR_UE4_23_OR_LATER
//UE4.23+
static void ApplicationHandleEventsForBackgroundURLSession_Handler_OneParam(FString fidentifier)
{   
    NSLog(@"ApplicationHandleEventsForBackgroundURLSession_Handler");
    NSString* identifier = [NSString stringWithUTF8String: TCHAR_TO_UTF8(*fidentifier)];
    [[GCloudAppLifecycle sharedInstance] application:[UIApplication sharedApplication] handleEventsForBackgroundURLSession:identifier completionHandler:[IOSAppDelegate GetDelegate].BackgroundSessionEventCompleteDelegate];
}
#endif

static GCloudCoreAppDelegate& s_GCloudCoreAppDelegate =  GCloudCoreAppDelegate::GetInstance();

void GCloudCoreAppDelegate::InitializeOpenUrl()
{
#ifdef EXTEND_OPENURL
    NSLog(@"GCloudCoreAppDelegate::InitializeOpenUrl");
    //FIOSCoreDelegates::GetExtendOnOpenURL().AddStatic(&OnGCloudCoreOpenURL);
#endif
}

void GCloudCoreAppDelegate::Initialize()
{
    NSLog(@"GCloudCoreAppDelegate::Initialize");
    
#ifndef EXTEND_OPENURL
    FIOSCoreDelegates::OnOpenURL.AddStatic(&OnGCloudCoreOpenURL);

  #ifdef ENABLE_BGDOWNLOAD_FOR_UE4_22_OR_LOWER
    //UE4.18 - 4.22; need change UE engine source codes
    FIOSCoreDelegates::OnApplicationHandleEventsForBackgroundURLSessionDelegate.AddStatic(&ApplicationHandleEventsForBackgroundURLSession_Handler_TwoParam);
  #endif

  #ifdef ENABLE_BGDOWNLOAD_FOR_UE4_23_OR_LATER
    //UE4.23+
    FCoreDelegates::ApplicationBackgroundSessionEventDelegate.AddStatic(&ApplicationHandleEventsForBackgroundURLSession_Handler_OneParam);
  #endif
#endif
    
    FCoreDelegates::ApplicationHasReactivatedDelegate.AddStatic(&OnGCloudCoreAppDidBecomeActive);
    FCoreDelegates::ApplicationWillDeactivateDelegate.AddStatic(&OnGCloudCoreAppWillResignActive);
    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddStatic(&OnGCloudCoreAppDidEnterBackground);
    FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddStatic(&OnGCloudCoreAppWillEnterForeground);
    FCoreDelegates::ApplicationWillTerminateDelegate.AddStatic(&OnGCloudCoreAppWillTerminate);

    FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.AddStatic(&ApplicationRegisteredForRemoteNotificationsDelegate_Handler);
    FCoreDelegates::ApplicationFailedToRegisterForRemoteNotificationsDelegate.AddStatic(&ApplicationFailedToRegisterForRemoteNotificationsDelegate_Handler);
    FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.AddStatic(&ApplicationReceivedRemoteNotificationDelegate_Handler);

    // Trigger GCloudCore last now that everything is setup
    dispatch_sync(dispatch_get_main_queue(), ^
                   {
                       NSLog(@"initialize gcloudcore in main queue");
                       //ensure initialize CNetwork in main queue
                       ABase::INetwork::GetInstance();
                       
                       UIApplication* sharedApp = [UIApplication sharedApplication];
                       NSDictionary* launchDict = [IOSAppDelegate GetDelegate].launchOptions;
                       [[GCloudAppLifecycle sharedInstance] application:sharedApp didFinishLaunchingWithOptions : launchDict];
                   });
}

#endif


