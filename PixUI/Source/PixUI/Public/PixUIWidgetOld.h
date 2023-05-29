/**************************************************

**** @file:     PixUIWidgetOldOld.h

**** @brief:    PixUI widget reflection UIcontrol, This UI control can be dragged and dropped visually in the UMG editor

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#include "CoreMinimal.h"


#ifdef DF_PX_USE_OLD_WIDGET


#include "Components/Widget.h"
//#include "Runtime/Core/Public/HAL/ThreadingBase.h"
#include "HAL/ThreadingBase.h"

#include "PixUIInput.h"
#include "PixUIWidget.h"

#include "PixUIWidgetOld.generated.h"

/**
 * 
 */
class SPixPaintWidgetOld;

//UCLASS()
class PIXUI_API UPixUIWidgetOld : public UWidget, public IPluginWindow, public IPxInputProxy
{
    GENERATED_BODY()

public:
    UPixUIWidgetOld(const FObjectInitializer& ObjectInitializer);
    
#if WITH_EDITOR
public:
    /************************************************************************/
    //~ Begin UWidget Interface
    virtual const FText GetPaletteCategory() override;
#endif //WITH_EDITOR

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    //~ End UWidget Interface
    /************************************************************************/


public:
    /************************************************************************/
    //~ Begin UVisual Interface
    virtual void ReleaseSlateResources(bool b_ReleaseChildren) override;
    //~ End UVisual Interface
    /************************************************************************/

    /************************************************************************/
    //~ Begin UObject Interface
    virtual void BeginDestroy() override;
    //~ End UObject Interface
    /************************************************************************/

public:
    /*********************************UFUNCTION start *********************************/
    
    //open page form url; such as : http://test.demo.html or /usr/tmp/demo.html or d://tmp//demo.html
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    int32 OpenPageFromUrl(const FString& fstr_Url);

    //open page form data
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    int32 OpenPageFromData(UPARAM(ref) TArray<uint8>& arry_Data, const FString& fstr_BasePath);

    //open page form game asset path,such as /Res/demo.html
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    int32 OpenPageFromGameAssetPath(const FString& fstr_File);

    //post string message to script
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    void PostPxMessage(const FString& fstr_Message);

    //close this page,and Can reopen a new page
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    void ClosePage();

    //Destroy this page,and Can not reopen a new page
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    void DestroyPage();

	//auto deal with transform event
	UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
	void SetAutoTransform(bool b_auto);

	UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
	int32 GetPxWinId();

	UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
	int32 GetCustomLayer();

	UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
	void SetCustomLayer(int32 n_in_layer);

    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    void CreateScriptGlobal(const FString& name);
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    void SetScriptGlobalNumber(const FString& name,const FString& key, float num);
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    void SetScriptGlobalString(const FString& name,const FString& key,const FString& str);
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    void SetScriptGlobalBoolean(const FString& name,const FString& key, bool v);
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    float GetScriptGlobalNumber(const FString& name,const FString& key);
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    FString GetScriptGlobalString(const FString& name,const FString& key);
    UFUNCTION(BlueprintCallable, Category = "UPixUIWidgetOld")
    bool GetScriptGlobalBoolean(const FString& name,const FString& key);
    /*********************************UFUNCTION End   *********************************/

public:

	/*********************************Period start *********************************/
	UPROPERTY(BlueprintAssignable, Category = Events)
	FPXWidgetOnPeriodDelegate OnCloseDelegate;

	UPROPERTY(BlueprintAssignable, Category = Events)
	FPXWidgetOnPeriodDelegate OnDestroyDelegate;
	/*********************************Period end *********************************/


    /*********************************deleage start *********************************/
    //loaded event,success or fiald
	UPROPERTY(BlueprintAssignable, Category = Events)
	FPXWidgetOnLoadDelegate pixuiOnLoadedDelegate;

	//script state init event
	UPROPERTY(BlueprintAssignable, Category = Events)
	FPXWidgetOnScriptStateInitDelegate pixuiOnScriptStateInitDelegate;

