/**************************************************

**** @file:     PixUIWidget.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/11/01

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixUIWidget.h"

#include "UnrealEngine.h"
#include "CoreUObject.h"
#include "Misc/CoreDelegates.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#include "Engine/GameViewportClient.h"
#endif //WITH_EDITOR


#include "UMG.h"
#include "UnrealEngine.h"
#include "CoreUObject.h"
#include "Misc/CoreDelegates.h"

#include "PixUIBPLibrary.h"

#include "PixUIInput.h"
#include "PixImpMgr.h"
#include "PixUILibMgr.h"
#include "PixUILog.h"
#include "PixUtil.h"


#include "PxSubCtrlWidget.h"
#include "PxSubLayerWidget.h"

#include "PixUIProfiler/PxpResCount.h"

#include "PixImp/PixImpSlot.h"

#include "PixImp/PixImpImg.h"

#include "PixUIDrawItem/PixDrawItem.h"
#include "PixUIDrawItem/PixDrawItemDrawBorder.h"
#include "PixUIDrawItem/PixDrawItemDrawImage.h"
#include "PixUIDrawItem/PixDrawItemDrawLine.h"
#include "PixUIDrawItem/PixDrawItemDrawRect.h"
#include "PixUIDrawItem/PixDrawItemDrawText.h"
#include "PixUIDrawItem/PixDrawItemFillRect.h"
#include "PixUIDrawItem/PixDrawItemPopClip.h"
#include "PixUIDrawItem/PixDrawItemPushClip.h"
#include "PixUIDrawItem/PixDrawItemDrawSlot.h"

#if DF_PIXUI_PROFILER
#include "PixUIProfiler/PxpTickCount.h"
#endif //DF_PIXUI_PROFILER

#include <string>

#define LOCTEXT_NAMESPACE "PIXUI"  //UE4 engine macro

//construct
UPixUIWidget::UPixUIWidget(const FObjectInitializer& ObjectInitializer)
	:UCanvasPanel(ObjectInitializer)
{
	if (PixUtil::IsGamePlay())
	{
		//Add only in play game
		UPixUIWidget::AddPixUIWidget(this);
	}

	mUnVirtualClipCount = 0;
	mIntPxViewId = 0;

	mBeAutoTransForm = false;
	mIntCurrentZorder = 0;

	//default variable
	bIsVariable = true;
	//Visibility = ESlateVisibility::Visible;
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixUIRes UPixUIWidget Construct Create total count:%d", ++ResItemCount::PixWidgetCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}

#if WITH_EDITOR
const FText UPixUIWidget::GetPaletteCategory()
{
	return LOCTEXT("PixUI", "PixUI");
}
#endif //WITH_EDITOR


TSharedRef<SWidget> UPixUIWidget::RebuildWidget()
{
	auto sptrRoot = Super::RebuildWidget();

	//add ctrl widget
	CreatePxView();

	UWorld* World = PixUtil::GameWorld();

	if (World)
	{
		//add root back
		mPtrRootLayerWidget = NewObject<UPxSubLayerWidget>();
		AddSubWidget(mPtrRootLayerWidget);
		mPtrRootLayerWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		mPtrRootLayerWidget->SetWidgetParent(this);
		mPtrRootLayerWidget->SetRootLayer(true);
		UCanvasPanelSlot* p_SlotPanle = UWidgetLayoutLibrary::SlotAsCanvasSlot(mPtrRootLayerWidget.Get());
		if (p_SlotPanle)
		{
			p_SlotPanle->SetZOrder(0);
		}

		mPtrCtrlWidget = NewObject<UPxSubCtrlWidget>();
		AddSubWidget(mPtrCtrlWidget);
		mPtrCtrlWidget->SetVisibility(ESlateVisibility::Visible);
		mPtrCtrlWidget->SetWidgetParent(this);

		p_SlotPanle = UWidgetLayoutLibrary::SlotAsCanvasSlot(mPtrCtrlWidget.Get());
		if (p_SlotPanle)
		{
			p_SlotPanle->SetZOrder(1);
		}
	}
	return sptrRoot;
}


void UPixUIWidget::ReleaseSlateResources(bool beReleaseChildren)
{
	//clear draw item
	ClearDrawItem();
	FreeDrawItemPools();

	//clear
	Super::ReleaseSlateResources(beReleaseChildren);

	DestroyPxView();

	//all pixui windows closed...
	if (PixUIWidgetTotalCount() < 1)
	{
		PixImpMgr::PixImpClear();
	}

	//unbound delegate
	OnCloseDelegate.Clear();
	OnDestroyDelegate.Clear();

	pixuiOnLoadedDelegate.Clear();
	pixuiOnInternalErrorDelegate.Clear();
	pixuiWinOpenDelegate.Clear();
	pixuiWinCloseDelegate.Clear();
	pixuiWinAlertDelegate.Clear();
	pixuiWinConfirmDelegate.Clear();
	pixuiWinPrompDelegate.Clear();
	pixuiWinTransformDelegate.Clear();
	pixuiWinMessageDelegate.Clear();

	pixuiWin_app_foreground_delegate.Clear();
	pixuiWin_app_background_delegate.Clear();

	FScopeLock ScopeLock(&mFcsEvent);
	if (mArrayEvent.Num() > 0)
	{
		PxLog_Warning("UPixUIWidget::ReleaseSlateResources will be empty window event but There are still some events here num:%d", mArrayEvent.Num());
	}
	mArrayEvent.Empty();
}


void UPixUIWidget::BeginDestroy()
{
	Super::BeginDestroy();

	if (PixUtil::IsGamePlay())
	{
		//Remove in play game
		UPixUIWidget::RemovePixUIWidget(this);
	}

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixUIRes UPixUIWidget BeginDestroy~ Destroy total count:%d", --ResItemCount::PixWidgetCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}

int32 UPixUIWidget::OpenPageFromUrl(const FString& fstrUrl)
{
	int32 n_ret = -1;
	if (IsPxViewValid() && !fstrUrl.IsEmpty())
	{
		n_ret = px_plugin::pxViewLoadPageFromUrl(PxViewId(), TCHAR_TO_UTF8(*fstrUrl.Replace(TEXT("\\"), TEXT("/"))));
	}
	else
	{
		if (fstrUrl.IsEmpty())
		{
			PxLog_Error(" UPixUIWidget::OpenPageFromUrl url empty");
		}
		else
		{
			PxLog_Error(" UPixUIWidget::OpenPageFromUrl SPixPaintWidget inValid empty; make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
		}
	}
	return n_ret;
}


int32 UPixUIWidget::OpenPageFromData(UPARAM(ref) TArray<uint8>& arry_Data, const FString& fstr_BasePath)
{
	int32 n_ret = -1;
	if (IsPxViewValid() && !fstr_BasePath.IsEmpty() && arry_Data.Num() > 0)
	{
		n_ret = px_plugin::pxViewLoadPageFromData(PxViewId(), arry_Data.GetData(), arry_Data.Num(), TCHAR_TO_UTF8(*fstr_BasePath));
	}
	else
	{
		if (fstr_BasePath.IsEmpty() || arry_Data.Num() <= 0)
		{
			PxLog_Error(" UPixUIWidget::OpenPageFromData base path empty  data number:%d", arry_Data.Num());
		}
		else
		{
			PxLog_Error(" UPixUIWidget:OpenPageFromData SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called  or multy page do not support");
		}
	}
	return n_ret;
}


int32 UPixUIWidget::OpenPageFromGameAssetPath(const FString& fstr_FilePath)
{
	int32 n_ret = -1;
	if (IsPxViewValid() && !fstr_FilePath.IsEmpty())
	{
		FString fstr_game_file_path = FPaths::ProjectContentDir() + fstr_FilePath;

		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*fstr_game_file_path))
		{
			n_ret = -2;
			PxLog_Error("UPixUIWidget::OpenPageFromGameFile error can not found file:%s", TCHAR_TO_UTF8(*fstr_game_file_path));
			onLoadComplete(TCHAR_TO_UTF8(*fstr_FilePath), -1);
			return n_ret;
		}

		// Load the compressed byte data from the file
		TArray<uint8> array_FileData;
		if (!FFileHelper::LoadFileToArray(array_FileData, *fstr_game_file_path))
		{
			n_ret = -3;
			PxLog_Error("UPixUIWidget::OpenPageFromGameFile Failed to load file: %s", TCHAR_TO_UTF8(*fstr_game_file_path));
			onLoadComplete(TCHAR_TO_UTF8(*fstr_FilePath), -2);
			return n_ret;
		}

		//open page from data
		n_ret = OpenPageFromData(array_FileData, fstr_game_file_path);
		onLoadComplete(TCHAR_TO_UTF8(*fstr_FilePath), -3);
	}
	else
	{
		if (fstr_FilePath.IsEmpty())
		{
			PxLog_Error(" UPixUIWidget::OpenPageFromGameAssetPath file path empty");
		}
		else
		{
			PxLog_Error(" UPixUIWidget::OpenPageFromGameAssetPath SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
		}
	}
	return n_ret;
}


void UPixUIWidget::PostPxMessage(const FString& fstr_Message)
{
	if (IsPxViewValid())
	{
		px_plugin::pxViewPostMessage(PxViewId(), TCHAR_TO_UTF8(*fstr_Message), 0);
	}
	else
	{
		PxLog_Error(" UPixUIWidget::PostMessage SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
	}
}


void UPixUIWidget::ClosePage()
{
	if (IsPxViewValid())
	{
		px_plugin::pxViewClose(PxViewId());

		if (OnCloseDelegate.IsBound())
		{
			OnCloseDelegate.Broadcast();
		}
	}
	else
	{
		PxLog_Error(" UPixUIWidget::ClosePage SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
	}

	//GEngine GC
	PixUtil::EngineGC(true);
}


void UPixUIWidget::DestroyPage()
{
	ClosePage();
	if (IsPxViewValid())
	{
		px_plugin::pxViewDestroy(PxViewId());

		mIntPxViewId = 0;
	}
	else
	{
		PxLog_Error(" UPixUIWidget::DestroyPage SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
	}

	//GEngine GC
	PixUtil::EngineGC(true);
}


void UPixUIWidget::SetAutoTransform(bool b_auto_transform)
{
	mBeAutoTransForm = b_auto_transform;
}


int32 UPixUIWidget::GetPxWinId()
{
	return mIntPxViewId;
}


void UPixUIWidget::CreateScriptGlobal(const FString& name)
{
	if (IsPxViewValid())
	{
		//px_plugin::pxViewGetScriptVM(PxViewId(), TCHAR_TO_UTF8(*name));
		PxLog_Error(" UPixUIWidget::CreateScriptGlobal not support");
	}
	else
	{
		PxLog_Error(" UPixUIWidget::CreateScriptGlobal SPixPaintWidget inValid");
	}
}


void UPixUIWidget::SetScriptGlobalNumber(const FString& name, const FString& key, float num)
{
	if (IsPxViewValid())
	{
		//PX_Plugin::PX_ViewSetScriptGlobalNumber(PxViewId(), TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*key), num);
		PxLog_Error(" UPixUIWidget::SetScriptGlobalNumber not support");
	}
	else
	{
		PxLog_Error(" UPixUIWidget::SetScriptGlobalNumber SPixPaintWidget inValid");
	}
}


void UPixUIWidget::SetScriptGlobalString(const FString& name, const FString& key, const FString& str)
{
	if (IsPxViewValid())
	{
		//PX_Plugin::PX_ViewSetScriptGlobalString(PxViewId(), TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*str));
		PxLog_Error(" UPixUIWidget::SetScriptGlobalString not support");
	}
	else
	{
		PxLog_Error(" UPixUIWidget::SetScriptGlobalString SPixPaintWidget inValid");
	}
}


void UPixUIWidget::SetScriptGlobalBoolean(const FString& name, const FString& key, bool v)
{
	if (IsPxViewValid())
	{
		//PX_Plugin::PX_ViewSetScriptGlobalBoolean(PxViewId(), TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*key), v);
		PxLog_Error(" UPixUIWidget::SetScriptGlobalBoolean not support");
	}
	else
	{
		PxLog_Error(" UPixUIWidget::SetScriptGlobalBoolean SPixPaintWidget inValid");
	}
}


float UPixUIWidget::GetScriptGlobalNumber(const FString& name, const FString& key)
{
	if (IsPxViewValid())
	{
		//return PX_Plugin::PX_ViewGetScriptGlobalNumber(PxViewId(), TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*key));
		PxLog_Error(" UPixUIWidget::GetScriptGlobalNumber not support");
		
	}
	else
	{
		PxLog_Error(" UPixUIWidget::GetScriptGlobalNumber SPixPaintWidget inValid");
	}
	return 0.0f;
}


FString UPixUIWidget::GetScriptGlobalString(const FString& name, const FString& key)
{
	if (IsPxViewValid())
	{
		//return PX_Plugin::PX_ViewGetScriptGlobalString(PxViewId(), TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*key));
		PxLog_Error(" UPixUIWidget::GetScriptGlobalString not support");
	}
	else
	{
		PxLog_Error(" UPixUIWidget::GetScriptGlobalString SPixPaintWidget inValid");
	}
	return "";
}


bool UPixUIWidget::GetScriptGlobalBoolean(const FString& name, const FString& key)
{
	if (IsPxViewValid())
	{
		//return PX_Plugin::PX_ViewGetScriptGlobalBoolean(PxViewId(), TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*key));
		PxLog_Error(" UPixUIWidget::GetScriptGlobalBoolean not support");
	}
	else
	{
		PxLog_Error(" UPixUIWidget::GetScriptGlobalBoolean SPixPaintWidget inValid");
	}
	return false;
}


UObject* UPixUIWidget::GetSlotObjectByTagId(const FString& slotTagId)
{
	UObject* slotObject = nullptr;

	TSharedPtr<PixSlot> ptrSlot = PixImpSlot::FindPixSlotByWinIdTagId(mIntPxViewId, slotTagId);
	if (ptrSlot.IsValid())
	{
		slotObject = ptrSlot->GetInnerObject();
	}

	return slotObject;
}

//push event to widget mArrayEvent
#define DF_PUSH_PX_EVENT(_type,_param1,_param2,_msg)    ST_PX_EVENT stTempEvent;	\
    stTempEvent.n_Type = (int)_type;												\
    stTempEvent.n_Param1 = _param1;													\
    stTempEvent.n_Param2 = _param2;													\
    stTempEvent.fstr_Msg = _msg;													\
    FScopeLock ScopeLock(&mFcsEvent);												\
    mArrayEvent.Push(stTempEvent);


void UPixUIWidget::onLoadComplete(const char* pszUrl, const int nErrorCode)
{
	if (IsInGameThread())
	{
		if (pixuiOnLoadedDelegate.IsBound())
		{
			pixuiOnLoadedDelegate.Broadcast(UTF8_TO_TCHAR(pszUrl), nErrorCode);
		}
	}
	else
	{
		TWeakObjectPtr<UPixUIWidget> wptr_this = this;
		//call in game thread
		AsyncTask(ENamedThreads::GameThread, [=]()
			{
				if (wptr_this.IsValid() && wptr_this->pixuiOnLoadedDelegate.IsBound())
				{
					wptr_this->pixuiOnLoadedDelegate.Broadcast(UTF8_TO_TCHAR(pszUrl), nErrorCode);
				}
			});
	}
}

/*
void UPixUIWidget::OnScriptStateInit()
{
	if (IsInGameThread())
	{
		if (pixuiOnScriptStateInitDelegate.IsBound())
		{
			pixuiOnScriptStateInitDelegate.Broadcast();
		}
	}
	else
	{
		TWeakObjectPtr<UPixUIWidget> wptr_this = this;
		//call in game thread
		AsyncTask(ENamedThreads::GameThread, [=]() {
			if (wptr_this.IsValid() && wptr_this->pixuiOnScriptStateInitDelegate.IsBound())
			{
				wptr_this->pixuiOnScriptStateInitDelegate.Broadcast();
			}
		});
	}
}
*/

