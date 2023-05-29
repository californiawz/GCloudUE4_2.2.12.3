//
//  INetwork.h
//  ABase
//
//  Created by vforkk on 23/5/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef ABase_INetwork_h
#define ABase_INetwork_h

#include "AString.h"
#include "ApolloBuffer.h"

namespace ABase
{
    typedef enum {
        kNetworkNotReachable = 0,
        kNetworkViaWWAN,
        kNetworkViaWifi,
        kNetworkViaOthers,
        kNetworkUnknown
    }ANetworkState;
    
    
    typedef enum{
        NotReachable = 0,
        Reserve1,
        ReachableViaWiFi,
        ReachableViaOthers,
        ReachableViaWWAN_UNKNOWN,
        ReachableViaWWAN_2G,
        ReachableViaWWAN_3G,
        ReachableViaWWAN_4G,
        ReachableViaWWAN_5G
    }ADetailNetworkState;
    
    typedef enum{
        None = 0,
        Unknown,
        StateMobile,
        StateUnicom,
        StateTelecom,
        StateSpacecom
        
    }ACarrier;
    
    
    typedef struct EXPORT_CLASS _tagADetailNetworkInfo : public ABase::ApolloBufferBase{
        ADetailNetworkState state;
        ACarrier carrier;
        AString carrierCode;
        AString ssid;
        AString bssid;
        AString currentAPN;
        
        virtual AObject* Clone()const;
        
        virtual void WriteTo(ABase::CApolloBufferWriter& writer)const
        {
            writer.Write(state);
            writer.Write(carrier);
            writer.Write(carrierCode);
            writer.Write(ssid);
            writer.Write(bssid);
            writer.Write(currentAPN);
        }
        
        virtual void ReadFrom(ABase::CApolloBufferReader& reader)
        {
            int tmp1;
            reader.Read(tmp1);
            state = (ADetailNetworkState)tmp1;
            
            int tmp2;
            reader.Read(tmp2);
            carrier = (ACarrier)tmp2;
            
            reader.Read(carrierCode);
            reader.Read(ssid);
            reader.Read(bssid);
            reader.Read(currentAPN);
        }
        _tagADetailNetworkInfo& operator=(const _tagADetailNetworkInfo& other)
        {
            state = other.state;
            carrier = other.carrier;
            carrierCode = other.carrierCode;
            ssid = other.ssid;
            bssid = other.bssid;
            currentAPN = other.currentAPN;
            return *this;
        }
        
    }ADetailNetworkInfo;

    
    
    typedef void (*ABaseNetworkChangedCallback)(ANetworkState state);
    class EXPORT_CLASS CNetworkObserver
    {
    public:
        CNetworkObserver();
        virtual ~CNetworkObserver();
        virtual void OnNetworkStateChanged(ANetworkState state);
        
    protected:
        bool PopStateFromChangedList(ANetworkState& state);
        int CountOfChangedStates();
    private:
        void* _container;
        void* _mutex;
    };
    
    
    class EXPORT_CLASS INetwork
    {
    protected:
        INetwork(){}
        virtual ~INetwork(){}
        
    public:
        static INetwork& GetInstance();
        
    public:
        virtual ANetworkState GetNetworkState() = 0;

        virtual ADetailNetworkInfo GetDetailNetworkInfo() = 0;

        virtual void SetCallback(ABaseNetworkChangedCallback callback) = 0;
        
    public:
        virtual void AddObserver(CNetworkObserver* observer) = 0;
        virtual void RemoveObserver(CNetworkObserver* observer) = 0;
    };
    
    EXPORT_CLASS bool IsNumericIPv6Notation(const char* host);
    EXPORT_CLASS bool IsNumericIPv4Notation(const char* host);
    EXPORT_CLASS bool ParseURI(const char* url, AString& scheme, AString& host, unsigned short& pPort);
    EXPORT_CLASS bool ConvertIpV4To6(const char* ipv4, AString& ipv6);
}

#endif
