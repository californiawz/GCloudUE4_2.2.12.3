//
//  PlatformObjectManager.h
//  Apollo
//
//  Created by vforkk on 13/5/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __ABase__PlatformObjectManager__
#define __ABase__PlatformObjectManager__
#include <map>
#include "IPlatformObjectManager.h"
#include "IPlatformObject.h"

namespace ABase {
    class CPlatformObject;
    class EXPORT_CLASS CPlatformObjectManager : public IPlatformObjectManager
    {
    private:
        CPlatformObjectManager(){}
        
    public:
        static CPlatformObjectManager& GetInstance();
        
        static CPlatformObjectManager& GetReqInstance();
        
        static CPlatformObjectManager& GetRespInstance();

    public:
        static void DestroyAll();
        
    public:
        CPlatformObject* GetPlatformObject(PlatformObjectId objId);
        void AddObject(PlatformObjectId objId, CPlatformObject* obj);
        void RemoveObject(PlatformObjectId objId);
        void RemoveAll();
        
    private:
        std::map<PlatformObjectId, CPlatformObject*> m_mapObjectCollection;
    };
    
}

#endif /* defined(__ABase__PlatformObjectManager__) */
