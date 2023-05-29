//
//  QueuePublicDefine.h
//  GCloudQueue
//
//  Created by teddyzhang on 2019/8/14.
//  Copyright © 2019 GCloud. All rights reserved.
//

#ifndef QueuePublicDefine_h
#define QueuePublicDefine_h

#include "ApolloBuffer.h"
#include "GCloudPublicDefine.h"
#include "ConnectorPublicDefine.h"

namespace GCloud
{

    typedef struct _tagQueueInitInfo : public GCloud::ApolloBufferBase
    {
    public:
        GCloud::AString Url;
        GCloud::AString AppId;
        GCloud::AString OpenId;
        GCloud::AString Token;
        int AuthType;
        int Channel;
        bool EnableManualUpdate;
        
    public:
        _tagQueueInitInfo()
            : AuthType(Conn::kAuthNone)
            , Channel(Conn::kChannelNone)
            , EnableManualUpdate(false)
        {
        }
        
    public:
        virtual AObject* Clone() const
        {
            _tagQueueInitInfo* clone = new _tagQueueInitInfo(*this);
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(Url);
            writer.Write(AppId);
            writer.Write(OpenId);
            writer.Write(Token);
            writer.Write(AuthType);
            writer.Write(Channel);
            writer.Write(EnableManualUpdate);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(Url);
            reader.Read(AppId);
            reader.Read(OpenId);
            reader.Read(Token);
            reader.Read(AuthType);
            reader.Read(Channel);
            reader.Read(EnableManualUpdate);
        }
        
    } QueueInitInfo;

    enum QueueStatusType
    {
        QSTypeInvalid = 0,
        QSTypeJoinQueue = 1,
        QSTypeExitQueue = 2,
        QSTypeStatus = 3,
    };

    typedef struct _tagQueueStatusInfo : public GCloud::ApolloBufferBase
    {
    public:
        QueueStatusType Type;
        EErrorCode ErrCode;
        GCloud::AString ErrMsg;
        int CurPosition;
        int TotalCount;
        int EstimatedTime;

    public:
        _tagQueueStatusInfo() : CurPosition(-1),  TotalCount(0), EstimatedTime(-1)
        {
        }
        
    public:
        virtual AObject* Clone() const
        {
            _tagQueueStatusInfo* clone = new _tagQueueStatusInfo(*this);
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write((int)Type);
            writer.Write((int)ErrCode);
            writer.Write(ErrMsg);
            writer.Write(CurPosition);
            writer.Write(TotalCount);
            writer.Write(EstimatedTime);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            int enumValue = 0;

            reader.Read(enumValue);
            Type = (QueueStatusType)enumValue;
            
            reader.Read(enumValue);
            ErrCode = (EErrorCode)enumValue;

            reader.Read(ErrMsg);

            reader.Read(CurPosition);
            reader.Read(TotalCount);
            reader.Read(EstimatedTime);
        }

    } QueueStatusInfo;


    typedef struct _tagQueueFinishedInfo : public GCloud::ApolloBufferBase
    {
    public:
        EErrorCode ErrCode;
        GCloud::AString ErrMsg;
        GCloud::AString Token;
        GCloud::AString PassTime;
        GCloud::AString JoinTime;
        
    public:
        _tagQueueFinishedInfo()
        {
        }
        
    public:
        virtual AObject* Clone() const
        {
            _tagQueueFinishedInfo* clone = new _tagQueueFinishedInfo(*this);
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write((int)ErrCode);
            writer.Write(ErrMsg);
            writer.Write(Token);
            writer.Write(PassTime);
            writer.Write(JoinTime);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            int enumValue = 0;

            reader.Read(enumValue);
            ErrCode = (EErrorCode)enumValue;

            reader.Read(ErrMsg);
            reader.Read(Token);
            reader.Read(PassTime);
            reader.Read(JoinTime);
        }

    } QueueFinishedInfo;

}

#endif /* QueuePublicDefine_h */
