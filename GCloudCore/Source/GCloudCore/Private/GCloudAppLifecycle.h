//
//  GCloudAppLifecycle.h
//  GCloudPluginManager
//
//  Created by cedar on 2018/8/8.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef GCloudAppLifecycle_h
#define GCloudAppLifecycle_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#include "GCloudCore/GCloudAppLifecycleObserver.h"

NS_ASSUME_NONNULL_BEGIN

@interface GCloudAppLifecycle : NSObject

+ (GCloudAppLifecycle*) sharedInstance;

- (void) addObserver:(NSObject<GCloudAppLifecycleObserver>*) observer;

- (void) removeObserver:(NSObject<GCloudAppLifecycleObserver>*) observer;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

- (BOOL)handleOpenURL:(NSURL *)url;

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

- (void)applicationDidEnterBackground:(UIApplication *)application;

- (void)applicationWillEnterForeground:(UIApplication *)application;

- (void)applicationDidBecomeActive:(UIApplication*)application;

- (void)applicationWillResignActive:(UIApplication*)application;

- (void)applicationWillTerminate:(UIApplication*)application;

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application;

- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;

#pragma clang diagnostic push  
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification;

#pragma clang diagnostic pop

- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray * _Nullable))restorationHandler;

- (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(nullable UIWindow *)window  NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;

- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)(void))completionHandler;

@property(nonatomic, strong) NSMutableArray* observers;
@end

NS_ASSUME_NONNULL_END


#endif /* GCloudAppLifecycle_h */
