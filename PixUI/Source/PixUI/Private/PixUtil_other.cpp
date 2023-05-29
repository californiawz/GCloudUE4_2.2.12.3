/**************************************************

**** @file:     PixUtil_other.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/21

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/





#include "PixUtil.h"

#if !PLATFORM_IOS && !PLATFORM_ANDROID && !PLATFORM_MAC && !PLATFORM_WINDOWS
FString PixUtil::OSversion()
{
	return TEXT("Other_system");
}


float PixUtil::OSversionCode()
{
	return 0.0f;
}
#endif //!PLATFORM_IOS && !PLATFORM_ANDROID && !PLATFORM_MAC && !PLATFORM_WINDOWS