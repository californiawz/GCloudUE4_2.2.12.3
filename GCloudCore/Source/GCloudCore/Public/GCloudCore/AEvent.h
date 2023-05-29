/*
 * Event.h
 *
 *  Created on: 2011-7-28
 *      Author: vforkkcai
 */

#ifndef EVENT_H_
#define EVENT_H_


#ifndef __ORBIS__

#include "ACondition.h"
#include "AMutex.h"

namespace ABase
{
	class EXPORT_CLASS CEvent
	{
	public:
        CEvent();
        
		~CEvent()
        {
#if !defined(_WIN32) && !defined(_WIN64)
			if(m_pCond != 0)
			{
				SAFE_DEL(m_pCond);
            }
#else
            CloseHandle(m_hEvent);
#endif
		}

	public:
		void Wait()
        {
#if !defined(_WIN32) && !defined(_WIN64)
			if(m_pCond != 0)
			{
				m_pCond->Wait();
            }
#else
            WaitForSingleObject(m_hEvent, INFINITE);
#endif
		}

		void TimeWait(a_uint32 tw) //millisecond
        {
#if !defined(_WIN32) && !defined(_WIN64)
			if(m_pCond != 0)
			{
				m_pCond->TimeWait(tw);
            }
#else
            ResetEvent(m_hEvent);
            WaitForSingleObject(m_hEvent, tw);
#endif
        }

		void Set()
        {
#if !defined(_WIN32) && !defined(_WIN64)
			if(m_pCond != 0)
			{
				m_pCond->Set();
			}
#else
            SetEvent(m_hEvent);
#endif
		}

        void Reset()
        {
#if !defined(_WIN32) && !defined(_WIN64)
#else
            ResetEvent(m_hEvent);
#endif
        }

    private:
#if !defined(_WIN32) && !defined(_WIN64)
		CMutex m_Mutex;
		CCondition* m_pCond;
#else
        HANDLE m_hEvent;
#endif
	};
}
#else
#include <pthread.h>
#include <sys/time.h>
namespace ABase
{
	class CEvent
	{
	public:
		CEvent()
			: _set_flag(false)
		{
			pthread_mutex_init(&_mutex, NULL);
			pthread_cond_init(&_cond, NULL);
			_set_flag = false;
		}
		~CEvent()
		{
			pthread_mutex_destroy(&_mutex);
			pthread_cond_destroy(&_cond);

		}
	private:
		pthread_cond_t _cond;
		pthread_mutex_t _mutex;
		bool _set_flag;
	public:
		void Set()
		{
			pthread_mutex_lock(&_mutex);
			_set_flag = true;
			//_set_count += 1;
			pthread_cond_signal(&_cond);
			pthread_mutex_unlock(&_mutex);

		}
		void Reset()
		{
			pthread_mutex_lock(&_mutex);
			_set_flag = false;
			pthread_mutex_unlock(&_mutex);

		}
	public:
		void Wait()
		{
			pthread_mutex_lock(&_mutex);
			while (!_set_flag)
				pthread_cond_wait(&_cond, &_mutex);
			pthread_mutex_unlock(&_mutex);

		}
		void TimeWait(unsigned int  tw) //millisecond
		{

			pthread_mutex_lock(&_mutex);

			struct timeval now;
			gettimeofday(&now, NULL);
			struct timespec ts;

			long inv_sec = tw / 1000;
			long inv_nsec = (tw % 1000) * 1000000;

			long now_sec = now.tv_sec;
			long now_nsec = now.tv_usec * 1000;

			ts.tv_sec = now_sec + inv_sec + (now_nsec + inv_nsec) / 1000000000;
			ts.tv_nsec = (now_nsec + inv_nsec) % 1000000000;

			pthread_cond_timedwait(&_cond, &_mutex, &ts);

			pthread_mutex_unlock(&_mutex);
		}
	};
}
#endif
#endif /* EVENT_H_ */


