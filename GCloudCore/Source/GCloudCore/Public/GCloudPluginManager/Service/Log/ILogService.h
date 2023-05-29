//
//  ILogService.h
//  GCloudPluginManager
//
//  Created by aaronyan on 2019/9/25.
//  Copyright © 2019年 GCloud. All rights reserved.
//

#ifndef ILogService_h
#define ILogService_h

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/PluginBase/PluginBase.h"
#include "ILogger.h"

GCLOUD_PLUGIN_NAMESPACE

class ILogService : public IPluginService
{
protected:
    ~ILogService(){}
    
public:
    virtual int GetVersion() = 0;

    virtual GCloud::ILogger* GetLogger(GCloud::Plugin::PluginBase* pBase) = 0;
};


GCLOUD_PLUGIN_NAMESPACE_END


#endif /* ILogService_h */
