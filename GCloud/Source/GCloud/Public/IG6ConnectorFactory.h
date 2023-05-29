#ifndef IG6ConnectorFactory_h
#define IG6ConnectorFactory_h

#include "IG6Connector.h"

namespace GCloud
{
    class EXPORT_CLASS IG6ConnectorFactory
    {
    public:
        virtual G6Client::IG6Connector* CreateConnector(bool manualUpdate) = 0;
        
        virtual void DestroyConnector(G6Client::IG6Connector* connector) = 0;
    };
}

#endif /* Header_h */
