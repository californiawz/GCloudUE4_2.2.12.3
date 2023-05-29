//
//  GCloudPluginPublicDefine.h
//  onesdk
//
//  Created by cedar on 2018/7/21.
//  Copyright © 2018年 GCloud. All rights reserved.
//

#ifndef GCloudPluginPublicDefine_h
#define GCloudPluginPublicDefine_h

#include <stdio.h>

#define GCLOUD_PLUGIN_NAMESPACE \
namespace GCloud{\
namespace Plugin {\

#define GCLOUD_PLUGIN_NAMESPACE_END \
}\
}\

#define USING_NAMESPACE_PLUGIN using namespace GCloud::Plugin;


#define PLUGIN_NAME_GCLOUDCORE  "GCloudCore"
#define PLUGIN_NAME_GCLOUD      "GCloud"
#define PLUGIN_NAME_MSDK        "MSDK"
#define PLUGIN_NAME_HTTPDNS     "HttpDNS"
#define PLUGIN_NAME_TGPA        "TGPA"
#define PLUGIN_NAME_APM         "APM"
#define PLUGIN_NAME_GEM         "GEM"
#define PLUGIN_NAME_TSS         "TSS"
#define PLUGIN_NAME_GVOICE      "GVoice"
#define PLUGIN_NAME_TDM         "TDM"
#define PLUGIN_NAME_QROBOT      "GRobot"
#define PLUGIN_NAME_APOLLO      "Apollo"
#define PLUGIN_NAME_MKV         "MKV"
#define PLUGIN_NAME_CROS_CURL   "PluginCrosCurl"


#define PLUGIN_SERVICE_NAME_COREREPORT      "COREREPORT"
#define PLUGIN_SERVICE_NAME_REPORT          "REPORT"
#define PLUGIN_SERVICE_NAME_ACCOUNT         "ACCOUNT"
#define PLUGIN_SERVICE_NAME_GVOICE          "GVOICE"
#define PLUGIN_SERVICE_NAME_GTRACE          "GTRACE"
#define PLUGIN_SERVICE_NAME_REMOTECONFIG    "REMOTECONFIG"
#define PLUGIN_SERVICE_NAME_LOG             "LOG"
#define PLUGIN_SERVICE_NAME_REMOTECONFIGEX  "REMOTECONFIGEX"
#define PLUGIN_SERVICE_NAME_CONNECTOR       "CONNECTOR"
#define PLUGIN_SERVICE_NAME_THREADPOOL      "THREADPOOL"
#define PLUGIN_SERVICE_NAME_CSSCRIPT        "CSSCRIPT"
#define PLUGIN_SERVICE_NAME_CONFIGFILE      "CONFIGFILE"
#define PLUGIN_SERVICE_NAME_MKV             "MKV"
#define PLUGIN_SERVICE_NAME_CURL_QUERY      "CurlFuncQueryService"
#define PLUGIN_SERVICE_NAME_OPENSSL_QUERY   "OpenSSLFuncQueryService"

#endif /* GCloudPluginPublicDefine_h */
