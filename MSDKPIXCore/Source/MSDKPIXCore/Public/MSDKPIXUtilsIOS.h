//
//  MSDKPIXUtilsIOS.h
//  MSDKPIXCore
//
//  Created by xiaoxuzheng on 8/2/21.
//  Copyright © 2021 MSDK. All rights reserved.
//

#ifndef MSDKPIXUtilsIOS_h
#define MSDKPIXUtilsIOS_h
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define GET_NSSTRING(cString) [NSString stringWithUTF8String:(cString ? cString : "")]

/**
 IOS common utility
 */
@interface MSDKPIXUtilsIOS : NSObject

+ (BOOL)swizzlingOriginalClass:(Class)originalClass
                 swizzledClass:(Class)swizzledClass
                   originalSEL:(SEL)originalSEL
                   swizzledSEL:(SEL)swizzledSEL;

+ (BOOL)addOriginalClass:(Class)originalClass swizzledClass:(Class)swizzledClass originalSEL:(SEL)originalSEL swizzledSEL:(SEL)swizzledSEL ;

+ (UIViewController *)topViewController:(UIViewController *)rootViewController;

+ (UIViewController *)getRootViewController;

+ (NSString *)jsonStringFromDict:(NSDictionary *)dict prettyPrint:(BOOL)prettyPrint;

+ (UIInterfaceOrientationMask)getSupportedInterfaceOrientations;

+ (UIViewController *)getRootViewController:(UIWindow *)keyWindow;

+ (NSDictionary *)dictFromJsonString:(NSString *)jsonString;

+ (void)loadImageWithUri:(NSString *)imageUri complete:(void(^)(NSData *image))completeHandle;
@end


#endif /* MSDKPIXUtilsIOS_h */
