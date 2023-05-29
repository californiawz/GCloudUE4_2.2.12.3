//
//  IServiceManager.h
//  onesdk
//
//  Created by cedar on 2018/7/24.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef IServiceManager_h
#define IServiceManager_h

#include "GCloudPluginManager/IPluginService.h"

GCLOUD_PLUGIN_NAMESPACE

class IServiceManager
{
protected:
    ~IServiceManager(){};
    
public:
    virtual IPluginService* GetServiceByName(const char* serviceName) = 0;
};

GCLOUD_PLUGIN_NAMESPACE_END

#endif /* IServiceManager_h */
