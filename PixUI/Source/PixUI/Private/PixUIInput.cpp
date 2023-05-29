/**************************************************

**** @file:     PixUIInput.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixUIInput.h"

#include "PixUIDef.h"
#include "PixUILog.h"



/*********************************system input***************************************/
#include "PixInputSystem/IPixInputSystem.h"

class DefaultInput : public IInputSystem
{
public:
	DefaultInput();
	~DefaultInput();

public:
	void UpdateInput(EKeyboardType e_type,const FString& fstr_default_text, const FString& fstr_hint_text);

public:
    /************************************************************************/
    //Begin IInputSystem implementation
    virtual FText GetInputText() override;
    virtual FText GetInputHintText() override;
    virtual EKeyboardType GetVirtualKeyboardType() override;

#if ENGINE_MAJOR_VERSION < 5

	/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 19    //ue4 minor version < 20 do not support GetVirtualKeyboardOptions
	virtual FVirtualKeyboardOptions GetVirtualKeyboardOptions() override;
#endif //ENGINE_MINOR_VERSION > 19
	/////////////////////////////////////////////////////////////////////for ue4

#else

	/////////////////////////////////////////////////////////////////////for ue5
	virtual FVirtualKeyboardOptions GetVirtualKeyboardOptions() override;
	/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5

    virtual bool IsMultilineEntry() override;
    virtual TSharedPtr<SWidget> GetWidget() override;

protected:
    virtual void OnTextInsert(const FString& fstrInsert, const bool b_replace) override;
    virtual void OnEndInput(const FString& fstrNewText) override;
    //End IInputSystem implementation
    /************************************************************************/

private:
	//input text
	FString fstr_InuputText_;

	//input hint text
	FString fstr_InuputHintText_;

	//keyboard type
	EKeyboardType e_Keyboardtype_;

};

DefaultInput::DefaultInput()
{
	e_Keyboardtype_ = Keyboard_Default;
}

DefaultInput::~DefaultInput()
{
}

void DefaultInput::UpdateInput(EKeyboardType e_type, const FString& fstr_default_text, const FString& fstr_hint_text)
{
	e_Keyboardtype_ = e_type;
	fstr_InuputText_ = fstr_default_text;
	fstr_InuputHintText_ = fstr_hint_text;
}

FText DefaultInput::GetInputText()
{
	return FText::FromString(fstr_InuputText_);
}

FText DefaultInput::GetInputHintText()
{
	return FText::FromString(fstr_InuputHintText_);
}

EKeyboardType DefaultInput::GetVirtualKeyboardType()
{
	return e_Keyboardtype_;
}

#if ENGINE_MAJOR_VERSION < 5

/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 19    //ue4 minor version < 20 do not support GetVirtualKeyboardOptions
FVirtualKeyboardOptions DefaultInput::GetVirtualKeyboardOptions()
{
	FVirtualKeyboardOptions tmpKeyBordOptions;
	return tmpKeyBordOptions;
}
#endif //ENGINE_MINOR_VERSION > 19
/////////////////////////////////////////////////////////////////////for ue4

#else

/////////////////////////////////////////////////////////////////////for ue5
FVirtualKeyboardOptions DefaultInput::GetVirtualKeyboardOptions()
{
	FVirtualKeyboardOptions tmpKeyBordOptions;
	return tmpKeyBordOptions;
}
/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5

bool DefaultInput::IsMultilineEntry()
{
	return false;
}

TSharedPtr<SWidget> DefaultInput::GetWidget()
{
	return UPixUIInput::GetWidget();
}

void DefaultInput::OnTextInsert(const FString& fstr_Insert, const bool b_replace)
{
    UPixUIInput::OnInputText(fstr_Insert, false, false, b_replace);
}

void DefaultInput::OnEndInput(const FString& fstr_NewText)
{
    UPixUIInput::OnInputText(fstr_NewText, true, false, false);
}

/*********************************system input***************************************/





#define PixUIInputRef PixUIInputWRef()


UPixUIInput::UPixUIInput(const FObjectInitializer& ObjectInitializer)
{
    PxLog_Trace("UPixUIInput::UPixUIInput Create");
	b_active_ = true;
	wptr_cur_pix_widget_ = nullptr;

	p_default_inputsystem_ = new DefaultInput();
}


void UPixUIInput::BeginDestroy()
{
	b_active_ = true;
	wptr_cur_pix_widget_ = nullptr;
	if (p_default_inputsystem_)
	{
		delete p_default_inputsystem_;
		p_default_inputsystem_ = nullptr;
	}
    Super::BeginDestroy();
    PxLog_Trace("UPixUIInput::UPixUIInput Destroy");
}


UPixUIInput* UPixUIInput::Get()
{
    if (!PixUIInputRef.IsValid())
    {
		PixUIInputRef = NewObject<UPixUIInput>();
		PixUIInputRef->AddToRoot();
    }
    return PixUIInputRef.Get();
}


void UPixUIInput::Tick(float InDeltaTime)
{
	if (PixUIInputRef.IsValid() && PixUIInputRef->b_active_ && GetWidget().IsValid() && PixUIInputRef->p_default_inputsystem_)
	{
		PixUIInputRef->p_default_inputsystem_->OnInputTick(GetWidget()->GetCachedGeometry(), FApp::GetCurrentTime(), InDeltaTime);
	}
}


