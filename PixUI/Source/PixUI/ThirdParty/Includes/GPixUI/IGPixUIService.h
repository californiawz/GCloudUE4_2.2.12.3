//
//  IGPixUIService.h
//  PixUI
//  PixUI API
//
//  Created by kiddpeng on 2022/6/29.
//  Copyright © 2022年 pixui. All rights reserved.
//

#ifndef IGPixUIService_h
#define IGPixUIService_h

#if defined (__APPLE__)
#import <UIKit/UIKit.h>
#include "PxUIView.h"
#endif

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/PluginBase/PluginBase.h"
#include "GCloudPluginManager/Service/Log/ILogger.h"
#include "GCloudPluginManager/Service/PluginCrosCurl/ICurlFunc.h"

GCLOUD_PLUGIN_NAMESPACE

class IGPixUIService : public IPluginService
{
protected:
    virtual ~IGPixUIService(){};
    
public:
    virtual GCloud::ILogger *GetGCloudLogger() = 0;
    virtual GCloud::Plugin::CurlFuncs *GetGCloudCrosCurl() = 0;

#if defined (ANDROID)
    virtual int StartUp(jobject activity) = 0;
    virtual bool IsStartUp() = 0;
    virtual const char *GetPixUIVersion() = 0;
    virtual jobject CreatePxView(jobject activity, int witdh, int height) = 0;
    virtual jobject CreatePxViewHD(jobject activity, int witdh, int height) = 0;
    virtual void AddView(jobject container, jobject view) = 0;
    virtual void RemoveView(jobject container, jobject view) = 0;
    virtual int PageLoadUrl(jobject view, const char* url, bool isHD) = 0;
    virtual int ShutDown() = 0;
#elif defined (__APPLE__)
    virtual const char *GetPixUIVersion() = 0;
    virtual bool IsStartUp() = 0;
    virtual int StartUp(NSString *agent) = 0;
    virtual PxViewHD* CreatePxViewHD(CGRect rect) = 0;
    virtual PxView* CreatePxView(CGRect rect) = 0;
    virtual int PageLoadUrl(PxViewHD* view, NSString *url) = 0;
    virtual int PageLoadUrl(PxView* view, NSString *url) = 0;
    virtual int ShutDown() = 0;
#endif
};

GCLOUD_PLUGIN_NAMESPACE_END

#endif /* IGPixUIService_h */
