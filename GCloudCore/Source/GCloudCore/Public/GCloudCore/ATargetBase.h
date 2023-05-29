//
//  ATargetBase.h
//  ABase
//
//  Created by vforkk on 10/1/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __ATargetBase__
#define __ATargetBase__
#include "ABasePal.h"
//#include "ALog.h"

namespace ABase {
    
    class CAFunctionSelector;
    class ISelectorCollection
    {
    public:
        virtual ~ISelectorCollection(){};
    public:
        virtual void AddSelector(const CAFunctionSelector& selector) = 0;
        virtual void Update() = 0;
        virtual void IgnoreTarget(void * target) = 0;
    };
    
    class EXPORT_CLASS CTargetBase
    {
    public:
        CTargetBase(bool enableManualUpdate = false);
        virtual ~CTargetBase();
        
        
    public:
        void EnableManualUpdate(bool enable);
        bool IsManualUpdateEnable();
        void UpdateByManual();
        
    public:
        ISelectorCollection* GetSelectorCollection()
        {
            return m_pSelctorCollection;
        }
        
    protected:
        ISelectorCollection* m_pSelctorCollection;
    };
    
    typedef void (CTargetBase::*ASEL_FUNC_VOID) ();
    
    typedef void (CTargetBase::*ASEL_FUNC_1P) (void* param);
    typedef void (CTargetBase::*ASEL_FUNC_2P) (void* param1, void* param2);
    typedef void (CTargetBase::*ASEL_FUNC_3P) (void* param1, void* param2, void* param3);
    
#define xfunc_void_selector(_SELECTOR) (ABase::ASEL_FUNC_VOID)(&_SELECTOR)
#define xfunc_1P_selector(_SELECTOR) (ABase::ASEL_FUNC_1P)(&_SELECTOR)
#define xfunc_2P_selector(_SELECTOR) (ABase::ASEL_FUNC_2P)(&_SELECTOR)
#define xfunc_3P_selector(_SELECTOR) (ABase::ASEL_FUNC_3P)(&_SELECTOR)
    
    
    
    typedef void (*SSEL_FUNC_VOID) ();
    typedef void (*SSEL_FUNC_1P) (void* param);
    typedef void (*SSEL_FUNC_2P) (void* param1, void* param2);
    typedef void (*SSEL_FUNC_3P) (void* param1, void* param2, void* param3);
    
#define xsfunc_void_selector(_SELECTOR) (SSEL_FUNC_VOID)(&_SELECTOR)
#define xsfunc_1P_selector(_SELECTOR) (SSEL_FUNC_1P)(&_SELECTOR)
#define xsfunc_2P_selector(_SELECTOR) (SSEL_FUNC_2P)(&_SELECTOR)
#define xsfunc_3P_selector(_SELECTOR) (SSEL_FUNC_3P)(&_SELECTOR)
    
    class CAFunctionSelector
    {
    public:
        CTargetBase* pTarget;
        ASEL_FUNC_VOID pVoid;
        ASEL_FUNC_1P p1P;
        ASEL_FUNC_2P p2P;
        ASEL_FUNC_3P p3P;
        
    public:
        SSEL_FUNC_VOID psVoid;
        SSEL_FUNC_1P ps1P;
        SSEL_FUNC_2P ps2P;
        SSEL_FUNC_3P ps3P;
        
        void* param1;
        void* param2;
        void* param3;
        
    public:
        CAFunctionSelector()
        : pTarget(0x00)
        , pVoid(0x00)
        , p1P(0x00)
        , p2P(0)
        , p3P(0)
        , psVoid(0x00)
        , ps1P(0x00)
        , ps2P(0)
        , ps3P(0)
        , param1(0)
        , param2(0)
        , param3(0)
        {
            
        }
        
    public:
        
        void Set(CTargetBase* target, ASEL_FUNC_VOID pFunc)
        {
            this->pTarget = (CTargetBase*)target;
            this->pVoid = pFunc;
        }
        
        void Set(CTargetBase* target, ASEL_FUNC_1P pFunc, void* p1)
        {
            this->pTarget = (CTargetBase*)target;
            this->p1P = pFunc;
            this->param1 = p1;
        }
        
        void Set(CTargetBase* target, ASEL_FUNC_2P pFunc, void* p1, void* p2)
        {
            this->pTarget = (CTargetBase*)target;
            this->p2P = pFunc;
            this->param1 = p1;
            this->param2 = p2;
        }
        
        void Set(CTargetBase* target, ASEL_FUNC_3P pFunc, void* p1, void* p2, void* p3)
        {
            this->pTarget = (CTargetBase*)target;
            this->p3P = pFunc;
            this->param1 = p1;
            this->param2 = p2;
            this->param3 = p3;
        }
        
        
        void Set(SSEL_FUNC_VOID pFunc)
        {
            this->psVoid = pFunc;
        }
        
        void Set(SSEL_FUNC_1P pFunc, void* p1)
        {
            this->ps1P = pFunc;
            this->param1 = p1;
        }
        
        void Set(SSEL_FUNC_2P pFunc, void* p1, void* p2)
        {
            this->ps2P = pFunc;
            this->param1 = p1;
            this->param2 = p2;
        }
        
