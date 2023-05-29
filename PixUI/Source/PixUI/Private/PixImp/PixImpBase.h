/**************************************************

**** @file:     PixImpBase.h

**** @brief:    pixui implementation item base

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#include "CoreMinimal.h"

//GetImp macro,
#define DF_GET_PX_IMP(_name) (_name*)PixImpBase::GetImp(TEXT(#_name))

//register macro,declare Register and Get member Function
//PixImpBase Subclasses must use this macro in the header file
#define DF_REG_PX_IMP(_name)  public:   \
static _name* Get() {                   \
    return DF_GET_PX_IMP(_name);        \
}                                       \
static _name* Register(){               \
    if (Get())                          \
        return Get();                   \
    return new _name();                 \
}


class PixImpBase
{
public:
    PixImpBase(const FString& fstr_name);

    virtual ~PixImpBase();

public:
    //called when pixui module start up
    void Startup();

    //called by pixui tick
    void Tick(const float f_DeltaTime);

	void Clear();
    //called when pixui module shutdown
    void Shutdown();

protected:
    //for override
    virtual void OnStartup() = 0;
    virtual void OnTick(const float f_DeltaTime) = 0;
	virtual void OnClear() = 0;
    virtual void OnShutdown() = 0;

private:
    //imp name
    FString fstr_name_;

public:
    //get imp array
    static TArray<PixImpBase*>& Imps();

    //get imp
    static PixImpBase* GetImp(const FString& fstr_name);
};