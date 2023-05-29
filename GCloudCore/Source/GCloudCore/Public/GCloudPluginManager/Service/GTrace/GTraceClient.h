//
// GTraceClient.h
// GCloudSDK
//
// Created by cedar on 2019-09-16.
// Copyright (c) 2019 GCloud. All rights reserved.
//

#ifndef GTraceClient_h
#define GTraceClient_h

#if !defined(_WIN32) && !defined(_WIN64) && !defined(_MAC)
#include "GCloudPluginManager/Service/GTrace/ITraceService.h"


#define GTRACE_GET_TRACEID(CLASS)\
sg_get_traceid(CLASS::GetInstance());

#define GTRACE_CREATE_CONTEXT(CLASS, PARENTCONTEXT, PUBLICTYPE, PRIVATETYPE)\
sg_create_context(CLASS::GetInstance(), PARENTCONTEXT, PUBLICTYPE, PRIVATETYPE);

#define GTRACE_SPAN_START(CLASS, CONTEXT, PUBLICTYPE, NAME, CALLER, CALLEE)\
sg_span_start(CLASS::GetInstance(), CONTEXT, PUBLICTYPE, NAME, CALLER, CALLEE);

#define GTRACE_SPAN_FLUSH(CLASS, CONTEXT, PUBLICTYPE, KEY, VALUE)\
sg_span_flush(CLASS::GetInstance(), CONTEXT, PUBLICTYPE, KEY, VALUE);

#define GTRACE_SPAN_FINISH(CLASS, CONTEXT, PUBLICTYPE, ERRCODE, ERRMSG)\
sg_span_finish(CLASS::GetInstance(), CONTEXT, PUBLICTYPE, ERRCODE, ERRMSG);


#endif
#endif //GTraceClient_h
