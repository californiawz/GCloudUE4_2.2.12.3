/**************************************************

**** @file:     PixUIWidgetOld.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/
#include "PixUIWidgetOld.h"


#ifdef DF_PX_USE_OLD_WIDGET


#include "SPixPaintWidgetOld.h"

#include "UnrealEngine.h"
#include "CoreUObject.h"
#include "Misc/CoreDelegates.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#endif

#include "UMG.h"



#include "PixUIInput.h"
#include "PixImpMgr.h"
#include "PixUILibMgr.h"
#include "PixUILog.h"
#include "PixUIWidget.h"
#include "PixUtil.h"

#include "PixUIProfiler/PxpResCount.h"


#define LOCTEXT_NAMESPACE "PIXUI"  //UE4 engine macro

//construct
UPixUIWidgetOld::UPixUIWidgetOld(const FObjectInitializer& ObjectInitializer)
    :sptr_SPixPaintWidget_(nullptr), b_auto_transform_(false)
{
    if (PixUtil::IsGamePlay())
    {
        //Add only in play game
		UPixUIWidgetOld::AddPixUIWidgetOld(this);
	}
	//Visibility = ESlateVisibility::Visible;
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixUIRes UPixUIWidgetOld Construct Create total count:%d", ++ResItemCount::PixWidgetCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}


#if WITH_EDITOR
const FText UPixUIWidgetOld::GetPaletteCategory()
{
    return LOCTEXT("PixUI", "PixUIOld");
}
#endif //WITH_EDITOR


TSharedRef<SWidget> UPixUIWidgetOld::RebuildWidget()
{
    //create paint widget
    sptr_SPixPaintWidget_ = SNew(SPixPaintWidget);
    sptr_SPixPaintWidget_->CreatePxView(this);

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixUIRes UPixUIWidgetOld CreatePxView total count:%d", ++PixUIWidgetOldTotalCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)

    return sptr_SPixPaintWidget_.ToSharedRef();
}


void UPixUIWidgetOld::ReleaseSlateResources(bool b_ReleaseChildren)
{
    //clear
    Super::ReleaseSlateResources(b_ReleaseChildren);

    if (IsPixViewValid())
    {
        //clear paint widget
        sptr_SPixPaintWidget_->DestroyPxView();

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
		PxLog_Trace("PixUIRes UPixUIWidgetOld DestroyPxView total count:%d", --PixUIWidgetOldTotalCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)

		
    }
    sptr_SPixPaintWidget_.Reset();

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


    if (array_Event_.Num() > 0)
    {
        PxLog_Warning("UPixUIWidgetOld::ReleaseSlateResources will be empty window event but There are still some events here num:%d", array_Event_.Num());
    }
    array_Event_.Empty();
}


void UPixUIWidgetOld::BeginDestroy()
{
    Super::BeginDestroy();

    if (PixUtil::IsGamePlay())
    {
        //Remove in play game
        UPixUIWidgetOld::RemovePixUIWidgetOld(this);
    }

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixUIRes UPixUIWidgetOld BeginDestroy~ Destroy total count:%d", --ResItemCount::PixWidgetCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}


int32 UPixUIWidgetOld::OpenPageFromUrl(const FString& fstr_Url)
{
    int32 n_ret = -1;
    if (IsPixViewValid() && !fstr_Url.IsEmpty())
    {
        n_ret = PX_Plugin::PX_ViewLoadPageFromUrl(ViewHandle(), TCHAR_TO_UTF8(*fstr_Url.Replace(TEXT("\\"),TEXT("/"))));
    }
    else
    {
		if (fstr_Url.IsEmpty())
		{
			PxLog_Error(" UPixUIWidgetOld::OpenPageFromUrl url empty");
		}
		else
		{
			PxLog_Error(" UPixUIWidgetOld::OpenPageFromUrl SPixPaintWidget inValid empty; make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
		}
    }
    return n_ret;
}


int32 UPixUIWidgetOld::OpenPageFromData(UPARAM(ref) TArray<uint8>& arry_Data, const FString& fstr_BasePath)
{
    int32 n_ret = -1;
    if (IsPixViewValid() && !fstr_BasePath.IsEmpty() && arry_Data.Num() > 0)
    {
        n_ret = PX_Plugin::PX_ViewLoadPageFromData(ViewHandle(), arry_Data.GetData(), arry_Data.Num(), TCHAR_TO_UTF8(*fstr_BasePath));
    }
	else
	{
		if (fstr_BasePath.IsEmpty() || arry_Data.Num() <= 0)
		{
			PxLog_Error(" UPixUIWidgetOld::OpenPageFromData base path empty  data number:%d", arry_Data.Num());
		}
		else
		{
			PxLog_Error(" UPixUIWidgetOld:OpenPageFromData SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called  or multy page do not support");
		}
    }
    return n_ret;
}


int32 UPixUIWidgetOld::OpenPageFromGameAssetPath(const FString& fstr_FilePath)
{
    int32 n_ret = -1;
    if (IsPixViewValid() && !fstr_FilePath.IsEmpty())
    {
        FString fstr_game_file_path = FPaths::ProjectContentDir() + fstr_FilePath;

        if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*fstr_game_file_path))
        {
            n_ret = -2;
            PxLog_Error("UPixUIWidgetOld::OpenPageFromGameFile error can not found file:%s", TCHAR_TO_UTF8(*fstr_game_file_path));
			OnLoadComplete(TCHAR_TO_UTF8(*fstr_FilePath), false);
			return n_ret;
        }

        // Load the compressed byte data from the file
        TArray<uint8> array_FileData;
        if (!FFileHelper::LoadFileToArray(array_FileData, *fstr_game_file_path))
        {
            n_ret = -3;
            PxLog_Error("UPixUIWidgetOld::OpenPageFromGameFile Failed to load file: %s", TCHAR_TO_UTF8(*fstr_game_file_path));
			OnLoadComplete(TCHAR_TO_UTF8(*fstr_FilePath), false);
			return n_ret;
        }

        //open page from data
        n_ret = OpenPageFromData(array_FileData, fstr_game_file_path);
		OnLoadComplete(TCHAR_TO_UTF8(*fstr_FilePath) , true);
    }
    else
    {
		if (fstr_FilePath.IsEmpty())
		{
			PxLog_Error(" UPixUIWidgetOld::OpenPageFromGameAssetPath file path empty");
		}
		else
		{
			PxLog_Error(" UPixUIWidgetOld::OpenPageFromGameAssetPath SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
		}
    }
    return n_ret;
}


void UPixUIWidgetOld::PostPxMessage(const FString& fstr_Message)
{
    if (IsPixViewValid())
    {
        PX_Plugin::PX_ViewPostMessage(ViewHandle(), TCHAR_TO_UTF8(*fstr_Message), nullptr);
    }
    else
    {
        PxLog_Error(" UPixUIWidgetOld::PostMessage SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
    }
}


void UPixUIWidgetOld::ClosePage()
{
	if (IsPixViewValid())
	{
		PX_Plugin::PX_ViewClose(ViewHandle());

		if (OnCloseDelegate.IsBound())
		{
			OnCloseDelegate.Broadcast();
		}
	}
	else
	{
		PxLog_Error(" UPixUIWidgetOld::ClosePage SPixPaintWidget inValid ;make sure UPixUIBPLibrary::PixUI_Startup was called or multy page do not support");
	}

	//GEngine GC
	PixUtil::EngineGC(true);
}


void UPixUIWidgetOld::DestroyPage()
{
    if (IsPixViewValid())
    {
        sptr_SPixPaintWidget_->DestroyPxView();
    }

	if (OnDestroyDelegate.IsBound())
	{
		OnDestroyDelegate.Broadcast();
	}

    //GEngine GC
    PixUtil::EngineGC(true);
}


void UPixUIWidgetOld::SetAutoTransform(bool b_auto_transform)
{
	b_auto_transform_ = b_auto_transform;
}


int32 UPixUIWidgetOld::GetPxWinId()
{
	if (sptr_SPixPaintWidget_.IsValid())
	{
		return sptr_SPixPaintWidget_->PxWindowID();
	}
	return 0;
}


int32 UPixUIWidgetOld::GetCustomLayer()
{
	if (sptr_SPixPaintWidget_.IsValid())
	{
		return sptr_SPixPaintWidget_->GetCustomLayer();
	}
	return 0;
}


void UPixUIWidgetOld::SetCustomLayer(int32 n_in_layer)
{
	if (sptr_SPixPaintWidget_.IsValid())
	{
		sptr_SPixPaintWidget_->SetCustomLayer(n_in_layer);
	}
}


void UPixUIWidgetOld::CreateScriptGlobal(const FString& name)
{
	if (IsPixViewValid())
	{
		PX_Plugin::PX_ViewCreateScriptGlobal(ViewHandle(), TCHAR_TO_UTF8(*name));
	}
	else
	{
		PxLog_Error(" UPixUIWidgetOld::CreateScriptGlobal SPixPaintWidget inValid");
	}
}


void UPixUIWidgetOld::SetScriptGlobalNumber(const FString& name, const FString& key, float num)
{
	if (IsPixViewValid())
	{
		PX_Plugin::PX_ViewSetScriptGlobalNumber(ViewHandle(), TCHAR_TO_UTF8(*name),TCHAR_TO_UTF8(*key),num);
	}
	else
	{
		PxLog_Error(" UPixUIWidgetOld::SetScriptGlobalNumber SPixPaintWidget inValid");
	}
}


void UPixUIWidgetOld::SetScriptGlobalString(const FString& name, const FString& key, const FString& str)
{
	if (IsPixViewValid())
	{
		PX_Plugin::PX_ViewSetScriptGlobalString(ViewHandle(), TCHAR_TO_UTF8(*name),TCHAR_TO_UTF8(*key),TCHAR_TO_UTF8(*str));
	}
	else
	{
		PxLog_Error(" UPixUIWidgetOld::SetScriptGlobalString SPixPaintWidget inValid");
	}
}


void UPixUIWidgetOld::SetScriptGlobalBoolean(const FString& name, const FString& key, bool v)
{
	if (IsPixViewValid())
	{
		PX_Plugin::PX_ViewSetScriptGlobalBoolean(ViewHandle(), TCHAR_TO_UTF8(*name),TCHAR_TO_UTF8(*key),v);
	}
	else
	{
		PxLog_Error(" UPixUIWidgetOld::SetScriptGlobalBoolean SPixPaintWidget inValid");
	}
}


float UPixUIWidgetOld::GetScriptGlobalNumber(const FString& name, const FString& key)
{
	if (IsPixViewValid())
	{
		return PX_Plugin::PX_ViewGetScriptGlobalNumber(ViewHandle(), TCHAR_TO_UTF8(*name),TCHAR_TO_UTF8(*key));
	}
	else
	{
		PxLog_Error(" UPixUIWidgetOld::GetScriptGlobalNumber SPixPaintWidget inValid");
	}
	return 0;
}


FString UPixUIWidgetOld::GetScriptGlobalString(const FString& name, const FString& key)
{
	if (IsPixViewValid())
	{
		return PX_Plugin::PX_ViewGetScriptGlobalString(ViewHandle(), TCHAR_TO_UTF8(*name),TCHAR_TO_UTF8(*key));
	}
	else
	{
		PxLog_Error(" UPixUIWidgetOld::GetScriptGlobalString SPixPaintWidget inValid");
	}
	return "";
}


bool UPixUIWidgetOld::GetScriptGlobalBoolean(const FString& name, const FString& key)
{
	if (IsPixViewValid())
	{
		return PX_Plugin::PX_ViewGetScriptGlobalBoolean(ViewHandle(), TCHAR_TO_UTF8(*name),TCHAR_TO_UTF8(*key));
	}
	else
	{
		PxLog_Error(" UPixUIWidgetOld::GetScriptGlobalBoolean SPixPaintWidget inValid");
	}
	return false;
}


//push event to widget array_Event_
#define DF_PUSH_PX_EVENT_OLD(_type,_param1,_param2,_msg)    ST_PX_EVENT stTempEvent;    \
    stTempEvent.n_Type = (int)_type;                                                \
    stTempEvent.n_Param1 = _param1;                                                 \
    stTempEvent.n_Param2 = _param2;                                                 \
    stTempEvent.fstr_Msg = _msg;                                                    \
    FScopeLock ScopeLock(&fcs_Mutex_);                                              \
    array_Event_.Push(stTempEvent);


void UPixUIWidgetOld::OnLoadComplete(const char* pszUrl, const bool bSuccess)
{
	if (IsInGameThread())
	{
		if (pixuiOnLoadedDelegate.IsBound())
		{
			pixuiOnLoadedDelegate.Broadcast(UTF8_TO_TCHAR(pszUrl), bSuccess);
		}
	}
	else
	{
		TWeakObjectPtr<UPixUIWidgetOld> wptr_this = this;
		//call in game thread
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			if (wptr_this.IsValid() && wptr_this->pixuiOnLoadedDelegate.IsBound())
			{
				wptr_this->pixuiOnLoadedDelegate.Broadcast(UTF8_TO_TCHAR(pszUrl), bSuccess);
			}
		});
	}
}

void UPixUIWidgetOld::OnScriptStateInit()
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
		TWeakObjectPtr<UPixUIWidgetOld> wptr_this = this;
		//call in game thread
		AsyncTask(ENamedThreads::GameThread, [=]() {
			if (wptr_this.IsValid() && wptr_this->pixuiOnScriptStateInitDelegate.IsBound())
			{
				wptr_this->pixuiOnScriptStateInitDelegate.Broadcast();
			}
		});
	}
}


void UPixUIWidgetOld::OnInternalError(int error, const char* msg)
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
		TWeakObjectPtr<UPixUIWidgetOld> wptr_this = this;
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


int UPixUIWidgetOld::OnOpen(const char* psz_Url, const char* psz_Name, const char* psz_Features, bool b_Replace)
{
    if (IsInGameThread())
    {
        //game thread need sync call
		FString fstr_url = UTF8_TO_TCHAR(psz_Url?psz_Url:"");
		FString fstr_name = UTF8_TO_TCHAR(psz_Name?psz_Name:"");
		FString fstr_features = UTF8_TO_TCHAR(psz_Features?psz_Features:"");
		//call in game thread
		TWeakObjectPtr<UPixUIWidgetOld> wptr_this = this;
    	if (wptr_this.IsValid() && wptr_this->pixuiWinOpenDelegate.IsBound())
    	{
    		return wptr_this->pixuiWinOpenDelegate.Execute( fstr_url, fstr_name, fstr_features, b_Replace);
    	}
    	else
    	{
    		PxLog_Warning(" UPixUIWidgetOld::OnOpen pixuiOpenDelegate is not bound or UPixUIWidgetOld inValid");
    	}
    }
    else
    {
        PxLog_Error(" UPixUIWidgetOld::OnOpen Called Not In Gamethread");
    }
    return 0;
}


void UPixUIWidgetOld::OnClose()
{
	DF_PUSH_PX_EVENT_OLD(ST_PX_EVENT::n_type_close, 0, 0, TEXT(""));
}


void UPixUIWidgetOld::OnAlert(const char* psz_Text)
{
	DF_PUSH_PX_EVENT_OLD(ST_PX_EVENT::n_type_alert, 0, 0, UTF8_TO_TCHAR(psz_Text));
}


bool UPixUIWidgetOld::OnConfirm(const char* psz_Message)
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
            PxLog_Error(" UPixUIWidgetOld::OnConfirm pixuiConfirmDelegate is not bound");
        }
    }
    else
    {
        PxLog_Error(" UPixUIWidgetOld::OnConfirm Called Not In Gamethread");
    }
    return b_Ret;
}


const char* UPixUIWidgetOld::OnPrompt(const char* psz_Text, const char* psz_DefaultText)
{
    if (IsInGameThread())
    {
        fstr_prompt_ret_.Empty();
        if (pixuiWinPrompDelegate.IsBound())
        {
            fstr_prompt_ret_ = pixuiWinPrompDelegate.Execute(UTF8_TO_TCHAR(psz_Text), UTF8_TO_TCHAR(psz_DefaultText));
        }
        else
        {
            PxLog_Error(" UPixUIWidgetOld::OnPrompt pixuiPrompDelegate PrompDelegate was not bound");
        }
        static std::string str_prompt_g;
        str_prompt_g = TCHAR_TO_UTF8(*fstr_prompt_ret_);

        //return TCHAR_TO_UTF8(*fstr_prompt_ret_) was not safe
        return str_prompt_g.c_str();
    }
    else
    {
        PxLog_Error(" UPixUIWidgetOld::OnPrompt Called Not In Gamethread");
    }
    return "";
}


void UPixUIWidgetOld::OnMoveBy(const int n_XposMoveBy, const int n_YposMoveBy)
{
	DF_PUSH_PX_EVENT_OLD(EPXViewEvent::em_px_event_moveby, n_XposMoveBy, n_YposMoveBy, TEXT(""));
}


void UPixUIWidgetOld::OnMoveTo(const int n_XposMoveTo, const int n_YposMoveTo)
{
	DF_PUSH_PX_EVENT_OLD(EPXViewEvent::em_px_event_moveto, n_XposMoveTo, n_YposMoveTo, TEXT(""));
}


void UPixUIWidgetOld::OnResizeBy(const int n_OffsetWidth, const  int n_OffsetHeight)
{
	DF_PUSH_PX_EVENT_OLD(EPXViewEvent::em_px_event_resizeby, n_OffsetWidth, n_OffsetHeight, TEXT(""));
}


void UPixUIWidgetOld::OnResizeTo(const int n_NewWidth, const int n_NewHeight)
{
	DF_PUSH_PX_EVENT_OLD(EPXViewEvent::em_px_event_resizeto, n_NewWidth, n_NewHeight, TEXT(""));
}


void UPixUIWidgetOld::OnScrollBy(const int n_OffsetXpos, const int n_OffsetYpos)
{
	DF_PUSH_PX_EVENT_OLD(EPXViewEvent::em_px_event_scrollby, n_OffsetXpos, n_OffsetYpos, TEXT(""));
}


void UPixUIWidgetOld::OnScrollTo(const int n_NewXpos, const int n_NewYpos)
{
	DF_PUSH_PX_EVENT_OLD(EPXViewEvent::em_px_event_scrollto, n_NewXpos, n_NewYpos, TEXT(""));
}


void UPixUIWidgetOld::OnMessage(const char* psz_Message)
{
	DF_PUSH_PX_EVENT_OLD(ST_PX_EVENT::n_type_message, 0, 0, UTF8_TO_TCHAR(psz_Message));
}


bool UPixUIWidgetOld::OnActivateInput(pixui::EKeyboardType e_KeyboardType, const char* psz_DefaultText, const char* psz_HintText)
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

    bool b_ret = UPixUIInput::OnActivateInput( this, e_type, UTF8_TO_TCHAR(psz_DefaultText), UTF8_TO_TCHAR(psz_HintText));
	if (IsPixViewValid())
	{
		sptr_SPixPaintWidget_->SetActiveInput(b_ret);
	}
	return b_ret;
}


bool UPixUIWidgetOld::OnDeativateInput()
{
	bool b_ret = UPixUIInput::OnDeativateInput(this);
	if (IsPixViewValid())
	{
		sptr_SPixPaintWidget_->SetActiveInput(b_ret);
	}
	return b_ret;
}


void UPixUIWidgetOld::SetWindowPass(bool b_pass)
{
	if (IsPixViewValid())
	{
		sptr_SPixPaintWidget_->SetVisibility(b_pass ? EVisibility::HitTestInvisible : EVisibility::Visible);
	}
}


void UPixUIWidgetOld::SetWindowPriority(int n_priority)
{
	UCanvasPanelSlot* p_panel_slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	if (p_panel_slot)
		p_panel_slot->SetZOrder(n_priority);
}


void UPixUIWidgetOld::OnInputText(const FString& fstr_new_input, const bool b_end_input, const bool b_lost_focus, const bool b_replace)
{
	if (IsPixViewValid())
	{
        sptr_SPixPaintWidget_->OnInputText(fstr_new_input, b_end_input, b_lost_focus, b_replace);
	}
}


TSharedPtr<SWidget> UPixUIWidgetOld::GetWidget()
{
	if (IsPixViewValid())
	{
		return sptr_SPixPaintWidget_;
	}
	return nullptr;
}


void UPixUIWidgetOld::OnAppForeground()
{
	if (pixuiWin_app_foreground_delegate.IsBound())
	{
		pixuiWin_app_foreground_delegate.Broadcast();
	}
}


void UPixUIWidgetOld::OnAppBackground()
{
	if (pixuiWin_app_background_delegate.IsBound())
	{
		pixuiWin_app_background_delegate.Broadcast();
	}
}


void UPixUIWidgetOld::ShowWidgetInfor()
{
	if (IsPixViewValid())
	{
		sptr_SPixPaintWidget_->ShowDrawItemInfor();
	}
}

px_ptr UPixUIWidgetOld::GetContextPtr()
{
	if (IsPixViewValid())
	{
		return sptr_SPixPaintWidget_->GetContextPtr();
	}

	return nullptr;
}

void UPixUIWidgetOld::OnTick(float InDeltaTime)
{
    int n_LoopTime = 0;
    int n_Num = 0;

    //Extract up to 10 events each time to prevent infinite loop
    while (IsPixViewValid() && n_LoopTime < 10)
    {
        ST_PX_EVENT stTempEvent;
        {
            FScopeLock ScopeLock(&fcs_Mutex_);

            n_Num = array_Event_.Num();
            if (n_Num > 0)
            {
                stTempEvent = array_Event_[0];
                array_Event_.RemoveAt(0);
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


void UPixUIWidgetOld::BroadcastEvent(const int n_Event, const int32 n_Param1, const int32 n_Param2, const FString& fstr_Msg)
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
                pixuiWinTransformDelegate.Broadcast((EPXViewEvent)n_Event,n_Param1,n_Param2);
            }
			else
			{
				if (b_auto_transform_)
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


bool UPixUIWidgetOld::IsPixViewValid()
{
    return sptr_SPixPaintWidget_.IsValid() && sptr_SPixPaintWidget_->PxViewHandle();
}


px_ptr UPixUIWidgetOld::ViewHandle()
{
    return sptr_SPixPaintWidget_.IsValid() ? sptr_SPixPaintWidget_->PxViewHandle() : nullptr;
}


void UPixUIWidgetOld::StartUp()
{
    //do stuff when start up
}


void UPixUIWidgetOld::Tick(float InDeltaTime)
{
    //for each widget
    for (auto widget : PixUIWidgetOlds())
    {
        if (widget.IsValid())
        {
            widget->OnTick(InDeltaTime);
        }
    }
}


void UPixUIWidgetOld::ShutDown()
{
    //clear all PixUIWidgetOld
    for (auto widget : PixUIWidgetOlds())
    {
        if (widget.IsValid())
        {
            widget->DestroyPage();
        }
    }
    PixUIWidgetOlds().Empty();
}


void UPixUIWidgetOld::AddPixUIWidgetOld(TWeakObjectPtr<UPixUIWidgetOld> wptr_PixUIWidgetOld)
{
    PixUIWidgetOlds().Add(wptr_PixUIWidgetOld);
}


void UPixUIWidgetOld::RemovePixUIWidgetOld(TWeakObjectPtr<UPixUIWidgetOld> wptr_PixUIWidgetOld)
{
    auto n_index = PixUIWidgetOlds().Find(wptr_PixUIWidgetOld);
    if (n_index >= 0)
    {
        PixUIWidgetOlds().RemoveAt(n_index);
    }
    else
    {
        PxLog_Warning("UPixUIWidgetOld::RemovePixUIWidgetOld Do not Found PixUIWidgetOld");
    }
}

UPixUIWidgetOld* UPixUIWidgetOld::FindPixUIWidgetOldByID(int64 windowId)
{
    for (auto px_widget : PixUIWidgetOlds())
    {
        if (px_widget.IsValid() && (int64)px_widget.Get()->ViewHandle() == windowId)
        {
            return px_widget.Get();
        }
    }
    PxLog_Warning("UPixUIWidgetOld::FindWindowIdByPixUIWidgetOld Do not Found PixUIWidgetOld");
    return nullptr;
}


void UPixUIWidgetOld::ShowWidgetsInfor()
{
	for (auto px_widget : PixUIWidgetOlds())
	{
		if (px_widget.IsValid())
		{
			px_widget->ShowWidgetInfor();
		}
	}
}

TArray<TWeakObjectPtr<UPixUIWidgetOld>>& UPixUIWidgetOld::PixUIWidgetOlds()
{
    static TArray< TWeakObjectPtr<UPixUIWidgetOld> > ary_PixUIWidgetOlds_s;
    return ary_PixUIWidgetOlds_s;
}



uint32& UPixUIWidgetOld::PixUIWidgetOldTotalCount()
{
	static uint32 un_pixui_widget_total_count_s = 0;
	return un_pixui_widget_total_count_s;
}


void UPixUIWidgetOld::NotifyAppForeground()
{
	for (auto widget : PixUIWidgetOlds())
	{
		if (widget.IsValid())
		{
			widget->OnAppForeground();
		}
	}
}

void UPixUIWidgetOld::NotifyAppBackground()
{
	for (auto widget : PixUIWidgetOlds())
	{
		if (widget.IsValid())
		{
			widget->OnAppBackground();
		}
	}
}


TSharedPtr<SWidget> UPixUIWidgetOld::GetSlateWidget()
{
	return TakeWidget();
}

#undef LOCTEXT_NAMESPACE


#endif // DF_PX_USE_OLD_WIDGET
