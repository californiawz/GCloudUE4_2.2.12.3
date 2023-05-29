//
//  IQueueService.h
//  GCloudQueue
//
//  Created by teddyzhang on 2019/8/14.
//  Copyright © 2019 GCloud. All rights reserved.
//

#ifndef IQueueService_h
#define IQueueService_h

#include "QueuePublicDefine.h"
#include "IConnector.h"

namespace GCloud
{

    class EXPORT_CLASS QueueObserver
    {
    public:
        virtual void OnQueueStatusProc(const Result& result, const QueueStatusInfo& info) = 0;
        virtual void OnQueueFinishedProc(const Result& result, const QueueFinishedInfo& info) = 0;
    };


    class EXPORT_CLASS IQueueService
    {
    protected:
        IQueueService() {}
        virtual ~IQueueService() {}

    public:
        static IQueueService& GetInstance();
        static void ReleaseInstance();

    public:
        virtual void AddObserver(const QueueObserver* observer) = 0;
        virtual void RemoveObserver(const QueueObserver* observer) = 0;

    public:
        virtual bool Initialize(const QueueInitInfo& initInfo) = 0;
        virtual bool JoinQueue(const char* zoneId,const char* queflag="") = 0;
        virtual bool ExitQueue() = 0;
        virtual void UpdateByManual() = 0;
        virtual bool IsServiceEnabled() = 0;
    };

}

#endif /* IQueueService_h */
