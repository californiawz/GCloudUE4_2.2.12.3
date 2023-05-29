//
//  PluginBase.h
//  GCloudPluginManager
//
//  Created by cedar on 2018/7/28.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef PluginBase_h
#define PluginBase_h

#if defined (ANDROID)
#include "GCloudPluginManager/PluginBase/PluginBase_Android.h"
#elif defined (__APPLE__)
#include "GCloudPluginManager/PluginBase/PluginBase_iOS.h"
#endif


#if defined (ANDROID)
#define REGISTER_GCLOUD_PLUGIN        REGISTER_GCLOUD_PLUGIN_A
#define GET_GCLOUD_PLUGIN_MANAGER     GET_GCLOUD_PLUGIN_MANAGER_A
#define GET_GCLOUD_SERVICE_MANAGER    GET_GCLOUD_SERVICE_MANAGER_A

#elif defined (__APPLE__)
#define REGISTER_GCLOUD_PLUGIN        REGISTER_GCLOUD_PLUGIN_I
#define GET_GCLOUD_PLUGIN_MANAGER     GET_GCLOUD_PLUGIN_MANAGER_I
#define GET_GCLOUD_SERVICE_MANAGER    GET_GCLOUD_SERVICE_MANAGER_I
#endif


#endif /* PluginBase_h */
