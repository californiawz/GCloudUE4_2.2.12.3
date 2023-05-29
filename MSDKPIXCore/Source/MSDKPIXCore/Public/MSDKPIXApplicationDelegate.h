//
//  MSDKPIXApplicationDelegate.h
//  MSDKPIXCore
//
//  Created by godmanzheng on 8/2/21.
//  Copyright © 2021 MSDK. All rights reserved.
//

#ifndef MSDKPIXApplicationDelegate_h
#define MSDKPIXApplicationDelegate_h


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


extern const char *MSDKPIX_DID_FINISH_LAUNCHING;     //methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_LAUNCH_OPTIONS;


extern const char *MSDKPIX_OPEN_URL_SOURCE;         //methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_URL;
extern const char *MSDKPIX_SOURCE_APPLICATION;
extern const char *MSDKPIX_ANNOTATION;


extern const char *MSDKPIX_OPEN_URL_OPTIONS;        //methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_URL;
extern const char *MSDKPIX_OPTIONS;


extern const char *MSDKPIX_CONTINUE_USER_ACTIVITY;  //methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_USER_ACTIVITY;
extern const char *MSDKPIX_RESTORATION_HANDLER;


extern const char *MSDKPIX_DID_ENTER_BACKGROUND;    //methodName
extern const char *MSDKPIX_NOTIFICATION;


extern const char *MSDK_DID_BECOME_ACTIVE;          //methodName
extern const char *MSDKPIX_NOTIFICATION;


extern const char *MSDK_WILL_CHANGE_STATUSBAR_ORIENTATION;  //methodName
extern const char *MSDKPIX_NOTIFICATION;


extern const char *MSDK_DID_REGISTER_REMOTE_NOTIFICATION;   //methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_DEVICE_TOKEN;


extern const char *MSDK_FAIL_REGISTER_REMOTE_NOTIFICATION;  //methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_ERROR;


extern const char *MSDK_DID_RECEIVE_REMOTE_NOTIFICATION;    //methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_USER_INFO;


extern const char *MSDK_DID_RECEIVE_REMOTE_NOTIFICATION_FETCHCOMPLETE;//methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_USER_INFO;
extern const char *MSDKPIX_COMPLETION_HANDLER;


extern const char *MSDK_DID_RECEIVE_LOCAL_NOTIFICATION;        //methodName
extern const char *MSDKPIX_APPLICATION;
extern const char *MSDKPIX_NOTIFICATION;


/**
    MSDK lifecycle event handler, application should call according method from
    ApplicationDelegate object, making sure all plugins got notified
 */
@interface MSDKPIXApplicationDelegate : NSObject

/*!
 @abstract get singleton object
 */
+ (instancetype)sharedInstance;

- (NSObject *)paramWithName:(const char*)paramName forMethod:(const char*)methodName uniqueID:(NSInteger)uniequeID;

- (void)removeParamsForMethodID:(NSInteger)uniqueID;

/*!
 @abstract MSDK SDK application entry,
 @discussion should be called inside [UIApplicationDelegate application:didFinishLaunchingWithOptions:]
 @param application     application
 @param launchOptions   launchOptions
 @result YES
 */
- (BOOL)application:(UIApplication *)application
didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

#pragma mark - Open URL

- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

//for iOS9+
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary *)options;
#pragma mark - Orientation

- (UIInterfaceOrientationMask)application:(UIApplication *)application
  supportedInterfaceOrientationsForWindow:(UIWindow *)window;

- (BOOL)isCallOrientation;

#pragma mark - APNS Push

- (void)application:(UIApplication *)application
didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

- (void)application:(UIApplication *)application
didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

- (void)application:(UIApplication *)application
didReceiveRemoteNotification:(NSDictionary *)userInfo;

- (void)application:(UIApplication *)application
didReceiveRemoteNotification:(NSDictionary *)userInfo
fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (void)application:(UIApplication *)application
didReceiveLocalNotification:(UILocalNotification *)notification;

#pragma clang diagnostic pop

- (BOOL)application:(UIApplication *)application
continueUserActivity:(NSUserActivity *)userActivity
 restorationHandler:(void (^)(NSArray * _Nullable))restorationHandler;

NS_ASSUME_NONNULL_END




@end


#endif /* MSDKPIXApplicationDelegate_h */
