//
//  ConnectorPublicDefine.h
//  Connector
//
//  Created by vforkk on 5/27/17.
//  Copyright © 2017 vforkk. All rights reserved.
//

#ifndef ConnectorPublicDefine_h
#define ConnectorPublicDefine_h
#include "ApolloBuffer.h"
#include "GCloudInnerDefine.h"
#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
#define snprintf _snprintf
#pragma warning(push)
#pragma warning(disable:4996)
#endif

namespace GCloud {
    
    namespace Conn
    {
        typedef enum
        {
            // Common
            kSuccess = 0,
            kErrorInnerError = 1,
            kErrorNetworkException = 2,
            kErrorTimeout = 3,
            kErrorInvalidArgument = 4,
            kErrorLengthError = 5,
            kErrorUnknown = 6,
            kErrorEmpty = 7,
            
            kErrorNotInitialized = 9,
            kErrorNotSupported = 10,
            kErrorNotInstalled = 11,
            kErrorSystemError = 12,
            kErrorNoPermission = 13,
            kErrorInvalidGameId = 14,
            
            // AccountService, from 100
            kErrorInvalidToken = 100,
            kErrorNoToken = 101,
            kErrorAccessTokenExpired = 102,
            kErrorRefreshTokenExpired = 103,
            kErrorPayTokenExpired = 104,
            kErrorLoginFailed = 105,
            kErrorUserCancel = 106,
            kErrorUserDenied,
            kErrorChecking,
            kErrorNeedRealNameAuth,
            
            // Connector, from 200
            kErrorNoConnection = 200,
            kErrorConnectFailed = 201,
            kErrorIsConnecting,
            kErrorGcpError,
            kErrorPeerCloseConnection,
            kErrorPeerStopSession,
            kErrorPkgNotCompleted,
            kErrorSendError,
            kErrorRecvError,
            kErrorStayInQueue,
            kErrorSvrIsFull,
            kErrorTokenSvrError,
            kErrorAuthFailed,
            kErrorOverflow,
            kErrorDNS,
            
        }EErrorCode;
        
        struct EXPORT_CLASS ConnectorResult : public GCloud::ApolloBufferBase
        {
            EErrorCode ErrorCode;//error code
            GCloud::AString Reason;//reason of error
            int Extend;//1st extra error message
            int Extend2;//2nd extra error message
            int64_t Extend3;//3rd extra error message
       
        public:
            ConnectorResult()
            : ErrorCode(kSuccess)
            , Extend(0)
            , Extend2(0)
            , Extend3(0)
            {
                
            }
            
            ConnectorResult(EErrorCode errorCode)
            : ErrorCode(errorCode)
            , Extend(0)
            , Extend2(0)
            , Extend3(0)
            {
                
            }
            
            ConnectorResult(EErrorCode errorCode, const char* reason)
            : ErrorCode(errorCode)
            , Reason(reason)
            , Extend(0)
            , Extend2(0)
            , Extend3(0)
            {
                
            }
            
            ConnectorResult(EErrorCode errorCode, int ext, const char* reason)
            : ErrorCode(errorCode)
            , Reason(reason)
            , Extend(ext)
            , Extend2(0)
            , Extend3(0)
            {
                
            }
            
            ConnectorResult(EErrorCode errorCode, int ext, int ext2, const char* reason)
            : ErrorCode(errorCode)
            , Reason(reason)
            , Extend(ext)
            , Extend2(ext2)
            , Extend3(0)
            {
                
            }
            
            ConnectorResult(const ConnectorResult& r)
            {
                ErrorCode = r.ErrorCode;
                Reason = r.Reason;
                Extend = r.Extend;
                Extend2= r.Extend2;
                Extend3= r.Extend3;
            }
            
        public:
            
            void Reset(EErrorCode error, const char* reason = "")
            {
                ErrorCode = error;
                Reason = reason;
                Extend = 0;
                Extend2 = 0;
                Extend3 = 0;
            }
            
            void Reset(EErrorCode error, int ext, const char* reason = "")
            {
                ErrorCode = error;
                Reason = reason;
                Extend = ext;
                Extend2 = 0;
                Extend3 = 0;
            }
            
            void Reset(EErrorCode error, int ext, int ext2, const char* reason = "")
            {
                ErrorCode = error;
                Reason = reason;
                Extend = ext;
                Extend2 = ext2;
                Extend3 = 0;
            }
            
            void Success()
            {
                ErrorCode = kSuccess;
                Reason = "";
                Extend = 0;
                Extend2 = 0;
                Extend3 = 0;
            }
            
            bool IsSuccess()const
            {
                return ErrorCode == kSuccess;
            }
            
