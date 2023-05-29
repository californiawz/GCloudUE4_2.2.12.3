// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UMG.h"

#include "PixUIViewPortWidget.h"
#include "PixUIWidget.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "PixUIBPLibrary.generated.h"


/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class PIXUI_API UPixUIBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	////////////////////////////////// module mgr start ////////////////////////////////////////

	//pixui plugin startup,Make sure to call this interface first
	//fstr_CachePathForWrite : for pixui core to write cache files and download url files
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI Startup ", Keywords = "PixUI Startup"), Category = "PixUI")
		static bool PixUI_Startup(const FString& fstr_CachePathForWrite);

	//shutdown pixui and Release all resources
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI Shutdown ", Keywords = "PixUI Shutdown"), Category = "PixUI")
		static bool PixUI_Shutdown();

	//get pixui version and core version
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI Version ", Keywords = "PixUI Version"), Category = "PixUI")
		static FString PixUI_Version();

	//get pixui cache path what set when call PixUI_Startup
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI GetCachePath ", Keywords = "PixUI GetCachePath"), Category = "PixUI")
		static FString PixUI_GetCachePath();

	//clear cache files
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI ClearCacheFile ", Keywords = "PixUI ClearCacheFile"), Category = "PixUI")
		static void PixUI_ClearCacheFile();

	//do or not out put log information
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI LogEnable ", Keywords = "PixUI LogEnable"), Category = "PixUI")
		static void PixUI_LogEnable(bool b_Enagble);

	//Check if the switch is StartUp
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsStartUp ", Keywords = "PixUI PixUI_IsStartUp"), Category = "PixUI")
		static bool PixUI_IsStartUp();

	//time tick call from FPixUIModule
	static void Tick(float f_DeltaTime);
	////////////////////////////////// module mgr end ////////////////////////////////////////


	////////////////////////////////font start//////////////////////////////////////////
	/*
	add font to pixui

	fstr_FontName: font name, e.g:gamefont
	fstr_FontPath: Can be absolute path and asset path, e.g: /usr/font/my.ttf  d://font/my.ttf    asste path:/res/font/my_my
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI AddSystemFont ", Keywords = "PixUI AddSystemFont"), Category = "PixUI")
		static void PixUI_AddSystemFont(const FString& fstr_FontName, const FString& fstr_FontPath);

	//remove font
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI RemoveSystemFont ", Keywords = "PixUI RemoveSystemFont"), Category = "PixUI")
		static void PixUI_RemoveSystemFont(const FString& fstr_FontName);

	//set default font
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI SetDefaultFont ", Keywords = "PixUI SetDefaultFont"), Category = "PixUI")
		static void PixUI_SetDefaultFont(const FString& fstr_FontName);

	//set default font size
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI SetDefaultFontSize ", Keywords = "PixUI SetDefaultFontSize"), Category = "PixUI")
		static void PixUI_SetDefaultFontSize(const int n_FontSize);

	//get default font
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI GetDefaultFont ", Keywords = "PixUI GetDefaultFont"), Category = "PixUI")
		static void PixUI_GetDefaultFont(FString& fstr_FontName);

	//get default font size
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI GetDefaultFontSize ", Keywords = "PixUI GetDefaultFontSize"), Category = "PixUI")
		static void PixUI_GetDefaultFontSize(int& n_FontSize);

	//get font path by font name
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI GetFontPath ", Keywords = "PixUI GetFontPath"), Category = "PixUI")
		static bool PixUI_GetFontPath(const FString& fstr_FontName, FString& fstr_FontPath);
	////////////////////////////////font end//////////////////////////////////////////


	//////////////////////////////////View port widget start////////////////////////////////////////
	//create pixui ViewPortWidget userwidget
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_CreateViewPortWidget ", Keywords = "PixUI PixUI_CreateViewPortWidget"), Category = "PixUI")
		static UPixUIViewPortWidget* PixUI_CreateViewPortWidget();

	//create pixui ViewPortWidget and to to canvas
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_CreateViewPortAddToCanvasEx ", Keywords = "PixUI PixUI_CreateViewPortAddToCanvasEx"), Category = "PixUI")
		static UPixUIViewPortWidget* PixUI_CreateViewPortAddToCanvasEx(UCanvasPanel* p_ParentCanvas);

	//create pixui ViewPortWidget and to to canvas
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_CreateViewPortAddToCanvas ", Keywords = "PixUI PixUI_CreateViewPortAddToCanvas"), Category = "PixUI")
		static UPixUIViewPortWidget* PixUI_CreateViewPortAddToCanvas(UCanvasPanel* p_ParentCanvas, const FAnchors& anchors, const FMargin& margin);

	//create pixui Widget userwidget
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_CreateWidget ", Keywords = "PixUI PixUI_CreateWidget"), Category = "PixUI")
		static UPixUIWidget* PixUI_CreateWidget();

	//create pixui Widget and to to canvas
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_CreateAddToCanvasEx ", Keywords = "PixUI PixUI_CreateAddToCanvasEx"), Category = "PixUI")
		static UPixUIWidget* PixUI_CreateAddToCanvasEx(UCanvasPanel* p_ParentCanvas);

	//create pixui Widget and to to canvas
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_CreateAddToCanvas ", Keywords = "PixUI PixUI_CreateAddToCanvas"), Category = "PixUI")
		static UPixUIWidget* PixUI_CreateAddToCanvas(UCanvasPanel* p_ParentCanvas, const FAnchors& anchors, const FMargin& margin);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_FindByWindowID ", Keywords = "PixUI PixUI_FindByWindowID"), Category = "PixUI")
		static UPixUIWidget* PixUI_FindByWindowID(int windowID);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetWindowSlotObject ", Keywords = "PixUI PixUI_GetWindowSlotObject"), Category = "PixUI")
		static UObject* PixUI_GetWindowSlotObject(int windowID, const FString& strTagId);

	//////////////////////////////////View port widget end////////////////////////////////////////


	////////////////////////////////// util //////////////////////////////////////////////////////
	/*
	Whether to enable dynamic font length measurement
	Because when the window size changes dynamically
	it will cause the engine scale rate to change, and the font length measurement will also change
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetDynamicFixFontSize ", Keywords = "PixUI PixUI_SetDynamicFixFontSize"), Category = "PixUI")
		static void PixUI_SetDynamicFixFontSize(bool b_OpenDynamicFix);

	/*
	do or not dynamic font length measurement
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsDynamicFixFontSize ", Keywords = "PixUI PixUI_IsDynamicFixFontSize"), Category = "PixUI")
		static bool PixUI_IsDynamicFixFontSize();
	////////////////////////////////// util //////////////////////////////////////////////////////


	////////////////////////////////// pixui mat path start////////////////////////////////////////
	/*
	get pixui mat root path
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetMatRootPath ", Keywords = "PixUI PixUI_SetMatRootPath"), Category = "PixUI")
		static FString PixUI_GetMatRootPath();

	/*
	set pixui mat root path
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetMatRootPath ", Keywords = "PixUI PixUI_SetMatRootPath"), Category = "PixUI")
		static void PixUI_SetMatRootPath(const FString& fstr_root_path);


	/*
	get pixui mat base path
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetMatBasePath ", Keywords = "PixUI PixUI_GetMatBasePath"), Category = "PixUI")
		static FString PixUI_GetMatBasePath();

	/*
	set pixui mat base path
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetMatBasePath ", Keywords = "PixUI PixUI_SetMatBasePath"), Category = "PixUI")
		static void PixUI_SetMatBasePath(const FString& fstr_base_path);

	////////////////////////////////// pixui mat path end  ////////////////////////////////////////

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_ShowTick ", Keywords = "PixUI PixUI_ShowTick"), Category = "PixUI")
		static void PixUI_ShowTick(bool b_show);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsShowTick ", Keywords = "PixUI PixUI_IsShowTick"), Category = "PixUI")
		static bool PixUI_IsShowTick();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_ShowMousePos ", Keywords = "PixUI PixUI_ShowMousePos"), Category = "PixUI")
		static void PixUI_ShowMousePos(bool b_show);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsShowMousePos ", Keywords = "PixUI PixUI_IsShowMousePos"), Category = "PixUI")
		static bool PixUI_IsShowMousePos();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsMobileUseTouchEvent ", Keywords = "PixUI PixUI_IsMobileUseTouchEvent"), Category = "PixUI")
		static bool PixUI_IsMobileUseTouchEvent();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetMobileUseTouchEvent ", Keywords = "PixUI PixUI_SetMobileUseTouchEvent"), Category = "PixUI")
		static void PixUI_SetMobileUseTouchEvent(bool b_used);
		
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_ShowResInfor ", Keywords = "PixUI PixUI_ShowResInfor"), Category = "PixUI")
		static void PixUI_ShowResInfor();
		
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_Platform ", Keywords = "PixUI PixUI_Platform"), Category = "PixUI")
		static FString PixUI_Platform();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_PlatformCode ", Keywords = "PixUI PixUI_PlatformCode"), Category = "PixUI")
		static int PixUI_PlatformCode();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_PlatformOSVersion ", Keywords = "PixUI PixUI_PlatformOSVersion"), Category = "PixUI")
		static FString PixUI_PlatformOSVersion();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_PlatformOSVersionCode ", Keywords = "PixUI PixUI_PlatformOSVersionCode"), Category = "PixUI")
		static float PixUI_PlatformOSVersionCode();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_RHIShaderPlatform ", Keywords = "PixUI PixUI_RHIShaderPlatform"), Category = "PixUI")
		static int PixUI_RHIShaderPlatform();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_RHIShaderLevel ", Keywords = "PixUI PixUI_RHIShaderLevel"), Category = "PixUI")
		static int PixUI_RHIShaderLevel();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsRHIShaderOpenGL ", Keywords = "PixUI PixUI_IsRHIShaderOpenGL"), Category = "PixUI")
		static bool PixUI_IsRHIShaderOpenGL();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsRHIShaderMetal ", Keywords = "PixUI PixUI_IsRHIShaderMetal"), Category = "PixUI")
		static bool PixUI_IsRHIShaderMetal();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsRHIShaderVulkan ", Keywords = "PixUI PixUI_IsRHIShaderVulkan"), Category = "PixUI")
		static bool PixUI_IsRHIShaderVulkan();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsRHIShaderDX ", Keywords = "PixUI PixUI_IsRHIShaderDX"), Category = "PixUI")
		static bool PixUI_IsRHIShaderDX();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsRHIShaderOpenGLES2 ", Keywords = "PixUI PixUI_IsRHIShaderOpenGLES2"), Category = "PixUI")
		static bool PixUI_IsRHIShaderOpenGLES2();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsOsBit64 ", Keywords = "PixUI PixUI_IsOsBit64"), Category = "PixUI")
		static bool PixUI_IsOsBit64();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_IsOsBit32 ", Keywords = "PixUI PixUI_IsOsBit32"), Category = "PixUI")
		static bool PixUI_IsOsBit32();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_CurrentGameFPS ", Keywords = "PixUI PixUI_CurrentGameFPS"), Category = "PixUI")
		static float PixUI_CurrentGameFPS();

	//tick
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetCoreTickDura ", Keywords = "PixUI PixUI_SetCoreTickDura"), Category = "PixUI")
		static void PixUI_SetCoreTickDura(int32 n_duar_count);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetCoreTickDura ", Keywords = "PixUI PixUI_GetCoreTickDura"), Category = "PixUI")
		static int32 PixUI_GetCoreTickDura();

	//paint
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetPaintDura ", Keywords = "PixUI PixUI_SetPaintDura"), Category = "PixUI")
		static void PixUI_SetPaintDura(int32 n_duar_count);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetPaintDura ", Keywords = "PixUI PixUI_GetPaintDura"), Category = "PixUI")
		static int32 PixUI_GetPaintDura();



	//for debug test
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetDebugTickDelay ", Keywords = "PixUI PixUI_SetDebugTickDelay"), Category = "PixUI")
		static void PixUI_SetDebugTickDelay(float f_delay);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetDebugTickDelay ", Keywords = "PixUI PixUI_GetDebugTickDelay"), Category = "PixUI")
		static float PixUI_GetDebugTickDelay();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetDebugCPURunTime ", Keywords = "PixUI PixUI_SetDebugCPURunTime"), Category = "PixUI")
		static void PixUI_SetDebugCPURunTime(int32 n_time);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetDebugCPURunTime ", Keywords = "PixUI PixUI_GetDebugCPURunTime"), Category = "PixUI")
		static int32 PixUI_GetDebugCPURunTime();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetDebugRetainDraw ", Keywords = "PixUI PixUI_SetDebugRetainDraw"), Category = "PixUI")
		static void PixUI_SetDebugRetainDraw(bool b_retain);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetDebugRetainDraw ", Keywords = "PixUI PixUI_GetDebugRetainDraw"), Category = "PixUI")
		static bool PixUI_GetDebugRetainDraw();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_SetDebugNoCoreTick ", Keywords = "PixUI PixUI_SetDebugNoCoreTick"), Category = "PixUI")
		static void PixUI_SetDebugNoCoreTick(bool b_no_tick);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUI PixUI_GetDebugNoCoreTick ", Keywords = "PixUI PixUI_GetDebugNoCoreTick"), Category = "PixUI")
		static bool PixUI_GetDebugNoCoreTick();

public:
	static void PixUI_OnBackground();
	static void PixUI_OnForeground();

protected:
	static bool& BeShowTick();
	static bool& BeShowMousePos();
    static bool& BeStartup();
    static FString& WriteCachePath();
    static FString& PixVersion();
    static bool& BeDynamicFixFontSize();
	static FString& MatRootPath();
	static FString& MatBasePath();
	static bool& BeMobileUseTouchEvent();
	static float& DebugTickDelayTime();
	static uint32& DebugCPUTRunTime();
	static bool& BeDebugRetainDraw();
	static bool& BeDebugNoCoreTick();
	static uint32& CoreTickDaru();
	static uint32& PaintDaru();
	static float& CurFps();
	static void CountFps(float f_DeltaTime);
};
