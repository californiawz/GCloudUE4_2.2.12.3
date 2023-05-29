//
//  IPlugin.h
//  onesdk
//
//  Created by cedar on 2018/7/20.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef IPlugin_h
#define IPlugin_h

#include <stdio.h>
#include "GCloudPluginManager/GCloudPluginPublicDefine.h"
#include "GCloudPluginManager/IPluginService.h"

GCLOUD_PLUGIN_NAMESPACE


template<typename T>
class Singleton
{
protected:
    Singleton(){};
    virtual ~Singleton(){};
    
private:
    static T* m_pInstance;
    
public:
    static T* GetInstance()
    {
        if(NULL == m_pInstance){
            m_pInstance = new T();
        }
        return m_pInstance;
    }
};
template<typename T> T* Singleton<T>::m_pInstance = NULL;


class IPlugin
{
public:
    virtual ~IPlugin(){};
    
public:
    virtual const char* GetName() const = 0;
    virtual const char* GetVersion() const = 0;
    
public:
    virtual void OnStartup(IServiceRegister* serviceRegister) = 0;
    virtual void OnPostStartup() = 0;
    virtual void OnPreShutdown() = 0;
    virtual void OnShutdown() = 0;
    
public:
    virtual IPluginService* GetServiceByName(const char* serviceName) = 0;
};


GCLOUD_PLUGIN_NAMESPACE_END


#endif /* IPlugin_h */