	UPROPERTY(BlueprintAssignable, Category = Events)
	FPXWidgetOnInternalError pixuiOnInternalErrorDelegate;

    //open event delegate,called by window.open
    UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
    FPXWidgetOpenDelegate pixuiWinOpenDelegate;

    //close event delegate,called by window.close
    UPROPERTY(BlueprintAssignable, Category = Events)
    FPXWidgetCloseDelegate pixuiWinCloseDelegate;

    //alert event delegate,called by window.alert
    UPROPERTY(BlueprintAssignable, Category = Events)
    FPXWidgetAlertDelegate pixuiWinAlertDelegate;

    //confirm event delegate,called by window.confirm
    UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
    FPXWidgetConfirmDelegate pixuiWinConfirmDelegate;

    //promp event delegate,called by window.promp
    UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
    FPXWidgetPromptDelegate pixuiWinPrompDelegate;

    //transform event delegate,called by window.moveby/window.moveto ...,event type see EPXViewEvent
    UPROPERTY(BlueprintAssignable, Category = Events)
    FPXWidgetTransformDelegate pixuiWinTransformDelegate;

    //message event delegate,called by window.postmessage
    UPROPERTY(BlueprintAssignable, Category = Events)
    FPXWidgetMessageDelegate pixuiWinMessageDelegate;

	UPROPERTY(BlueprintAssignable, Category = Events)
	FPXWidgetAppForegroundDelegate pixuiWin_app_foreground_delegate;

	UPROPERTY(BlueprintAssignable, Category = Events)
	FPXWidgetAppBackgroundDelegate pixuiWin_app_background_delegate;
    /*********************************deleage end   *********************************/

public:
	
    /************************************************************************/
    //~ Begin IPluginWindow Interface

	/*
	load complete event
	
	@ pszUrl: load path
	@ bSuccess: success or failed
	
	@ return: 
	*/
	virtual void OnLoadComplete(const char* pszUrl, const bool bSuccess) override;

	/*
	scriptstate init event
	
	@ return: 
	*/
	virtual void OnScriptStateInit() override;

	virtual void OnInternalError(int error, const char* msg) override;

    /*
    open new page event form script by window.open
    
    @ psz_Url:          page url
    @ psz_Name:         windows name
    @ psz_Features:     page features
    @ b_Replace:        be or not replace current window
    
    @ return: 
    */
    virtual int OnOpen(const char* psz_Url = "", const char* psz_Name = "", const char* psz_Features = "", bool b_Replace = false) override;
    
    /*
    close page event form script by window.close,async call
    
    @ return: 
    */
    virtual void OnClose() override;

    /*
    alert event form script by window.alert,async call
    
    @ return: 
    */
    virtual void OnAlert(const char* psz_Text) override;

    /*
    confirm event form script by window.confirm,sync call will be wait until return

    @ return:
    */
    virtual bool OnConfirm(const char* psz_Message) override;

    /*
    prompt event form script by window.prompt,sync call will be wait until return
    
    @ psz_Text:         input tip text
    @ psz_DefaultText:  input box default text
    
    @ return: input content
    */
    virtual const char* OnPrompt(const char* psz_Text, const char* psz_DefaultText) override;

    /*
    transform event form script by window.moveby/window,moveto/window.resizeby/window.resizeto/window.scrollby/window.scrollto

    @ return: 
    */
    virtual void OnMoveBy(const int n_XposMoveBy, const int n_YposMoveBy) override;
    virtual void OnMoveTo(const int n_XposMoveTo, const int n_YposMoveTo) override;
    virtual void OnResizeBy(const int n_OffsetWidth, const  int n_OffsetHeight) override;
    virtual void OnResizeTo(const int n_NewWidth, const int n_NewHeight) override;
    virtual void OnScrollBy(const int n_OffsetXpos, const int n_OffsetYpos) override;
    virtual void OnScrollTo(const int n_NewXpos, const int n_NewYpos) override;

    /*
    message event form script by window.postMessage

    @ psz_Message:  message information,async call
    
    @ return: 
    */
    virtual void OnMessage(const char* psz_Message) override;

