// Copyright Epic Games, Inc. All Rights Reserved.

#include "PixUIEditor.h"
#include "PixUIEditorMgr.h"

#define LOCTEXT_NAMESPACE "FPixUIEditorModule"

void FPixUIEditorModule::StartupModule()
{
#if WITH_EDITOR
	PixUIEditorMgr::StartUp();
#endif //WITH_EDITOR

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FPixUIEditorModule::ShutdownModule()
{
#if WITH_EDITOR
	PixUIEditorMgr::Shutdown();
#endif //WITH_EDITOR

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPixUIEditorModule, PixUIEditor)
