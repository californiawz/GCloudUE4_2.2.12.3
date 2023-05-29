//
//  GCloudPublicDefine.h
//  TGSF
//
//  Created by vforkk on 14/1/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef _GCloud_PublicDefine_h
#define _GCloud_PublicDefine_h

#include <stdio.h>
#include <sstream>
#include <vector>
#include "ApolloBuffer.h"
#include "AString.h"
#include "GCloudInnerDefine.h"
#if defined(_WIN32) || defined(_WIN64)
#define snprintf _snprintf
#pragma warning(push)
#pragma warning(disable:4996)
#endif

namespace GCloud {
    
    ///////////////////////////////////////////////////////////////////////////////////
    // Macro & enum
    ///////////////////////////////////////////////////////////////////////////////////
    
    
#define ASYN
#define SYN
    
#define IN
#define OUT
#define INOUT
    
    
    typedef long long SeqId;
#define INVALID_ID -1
    
    static const char* kPluginNameNone = "None";
    static const char* kPluginNameMsdk =  "MSDK";
    
    typedef const char* PluginName;
    
    // Platform
    
    enum
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
        
        kErrorInvalidGameId,
        
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
        
        // PayService, from 300
        // Common  from 400
        
        
        // TDir from 500
        kErrorLeafNotFound = 500,
        kErrorPlatformNotFound,
        kErrorAccDisabled,
        
        
        // LBS from 600
        kErrorLbsNeedOpenLocation = 600,
        kErrorLbsLocateFail,
        
        // LEAP from 700-799
        kErrorSimpleClientNull = 700,
        kErrorMSDGClientOffline = 701,
        
        kErrorOverlappingAccess = 710,
        
        kErrorSaveInvalidData = 731,
        kErrorSaveDataTooBig  = 732,
        kErrorSaveInvalidType = 733,
        kErrorSaveOverflowKeyLimit = 734,
        kErrorSaveFailedToAllocate = 735,
        
        kErrorLoadNoData      = 751,
        kErrorLoadInvalidType = 752,
        kErrorLoadFailedToAllocate = 753,
        
        kErrorOrderParamsInvalid = 771,
        kErrorOrderFailedToAllocate = 772,
        kErrorOrderTimeout = 773,
        
        kErrorEasyPayUnderProcessing = 781,
        kErrorEasyPayError = 782,
        kErrorEasyPayCancel = 783,
        kErrorEasyPayParamError = 784,
        kErrorEasyPayNeedLogin = 785,
        
        kErrorSetDeliveredNonexistent = 791,
        kErrorSetDeliveredParamsInvalid = 792,
        
