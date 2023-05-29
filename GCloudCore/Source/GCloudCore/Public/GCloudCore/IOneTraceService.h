
//
//  IOneTraceService.h
//  GCloudCore
//
//  Created by cedar on 2020/2/26.
//  Copyright © 2020 GCloud. All rights reserved.
//
#include "ABasePal.h"
#if defined (ANDROID) || defined (_IOS)
#ifndef IOneTraceService_h
#define IOneTraceService_h
namespace GCloud {
    class EXPORT_CLASS IOneTraceService
    {
    protected:
        virtual ~IOneTraceService(){}
        
    public:
        static IOneTraceService* GetInstance();
        static void ReleaseInstance();
        
    public:
        virtual const char* GetTraceId()=0;
        virtual const char* CreateContext(const char* parentContext, const char* privateType)=0;
        virtual void SpanStart(const char* context, const char* name, const char* caller, const char* callee)=0;
        virtual void SpanFlush(const char* context, const char* key, const char* value)=0;
        virtual void SpanFinish(const char* context, const char* errCode, const char* errMsg)=0;
    };
}
#endif /* IOneTraceService_h */
#endif
 