void UPixUIInput::Destroy()
{
    if (PixUIInputRef.IsValid())
    {
		PixUIInputRef->ActivateDelegate.Clear();
		PixUIInputRef->DeativateInput.Clear();

		PixUIInputRef->RemoveFromRoot();
		PixUIInputRef = nullptr;
    }
}


void UPixUIInput::OnInputText(const FString& fstrInsert, const bool b_end_input, const bool b_lost_focus, const bool b_replace)
{
	PxLog_Trace("UPixUIInput::OnInputText %s replace: %d", TCHAR_TO_UTF8(*fstrInsert), b_replace);
    //make sure call SafeDispach in game thread
    if (IsInGameThread())
    {
		OnSafeInput(fstrInsert, b_end_input, b_lost_focus, b_replace);
    }
    else
    {
		//call in game thread
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			OnSafeInput(fstrInsert, b_end_input, b_lost_focus, b_replace);
		});
    }
}


bool UPixUIInput::OnActivateInput(IPxInputProxy* p_pix_Widget, const EPXKeyboardTypes& e_keyboard_type, const FString& fstr_default_text, const FString& fstr_hint_text)
{
	bool b_ret = false;
	if (Get())
	{
		if (PixUIInputRef->b_active_)
		{
			PxLog_Warning("UPixUIInput::OnActivateInput already active");
		}
		PixUIInputRef->wptr_cur_pix_widget_ = p_pix_Widget;
		PixUIInputRef->b_active_ = true;
		if (PixUIInputRef->ActivateDelegate.IsBound() && PixUIInputRef->DeativateInput.IsBound())
		{
			//use bound delegate
			b_ret = PixUIInputRef->ActivateDelegate.Execute(e_keyboard_type, fstr_default_text, fstr_hint_text);
		}
		else
		{
			EKeyboardType e_type;
			switch (e_keyboard_type)
			{
			case EPXKeyboardTypes::em_px_key_board_number:
				e_type = Keyboard_Number;
				break;
			case EPXKeyboardTypes::em_px_key_board_password:
				e_type = Keyboard_Password;
				break;
			default:
				e_type = Keyboard_Default;
				break;
			}
			PixUIInputRef->p_default_inputsystem_->UpdateInput(e_type, fstr_default_text, fstr_hint_text);
			//use default input system
			PixUIInputRef->p_default_inputsystem_->ActivateInput();

			b_ret = true;
		}

		PxLog_Trace("UPixUIInput::OnActivateInput %d", b_ret);
	}
	else
	{
		PxLog_Error("UPixUIInput::OnActivateInput PixUIInputWRef IsInValid");
	}
	return b_ret;
}


bool UPixUIInput::OnDeativateInput(IPxInputProxy* p_pix_Widget)
{
	bool b_ret = false;
	if (Get())
	{
		if (!PixUIInputRef->b_active_)
		{
			PxLog_Warning("UPixUIInput::OnActivateInput not active");
		}

		if (PixUIInputRef->wptr_cur_pix_widget_ != p_pix_Widget)
		{
			PxLog_Warning("UPixUIInput::OnActivateInput active widget diffrent.........");
		}
		PixUIInputRef->wptr_cur_pix_widget_ = nullptr;
		PixUIInputRef->b_active_ = false;
		if (PixUIInputRef->ActivateDelegate.IsBound() && PixUIInputRef->DeativateInput.IsBound())
		{
			//use bound delegate
			b_ret = PixUIInputRef->DeativateInput.Execute();
		}
		else
		{
			//use default input system
			PixUIInputRef->p_default_inputsystem_->DeativateInput();
			b_ret = true;
		}

		PxLog_Trace("UPixUIInput::OnDeativateInput %d", b_ret);
	}
	else
	{
		PxLog_Error("UPixUIInput::OnDeativateInput PixUIInputWRef IsInValid");
	}
	return b_ret;
}


TSharedPtr<SWidget> UPixUIInput::GetWidget()
{
	TSharedPtr<SWidget> ret_widget = nullptr;
	if (PixUIInputRef.IsValid())
	{
		if (PixUIInputRef->wptr_cur_pix_widget_)
		{
			ret_widget = PixUIInputRef->wptr_cur_pix_widget_->GetSlateWidget();
		}
	}
	return ret_widget;
}


void UPixUIInput::OnSafeInput(const FString& fstrInsert, const bool b_end_input, const bool b_lost_focus, const bool b_replace)
{
	if (PixUIInputRef.IsValid())
	{
		if (PixUIInputRef->wptr_cur_pix_widget_)
		{
			PixUIInputRef->wptr_cur_pix_widget_->OnInputText(fstrInsert, b_end_input, b_lost_focus, b_replace);
			
		}
		else
		{
			PxLog_Error("UPixUIInput::OnSafeInput PixUIInputWRef wptr_cur_pix_widget_ IsInValid");
		}
	}
	else
	{
		PxLog_Error("UPixUIInput::OnSafeInput PixUIInputWRef IsInValid");
	}
}


TWeakObjectPtr<UPixUIInput>& UPixUIInput::PixUIInputWRef()
{
    static TWeakObjectPtr<UPixUIInput> sptr_PixUIInput_s = nullptr;
    return sptr_PixUIInput_s;
}