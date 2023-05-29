/**
 * @file MSDKMutex.h
 *
 * @author developer
 *
 * @section DESCRIPTION
 *
 * 线程锁工具类声明，非递归锁不可重入，一条线程只可以锁一次
 *
 * @section UPDATE HISTORY
 *
 * Created by jarrettYe @2018.03.20
 *
 * Copyright © company. All rights reserved.
 */
#ifndef MSDKMutex_H
#define MSDKMutex_H

#include "MSDKMacros.h"
#include <stdio.h>
#if MSDK_ENGINE_UE4_SIMULATE_LOGIN
#elif MSDK_PLATFORM_WINDOWS
#include "pthread.h"
#else
#include <pthread.h>
#endif
#include <stdint.h>
#include <sys/types.h>
#include <time.h>


// use this type to return error codes
typedef int32_t status_t;

NS_MSDK_BEGIN

class MSDKMutex {
public:
    enum {
        kMutexPrivate = 0, kMutexShare = 1
    };

    MSDKMutex();

    MSDKMutex(const char *name);

    MSDKMutex(int type, const char *name = NULL);

    ~MSDKMutex();

    status_t Lock();

    void Unlock();

    // lock if possible; returns 0 on success, error otherwise
    status_t TryLock();

    class AutoLock {
    public:
        inline AutoLock(MSDKMutex &mutex) : mLock(mutex) {
            mLock.Lock();
        }

        inline AutoLock(MSDKMutex *mutex) : mLock(*mutex) {
            mLock.Lock();
        }

        inline ~AutoLock() {
            mLock.Unlock();
        }

    private:
        MSDKMutex &mLock;
    };

private:
    friend class Condition;

    // A mutex cannot be copied
    MSDKMutex(const MSDKMutex &);

    MSDKMutex &operator=(const MSDKMutex &);
#if MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else
    pthread_mutex_t mMutex;
#endif
    friend class MSDKCondition;

};

NS_MSDK_END

#endif /* MSDKMutex_h */

