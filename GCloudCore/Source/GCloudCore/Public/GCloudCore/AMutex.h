/*
 * Mutex.h
 *
 *  Created on: 2011-7-28
 *      Author: vforkkcai
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#if !defined(_WIN32) && !defined(_WIN64)
#include <pthread.h>
#else
#include <Windows.h>
#endif
#include <string.h>
#include "ABasePal.h"

namespace ABase
{
    class CCondition;
	class EXPORT_CLASS CMutex
	{
	public:
		CMutex(bool bRecursive = true)
		{

#if !defined(_WIN32) && !defined(_WIN64)
            pthread_mutexattr_t mAttr ;
            memset(&mAttr,0,sizeof(mAttr));
            pthread_mutexattr_init(&mAttr);
            // setup recursive mutex for mutex attribute
#if defined(__APPLE__) || defined(__ORBIS__)
            pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE);
#else
            pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP);
#endif
            // Use the mutex attribute to create the mutex
            if(bRecursive)
            {
                pthread_mutex_init(&m_pMutex, &mAttr);
            }
            else
            {
                pthread_mutex_init(&m_pMutex, NULL);
            }
            
            // Mutex attribute can be destroy after initializing the mutex variable
            pthread_mutexattr_destroy(&mAttr);
            
            //Unlock();
#else
            InitializeCriticalSection(&m_criticalSection);
#endif

		}
		~CMutex()
        {
            //Unlock();
#if !defined(_WIN32) && !defined(_WIN64)
            pthread_mutex_destroy(&m_pMutex);
#else
            DeleteCriticalSection(&m_criticalSection);
#endif
		}

	public:
		void Lock()
		{

#if !defined(_WIN32) && !defined(_WIN64)
            pthread_mutex_lock(&m_pMutex);
#else
            EnterCriticalSection(&m_criticalSection);
#endif
		}
		void Unlock()
		{

#if !defined(_WIN32) && !defined(_WIN64)
            pthread_mutex_unlock(&m_pMutex);
#else
            LeaveCriticalSection(&m_criticalSection);
#endif
		}

    public:

#if !defined(_WIN32) && !defined(_WIN64)
        pthread_mutex_t m_pMutex;
#else
        CRITICAL_SECTION m_criticalSection;
#endif

        friend class CCondition;
	};
}
#endif /* MUTEX_H_ */
