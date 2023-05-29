/**************************************************

**** @file:     PixExtBpCall.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/11/09

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/



#pragma once

#include "CoreMinimal.h"
#include "hf_loadlib_template.h"


class PixExtBpCall
{
public:
	PixExtBpCall();
	~PixExtBpCall();

public:
	static pixui::PxLibValue CappBPClassFun(const FString& fstr_bp_path, const FString& fstr_fun_name, pixui::PxLibParams* p_args);
	static pixui::PxLibValue CappCBPClassFun(const FString& fst_cbp_path, const FString& fstr_fun_name, pixui::PxLibParams* p_args);
private:
	static pixui::PxLibValue ProcessClassFun(UClass* p_bpClass, UFunction* BlueprintLibraryFunction, pixui::PxLibParams* p_args);
};

