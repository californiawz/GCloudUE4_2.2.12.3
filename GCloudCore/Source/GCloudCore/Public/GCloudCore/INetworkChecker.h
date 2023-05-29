//
// Created by tiniazhu on 2018/7/27.
// ABase
//

#ifndef ABASE_INETWORKCHECKER_H
#define ABASE_INETWORKCHECKER_H
#include "AArray.h"
#include "AString.h"
#include "ApolloBuffer.h"
#include "ApolloBufferReader.h"

namespace ABase
{
    class PingResult : public ABase::ApolloBufferBase{
    public:
        virtual AObject* Clone()const{
            PingResult* clone = new PingResult();
            *clone = *this;
            return clone;
        };
        
        virtual void WriteTo(ABase::CApolloBufferWriter& writer)const
        {
            writer.Write(Tag);
            writer.Write(Destination);
            writer.Write(SendPacketsNumber);
            writer.Write(ReceivedPacketsNumber);
//            writer.Write(_packetLoss);
            writer.Write(TotalTimeMS);
            writer.Write(MinRTTTimeMS);
            writer.Write(AvgRTTTimeMS);
            writer.Write(MaxRTTTimeMS);
            writer.Write(ResultCode);
        }
        
        virtual void ReadFrom(ABase::CApolloBufferReader& reader)
        {
            reader.Read(Tag);
            reader.Read(Destination);
            reader.Read(SendPacketsNumber);
            reader.Read(ReceivedPacketsNumber);
//            reader.Read(_packetLoss);
            reader.Read(TotalTimeMS);
            reader.Read(MinRTTTimeMS);
            reader.Read(AvgRTTTimeMS);
            reader.Read(MaxRTTTimeMS);
            reader.Read(ResultCode);
        }
        PingResult& operator=(const PingResult& other)
        {
            Tag = other.Tag;
            Destination = other.Destination;
            SendPacketsNumber = other.SendPacketsNumber;
            ReceivedPacketsNumber = other.ReceivedPacketsNumber;
//            _packetLoss = other._packetLoss;
            TotalTimeMS = other.TotalTimeMS;
            MinRTTTimeMS = other.MinRTTTimeMS;
            AvgRTTTimeMS = other.AvgRTTTimeMS;
            MaxRTTTimeMS = other.MaxRTTTimeMS;
            ResultCode = other.ResultCode;
            return *this;
        }
    public:
        int Tag;
        AString Destination;
        int SendPacketsNumber;
        int ReceivedPacketsNumber;
//        int _packetLoss;
        int TotalTimeMS;
        int MinRTTTimeMS;
        int AvgRTTTimeMS;
        int MaxRTTTimeMS;
        int ResultCode;
    };
    class TraceRouteMessage: public ABase::ApolloBufferBase{
    public:
        virtual AObject* Clone()const{
            TraceRouteMessage* clone = new TraceRouteMessage();
            *clone = *this;
            return clone;
        };
        virtual void WriteTo(ABase::CApolloBufferWriter& writer)const
        {
            writer.Write(Address);
            writer.Write(AvgDelay);
        }
        
        virtual void ReadFrom(ABase::CApolloBufferReader& reader)
        {
            reader.Read(Address);
            reader.Read(AvgDelay);
        }
        TraceRouteMessage& operator=(const TraceRouteMessage& other)
        {
            Address = other.Address;
            AvgDelay = other.AvgDelay;
            return *this;
        }
    public:
        AString Address;
        AString AvgDelay;
    };
    
    class TraceRouteResult : public ABase::ApolloBufferBase{
    public:
        virtual AObject* Clone()const{
            TraceRouteResult* clone = new TraceRouteResult();
            *clone = *this;
            return clone;
        };
        
        virtual void WriteTo(ABase::CApolloBufferWriter& writer)const
        {
            writer.Write(Tag);
            writer.Write(Destination);
            writer.Write(NodeNumber);
            writer.Write(TraceRouteMessages);
            writer.Write(ResultCode);
        }
        
        virtual void ReadFrom(ABase::CApolloBufferReader& reader)
        {
            reader.Read(Tag);
            reader.Read(Destination);
            reader.Read(NodeNumber);
            reader.Read<TraceRouteMessage>(TraceRouteMessages);
            reader.Read(ResultCode);
        }
        TraceRouteResult& operator=(const TraceRouteResult& other)
        {
            Tag = other.Tag;
            Destination = other.Destination;
            NodeNumber = other.NodeNumber;
            TraceRouteMessages = other.TraceRouteMessages;
            ResultCode = other.ResultCode;
            return *this;
        }
        int Tag;
        AString Destination;
        int NodeNumber;
        AArray TraceRouteMessages;
        int ResultCode;
    };
    
    class NSLookupResult : public ABase::ApolloBufferBase{
    public:
        virtual AObject* Clone()const{
            NSLookupResult* clone = new NSLookupResult();
            *clone = *this;
            return clone;
        };
        
        virtual void WriteTo(ABase::CApolloBufferWriter& writer)const
        {
            writer.Write(Tag);
            writer.Write(Destination);
            writer.Write(Addresses);
            writer.Write(ResultCode);
        }
        
        virtual void ReadFrom(ABase::CApolloBufferReader& reader)
        {
            reader.Read(Tag);
            reader.Read(Destination);
            reader.Read<AString>(Addresses);
            reader.Read(ResultCode);
        }
        NSLookupResult& operator=(const NSLookupResult& other)
        {
            Tag = other.Tag;
            Destination = other.Destination;
            Addresses = other.Addresses;
            ResultCode = other.ResultCode;
            return *this;
        }
//    public:
//        int GetId(){ return  Tag;}
//        void SetId(const int id){Tag = id;}
//
//        AString &GetDestination(){ return Destination;}
//        void SetDestination(const AString &destination){Destination = destination;}
//
//        int GetResultCode(){ return  ResultCode;}
//        void SetResultCode(const uint8_t resultCode){ResultCode = resultCode;}
//
//        AArray &GetAddresses(){return Addresses;}
//        void SetAddresses(const AArray &addresses){ Addresses = addresses; }
    public:
        int Tag;
        AString Destination;
        int ResultCode;
        AArray Addresses;
    };
    
    typedef void (*NetworkCheckerPingCallback)(PingResult &s);
    typedef void (*NetworkCheckerTraceRouteCallback)(TraceRouteResult &s);
    typedef void (*NetworkCheckerNSLookupCallback)(NSLookupResult &s);
    class EXPORT_CLASS INetworkChecker
    {
        
    public:
        static INetworkChecker& GetInstance();
    public:
        
        /*
         Ping指令
         @param ipAddress  要ping的ip地址
         @param callback   回调操作
         @param timeOut    每个ping包的超时时间(s),默认为1(s)
         @param packageNum icmp包个数，默认为4
         */
        virtual void Ping(const char* ipAddress,int tag,NetworkCheckerPingCallback callback,uint8_t timeOut=4,uint8_t packageNum=4) = 0;
        
        /*
         模拟TraceRoute指令
         @param IPAddress 要TraceRoute的ip地址
         @param totalTTL总跳数
         @param callback 回调函数指针
         */
        virtual void TraceRoute(const char* ipAddress,int tag,NetworkCheckerTraceRouteCallback callback,uint8_t totalTTL=30) = 0;
        
        /*
         模拟NSLookup指令
         @param IPAddress 要NSLookup的ip地址
         @param callback 回调函数指针
         */
        virtual void NSLookup(const char* ipAddress,int tag,NetworkCheckerNSLookupCallback callback) = 0;
        
        
    };
}
#endif //ABASE_INETWORKCHECKER_H