        kErrorOthers = 10000,
        
    };
    typedef int EErrorCode;
    
    struct EXPORT_CLASS Result : public GCloud::ApolloBufferBase
    {
        EErrorCode ErrorCode;
        GCloud::AString Reason;
        int Extend;
        int Extend2;
        //
        // Construtions
        //
    public:
        Result()
        : ErrorCode(kSuccess)
        , Extend(0)
        , Extend2(0)
        {
            
        }
        
        Result(EErrorCode errorCode)
        : ErrorCode(errorCode)
        , Extend(0)
        , Extend2(0)
        {
            
        }
        
        Result(EErrorCode errorCode, const char* reason)
        : ErrorCode(errorCode)
        , Reason(reason)
        , Extend(0)
        , Extend2(0)
        {
            
        }
        
        Result(EErrorCode errorCode, int ext, const char* reason)
        : ErrorCode(errorCode)
        , Reason(reason)
        , Extend(ext)
        , Extend2(0)
        {
            
        }
        
        Result(EErrorCode errorCode, int ext, int ext2, const char* reason)
        : ErrorCode(errorCode)
        , Reason(reason)
        , Extend(ext)
        , Extend2(ext2)
        {
            
        }
        
        Result(const Result& r)
        {
            ErrorCode = r.ErrorCode;
            Reason = r.Reason;
            Extend = r.Extend;
            Extend2= r.Extend2;
        }
        
        //
        // static functions
        //
    public:
        
        
        void Reset(EErrorCode error, const char* reason = "")
        {
            ErrorCode = error;
            Reason = reason;
            Extend = 0;
            Extend2 = 0;
        }
        
        void Success()
        {
            ErrorCode = kSuccess;
            Reason = "";
            Extend = 0;
            Extend2 = 0;
        }
        
        bool IsSuccess()const
        {
            return ErrorCode == kSuccess;
        }
        
        GCloud::AString ToString()const
        {
            char buf[50]={0};
            snprintf(buf, sizeof(buf), "%d, ext:%d, ext2:%d, ", ErrorCode, Extend, Extend2);
            
            GCloud::AString desc;
            desc = buf;
            desc += Reason;
            return desc;
        }
        
        bool operator == (EErrorCode errorCode)const
        {
            return ErrorCode == errorCode;
        }
        
        bool operator != (EErrorCode errorCode)const
        {
            return ErrorCode != errorCode;
        }
        
    public:
        virtual AObject* Clone()const;
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& write)const
        {
            write.Write(ErrorCode);
            write.Write(Reason);
            write.Write(Extend);
            write.Write(Extend2);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            int tmp;
            reader.Read(tmp);
            ErrorCode = (EErrorCode)tmp;
            reader.Read(Reason);
            reader.Read(Extend);
            reader.Read(Extend2);
        }
    };
    
    // Log
    typedef enum
    {
        kDebug,
        kInfo,
        kWarning,
        kEvent,
        kError,
        kNone,
    }LogPriority;
    
    
    typedef int StopReason;
    
    struct EXPORT_CLASS InitializeInfo : public GCloud::ApolloBufferBase
    {
        GCloud::AString PluginName;
        uint64_t GameId;
        GCloud::AString GameKey;
        GCloud::AString EncKey;
        
    public:
        InitializeInfo()
        : GameId(0)
        {
            
        }
        
        InitializeInfo(uint64_t gameId, const char* gameKey, const char* pluginName = "")
        {
            PluginName = pluginName;
            GameId = gameId;
            GameKey = gameKey;
        }
        
        
    public:
        virtual AObject* Clone()const;
        
        void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(PluginName);
            writer.Write(GameId);
            writer.Write(GameKey);
            writer.Write(EncKey);
        }
        
        void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(PluginName);
            reader.Read(GameId);
            reader.Read(GameKey);
            reader.Read(EncKey);
        }
    };
    
    
    
    ///////////////////////////////////////////////////////////////////////////////////
    // Inline Function
    ///////////////////////////////////////////////////////////////////////////////////
    
    inline GCloud::AString replace( const GCloud::AString& inStr, const char* pSrc, const char* pReplace )
    {
        if (inStr.length() == 0) {
            return "";
        }
        std::string strSrc = inStr.c_str()?inStr.c_str():"";
        std::string::size_type pos=0;
        std::string::size_type srclen = strlen( pSrc );
        std::string::size_type dstlen = strlen( pReplace );
        while( (pos=strSrc.find(pSrc, pos)) != std::string::npos)
        {
            strSrc.replace(pos, srclen, pReplace);
            pos += dstlen;
        }
        return strSrc.c_str();
    }
    
    inline GCloud::AString replaceString(GCloud::AString& src)
    {
        src = replace(src, "%", "%25");
        src = replace(src, "&", "%26");
        src = replace(src, "=", "%3d");
        return src;
    }
    
    inline GCloud::AString replaceStringQuto(GCloud::AString& src)
    {
        src = replace(src, "%", "%25");
        src = replace(src, "&", "%26");
        src = replace(src, "=", "%3d");
        src = replace(src, ",", "%2c");
        return src;
    }
    
    ///////////////////////////////////////////////////////////////////////////////////
    // Public Structure
    ///////////////////////////////////////////////////////////////////////////////////
    
    // TokenType
    enum
    {
        kTokenNone = 0,
        kTokenAccess = 1,
        kTokenRefresh = 2,
        kTokenPay = 3,
        kTokenPf = 4,
        kTokenPfKey = 5,
    };
    typedef int TokenType;
    
    // Token
    struct EXPORT_CLASS Token  : public GCloud::ApolloBufferBase{
        TokenType eType;   //ST  OR  OPEN
        GCloud::AString strValue;
        int64_t llExpire; // s
        Token()
        : eType(kTokenNone)
        , llExpire(0)
        {
        }
        
    public:
        virtual AObject* Clone()const;
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(eType);
            writer.Write(strValue);
            writer.Write(llExpire);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(eType);
            reader.Read(strValue);
            reader.Read(llExpire);
        }
        
        void ToString(GCloud::AString& str) const
        {
            str += "Type=";
            str += int2str((int)eType).c_str();
            
            GCloud::AString value = strValue;
            str += "&Value=" + replaceString(value);
            str += "&Expire=";
            str += int2str((int)llExpire).c_str();
        }
    };
    
    // AccountInfo
    struct EXPORT_CLASS AccountInfo : public GCloud::ApolloBufferBase
    {
        ChannelType Channel; //wtlogin
        GCloud::AString OpenId;    //
        GCloud::AString UserId; // diff from OpenId in some special Plugins(Netmarble, etc), otherwise, it's as same as OpenId
        GCloud::AArray/*Token*/ vecTokenList;
        AccountInfo()
        :Channel(kChannelNone)
        {
            Reset();
        }
        
    public:
        const char* GetToken(TokenType type) const
        {
            for (int i = 0; i<vecTokenList.Count(); i++) {
                const Token* token = (const Token*)vecTokenList[i];
                if (token->eType == type) {
                    return token->strValue.c_str();
                }
            }
            return 0;
        }
        
        int GetTokenLen(TokenType type) const
        {
            for (int i = 0; i<vecTokenList.Count(); i++) {
                const Token* token = (const Token*)vecTokenList[i];
                if (token->eType == type) {
                    return (int)token->strValue.size();
                }
            }
            return 0;
        }
        
        void SetToken(TokenType type, const char* pszToken, long long llExpire)
        {
            if (pszToken) {
                for (int i = 0; i<vecTokenList.Count(); i++) {
                    Token* token = (Token*)vecTokenList[i];
                    if (token->eType == type) {
                        token->strValue = pszToken;
                        token->llExpire = llExpire;
                        return;
                    }
                }
                
                Token tk;
                tk.eType = type;
                tk.strValue = pszToken;
                tk.llExpire = llExpire;
                vecTokenList.Add(tk);
            }
        }
        
        void SetToken(TokenType type, const char* pszToken, int size, long long llExpire)
        {
            if (pszToken) {
                for (int i = 0; i<vecTokenList.Count(); i++) {
                    Token* token = (Token*)vecTokenList[i];
                    if (token->eType == type) {
                        token->strValue.assign(pszToken, size);
                        token->llExpire = llExpire;
                        return;
                    }
                }
                
                Token tk;
                tk.eType = type;
                tk.strValue.assign(pszToken, size);
                tk.llExpire = llExpire;
                vecTokenList.Add(tk);
            }
        }
        
    public:
        void Reset()
        {
            Channel = kChannelNone;
            OpenId.clear();
            vecTokenList.RemoveAll();
        }
        
    public:
        virtual AObject* Clone()const;
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(Channel);
            writer.Write(OpenId);
            writer.Write(UserId);
            writer.Write(vecTokenList);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(Channel);
            reader.Read(OpenId);
            reader.Read(UserId);
            reader.Read<Token>(vecTokenList);
        }
        
    };

    struct EXPORT_CLASS WaitingInfo : public GCloud::ApolloBufferBase
    {
        unsigned int Position;          //
        unsigned int QueueLen;     //
        unsigned int EstimateTime;
        WaitingInfo()
        : Position(0)
        , QueueLen(0)
        , EstimateTime(0)
        {
            
        }
        
    public:
        virtual AObject* Clone()const;
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(Position);
            writer.Write(QueueLen);
            writer.Write(EstimateTime);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(Position);
            reader.Read(QueueLen);
            reader.Read(EstimateTime);
        }
    };
    
    enum
    {
        kRouteNone = 0,
        kRouteZone,
        kRouteServer,
        kRouteLoginPosition,
        kRouteSpecifyName,
    };
    typedef int RouteType;
    
    struct EXPORT_CLASS RouteInfoBase : public GCloud::ApolloBufferBase
    {
    public:
        bool AllowLost;
    protected:
        RouteType Type;
        RouteInfoBase(::GCloud::RouteType routeType)
        {
            AllowLost = false;
            Type = routeType;
        }
        
    public:
        virtual ~RouteInfoBase(){}
        
    public:
        ::GCloud::RouteType GetRouteType()const
        {
            return Type;
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
        virtual AObject* Clone()const;
        
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
        
    public:
        void ToString(GCloud::AString& str) const
        {
            str += "ServerId=" + ull2str(ServerId);
        }
        
    protected:
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
        
        virtual RouteInfoBase* Clone()const;
        
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
        virtual AObject* Clone()const;
        
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
    
    RouteInfoBase* CreateRouteInfo(RouteType routeType);
    
    // LoginInfo
    struct EXPORT_CLASS ConnectedInfo : public GCloud::ApolloBufferBase
    {
        AccountInfo Account;
        ServerRouteInfo ServerRoute;
        WaitingInfo Waiting;
        GCloud::AString ConnectIP;
        ConnectedInfo()
        {
            
        }
        
        void Reset()
        {
            Account.Reset();
        }
        
    public:
        virtual AObject* Clone()const;
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(Account);
            writer.Write(ServerRoute);
            writer.Write(Waiting);
            writer.Write(ConnectIP);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(Account);
            reader.Read(ServerRoute);
            reader.Read(Waiting);
            reader.Read(ConnectIP);
        }
    };
    
    struct EXPORT_CLASS UserInfo: public GCloud::ApolloBufferBase
    {
        int ChannelID;
        GCloud::AString OpenID;
        UserInfo():ChannelID(0)
        {
        }
    public:
        virtual AObject* Clone()const;
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(ChannelID);
            writer.Write(OpenID);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(ChannelID);
            reader.Read(OpenID);
        }
        bool operator == (UserInfo userInfo)const
        {
            if(OpenID==userInfo.OpenID&&ChannelID==userInfo.ChannelID)
            {
                return true;
            }
            return false;
        }
        
        bool operator != (UserInfo userInfo)const
        {
            if(OpenID==userInfo.OpenID&&ChannelID==userInfo.ChannelID)
            {
                return false;
            }
            return true;
        }
    };
    
    
    
}

#if defined(_WIN32) || defined(_WIN64)
typedef void (__stdcall *GCloudLogCallback)(GCloud::LogPriority pri, const char* msg);
#else
typedef void (*GCloudLogCallback)(GCloud::LogPriority pri, const char* msg);
#endif

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif
