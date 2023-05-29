//
//  IPluginServiceBase.h
//  onesdk
//
//  Created by cedar on 2018/7/23.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef IPluginService_h
#define IPluginService_h

#include "GCloudPluginManager/GCloudPluginPublicDefine.h"

GCLOUD_PLUGIN_NAMESPACE

class IPluginService
{
public:
    virtual ~IPluginService(){};
    
public:
    virtual const char* GetName() const = 0;
    virtual const char* GetPluginName() const = 0;
};

class IServiceRegister
{
protected:
    ~IServiceRegister(){};
    
public:
    virtual bool Register(const char* serviceName) = 0;
};




GCLOUD_PLUGIN_NAMESPACE_END

#endif /* IPluginService_h */
