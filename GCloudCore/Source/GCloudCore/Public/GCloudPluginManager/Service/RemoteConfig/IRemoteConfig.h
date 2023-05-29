//
// Created by aaronyan on 2019/8/23.
//

#ifndef ANDROID_AS_IREMOTECONFIG_H
#define ANDROID_AS_IREMOTECONFIG_H

#include <stdint.h>

#if defined(ANDROID) || defined(__ANDROID__)
#define PLUGINMANAGER_API_EXPORT __attribute__ ((visibility ("default")))

#else
#define PLUGINMANAGER_API_EXPORT
#endif

namespace GCloud {
    class IStringIterator
    {
    public:
        virtual const char* Next() = 0;
        virtual bool IsEnd() = 0;
    };
    
    class IRemoteConfig;
    class RemoteConfigObserver
    {
    public:
        virtual void OnRemoteConfigRefreshed(class IRemoteConfig* config, IStringIterator* keyList) = 0;
    };
    
    class IRemoteConfig
    {
    public:
        IRemoteConfig(){};
        virtual ~IRemoteConfig(){};
    public:
        virtual int32_t GetInt(const char* key, int32_t defaultvalue) = 0;
        virtual int64_t GetLong(const char* key, int64_t defaultvalue) = 0;
        virtual double GetDouble(const char* key, double defaultvalue) = 0;
        virtual bool GetBool(const char* key, bool defaultvalue) = 0;
        virtual bool GetString(const char* key, char* value, int& len, const char* defaultvalue) = 0;
        
    public:

        virtual void AddObserver(RemoteConfigObserver* observer) = 0;
        virtual void RemoveObserver(RemoteConfigObserver* observer) = 0;


        //optional, only for sdk
        virtual void SetUserInfo(int channelid, const char* openid) = 0;
        virtual void Fetch() = 0;
        //reserve
        virtual void SetOption(const char* key, int value) = 0;
        virtual void SetOption(const char* key, const char* value) = 0;

    };

    // for Games
    PLUGINMANAGER_API_EXPORT IRemoteConfig* GetGCloudRemoteConfig();
}


#endif //ANDROID_AS_IREMOTECONFIG_H
