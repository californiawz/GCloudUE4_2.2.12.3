/**************************************************

**** @file:     PixUtil_android.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/21

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/




#include "PixUtil.h"

#if PLATFORM_ANDROID

#include "PixUILog.h"

#include <sys/system_properties.h>

FString GetAndroidOSVersion()
{
	char *key = (char *)"ro.build.version.sdk";
	//char *key = (char *)"ro.build.version.release";
	char value[1024] = { 0 };
 	int ret = __system_property_get(key, value);
 	if (ret <= 0) {
		PxLog_Error("PixUtil::OSversion __system_property_get ERROR");
 	}
	return UTF8_TO_TCHAR(value);
}

FString PixUtil::OSversion()
{
	static FString fstr_os_version = GetAndroidOSVersion();
	return fstr_os_version;
}


float PixUtil::OSversionCode()
{
	static float f_os_version = FCString::Atof(*OSversion());
	return f_os_version;
}
#endif	//PLATFORM_ANDROID