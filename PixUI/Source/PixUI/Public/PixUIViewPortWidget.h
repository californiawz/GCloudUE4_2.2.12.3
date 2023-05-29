/**************************************************

**** @file:     PixUIViewPortWidget.h

**** @brief:    pixui UserWidget for viewport widget

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Slate.h"
#include "SlateCore.h"
//#include "Runtime/Core/Public/HAL/ThreadingBase.h"
#include "HAL/ThreadingBase.h"

#include "PixUIWidget.h"

#include "PixUIViewPortWidget.generated.h"


UCLASS()
class PIXUI_API UPixUIViewPortWidget : public UUserWidget
{
    GENERATED_BODY() 

    /************************************************************************/
    //Begin~ UUserWidget interface
protected:
	virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual TSharedRef<SWidget> RebuildWidget() override;
    //End~ UUserWidget interface
    /************************************************************************/

public:
    /************************************************************************/
    //Begin~ delegate

    //open event delegate,called by window.open
    UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
    FPXWidgetOpenDelegate pixuiWinOpenDelegate;

    //confirm event delegate,called by window.confirm
    UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
    FPXWidgetConfirmDelegate pixuiWinConfirmDelegate;

    //promp event delegate,called by window.promp
    UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
    FPXWidgetPromptDelegate pixuiWinPrompDelegate;

    //End~ delegate
    /************************************************************************/
    

public:
    /*********************************UFUNCTION start *********************************/

    UFUNCTION(BlueprintCallable, Category = "UPixUIViewPortWidget")
    UPixUIWidget* GetPixuiWidget();

    UFUNCTION(BlueprintCallable, Category = "UPixUIViewPortWidget")
    int32 LoadPXViewFromUrl(const FString& fstr_Url);

    UFUNCTION(BlueprintCallable, Category = "UPixUIViewPortWidget")
    int32 LoadPXViewFromData(UPARAM(ref) TArray<uint8>& arry_Data, const FString& fstr_RootPath);

    UFUNCTION(BlueprintCallable, Category = "UPixUIViewPortWidget")
    int32 LoadPXViewFromGameAssetPath(const FString& fstr_FilePath);

    UFUNCTION(BlueprintCallable, Category = "UPixUIViewPortWidget")
    void PostPxMessage(const FString& fstr_Message);

    UFUNCTION(BlueprintCallable, Category = "UPixUIViewPortWidget")
    void Close();

    /*********************************UFUNCTION End   *********************************/

public:
    /*********************************deleage start *********************************/
    //for static bound UPixUIWidget window event and dispatch to UPixUIViewPortWidget delegate
	UFUNCTION()
    int OnPixuiOpenDelegate(const FString& fstr_Url, const FString& fstr_Name, const FString& fstr_Features,bool b_Replace);
	UFUNCTION()
    bool OnPixuiConfirmDelegate(const FString& fstr_ConfirmMsg);
	UFUNCTION()
    FString OnPixuiPromptDelegate(const FString& fstr_Tip, const FString& fstr_Default);
    /*********************************deleage end   *********************************/

private:
	TWeakObjectPtr<UPixUIWidget>& PixUIWidget() {
		return wptr_child_widget_pixui_;
	};
    //child UPixUIWidget
    TWeakObjectPtr<UPixUIWidget> wptr_child_widget_pixui_;
};
