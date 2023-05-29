//
// Created by aaronyan on 2019/8/21.
//

#ifndef IREMOTECONFIGSERVICE_H
#define IREMOTECONFIGSERVICE_H

#include <string.h>

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/PluginBase/PluginBase.h"
#include "IRemoteConfig.h"

GCLOUD_PLUGIN_NAMESPACE

class IRemoteConfigService : public IPluginService
{
protected:
    ~IRemoteConfigService(){}

public:
    virtual GCloud::IRemoteConfig* GetRemoteConfig(GCloud::Plugin::PluginBase* pBase) = 0;
};


class IRemoteConfigExService : public IPluginService
{
protected:
    ~IRemoteConfigExService(){}

public:
    virtual int GetVersion() = 0;
    virtual GCloud::IRemoteConfig* GetRemoteConfig(GCloud::Plugin::PluginBase* pBase) = 0;
};





GCLOUD_PLUGIN_NAMESPACE_END

#endif //IREMOTECONFIGSERVICE_H
