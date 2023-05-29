//
//  IGCloudCore.h
//  ABase
//
//  Created by vforkk on 14/1/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef ABase_IGCloudCore_h
#define ABase_IGCloudCore_h

#include "ABasePal.h"

namespace ABase
{
    class EXPORT_CLASS IGCloudCore
    {
    protected:
        IGCloudCore(){}
        virtual ~IGCloudCore(){}
        
    public:
        static IGCloudCore& GetInstance();

    public:
        virtual int Initialize() = 0;
        virtual void SetLogLevel(int level) = 0;
        virtual const char* GetVersion()= 0;
        virtual void SetRemoteConfigUrl(const char* url)=0;
        virtual void ClearRemoteConfigCache()=0;
    };
}
#endif
