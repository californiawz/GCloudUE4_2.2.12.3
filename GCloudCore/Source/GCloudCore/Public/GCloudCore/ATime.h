#ifndef __XTIME_H__
#define __XTIME_H__

#include "ABasePal.h"


namespace ABase
{
    
    class EXPORT_CLASS CTime
    {
    private:
        CTime();
        ~CTime( );
        
    public:
        
        static int GetYear(void);
        static int GetMonth(void);
        static int GetDay(void);
        
        // Get current timestamp, seconds from 1970.1.1 0:0:0
        static int64_t GetCurTime(void) ;
        
        // Get current tick(us)
        static int64_t GetTimeTick();
        
        // Get the result of time_end(s) minus time_begin(s)
        static int64_t  GetTimeDiff(int64_t time_end, int64_t time_begin) ;
    };
    
//#if defined(_WIN32) || defined(_WIN64)
//    int gettimeofday(struct timeval *a_pstTv, struct timezone *a_pstTz);
//#endif
    
    
    struct TimeCounter
    {
    public:
        TimeCounter()
        : Begin(0)
        , End(0)
        {
            
        }
        
        long long Start()
        {
            Begin = CTime::GetTimeTick();
            return  Begin;
        }
        
        long long Stop()
        {
            long long result = 0;

            if (Begin)
            {
                End = CTime::GetTimeTick();
                long long offset = End - Begin;
                result = offset / 1000;
            }

            return result;
        }
        
        long long Ticks()
        {
            long long result = 0;

            if (Begin)
            {
                int64_t cur = CTime::GetTimeTick();
                result = cur - Begin;
            }

            return result;
        }
        
    public:
        int64_t Begin;
        int64_t End;
    };
    
    
    class EXPORT_CLASS TimeOutInfo
    {
    public:
        unsigned int nExpire;
        long long llStartTime;
        
        bool bEnable;
        
    public:
        TimeOutInfo()
        {
            bEnable = false;
            this->nExpire = 15;
            this->llStartTime = 0;
        }
        
        // seconds
        TimeOutInfo(unsigned int expire)
        {
            bEnable = false;
            this->nExpire = expire;
            this->llStartTime = 0;
        }
        
        // seconds
        void Start(unsigned int nExpire);
        bool Update();
        bool Update(long long currentSecond);
        void Stop();
        void Reset();
        
        bool IsEnabled();
    };
    
}


#endif /*__MTIME_H__*/
