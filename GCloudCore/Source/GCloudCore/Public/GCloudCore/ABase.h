//
//  ABase.h
//  ABase
//
//  Created by vforkk on 9/10/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef ABase_ABase_h
#define ABase_ABase_h

#include "ABasePal.h"

// AContainer
#include "AObject.h"
#include "ANumber.h"
#include "AData.h"
#include "AString.h"
#include "AStringBuilder.h"
#include "AArray.h"
#include "ADictionary.h"
#include "AValue.h"

// Platform
#include "IPlatformObject.h"
#include "PlatformObject.h"
#include "PlatformObjectRegister.h"
#include "PlatformObjectWrapper.h"
#include "PlatformObjectManager.h"

// TDR
#include "TdrTypeUtil.h"
#include "TdrBuf.h"
#include "TdrTLV.h"
//#include "TdrXml.h"
#include "TdrParse.h"
#include "TdrIO.h"

// GCloudCore
#include "ATargetBase.h"
#include "ATime.h"
#include "ATimer.h"
#include "ASystem.h"
#include "AThreadBase.h"
#include "ACondition.h"
#include "ACritical.h"
#include "AEvent.h"
#include "AMutex.h"
#include "AFile.h"
#include "IniFile.h"
#include "APath.h"
#include "ALog.h"
#include "ABaseCommon.h"
#include "Bundle.h"

// GCloudCore
#ifdef ANDROID
#include "ABaseJVM.h"
#endif

namespace ABase
{
    class EXPORT_CLASS IBase
    {
    protected:
        IBase();
        virtual ~IBase();
        
    public:
        static IBase& GetInstance();
        static void Release();
    };
    
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Application Functions
    /////////////////////////////////////////////////////////////////////////////////////////////////
    typedef void (*ApplicationQuitCallback)();
    EXPORT_CLASS void AddApplicationQuitCallback(ApplicationQuitCallback callback);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // ABaseInitializer
    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    class EXPORT_CLASS ABaseInitializer
    {
    public:
        ABaseInitializer();
        ABaseInitializer(const char* projectname);
    };
    
   
}



#endif
