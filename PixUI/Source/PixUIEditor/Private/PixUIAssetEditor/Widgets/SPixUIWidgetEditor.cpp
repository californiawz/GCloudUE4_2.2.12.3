// Fill out your copyright notice in the Description page of Project Settings.


#include "SPixUIWidgetEditor.h"

#include "PixUIWidget.h"
#include "SlateOptMacros.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SPixUIWidgetEditor::~SPixUIWidgetEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
	auto PixUIWidget = Cast<UPixUIWidget>(UserWidget->GetRootWidget());
	PixUIWidget->ClosePage();
}


void SPixUIWidgetEditor::Construct(const FArguments& InArgs, UPixUIAsset* InTextAsset)
{
	PixUIAsset = InTextAsset;
	UserWidget = CreateWidget<UUserWidget>(GEditor->GetEditorWorldContext().World(), LoadClass<UUserWidget>(NULL, TEXT("/Game/umg/umg_test.umg_test_C")));
	UserWidget->Construct();


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
			UserWidget->TakeWidget()
		]
		+ SVerticalBox::Slot()
		.FillHeight(0.1f)
		[
			SNew(SButton)
			.OnClicked(this, &SPixUIWidgetEditor::HandleFlushPixUIView)
		]
	];

	//FCoreUObjectDelegates::OnObjectSaved.AddSP(this, &SPixUIWidgetEditor::HandlePixUIAssetPropertySaved);

#if ENGINE_MAJOR_VERSION < 5
	/////////////////////////////////////////////////////////////////////for ue4
	FCoreUObjectDelegates::OnObjectSaved.AddSP(this, &SPixUIWidgetEditor::HandlePixUIAssetPropertySaved);
	/////////////////////////////////////////////////////////////////////for ue4
#else
	/////////////////////////////////////////////////////////////////////for ue5
	//FCoreUObjectDelegates::OnObjectSaved
	FCoreUObjectDelegates::OnObjectSaved.AddSP(this, &SPixUIWidgetEditor::HandlePixUIAssetPropertySaved);
	/////////////////////////////////////////////////////////////////////for ue5
#endif  //ENGINE_MAJOR_VERSION < 5

}

FReply SPixUIWidgetEditor::HandleFlushPixUIView()
{
	if (PixUIAsset->AssetType == UPixUIAsset::Html)
	{
		auto PixUIWidget = Cast<UPixUIWidget>(UserWidget->GetRootWidget());
		if (PixUIAsset->NeedPfbsData)
		{
			PixUIWidget->OpenPageFromUrl(PixUIAsset->PFBS_Path);
		}
		else
		{
			PixUIWidget->OpenPageFromUrl(PixUIAsset->Path);
		}
	}
	else if (PixUIAsset->AssetType == UPixUIAsset::JavaScript)
	{
		TArray<uint8> content;
		FString templateHtml = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>Title</title></head><body><script>window.onload(()=>{external.doBuffer(`{PixUIJavaScript}`);})</script></body></html>";
		templateHtml = templateHtml.Replace(TEXT("{PixUIJavaScript}"), *PixUIAsset->Text.ToString());
		content.SetNum(templateHtml.Len());
		auto PixUIWidget = Cast<UPixUIWidget>(UserWidget->GetRootWidget());
		memcpy(content.GetData(), TCHAR_TO_ANSI(*templateHtml), templateHtml.Len());
		PixUIWidget->OpenPageFromData(content, PixUIAsset->Path);
	}
	else
	{
		return FReply::Unhandled();
	}
	return FReply::Handled();
}

void SPixUIWidgetEditor::HandlePixUIAssetPropertySaved(UObject* Object)
{
	if (Object == PixUIAsset)
	{
	}
}


/* SPixUIWidgetEditor callbacks
 *****************************************************************************/

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