            GCloud::AString ToString()const;
            
            bool operator == (EErrorCode errorCode)const
            {
                return ErrorCode == errorCode;
            }
            
            bool operator != (EErrorCode errorCode)const
            {
                return ErrorCode != errorCode;
            }
            
            ConnectorResult& operator= (const ConnectorResult& cRet)
            {
                ErrorCode = cRet.ErrorCode;
                Reason = cRet.Reason;
                Extend = cRet.Extend;
                Extend2 = cRet.Extend2;
                Extend3 = cRet.Extend3;
                
                return *this;
            }
            
        public:
            virtual AObject* Clone()const
            {
                ConnectorResult* clone = new ConnectorResult();
                *clone = *this;
                return clone;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& write)const
            {
                write.Write(ErrorCode);
                write.Write(Reason);
                write.Write(Extend);
                write.Write(Extend2);
                write.Write(Extend3);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                int tmp;
                reader.Read(tmp);
                ErrorCode = (EErrorCode)tmp;
                reader.Read(Reason);
                reader.Read(Extend);
                reader.Read(Extend2);
                reader.Read(Extend3);
            }
        };
        
        enum ConnectorType
        {
            kTConnd = 0,    //Default GCP
            kGConnd = 1,    //Default GCP
            
            // Interim
            kTConnd_GCP = 11,
            kTConnd_PRT = 12,   // reserve
            
            kGConnd_GCP = 21,
            kGConnd_PRT = 22,
        };
        
        enum ConnectorMode
        {
            kCMode_Default = 0,
            kCMode_TP      = 1,
        };
        
        enum KeyMaking {
            kKeyMakingNone = 0,
            kKeyMakingInauth,
            kKeyMakingInSvr,
            kKeyMakingRawDH,
            kKeyMakingEncDH,
        };
        
        enum ConnectorState
        {
            kConnectorStateRunning,
            kConnectorStateReconnecting, // Reconnecting to the server
            kConnectorStateReconnected,
            kConnectorStateStayInQueue, // In queue
            kConnectorStateError, // Error occured
        };

        enum
        {
            kRouteNone = 0,
            kRouteZone,
            kRouteServer,
            kRouteLoginPosition,
            kRouteSpecifyName,
            kRouteSpecifyNameData,
        };
        typedef int RouteType;
        
        struct EXPORT_CLASS RouteInfoBase : public GCloud::ApolloBufferBase
        {
        public:
            bool AllowLost;
            RouteType Type;
            
            RouteInfoBase()
            {
                AllowLost = false;
                Type = kRouteNone;
            }
            
            RouteInfoBase(RouteType routeType)
            {
                AllowLost = false;
                Type = routeType;
            }
            
        public:
            RouteType GetRouteType()const
            {
                return Type;
            }
            
            virtual AObject* Clone()const
            {
                RouteInfoBase* instance = new RouteInfoBase();
                *instance = *this;
                return instance;
            }
            
        protected:
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(Type);
                writer.Write(AllowLost);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                int tmp = 0;
                reader.Read(tmp);
                Type = (RouteType)tmp;
                
                reader.Read(AllowLost);
            }
        };
        
        struct EXPORT_CLASS ZoneRouteInfo : RouteInfoBase
        {
        public:
            unsigned int TypeId;
            unsigned int ZoneId;
            
            ZoneRouteInfo()
            : RouteInfoBase(kRouteZone)
            {
                TypeId = 0;
                ZoneId = 0;
            }
            
        public:
            virtual AObject* Clone()const
            {
                ZoneRouteInfo* instance = new ZoneRouteInfo();
                *instance = *this;
                return instance;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                RouteInfoBase::WriteTo(writer);
                writer.Write(TypeId);
                writer.Write(ZoneId);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                RouteInfoBase::ReadFrom(reader);
                reader.Read(TypeId);
                reader.Read(ZoneId);
            }
            
        };
        
        struct EXPORT_CLASS ServerRouteInfo : RouteInfoBase
        {
        public:
            uint64_t ServerId;
            
            ServerRouteInfo()
            : RouteInfoBase(kRouteServer)
            {
                ServerId = 0;
            }
            
        protected:
            virtual ServerRouteInfo* Clone()const
            {
                ServerRouteInfo* instance = new ServerRouteInfo();
                *instance = *this;
                return instance;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                RouteInfoBase::WriteTo(writer);
                writer.Write(ServerId);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                RouteInfoBase::ReadFrom(reader);
                reader.Read(ServerId);
            }
        };
        
