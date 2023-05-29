/**************************************************

**** @file:     PixUtil_win.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/21

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/


#include "PixUtil.h"


#if PLATFORM_WINDOWS

#include "Projects.h"

FString GetWinOSVersion()
{
	DWORD dwMajorVer = 0, dwMinorVer = 0, dwBuildNumber = 0;
	bool bRet = false;
	void* hModNtdll = FPlatformProcess::GetDllHandle(TEXT("ntdll.dll"));
	if (hModNtdll)
	{
		typedef void (WINAPI *pfRTLGETNTVERSIONNUMBERS)(DWORD*, DWORD*, DWORD*);
		pfRTLGETNTVERSIONNUMBERS pfRtlGetNtVersionNumbers;
		pfRtlGetNtVersionNumbers = (pfRTLGETNTVERSIONNUMBERS)FPlatformProcess::GetDllExport(hModNtdll, TEXT("RtlGetNtVersionNumbers"));
		if (pfRtlGetNtVersionNumbers)
		{
			pfRtlGetNtVersionNumbers(&dwMajorVer, &dwMinorVer, &dwBuildNumber);
			dwBuildNumber &= 0x0ffff;
			bRet = true;
		}

		FPlatformProcess::FreeDllHandle(hModNtdll);
		hModNtdll = nullptr;
	}

	return FString::Printf(TEXT("%ld.%ld"), dwMajorVer, dwMinorVer);
}



FString PixUtil::OSversion()
{
	static FString fstr_os_version = GetWinOSVersion();
	return fstr_os_version;
}

float PixUtil::OSversionCode()
{
	static float f_os_version = FCString::Atof(*OSversion());
	return f_os_version;
}

#endif //PLATFORM_WINDOWS