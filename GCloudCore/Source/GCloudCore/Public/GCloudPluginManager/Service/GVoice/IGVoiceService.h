//
//  IGVoiceService.h
//  GCloudCore
//
//  Created by cedar on 2019/1/7.
//  Copyright © 2019年 GCloud. All rights reserved.
//

#ifndef IGVoiceService_h
#define IGVoiceService_h

#include "GCloudPluginManager/IPluginService.h"

GCLOUD_PLUGIN_NAMESPACE

class IGVoiceObserver
{
protected:
    virtual ~IGVoiceObserver(){}
public:
    virtual void OnGVoiceServiceNotify(const char* msg, size_t len) = 0;
};

class IGVoiceService : public IPluginService
{
protected:
    virtual ~IGVoiceService(){}
    
public:
    virtual void SetObserver(IGVoiceObserver* pObserver) = 0;
    
public:
    virtual void EnableService(bool enable) = 0;
    virtual bool HandleActionAsync(const char* data, size_t len) = 0;
    virtual bool HandleActionSync(const char* data, size_t len, char** dataOut, size_t& outlen) = 0;
};

GCLOUD_PLUGIN_NAMESPACE_END

#endif /* IGVoiceService_h */