        void Set(SSEL_FUNC_3P pFunc, void* p1, void* p2, void* p3)
        {
            this->ps3P = pFunc;
            this->param1 = p1;
            this->param2 = p2;
            this->param3 = p3;
        }
        
        void Perform()
        {
            //XLogInfo("Perform, target:%d, pvoid:%d, p1p:%d", pTarget, pVoid, p1P);
            if (pTarget != 0x00) {
                
                if (pVoid) {
                    (pTarget->*pVoid)();
                    return;
                }
                else if(p1P)
                {
                    (pTarget->*p1P)(param1);
                    return;
                }
                else if(p2P)
                {
                    (pTarget->*p2P)(param1, param2);
                    return;
                }
                else if(p3P)
                {
                    (pTarget->*p3P)(param1, param2, param3);
                    return;
                }
            }
            
            
            if (psVoid) {
                (*psVoid)();
            }
            else if(ps1P)
            {
                (*ps1P)(param1);
            }
            else if(ps2P)
            {
                (*ps2P)(param1, param2);
            }
            else if(ps3P)
            {
                (*ps3P)(param1, param2, param3);
            }
        }
        
    };
    
#ifdef __cplusplus
    extern "C"
    {
#endif
        
        EXPORT_API bool InitABaseObjectEnvironment();
        EXPORT_API void ReleaseABaseObjectEnvironment();
        
		EXPORT_API void ABase_EnableManualUpdate();
		EXPORT_API void ABase_UpdateUIThread();
		EXPORT_API void ABase_IgnoreUIThread(void *);
		EXPORT_API void ABase_EndUIThread ();
		EXPORT_API bool ABase_IsManualUpdate();
        
        
		EXPORT_API void ABase_RemoveTargetFromMainThread(void * target);
        
#ifdef __cplusplus
    }
#endif
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // OnMainThread
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    EXPORT_CLASS void PerformSelectorOnMainThread(CAFunctionSelector* pSelector);
    
    inline void PerformSelectorOnMainThread(CTargetBase* pTarget, ASEL_FUNC_VOID pFunc)
    {
        CAFunctionSelector selector;
        selector.Set(pTarget, pFunc);
        
        PerformSelectorOnMainThread(&selector);
    }
#define SEL_VOID_ON_MAIN_THREAD(Target, FUNC) PerformSelectorOnMainThread(Target, xfunc_void_selector(FUNC))
    
    inline void PerformSelectorOnMainThread(CTargetBase* pTarget, ASEL_FUNC_1P pFunc, void* param)
    {
        CAFunctionSelector selector;
        selector.Set(pTarget, pFunc, (void*)param);
        
        PerformSelectorOnMainThread(&selector);
    }
#define SEL_1P_ON_MAIN_THREAD(Target, FUNC, PARAM) PerformSelectorOnMainThread(Target, xfunc_1P_selector(FUNC), (void*)PARAM)
    
    inline void PerformSelectorOnMainThread(CTargetBase* pTarget, ASEL_FUNC_2P pFunc, void* p1, void* p2)
    {
        CAFunctionSelector selector;
        selector.Set(pTarget, pFunc, (void*)p1, (void*)p2);
        
        PerformSelectorOnMainThread(&selector);
    }
#define SEL_2P_ON_MAIN_THREAD(Target, FUNC, P1, P2) PerformSelectorOnMainThread(Target, xfunc_2P_selector(FUNC), (void*)P1, (void*)P2)
    
    inline void PerformSelectorOnMainThread(CTargetBase* pTarget, ASEL_FUNC_3P pFunc, void* p1, void* p2, void* p3)
    {
        CAFunctionSelector selector;
        selector.Set(pTarget, pFunc, (void*)p1, (void*)p2, (void*)p3);
        
        PerformSelectorOnMainThread(&selector);
    }
#define SEL_3P_ON_MAIN_THREAD(Target, FUNC, P1, P2, P3) PerformSelectorOnMainThread(Target, xfunc_3P_selector(FUNC), (void*)P1, (void*)P2, (void*)P3)
    
    inline void PerformSelectorOnMainThread(SSEL_FUNC_VOID pFunc)
    {
        CAFunctionSelector selector;
        selector.Set(pFunc);
        
        PerformSelectorOnMainThread(&selector);
    }
#define STATIC_SEL_VOID_ON_MAIN_THREAD(FUNC) PerformSelectorOnMainThread(xsfunc_void_selector(FUNC))
    
    inline void PerformSelectorOnMainThread(SSEL_FUNC_1P pFunc, void* param)
    {
        CAFunctionSelector selector;
        selector.Set(pFunc, (void*)param);
        
        PerformSelectorOnMainThread(&selector);
    }
#define STATIC_SEL_1P_ON_MAIN_THREAD(FUNC, PARAM) PerformSelectorOnMainThread(xsfunc_1P_selector(FUNC), (void*)PARAM)
    
