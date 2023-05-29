/*
 * ThreadBase.h
 *
 *  Created on: 2011-7-28
 *      Author: vforkkcai
 */

#ifndef THREADBASE_JNI_H_
#define THREADBASE_JNI_H_

#if !defined(_WIN32) && !defined(_WIN64)
#include <pthread.h>
#else
#include <Windows.h>
#endif

#include "AMutex.h"
#include "AEvent.h"
#include "AAtomic.h"
#include "ATargetBase.h"

#include <vector>
using namespace std;

namespace ABase
{
	enum EThreadState
	{
		TS_Idle = 0,
		TS_Running,
		TS_Pause,
		TS_Exit,
	};
    
	void print();
	
	class EXPORT_CLASS CThreadBase : public CTargetBase
	{
	public:
		CThreadBase();
		virtual ~CThreadBase(){};
        
    public:
        static void Destroy(CThreadBase** pThread, bool asyn = true);

	public:
		// Start the Thread, which can be called once, per object;
		void Start();
		// Stop the Thread
		void Stop();
		void Pause();
		void Resume(bool bSleep = true);

	protected:
#if !defined(_WIN32) && !defined(_WIN64)
        bool Sleep(int milliseconds);
#else
        static bool Sleep(int milliseconds);
#endif 
		EThreadState GetState()
		{
			return m_State;
		}

	protected:
		virtual void OnThreadProc() = 0;
		virtual void OnThreadStart()
		{
		}
		virtual void OnThreadExit()
		{
		}
		virtual void OnThreadPause()
		{
		}
		virtual void OnThreadResume()
		{
		}
		virtual void OnThreadError(int Error)
		{
		}
        
    protected:
        void AddSelector(ASEL_FUNC_1P func, void* param);
        void AddSelector(ASEL_FUNC_VOID func);
        
    private:
        void runSelectors();

	private:
		static void* onThreadProc(void* state);

	private:
#if !defined(_WIN32) && !defined(_WIN64)
        pthread_t m_ThreadId;
#else
        HANDLE m_hThread;
#endif
        
		//
		CAtomic<bool> m_bThreadRun;
		volatile bool m_bThreadExit;
		CEvent m_StartEvent;
		CEvent m_AbortEvent;
		CEvent m_PauseEvent;
		CAtomic<bool> m_bPause;
        
        CAtomic<bool> m_bPauseChanged;

		EThreadState m_State;

		volatile bool m_bDestroy;
        
        CMutex m_mutexSelector;
        vector<CAFunctionSelector> m_vecSelectors;
	};
}

#endif /* THREADBASE_H_ */
