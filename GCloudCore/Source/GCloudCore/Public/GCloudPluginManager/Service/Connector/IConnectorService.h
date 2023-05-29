//
//  IConnectorService.h
//  Connector
//
//  Created by vforkk on 2/17/17.
//  Copyright © 2017 vforkk. All rights reserved.
//

#ifndef GCloud_IConnectorService_h
#define GCloud_IConnectorService_h

#include "GCloudPluginManager/IPluginService.h"

GCLOUD_PLUGIN_NAMESPACE

enum CSRetCode
{
    kCSRetCodeSuccess           = 0,
    kCSRetCodeError             = -1,
    kCSRetCodeArgumentError     = -2,
    kCSRetCodeConnectorError    = -3,
    kCSRetCodeNoConnection      = -4,
    kCSRetCodeServiceClosed     = -5,
    kCSRetCodeAPIClosed         = -6,
    kCSRetCodeGameFobidden      = -7,
    kCSRetCodeTconndFobidden    = -8,
};

enum CSState
{
    kCSStateOnline  = 1,
    kCSStateOffline = 2,
};

enum CSDataType
{
    kCSDataTypeBase  = 0,
    kCSDataTypeTP    = 1,
};

class IConnectorServiceObserver
{
public:
    virtual ~IConnectorServiceObserver(){}
    
public:
    virtual int GetVersion(){ return 1; }
    
public:
    virtual void OnEchoNotify(int ret, int seq, long long rtt) = 0;
    virtual void OnDataNotify(int ret, int seq, int dataType, const char* data, int len) = 0;
    virtual void OnStateNotify(int ret, int state, const char* url) = 0;
};

class IConnectorService : public IPluginService
{
public:
    virtual int GetVersion(){ return 1; }

public:
    virtual int GetState() = 0;
    virtual const char * GetServerIP() = 0;
    
    virtual int SendEcho() = 0;
    virtual int SendData(int dataType, const char* data, int len) = 0;

    virtual void AddObserver(IConnectorServiceObserver* observer) = 0;
    virtual void RemoveObserver(IConnectorServiceObserver* pObserver) = 0;
};

GCLOUD_PLUGIN_NAMESPACE_END

#endif /* GCloud_IConnectorService_h */

