// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "GVoice.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "GVoiceAppDelegate.h"

#define LOCTEXT_NAMESPACE "FGVoiceModule"

void FGVoiceModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

    UE_LOG(LogInit, Warning, TEXT("StartupModule()1"));
	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("GVoice")->GetBaseDir();

#ifndef __GVOICE_MAC__
    GVoiceAppDelegate::GetInstance().Initialize();
#endif

}

void FGVoiceModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	//FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	//ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGVoiceModule, GVoice)
