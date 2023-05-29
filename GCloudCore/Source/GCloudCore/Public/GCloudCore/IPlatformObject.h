//
//  IPlatformObject.h
//  Apollo
//
//  Created by vforkk on 16/5/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef Apollo_IPlatformObject_h
#define Apollo_IPlatformObject_h
#include <string>
#include <string.h>
#include "ABasePal.h"

namespace ABase {
    typedef unsigned long long PlatformObjectId;
    
    class IPlatformObject
    {
    protected:
        IPlatformObject()
        {
            m_pszObjectName=0;
            nObjectId = 0;

        }
    public:
        virtual ~IPlatformObject()
        {
            if (m_pszObjectName) {
                delete []m_pszObjectName;
                m_pszObjectName = NULL;
            }
        }
        
    public:
        PlatformObjectId nObjectId;
        
    public:
        void SetObjectName(const char* name);
        const char* GetObjectName()
        {
            return m_pszObjectName;
        }
    private:
        char* m_pszObjectName;
    };
}

#endif
