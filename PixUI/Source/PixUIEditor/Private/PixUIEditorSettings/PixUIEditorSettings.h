// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PixUIEditorSettings.generated.h"

/**
 * 
 */
UCLASS(config=Engine, defaultconfig)
class PIXUIEDITOR_API UPixUIEditorSettings : public UObject
{
	GENERATED_UCLASS_BODY()
	static void Initialize();

	static void Shutdown();

	static void RegisterAssetSettings();
	static void UnregisterAssetSettings();

	UPROPERTY(EditAnywhere, config, Category=Experimental)
	bool bUsePfbsData;
	
	UPROPERTY(EditAnywhere, config, Category=EditorSettings)
	FDirectoryPath PixUIHtmlSrcDir;

	UPROPERTY(EditAnywhere, config, Category=EditorSettings)
	FDirectoryPath PixUIHtmlDstDir;
	
	UPROPERTY(EditAnywhere, config, Category=AssetSettings)
	TArray<FDirectoryPath> arrHtmlFilePath;
};