void UPixUIWidget::onInternalError(int error, const char* msg)
{
	if (IsInGameThread())
	{
		if (pixuiOnInternalErrorDelegate.IsBound())
		{
			pixuiOnInternalErrorDelegate.Broadcast(error, UTF8_TO_TCHAR(msg ? msg : ""));
		}
	}
	else
	{
		TWeakObjectPtr<UPixUIWidget> wptr_this = this;
		//call in game thread
		AsyncTask(ENamedThreads::GameThread, [=]()
			{
				if (wptr_this.IsValid() && wptr_this->pixuiOnInternalErrorDelegate.IsBound())
				{
					wptr_this->pixuiOnInternalErrorDelegate.Broadcast(error, UTF8_TO_TCHAR(msg ? msg : ""));
				}
			});
	}
}


pixui::uint_ptr UPixUIWidget::onOpen(const char* pszUrl, const char* pszName, const char* pszFeatures, bool bReplace, void* pContext, pixui::PFunWindowOpenCallBack callback)
{
	if (IsInGameThread())
	{
		//game thread need sync call
		FString fstr_url = UTF8_TO_TCHAR(pszUrl ? pszUrl : "");
		FString fstr_name = UTF8_TO_TCHAR(pszName ? pszName : "");
		FString fstr_features = UTF8_TO_TCHAR(pszFeatures ? pszFeatures : "");
		//call in game thread
		TWeakObjectPtr<UPixUIWidget> wptr_this = this;
		if (wptr_this.IsValid() && wptr_this->pixuiWinOpenDelegate.IsBound())
		{
			wptr_this->pixuiWinOpenDelegate.Execute(fstr_url, fstr_name, fstr_features, bReplace);
		}
		else
		{
			PxLog_Warning(" UPixUIWidget::onOpen pixuiOpenDelegate is not bound or UPixUIWidget inValid");
		}
	}
	else
	{
		PxLog_Error(" UPixUIWidget::onOpen Called Not In Gamethread");
	}
	return nullptr;
}


