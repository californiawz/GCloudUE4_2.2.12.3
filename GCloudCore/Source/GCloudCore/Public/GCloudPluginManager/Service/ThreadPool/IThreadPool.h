//
//  IThreadPool.h
//
//  Created by saitexie on 2020/4/20.
//  Copyright © 2020年 ten$cent. All rights reserved.
//

#ifndef IThreadPool_h
#define IThreadPool_h


#include "GCloudPluginManager/GCloudPluginPublicDefine.h"

#include "IFdListener.h"
#include "IThreadRunnable.h"


GCLOUD_PLUGIN_NAMESPACE

class IThreadPool
{
public:
	virtual ~IThreadPool() {}
    virtual int GetVersion() { return 1; }

public:
    virtual int RequestSchedule(IThreadRunnable *runnable, const char *group, const char *name, bool high_lv) = 0;
    virtual int RegFdListener(IFdListener *listener) = 0;
    virtual void UnRegFdListener(IFdListener *listener) = 0;
};


GCLOUD_PLUGIN_NAMESPACE_END


#endif /* IThreadPool_h */
