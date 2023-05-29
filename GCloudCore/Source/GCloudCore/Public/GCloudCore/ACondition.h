/*
 * Condition.h
 *
 *  Created on: 2011-7-28
 *      Author: vforkkcai
 */

#ifndef CONDITION_H_
#define CONDITION_H_


#if !defined(_WIN32) && !defined(_WIN64)
#include <pthread.h>
#include <sys/time.h>
#else
#include <Windows.h>
#endif

#include "ABasePal.h"
#include "AMutex.h"

namespace ABase
{
	class EXPORT_CLASS CCondition
	{
	public:
		CCondition(CMutex* pMutex, bool autoLock = true)
		{
            m_autoLock = autoLock;
            m_pMutex = pMutex;
#if !defined(_WIN32) && !defined(_WIN64)
            pthread_cond_init(&m_pCond, 0);
#else
            InitializeConditionVariable(&m_conditionVariable);
#endif
		}

		~CCondition()
		{
#if !defined(_WIN32) && !defined(_WIN64)
            pthread_cond_destroy(&m_pCond);
#endif
		}

	public:
		void Wait()
		{
			if (m_pMutex)
			{

                if(m_autoLock)
                {
                    m_pMutex->Lock();
                }
                #if !defined(_WIN32) && !defined(_WIN64)
                pthread_cond_wait(&m_pCond, &(m_pMutex->m_pMutex));
                #else
				SleepConditionVariableCS(&m_conditionVariable, &(m_pMutex->m_criticalSection), INFINITE);
                #endif
				if (m_autoLock)
                {
                    m_pMutex->Unlock();
                }



			}
		}

	    void TimeWait(a_uint32 milliseconds) //tw is millSecond
		{
			if (m_pMutex)
			{
                m_pMutex->Lock();
#if !defined(_WIN32) && !defined(_WIN64)
				long inv_sec  = milliseconds / 1000;
                long inv_nsec = (milliseconds % 1000) * 1000000;
				
				struct timeval now;
                gettimeofday(&now, NULL);
				long now_sec  = now.tv_sec;
                long now_nsec = now.tv_usec * 1000;
				
                struct timespec ts;
                ts.tv_sec  = now_sec + inv_sec + (now_nsec+inv_nsec)/1000000000;
                ts.tv_nsec = (now_nsec + inv_nsec) % 1000000000;
				
                pthread_cond_timedwait(&m_pCond, &(m_pMutex->m_pMutex), &ts);
#else
				SleepConditionVariableCS(&m_conditionVariable, &(m_pMutex->m_criticalSection), milliseconds);
#endif
                m_pMutex->Unlock();
			}
		}

		void Set()
		{
			if (m_pMutex)
			{
				m_pMutex->Lock();
#if !defined(_WIN32) && !defined(_WIN64)
				pthread_cond_broadcast(&m_pCond);
#else
				WakeAllConditionVariable(&m_conditionVariable);
#endif
				m_pMutex->Unlock();
			}

		}
        
        void WakeUp()
        {
			if (m_pMutex)
			{
				m_pMutex->Lock();
#if !defined(_WIN32) && !defined(_WIN64)
				pthread_cond_signal(&m_pCond);
#else
				WakeConditionVariable(&m_conditionVariable);
#endif
				m_pMutex->Unlock();
			}
        }

	private:

#if !defined(_WIN32) && !defined(_WIN64)
        pthread_cond_t m_pCond;
#else
        CONDITION_VARIABLE m_conditionVariable;
#endif
        CMutex* m_pMutex;
        bool m_autoLock;
	};
}


#endif /* CONDITION_H_ */
