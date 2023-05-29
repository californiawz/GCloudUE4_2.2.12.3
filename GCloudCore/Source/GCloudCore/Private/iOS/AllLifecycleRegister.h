#ifndef AllLifecycleRegister_h
#define AllLifecycleRegister_h


#import <GCloudCore/GCloudAppLifecycleObserver.h>

//PluginCrosCurl
#import "PluginCrosCurlLifecycle.h"
REGISTER_LIFECYCLE_OBSERVER(PluginCrosCurlLifecycle);

//TDM
#import "PluginReportLifecycle.h"
REGISTER_LIFECYCLE_OBSERVER(PluginReportLifecycle);

//PixUI
#import "GPixUILifecycle.h"
REGISTER_LIFECYCLE_OBSERVER(GPixUILifecycle);

//GCloud
#import "GCloudAppLifecycleListener.h"
REGISTER_LIFECYCLE_OBSERVER(GCloudAppLifecycleListener);

//GVoice
#import "PluginGVoiceLifecycle.h"
REGISTER_LIFECYCLE_OBSERVER(PluginGVoiceLifecycle);

//MSDKPIXCore
#import "PluginMSDKLifecycle.h"
REGISTER_LIFECYCLE_OBSERVER(PluginMSDKLifecycle);


#endif