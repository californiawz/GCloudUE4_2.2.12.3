//
//  PlatformObject.h
//  Apollo
//
//  Created by vforkk on 13/5/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __ABase__PlatformObject__
#define __ABase__PlatformObject__

#include "IPlatformObject.h"

namespace ABase {
    class EXPORT_CLASS CPlatformObject : public IPlatformObject
    {
    protected:
        CPlatformObject();
    public:
        virtual ~CPlatformObject();
        
    public:
        void SendUnityMessage(const char* function, const char* param);
        void SendUnityStruct(const char* function, void* param);
        void SendUnityResult(const char* function, int result);
        void SendUnityResult(const char* function, const char* buf, int len);
        void SendUnityBuffer(const char* function, const char* buf, int len);
        void SendUnityBuffer(const char* function, int result, const char* buf, int len);
        void SendUnityBuffer(const char* function, const char* resultBuf, int resultBufLen, const char* buf, int len);
        void SendUnityMethod(int methodId);
        void SendUnityMethod(int methodId, const char* param);
        void SendUnityMethod(int methodId, const char* buf, int len);
        
    public:
        static void ClearEnvironment();
    };
}

#include "PlatformObjectRegister.h"
#include "IPlatformObjectManager.h"

#define GET_APOLLO_OBJECT(C, OBJID) dynamic_cast<C>(IPlatformObjectManager::GetInstance().GetPlatformObject(OBJID))

#define REG_REQ_CLASS(N, CLASS) REG_CLASS_WITH_TYPE(N".REQ", CLASS, REQ)
#define REG_REQ_INSTANCE(N, INST) REG_INSTANCE(N".REQ", INST)
#define CREATE_REQ_INSTANCE(CLASS, N) CREATE_INSTANCE_S(CLASS, N, ".REQ")
#define GET_REQ_OBJECT(C, OBJID) dynamic_cast<C>(IPlatformObjectManager::GetReqInstance().GetPlatformObject(OBJID))

#define REG_RESP_CLASS(N, CLASS) REG_CLASS_WITH_TYPE(N".RESP", CLASS, RESP)
#define REG_RESP_INSTANCE(N, INST) REG_INSTANCE(N".RESP", INST)
#define CREATE_RESP_INSTANCE(CLASS, NAME) CREATE_INSTANCE_S(CLASS, NAME, ".RESP")
#define GET_RESP_OBJECT(C, OBJID) dynamic_cast<C>(IPlatformObjectManager::GetRespInstance().GetPlatformObject(OBJID))

#define REG_SVC_CLASS       REG_REQ_CLASS
#define REG_SVC_INSTANCE    REG_REQ_INSTANCE
#define CreateSvcInstance      CREATE_REQ_INSTANCE
#define GetSvcObject GET_REQ_OBJECT

#define REG_OBSERVER_CLASS      REG_RESP_CLASS
#define REG_OBSERVER_INSTANCE   REG_RESP_INSTANCE
#define CreateObserverInstance     CREATE_RESP_INSTANCE
#define GetObserverObject   GET_RESP_OBJECT


#endif /* defined(__ABase__PlatformObject__) */
