/**************************************************

**** @file:     PixExtBpCall.cpp

**** @brief:

**** @author:   tianzelei

**** @date:     2021/11/09

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/


#include "PixExtBpCall.h"


#include "UObject/UObjectGlobals.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/StructOnScope.h"

#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Engine/Engine.h"
#include "Runtime/Launch/Resources/Version.h"


#include "PixUILog.h"


bool IsInputParam(uint64 PropertyFlags)
{
	const uint64 ConstOutParamFlag = CPF_OutParm | CPF_ConstParm;
	const uint64 IsConstOut = PropertyFlags & ConstOutParamFlag;
	return (CPF_Parm == (PropertyFlags & (CPF_Parm | CPF_ReturnParm)))
		&& ((0 == IsConstOut) || (ConstOutParamFlag == IsConstOut));
}


PixExtBpCall::PixExtBpCall()
{
}

PixExtBpCall::~PixExtBpCall()
{
}


pixui::PxLibValue PixExtBpCall::CappBPClassFun(const FString& fstr_bp_path, const FString& fstr_fun_name, pixui::PxLibParams* p_args)
{
	pixui::PxLibValue px_lib_value;

	if (IsInGameThread())
	{
		//	fstr_bp_path:/Game/bp/bp_lib_my
		//   Blueprint'/Game/bp/bp_lib_my.bp_lib_my_C'
		FString fstr_bp_lib_name = FPaths::GetBaseFilename(fstr_bp_path);
		FString fstr_bp_lib_path = TEXT("Blueprint'") + fstr_bp_path + TEXT(".") + fstr_bp_lib_name + TEXT("_C'");

		UClass* BlueprintGeneratedClass = LoadClass<UObject>(NULL, *fstr_bp_lib_path, NULL, 0, NULL);

		//PxLog_Trace("PixExtBpCall::CappBPClassFun  try to load %s   fun:%s", TCHAR_TO_UTF8(*fstr_bp_lib_path), TCHAR_TO_UTF8(*fstr_fun_name));
		if (BlueprintGeneratedClass)
		{
			//UBlueprintFunctionLibrary* pObjFuncTion = NewObject<UBlueprintFunctionLibrary>(GetTransientPackage(), BlueprintGeneratedClass);
			UFunction* BlueprintLibraryFunction = BlueprintGeneratedClass->FindFunctionByName(*fstr_fun_name);
			px_lib_value = ProcessClassFun(BlueprintGeneratedClass, BlueprintLibraryFunction, p_args);
		}
		else
		{
			PxLog_Error("PixExtBpCall::CappBPClassFun %s  error", TCHAR_TO_UTF8(*fstr_bp_lib_path));
		}
		//PxLog_Trace("PixExtBpCall::CappBPClassFun load %s   fun:%s  End", TCHAR_TO_UTF8(*fstr_bp_lib_path), TCHAR_TO_UTF8(*fstr_fun_name));
	}
	else
	{
		bool b_call_in_game = false;
		//call in game thread
		AsyncTask(ENamedThreads::GameThread, [&]()
		{
			px_lib_value = CappBPClassFun(fstr_bp_path, fstr_fun_name, p_args);

			b_call_in_game = true;
		});

		int n_wait_count = 0;
		while (true)
		{
			if (b_call_in_game)
			{
				break;
			}
			if (n_wait_count > 3)
			{
				break;
			}

			FPlatformProcess::Sleep(0.01f); //s  10ms
			n_wait_count++;
		}
		if (!b_call_in_game)
		{
			PxLog_Warning("Can not call CappBPClassFun in game thread  path:%s  fun:%s", TCHAR_TO_UTF8(*fstr_bp_path), TCHAR_TO_UTF8(*fstr_fun_name));
		}
	}
	return px_lib_value;
}


pixui::PxLibValue PixExtBpCall::CappCBPClassFun(const FString& fst_cbp_path, const FString& fstr_fun_name, pixui::PxLibParams* p_args)
{
	pixui::PxLibValue px_lib_value;

	if (IsInGameThread())
	{
		//	fst_cbp_path: PixUI.PixUIBPLibrary
		//	Blueprint'Class'/Script/PixUI.PixUIBPLibrary'

		FString fstr_bp_lib_path = TEXT("Class'/Script/") + fst_cbp_path + TEXT("'");

		UClass* BlueprintGeneratedClass = LoadClass<UObject>(NULL, *fstr_bp_lib_path, NULL, 0, NULL);
		//PxLog_Trace("PixExtBpCall::CappCBPClassFun  try to load %s   fun:%s", TCHAR_TO_UTF8(*fstr_bp_lib_path), TCHAR_TO_UTF8(*fstr_fun_name));
		if (BlueprintGeneratedClass)
		{
			//UBlueprintFunctionLibrary* pObjFuncTion = NewObject<UBlueprintFunctionLibrary>(GetTransientPackage(), BlueprintGeneratedClass);
			UFunction* BlueprintLibraryFunction = BlueprintGeneratedClass->FindFunctionByName(*fstr_fun_name);
			px_lib_value = ProcessClassFun(BlueprintGeneratedClass, BlueprintLibraryFunction, p_args);
		}
		else
		{
			PxLog_Error("PixExtBpCall::CappCBPClassFun %s  error", TCHAR_TO_UTF8(*fstr_bp_lib_path));
		}
		//PxLog_Trace("PixExtBpCall::CappCBPClassFun load %s   fun:%s  End", TCHAR_TO_UTF8(*fstr_bp_lib_path), TCHAR_TO_UTF8(*fstr_fun_name));
	}
	else
	{
		bool b_call_in_game = false;
		//call in game thread
		AsyncTask(ENamedThreads::GameThread, [&]()
		{
			px_lib_value = CappCBPClassFun(fst_cbp_path, fstr_fun_name, p_args);

			b_call_in_game = true;
		});

		int n_wait_count = 0;
		while (true)
		{
			if (b_call_in_game)
			{
				break;
			}
			if (n_wait_count > 3)
			{
				break;
			}

			FPlatformProcess::Sleep(0.01f); //s  10ms
			n_wait_count++;
		}
		if (!b_call_in_game)
		{
			PxLog_Warning("Can not call CappCBPClassFun in game thread  path:%s  fun:%s", TCHAR_TO_UTF8(*fst_cbp_path), TCHAR_TO_UTF8(*fstr_fun_name));
		}
	}


	return px_lib_value;
}


pixui::PxLibValue PixExtBpCall::ProcessClassFun(UClass* p_bpClass, UFunction* BlueprintLibraryFunction, pixui::PxLibParams* p_args)
{
	pixui::PxLibValue px_lib_value;
	//UBlueprintFunctionLibrary* pObjFuncTion = NewObject<UBlueprintFunctionLibrary>(GetTransientPackage(), BlueprintGeneratedClass);
	if (p_bpClass && BlueprintLibraryFunction && p_args)
	{
		FStructOnScope params(BlueprintLibraryFunction);
		/*
		void* funcPramsBuffer = (uint8*)FMemory_Alloca(BlueprintLibraryFunction->ParmsSize);
		uint8* inPramsBuffer = (uint8*)&inParams;
		for (TFieldIterator<UProperty> i(func); i; ++i)
		{
		UProperty* prop = *i;
		if (prop->GetFName().ToString().StartsWith("__"))
		{
		//ignore private param like __WolrdContext of function in blueprint function library
		continue;
		}
		void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
		if (prop->PropertyFlags & CPF_OutParm)
		{
		prop->CopyCompleteValue(propBuffer, outPramsBuffer);
		outPramsBuffer += prop->GetSize();
		}
		else if (prop->PropertyFlags & CPF_Parm)
		{
		prop->CopyCompleteValue(propBuffer, inPramsBuffer);
		inPramsBuffer += prop->GetSize();
		}
		}
		*/

		int32 ParamIndex = 0;
		//PxLog_Trace("param size:%d  ", BlueprintLibraryFunction->ParmsSize);
		uint8* funcPramsBuffer = params.GetStructMemory();	//(uint8*)FMemory_Alloca(BlueprintLibraryFunction->ParmsSize);

		bool b_can_call = true;
		bool b_have_support_return = false;

