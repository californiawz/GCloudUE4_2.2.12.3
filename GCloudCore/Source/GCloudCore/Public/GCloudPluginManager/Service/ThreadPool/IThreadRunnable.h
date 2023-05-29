//
//  IThreadRunnable.h
//
//  Created by saitexie on 2020/4/20.
//  Copyright © 2020年 ten$cent. All rights reserved.
//

#ifndef IThreadRunnable_H
#define IThreadRunnable_H

#include "GCloudPluginManager/GCloudPluginPublicDefine.h"

GCLOUD_PLUGIN_NAMESPACE

class IThreadRunnable
{
public:
	virtual ~IThreadRunnable() {}
	virtual int GetVersion() { return 1; }

public:
	virtual void Execute() = 0;
};



GCLOUD_PLUGIN_NAMESPACE_END

#endif //ILOGGER_H
