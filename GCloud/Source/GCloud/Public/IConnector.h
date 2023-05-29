//
//  IConnector.h
//  Connector
//
//  Created by vforkk on 2/17/17.
//  Copyright © 2017 vforkk. All rights reserved.
//

#ifndef GCloud_IConnector_h
#define GCloud_IConnector_h
#include "ConnectorPublicDefine.h"
#include "AString.h"

namespace GCloud {
    namespace Conn
    {
        class ConnectorObserver;
        
        class EXPORT_CLASS IConnector
        {
        protected:
            IConnector(){};
            virtual ~IConnector(){};
            
        public:
            /// <summary>
            /// Initialize connector
            /// </summary>
            /// <param name="initInfo">Information to initialize connector</param>
            virtual void Initialize(const Conn::InitializeInfo& initInfo) = 0;
            
            /// <summary>
            /// Star connect
            /// </summary>
            /// <returns>The result of connect</returns>
            /// <param name="channel">platform,such as fb</param>
            /// <param name="url">url for connect</param>
            /// <param name="clearBuffer">clear buffer or no</param>
            virtual bool Connect(int channel, const char* url, bool clear = true) = 0;
            
            /// <summary>
            /// Star connect
            /// </summary>
            /// <returns>The result of connect</returns>
            /// <param name="channel">platform,such as fb</param>
            /// <param name="urlList">urls for connect</param>
            /// <param name="clearBuffer">clear buffer or no</param>
            virtual bool Connect(int channel, const AArray& urlList, bool clear = true) = 0;
            
            /// <summary>
            /// Restar connect
            /// </summary>
            /// <returns>The result of connect</returns>
            virtual bool RelayConnect() = 0;
            
            /// <summary>
            /// Disconnect
            /// </summary>
            /// <returns>The result of disconnect</returns>
            virtual void Disconnect() = 0;
            
            /// <summary>
            /// Receice TCP/RUDP data
            /// </summary>
            /// <returns>The result of reading</returns>
            /// <param name="buffer">data of reading</param>
            virtual bool Read(GCloud::AString& buffer) = 0;
            
            /// <summary>
            /// Send data to service by TCP/RUDP(Cluster mode)
            /// </summary>
            /// <returns>The result of sending</returns>
            /// <param name="data">data for sending</param>
            /// <param name="dataLen">length of data</param>
            /// <param name="routeInfo">information of route</param>
            virtual bool Write(const char* data, int len, const Conn::RouteInfoBase* routeInfo = 0) = 0;
            
            /// <summary>
            /// receive UDP data
            /// </summary>
            /// <returns>The result of reading</returns>
            /// <param name="buffer">data of reading</param>
            virtual bool ReadUDP(GCloud::AString& buffer) = 0;
            
            /// <summary>
            /// Send data to service by UDP
            /// </summary>
            /// <returns>The result of sending</returns>
            /// <param name="data">data for sending</param>
            /// <param name="dataLen">length of data</param>
            /// <param name="routeInfo">information of route</param>
            virtual bool WriteUDP(const char* data, int len, const Conn::RouteInfoBase* routeInfo = 0, unsigned int flags = 0) = 0;
            
            /// <summary>
            /// Send ping cmd to tconnd
            /// </summary>
            /// <returns>The sequence of ping</returns>
            virtual int SendPing() = 0;
            
            /// <summary>
            /// drive the logic of connector by manuel
            /// </summary>
            /// <returns>whether success  or not </returns>
            virtual bool Update() = 0;
            
            /// <summary>
            /// Get current IP and service id
            /// </summary>
            /// <returns>The result of getting</returns>
            /// <param name="info">information of connection</param>
            virtual bool GetConnectedInfo(Conn::ConnectedInfo* connectedInfo) = 0;
            
            /// <summary>
            /// Set the information of route(Cluster mode)
            /// </summary>
            /// <param name="routeInfo">information of route</param>
            virtual void SetRouteInfo(Conn::RouteInfoBase* routeInfo) = 0;
            