    /*
    Activate input event 
    
    @ e_KeyboardType:   keyboard type
    @ psz_DefaultText:  default text
    @ psz_HintText:     hint text
    
    @ return: be or not support
    */
    virtual bool OnActivateInput(pixui::EKeyboardType e_KeyboardType, const char* psz_DefaultText, const char* psz_HintText) override;

    /*
    deativate input event

    @ return: be or not support
    */
    virtual bool OnDeativateInput() override;

    /*
    Set whether window the event pass
    @ b_pass: be or not window the event pass
    @ return: be or not support
    */
    virtual void SetWindowPass(bool b_pass) override;

    /*
    Set window priority
    @ n_priority: window priority
    @ return: be or not support
    */
    virtual void SetWindowPriority(int n_priority) override;
    //~ End IPluginWindow Interface
    /************************************************************************/

public:
	TSharedPtr<SWidget> GetWidget();


	void OnAppForeground();
	void OnAppBackground();

	void ShowWidgetInfor();

	px_ptr GetContextPtr();

private:
    void OnTick(float InDeltaTime);

protected:
    //broadcast window event
    void BroadcastEvent(const int n_PxEvent, const int32 n_Param1, const int32 n_Param2, const FString& fstr_Msg);

    //
    bool IsPixViewValid();

    //get pixui view handle
    px_ptr ViewHandle();

public:
    /************************************************************************/
    //~ Begin static UPixUIWidgetOld manager

    //called when pixui plugin startup
    static void StartUp();

    //called form pixui plugin tick
    static void Tick(float InDeltaTime);

    //called when pixui plugin shutdown
    static void ShutDown();

	//find by WindowId
	static UPixUIWidgetOld* FindPixUIWidgetOldByID(int64 windowId);

	static void ShowWidgetsInfor();

protected:
    //when UPixUIWidgetOld create, add to PixUIWidgetOlds
    static void AddPixUIWidgetOld(TWeakObjectPtr<UPixUIWidgetOld> wptr_PixUIWidgetOld);

    //when UPixUIWidgetOld destroy remove form PixUIWidgetOlds
    static void RemovePixUIWidgetOld(TWeakObjectPtr<UPixUIWidgetOld> wptr_PixUIWidgetOld);
	
    //UPixUIWidgetOld manager array for safe use
    static TArray<TWeakObjectPtr<UPixUIWidgetOld>>& PixUIWidgetOlds();

	static uint32& PixUIWidgetOldTotalCount();

public:
	static void NotifyAppForeground();

	static void NotifyAppBackground();

    //~ End static static UPixUIWidgetOld manager
    /************************************************************************/


	/************************************************************************/
	//~ Begin IPxInputProxy Interface
	virtual TSharedPtr<SWidget> GetSlateWidget() override;
	virtual void OnInputText(const FString& fstr_new_input, const bool b_end_input, const bool b_lost_focus, const bool b_replace) override;
	//~ End IPxInputProxy Interface
	/************************************************************************/

private:
    //SPixPaintWidget for draw page
    TSharedPtr<SPixPaintWidgetOld> sptr_SPixPaintWidget_;

    //script event information
    struct ST_PX_EVENT
    {
        //close type based on EPXViewEvent::em_px_event_count
        static const int n_type_close = 1 + (int)(EPXViewEvent::em_px_event_count);

        static const int n_type_alert = 1 + n_type_close;

        static const int n_type_message = 1 + n_type_alert;

        int n_Type;         //event type
        int n_Param1;       //param 1
        int n_Param2;       //param 2
        FString fstr_Msg;   //message

        ST_PX_EVENT() {
            n_Type = n_type_close - 1;
            n_Param1 = -1;
            n_Param2 = -1;
        }
    };
    //mutex for events array
    FCriticalSection     fcs_Mutex_;

    //events array
    TArray<ST_PX_EVENT>  array_Event_;

    //prompt result value for store
    FString fstr_prompt_ret_;

	//auto deal with event moveto moveby sizeto sizeby
	bool b_auto_transform_;
};


#endif // DF_PX_USE_OLD_WIDGET