void UPixUIWidget::onClose()
{
	DF_PUSH_PX_EVENT(ST_PX_EVENT::n_type_close, 0, 0, TEXT(""));
}


void UPixUIWidget::onAlert(const char* psz_Text)
{
	DF_PUSH_PX_EVENT(ST_PX_EVENT::n_type_alert, 0, 0, UTF8_TO_TCHAR(psz_Text));
}


bool UPixUIWidget::onConfirm(const char* psz_Message)
{
	bool b_Ret = false;
	if (IsInGameThread())
	{
		//game thread need sync call
		if (pixuiWinConfirmDelegate.IsBound())
		{
			b_Ret = pixuiWinConfirmDelegate.Execute(UTF8_TO_TCHAR(psz_Message));
		}
		else
		{
			PxLog_Error(" UPixUIWidget::OnConfirm pixuiConfirmDelegate is not bound");
		}
	}
	else
	{
		PxLog_Error(" UPixUIWidget::OnConfirm Called Not In Gamethread");
	}
	return b_Ret;
}


const char* UPixUIWidget::onPrompt(const char* psz_Text, const char* psz_DefaultText)
{
	if (IsInGameThread())
	{
		mFstrPromptRet.Empty();
		if (pixuiWinPrompDelegate.IsBound())
		{
			mFstrPromptRet = pixuiWinPrompDelegate.Execute(UTF8_TO_TCHAR(psz_Text), UTF8_TO_TCHAR(psz_DefaultText));
		}
		else
		{
			PxLog_Error(" UPixUIWidget::OnPrompt pixuiPrompDelegate PrompDelegate was not bound");
		}
		static std::string str_prompt_g;
		str_prompt_g = TCHAR_TO_UTF8(*mFstrPromptRet);

		//return TCHAR_TO_UTF8(*mFstrPromptRet) was not safe
		return str_prompt_g.c_str();
	}
	else
	{
		PxLog_Error(" UPixUIWidget::OnPrompt Called Not In Gamethread");
	}
	return "";
}


void UPixUIWidget::onMoveBy(const int n_XposMoveBy, const int n_YposMoveBy)
{
	DF_PUSH_PX_EVENT(EPXViewEvent::em_px_event_moveby, n_XposMoveBy, n_YposMoveBy, TEXT(""));
}


void UPixUIWidget::onMoveTo(const int n_XposMoveTo, const int n_YposMoveTo)
{
	DF_PUSH_PX_EVENT(EPXViewEvent::em_px_event_moveto, n_XposMoveTo, n_YposMoveTo, TEXT(""));
}


void UPixUIWidget::onResizeBy(const int n_OffsetWidth, const  int n_OffsetHeight)
{
	DF_PUSH_PX_EVENT(EPXViewEvent::em_px_event_resizeby, n_OffsetWidth, n_OffsetHeight, TEXT(""));
}


void UPixUIWidget::onResizeTo(const int n_NewWidth, const int n_NewHeight)
{
	DF_PUSH_PX_EVENT(EPXViewEvent::em_px_event_resizeto, n_NewWidth, n_NewHeight, TEXT(""));
}


void UPixUIWidget::onScrollBy(const int n_OffsetXpos, const int n_OffsetYpos)
{
	DF_PUSH_PX_EVENT(EPXViewEvent::em_px_event_scrollby, n_OffsetXpos, n_OffsetYpos, TEXT(""));
}


void UPixUIWidget::onScrollTo(const int n_NewXpos, const int n_NewYpos)
{
	DF_PUSH_PX_EVENT(EPXViewEvent::em_px_event_scrollto, n_NewXpos, n_NewYpos, TEXT(""));
}


int UPixUIWidget::getOpener()
{
	return 0;
}

pixui::uint32 UPixUIWidget::getId()
{
	return mIntPxViewId;
}

void UPixUIWidget::setWindowPass(bool bePass)
{
	if (IsPxViewValid())
	{
		mPtrCtrlWidget->SetVisibility(bePass ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Visible);
	}
}


void UPixUIWidget::setWindowPriority(int n_priority)
{
	UCanvasPanelSlot* p_panel_slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	if (p_panel_slot)
		p_panel_slot->SetZOrder(n_priority);
}

void UPixUIWidget::onMessage(const char* psz_Message)
{
	DF_PUSH_PX_EVENT(ST_PX_EVENT::n_type_message, 0, 0, UTF8_TO_TCHAR(psz_Message));
}


