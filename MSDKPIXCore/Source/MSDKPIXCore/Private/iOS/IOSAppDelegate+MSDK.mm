//

#define WITH_MSDK 1

#if WITH_MSDK
#ifdef __APPLE__

#import <Foundation/Foundation.h>
#import "IOSAppDelegate.h"//UE4

#include "Misc/CoreDelegates.h"//UE4
#include "MSDKPIXApplicationDelegate.h"
#import "objc/runtime.h"

typedef void(^MSDKPolicyLifecycleEventCallback)(void);
static NSMutableArray<MSDKPolicyLifecycleEventCallback>* events;
static NSCondition *eventsLock;
static bool isPolicyProcessed = false;

static void addLifecycleEvent(void(^callback)()) {
    [eventsLock lock];
    [events addObject:callback];
    [eventsLock unlock];
}

static void invokeLifecycleEvent() {
    if (events) {
        [eventsLock lock];
        NSUInteger count = [events count];
        if (count > 0 && eventsLock) {
            for (MSDKPolicyLifecycleEventCallback callback in events) {
                callback();
            }
            [events removeAllObjects];
        }
        [eventsLock unlock];
    }
}

static void showPolicyPopup(void(^callback)(id param))
{
  Class policyClass = NSClassFromString(@"MSDKPolicy");
  if (policyClass) {
      SEL selector = NSSelectorFromString(@"showPolicy:complete:");
      if (selector) {
          NSMethodSignature *signature = [policyClass methodSignatureForSelector:selector];
          if (signature) {
              NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:signature];
              invocation.target = policyClass;
              invocation.selector = selector;
              void(^policyCallback)(id) = ^(id param) {
                  if (callback) {
                    callback(param);
                  }
              };
              id firstParams = nil;
              [invocation setArgument:&firstParams atIndex:2];
              [invocation setArgument:&policyCallback atIndex:3];
              [invocation invoke];
              return;
          }
      }
  }
  if (callback) {
    callback(nil);
  }
}

static void invokeOriginalMethod(Class clazz, NSString* methodName, void(^callback)(IMP imp, SEL sel)) {
    if (clazz) {
        unsigned int methodCount;
        Method *methodList = class_copyMethodList(clazz, &methodCount);
        IMP currentImp = NULL;
        SEL currentSel = NULL;
        int index = 0;
        for (NSInteger i = 0; i < methodCount; i++) {
            Method method = methodList[i];
            NSString *currentMethodName = [NSString stringWithCString:sel_getName(method_getName(method))
                                            encoding:NSUTF8StringEncoding];
            if ([methodName isEqualToString:currentMethodName]) {
                currentImp = method_getImplementation(method);
                if (currentImp != NULL && index != 0) {
                    currentSel = method_getName(method);
                    callback(currentImp, currentSel);
                    break;
                }
                index++;
            }
        }
        free(methodList);
    }
}

@interface IOSAppDelegate(MSDK)

@end

@implementation IOSAppDelegate(MSDK)

+(void)load {
    eventsLock = [[NSCondition alloc] init];
    events = [NSMutableArray new];
}

- (BOOL)application:(UIApplication*)application willFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
    return YES;
}

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
    showPolicyPopup(^(id param){
        dispatch_async(dispatch_get_main_queue(), ^() {
            invokeOriginalMethod([IOSAppDelegate class], @"application:willFinishLaunchingWithOptions:", ^(IMP imp, SEL sel){
                ((BOOL(*)(id, SEL, id, id))imp)(self, sel, application, launchOptions);
            });
            invokeOriginalMethod([IOSAppDelegate class], @"application:didFinishLaunchingWithOptions:", ^(IMP imp, SEL sel){
                ((BOOL(*)(id, SEL, id, id))imp)(self, sel, application, launchOptions);
            });
            invokeLifecycleEvent();
            isPolicyProcessed = true;
        });
    });
     return YES;
}

