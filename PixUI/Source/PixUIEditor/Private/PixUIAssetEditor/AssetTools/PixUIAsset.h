// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PixUIAsset.generated.h"

/**
 * 
 */
UCLASS()
class PIXUIEDITOR_API UPixUIAsset : public UObject
{
	GENERATED_BODY()
public:
	enum PixUIAssetType
	{
		Html,
		JavaScript
	};

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="PixUIEditorAsset")
	bool NeedPfbsData = false;
	FString Name;
	FString Path;
	FString PFBS_Path;
	FText Text;
	TArray<uint8> Pfbs_Text_Array;
	PixUIAssetType AssetType;
};