bool UPixUIWidget::onActivateInput(pixui::EKeyboardType e_KeyboardType, const char* psz_DefaultText, const char* psz_HintText)
{
	EPXKeyboardTypes e_type;
	switch (e_KeyboardType)
	{
	case pixui::em_Keyboard_Number:
		e_type = EPXKeyboardTypes::em_px_key_board_number;
		break;
	case pixui::em_Keyboard_Password:
		e_type = EPXKeyboardTypes::em_px_key_board_password;
		break;
	case pixui::em_Keyboard_Default:
	default:
		e_type = EPXKeyboardTypes::em_px_key_board_default;
		break;
	}

	bool b_ret = UPixUIInput::OnActivateInput(this, e_type, UTF8_TO_TCHAR(psz_DefaultText), UTF8_TO_TCHAR(psz_HintText));
	if (IsPxViewValid())
	{
		mPtrCtrlWidget->SetActiveInput(b_ret);
	}
	return b_ret;
}


bool UPixUIWidget::onDeativateInput()
{
	bool b_ret = UPixUIInput::OnDeativateInput(this);
	if (IsPxViewValid())
	{
		mPtrCtrlWidget->SetActiveInput(b_ret);
	}
	return b_ret;
}

const char* UPixUIWidget::getClipboardText()
{
	return "";
}

void UPixUIWidget::setClipboardText(const char* text)
{

}
//~ End IPluginWindow Interface



/*
bool UPixUIWidget::QueryPixelFormatSupport(pixui::EPixelFormat emPixelFormat)
{
	if (GPixelFormats[PixUtil::PixUIPixelFormatToUEPixelFormat(emPixelFormat)].Supported)
	{
		return true;
	}
	return false;
}
*/

void UPixUIWidget::queryCapability(pixui::Capability* cap)
{
	if (cap)
	{
		cap->supportRetainFrame = true;
		cap->supportDrawTextWithLetterSpace = false;
	}
}

pixui::uint_ptr UPixUIWidget::getContextPtr()
{
	if (IsPxViewValid())
	{
		return (pixui::uint_ptr)px_plugin::pxViewGetContext(PxViewId());
	}
	PxLog_Error(" getContextPtr PxViewId() inValid");
	return nullptr;
}


void UPixUIWidget::onPrePaint()
{
	mIntCurrentZorder = 0;
	ClearDrawItem();
	ResetDrawParams();

	for (auto slotWidget : mArraySlotLayer)
	{
		slotWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	mPtrCurrentLayerWidget = mPtrRootLayerWidget;
	mPtrLastSlotWidget = nullptr;
}


void UPixUIWidget::onEndPaint(const int nPaintCode)
{
	if (mArrayClipType.Num() > 0)
	{
		PxLog_Error("UPixUIWidget::OnEndPaint error clip Number Mismatch :%d", mArrayClipType.Num());
		mArrayClipType.Empty();
	}

	UCanvasPanelSlot* pPanleCtrl = UWidgetLayoutLibrary::SlotAsCanvasSlot(mPtrCtrlWidget.Get());
	if (pPanleCtrl)
	{
		pPanleCtrl->SetZOrder(mIntCurrentZorder);
	}

	if (mPtrLastSlotWidget.IsValid())
	{
		UCanvasPanelSlot* pPanleSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(mPtrLastSlotWidget.Get());
		if (pPanleSlot)
		{
			pPanleSlot->SetZOrder(mIntCurrentZorder + 1);
		}
	}
}


pixui::uint_ptr UPixUIWidget::createSlot(const char* src)
{
	return PixImpMgr::Get().CreateSlot(src, PxViewId(), "");
}

void UPixUIWidget::deleteSlot(pixui::uint_ptr hSlot)
{
	PixImpMgr::Get().DeleteSlot(hSlot);
}

void UPixUIWidget::drawSlot(pixui::uint32 id, pixui::uint_ptr hSlot, const pixui::matrix& mat, const pixui::position& rect)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewId(), e_px_draw_item_draw_slot);
#endif //DF_PIXUI_PROFILER

	if (mUnVirtualClipCount <= 0)
	{
		//try widget
		TWeakPtr<PixSlot> weakSlot = PixImpSlot::FindPixSlotByHandle((void*)hSlot);
		if (weakSlot.IsValid())
		{
			mPtrLastSlotWidget = weakSlot.Pin().Get()->GetWidget();
			if (mPtrLastSlotWidget.IsValid())
			{
				mPtrLastSlotWidget->SetVisibility(ESlateVisibility::Visible);
				UCanvasPanelSlot* pPanleSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(mPtrLastSlotWidget.Get());
				if (pPanleSlot)
				{
					FGeometry fGeometry = mPtrLastSlotWidget->GetCachedGeometry();
					pPanleSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
					pPanleSlot->SetOffsets(FMargin(0.0f, 0.0f, rect.width, rect.height));
					pPanleSlot->SetZOrder(mIntCurrentZorder++);
					//pPanleSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				}

				// 				if (0)
				// 				{
				// 					FMatrix2x2 mtrix = FMatrix2x2(mat.a(), mat.b(), mat.c(), mat.d());
				// 					auto angle = mtrix.GetRotationAngle();
				// 					FWidgetTransform widgetTransForm(FVector2D::ZeroVector, mtrix.GetScale().GetVector(), FVector2D::ZeroVector, angle);
				// 					mPtrLastSlotWidget->SetRenderTransform(widgetTransForm);
				// 				}
				// 				else
				{
					pixui::matrix tmpMat;
					if (PX_LOFAT_EQUAL_ZERO(rect.x) && PX_LOFAT_EQUAL_ZERO(rect.y))
					{
						tmpMat = mat;
					}
					else
					{
						tmpMat.initTranslate(rect.x, rect.y);
						tmpMat = mat * tmpMat;
					}
					FSlateRenderTransform slate_renderTransform2D = FSlateRenderTransform(FMatrix2x2(tmpMat[0], tmpMat[1], tmpMat[2], tmpMat[3]), FVector2D(tmpMat[4], tmpMat[5]));

					TSharedPtr<SWidget> SafeWidget = mPtrLastSlotWidget->GetCachedWidget();
					if (SafeWidget.IsValid())
					{
						SafeWidget->SetRenderTransformPivot(FVector2D(0.0f, 0.0f));
						SafeWidget->SetRenderTransform(slate_renderTransform2D);
					}
				}
				mPtrCurrentLayerWidget = nullptr;
			}
			else
			{
				//try brush
				auto p_item = DrawItemFromPools(e_px_draw_item_draw_slot); //PixDrawItem::NewDrawItemFromPools(e_px_draw_item_draw_slot);
				if (p_item)
				{
					TArray<void*> arrayParams;
					arrayParams.Add((void*)(hSlot));
					arrayParams.Add((void*)(&mat));
					arrayParams.Add((void*)(&rect));
					p_item->UpdateParams(arrayParams);

					GetCurSubLayer()->PushDrawItem(p_item);
				}
				mPtrLastSlotWidget = nullptr;
			}
		}
		else
		{
			//not found slot
		}
	}
}

void UPixUIWidget::registerFont(pixui::IHostDraw::RegisterFontArg& arg)
{
	PixImpMgr::Get().RegisterFont(arg.fontSrc, arg.fontFamily, arg.fontWeight, arg.fontStyle, arg.notifyCtx, arg.notify);
}

pixui::uint_ptr UPixUIWidget::createFont(
	const char* pszFontName,
	const int nSize,
	const int nWeight,
	const unsigned int unDecoration,
	const pixui::font_style emItalic,
	pixui::FontMetrics* pStFontMetrics)
{
	return PixImpMgr::Get().CreateFont(pszFontName, nSize, nWeight, unDecoration, emItalic, pStFontMetrics);
}

void UPixUIWidget::delFont(pixui::uint_ptr hFont)
{
	PixImpMgr::Get().DeleteFont(hFont);
}

float UPixUIWidget::textWidth(const char* pszText, pixui::uint_ptr hFont)
{
	return mPtrRootLayerWidget->TextWidth(pszText, hFont);
}

