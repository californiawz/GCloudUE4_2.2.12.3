//
//  IGCloud.h
//  GCloud
//
//  Created by vforkk on 14/1/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef GCloud_IGCloud_h
#define GCloud_IGCloud_h

#include "GCloudPublicDefine.h"
#include <string>

namespace GCloud {
	
    class EXPORT_CLASS IGCloud
    {
    protected:
        IGCloud(){}
        virtual ~IGCloud(){}
        
    public:
        static IGCloud& GetInstance();
        static void ReleaseInstance();
        ///////////////////////////////////////////////////////////////////////////////
        // Required
        ///////////////////////////////////////////////////////////////////////////////
    public:
        virtual EErrorCode Initialize(const InitializeInfo& initInfo) = 0;
        virtual void SetUserInfo(const UserInfo& userInfo) = 0;
        virtual bool GetInstanceId(char* buf, int bufSize) = 0;

    public:
        virtual void SetLogger(LogPriority priority) = 0;
        virtual const char* GetVersion()= 0;
    };
    
    
    void DisableOneSDK();
}

#endif
