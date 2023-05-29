//
//  IGFMConnectorFactory.h
//  Connector
//
//  Created by Morris on 2018/4/4.
//  Copyright © 2018年 vforkk. All rights reserved.
//

#ifndef IGFMConnectorFactory_h
#define IGFMConnectorFactory_h

#include "IGFMConnector.h"
namespace GCloud
{
    class EXPORT_CLASS IGFMConnectorFactory
    {
    public:
        virtual  Conn::IGFMConnector* CreateGFMConnector(Conn::ConnectorType type, bool manualUpdate, bool autoReconnect, bool autoLogin) = 0;
        virtual void DestroyGFMConnector(Conn::IGFMConnector* connector) = 0;
    };
    
    EXPORT_API IGFMConnectorFactory* GetGFMConnectorFactory();
}

#endif /* IGFMConnectorFactory_h */