float UPixUIWidget::charWidth(uint32_t unCharCode, pixui::uint_ptr hFont)
{

	char szText[8] = { 0 };

	PixUtil::UTF32toUTF8(unCharCode, (uint8*)szText);
	return textWidth(szText, hFont);
}

int UPixUIWidget::getDefaultFontSize()
{
	return PixImpFont::GetDefaultFontSize();
}

const char* UPixUIWidget::getDefaultFontName()
{
	return PixImpFont::GetDefaultFont();
}

int UPixUIWidget::ptToPix(const int nPt)
{
	return PixUtil::PtToPix(nPt);
}

void UPixUIWidget::setCursor(const char* pszCursor)
{
	//
}


pixui::uint_ptr UPixUIWidget::createImage(const char* pszName)
{
	return PixImpMgr::Get().CreateImage(pszName);
}

bool UPixUIWidget::initImageByRawData(pixui::uint_ptr hImage, const int nWidth, const int nHeight, const int nImageFlag, const pixui::EPixelFormat emPixelFormat, const pixui::uint8* pRawData, size_t nDataSize)
{
	return PixImpMgr::Get().InitImageByRawData(hImage, nWidth, nHeight, nImageFlag, emPixelFormat, pRawData, nDataSize);
}

void UPixUIWidget::updateImageByRawData(pixui::uint_ptr hImage, const pixui::EPixelFormat emPixel, const pixui::uint8* pRawData, size_t nDataSize)
{
	return PixImpMgr::Get().updateImageByRawData(hImage, emPixel, pRawData, nDataSize);
}

void UPixUIWidget::getImageSize(pixui::uint_ptr hImage, pixui::size& sz)
{
	PixImpMgr::Get().GetImageSize(hImage, sz);
}

bool UPixUIWidget::isExternalImage(pixui::uint_ptr hImage)
{
	return PixImpMgr::Get().IsExternalImage(hImage);
}

bool UPixUIWidget::delImage(pixui::uint_ptr hImage)
{
	return PixImpMgr::Get().DeleteImage(hImage);
}

void UPixUIWidget::pushClip(pixui::uint32 id, const pixui::ClipRegion& polygon)
{
	pushClip(id, polygon.getMatrix(), polygon.getPosition());
}


void UPixUIWidget::pushClip(pixui::uint32 id, const pixui::matrix& mat, const pixui::position& rcClip)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewId(), e_px_draw_item_push_clip);
#endif //DF_PIXUI_PROFILER

	auto p_item = DrawItemFromPools(e_px_draw_item_push_clip); //PixDrawItem::NewDrawItemFromPools(e_px_draw_item_push_clip);
	if (p_item)
	{
		TArray<void*> arrayParams;
		arrayParams.Add((void*)(&mat));
		arrayParams.Add((void*)(&rcClip));
		p_item->UpdateParams(arrayParams);

		GetCurSubLayer()->PushDrawItem(p_item);

		//0 valid ,1 invalid
		auto unClipType = ((PixDrawItemPushClip*)(p_item))->CheckClipType(GetCurSubLayer()->GetCachedGeometry());

		mArrayClipType.Add(unClipType);
		if (unClipType == 1)
		{
			mUnVirtualClipCount++;
		}
	}
}


void UPixUIWidget::popClip()
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewId(), e_px_draw_item_pop_clip);
#endif //DF_PIXUI_PROFILER

	auto p_item = DrawItemFromPools(e_px_draw_item_pop_clip); //PixDrawItem::NewDrawItemFromPools(e_px_draw_item_pop_clip);
	if (p_item)
	{
		auto unClipType = mArrayClipType.Pop();

		TArray<void*> arrayParams;
		bool bValid = unClipType == 0;
		arrayParams.Add((void*)&bValid);
		p_item->UpdateParams(arrayParams);
		GetCurSubLayer()->PushDrawItem(p_item);
		if (unClipType == 1)
		{
			mUnVirtualClipCount--;
		}
	}
}

void UPixUIWidget::pushGroup(pixui::uint32 id, const pixui::matrix& mat, const pixui::size& size)
{
	//
}

void UPixUIWidget::popGroup()
{
	//
}

void UPixUIWidget::nextRenderLayer()
{
	//
}

int UPixUIWidget::getCurrentRenderLayer()
{
	//
	return mUlCurDrawBaseLayer;
}

void UPixUIWidget::fillBackgroundRect(
	pixui::uint32 id,
	const pixui::matrix& mat,
	const pixui::position& rcDrawPos,
	const pixui::color& stColor,
	const pixui::BorderRadiuses& radius)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewId(), e_px_draw_item_fill_rect);
#endif //DF_PIXUI_PROFILER

	if (mUnVirtualClipCount <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_fill_rect); //PixDrawItem::NewDrawItemFromPools(e_px_draw_item_fill_rect);
		if (p_item)
		{
			TArray<void*> arrayParams;
			arrayParams.Add((void*)(&mat));
			arrayParams.Add((void*)(&rcDrawPos));
			arrayParams.Add((void*)(&stColor));
			arrayParams.Add((void*)(&radius));
			p_item->UpdateParams(arrayParams);

			GetCurSubLayer()->PushDrawItem(p_item);
		}
	}
	mPtrLastSlotWidget = nullptr;
}

void UPixUIWidget::drawBackgroundImage(
	pixui::uint32 id,
	pixui::uint_ptr pImage,
	const pixui::matrix& mat,
	const pixui::position& rcDraw,
	const pixui::position& rcImageSrc,
	const pixui::BackgroundRepeat emRepeat,
	const pixui::BackgroundAttachment emAttachment,
	const pixui::ImageSlice& sliceImage,
	const pixui::color& tintColor,
	const pixui::BorderRadiuses& radius)
{
	drawContentImage(id, pImage, mat, rcDraw, rcImageSrc, emRepeat, emAttachment, sliceImage, tintColor, radius);
}

void UPixUIWidget::drawBorderImage(
	pixui::uint32 id,
	pixui::uint_ptr pImage,
	const pixui::matrix& mat,
	const pixui::position& rcDraw,
	const pixui::position& rcImageSrc,
	const pixui::BackgroundRepeat emRepeat,
	const pixui::BackgroundAttachment emAttachment,
	const pixui::ImageSlice& sliceImage,
	const pixui::color& tintColor,
	const pixui::BorderRadiuses& radius)
{
	drawContentImage(id, pImage, mat, rcDraw, rcImageSrc, emRepeat, emAttachment, sliceImage, tintColor, radius);
}

void UPixUIWidget::drawBorderRect(
	pixui::uint32 id,
	const pixui::matrix& mat,
	const pixui::position& stDrawPos,
	const unsigned int nLeftWidth, const pixui::BorderStyle emLeftLineType, const pixui::color& stLeftColor,
	const unsigned int nRightWidth, const pixui::BorderStyle emRightLineType, const pixui::color& stRightColor,
	const unsigned int nTopWidth, const pixui::BorderStyle emTopLineType, const pixui::color& stTopColor,
	const unsigned int nBottomWidth, const pixui::BorderStyle emBottomLineType, const pixui::color& stBottomColor,
	const pixui::BorderRadiuses& radius)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewId(), e_px_draw_item_draw_border);
