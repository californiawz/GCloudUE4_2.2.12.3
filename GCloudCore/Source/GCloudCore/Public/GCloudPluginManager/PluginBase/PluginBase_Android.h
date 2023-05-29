//
//  PluginBase_Android.h
//  GCloudPluginManager
//
//  Created by cedar on 2018/7/28.
//  Copyright © 2018年 All rights reserved.
//

#ifndef PluginBase_Android_h
#define PluginBase_Android_h

#if defined (ANDROID)

#include <jni.h>
#include <android/log.h>
#include "GCloudPluginManager/GCloudPluginPublicDefine.h"
#include "GCloudPluginManager/IPluginManager.h"
#include "PluginInnerDefine.h"

GCLOUD_PLUGIN_NAMESPACE

static void* gs_GetCachePtr(JavaVM* jvm, const char* className, const char* methodName)
{
    if(!jvm || !className || !methodName){
        __android_log_print(ANDROID_LOG_ERROR, "", "!jvm || !className || !methodName");
        return NULL;
    }
    __android_log_print(ANDROID_LOG_INFO, "", "gs_GetCachePtr jvm:%p, className:%s, methodName:%s", jvm, className, methodName);
    
    JNIEnv* pEnv = NULL;
    bool attached = false;
    int status = jvm->GetEnv((void**)&pEnv, JNI_VERSION_1_4);
    if(status < 0 || pEnv == NULL)
    {
        if(jvm != NULL)
        {
            attached = true;
            jvm->AttachCurrentThread(&pEnv, NULL);
        }
    }
    
    if(pEnv == NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "", "pEnv is null");
        return NULL;
    }
    
    //2.find class
    jclass cls = pEnv->FindClass(className);
    
    if(cls == NULL){
        __android_log_print(ANDROID_LOG_ERROR, "", "cls is null");
        
        //__android_log_print(ANDROID_LOG_ERROR, "", "before ExceptionCheck");
        if(pEnv->ExceptionCheck()){
            
            //__android_log_print(ANDROID_LOG_ERROR, "", "start ExceptionCheck");
            pEnv->ExceptionClear();
        }
        //__android_log_print(ANDROID_LOG_ERROR, "", "after ExceptionCheck");
        return NULL;
    }
    
    //3.find method
    jmethodID mid = pEnv->GetStaticMethodID(cls, methodName, "()J");
    
    if(mid == NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "", "mid is null");
        pEnv->DeleteLocalRef(cls);
        return NULL;
    }
    
    //4.get java cached ptr
    jlong ret = (jlong)pEnv->CallStaticLongMethod(cls, mid);
    void* p = (void*)ret;
    
    __android_log_print(ANDROID_LOG_INFO, "", "cached ptr:%p", p);
    
    pEnv->DeleteLocalRef(cls);
    
    if(attached)
    {
        jvm->DetachCurrentThread();
    }
    return p;
}

static void* gs_GetGCloudPluginManager(void* param1)
{
    GCloud::Plugin::IPluginManager* pMgr = static_cast<GCloud::Plugin::IPluginManager*>(gs_GetCachePtr(
                                                                                                       static_cast<JavaVM*>(param1),
                                                                                                       JNI_CLASS_GCORE_GCLOUD_PLUGIN_LIFE_CYCLE,
                                                                                                       "GetNativePluginManager"
                                                                                                       ));
    
    __android_log_print(ANDROID_LOG_INFO, "", "gs_GetGCloudPluginManager pluginManager:%p", pMgr);
    
    return pMgr;
}

static void* gs_GetGCloudServiceManager(void* param1)
{
    GCloud::Plugin::IPluginManager* pMgr = static_cast<GCloud::Plugin::IPluginManager*>(gs_GetCachePtr(
                                                                                                       static_cast<JavaVM*>(param1),
                                                                                                       JNI_CLASS_GCORE_GCLOUD_PLUGIN_LIFE_CYCLE,
                                                                                                       "GetNativeServiceManager"
                                                                                                       ));
    
    __android_log_print(ANDROID_LOG_INFO, "", "gs_GetGCloudServiceManager serviceManager:%p", pMgr);
    
    return pMgr;
}


static void gs_RegisterGCloudPlugin(void* param1, void* param2)
{
    GCloud::Plugin::IPluginManager* pMgr = static_cast<GCloud::Plugin::IPluginManager*>(gs_GetGCloudPluginManager(param1));
    
    if(pMgr){
        pMgr->Install(static_cast<GCloud::Plugin::IPlugin*>(param2));
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "", "gs_RegisterGCloudPlugin pluginManager is null");
    }
}


class PluginBase : public IPlugin
{
protected:
    PluginBase():_jvm(NULL), _pluginManager(NULL){}
    ~PluginBase(){};
    
public:
    
    void GetCachePluginManager()
    {
        if(NULL!=_jvm && NULL==_pluginManager){
            _pluginManager = static_cast<GCloud::Plugin::IPluginManager*>(gs_GetGCloudPluginManager((void*)_jvm));
        }
    }
    
    IPluginManager* GetPluginManager() const
    {
        return _pluginManager;
    }
    
    void SetJavaVM(JavaVM* vm)
    {
        if(NULL!=vm && NULL==_jvm){
            _jvm = vm;
        }
    }
    JavaVM* GetJavaVM() const
    {
        return _jvm;
    }
    
    void RegisterPlugin(GCloud::Plugin::IPlugin* plugin)
    {
        if(!plugin){
            __android_log_print(ANDROID_LOG_ERROR, "", "PluginBase::RegisterPlugin plugin is null");
            return;
        }
        
        GCloud::Plugin::IPluginManager* pluginManager = GetPluginManager();
        if(pluginManager){
            pluginManager->Install(plugin);
            __android_log_print(ANDROID_LOG_INFO, "", "PluginBase::RegisterPlugin PluginManager:%p , IPlugin:%p", pluginManager, plugin);
        }
    }
protected:
    JavaVM* _jvm;
    IPluginManager* _pluginManager;
};

#define GET_GCLOUD_PLUGIN_MANAGER_A(PTR_REF, CLASS)\
PTR_REF = NULL;\
GCloud::Plugin::PluginBase*  pluginBase = (GCloud::Plugin::PluginBase*)CLASS::GetInstance();\
if(NULL!=pluginBase){\
PTR_REF = pluginBase->GetPluginManager();\
}

#define GET_GCLOUD_SERVICE_MANAGER_A(PTR_REF, CLASS)\
PTR_REF = NULL;\
GCloud::Plugin::PluginBase*  pluginBase = (GCloud::Plugin::PluginBase*)CLASS::GetInstance();\
if(NULL!=pluginBase){\
PTR_REF = pluginBase->GetServiceManager();\
}

#define REGISTER_GCLOUD_PLUGIN_A(JVM, CLASS) \
do{\
GCloud::Plugin::PluginBase*  pluginBase = (GCloud::Plugin::PluginBase*)CLASS::GetInstance();\
if(NULL!=pluginBase){\
pluginBase->SetJavaVM(JVM);\
pluginBase->GetCachePluginManager();\
pluginBase->RegisterPlugin(CLASS::GetInstance());\
}\
}\
while(0)


GCLOUD_PLUGIN_NAMESPACE_END

#endif

#endif /* PluginBase_Android_h */
