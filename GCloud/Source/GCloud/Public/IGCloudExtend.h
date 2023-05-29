//
//  IGCloudExtend.h
//  GCloud
//
//  Created by morris on 2022/10/11.
//  Copyright © 2022 . All rights reserved.
//

#ifndef IGCloudExtend_h
#define IGCloudExtend_h

#include "GCloudPal.h"

namespace GCloud
{
    enum ModuleType
    {
        kGModuleType_None = 0,
        kGModuleType_Log = 1,
        kGModuleType_Report = 2,
        kGModuleType_Config = 3,
    };
    
    class IModuleBase
    {
    private:
        int moduleType;
        
    protected:
        IModuleBase(int type): moduleType(type) {}
        virtual ~IModuleBase(){}
        
    public:
        int GetModuleType() const { return moduleType; };
    };
    
    // 日志功能 Interface
    class IModuleLog: public IModuleBase
    {
    protected:
        IModuleLog(): IModuleBase(kGModuleType_Log) {}
        virtual ~IModuleLog(){}
        
    public:
        virtual int GetLogLevel() = 0;
        virtual void SetLogLevel(int level) = 0;
        virtual void Log(int level, const char *file, unsigned int line, const char *function, const char* tag, const char* log) = 0;
    };
    
    // 上报功能 Interface
    class IReportEvent
    {
    protected:
        virtual ~IReportEvent(){}
        
    public:
        virtual void Add(const char* key, const char* value, const int valueLen) = 0;
        virtual void Add(int key, const char* value, const int valueLen) = 0;
        virtual void Add(int key, long long value) = 0;

        virtual void Report() = 0;
    };
    
    class IModuleReport: public IModuleBase
    {
    protected:
        IModuleReport(): IModuleBase(kGModuleType_Report) {}
        virtual ~IModuleReport(){}
        
    public:
        virtual IReportEvent* CreateEvent(int srcID, const char* eventName) = 0;
        virtual void DestroyEvent(IReportEvent* pEvent) = 0;
    };
    
    // 配置功能 Interface
    class IModuleConfig: public IModuleBase
    {
    protected:
        IModuleConfig(): IModuleBase(kGModuleType_Config) {}
        virtual ~IModuleConfig(){}
        
    public:
        virtual int GetInt(const char* key, int defaultvalue) = 0;
        virtual long long GetLong(const char* key, long long defaultvalue) = 0;
        virtual double GetDouble(const char* key, double defaultvalue) = 0;
        virtual bool GetBool(const char* key, bool defaultvalue) = 0;
        virtual bool GetString(const char* key, const char* defaultvalue, char* value, int& len) = 0;
    };
    
    // GCloud 扩展接口
    class EXPORT_CLASS IGCloudExtend
    {
    protected:
        IGCloudExtend(){}
        virtual ~IGCloudExtend(){}
        
    public:
        static IGCloudExtend& GetInstance();

    public:
        virtual int RegisterModule(IModuleBase* mod) = 0;
        virtual int UnregisterModule(IModuleBase* mod) = 0;
        virtual IModuleBase* GetModule(int type) = 0;
    };
}

#endif /* IGCloudExtend_h */
