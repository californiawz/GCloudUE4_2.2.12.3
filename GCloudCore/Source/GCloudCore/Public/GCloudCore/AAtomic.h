/*
 * Atomic.h
 *
 *  Created on: 2011-8-16
 *      Author: vforkkcai
 */

#ifndef ATOMIC_H_
#define ATOMIC_H_
#include "ACritical.h"
namespace ABase
{
    
    template<typename T>
    class CAtomic
    {
    public:
        CAtomic(T v)
        {
            Set(v);
        }
        T Get()
        {
#if !defined(__ORBIS__)
            CCritical c(&m_Mutex);
#endif
            //LogI("CAtomic: Get: ", m_Value);
            return m_Value;
        }
        void Set(T v)
        {
#if !defined(__ORBIS__)
			CCritical c(&m_Mutex);
#endif
            m_Value = v;
            //LogI("CAtomic: Set: ", m_Value);
        }
    private:
        volatile T m_Value;
        CMutex m_Mutex;
    };
}

#endif /* ATOMIC_H_ */