#if ENGINE_MAJOR_VERSION < 5

		/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 24
		for (TFieldIterator<FProperty> ParamIt(BlueprintLibraryFunction); ParamIt; ++ParamIt, ++ParamIndex)
#else
		for (TFieldIterator<UProperty> ParamIt(BlueprintLibraryFunction); ParamIt; ++ParamIt, ++ParamIndex)
#endif	//ENGINE_MINOR_VERSION > 24
		/////////////////////////////////////////////////////////////////////for ue4
#else

		/////////////////////////////////////////////////////////////////////for ue5
		for (TFieldIterator<FProperty> ParamIt(BlueprintLibraryFunction); ParamIt; ++ParamIt, ++ParamIndex)
		/////////////////////////////////////////////////////////////////////for ue5
#endif	//ENGINE_MAJOR_VERSION < 5
		{
			auto Param = *ParamIt;
			if (Param)
			{
				if (Param->GetFName().ToString().StartsWith("__"))
				{
					//__WolrdContext of function in blueprint function library
					continue;
				}
				//PxLog_Trace("Param index:%d size:%d   name:%s   type:%s", ParamIndex, Param->GetSize(), TCHAR_TO_UTF8(*Param->GetName()), TCHAR_TO_UTF8(*Param->GetCPPType()));


				uint64 propflag = Param->GetPropertyFlags();

				if (Param->HasAnyPropertyFlags(CPF_ReturnParm) || Param->HasAllPropertyFlags(CPF_OutParm))
				{
					//PxLog_Trace("return Params.%s = %s;  size:%d  type:%s", TCHAR_TO_ANSI(*Param->GetName()), TCHAR_TO_ANSI(*Param->GetNameCPP()), Param->GetSize(), TCHAR_TO_UTF8(*(Param->GetCPPType())));

					if (Param->GetCPPType() == TEXT("bool"))
					{
						b_have_support_return = true;
						px_lib_value = false;
					}
					else if (Param->GetCPPType() == TEXT("int32"))
					{
						b_have_support_return = true;
						px_lib_value = 0;
					}
					else if (Param->GetCPPType() == TEXT("float"))
					{
						b_have_support_return = true;
						px_lib_value = 0.0f;
					}
					else if (Param->GetCPPType() == TEXT("FString"))
					{
						b_have_support_return = true;
						px_lib_value = "";
					}
					else if (Param->GetCPPType() == TEXT("uint8"))
					{
						b_have_support_return = true;
						px_lib_value = 0;
					}
					else if (Param->GetCPPType() == TEXT("FText"))
					{
						b_have_support_return = true;
						px_lib_value = "";
					}
					else if (Param->GetCPPType() == TEXT("FName"))
					{
						b_have_support_return = true;
						px_lib_value = "";
					}
				}

				if (Param->HasAnyPropertyFlags(CPF_Parm | CPF_ReferenceParm | CPF_ConstParm))
					//if (IsInputParam(propflag) || Param->HasAnyPropertyFlags(CPF_OutParm))
				{
					if (Param->HasAnyPropertyFlags(CPF_OutParm))
					{
						//bp out param can not set with value
						continue;
					}

					if (ParamIndex >= p_args->ParamCount())
					{
						PxLog_Error("PixExtBpCall::ProcessClassFun to many params:%d  but cur over count:%d", ParamIndex, p_args->ParamCount());
						b_can_call = false;
						break;
					}

					void* propBuffer = Param->ContainerPtrToValuePtr<void*>(funcPramsBuffer);

					if (ParamIndex < p_args->ParamCount())
					{
						if (Param->GetCPPType() == TEXT("bool"))
						{
							if (p_args->ParamType(ParamIndex) == pixui::em_pxlib_value_bool)
							{
								bool b_in_value = p_args->GetVal<bool>(ParamIndex);
								Param->CopyCompleteValue(propBuffer, &b_in_value);
							}
							else
							{
								PxLog_Error("index:%d param error expect bool bug get %d", ParamIndex, p_args->ParamType(ParamIndex));
								b_can_call = false;
							}
						}
						else if (Param->GetCPPType() == TEXT("int32"))
						{
							if (p_args->ParamType(ParamIndex) == pixui::em_pxlib_value_long)
							{
								int32 n_in_value = p_args->GetVal<int32>(ParamIndex);
								Param->CopyCompleteValue(propBuffer, &n_in_value);
							}
							else
							{
								PxLog_Error("index:%d param error expect int bug get %d", ParamIndex, p_args->ParamType(ParamIndex));
								b_can_call = false;
							}
						}
						else if (Param->GetCPPType() == TEXT("float"))
						{
							if (p_args->ParamType(ParamIndex) == pixui::em_pxlib_value_double)
							{
								float f_in_value = p_args->GetVal<float>(ParamIndex);
								Param->CopyCompleteValue(propBuffer, &f_in_value);
							}
							else
							{
								PxLog_Error("index:%d param error expect float bug get %d", ParamIndex, p_args->ParamType(ParamIndex));
								b_can_call = false;
							}
						}
						else if (Param->GetCPPType() == TEXT("FString"))
						{
							if (p_args->ParamType(ParamIndex) == pixui::em_pxlib_value_string)
							{
								char* psz_string = p_args->GetVal<char*>(ParamIndex);
								FString str_in_value = UTF8_TO_TCHAR(psz_string);
								Param->CopyCompleteValue(propBuffer, &str_in_value);
							}
							else
							{
								PxLog_Error("index:%d param error expect string bug get %d", ParamIndex, p_args->ParamType(ParamIndex));
								b_can_call = false;
							}
						}
						else if (Param->GetCPPType() == TEXT("uint8"))
						{
							if (p_args->ParamType(ParamIndex) == pixui::em_pxlib_value_long)
							{
								int32 n_in_value = p_args->GetVal<int32>(ParamIndex);
								Param->CopyCompleteValue(propBuffer, &n_in_value);
							}
							else
							{
								PxLog_Error("index:%d param error expect byte bug get %d", ParamIndex, p_args->ParamType(ParamIndex));
								b_can_call = false;
							}
						}
						else if (Param->GetCPPType() == TEXT("FText"))
						{
							if (p_args->ParamType(ParamIndex) == pixui::em_pxlib_value_string)
							{
								char* psz_string = p_args->GetVal<char*>(ParamIndex);
								FString str_in_value = UTF8_TO_TCHAR(psz_string);
								FText txt_value = FText::FromString(str_in_value);
								Param->CopyCompleteValue(propBuffer, &txt_value);
							}
							else
							{
								PxLog_Error("index:%d param error expect string bug get %d", ParamIndex, p_args->ParamType(ParamIndex));
								b_can_call = false;
							}
						}
						else if (Param->GetCPPType() == TEXT("FName"))
						{
							if (p_args->ParamType(ParamIndex) == pixui::em_pxlib_value_string)
							{
								char* psz_string = p_args->GetVal<char*>(ParamIndex);
								FString str_in_value = UTF8_TO_TCHAR(psz_string);

								FName name_value(*str_in_value);
								Param->CopyCompleteValue(propBuffer, &name_value);
							}
							else
							{
								PxLog_Error("index:%d param error expect string bug get %d", ParamIndex, p_args->ParamType(ParamIndex));
								b_can_call = false;
							}
						}
					}
					else
					{
						b_can_call = false;
					}
				}
			}
		}

		if (b_can_call)
		{
			//do stuff with UFunction
			p_bpClass->GetDefaultObject()->ProcessEvent(BlueprintLibraryFunction, funcPramsBuffer);
			//pObjFuncTion->ProcessEvent(BlueprintLibraryFunction, params.GetStructMemory());

			if (b_have_support_return)
			{
				//get return value
#if ENGINE_MAJOR_VERSION < 5

				/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 24
				for (TFieldIterator<FProperty> ParamIt(BlueprintLibraryFunction); ParamIt; ++ParamIt, ++ParamIndex)
#else
				for (TFieldIterator<UProperty> ParamIt(BlueprintLibraryFunction); ParamIt; ++ParamIt, ++ParamIndex)
#endif	//ENGINE_MINOR_VERSION > 24
				/////////////////////////////////////////////////////////////////////for ue4
#else
				/////////////////////////////////////////////////////////////////////for ue5
				for (TFieldIterator<FProperty> ParamIt(BlueprintLibraryFunction); ParamIt; ++ParamIt, ++ParamIndex)
				/////////////////////////////////////////////////////////////////////for ue5
#endif	//ENGINE_MAJOR_VERSION < 5
				{
					auto prop = *ParamIt;
					if (prop->HasAnyPropertyFlags(CPF_ReturnParm) || prop->HasAllPropertyFlags(CPF_OutParm))
					{
						void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
						if (prop->GetCPPType() == TEXT("bool"))
						{
							bool b_ret = false;
							prop->CopyCompleteValue(&b_ret, propBuffer);
							px_lib_value = b_ret;
						}
						else if (prop->GetCPPType() == TEXT("int32"))
						{
							int32 n_ret = 0;
							prop->CopyCompleteValue(&n_ret, propBuffer);
							px_lib_value = n_ret;
						}
						else if (prop->GetCPPType() == TEXT("float"))
						{
							float f_ret = 0.0f;
							prop->CopyCompleteValue(&f_ret, propBuffer);
							px_lib_value = f_ret;
						}
						else if (prop->GetCPPType() == TEXT("FString"))
						{
							FString fstr_ret = "";
							prop->CopyCompleteValue(&fstr_ret, propBuffer);
							px_lib_value = TCHAR_TO_UTF8(*fstr_ret);
						}
						else if (prop->GetCPPType() == TEXT("uint8"))
						{
							uint8 n_ret = 0;
							prop->CopyCompleteValue(&n_ret, propBuffer);
							px_lib_value = n_ret;
						}
						else if (prop->GetCPPType() == TEXT("FText"))
						{
							FText text;
							prop->CopyCompleteValue(&text, propBuffer);
							FString fstr_ret = text.ToString();
							px_lib_value = TCHAR_TO_UTF8(*fstr_ret);
						}
						else if (prop->GetCPPType() == TEXT("FName"))
						{
							FName name_;
							prop->CopyCompleteValue(&name_, propBuffer);
							FString fstr_ret = name_.ToString();
							px_lib_value = TCHAR_TO_UTF8(*fstr_ret);
						}
						break;
					}
				}
			}
		}
	}
	else
	{
		PxLog_Error("PixExtBpCall::ProcessClassFun error:BlueprintLibraryFunction null!!!");
	}
	return px_lib_value;
}