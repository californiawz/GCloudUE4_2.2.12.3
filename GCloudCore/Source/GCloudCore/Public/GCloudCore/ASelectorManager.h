//
//  XSelectorManager.h
//  ABase
//
//  Created by vforkk on 10/8/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __ABase__ASelectorManager__
#define __ABase__ASelectorManager__
#include "ATargetBase.h"
#include "AMutex.h"
#include <vector>
using namespace std;

namespace ABase {
    class CSelectorManager : public ISelectorCollection
    {
    public:
        void AddSelector(const CAFunctionSelector& selector);
        
        void Update();
        
		void IgnoreTarget(void * target);
    private:
        bool Pop1stSelector(CAFunctionSelector& selector);
        
    private:
        vector<CAFunctionSelector> m_vecSelectorCollection;
        CMutex m_mutex;
    };
}

#endif /* defined(__ABase__XSelectorManager__) */
