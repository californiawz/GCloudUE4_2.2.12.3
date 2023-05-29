// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.


#include "PixUIAssetEditorToolkit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
#include "Blueprint/UserWidget.h"
#include "PixUIAssetEditor/AssetTools/PixUIAsset.h"
#include "PixUIAssetEditor/Widgets/SPixUIAssetEditor.h"
#include "PixUIAssetEditor/Widgets/SPixUIWidgetEditor.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FPixUIAssetEditorToolkit"

DEFINE_LOG_CATEGORY_STATIC(LogTextAssetEditor, Log, All);


/* Local constants
 *****************************************************************************/

namespace TextAssetEditor
{
	static const FName AppIdentifier("PixUIEditorApp");
	static const FName PixUIWidgetTabId("PixUIWidgetEditor");
	static const FName PixUIContentTabId("PixUIContentEditor");
}


/* FPixUIAssetEditorToolkit structors
 *****************************************************************************/

FPixUIAssetEditorToolkit::FPixUIAssetEditorToolkit()
	: PixUIAsset(nullptr)
{
}


FPixUIAssetEditorToolkit::~FPixUIAssetEditorToolkit()
{
	FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	GEditor->UnregisterForUndo(this);
}


/* FPixUIAssetEditorToolkit interface
 *****************************************************************************/

void FPixUIAssetEditorToolkit::Initialize(UPixUIAsset* InTextAsset, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost)
{
	PixUIAsset = InTextAsset;

	// Support undo/redo
	PixUIAsset->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	// create tab layout
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_PixUIAssetEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.66f)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.1f)
				)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(TextAssetEditor::PixUIWidgetTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.9f)
				)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(TextAssetEditor::PixUIContentTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.9f)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor(
		InMode,
		InToolkitHost,
		TextAssetEditor::AppIdentifier,
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		InTextAsset
	);

	RegenerateMenusAndToolbars();
}


/* FAssetEditorToolkit interface
 *****************************************************************************/

void FPixUIAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_PixUIAssetEditor", "PixUI Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(TextAssetEditor::PixUIContentTabId, FOnSpawnTab::CreateSP(this, &FPixUIAssetEditorToolkit::HandleTabManagerSpawnTab, TextAssetEditor::PixUIContentTabId))
	            .SetDisplayName(LOCTEXT("PixUIEditorContentTabName", "PixUI Content Editor"))
	            .SetGroup(WorkspaceMenuCategoryRef)
	            .SetIcon(FSlateIcon());

	InTabManager->RegisterTabSpawner(TextAssetEditor::PixUIWidgetTabId, FOnSpawnTab::CreateSP(this, &FPixUIAssetEditorToolkit::HandleTabManagerSpawnTab, TextAssetEditor::PixUIWidgetTabId))
	            .SetDisplayName(LOCTEXT("PixUIEditorWidgetTabName", "PixUI Widget Editor"))
	            .SetGroup(WorkspaceMenuCategoryRef)
	            .SetIcon(FSlateIcon());
}


void FPixUIAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(TextAssetEditor::PixUIContentTabId);
	InTabManager->UnregisterTabSpawner(TextAssetEditor::PixUIWidgetTabId);
}


/* IToolkit interface
 *****************************************************************************/

FText FPixUIAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "PixUI Asset Editor");
}


FName FPixUIAssetEditorToolkit::GetToolkitFName() const
{
	return FName("PixUIAssetEditor");
}


FLinearColor FPixUIAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}


FString FPixUIAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "PixUIAsset ").ToString();
}


/* FGCObject interface
 *****************************************************************************/

void FPixUIAssetEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(PixUIAsset);
}


/* FEditorUndoClient interface
*****************************************************************************/

void FPixUIAssetEditorToolkit::PostUndo(bool bSuccess)
{
}


void FPixUIAssetEditorToolkit::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}


/* FPixUIAssetEditorToolkit callbacks
 *****************************************************************************/

TSharedRef<SDockTab> FPixUIAssetEditorToolkit::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;

	if (TabIdentifier == TextAssetEditor::PixUIContentTabId)
	{
		TabWidget = SNew(SPixUIAssetEditor, PixUIAsset);
		if (PixUIAsset->AssetType == UPixUIAsset::Html)
		{
		}
	}
	else if (TabIdentifier == TextAssetEditor::PixUIWidgetTabId)
	{
		TabWidget = SNew(SPixUIWidgetEditor, PixUIAsset);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}


#undef LOCTEXT_NAMESPACE
