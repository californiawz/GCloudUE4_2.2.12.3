//
// ITraceService.h
// GCloudSDK
//
// Created by cedar on 2019/8/26.
// Copyright (c) 2019 GCloud. All rights reserved.
//

#ifndef ITraceService_H
#define ITraceService_H


#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/PluginBase/PluginBase.h"

GCLOUD_PLUGIN_NAMESPACE

#define GTRACE_KEY_TRACEID           "tid"
#define GTRACE_KEY_SPANID            "sid"
#define GTRACE_KEY_PARENTID          "pid"
#define GTRACE_KEY_KIND              "kind"
#define GTRACE_KEY_BUSINESSID        "buzid"
#define GTRACE_KEY_SETID             "setid"
#define GTRACE_KEY_PRIVATETYPE       "pritype"
#define GTRACE_KEY_PUBLICTYPE        "pubtype"
#define GTRACE_KEY_NAME              "name"
#define GTRACE_KEY_TIMESTAMP_US      "ts"
#define GTRACE_KEY_DURATION_US       "dur"
#define GTRACE_KEY_ERRCODE           "errcode"
#define GTRACE_KEY_ERRMSG            "errmsg"
#define GTRACE_KEY_OPENID            "openid"
#define GTRACE_KEY_CALLER            "locname"
#define GTRACE_KEY_CALLEE            "rmtname"
#define GTRACE_KEY_TAGS              "tags"


#define GTRACE_PUBTYPE_UNKNOWN              "-1"
#define GTRACE_PUBTYPE_GCLOUDCORE           "100"
#define GTRACE_PUBTYPE_CONNECTOR            "1"
#define GTRACE_PUBTYPE_DOLPHIN              "2"
#define GTRACE_PUBTYPE_PUFFER               "3"
#define GTRACE_PUBTYPE_MAPLE                "4"

#define GTRACE_PRITYPE_UNKNOWN              "0"

enum GTraceDataType
{
    kGTraceDataTypeKernel = 0x01,
    kGTraceDataTypeUser = 0x02
};

class ISpanContext
{
public:
    virtual ~ISpanContext(){};

public:
    virtual bool Set(const char* key, const char* value) = 0;
    virtual const char* Get(const char* key) = 0;
    virtual bool SetTag(const char* key, const char* value) = 0;
    virtual const char* GetTag(const char* key) = 0;
    virtual const char* ToString() = 0;
    virtual const char* GetEncodedUserData() = 0;
};

class ITraceService : public IPluginService
{
protected:
    ~ITraceService(){};

public:
    virtual bool IsEnabled() const = 0;
    virtual const char* GetTraceId()= 0;
    virtual bool IsReady(const char* publicType) = 0;

public:
    virtual const char* CreateContext(const char* parentContext, const char* publicType, const char* privateType) = 0;
    virtual bool FlushContext(const char* context, GTraceDataType dataType, const char* key, const char* value) = 0;
    virtual bool ReportContext(const char* context) = 0;
    virtual bool DestroyContext(const char* context) = 0;
};

static IPluginService* sg_get_service_by_name(GCloud::Plugin::PluginBase *pBase, const char* pluginName, const char* serviceName){
    if(NULL==pBase || NULL==pluginName || NULL==serviceName){
                return NULL;
    }
    GCloud::Plugin::IPluginManager *pluginManager = pBase->GetPluginManager();
    if (NULL == pluginManager) {
        return NULL;
    }
    GCloud::Plugin::IPlugin *plugin = (GCloud::Plugin::IPlugin *) pluginManager->GetPluginByName(pluginName);
    if (NULL == plugin) {
        return NULL;
    }
    GCloud::Plugin::IPluginService* service = (GCloud::Plugin::ITraceService *) plugin->GetServiceByName(serviceName);
    if (NULL == service) {
        return NULL;
    }
    return service;
}

