//
//  PlatformObjectRegister.h
//  Apollo
//
//  Created by vforkk on 14/5/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __ABase__PlatformObjectRegister__
#define __ABase__PlatformObjectRegister__
#include "IPlatformObject.h"
#include <map>
#include <string>


class IPlatformObjectFactory
{
public:
    virtual ABase::IPlatformObject* NewInstance() = 0;
};

template <typename CLASS>
class CPlatformObjectFactory : public IPlatformObjectFactory
{
    
public:
    virtual ABase::IPlatformObject* NewInstance()
    {
        return new CLASS();
    }
};

class EXPORT_CLASS CPlatformObjectClass
{
    
public:
    
    static CPlatformObjectClass& GetInstance();
    static void ReleaseInstance();
    
    void RegisterClassG(const char* className, IPlatformObjectFactory* factory);
    
    void RegisterInstance(const char* className, ABase::IPlatformObject* obj);
    
    ABase::IPlatformObject* Instance(const char* className);
    
//    void RegisterClass(const std::string& className, IPlatformObjectFactory* factory)
//    {
//        return RegisterClass(className.c_str(), factory);
//    }
//
//    void RegisterInstance(const std::string& className, ABase::IPlatformObject* obj)
//    {
//        return RegisterInstance(className.c_str(), obj);
//    }
//
//    ABase::IPlatformObject* Instance(const std::string& className)
//    {
//        return InstanceC(className.c_str());
//    }
    
    ABase::IPlatformObject* Instance(const char* className, const char* subfix)
    {
        if(!className)
        {
            return 0;
        }
        
        std::string name = className;
        if (subfix) {
            name += subfix;
        }
        return Instance(name.c_str());
    }
    
};


template <typename CLASS = void>
class CPlatformObjectRegister
{
public:
    CPlatformObjectRegister(const char* className)
    {
        //LOG_I("CPlatformObjectRegister: %s", className.c_str());
        CPlatformObjectClass::GetInstance().RegisterClassG(className, new CPlatformObjectFactory<CLASS>());
    }
    
    CPlatformObjectRegister(const char* className, ABase::IPlatformObject* obj)
    {
        CPlatformObjectClass::GetInstance().RegisterInstance(className, obj);
    }
};

#define REG_CLASS_WITH_TYPE(NAME, CLASS, TYPE) static CPlatformObjectRegister<CLASS> __##CLASS##TYPE##_Register(NAME);
#define REG_CLASS(NAME, CLASS) REG_CLASS_WITH_TYPE(NAME, CLASS, A)
#define REG_INSTANCE(NAME, INST) static CPlatformObjectRegister<> __s_Instance_Register(NAME, INST);
#define CREATE_INSTANCE(CLASS, NAME) dynamic_cast<CLASS>(CPlatformObjectClass::GetInstance().Instance((NAME)))
#define CREATE_INSTANCE_S(CLASS, NAME, S) dynamic_cast<CLASS>(CPlatformObjectClass::GetInstance().Instance((NAME), (S)))

#endif /* defined(__ABase__PlatformObjectRegister__) */
