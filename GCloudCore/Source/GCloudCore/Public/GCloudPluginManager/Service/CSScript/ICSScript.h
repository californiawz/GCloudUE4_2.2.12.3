//
//  ICSScriptVM.h
//
//  Created by saitexie on 2020/4/20.
//  Copyright © 2020年 ten$cent. All rights reserved.
//

#ifndef ICSScriptVM_h
#define ICSScriptVM_h

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/PluginBase/PluginBase.h"

GCLOUD_PLUGIN_NAMESPACE


typedef int (*GCloudCSCommFunc)(void *context, void *ret_token);


class ICSScriptVM
{
public:
	virtual ~ICSScriptVM() {}
    virtual int GetVersion() { return 1; }

public:
    virtual void *CreateVM(bool enable_built_funcs) = 0;
    virtual int Exec(const char* script, int is_check_mod, void *vm) = 0;
    virtual void DelVM(void *vm) = 0;

    virtual int RegistFunc(void *vm, const char *func_name, GCloudCSCommFunc func) = 0;

    virtual int GetParamCnt(void *context) = 0;
    virtual const char *GetStrParam(void *context, int index) = 0;
    virtual unsigned long GetUlongParam(void *context, int index) = 0;
    virtual int Print2RetToken(void *ret_token, const char *str) = 0;
    virtual void Abort(void *context) = 0;
};


GCLOUD_PLUGIN_NAMESPACE_END


#endif /* ICSScriptVM_h */
