/**************************************************

**** @file:     PixUtil_mac.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/21

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/


#include "PixUtil.h"

#if PLATFORM_MAC

#include <stdio.h>

/*!
@brief    Returns one component of the OS version
@param    n_part  1=major, 2=minor, 3=bugfix
*/
int GetOSVersionPart(int n_part) {
	char cmd[64];
	sprintf(
		cmd,
		"sw_vers -productVersion | awk -F '.' '{print $%d}'",
		n_part
	);
	FILE* stdoutFile = popen(cmd, "r");

	int answer = 0;
	if (stdoutFile) {
		char buff[16];
		char *stdout = fgets(buff, sizeof(buff), stdoutFile);
		pclose(stdoutFile);
		sscanf(stdout, "%d", &answer);
	}

	return answer;
}


FString PixUtil::OSversion()
{
	static FString fstr_os_version = FString::Printf(TEXT("%d.%d.%d"), GetOSVersionPart(1), GetOSVersionPart(2), GetOSVersionPart(3));
	return fstr_os_version;
}


float PixUtil::OSversionCode()
{
	static float f_os_version = FCString::Atof(*OSversion());
	return f_os_version;
}


#endif //PLATFORM_MAC