#endif //DF_PIXUI_PROFILER

	unsigned int nWidths[EPxBoderIndex::e_px_boder_index_count] = {nTopWidth, nBottomWidth, nLeftWidth, nRightWidth};
	pixui::BorderStyle eLineTypes[EPxBoderIndex::e_px_boder_index_count] = {emTopLineType, emBottomLineType, emLeftLineType, emRightLineType};
	pixui::color colors[EPxBoderIndex::e_px_boder_index_count] = {stTopColor, stBottomColor, stLeftColor, stRightColor};

	if (mUnVirtualClipCount <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_border); //PixDrawItem::NewDrawItemFromPools(e_px_draw_item_draw_border);
		if (p_item)
		{
			TArray<void*> arrayParams;
			arrayParams.Add((void*)(&mat));
			arrayParams.Add((void*)(&stDrawPos));
			arrayParams.Add((void*)(nWidths));
			arrayParams.Add((void*)(eLineTypes));
			arrayParams.Add((void*)(colors));
			arrayParams.Add((void*)(&radius));
			p_item->UpdateParams(arrayParams);

			GetCurSubLayer()->PushDrawItem(p_item);
		}
	}
	mPtrLastSlotWidget = nullptr;
}

void UPixUIWidget::drawContentImage(
	pixui::uint32 id,
	pixui::uint_ptr pImage,
	const pixui::matrix& mat,
	const pixui::position& rcDraw,
	const pixui::position& rcImageSrc,
	const pixui::BackgroundRepeat emRepeat,
	const pixui::BackgroundAttachment emAttachment,
	const pixui::ImageSlice& sliceImage,
	const pixui::color& drawColor,
	const pixui::BorderRadiuses& radius)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewId(), e_px_draw_item_draw_image);
#endif //DF_PIXUI_PROFILER

	if (mUnVirtualClipCount <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_image); //PixDrawItem::NewDrawItemFromPools(e_px_draw_item_draw_image);
		if (p_item)
		{
			TArray<void*> arrayParams;
			arrayParams.Add((void*)(pImage));
			arrayParams.Add((void*)(&mat));
			arrayParams.Add((void*)(&rcDraw));
			arrayParams.Add((void*)(&rcImageSrc));
			arrayParams.Add((void*)(&emRepeat));
			arrayParams.Add((void*)(&emAttachment));
			arrayParams.Add((void*)(&sliceImage));
			arrayParams.Add((void*)(&drawColor));
			arrayParams.Add((void*)(&radius));
			p_item->UpdateParams(arrayParams);

			GetCurSubLayer()->PushDrawItem(p_item);
		}
	}
	mPtrLastSlotWidget = nullptr;
}

void UPixUIWidget::drawContentText(
	pixui::uint32 id,
	pixui::uint_ptr hFont,
	const pixui::matrix& mat,
	const char* pszTextDraw,
	const pixui::color& drawColor,
	const pixui::position& rcDraw,
	const float fBlur,
	const float letterSpace)
{
	//PxLog_Trace("DrawText x pos:%f y pos:%f   text:%s                       ", mat[4], mat[5], pszTextDraw);
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewId(), e_px_draw_item_draw_text);
#endif //DF_PIXUI_PROFILER

	if (mUnVirtualClipCount <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_text); //PixDrawItem::NewDrawItemFromPools(e_px_draw_item_draw_text);
		if (p_item)
		{
			TArray<void*> arrayParams;
			arrayParams.Add((void*)(hFont));
			arrayParams.Add((void*)(&mat));
			arrayParams.Add((void*)(pszTextDraw));
			arrayParams.Add((void*)(&drawColor));
			arrayParams.Add((void*)(&rcDraw));
			arrayParams.Add((void*)(&fBlur));
			p_item->UpdateParams(arrayParams);

			GetCurSubLayer()->PushDrawItem(p_item);
		}
	}
	mPtrLastSlotWidget = nullptr;
}

void UPixUIWidget::drawContentLine(
	pixui::uint32 id,
	const pixui::matrix& mat,
	const unsigned int unWidth,
	const pixui::BorderStyle emLineType,
	const pixui::color& tintColor,
	const pixui::point& ptStart,
	const pixui::point& ptEnd)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewId(), e_px_draw_item_draw_line);
#endif //DF_PIXUI_PROFILER

	if (mUnVirtualClipCount <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_line); //PixDrawItem::NewDrawItemFromPools(e_px_draw_item_draw_line);
		if (p_item)
		{
			TArray<void*> arrayParams;
			arrayParams.Add((void*)(&mat));
			arrayParams.Add((void*)(&unWidth));
			arrayParams.Add((void*)(&emLineType));
			arrayParams.Add((void*)(&tintColor));
			arrayParams.Add((void*)(&ptStart));
			arrayParams.Add((void*)(&ptEnd));
			p_item->UpdateParams(arrayParams);

			GetCurSubLayer()->PushDrawItem(p_item);
		}
	}
	mPtrLastSlotWidget = nullptr;
}


TSharedPtr<SWidget> UPixUIWidget::GetSlateWidget()
{
	return TakeWidget();
}


void UPixUIWidget::OnInputText(const FString& fstr_new_input, const bool b_end_input, const bool b_lost_focus, const bool b_replace)
{
	if (IsPxViewValid())
	{
		px_plugin::pxViewKeyboardInput(PxViewId(), TCHAR_TO_UTF8(*fstr_new_input), b_end_input, b_lost_focus, b_replace);
	}
	else
	{
		PxLog_Error(" OnTextInsert PxViewId() inValid");
	}
}

void UPixUIWidget::ShowWidgetInfor()
{
	uint32 un_total_count = 0;
	for (auto i = 0; i < e_px_draw_item_count; i++)
	{
		un_total_count += mArrayDrawItemPools[i].Num();
	}
	PxLog_Log("UPixUIWidget  draw item total count:%d ", un_total_count);
	for (auto i = 0; i < e_px_draw_item_count; i++)
	{
		PxLog_Log("    UPixUIWidget draw item used type:%d count:%d ", i, mUnDrawItemPoolsIndex[i]);
	}

	for (auto i = 0; i < e_px_draw_item_count; i++)
	{
		PxLog_Log("    UPixUIWidget draw item pools type:%d count:%d ", i, mArrayDrawItemPools[i].Num());
	}

	PxLog_Log("    UPixUIWidget slot mArraySlotLayer count:%d ", mArraySlotLayer.Num());

	PxLog_Log("    UPixUIWidget show mArrayLayerWidget count:%d ", mArrayLayerWidget.Num());

	PxLog_Log("    UPixUIWidget hide mArrayFreeLayerWidget count:%d ", mArrayFreeLayerWidget.Num());
}

void UPixUIWidget::AddSlotWidget(TWeakObjectPtr<UWidget> weakWidget)
{
	if (weakWidget.IsValid())
	{
		UCanvasPanelSlot* p_SlotPanle = AddChildToCanvas(weakWidget.Get());
		if (p_SlotPanle)
		{
			p_SlotPanle->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
			p_SlotPanle->SetOffsets(FMargin(0.0f, 0.0f, 100.0f, 100.0f));
			p_SlotPanle->SetZOrder(-1);
		}
		weakWidget->SetVisibility(ESlateVisibility::Hidden);
		mArraySlotLayer.Add(weakWidget);

#if DF_PX_BUILD_NO_SHIPPING
		PxLog_Trace("UPixUIWidget::AddSlotWidget mArraySlotLayer add count:%d", mArraySlotLayer.Num());
#endif //DF_PX_BUILD_NO_SHIPPING
	}
}


void UPixUIWidget::RemoveSlotWidget(TWeakObjectPtr<UWidget> weakWidget)
{
	if (weakWidget.IsValid())
	{
		if (mArraySlotLayer.Find(weakWidget) >= 0)
		{
			weakWidget->RemoveFromParent();
			mArraySlotLayer.Remove(weakWidget);
#if DF_PX_BUILD_NO_SHIPPING
			PxLog_Trace("UPixUIWidget::RemoveSlotWidget mArraySlotLayer remove count:%d", mArraySlotLayer.Num());
#endif //DF_PX_BUILD_NO_SHIPPING
		}
	}
}

