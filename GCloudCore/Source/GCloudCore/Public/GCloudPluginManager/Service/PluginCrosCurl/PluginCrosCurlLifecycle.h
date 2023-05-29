//
//  PluginCrosCurlLifecycle.h
//  CrosCurl
//  Query and Call Curl Functions base by CrosCurl
//
//  Created by kiddpeng on 2022/5/19.
//  Copyright © 2022年 gcloud. All rights reserved.
//

#ifndef PluginCrosCurlLifecycle_h
#define PluginCrosCurlLifecycle_h
#import "GCloudPluginManager/GCloudAppLifecycleObserver.h"

/**
  PluginCrosCurlLifecycle 用于注册到插件管理器
 */
@interface PluginCrosCurlLifecycle : NSObject <GCloudAppLifecycleObserver>

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

- (BOOL)handleOpenURL:(NSURL *)url;

- (BOOL)application:(UIApplication *)app
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options;

- (void)applicationDidEnterBackground:(UIApplication *)application;

- (void)applicationWillEnterForeground:(UIApplication *)application;

- (void)applicationDidBecomeActive:(UIApplication *)application;

- (void)applicationWillResignActive:(UIApplication *)application;

- (void)applicationWillTerminate:(UIApplication *)application;

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application;

- (void)application:(UIApplication *)application
    didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

- (void)application:(UIApplication *)application
    didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

- (void)application:(UIApplication *)application
    didReceiveRemoteNotification:(NSDictionary *)userInfo
          fetchCompletionHandler:
              (void (^)(UIBackgroundFetchResult))completionHandler;

@end

#endif /* PluginCrosCurlLifecycle_h */
