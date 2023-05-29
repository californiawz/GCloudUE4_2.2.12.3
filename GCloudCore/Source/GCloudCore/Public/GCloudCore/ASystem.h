//
//  CSystem.h
//  ABase
//
//  Created by waltli on 14-7-23.
//  Copyright (c) 2014年 TSF4G. All rights reserved.
//

#ifndef ABase_CSystem_h
#define ABase_CSystem_h
#include "ABasePal.h"

namespace ABase
{
    class EXPORT_CLASS CSystem
    {
    public:
        CSystem(){};
        ~CSystem(){};

        static long long GetFreeDiskSpace();

        static const char* GetUdid();
        
        static const char* GetBundleId();

		static const char* GetModel();

		static const char* GetSysVersion();
        //deprecated
        static bool IsDeviceRooted();
        
        static const char* GetAppVersion();
        
        static bool IsFirstLaunch();
        
        static int CheckPermission(int );

        static const char* GetDeviceBrand();
        
#ifdef ANDROID
        static const char* GetCombinedDeviceId();
#endif
    };

}

#endif
