//
//  INameService.h
//  Apollo
//
//  Created by vforkk on 12/8/15.
//  Copyright © 2015 TSF4G. All rights reserved.
//

#ifndef Apollo_INameService_h
#define Apollo_INameService_h
#include "AArray.h"
#include "AString.h"
#include "ApolloBuffer.h"

namespace GCloud {
    
    
    enum ApoErrorCode
    {
        ApoResultSuccess,
        ApoErrorInnerError,
        ApoErrorUnknown,
        
        ApoErrorInvalidParam,
        ApoErrorSystemError,
        ApoErrorTimeout,
        
        // rpc
        ApoErrorSendError = 50,
        ApoErrorRecvError,
        
        // Apo
        ApoErrorInvalidGameId = 100,
        ApoErrorNoPermission,
        ApoErrorPlatformNotFound,
        ApoErrorLeafNotFound,
        
        
        //const int pebble::rpc::ErrorInfo::kRpcNoRrror = 0;
        //const int pebble::rpc::ErrorInfo::kInitZKFailed = -1;
        //const int pebble::rpc::ErrorInfo::kRpcTimeoutError = -2;
        //const int pebble::rpc::ErrorInfo::kResolveServiceAddressError = -3;
        //const int pebble::rpc::ErrorInfo::kSendRequestFailed = -4;
        //const int pebble::rpc::ErrorInfo::kCreateServiceInstanceFailed = -5;
        //const int pebble::rpc::ErrorInfo::kInvalidPara = -6;
        //const int pebble::rpc::ErrorInfo::kRecvException = -7;
        //const int pebble::rpc::ErrorInfo::kRecvFailed = -8;
        //const int pebble::rpc::ErrorInfo::kMsgTypeError = -9;
        //const int pebble::rpc::ErrorInfo::kOtherException = -10;
        //const int pebble::rpc::ErrorInfo::kMissingResult  = -11;
        //const int pebble::rpc::ErrorInfo::kSystemError = -100;
    };
    
    typedef struct _tagApoResult : public GCloud::ApolloBufferBase
    {
        ApoErrorCode ErrorCode;
        GCloud::AString Reason;
        int Extend;
        
        //
        // Construtions
        //
    public:
        _tagApoResult()
        : ErrorCode(ApoResultSuccess)
        , Extend(0)
        {
            
        }
        
        _tagApoResult(ApoErrorCode errorCode)
        : ErrorCode(errorCode)
        , Extend(0)
        {
            
        }
        
        _tagApoResult(ApoErrorCode errorCode, const char* reason)
        : ErrorCode(errorCode)
        , Reason(reason)
        , Extend(0)
        {
            
        }
        
        _tagApoResult(ApoErrorCode errorCode, int ext, const char* reason)
        : ErrorCode(errorCode)
        , Reason(reason)
        , Extend(ext)
        {
            
        }
        
        //
        // static functions
        //
    public:
        bool IsSuccess()const
        {
            return ErrorCode == ApoResultSuccess;
        }
        
        
    public:
        virtual AObject* Clone()const
        {
            _tagApoResult* clone = new _tagApoResult();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& write)const
        {
            write.Write(ErrorCode);
            write.Write(Reason);
            write.Write(Extend);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            int tmp;
            reader.Read(tmp);
            ErrorCode = (ApoErrorCode)tmp;
            reader.Read(Reason);
            reader.Read(Extend);
        }
    }ApoResult;
    
    typedef struct _tagIPCollection : public GCloud::ApolloBufferBase
    {
    public:
        GCloud::AArray/*AString**/ IPList;
        
        
    protected:
        virtual AObject* Clone()const
        {
            _tagIPCollection* clone = new _tagIPCollection();
            *clone = *this;
            
            return clone;
        }
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(IPList);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read<GCloud::AString>(IPList);
        }
    }IPCollection;
    
    class INameServiceObserver
    {
    public:
        virtual void OnQueryNameResult(ApoResult errorCode, const IPCollection* ipList) = 0;
    };
    
    class INameService
    {
    public:
        virtual ~INameService(){}
        
    public:
        virtual void Query(const char* name) = 0;
        virtual void Update() = 0;
        
    public:
        virtual void SetObserver(INameServiceObserver* observer) = 0;
        //virtual void RemoveObserver(CNameServiceObserver* observer) = 0;
    };
}

#endif /* INameService_h */
