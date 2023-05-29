//
//  GCloudAppLifecycleObserver.h
//  GCloudPluginManager
//
//  Created by cedar on 2018/8/8.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef GCloudAppLifecycleObserver_h
#define GCloudAppLifecycleObserver_h

#import "TargetConditionals.h"
#if TARGET_OS_IOS || TARGET_OS_IPHONE

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol GCloudAppLifecycleObserver<NSObject>

@required
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

@optional
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

@end


//wrapper
static void gs_GCloudAppLifecycleAddObserver(void* observer)
{
    id wrapper = [[NSClassFromString(@"GCloudAppLifecycleWrapper") alloc] init];

    if(nil!=wrapper && [wrapper respondsToSelector:@selector(addObserver:)]){
        [wrapper performSelector:@selector(addObserver:) withObject:(__bridge id)observer];
    }
}

static void gs_GCloudAppLifecycleRemoveObserver(void* observer)
{
    id wrapper = [[NSClassFromString(@"GCloudAppLifecycleWrapper") alloc] init];
    
    if(nil!=wrapper && [wrapper respondsToSelector:@selector(removeObserver:)]){
        [wrapper performSelector:@selector(removeObserver:) withObject:((__bridge id)observer)];
    }
}

NS_ASSUME_NONNULL_END

#define REGISTER_LIFECYCLE_OBSERVER(CLASS)\
class C##CLASS##LifeObserver\
{\
public:\
C##CLASS##LifeObserver()\
{\
static CLASS* g_Instance = nil;\
if (g_Instance == nil)\
{\
g_Instance = [[CLASS alloc] init];\
}\
gs_GCloudAppLifecycleAddObserver((__bridge void*)g_Instance);\
}\
};\
static C##CLASS##LifeObserver __g_##CLASS##LifeObserver__;

void g_GCloudCoreManualHook(const char * _Nonnull className);
#define GCLOUDCORE_HOOK_LIFECYCLE(CLASS_NAME)\
class CGCloudCoreLifeHooker\
{\
public:\
CGCloudCoreLifeHooker()\
{\
g_GCloudCoreManualHook(#CLASS_NAME);\
}\
};\
static CGCloudCoreLifeHooker __g_##CLASS_NAME##_GCloudCoreLifeHooker__;


#endif

#endif /* GCloudAppLifecycleObserver_h */
