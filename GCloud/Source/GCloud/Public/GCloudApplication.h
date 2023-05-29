//
//  GCloudApplication.h
//  GCloud
//
//  Created by cedar on 17/2/5.
//  Copyright © 2017年 vforkk. All rights reserved.
//
#ifndef _MAC

#ifndef GCloudApplication_h
#define GCloudApplication_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface GCloudApplication : NSObject

+ (GCloudApplication*)sharedInstance;

- (void)initialize;

- (BOOL)handleOpenURL:(NSURL *)url;

- (void)applicationDidEnterBackground:(UIApplication *)application;

- (void)applicationWillEnterForeground:(UIApplication *)application;

- (void)applicationDidBecomeActive:(UIApplication*)application;

- (void)applicationWillResignActive:(UIApplication*)application;

- (void)applicationWillTerminate:(UIApplication*)application;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;

- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler;

@end


#endif /* GCloudApplication_h */

#endif
