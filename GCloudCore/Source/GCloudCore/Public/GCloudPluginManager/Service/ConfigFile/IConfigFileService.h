//
// Created by aaronyan on 2019/8/21.
//

#ifndef ICONFIGFILESERVICE_H
#define ICONFIGFILESERVICE_H

#include "GCloudPluginManager/IPluginService.h"
#include "IConfigFile.h"

GCLOUD_PLUGIN_NAMESPACE

class IConfigFileService : public IPluginService
{
protected:
    ~IConfigFileService(){}

public:
    virtual GCloud::IConfigFile* NewConfigFile(const char* name) = 0;
    virtual void DeleteConfigFile(GCloud::IConfigFile** configFile) = 0;
    virtual IConfigFile& GetDefaultConfigFile() = 0;
};

GCLOUD_PLUGIN_NAMESPACE_END

#endif //ICONFIGFILESERVICE_H
