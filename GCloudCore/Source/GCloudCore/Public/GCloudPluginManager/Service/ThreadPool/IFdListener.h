//
//  IFdListener.h
//
//  Created by saitexie on 2020/4/20.
//  Copyright © 2020年 ten$cent. All rights reserved.
//

#ifndef IFdListener_H
#define IFdListener_H

#include "GCloudPluginManager/GCloudPluginPublicDefine.h"

GCLOUD_PLUGIN_NAMESPACE


class IFdListener
{
public:
	virtual ~IFdListener() {}
	virtual int GetVersion() { return 1; }
	virtual int GetFd() = 0;
	virtual void OnSelect(int fd, double t) = 0;
	virtual const char *GetSCName() = 0;
};


GCLOUD_PLUGIN_NAMESPACE_END

#endif //ILOGGER_H
