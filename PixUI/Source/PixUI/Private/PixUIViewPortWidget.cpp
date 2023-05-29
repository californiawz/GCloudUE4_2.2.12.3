/**************************************************

**** @file:     PixUIViewPortWidget.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixUIViewPortWidget.h"
#include "UnrealEngine.h"
#include "CoreUObject.h"
#include "Misc/CoreDelegates.h"

#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

#include "PixUILog.h"

#include "UMG.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#endif


void UPixUIViewPortWidget::NativeConstruct()
{
    //call super NativeConstruct
    Super::NativeConstruct();

    PxLog_Log("UPixUIViewPortWidget::NativeConstruct Create");
}


void UPixUIViewPortWidget::NativeDestruct()
{
    Super::NativeDestruct();

    pixuiWinOpenDelegate.Clear();
    pixuiWinConfirmDelegate.Clear();
    pixuiWinPrompDelegate.Clear();

    if (PixUIWidget().IsValid())
    {
        PixUIWidget()->RemoveFromRoot();
    }

    PixUIWidget() = nullptr;

    PxLog_Log("UPixUIViewPortWidget::NativeDestruct Destroy");
}


void UPixUIViewPortWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}


TSharedRef<SWidget> UPixUIViewPortWidget::RebuildWidget()
{
	UCanvasPanel* p_root = Cast<UCanvasPanel>(GetRootWidget());

	if (!p_root && WidgetTree && !GetRootWidget())
	{
		//try to create root widget
		p_root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootWidget"));
		WidgetTree->RootWidget = p_root;
	}

	//UPixUIWidget need a root panel
	if (p_root)
	{
		//create pixui widget
		PixUIWidget() = NewObject<UPixUIWidget>();

		UCanvasPanelSlot* p_SlotPanle = p_root->AddChildToCanvas(PixUIWidget().Get());
		if (p_SlotPanle)
		{
			PixUIWidget()->AddToRoot();

			p_SlotPanle->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
			p_SlotPanle->SetOffsets(FMargin(0.0f, 0.0f, 0.0f, 0.0f));

			//FScriptDelegate Delegate;
			//Delegate.BindUFunction(this, FName(TEXT("OnPixuiOpenDelegate")));
			PixUIWidget()->pixuiWinOpenDelegate.BindDynamic(this, &UPixUIViewPortWidget::OnPixuiOpenDelegate);
			PixUIWidget()->pixuiWinConfirmDelegate.BindDynamic(this, &UPixUIViewPortWidget::OnPixuiConfirmDelegate);
			PixUIWidget()->pixuiWinPrompDelegate.BindDynamic(this, &UPixUIViewPortWidget::OnPixuiPromptDelegate);
		}
		else
		{
			PixUIWidget() = nullptr;
		}
	}
	else
	{
		PxLog_Error(" UPixUIViewPortWidget::RebuildWidget create UPixUIWidget error,have not root canvaspanel node");
	}
	PxLog_Log("UPixUIViewPortWidget::RebuildWidget build");
	return Super::RebuildWidget();
}


UPixUIWidget* UPixUIViewPortWidget::GetPixuiWidget()
{
    return PixUIWidget().IsValid() ? PixUIWidget().Get() : nullptr;
}


int32 UPixUIViewPortWidget::LoadPXViewFromUrl(const FString& fst_Url)
{
    int32 n_ret = -1;
    if (PixUIWidget().IsValid())
    {
        n_ret = PixUIWidget()->OpenPageFromUrl(fst_Url);
    }
    else
    {
        PxLog_Error(" UPixUIViewPortWidget::LoadPXViewFromUrl Error,Called after the Event of Construct or make sure root panel is CanvasPanel");
    }
    return n_ret;
}


int32 UPixUIViewPortWidget::LoadPXViewFromData(TArray<uint8>& arry_Data,const FString& fstr_BasePath)
{
    int32 n_ret = -1;
    if (PixUIWidget().IsValid())
    {
        n_ret = PixUIWidget()->OpenPageFromData(arry_Data, fstr_BasePath);
    }
    else
    {
        PxLog_Error(" UPixUIViewPortWidget::LoadPXViewFromData Error,Called after the Event of Construct or make sure root panel is CanvasPanel");
    }
    return n_ret;
}


int32 UPixUIViewPortWidget::LoadPXViewFromGameAssetPath(const FString& fstr_FilePath)
{
    int32 n_ret = -1;
    if (PixUIWidget().IsValid())
    {
        PixUIWidget()->OpenPageFromGameAssetPath(fstr_FilePath);
    }
    else
    {
        PxLog_Error(" UPixUIViewPortWidget::LoadPXViewFromGameAssetPath Error,Called after the Event of Construct or make sure root panel is CanvasPanel");
    }
    return n_ret;
}


void UPixUIViewPortWidget::PostPxMessage(const FString& fstr_Message)
{
    if (PixUIWidget().IsValid())
    {
        PixUIWidget()->PostPxMessage(fstr_Message);
    }
    else
    {
        PxLog_Error(" UPixUIViewPortWidget::PostMessage Error,Called after the Event of Construct or make sure root panel is CanvasPanel");
    }
}


void UPixUIViewPortWidget::Close()
{
    if (PixUIWidget().IsValid())
    {
        PixUIWidget()->ClosePage();
    }
    else
    {
        PxLog_Error(" UPixUIViewPortWidget::Close Error,Called after the Event of Construct or make sure root panel is CanvasPanel");
    }
}


int UPixUIViewPortWidget::OnPixuiOpenDelegate(const FString& fstr_Url, const FString& fstr_Name, const FString& fstr_Features, bool b_Replace)
{
    int b_Ret = 0;
    if (pixuiWinOpenDelegate.IsBound())
    {
        b_Ret = pixuiWinOpenDelegate.Execute(fstr_Url, fstr_Name, fstr_Features, b_Replace);
    }
    return b_Ret;
}


bool UPixUIViewPortWidget::OnPixuiConfirmDelegate(const FString& fstr_ConfirmMsg)
{
    bool b_Ret = false;
    if (pixuiWinConfirmDelegate.IsBound())
    {
        b_Ret = pixuiWinConfirmDelegate.Execute(fstr_ConfirmMsg);
    }
    return b_Ret;
}


FString UPixUIViewPortWidget::OnPixuiPromptDelegate(const FString& fstr_Tip, const FString& fstr_Default)
{
    FString fstr_Ret;
    if (pixuiWinConfirmDelegate.IsBound())
    {
        fstr_Ret = pixuiWinPrompDelegate.Execute(fstr_Tip, fstr_Default);
    }
    return fstr_Ret;
}