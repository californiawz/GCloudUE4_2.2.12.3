//
//  IGFMConnector.hpp
//  Connector
//
//  Created by Morris on 2018/4/4.
//  Copyright © 2018年 vforkk. All rights reserved.
//

#ifndef IGFMConnector_hpp
#define IGFMConnector_hpp

#include "ConnectorPublicDefine.h"
#include "AString.h"

namespace GCloud
{
    namespace Conn
    {
        class GFMConnectorObserver;
        
        class EXPORT_CLASS IGFMConnector
        {
        protected:
            IGFMConnector(){};
            virtual ~IGFMConnector(){};
            
        public:
            virtual void Initialize(const Conn::InitializeInfo& initInfo) = 0;
            virtual bool Connect(int channel, const char* url, bool clear = true) = 0;
            virtual bool Connect(int channel, const AArray& urlList, bool clear = true) = 0;
            virtual void Disconnect() = 0;
            virtual bool Read(GCloud::AString& buffer, bool rawUdp = false) = 0;
            virtual bool Write(const char* data, int len, bool rawUdp = false, const Conn::RouteInfoBase* routeInfo = 0) = 0;
            
            virtual void SetUserInfo(const char* appid, int channel, const char* openid, const char* token, long long expire) = 0;
            virtual void SetProtocolVersion(int headVersion, int bodyVersion) = 0;
            virtual void SetRouteInfo(Conn::RouteInfoBase* routeInfo) = 0;
            
            virtual bool ManualUpdate() = 0;
            
        public:
            virtual void SetObserver(GFMConnectorObserver* observer) = 0;
            virtual void ClearObserver() = 0;
            
        public:
            virtual bool IsConnected() = 0;
            virtual const char* GetUrl()const = 0;
            virtual const char* GetRealIP()const = 0;
        };
        
        class EXPORT_CLASS GFMConnectorObserver
        {
        public:
            GFMConnectorObserver(){}
            virtual ~GFMConnectorObserver(){}
            
        public:
            virtual void OnConnectedProc(IGFMConnector* connector, const Conn::ConnectorResult& result) = 0;
            virtual void OnDisconnectProc(IGFMConnector* connector, const Conn::ConnectorResult& result) = 0;
            virtual void OnStateChangedProc(IGFMConnector* connector, Conn::ConnectorState state, const Conn::ConnectorResult& result) = 0;
            virtual void OnDataRecvedProc(IGFMConnector* connector, const Conn::ConnectorResult& result) = 0;
        };
    }
}

#endif /* IGFMConnector_hpp */
