//
// AccountHelper.h
// GCloudSDK
//
// Created by cedar on 2019-09-22.
// Copyright (c) 2019 GCloud. All rights reserved.
//

#ifndef AccountHelper_h
#define AccountHelper_h

#if !defined(_WIN32) && !defined(_WIN64) && !defined(_MAC)

#include "GCloudPluginManager/Service/Account/IServiceAccount.h"

static bool sg_get_login_ret(GCloud::Plugin::PluginBase* pBase, GCloud::Plugin::MSDK::MSDKAccount& msdkAccount)
{
    GCloud::Plugin::PluginBase*  pluginBase = pBase;
    if(NULL==pBase){
        return false;
    }
    GCloud::Plugin::IPluginManager *pluginManager = pBase->GetPluginManager();
    if (NULL == pluginManager) {
        return false;
    }
    GCloud::Plugin::IPlugin *plugin = (GCloud::Plugin::IPlugin *) pluginManager->GetPluginByName(PLUGIN_NAME_MSDK);
    if (NULL == plugin) {
        return false;
    }
    GCloud::Plugin::MSDK::IServiceAccount* pService = (GCloud::Plugin::MSDK::IServiceAccount*)plugin->GetServiceByName(PLUGIN_SERVICE_NAME_ACCOUNT);
    if (NULL == pService) {
        return false;
    }
    return pService->getLoginRet(msdkAccount);
}

#define GET_LOGIN_RET(CLASS, ACCOUNT_REF)\
sg_get_login_ret(CLASS::GetInstance(), ACCOUNT_REF)


#endif

#endif //AccountHelper_h
