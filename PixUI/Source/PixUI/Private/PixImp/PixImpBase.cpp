/**************************************************

**** @file:     PixImpBase.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixImpBase.h"

#include "PixUILog.h"


PixImpBase::PixImpBase(const FString& fstr_name)
    :fstr_name_(fstr_name)
{
    //atuo add to imps
    Imps().Add(this);

    PxLog_Trace("PixImp %s Construct",TCHAR_TO_UTF8(*fstr_name_));
}

PixImpBase::~PixImpBase()
{
    //do not need delete this form imps here,PixImpMgr will clear it
    //Imps().Remove(this);

    PxLog_Trace("PixImp %s Destruct", TCHAR_TO_UTF8(*fstr_name_));
}


void PixImpBase::Startup()
{
    PxLog_Trace("PixImp %s Startup", TCHAR_TO_UTF8(*fstr_name_));
    OnStartup();
}


void PixImpBase::Tick(const float f_DeltaTime)
{
    //PxLog_Trace("PixImp %s Tick", TCHAR_TO_UTF8(*fstr_name_));
    OnTick(f_DeltaTime);
}


void PixImpBase::Clear()
{
	OnClear();
}

void PixImpBase::Shutdown()
{
    PxLog_Trace("PixImp %s Shutdown", TCHAR_TO_UTF8(*fstr_name_));
    OnShutdown();
}


TArray<PixImpBase*>& PixImpBase::Imps()
{
    //imp array
    static TArray<PixImpBase*> ary_PixImps_s;
    return ary_PixImps_s;
};


PixImpBase* PixImpBase::GetImp(const FString& fstr_name)
{
    PixImpBase* p_PixImp = nullptr;
    for (auto imp : Imps())
    {
        if (imp->fstr_name_ == fstr_name)
        {
            p_PixImp = imp;
            break;
        }
    }
    return p_PixImp;
}
