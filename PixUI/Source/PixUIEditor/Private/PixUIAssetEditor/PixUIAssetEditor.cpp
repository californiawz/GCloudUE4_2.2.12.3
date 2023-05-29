// Fill out your copyright notice in the Description page of Project Settings.


#include "PixUIAssetEditor.h"

#include "AssetToolsModule.h"
#include "AssetTools/PixUIAssetActions.h"
#define LOCTEXT_NAMESPACE "FPixUIModule"

void FPixUIAssetEditor::Initialize()
{
	RegisterAssetTools();
}

void FPixUIAssetEditor::Shutdown()
{
	UnregisterAssetTools();
}

void FPixUIAssetEditor::RegisterAssetTools()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FPixUIAssetActions()));
}

/** The collection of registered asset type actions. */
TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;

void FPixUIAssetEditor::UnregisterAssetTools()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();

		for (const TSharedRef<IAssetTypeActions>& Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}

	RegisteredAssetTypeActions.Reset();
}

/**
 * Registers a single asset type action.
 *
 * @param AssetTools The asset tools object to register with.
 * @param Action The asset type action to register.
 */
void FPixUIAssetEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetTypeActions.Add(Action);
}
#undef LOCTEXT_NAMESPACE
