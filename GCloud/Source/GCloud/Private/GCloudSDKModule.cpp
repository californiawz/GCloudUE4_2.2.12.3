// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "GCloudSDKModule.h"
#include "Misc/CoreDelegates.h"
#include "CoreGlobals.h"
#include "GCloudAppDelegate.h"

#if PLATFORM_MAC
#include "Misc/Paths.h"
extern "C" void gcloud_set_engine_plugin_path(const char* path , int len);
#elif PLATFORM_PS4 || PLATFORM_PS5
#include <kernel.h>
#endif

//using namespace ABase;
#define LOCTEXT_NAMESPACE "FGCloudSDKModule"

void FGCloudSDKModule::StartupModule()
{
#if PLATFORM_MAC
    FString relativePath = FPaths::ProjectDir();
    FString absPath = FPaths::ConvertRelativePathToFull(relativePath);
    const char* cpath = TCHAR_TO_UTF8(*absPath);
    gcloud_set_engine_plugin_path(cpath, strlen(cpath));

#elif PLATFORM_PS4 || PLATFORM_PS5
    //FString prxPath(TEXT("/app0/prx/"));
    SceKernelModule mod = sceKernelLoadStartModule("/app0/prx/gcloud.prx", 0, NULL, 0, NULL, NULL);
    if (mod < 0)
    {
       // error
      gcloudPSMod = -1;
    }
    else
    {
      gcloudPSMod = mod;
    }
#endif
    
#if !PLATFORM_LINUX
    
    GCloudAppDelegate::GetInstance().Initialize();
#endif
} 

void FGCloudSDKModule::ShutdownModule()
{
#if PLATFORM_PS4 || PLATFORM_PS5
    SceKernelModule mod = gcloudPSMod;
    if (gcloudPSMod > 0)
    {
      int iRet = sceKernelStopUnloadModule(mod, 0, NULL, 0, NULL, NULL);
      if (iRet < 0)
      {
        // error
      }

      gcloudPSMod = -1;
    }
#endif
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGCloudSDKModule, GCloud)
