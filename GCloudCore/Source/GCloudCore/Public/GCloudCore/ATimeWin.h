#ifndef __ATIMEWIN_H__
#define __ATIMEWIN_H__
#if defined(_WIN32) || defined(_WIN64)
//_GCLOUDCORE_UE defined in GCloudCore.Build.cs
#if defined(_GCLOUDCORE_UE) && (_GCLOUDCORE_UE > 0)
#include "Windows/AllowWindowsPlatformAtomics.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <winsock2.h>
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#else
#include <winsock2.h>
#endif
#include <Windows.h>

namespace ABase
{
    int gettimeofday(struct timeval *a_pstTv, struct timezone *a_pstTz);
}
#endif

#endif /*__ATIMEWIN_H__*/
