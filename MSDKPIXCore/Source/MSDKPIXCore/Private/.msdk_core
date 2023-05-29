// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MSDKCore.h"
#include "Interfaces/IPluginManager.h"
#include "HAL/PlatformProcess.h"

#define LOCTEXT_NAMESPACE "FMSDKCoreModule"

void FMSDKCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if PLATFORM_WINDOWS
	if (GIsEditor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Run for editor, no need to load dll"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Run for standalone, load dll"));
		FString path = IPluginManager::Get().FindPlugin("MSDKCore")->GetBaseDir() + "/Source/MSDKCore/lib/Win64/";
		TArray<FString> dllsArr;
		dllsArr.Add(TEXT("zlibwapi.dll"));
		dllsArr.Add(TEXT("libcrypto-1_1.dll"));
		dllsArr.Add(TEXT("libssh2.dll"));
		dllsArr.Add(TEXT("libssl-1_1.dll"));
		dllsArr.Add(TEXT("libcurl.dll"));
		dllsArr.Add(TEXT("pthreadGC2.dll"));
		dllsArr.Add(TEXT("pthreadVC2.dll"));
		dllsArr.Add(TEXT("MSDKCore.dll"));
	
		for (auto& dllName:dllsArr) {
			FString dllPath = path + dllName;
			UE_LOG(LogTemp, Warning, TEXT("Start to load %s"), *dllPath);
			void *dllHandle = FPlatformProcess::GetDllHandle(*dllPath);
			if (!dllHandle)
			{
				FString errMsg = "Failed to load dll for " + dllPath;
				UE_LOG(LogTemp, Warning, TEXT("%s"), *errMsg);
			}
		}
	}
	

#endif
}

void FMSDKCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMSDKCoreModule, MSDKCore)