/**************************************************

**** @file:     PixUIInput.h

**** @brief:    pixui input system

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core.h"
#include "SlateCore.h"
#include "HAL/ThreadingBase.h"

#include "PixUIDef.h"
#include "PixUIInput.generated.h"

//pixui plugin log levels
UENUM(BlueprintType)
enum class EPXKeyboardTypes :uint8
{
	em_px_key_board_default		UMETA(DisplayName = "pix keyboard type default"),
	em_px_key_board_number		UMETA(DisplayName = "pix keyboard type default"),
	em_px_key_board_password	UMETA(DisplayName = "pix keyboard type default"),

	em_px_key_board_count		UMETA(DisplayName = "pix keyboard type count"),
};

DECLARE_DYNAMIC_DELEGATE_RetVal_ThreeParams(bool, FPXOnActivateInput, EPXKeyboardTypes, keyboardType, const FString&, defaultText, const FString&, HintText);
DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FPXOnDeativateInput);



class SWidget;
class IPxInputProxy
{
public:
	virtual ~IPxInputProxy() {};

public:
	virtual TSharedPtr<SWidget> GetSlateWidget() = 0;
	virtual void OnInputText(const FString& fstr_new_input, const bool b_end_input, const bool b_lost_focus, const bool b_replace) = 0;
};

class DefaultInput;

/**
 * 
 */
UCLASS()
class PIXUI_API UPixUIInput : public UObject
{
    GENERATED_BODY()

public:
	UPixUIInput(const FObjectInitializer& ObjectInitializer);

    /************************************************************************/
    // UObject implementation
    virtual void BeginDestroy() override;
    // UObject implementation
    /************************************************************************/

public:
	//input delegate  ActivateDelegate && DeativateInput Must be bound at the same time;
	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
	FPXOnActivateInput ActivateDelegate;

	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
	FPXOnDeativateInput DeativateInput;

public:
    //get pixui input instance
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUIInput Get", Keywords = "PixUIInput Get"), Category = "PixUIInput")
    static UPixUIInput* Get();


	static void Tick(float InDeltaTime);

	static void Destroy();

	//input text
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUIInput OnInputText", Keywords = "PixUIInput OnInputText"), Category = "PixUIInput")
    static void OnInputText(const FString& fstrInsert, const bool b_end_input, const bool b_lost_focus, const bool b_replace);

public:
	static bool OnActivateInput(IPxInputProxy* wptr_pix_Widget, const EPXKeyboardTypes& e_keyboard_type, const FString& fstr_default_text, const FString& fstr_hint_text);
	static bool OnDeativateInput(IPxInputProxy* wptr_pix_Widget);

	static TSharedPtr<SWidget> GetWidget();

protected:
	static void OnSafeInput(const FString& fstrInsert, const bool b_end_input, const bool b_lost_focus, const bool b_replace);
    //UPixUIInput reference
    static TWeakObjectPtr<UPixUIInput>& PixUIInputWRef();

private:
	bool b_active_;

	IPxInputProxy* wptr_cur_pix_widget_;

	DefaultInput* p_default_inputsystem_;
};
