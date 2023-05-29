#ifndef __MTIMER_JNI_H__
#define __MTIMER_JNI_H__


#include "ABasePal.h"
#include <map>
#include "AThreadBase.h"

namespace ABase
{
    class CTimerImp;
    
    typedef void (*TimeoutCallback)(uint32_t timerId, void* param);
    
    class EXPORT_CLASS CTimer
    {
    public:
        CTimer();
        virtual ~CTimer( );
        
    public:
        /**
         ** aInterval : milliseconds
         **/
        uint32_t StartTimer(uint64_t interval, bool repeat, TimeoutCallback, void* param);  //return timerId
        void StopTimer(uint32_t timerId);
        
        
    private:
        uint32_t GetNextTimerId(void);
        CMutex m_Mutex;
        std::map<uint32_t, CTimerImp*>* m_TimerMap; //map to store all timer
        
        static uint32_t _uNextId;
    };
    
}

#endif /*__MTIMER_JNI_H__*/