        struct EXPORT_CLASS NameRouteInfo : RouteInfoBase
        {
        public:
            GCloud::AString ServiceName;
            NameRouteInfo()
            : RouteInfoBase(kRouteSpecifyName)
            {
            }
            
        public:
            virtual AObject* Clone()const
            {
                NameRouteInfo* instance = new NameRouteInfo();
                *instance = *this;
                return instance;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                RouteInfoBase::WriteTo(writer);
                writer.Write(ServiceName);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                RouteInfoBase::ReadFrom(reader);
                reader.Read(ServiceName);
            }
            
        };
    
        struct EXPORT_CLASS NameDataRouteInfo : RouteInfoBase
        {
        public:
            GCloud::AString ServiceName;
            GCloud::AString UserData;
            
            NameDataRouteInfo()
            : RouteInfoBase(kRouteSpecifyNameData)
            {
            }
            
        public:
            virtual AObject* Clone()const
            {
                NameDataRouteInfo* instance = new NameDataRouteInfo();
                *instance = *this;
                return instance;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                RouteInfoBase::WriteTo(writer);
                writer.Write(ServiceName);
                writer.Write(UserData);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                RouteInfoBase::ReadFrom(reader);
                reader.Read(ServiceName);
                reader.Read(UserData);
            }
        };
        
        inline RouteInfoBase* CreateRouteInfo(RouteType routeType)
        {
            switch(routeType)
            {
                case kRouteServer:
                {
                    return new ServerRouteInfo();
                }
                case kRouteZone:
                {
                    return new ZoneRouteInfo();
                }
                case kRouteSpecifyName:
                {
                    return new NameRouteInfo();
                }
                case kRouteSpecifyNameData:
                {
                    return new NameDataRouteInfo();
                }
                default:
                {
                    return 0;
                }
            }
        }
        
        class InitializeInfo : public GCloud::ApolloBufferBase
        {
        public:
            //The buffer size is set according to the maximum data of a single Write or Read
            //(GCloudSDK2.0.7 or higher, it is recommended to use MaxSendMessageSize and MaxRecvMessageSize respectively).
            uint32_t MaxBufferSize;
            //The buffer size is set according to the maximum data of a single Write or Read
            //(GCloudSDK2.0.7 or higher, it is recommended to use MaxSendMessageSize and MaxRecvMessageSize respectively).
            uint32_t MaxSendMessage;
            //The receive buffer size is set according to the maximum data size of a single Read (GCloudSDK2.0.7 or higher).
            uint32_t MaxRecvMessage;
            //The encryption algorithm needs to be consistent with the backend TConnd configuration.
            EncryptMethod EncMethod;
            //The key generation method needs to be consistent with the backend TConnd configuration.
            KeyMaking KeyMakingMethod;
            //The Diffie-Hellman key, obtained from Tconnd, is valid when KeyMaking is RawDH or EncDH.
            GCloud::AString DH;
            //The Maximum time taken by creating connection between client and server. The default is 10s.
            uint32_t Timeout;
            //The Connector thread sending and receiving cycle (milliseconds) controls the period of the internal network messaging of the Connector.
            //The default is 10ms. Pay attention to balance performance and efficiency when adjusting the service.
            uint32_t LoopInterval;
            //Whether to clear the buffer when reconnecting.
            bool ClearBufferWhenReconnect;
            
        protected:
            uint32_t InfoType;
            
        public:
            InitializeInfo()
            : MaxBufferSize(0)
            , MaxSendMessage(0)
            , MaxRecvMessage(0)
            , EncMethod(kEncryptNone)
            , KeyMakingMethod(kKeyMakingNone)
            , Timeout(10)
            , LoopInterval(10)
            , ClearBufferWhenReconnect(false)
            , InfoType(0)
            {
            }
            
            virtual ~InitializeInfo()
            {
            }
            
            uint32_t GetInfoType() const
            {
                return InfoType;
            }
            
