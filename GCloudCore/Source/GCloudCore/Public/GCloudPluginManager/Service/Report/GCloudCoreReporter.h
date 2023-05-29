//
//  GCloudCoreReporter.h
//  GCloudCore
//
//  Created by cedar on 2018/9/20.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef GCloudCoreReporter_h
#define GCloudCoreReporter_h

#if !defined(_WIN64) && !defined(_WIN32) && !defined(__ORBIS__)

#include "GCloudPluginManager/PluginBase/PluginBase.h"
#include "GCloudPluginManager/Service/Report/IReportService.h"


GCLOUD_PLUGIN_NAMESPACE

static GCloud::Plugin::IEvent* sg_create_gcloudcore_report_event(GCloud::Plugin::PluginBase* pBase, int env, int srcID, const char* eventName)
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
    GCloud::Plugin::ICoreReportService* reportService = (GCloud::Plugin::ICoreReportService*)plugin->GetServiceByName(PLUGIN_SERVICE_NAME_COREREPORT);
    if(NULL==reportService){
        return NULL;
    }
    return reportService->CreateEvent(env, srcID, eventName);
}

static void sg_destroy_gcloudcore_report_event(GCloud::Plugin::PluginBase* pBase, GCloud::Plugin::IEvent** ppEvent)
{
    GCloud::Plugin::PluginBase*  pluginBase = pBase;
    if(NULL==pluginBase){
        return;
    }
    GCloud::Plugin::IPluginManager* pluginManager = pluginBase->GetPluginManager();
    if(NULL==pluginManager){
        return;
    }
    GCloud::Plugin::IPlugin* plugin = (GCloud::Plugin::IPlugin*)pluginManager->GetPluginByName(PLUGIN_NAME_GCLOUDCORE);
    if(NULL==plugin){
        return;
    }
    GCloud::Plugin::ICoreReportService* reportService = (GCloud::Plugin::ICoreReportService*)plugin->GetServiceByName(PLUGIN_SERVICE_NAME_COREREPORT);
    if(NULL==reportService){
        return;
    }
    reportService->DestroyEvent(ppEvent);
}

//
#define CREATE_GCLOUDCORE_REPORT_EVENT(CLASS, REPORT_ENV, SRC_ID, EVENT_NAME) \
sg_create_gcloudcore_report_event(CLASS::GetInstance(), REPORT_ENV, SRC_ID, EVENT_NAME);

#define DESTROY_GCLOUDCORE_REPORT_EVENT(CLASS, PPEVENT) \
sg_destroy_gcloudcore_report_event(CLASS::GetInstance(), PPEVENT);


GCLOUD_PLUGIN_NAMESPACE_END

#endif /* Not WIN */
#endif /* GCloudCoreReporter_h */