            /// <summary>
            /// Set the Connector and Tconnd communication protocol version
            /// </summary>
            /// <param name="headVersion">version of protocol head</param>
            /// <param name="bodyVersion">version of protocol body</param>
            virtual void SetProtocolVersion(int headVersion, int bodyVersion) = 0;
            
            /// <summary>
            /// Set the type of client
            /// </summary>
            /// <param name="type">type of client</param>
            virtual void SetClientType(Conn::ClientType clientType) = 0;
            
            /// <summary>
            /// Set player login authentication information
            /// </summary>
            /// <param name="type">type of authentication</param>
            /// <param name="channel">platform</param>
            /// <param name="appid">appId of game</param>
            /// <param name="openid">openId of player</param>
            /// <param name="token">token of player</param>
            /// <param name="expire">token expire time</param>
            /// <param name="extInfo">extend auth info transfered to authServer</param>
            virtual void SetAuthInfo(Conn::AuthType authType, const char* appid, int channel, const char* openid, const char* token, long long expire, const char* extInfo = NULL) = 0;
            
            /// <summary>
            /// Set data of start package
            /// </summary>
            /// <param name="reserve">reserve length</param>
            /// <param name="data">data</param>
            /// <param name="len">length of data</param>
            virtual void SetSyncInfo(unsigned int extInt, const char * msgData, unsigned int msgLen) = 0;
            
            /// <summary>
            /// set socket linger param
            /// </summary>
            /// <param name="linger"> 0, close socket immediately; positive, close socket after x second; Negative, close socket after buffer all sent</param>
            virtual void SetSocketLinger(int linger) = 0;

            
        public:
            virtual void SetObserver(ConnectorObserver* observer) = 0;
            virtual void ClearObserver() = 0;
            
        public:
            virtual bool IsConnected() = 0;
            virtual const char* GetUrl()const = 0;
            virtual const char* GetRealIP()const = 0;
        };
        
        class EXPORT_CLASS ConnectorObserver
        {
        public:
            ConnectorObserver(){}
            virtual ~ConnectorObserver(){}
        public:
            /// <summary>
            /// Callback of Connect
            /// </summary>
            virtual void OnConnected(IConnector* connector, const Conn::ConnectorResult& result) = 0;
            
            /// <summary>
            /// Callback of Disconnect
            /// </summary>
            virtual void OnDisconnectProc(IConnector* connector, const Conn::ConnectorResult& result) = 0;
            
            /// <summary>
            /// Called when state of connection change
            /// </summary>
            virtual void OnStateChangedProc(IConnector* connector, Conn::ConnectorState state, const Conn::ConnectorResult& result) = 0;
            
            /// <summary>
            /// Called when receive TCP/RUDP data
            /// </summary>
            virtual void OnDataRecvedProc(IConnector* connector, const Conn::ConnectorResult& result) = 0;
            
            /// <summary>
            /// Callback of RelayConnect
            /// </summary>
            virtual void OnRelayConnectedProc(IConnector* connector, const Conn::ConnectorResult& result){}
            
            /// <summary>
            /// Called when receive UDP data
            /// </summary>
            virtual void OnUDPDataRecvedProc(IConnector* connector, const Conn::ConnectorResult& result) {}
            
            /// <summary>
            /// Called when route information change
            /// </summary>
            virtual void OnRouteChangedProc(IConnector* connector, const Conn::ConnectorResult& result, unsigned long long serverID){}
            
            /// <summary>
            /// Called when Ping package received
            /// </summary>
            virtual void OnPingProc(IConnector* connector, int seq, unsigned long long rtt){}
        };
        
        #define IManualConnector IConnector
        #define ILWIPConnector   IConnector
        #define LWIPConnectorObserver ConnectorObserver
    }
}

#endif /* IConnector_h */