    inline void PerformSelectorOnMainThread(SSEL_FUNC_2P pFunc, void* p1, void* p2)
    {
        CAFunctionSelector selector;
        selector.Set(pFunc, (void*)p1, (void*)p2);
        
        PerformSelectorOnMainThread(&selector);
    }
#define STATIC_SEL_2P_ON_MAIN_THREAD(FUNC, P1, P2) PerformSelectorOnMainThread(xsfunc_2P_selector(FUNC), (void*)P1, (void*)P2)
    
    inline void PerformSelectorOnMainThread(SSEL_FUNC_3P pFunc, void* p1, void* p2, void* p3)
    {
        CAFunctionSelector selector;
        selector.Set(pFunc, (void*)p1, (void*)p2, (void*)p3);
        
        PerformSelectorOnMainThread(&selector);
    }
#define STATIC_SEL_3P_ON_MAIN_THREAD(FUNC, P1, P2, P3) PerformSelectorOnMainThread(xsfunc_3P_selector(FUNC), (void*)P1, (void*)P2, (void*)P3)
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // OnUIThread
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    EXPORT_CLASS void PerformSelectorOnUIThread(CAFunctionSelector* pSelector);
    
    inline void PerformSelectorOnUIThread(CTargetBase* pTarget, ASEL_FUNC_VOID pFunc)
    {
        CAFunctionSelector selector;
        selector.Set(pTarget, pFunc);
        
        PerformSelectorOnUIThread(&selector);
    }
#define SEL_VOID_ON_UI_THREAD(Target, FUNC) PerformSelectorOnUIThread(Target, xfunc_void_selector(FUNC))
    
    inline void PerformSelectorOnUIThread(CTargetBase* pTarget, ASEL_FUNC_1P pFunc, void* param)
    {
        CAFunctionSelector selector;
        selector.Set(pTarget, pFunc, (void*)param);
        
        PerformSelectorOnUIThread(&selector);
    }
#define SEL_1P_ON_UI_THREAD(Target, FUNC, PARAM) PerformSelectorOnUIThread(Target, xfunc_1P_selector(FUNC), (void*)PARAM)
    
    inline void PerformSelectorOnUIThread(CTargetBase* pTarget, ASEL_FUNC_2P pFunc, void* p1, void* p2)
    {
        CAFunctionSelector selector;
        selector.Set(pTarget, pFunc, (void*)p1, (void*)p2);
        
        PerformSelectorOnUIThread(&selector);
    }
#define SEL_2P_ON_UI_THREAD(Target, FUNC, P1, P2) PerformSelectorOnUIThread(Target, xfunc_2P_selector(FUNC), (void*)P1, (void*)P2)
    
    inline void PerformSelectorOnUIThread(CTargetBase* pTarget, ASEL_FUNC_3P pFunc, void* p1, void* p2, void* p3)
    {
        CAFunctionSelector selector;
        selector.Set(pTarget, pFunc, (void*)p1, (void*)p2, (void*)p3);
        
        PerformSelectorOnUIThread(&selector);
    }
#define SEL_3P_ON_UI_THREAD(Target, FUNC, P1, P2, P3) PerformSelectorOnUIThread(Target, xfunc_3P_selector(FUNC), (void*)P1, (void*)P2, (void*)P3)
    
    
    
    inline void PerformSelectorOnUIThread(SSEL_FUNC_VOID pFunc)
    {
        CAFunctionSelector selector;
        selector.Set(pFunc);
        
        PerformSelectorOnUIThread(&selector);
    }
#define STATIC_SEL_VOID_ON_UI_THREAD(FUNC) PerformSelectorOnUIThread(xsfunc_void_selector(FUNC))
    
    inline void PerformSelectorOnUIThread(SSEL_FUNC_1P pFunc, void* param)
    {
        CAFunctionSelector selector;
        selector.Set(pFunc, (void*)param);
        
        PerformSelectorOnUIThread(&selector);
    }
#define STATIC_SEL_1P_ON_UI_THREAD(FUNC, PARAM) PerformSelectorOnUIThread(xsfunc_1P_selector(FUNC), (void*)PARAM)
    
    inline void PerformSelectorOnUIThread(SSEL_FUNC_2P pFunc, void* p1, void* p2)
    {
        CAFunctionSelector selector;
        selector.Set(pFunc, (void*)p1, (void*)p2);
        
        PerformSelectorOnUIThread(&selector);
    }
#define STATIC_SEL_2P_ON_UI_THREAD(FUNC, P1, P2) PerformSelectorOnUIThread(xsfunc_2P_selector(FUNC), (void*)P1, (void*)P2)
    
    inline void PerformSelectorOnUIThread(SSEL_FUNC_3P pFunc, void* p1, void* p2, void* p3)
    {
        CAFunctionSelector selector;
        selector.Set(pFunc, (void*)p1, (void*)p2, (void*)p3);
        
        PerformSelectorOnUIThread(&selector);
    }
#define STATIC_SEL_3P_ON_UI_THREAD(FUNC, P1, P2, P3) PerformSelectorOnUIThread(xsfunc_3P_selector(FUNC), (void*)P1, (void*)P2, (void*)P3)
    
}
#endif /* defined(__APOLLO__TObject__) */