void UPixUIWidget::OnAppForeground()
{
	if (pixuiWin_app_foreground_delegate.IsBound())
	{
		pixuiWin_app_foreground_delegate.Broadcast();
	}
}


void UPixUIWidget::OnAppBackground()
{
	if (pixuiWin_app_background_delegate.IsBound())
	{
		pixuiWin_app_background_delegate.Broadcast();
	}
}


void UPixUIWidget::OnTick(float InDeltaTime)
{
	int n_LoopTime = 0;
	int n_Num = 0;

	//Extract up to 10 events each time to prevent infinite loop
	while (IsPxViewValid() && n_LoopTime < 10)
	{
		ST_PX_EVENT stTempEvent;
		{
			FScopeLock ScopeLock(&mFcsEvent);
			n_Num = mArrayEvent.Num();
			if (n_Num > 0)
			{
				stTempEvent = mArrayEvent[0];
				mArrayEvent.RemoveAt(0);
			}
		}
		if (n_Num > 0)
		{
			//broadcast event
			BroadcastEvent(stTempEvent.n_Type, stTempEvent.n_Param1, stTempEvent.n_Param2, stTempEvent.fstr_Msg);
		}
		else
		{
			break;
		}
		n_LoopTime++;
	}
}


void UPixUIWidget::BroadcastEvent(const int n_Event, const int32 n_Param1, const int32 n_Param2, const FString& fstr_Msg)
{
	switch (n_Event)
	{
	case ST_PX_EVENT::n_type_close:
	{
		if (pixuiWinCloseDelegate.IsBound())
		{
			pixuiWinCloseDelegate.Broadcast();
		}
	}
	break;
	case ST_PX_EVENT::n_type_alert:
	{
		if (pixuiWinAlertDelegate.IsBound())
		{
			pixuiWinAlertDelegate.Broadcast(fstr_Msg);
		}
	}
	break;
	case ST_PX_EVENT::n_type_message:
	{
		if (pixuiWinMessageDelegate.IsBound())
		{
			pixuiWinMessageDelegate.Broadcast(fstr_Msg);
		}
	}
	break;
	default:
	{
		if (pixuiWinTransformDelegate.IsBound())
		{
			pixuiWinTransformDelegate.Broadcast((EPXViewEvent)n_Event, n_Param1, n_Param2);
		}
		else
		{
			if (mBeAutoTransForm)
			{
				UCanvasPanelSlot* p_panel_slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
				if (p_panel_slot)
				{
					switch ((EPXViewEvent)n_Event)
					{
					case EPXViewEvent::em_px_event_moveby:
						//PxLog_Trace("em_px_event_moveby x:%d y:%d!!", n_Param1, n_Param2);
						p_panel_slot->SetPosition(p_panel_slot->GetPosition() + FVector2D(n_Param1, n_Param2));
						break;
					case EPXViewEvent::em_px_event_moveto:
						//PxLog_Trace("em_px_event_moveto x:%d y:%d!!", n_Param1, n_Param2);
						p_panel_slot->SetPosition(FVector2D(n_Param1, n_Param2));
						break;
					case EPXViewEvent::em_px_event_resizeby:
						//PxLog_Trace("em_px_event_resizeby x:%d y:%d!!", n_Param1, n_Param2);
						p_panel_slot->SetSize(p_panel_slot->GetSize() + FVector2D(n_Param1, n_Param2));
						break;
					case EPXViewEvent::em_px_event_resizeto:
						//PxLog_Trace("em_px_event_resizeto x:%d y:%d!!", n_Param1, n_Param2);
						p_panel_slot->SetSize(FVector2D(n_Param1, n_Param2));
						break;
					case EPXViewEvent::em_px_event_scrollby:
						//PxLog_Warning("EPXViewEvent::em_px_event_scrollby do not support!!");
						break;
					case EPXViewEvent::em_px_event_scrollto:
						//PxLog_Warning("EPXViewEvent::em_px_event_scrollto do not support!!");
						break;
					default:
						break;
					}
				}
				else
				{
					PxLog_Warning("SlotAsCanvasSlot do not get UCanvasPanelSlot!!");
				}
			}
		}
	}
	break;
	}
}


void UPixUIWidget::AddSubWidget(TWeakObjectPtr<class UPxSubLayerWidget> subWidget)
{
	if (subWidget.IsValid())
	{
		UCanvasPanelSlot* p_SlotPanle = AddChildToCanvas(subWidget.Get());
		if (p_SlotPanle)
		{
			p_SlotPanle->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
			p_SlotPanle->SetOffsets(FMargin(0.0f, 0.0f, 0.0f, 0.0f));
			p_SlotPanle->SetZOrder(-1);
		}
	}
}

TWeakObjectPtr<UPxSubLayerWidget>& UPixUIWidget::GetCurSubLayer()
{
	if (!mPtrCurrentLayerWidget.IsValid())
	{
		mPtrCurrentLayerWidget = PopFreeSubLayer();
		UCanvasPanelSlot* pPanleSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(mPtrCurrentLayerWidget.Get());
		if (pPanleSlot)
		{
			pPanleSlot->SetZOrder(mIntCurrentZorder++);
		}
	}
	return mPtrCurrentLayerWidget;
}


TWeakObjectPtr<UPxSubLayerWidget> UPixUIWidget::PopFreeSubLayer()
{
	TWeakObjectPtr<UPxSubLayerWidget> ptrWeakWidge = nullptr;
	if (mArrayFreeLayerWidget.Num() > 0)
	{
		ptrWeakWidge = mArrayFreeLayerWidget.Pop();
		ptrWeakWidge->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		ptrWeakWidge = NewObject<UPxSubLayerWidget>();
		ptrWeakWidge->SetWidgetParent(this);
		AddSubWidget(ptrWeakWidge);
	}

	mArrayLayerWidget.Add(ptrWeakWidge);
	return ptrWeakWidge;
}


void UPixUIWidget::PushFreeSubLayer(TWeakObjectPtr<class UPxSubLayerWidget> weakSubLayer)
{
	weakSubLayer->SetVisibility(ESlateVisibility::Hidden);
	mArrayFreeLayerWidget.Push(weakSubLayer);
}


