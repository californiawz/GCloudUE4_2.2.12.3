//
//  Apollo.h
//  Apollo
//
//  Created by vforkk on 4/7/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//
#ifndef _MAC

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>



@interface ABaseApplication : NSObject

+ (ABaseApplication*)sharedInstance;

- (BOOL)handleOpenURL:(NSURL *)url;

- (void)applicationDidEnterBackground:(UIApplication *)application;

- (void)applicationWillEnterForeground:(UIApplication *)application;

- (void)applicationDidBecomeActive:(UIApplication*)application;

- (void)applicationWillResignActive:(UIApplication*)application;

- (void)applicationWillTerminate:(UIApplication*)application;

- (BOOL)applicationContinueUserActivity:(UIApplication*)application Activity:(NSUserActivity *)userActivity;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;

- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler;

@property(nonatomic, strong) UIViewController* rootVC;
@property(nonatomic, strong) NSMutableArray* observers;
@end


@interface ABaseApplicationObserver : NSObject

- (void)initialize;

- (BOOL)handleOpenURL:(NSURL *)url;

- (void)applicationDidEnterBackground:(UIApplication *)application;

- (void)applicationWillEnterForeground:(UIApplication *)application;

- (void)applicationDidBecomeActive:(UIApplication*)application;

- (void)applicationWillResignActive:(UIApplication*)application;

- (void)applicationWillTerminate:(UIApplication*)application;

- (BOOL)applicationContinueUserActivity:(UIApplication*)application Activity:(NSUserActivity *)userActivity;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;

- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler;

@end

typedef void (^ABaseApplicationObserverCallback)(ABaseApplicationObserver* observer);

#define LAUNCH_OC(NAME) class C##NAME##Launch\
{\
public:\
C##NAME##Launch()\
{\
static NAME* g_Instance = nil;\
if (g_Instance == nil)\
{\
g_Instance = [[NAME alloc] init];\
}\
}\
};\
static C##NAME##Launch __g_Launch__;
#endif
