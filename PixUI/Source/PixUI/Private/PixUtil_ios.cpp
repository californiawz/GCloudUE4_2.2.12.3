/**************************************************

**** @file:     PixUtil_ios.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/21

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/




#include "PixUtil.h"

#if PLATFORM_IOS

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

FString PixUtil::OSversion()
{
	static FString fstr_os_version = UTF8_TO_TCHAR([[UIDevice currentDevice].systemVersion UTF8String]);
	return fstr_os_version;
}

float PixUtil::OSversionCode()
{
	static float f_os_version = FCString::Atof(*OSversion());
	return f_os_version;
}
#endif //PLATFORM_IOS