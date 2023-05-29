//
//  PlatformObjectManager.h
//  Apollo
//
//  Created by vforkk on 13/5/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __Apollo__IPlatformObjectManager__
#define __Apollo__IPlatformObjectManager__
#include "IPlatformObject.h"

namespace ABase {
    class CPlatformObject;
    class EXPORT_CLASS IPlatformObjectManager
    {
    protected:
        IPlatformObjectManager(){}
        virtual ~IPlatformObjectManager(){}
        
    public:
        static IPlatformObjectManager& GetInstance();
        
        static IPlatformObjectManager& GetReqInstance();
        
        static IPlatformObjectManager& GetRespInstance();
        
    public:
        static void DestroyAll();
        
    public:
        virtual CPlatformObject* GetPlatformObject(PlatformObjectId objId) = 0;
        virtual void AddObject(PlatformObjectId objId, CPlatformObject* obj) = 0;
        virtual void RemoveObject(PlatformObjectId objId) = 0;
        virtual void RemoveAll() = 0;
    };
    
}

#endif /* defined(__Apollo__PlatformObjectManager__) */
