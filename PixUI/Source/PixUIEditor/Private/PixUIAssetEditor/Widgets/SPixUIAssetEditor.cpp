// Fill out your copyright notice in the Description page of Project Settings.


#include "SPixUIAssetEditor.h"

#include "SlateOptMacros.h"
#include "Blueprint/UserWidget.h"
#include "PixUIAssetEditor/Factories/PixUIAssetFactory.h"
#include "Components/CanvasPanelSlot.h"
#include "Runtime/Launch/Resources/Version.h"

#include "EditorStyleSet.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SPixUIAssetEditor::~SPixUIAssetEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}


void SPixUIAssetEditor::Construct(const FArguments& InArgs, UPixUIAsset* InTextAsset)
{
	PixUIAsset = InTextAsset;
	if (PixUIAsset->AssetType == UPixUIAsset::Html)
	{
		// UCanvasPanelSlot* p_panel_slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(wptr_child_widget_pixui_.Get());
		// wptr_child_widget_pixui_->AddToRoot();
		// wptr_child_widget_pixui_->OpenPageFromUrl("https://pixui-dev.cdn-go.cn/pxtests/latest/v0.4/index.html");
		// p_panel_slot->SetSize(FVector2D(200, 200));
	}
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SAssignNew(EditableTextBox, SMultiLineEditableTextBox)
					.BackgroundColor(FLinearColor::White)
#if ENGINE_MAJOR_VERSION < 5

		/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION >= 21 
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
#else
					.Font(FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
#endif
		/////////////////////////////////////////////////////////////////////for ue4

#else

		/////////////////////////////////////////////////////////////////////for ue5
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
		/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5
					.ForegroundColor(FLinearColor::Black)
					.Margin(4.0f)
					.OnTextChanged(this, &SPixUIAssetEditor::HandleEditableTextBoxTextChanged)
					.OnTextCommitted(this, &SPixUIAssetEditor::HandleEditableTextBoxTextCommitted)
					.Text(PixUIAsset->Text)
		]
	];

#if ENGINE_MAJOR_VERSION < 5
	/////////////////////////////////////////////////////////////////////for ue4
	FCoreUObjectDelegates::OnObjectSaved.AddSP(this, &SPixUIAssetEditor::HandlePixUIAssetPropertySaved);
	/////////////////////////////////////////////////////////////////////for ue4
#else
	/////////////////////////////////////////////////////////////////////for ue5
	//FCoreUObjectDelegates::OnObjectSaved
	FCoreUObjectDelegates::OnObjectSaved.AddSP(this, &SPixUIAssetEditor::HandlePixUIAssetPropertySaved);
	/////////////////////////////////////////////////////////////////////for ue5
#endif  //ENGINE_MAJOR_VERSION < 5

	//FCoreUObjectDelegates::OnObjectSaved.AddSP(this, &SPixUIAssetEditor::HandlePixUIAssetPropertySaved);
}


/* SPixUIAssetEditor callbacks
 *****************************************************************************/

void SPixUIAssetEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	PixUIAsset->MarkPackageDirty();
}


void SPixUIAssetEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	PixUIAsset->Text = EditableTextBox->GetText();
}


void SPixUIAssetEditor::HandlePixUIAssetPropertySaved(UObject* Object)
{
	if (Object == PixUIAsset)
	{
		EditableTextBox->SetText(PixUIAsset->Text);
		FFileHelper::SaveStringToFile(*PixUIAsset->Text.ToString(), *PixUIAsset->Path);
		if (PixUIAsset->NeedPfbsData)
		{
			UPixUIAssetFactory::TransformToPfbs(PixUIAsset->Path, PixUIAsset->PFBS_Path);
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
