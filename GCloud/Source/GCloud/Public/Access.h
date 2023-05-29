//
//  Access.h
//  GCloud
//
//  Created by vforkk on 14/1/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef GCloud_Access_h
#define GCloud_Access_h
#include "GCloudPublicDefine.h"
//#include "IConnectorOld.h"

#include <string>

namespace GCloud {
	
    class IService;
    class IConnectorOld;
    class IConnectorFactory;
    class IG6ConnectorFactory;
    
    class EXPORT_CLASS Access
    {
    protected:
        Access(){}
        virtual ~Access(){}
        
    public:
        static Access& GetInstance();
        static void ReleaseInstance();
        ///////////////////////////////////////////////////////////////////////////////
        // Required
        ///////////////////////////////////////////////////////////////////////////////
    public:
        virtual bool SwitchPlugin(const char* pluginName) = 0;

        
        ///////////////////////////////////////////////////////////////////////////////
        // Optional
        ///////////////////////////////////////////////////////////////////////////////
    public:
        virtual IConnectorOld* CreateConnection(ChannelType channel, const char* pszSvrUrl, int maxBuflen, int connectorkind = 0, int timeoutSec = 0) = 0;
        
        virtual void DestroyConnector(IConnectorOld** lppConnector) = 0;
        
        virtual IConnectorFactory* GetConnectorFactory() = 0;
        
        virtual IG6ConnectorFactory* GetG6ConnectorFactory() = 0;

        virtual void SetUserInfo(const UserInfo& userInfo) = 0;
    };
}

#endif
