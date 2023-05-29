//
//  IPluginManager.h
//  onesdk
//
//  Created by cedar on 2018/7/21.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef IPluginManager_h
#define IPluginManager_h

#include "GCloudPluginManager/IPlugin.h"

GCLOUD_PLUGIN_NAMESPACE

class IPluginManager
{
public:
    ~IPluginManager(){};
    
public:
    virtual bool Install(IPlugin* plugin) = 0;
    
    virtual bool Uninstall(IPlugin* plugin) = 0;
    
    virtual bool UninstallByName(const char* pluginName) = 0;
    
    virtual const char** GetAllPluginNames() = 0;
    
    virtual IPlugin* GetPluginByName(const char* pluginName) = 0;
};

GCLOUD_PLUGIN_NAMESPACE_END


#endif /* IPluginManager_h */
