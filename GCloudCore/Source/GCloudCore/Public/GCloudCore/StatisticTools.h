
#ifndef _ABase_StatisticTools_H
#define _ABase_StatisticTools_H
#include "ABasePal.h"

namespace ABase {
    
    //
    // D(X^2) = E(X^2) - (EX)^2
    //
    class EXPORT_CLASS Variance{
    public:
        Variance();
        void Add(int64_t x);
        uint32_t   GetMean();
        uint32_t   GetVariance();
        
    public:
        void Clear()
        {
            _count = 0;
            _sum = 0;
            _sum_squre = 0;
        }
    protected:
        uint32_t    _count;
        uint64_t  _sum;
        uint64_t  _sum_squre;
    };
    
}

#endif
