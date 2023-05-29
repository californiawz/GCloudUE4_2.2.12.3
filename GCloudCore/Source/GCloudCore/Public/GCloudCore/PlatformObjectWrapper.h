//
//  PlatformObjectWrapper.h
//  Apollo
//
//  Created by vforkk on 30/5/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef Apollo_PlatformObjectWrapper_h
#define Apollo_PlatformObjectWrapper_h
#include "PlatformObject.h"

namespace ABase {
    
    class CPlatformObjectWrapper : public CPlatformObject
    {
    public:
        CPlatformObjectWrapper()
        {
            m_bAutoDelete = true;
            m_pTarget = 0;
        }
        ~CPlatformObjectWrapper()
        {
            //LogInfo("~CPlatformObjectWrapper: %d", m_bAutoDelete);
        }
    public:
        void SetTarget(void* target, bool autoDelete)
        {
            m_pTarget = target;
            m_bAutoDelete = autoDelete;
        }
        
        void* GetTarget()
        {
            return m_pTarget;
        }
        
        
    protected:
        void* m_pTarget;
        bool m_bAutoDelete;
    };
    
}
#endif
