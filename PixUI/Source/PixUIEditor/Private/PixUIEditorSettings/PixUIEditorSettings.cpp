// Fill out your copyright notice in the Description page of Project Settings.


#include "PixUIEditorSettings.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FPixUIModule"

UPixUIEditorSettings::UPixUIEditorSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPixUIEditorSettings::RegisterAssetSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "PixUI",
		                                 LOCTEXT("RuntimeSettingsName", "PixUI"),
		                                 LOCTEXT("RuntimeSettingsDescription", "Configure the PixUI Editor plugin"),
		                                 GetMutableDefault<UPixUIEditorSettings>());
	}
}

void UPixUIEditorSettings::UnregisterAssetSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "PixUI");
	}
}

void UPixUIEditorSettings::Initialize()
{
	RegisterAssetSettings();
}

void UPixUIEditorSettings::Shutdown()
{
	UnregisterAssetSettings();
}
#undef LOCTEXT_NAMESPACE
