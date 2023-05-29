//
//  Configure.hpp
//  Configure
//
//  Created by vforkk on 11/28/16.
//  Copyright © 2016 vforkk. All rights reserved.
//

#ifndef Configure_hpp
#define Configure_hpp

#include "ABasePal.h"
#include "AValue.h"

#include "GCloudPluginManager/Service/RemoteConfig/IRemoteConfig.h"


namespace GCloud {

    class ConfigureObserver;
    class EXPORT_CLASS Configure                                                                                                                                                                            
    {
    public:
        static Configure* GetInstance();
        
    public:
        virtual void Start() = 0;

    public:
        virtual int32_t GetInt(const char* module, const char* key, int32_t defaultvalue) = 0;
        virtual int64_t GetLong(const char* module, const char* key, int64_t defaultvalue) = 0;
        virtual double GetDouble(const char* module, const char* key, double defaultvalue) = 0;
        virtual bool GetBool(const char* module, const char* key, bool defaultvalue) = 0;
        virtual ABase::AString GetString(const char* module, const char* key, const char* defaultvalue) = 0;

    public:
        virtual void AddObserver(const char* module, ConfigureObserver* observer) = 0;
        virtual void RemoveObserver(const char* module) = 0;

    public:
        virtual void StartOnce() = 0;
        
        virtual void SetUrl(const char* url) = 0;
        virtual void Clear() = 0;
    };
    
    class ConfigureObserver
    {
    public:
        virtual void OnConfigureRefreshed(IStringIterator* keyList) = 0;   //{"module1":{"name1":"value1","name2":["value2","value3"]}}
    };
}

#endif /* Configure_hpp */