void UPixUIWidget::CreatePxView()
{
	if (UPixUIBPLibrary::PixUI_IsStartUp())
	{
		if (!IsPxViewValid() && PixUtil::IsGamePlay())
		{
			UCanvasPanelSlot* ptrPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
			if (ptrPanelSlot)
			{
				FVector2D v2dSize = ptrPanelSlot->GetSize();
				mIntPxViewId = px_plugin::pxViewCreate(0);
				if (mIntPxViewId <= 0)
				{
					PxLog_Error("UPixUIWidget::CreatePxView PX_Plugin::PX_ViewCreate error!!!!!!!!!!!!!!!!!!!!!");
				}
				else
				{
					px_plugin::pxViewInit(mIntPxViewId, this, this, v2dSize.X > 0 ? v2dSize.X : 10, v2dSize.Y > 0 ? v2dSize.Y : 10);
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
					PxLog_Trace("PixUIRes UPixUIWidget CreatePxView total count:%d", ++PixUIWidgetTotalCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
				}
			}
			
		}
		else
		{
			PxLog_Warning("UPixUIWidget::CreatePxView recreate!!!!!!!!!!!!!!!!!!!!!");
		}
	}
	else
	{
		PxLog_Warning("UPixUIWidget::CreatePxView not startup please call PixUI_Startup first !!!!!!!!!!!!!!!!!!!!!");
	}
}

void UPixUIWidget::DestroyPxView()
{
	if (UPixUIBPLibrary::PixUI_IsStartUp())
	{
		if (IsPxViewValid())
		{
			auto ret = px_plugin::pxViewDestroy(PxViewId());
			if (ret != 0)
			{
				PxLog_Error("UPixUIWidget::CreatePxView px_plugin::pxViewDestroy error ret:%d !!!!!!!!!!!!!!!!!!!!!, ret");
			}
			mIntPxViewId = 0;

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
			PxLog_Trace("PixUIRes UPixUIWidget DestroyPxView total count:%d", --PixUIWidgetTotalCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)

		}
	}

	if (OnDestroyDelegate.IsBound())
	{
		OnDestroyDelegate.Broadcast();
	}

	//GEngine GC
	PixUtil::EngineGC(true);
}


bool UPixUIWidget::IsPxViewValid()
{
	return PxViewId() > 0;
}


void UPixUIWidget::ClearDrawItem()
{
	if (mPtrCtrlWidget.IsValid())
	{
		auto pDrawItem = mPtrCtrlWidget->PopAllDrawItem();
// 		while (pDrawItem)
// 		{
// 			PixDrawItem::FreeDrawItemToPools(pDrawItem);
// 			pDrawItem = pDrawItem->Next();
// 		}

		pDrawItem = mPtrRootLayerWidget->PopAllDrawItem();
// 		while (pDrawItem)
// 		{
// 			PixDrawItem::FreeDrawItemToPools(pDrawItem);
// 			pDrawItem = pDrawItem->Next();
// 		}

		for (auto layerWidget : mArrayLayerWidget)
		{
			pDrawItem = layerWidget->PopAllDrawItem();
// 			while (pDrawItem)
// 			{
// 				PixDrawItem::FreeDrawItemToPools(pDrawItem);
// 				pDrawItem = pDrawItem->Next();
// 			}

			PushFreeSubLayer(layerWidget);
		}
		mArrayLayerWidget.Empty();
	}

	for (int i = 0; i < e_px_draw_item_count; i++)
	{
		mUnDrawItemPoolsIndex[i] = 0;
	}
}

void UPixUIWidget::ResetDrawParams()
{
	mEmLastBatchType = e_px_batch_none;
	mPtrLastBatchStatus = nullptr;
	mUlCurDrawBaseLayer = 0;
}

int32 UPixUIWidget::BatchElement(PixDrawItem* ptrBatchItem)
{
	EPxBatchType e_batch_type = ptrBatchItem->BatchType();
	void* p_batch_status = ptrBatchItem->BatchStatus();

	if (e_batch_type != e_px_batch_none)
	{
		if (mEmLastBatchType != e_batch_type ||
			mEmLastBatchType == e_px_batch_rect_mat ||
			mEmLastBatchType == e_px_batch_matiral ||
			mEmLastBatchType == e_px_batch_image)
		{
			if (mEmLastBatchType == e_px_batch_image && e_batch_type == e_px_batch_image && mPtrLastBatchStatus == p_batch_status)
			{
				//to check draw status
				return mUlCurDrawBaseLayer;
			}

			//em_draw_rect_mat or em_draw_matiral need to add layer,
			//Make sure the same brush rendering level is correct
			if (mEmLastBatchType != e_px_batch_none)
			{
				mUlCurDrawBaseLayer++;
			}
			mEmLastBatchType = e_batch_type;
			mPtrLastBatchStatus = p_batch_status;
		}
	}
	return mUlCurDrawBaseLayer;
}


PixDrawItem* UPixUIWidget::DrawItemFromPools(EPxDrawItem e_type)
{
	PixDrawItem* p_draw_item = nullptr;
	if (e_type < e_px_draw_item_count)
	{
		if (mUnDrawItemPoolsIndex[e_type] < (uint32)(mArrayDrawItemPools[e_type].Num()))
		{
			p_draw_item = mArrayDrawItemPools[e_type][mUnDrawItemPoolsIndex[e_type]++];
		}
		else
		{
			p_draw_item = PixDrawItem::NewDrawItem(e_type);
			if (p_draw_item)
			{
				mUnDrawItemPoolsIndex[e_type]++;
				mArrayDrawItemPools[e_type].Add(p_draw_item);
			}
		}
	}
	else
	{
		PxLog_Error("UPixUIWidget::DrawItemFromPools e_type error %d", e_type);
	}
	return p_draw_item;
}


void UPixUIWidget::FreeDrawItemPools()
{
	for (int i = 0; i < e_px_draw_item_count; i++)
	{
		mUnDrawItemPoolsIndex[i] = 0;
		for (auto p_item : mArrayDrawItemPools[i])
		{
			delete p_item;
		}
		mArrayDrawItemPools[i].Empty();
	}
}


pixui::PxViewHandle UPixUIWidget::PxViewId()
{
	return mIntPxViewId;
}


void UPixUIWidget::StartUp()
{
	//do stuff when start up
}


void UPixUIWidget::Tick(float InDeltaTime)
{
	//for each widget
	for (auto widget : PixUIWidgets())
	{
		if (widget.IsValid())
		{
			widget->OnTick(InDeltaTime);
		}
	}
}


void UPixUIWidget::ShutDown()
{
	//clear all PixUIWidget
	for (auto widget : PixUIWidgets())
	{
		if (widget.IsValid())
		{
			widget->DestroyPage();
		}
	}
	PixUIWidgets().Empty();
}


void UPixUIWidget::AddPixUIWidget(TWeakObjectPtr<UPixUIWidget> wptr_PixUIWidget)
{
	PixUIWidgets().Add(wptr_PixUIWidget);
}


void UPixUIWidget::RemovePixUIWidget(TWeakObjectPtr<UPixUIWidget> wptr_PixUIWidget)
{
	auto n_index = PixUIWidgets().Find(wptr_PixUIWidget);
	if (n_index >= 0)
	{
		PixUIWidgets().RemoveAt(n_index);

		if (PixUIWidgets().Num() <= 0)
		{
			PixDrawItem::FreeAllDrawItem();
		}
	}
	else
	{
		PxLog_Warning("UPixUIWidget::RemovePixUIWidget Do not Found PixUIWidget");
	}
}

UPixUIWidget* UPixUIWidget::FindPixUIWidgetByID(int32 windowId)
{
	for (auto px_widget : PixUIWidgets())
	{
		if (px_widget.IsValid())
		{
			auto handle = px_widget.Get()->PxViewId();
			if (px_widget.IsValid() && *((int32*)(&(handle))) == windowId)
			{
				return px_widget.Get();
			}
		}
	}
	PxLog_Warning("UPixUIWidget::FindWindowIdByPixUIWidget Do not Found PixUIWidget");
	return nullptr;
}


void UPixUIWidget::ShowWidgetsInfor()
{
	for (auto px_widget : PixUIWidgets())
	{
		if (px_widget.IsValid())
		{
			px_widget->ShowWidgetInfor();
		}
	}
}


TArray<TWeakObjectPtr<UPixUIWidget>>& UPixUIWidget::PixUIWidgets()
{
	static TArray< TWeakObjectPtr<UPixUIWidget> > ary_PixUIWidgets_s;
	return ary_PixUIWidgets_s;
}


uint32& UPixUIWidget::PixUIWidgetTotalCount()
{
	static uint32 un_pixui_widget_total_count_s = 0;
	return un_pixui_widget_total_count_s;
}


void UPixUIWidget::NotifyAppForeground()
{
	for (auto widget : PixUIWidgets())
	{
		if (widget.IsValid())
		{
			widget->OnAppForeground();
		}
	}
}

void UPixUIWidget::NotifyAppBackground()
{
	for (auto widget : PixUIWidgets())
	{
		if (widget.IsValid())
		{
			widget->OnAppBackground();
		}
	}
}

#undef LOCTEXT_NAMESPACE