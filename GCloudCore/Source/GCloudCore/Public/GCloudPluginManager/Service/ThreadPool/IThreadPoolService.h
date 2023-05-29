//
//  IThreadPoolService.h
//
//  Created by saitexie on 2020/4/20.
//  Copyright © 2020年 ten$cent. All rights reserved.
//

#ifndef IThreadPoolService_h
#define IThreadPoolService_h


#include "IThreadPool.h"
#include "GCloudPluginManager/IPluginService.h"

GCLOUD_PLUGIN_NAMESPACE


class IThreadPoolService : public IPluginService
{
public:
    virtual int GetVersion() { return 1; }

public:
    virtual IThreadPool* GetThreadPool(void* pBase) = 0;
};

inline bool IsThreadPoolSupport(const char *ver)
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


#endif /* IThreadPoolService_h */