        public:
            virtual AObject* Clone()const
            {
                InitializeInfo* clone = new InitializeInfo();
                *clone = *this;
                return clone;
            }

            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(MaxBufferSize);
                writer.Write(MaxSendMessage);
                writer.Write(MaxRecvMessage);
                writer.Write(EncMethod);
                writer.Write(KeyMakingMethod);
                writer.Write(DH);
                writer.Write(Timeout);
                writer.Write(LoopInterval);
                writer.Write(ClearBufferWhenReconnect);
                writer.Write(InfoType);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                reader.Read(MaxBufferSize);
                reader.Read(MaxSendMessage);
                reader.Read(MaxRecvMessage);
                int temp = 0;
                reader.Read(temp);
                EncMethod = (EncryptMethod)temp;
                reader.Read(temp);
                KeyMakingMethod = (KeyMaking)temp;
                reader.Read(DH);
                reader.Read(Timeout);
                reader.Read(LoopInterval);
                reader.Read(ClearBufferWhenReconnect);
                reader.Read(InfoType);
            }
        };
        
        
        class TInitializeInfo : public Conn::InitializeInfo
        {
        public:
            
        public:
            TInitializeInfo()
            {
                InfoType = kTConnd;
            }
            
        protected:
            virtual InitializeInfo* Clone()const
            {
                TInitializeInfo* clone = new TInitializeInfo();
                *clone = *this;
                return clone;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                Conn::InitializeInfo::WriteTo(writer);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                Conn::InitializeInfo::ReadFrom(reader);
            }
        };
        
        class GInitializeInfo : public Conn::InitializeInfo
        {
        public:
            uint64_t UnitID;
            GCloud::AString ServiceName;
            
        public:
            GInitializeInfo()
            : UnitID(0)
            {
                InfoType = kGConnd;
            }
        protected:
            virtual InitializeInfo* Clone()const
            {
                GInitializeInfo* clone = new GInitializeInfo();
                *clone = *this;
                return clone;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                Conn::InitializeInfo::WriteTo(writer);
                writer.Write(UnitID);
                writer.Write(ServiceName);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                Conn::InitializeInfo::ReadFrom(reader);
                reader.Read(UnitID);
                reader.Read(ServiceName);
            }
        };
        
        struct EXPORT_CLASS ConnectedInfo : public GCloud::ApolloBufferBase
        {
        public:
            GCloud::AString  currentIP;
            uint64_t currentServerID;

        public:
            
            virtual AObject* Clone()const
            {
                ConnectedInfo* instance = new ConnectedInfo();
                *instance = *this;
                return instance;
            }
            
        protected:
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(currentIP);
                writer.Write(currentServerID);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                reader.Read(currentIP);
                reader.Read(currentServerID);
            }
        };
    
        enum ClientType {
            kClientPC       = 0,
            kClientAndroid  = 101,
            kClientIOS      = 102,
            kClientMac      = 103,
            kClientWin      = 104,
            
            kClientSwitch   = 110,
            kClientPS       = 120,
            kClientXbox     = 130,
        };
        
        enum AuthType {
            kAuthNone = 0,
            kAuthMSDKv3 = 32767,
            kAuthMSDKv5 = 4096,
            kAuthWeGame = 4101,
            kAuthMSDKPC = 4102,
            kAuthMSDKPCUID = 4105,
            kAuthMSDKV5UID = 4112,
            kAuthINTL   = 4117,
        };

        enum StopReason
        {
            kStopReasonSuccess = 0,
            kStopReasonIdleClose = 1,
            kStopReasonPeerClose = 2,
            kStopReasonNetworkFailed = 3,
            kStopReasonBadPackageLen = 4,
            kStopReasonExceedLimit = 5,
            kStopReasonTConndShutdown = 6,
            kStopReasonSelfClose = 7,
            kStopReasonAuthFailed = 8,
            kStopReasonSynAckFailed = 9,
            kStopReasonWriteBlocked = 10,
            kStopReasonSequenceInvalid = 11,
            kStopReasonTransRelay = 12,
            kStopReasonTransLost = 13,
            kStopReasonRelayFailed = 14,
            kStopReasonSessionRenewFailed = 15,
            kStopReasonRecvBuffFull = 16,
            kStopReasonUnpackFailed = 17,
            kStopReasonInvalidPackage = 18,
            kStopReasonInvalidSkey = 19,
            kStopReasonVerifyDup = 20,
            kStopReasonClientClose = 21,
            kStopReasonPreRelayFailed = 22,
            kStopReasonSystemError = 23,
            kStopReasonClientReconnect = 24,
            kStopReasonGenKeyFailed = 25,
            kStopReasonIDMappingFailed = 26,
            kStopReasonSvrConfirmTimeout = 27, // Waiting for GameSvr's Start response
            kStopReasonRoutingFailed = 28,
            kStopReasonTConndUnreachable = 29, // occured in Rounting Mode
            kStopReasonLoginOnNewSvr = 30,
            kStopReasonCanNotFindRoute = 31,
            kStopReasonClusterWaitQueueTimeout = 32,
            kStopReasonClusterPushQueueFailed = 33,
            kStopReasonAuthParamInvalidInRequest = 34,
            kStopReasonGetClusterRouteFailed = 35,
        };
        
        const char* GetStopReasonString(Conn::StopReason reason);
        
    }// Conn
}

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif /* ConnectorPublicDefine_h */
