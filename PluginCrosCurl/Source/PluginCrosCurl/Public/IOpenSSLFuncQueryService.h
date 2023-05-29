//
//  IOpenSSLFuncQueryService.h
//  CrosCurl
//  Query and Call OpenSSL Functions base by CrosCurl
//
//  Created by kiddpeng on 2022/5/19.
//  Copyright © 2022年 gcloud. All rights reserved.
//

#ifndef PLUGINCROSCURL_SOURCE_IOPENSSLFUNCQUERYSERVICE_H_
#define PLUGINCROSCURL_SOURCE_IOPENSSLFUNCQUERYSERVICE_H_

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/PluginBase/PluginBase.h"

#include "IOpenSSLFunc.h"
#include "crosCurl.h"
#include "crosCurlDefine.h"

GCLOUD_PLUGIN_NAMESPACE

class IOpenSSLFuncQueryService : public IPluginService {
 protected:
  virtual ~IOpenSSLFuncQueryService() {}

 public:
  virtual int QueryOpenSSLFuncs(OpenSSLFuncs *pOpenSSLFuncs) = 0;
};

GCLOUD_PLUGIN_NAMESPACE_END

#endif  // PLUGINCROSCURL_SOURCE_IOPENSSLFUNCQUERYSERVICE_H_
