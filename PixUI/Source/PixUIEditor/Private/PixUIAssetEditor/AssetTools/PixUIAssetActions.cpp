// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PixUIAssetActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "PixUIAssetEditor/AssetTools/PixUIAsset.h"
#include "PixUIAssetEditor/Toolkits/PixUIAssetEditorToolkit.h"



#define LOCTEXT_NAMESPACE "AssetTypeActions"


/* FPixUIAssetActions constructors
 *****************************************************************************/

FPixUIAssetActions::FPixUIAssetActions()
{
}


/* FAssetTypeActions_Base overrides
 *****************************************************************************/

bool FPixUIAssetActions::CanFilter()
{
	return true;
}


void FPixUIAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);

	auto TextAssets = GetTypedWeakObjectPtrs<UPixUIAsset>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("PixUIAsset_ReverseText", "Reverse Text"),
		LOCTEXT("PixUIAsset_ReverseTextToolTip", "Reverse the text stored in the selected text asset(s)."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=]
			{
				for (auto& PixUIAsset : TextAssets)
				{
					if (PixUIAsset.IsValid() && !PixUIAsset->Text.IsEmpty())
					{
						PixUIAsset->Text = FText::FromString(PixUIAsset->Text.ToString().Reverse());
						PixUIAsset->PostEditChange();
						PixUIAsset->MarkPackageDirty();
					}
				}
			}),
			FCanExecuteAction::CreateLambda([=]
			{
				for (auto& PixUIAsset : TextAssets)
				{
					if (PixUIAsset.IsValid() && !PixUIAsset->Text.IsEmpty())
					{
						return true;
					}
				}
				return false;
			})
		)
	);
}


uint32 FPixUIAssetActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}


FText FPixUIAssetActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_PixUIAsset", "PixUI Asset");
}


UClass* FPixUIAssetActions::GetSupportedClass() const
{
	return UPixUIAsset::StaticClass();
}


FColor FPixUIAssetActions::GetTypeColor() const
{
	return FColor::White;
}


bool FPixUIAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}


void FPixUIAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
		                          ? EToolkitMode::WorldCentric
		                          : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto PixUIAsset = Cast<UPixUIAsset>(*ObjIt);

		if (PixUIAsset != nullptr)
		{
			TSharedRef<FPixUIAssetEditorToolkit> EditorToolkit = MakeShareable(new FPixUIAssetEditorToolkit());
			EditorToolkit->Initialize(PixUIAsset, Mode, EditWithinLevelEditor);
		}
	}
}


#undef LOCTEXT_NAMESPACE
