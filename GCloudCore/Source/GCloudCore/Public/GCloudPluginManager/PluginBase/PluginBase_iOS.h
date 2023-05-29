//
//  PluginBase_iOS.h
//  GCloudPluginManager
//
//  Created by cedar on 2018/7/31.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef PluginBase_iOS_h
#define PluginBase_iOS_h

#ifdef __APPLE__
#import <Foundation/Foundation.h>

#include "GCloudPluginManager/IPluginManager.h"

GCLOUD_PLUGIN_NAMESPACE

static void* gs_GetGCloudPluginManager()
{
    void* pMgr = NULL;
    id wrapper = [[NSClassFromString(@"PluginUtilsWrapper") alloc] init];
    
    if(nil!=wrapper && [wrapper respondsToSelector:@selector(getNativePluginManager)]){
        pMgr = (__bridge void*)[wrapper performSelector:@selector(getNativePluginManager)];
    }
    NSLog(@"gs_GetGCloudPluginManager pluginManager:%p", pMgr);
    return pMgr;
}


class PluginBase : public GCloud::Plugin::IPlugin
{
protected:
    PluginBase():_pluginManager(NULL){}
    ~PluginBase(){};

public:

    void GetCachePluginManager()
    {
        if(NULL == _pluginManager){
            _pluginManager = (GCloud::Plugin::IPluginManager*)gs_GetGCloudPluginManager();
        }
    }

    GCloud::Plugin::IPluginManager* GetPluginManager() const
    {
        return _pluginManager;
    }

    void RegisterPlugin(GCloud::Plugin::IPlugin* plugin)
    {
        if(!plugin){
            NSLog(@"PluginBase::RegisterPlugin plugin is null");
            return;
        }
        GCloud::Plugin::IPluginManager* pluginManager = GetPluginManager();
        if(pluginManager){
            pluginManager->Install(plugin);
            NSLog(@"PluginBase::RegisterPlugin PluginManager:%p , IPlugin:%p", pluginManager, plugin);
        }
    }
protected:
    GCloud::Plugin::IPluginManager* _pluginManager;
};


#define REGISTER_GCLOUD_PLUGIN_I(CLASS)\
do{\
GCloud::Plugin::PluginBase*  pluginBase = (GCloud::Plugin::PluginBase*)CLASS::GetInstance();\
if(NULL!=pluginBase){\
pluginBase->GetCachePluginManager();\
pluginBase->RegisterPlugin(CLASS::GetInstance());\
}\
}\
while(0)

#define GET_GCLOUD_PLUGIN_MANAGER_I(PTR_REF, CLASS)\
PTR_REF = NULL;\
GCloud::Plugin::PluginBase*  pluginBase = (GCloud::Plugin::PluginBase*)CLASS::GetInstance();\
if(NULL!=pluginBase){\
PTR_REF = pluginBase->GetPluginManager();\
}

#define GET_GCLOUD_SERVICE_MANAGER_I(PTR_REF, CLASS)\
PTR_REF = NULL;\
GCloud::Plugin::PluginBase*  pluginBase = (GCloud::Plugin::PluginBase*)CLASS::GetInstance();\
if(NULL!=pluginBase){\
PTR_REF = pluginBase->GetServiceManager();\
}

GCLOUD_PLUGIN_NAMESPACE_END

#endif

#endif /* PluginBase_iOS_h */