static const char* sg_get_traceid(GCloud::Plugin::PluginBase* pBase)
{
    GCloud::Plugin::PluginBase*  pluginBase = pBase;
    if(NULL==pluginBase){
        return NULL;
    }
    GCloud::Plugin::IPluginManager* pluginManager = pluginBase->GetPluginManager();
    if(NULL==pluginManager){
        return NULL;
    }
    GCloud::Plugin::IPlugin* plugin = (GCloud::Plugin::IPlugin*)pluginManager->GetPluginByName(PLUGIN_NAME_GCLOUDCORE);
    if(NULL==plugin){
        return NULL;
    }
    GCloud::Plugin::ITraceService* traceService = (GCloud::Plugin::ITraceService*)plugin->GetServiceByName(PLUGIN_SERVICE_NAME_GTRACE);
    if(NULL==traceService){
        return NULL;
    }
    if(!traceService->IsEnabled()){
        return NULL;
    }
    return traceService->GetTraceId();
}


static const char* sg_create_context(GCloud::Plugin::PluginBase* pBase, const char* parentContext, const char* publicType, const char* privateType)
{
    GCloud::Plugin::ITraceService *traceService = (GCloud::Plugin::ITraceService *) sg_get_service_by_name(pBase, PLUGIN_NAME_GCLOUDCORE, PLUGIN_SERVICE_NAME_GTRACE);
    if (NULL == traceService) {
        return NULL;
    }
    if(!traceService->IsEnabled() || !traceService->IsReady(publicType)){
        return NULL;
    }
    return traceService->CreateContext(parentContext, publicType, privateType);
}

static void sg_destroy_context(GCloud::Plugin::PluginBase *pBase, const char* context, const char* publicType)
{
    GCloud::Plugin::ITraceService *traceService = (GCloud::Plugin::ITraceService *) sg_get_service_by_name(pBase, PLUGIN_NAME_GCLOUDCORE, PLUGIN_SERVICE_NAME_GTRACE);
    if (NULL == traceService) {
        return;
    }
    if(!traceService->IsEnabled() || !traceService->IsReady(publicType)){
        return;
    }
    traceService->DestroyContext(context);
}

static void sg_span_start(GCloud::Plugin::PluginBase *pBase, const char* context, const char* publicType, const char* name, const char* caller, const char* callee)
{
    if(NULL==context){
        return;
    }
    GCloud::Plugin::ITraceService *traceService = (GCloud::Plugin::ITraceService *) sg_get_service_by_name(pBase, PLUGIN_NAME_GCLOUDCORE, PLUGIN_SERVICE_NAME_GTRACE);
    if (NULL==traceService) {
        return;
    }
    if(!traceService->IsEnabled() || !traceService->IsReady(publicType)){
        return;
    }
    traceService->FlushContext(context, kGTraceDataTypeKernel, GTRACE_KEY_NAME, name);
    traceService->FlushContext(context, kGTraceDataTypeKernel, GTRACE_KEY_CALLER, caller);
    traceService->FlushContext(context, kGTraceDataTypeKernel, GTRACE_KEY_CALLEE, callee);
}

static void sg_span_flush(GCloud::Plugin::PluginBase *pBase, const char* context, const char* publicType, const char* key, const char* value)
{
    if(NULL==context){
        return;
    }
    GCloud::Plugin::ITraceService *traceService = (GCloud::Plugin::ITraceService *) sg_get_service_by_name(pBase, PLUGIN_NAME_GCLOUDCORE, PLUGIN_SERVICE_NAME_GTRACE);
    if (NULL==traceService) {
        return;
    }
    if(!traceService->IsEnabled() || !traceService->IsReady(publicType)){
        return;
    }
    traceService->FlushContext(context, kGTraceDataTypeUser, key, value);
}

static void sg_span_finish(GCloud::Plugin::PluginBase *pBase, const char* context, const char* publicType, const char* errCode, const char* errMsg)
{
    if(NULL==context){
        return;
    }
    GCloud::Plugin::ITraceService *traceService = (GCloud::Plugin::ITraceService *) sg_get_service_by_name(pBase, PLUGIN_NAME_GCLOUDCORE, PLUGIN_SERVICE_NAME_GTRACE);
    if (NULL == traceService) {
        return;
    }
    if(!traceService->IsEnabled() || !traceService->IsReady(publicType)){
        return;
    }
    traceService->FlushContext(context, kGTraceDataTypeKernel, GTRACE_KEY_ERRCODE, errCode);
    traceService->FlushContext(context, kGTraceDataTypeKernel, GTRACE_KEY_ERRMSG, errMsg);
    traceService->ReportContext(context);
    traceService->DestroyContext(context);
}


GCLOUD_PLUGIN_NAMESPACE_END


#endif //ITraceService_H