- (BOOL)application:(UIApplication*)application openURL:(NSURL*)url sourceApplication:(NSString*)sourceApplication annotation:(id)annotation
{
    if (isPolicyProcessed) {
        invokeOriginalMethod([IOSAppDelegate class], @"application:openURL:sourceApplication:annotation:", ^(IMP imp, SEL sel){
            ((BOOL(*)(id, SEL, id, id, id, id))imp)(self, sel, application, url, sourceApplication, annotation);
        });
    } else {
        addLifecycleEvent([^() {
            invokeOriginalMethod([IOSAppDelegate class], @"application:openURL:sourceApplication:annotation:", ^(IMP imp, SEL sel){
                ((BOOL(*)(id, SEL, id, id, id, id))imp)(self, sel, application, url, sourceApplication, annotation);
            });
        } copy]);
    }
    return YES;
}

// 目前ue4.18、ue4.21、ue4.22、ue4.23、ue4.27、ue5.0都没有这个方法，因此将其注释掉。
// 注意：业务使用的ue版本有这个方法，则需要将下面注释放开。
//- (BOOL)application:(UIApplication*)application openURL:(NSURL*)url options:(NSDictionary<NSString*, id>*)options
//{
//    if (isPolicyProcessed) {
//        invokeOriginalMethod([IOSAppDelegate class], @"application:openURL:options", ^(IMP imp, SEL sel){
//            ((BOOL(*)(id, SEL, id, id, id))imp)(self, sel, application, url, options);
//        });
//    } else {
//        addLifecycleEvent([^() {
//            invokeOriginalMethod([IOSAppDelegate class], @"application:openURL:options", ^(IMP imp, SEL sel){
//                ((BOOL(*)(id, SEL, id, id, id))imp)(self, sel, application, url, options);
//            });
//        } copy]);
//    }
//    return YES;
//}

- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void(^)(NSArray * __nullable restorableObjects))restorationHandler
{
    if (isPolicyProcessed) {
        [[MSDKPIXApplicationDelegate sharedInstance] application:application continueUserActivity:userActivity restorationHandler:restorationHandler];
    } else {
        addLifecycleEvent([^() {
            [[MSDKPIXApplicationDelegate sharedInstance] application:application continueUserActivity:userActivity restorationHandler:restorationHandler];
        } copy]);
    }
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication*)application
{
    if (isPolicyProcessed) {
        invokeOriginalMethod([IOSAppDelegate class], @"applicationDidBecomeActive:", ^(IMP imp, SEL sel){
            ((void(*)(id, SEL, id))imp)(self, sel, application);
        });
    } else {
        addLifecycleEvent([^() {
            invokeOriginalMethod([IOSAppDelegate class], @"applicationDidBecomeActive:", ^(IMP imp, SEL sel){
                ((void(*)(id, SEL, id))imp)(self, sel, application);
            });
        } copy]);
    }
}

- (void)applicationWillResignActive:(UIApplication*)application
{
    if (isPolicyProcessed) {
        invokeOriginalMethod([IOSAppDelegate class], @"applicationWillResignActive:", ^(IMP imp, SEL sel){
            ((void(*)(id, SEL, id))imp)(self, sel, application);
        });
    }
}

- (void)applicationDidEnterBackground:(UIApplication*)application
{
    if (isPolicyProcessed) {
        invokeOriginalMethod([IOSAppDelegate class], @"applicationDidEnterBackground:", ^(IMP imp, SEL sel){
            ((void(*)(id, SEL, id))imp)(self, sel, application);
        });
    }
}

- (void)applicationWillEnterForeground:(UIApplication*)application
{
    if (isPolicyProcessed) {
        invokeOriginalMethod([IOSAppDelegate class], @"applicationWillEnterForeground:", ^(IMP imp, SEL sel){
            ((void(*)(id, SEL, id))imp)(self, sel, application);
        });
    }
}

- (void)applicationWillTerminate:(UIApplication*)application
{
    if (isPolicyProcessed) {
        invokeOriginalMethod([IOSAppDelegate class], @"applicationWillTerminate:", ^(IMP imp, SEL sel){
            ((void(*)(id, SEL, id))imp)(self, sel, application);
        });
    }
}

@end

#endif
#endif

