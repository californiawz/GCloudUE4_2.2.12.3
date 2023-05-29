//
//  Copyright © 2022-2023 MSDK team. All rights reserved.
//

#ifndef MSDK_SINGLETON_H
#define MSDK_SINGLETON_H

#include <stdio.h>
#include "MSDKMacros.h"

#if MSDK_PLATFORM_WINDOWS
#include "pthread.h"
#endif

template<class T>
class MSDKSingleton
{
protected:
    MSDKSingleton() {};
private:
    MSDKSingleton(const MSDKSingleton &) {};

    MSDKSingleton &operator=(const MSDKSingleton &) {};
    static T *mInstance;
#if MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else
	static pthread_mutex_t mMutex;
#endif
public:
    static T *GetInstance();
};


template<class T>
T *MSDKSingleton<T>::GetInstance()
{
    if (mInstance == NULL)
    {
#if MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else
        pthread_mutex_lock(&mMutex);
#endif
        if (mInstance == NULL)
        {
            T *tmp = new T();
            mInstance = tmp;
        }
#if MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else
        pthread_mutex_unlock(&mMutex);
#endif
    }
    return mInstance;
}

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else
template<class T>
pthread_mutex_t MSDKSingleton<T>::mMutex = PTHREAD_MUTEX_INITIALIZER;
#endif

template<class T>
T *MSDKSingleton<T>::mInstance = NULL;

#endif /* MSDK_SINGLETON_H */
