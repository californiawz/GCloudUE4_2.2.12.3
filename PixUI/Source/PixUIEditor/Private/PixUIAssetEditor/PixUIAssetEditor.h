// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IAssetTools.h"

/**
 * 
 */
class PIXUIEDITOR_API FPixUIAssetEditor
{
public:
	static void Initialize();

	static void Shutdown();

	static void RegisterAssetTools();
	static void UnregisterAssetTools();
	static void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
};
