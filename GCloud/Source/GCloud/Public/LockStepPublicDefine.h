//
//  LockStepPublicDefine.h
//  LockStep
//
//  Created by vforkk on 6/21/16.
//  Copyright © 2016 vforkk. All rights reserved.
//

#ifndef _GCloud_LockStepPublicDefine_h
#define _GCloud_LockStepPublicDefine_h
#include "AString.h"
#include "ApolloBuffer.h"
#include "AArray.h"

namespace GCloud
{
    namespace LockStep
    {
        enum LockStepProtocol
        {
            kLsUdp,
            kLsRUdp,
            kLsTcp,
        };
        
        enum LockStepInputFlag
        {
            kLsInputFlagNone = 0,
            kLsInputFlagSubscribable = 0x01,
            kLsInputFlagDuplicateUpstream = 0x10,
        };
        
        enum LockStepBroadcastFlag
        {
            kLsBroadcastFlagNone = 0,
            kLsBroadcastFlagSubscribable = 0x01,
            kLsBroadcastFlagGameServerOnly = 0x02,
            kLsBroadcastFlagDuplicateUpstream = 0x10,
            kLsBroadcastFlagDuplicateDownstream = 0x20,
            kLsBroadcastFlagDownstreamReliable = 0x40,
        };
        
        enum LockStepErrorCode
        {
            kLsSuccess = 0,
            kLsConnectFailed = 1,
            kLsNetworkException = 2,
            kLsTimeout = 3,
            kLsUnknown = 4,
            
            kLsSessionStop =5,
            kLsServerFull = 6,
            kLsStayInQueue = 7,
            
            kLsRoomNotFound = 8,
            kLsUserNotFound = 9,
            
            kLsAuthFailed = 10,
            kLsLogoutNotFinished = 11,
			kLsUninitialized = 12,
			kLsLastLoginNotFinished = 13,
			kLsAlreadyLogged = 14,
            
            kLsBusinessError = 100,
        };

		// kLsStatusUninitialized => kLsStatusIdle => kLsStatusLogining => kLsStatusLogined => kLsStatusLogouting => kLsStatusIdle
		enum LockStepStatus
		{
			kLsStatusUninitialized = 0,
			kLsStatusIdle = 1,
			kLsStatusLogining = 2,
			kLsStatusLogined = 3,
			kLsStatusLogouting = 4,
		};
        
        class LockStepResult : public GCloud::ApolloBufferBase
        {
        public:
            LockStepErrorCode Error;
            GCloud::AString Reason;
            int ExtCode;
            int ExtCode2;
            
        public:
            LockStepResult()
            : Error(kLsSuccess)
            , ExtCode(0)
            , ExtCode2(0)
            {
                
            }
            
        public:
            void Success()
            {
                Error = kLsSuccess;
                ExtCode = 0;
                ExtCode2 = 0;
                Reason = "";
            }
            
            bool IsSuccess()const
            {
                return Error == kLsSuccess;
            }
            
            void Reset(LockStepErrorCode error, const char* reason = "")
            {
                Error = error;
                Reason = reason;
                ExtCode = 0;
                ExtCode2 = 0;
            }
            
        public:
            virtual AObject* Clone()const
            {
                LockStepResult* copy = new LockStepResult();
                *copy = *this;
                return copy;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(Error);
                writer.Write(Reason);
                writer.Write(ExtCode);
                writer.Write(ExtCode2);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                int temp = 0;
                reader.Read(temp);
                Error = (LockStepErrorCode)temp;
                reader.Read(Reason);
                reader.Read(ExtCode);
                reader.Read(ExtCode2);
            }
            
        };
        
        enum LockStepState
        {
            kLsFighting,
            kLsStateReconnecting, // Reconnecting to the server
            kLsStateReconnected,
            kLsStateStayInQueue, // In queue
            kLsStateError, // Error occured
        };
        
        enum
        {
            kLsUpdateCallback = 0x01,
            kLsUpdateLoop = 0x02,
            kLsUpdateAll = kLsUpdateCallback | kLsUpdateLoop,
        };
        
        typedef int LockStepManualUpdateOption;
        
        class LockStepInitializeInfo : public GCloud::ApolloBufferBase
        {
        public:
            int MaxBufferSize;
            int StartFrameId;
            int MaxHistorySize;
            LockStepManualUpdateOption ManualUpdateOption;
            
            bool IsTcpCritical;
            
        public:
            LockStepInitializeInfo()
            : MaxBufferSize(1024*100)
            , StartFrameId(0)
            , MaxHistorySize(0)
            , ManualUpdateOption(0)
            , IsTcpCritical(false)
            {
                
            }
            
        public:
            virtual AObject* Clone()const
            {
                LockStepInitializeInfo* copy = new LockStepInitializeInfo();
                *copy = *this;
                return copy;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(MaxBufferSize);
                writer.Write(StartFrameId);
                writer.Write(ManualUpdateOption);
                writer.Write(IsTcpCritical);
                writer.Write(MaxHistorySize);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                reader.Read(MaxBufferSize);
                reader.Read(StartFrameId);
                reader.Read(ManualUpdateOption);
                reader.Read(IsTcpCritical);
                reader.Read(MaxHistorySize);
            }
        };
        
        enum RelayDataFlag
        {
            RelayDataFlagUserStatus = 0x01,
        };
        
