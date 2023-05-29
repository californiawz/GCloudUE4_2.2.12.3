//
//  ICurlFuncQueryService.h
//  CrosCurl
//  Query and Call Curl Functions base by CrosCurl
//
//  Created by kiddpeng on 2022/5/19.
//  Copyright © 2022年 gcloud. All rights reserved.
//

#ifndef PLUGINCROSCURL_SOURCE_ICURLFUNCQUERYSERVICE_H_
#define PLUGINCROSCURL_SOURCE_ICURLFUNCQUERYSERVICE_H_

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/PluginBase/PluginBase.h"

#include "ICurlFunc.h"
#include "crosCurlDefine.h"

GCLOUD_PLUGIN_NAMESPACE

class ICurlFuncQueryService : public IPluginService {
 protected:
  virtual ~ICurlFuncQueryService() {}

 public:
  virtual int QueryCurlFuncs(CurlFuncs *pCurlFuncs) = 0;
  virtual int QueryCurlFuncs(CurlFuncs_V1 *pCurlFuncs) = 0;
};

GCLOUD_PLUGIN_NAMESPACE_END

#endif  // PLUGINCROSCURL_SOURCE_ICURLFUNCQUERYSERVICE_H_
