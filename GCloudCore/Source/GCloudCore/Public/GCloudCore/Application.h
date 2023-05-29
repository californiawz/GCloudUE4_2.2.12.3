//
//  Application.h
//  ABase
//
//  Created by vforkk on 8/5/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __ABase__Application__
#define __ABase__Application__
#include <vector>
#include "AMutex.h"

namespace ABase
{
    
    class EXPORT_CLASS IApplicationObserver
    {
    public:
        IApplicationObserver();
        virtual ~IApplicationObserver();
    public:
        virtual void OnCreate() = 0;
        virtual void OnStart() = 0;
        virtual void OnPause() = 0;
        virtual void OnResume() = 0;
        virtual void OnStop() = 0;
        virtual void OnDestroy() = 0;
    };
    
    class EXPORT_CLASS CApplication
    {
    private:
        CApplication();
        ~CApplication();
        
    public:
        static CApplication& GetInstance();
        static void ReleaseInstance();
      
        
    public:
        void AddObserver(IApplicationObserver* observer);
        void RemoveObserver(IApplicationObserver* observer);
        
        void OnCreate(); // call by platform
        void OnStart();
        void OnPause();
        void OnResume();
        void OnStop();
        void OnDestroy();
    private:
        CMutex _mutext;
		//Observer
        std::vector<IApplicationObserver*> m_vecObservers;
    };

}

#endif /* defined(__ABase__ANetwork__) */