        class RelayData : public GCloud::ApolloBufferBase
        {
        public:
            int32_t ObjectId;
            int32_t Flag;
            int16_t DataLen;
            unsigned char* Data;
            // input delay
            int32_t DelayMS;
            uint32_t SequenceId;
            
        public:
            RelayData()
            {
                Init();
            }
            RelayData(unsigned int bufferSize)
            {
                Init();

                if (bufferSize)
                    Data = new unsigned char[bufferSize];
            }
            ~RelayData()
            {
                if (Data)
                {
                    delete[] Data;
                    Data = NULL;
                }
            }

            bool IsUserOnline()
            {
                return Flag & RelayDataFlagUserStatus;
            }
        private:
            void Init()
            {
                ObjectId = 0;
                Flag = 0;
                DataLen = 0;
                Data = NULL;
                DelayMS = 0;
                SequenceId = 0;
            }
        public:
            virtual AObject* Clone()const
            {
                RelayData* copy = new RelayData(DataLen);

                copy->ObjectId = ObjectId;
                copy->Flag = Flag;
                copy->DataLen = DataLen;
                if (DataLen > 0)
                    memcpy(copy->Data, Data, DataLen);

                copy->DelayMS = DelayMS;
                copy->SequenceId = SequenceId;

                return copy;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(ObjectId);
                writer.Write(Flag);
                writer.Write(DelayMS);
                writer.Write(Data, DataLen);
                writer.Write(SequenceId);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                reader.Read(ObjectId);
                reader.Read(Flag);
                reader.Read(DelayMS);

                GCloud::AString temp;
                reader.Read(temp);
                DataLen = temp.length();
                if (DataLen)
                {
                    if (Data)
                        delete[] Data;
                    Data = new unsigned char[DataLen];

                    memcpy(Data, temp.data(), DataLen);
                }
                else
                {
                    if (!Data)
                        Data = new unsigned char[1];
                }
                
                reader.Read(SequenceId);
            }
        };
        
        class FrameInfo : public GCloud::ApolloBufferBase
        {
        public:
            int32_t FrameId;
            // tick of add frame ms
            int32_t RecvTickMS;
            GCloud::AArray DataCollection;
            bool LostEmptyFrame;
            
        public:
            virtual AObject* Clone()const
            {
                FrameInfo* copy = new FrameInfo();
                *copy = *this;
                return copy;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(FrameId);
                writer.Write(RecvTickMS);
                writer.Write(DataCollection);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                reader.Read(FrameId);
                reader.Read(RecvTickMS);
                reader.Read<RelayData>(DataCollection);
            }
        };
        
        class FrameCollection : public GCloud::ApolloBufferBase
        {
        public:
            GCloud::AArray/* FrameInfo* */ Frames;
            
        public:
            virtual AObject* Clone()const
            {
                FrameCollection* copy = new FrameCollection();
                *copy = *this;
                return copy;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(Frames);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                reader.Read<FrameInfo>(Frames);
            }
        };
        
        class LockStepFlowStaticItem : public GCloud::ApolloBufferBase
        {
        public:
            uint64_t SentLen;
            uint64_t RecveivedLen;
            
        public:
            LockStepFlowStaticItem()
            : SentLen(0)
            , RecveivedLen(0)
            {
                
            }
            
        public:
            void Reset()
            {
                SentLen = 0;
                RecveivedLen = 0;
            }
            
        public:
            virtual AObject* Clone()const
            {
                LockStepFlowStaticItem* copy = new LockStepFlowStaticItem();
                *copy = *this;
                return copy;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(SentLen);
                writer.Write(RecveivedLen);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                reader.Read(SentLen);
                reader.Read(RecveivedLen);
            }
        };
        
        class LockStepFlowStaticInfo : public GCloud::ApolloBufferBase
        {
        public:
            LockStepFlowStaticItem Tcp;
            LockStepFlowStaticItem Udp;
            LockStepFlowStaticItem Rudp;
            
        public:
            LockStepFlowStaticInfo()
            {
                
            }
            void Reset()
            {
                Tcp.Reset();
                Udp.Reset();
                Rudp.Reset();
            }
            
            uint64_t GetTotalLen()const
            {
                return GetTotalSentLen() + GetTotalReceivedLen();
            }
            
            uint64_t GetTotalReceivedLen()const
            {
                return Tcp.RecveivedLen + Udp.RecveivedLen + Rudp.RecveivedLen;
            }
            
            uint64_t GetTotalSentLen()const
            {
                return Tcp.SentLen + Udp.SentLen + Rudp.SentLen;
            }
            
        public:
            virtual AObject* Clone()const
            {
                LockStepFlowStaticInfo* copy = new LockStepFlowStaticInfo();
                *copy = *this;
                return copy;
            }
            
            virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
            {
                writer.Write(Tcp);
                writer.Write(Udp);
                writer.Write(Rudp);
            }
            
            virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
            {
                reader.Read(Tcp);
                reader.Read(Udp);
                reader.Read(Rudp);
            }
        };
        
        struct NetworkEmulatorConfig {
            bool enableSendEmulator;
            double udpSendLossRate;
            unsigned int sendMinDelayMS;
            unsigned int sendMaxDelayMS;
            
            bool enableRecvEmulator;
            double udpRecvLossRate;
            unsigned int recvMinDelayMS;
            unsigned int recvMaxDelayMS;
        };

    }
}

#endif  // _GCloud_LockStepPublicDefine_h
