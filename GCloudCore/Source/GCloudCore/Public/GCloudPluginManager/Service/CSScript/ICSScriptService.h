//
//  ICSScriptService.h
//
//  Created by saitexie on 2020/4/20.
//  Copyright © 2020年 ten$cent. All rights reserved.
//

#ifndef ICSScriptService_h
#define ICSScriptService_h

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/PluginBase/PluginBase.h"
#include "ICSScript.h"


GCLOUD_PLUGIN_NAMESPACE


typedef int (*GCloudCSCommFunc)(void *context, void *ret_token);


class ICSScriptService : public IPluginService
{
public:
	virtual ~ICSScriptService() {}

public:
    virtual int GetVersion() { return 1; }
    virtual ICSScriptVM *GetCSScriptVM(GCloud::Plugin::PluginBase* pBase) = 0;
};

inline bool IsCSScriptSupport(const char *ver)
{
    if (ver == NULL)
    {
        return false;
    }
    const int v1[] = {4, 6, 0, 0};
    int v2[] = {0, 0, 0, 0};
    
    if (sscanf(ver, "%d.%d.%d.%d", &v2[0], &v2[1], &v2[2], &v2[3]) < 4)
    {
        return false;
    }

    for(size_t i = 0; i < sizeof(v1)/sizeof(v1[0]); i++)
    {
        if (v2[i] > v1[i]) return true;
        else if (v2[i] < v1[i]) return false;
    }
	return true;
}

GCLOUD_PLUGIN_NAMESPACE_END


#endif /* ICSScriptService_h */
