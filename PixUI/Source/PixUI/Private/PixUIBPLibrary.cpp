// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PixUIBPLibrary.h"
#include "PixUI.h"

#include "UnrealEngine.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#endif

#include "PixUIDef.h"
#include "PixUILog.h"
#include "PixUILibMgr.h"
#include "PixImpMgr.h"
#include "PixImp/PixImpFont.h"
#include "PixUtil.h"
#include "PixUIInput.h"
#include "PixUIWidget.h"

#if DF_PIXUI_PROFILER
#include "PixUIProfiler/PxpResCount.h"
#include "PixUIProfiler/PxpTickCount.h"
#endif //DF_PIXUI_PROFILER


#define BeStartupRef				BeStartup()
#define WriteCachePathRef			WriteCachePath()
#define PixVersionRef				PixVersion()
#define BeDynamicFixFontSizeRef		BeDynamicFixFontSize()



UPixUIBPLibrary::UPixUIBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


bool UPixUIBPLibrary::PixUI_Startup(const FString& fstr_CachePathForWrite)
{
    if (BeStartupRef)
    {
        PxLog_Warning("PixUI Already Startup");
        return BeStartupRef;
    }

    //PixLibLoad Called first,such as dynamic load .so/.dll/.dylib file
    if (!PixUI::PixLibLoad())
    {
        PxLog_Error("UPixUIBPLibrary::PixUI_Startup PixLibLoad error");
        return false;
    }

    WriteCachePathRef = fstr_CachePathForWrite;
    if (WriteCachePathRef.IsEmpty())
    {
        WriteCachePathRef = FPaths::ProjectSavedDir();
#if PLATFORM_ANDROID
        WriteCachePathRef = IAndroidPlatformFile::GetPlatformPhysical().FileRootPath(*WriteCachePathRef);
#elif PLATFORM_IOS
        WriteCachePathRef = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*WriteCachePathRef);
#else
        WriteCachePathRef = FPaths::ConvertRelativePathToFull(WriteCachePathRef);
#endif
        //for mac or windows,create save dir
        if (!FPaths::DirectoryExists(WriteCachePathRef))
        {
            IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
            if (!PlatformFile.CreateDirectory(*WriteCachePathRef))
            {
                PxLog_Error("Create Pixui Cache dir error :%s",TCHAR_TO_UTF8(*WriteCachePathRef));
            }
        }

        //create Pixui Default cache directory
        WriteCachePathRef += TEXT("pixuicache/");
        if (!FPaths::DirectoryExists(WriteCachePathRef))
        {
            IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
            if (!PlatformFile.CreateDirectory(*WriteCachePathRef))
            {
                PxLog_Error("Create Pixui Cache dir error :%s", TCHAR_TO_UTF8(*WriteCachePathRef));
            }
        }
    }

	//write cache path add '/' at the end
	if (!WriteCachePathRef.EndsWith(TEXT("/")))
	{
		WriteCachePathRef += TEXT("/");
	}

    //pixui version
	TArray<FStringFormatArg> Args;

	FString fstr_plugin_version = DF_PIXUI_PLUGIN_VERSION;
	Args.Add(FStringFormatArg(fstr_plugin_version));

	FString fstr_core_version = UTF8_TO_TCHAR(px_plugin::pxVersion());
	Args.Add(FStringFormatArg(fstr_core_version));

	PixVersionRef = FString::Format(TEXT("plugin:{0} core:{1}"), Args);

    PxLog_Log("Pix module UPixUIBPLibrary PixUI_Startup   Version:%s", TCHAR_TO_UTF8(*PixVersionRef));

	PxLog_Log("Pix module UPixUIBPLibrary PixUI_Startup   platform:%s  platform code:%d    os version:%s   os version code:%f  RHIShaderPlatform:%d RHIShaderLevel:%d",
		TCHAR_TO_UTF8(*PixUI_Platform()),
		PixUI_PlatformCode(),
		TCHAR_TO_UTF8(*PixUI_PlatformOSVersion()),
		PixUI_PlatformOSVersionCode(),
		PixUI_RHIShaderPlatform(),
		PixUI_RHIShaderLevel());

#if !UE_BUILD_SHIPPING
    //debug trace
	px_plugin::pxCatchDebugTrace(true);
#endif

    //imp startup
    PixImpMgr::PixImpStartup();

    //pixui core startup
    PxLog_Log("Pix module UPixUIBPLibrary PixUI_Startup   cachepath:%s", TCHAR_TO_UTF8(*WriteCachePathRef));
	px_plugin::pxStartup(PixImpMgr::GetImpProxy(), TCHAR_TO_UTF8(*WriteCachePathRef), DF_PIXUI_UE4_AGENT);

    //widget startup
    UPixUIWidget::StartUp();

    BeStartupRef = true;
    return BeStartupRef;
}


bool UPixUIBPLibrary::PixUI_Shutdown()
{
    if (!BeStartupRef)
    {
        PxLog_Warning("shutdown px_plugin Waring,do not start up!!");
        return true;
    }

    //Widget Shutdown first
    UPixUIWidget::ShutDown();

    //pixui core library shutdown
    bool b_Ret = px_plugin::pxShutdown();

    if (b_Ret)
    {
        //ImpMgr shutdown
        PixImpMgr::PixImpShutdown();

        //lib UnLoad
        PixUI::PixLibUnLoad();

        PxLog_Log("UPixUIBPLibrary::PixUI_Shutdown");


		UPixUIInput::Destroy();

        //destroy log instance
        UPixUILog::Destroy();

        BeStartupRef = false;

        PixUtil::EngineGC(true);
    }
    else
    {
        PxLog_Error("shutdown px_plugin error");
    }
    return b_Ret;
}


FString UPixUIBPLibrary::PixUI_Version()
{
    return PixVersionRef;
}


FString UPixUIBPLibrary::PixUI_GetCachePath()
{
    return WriteCachePathRef;
}


void UPixUIBPLibrary::PixUI_ClearCacheFile()
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DeleteDirectoryRecursively(*WriteCachePathRef))
    {
        PxLog_Error("UPixUIBPLibrary::PixUI_ClearCacheFile error dir:%s", TCHAR_TO_UTF8(*WriteCachePathRef));
    }
    else
    {
        //create empty dir
        PlatformFile.CreateDirectory(*WriteCachePathRef);
    }
}


void UPixUIBPLibrary::Tick(float f_DeltaTime)
{
	CountFps(f_DeltaTime);

    if (BeStartupRef)
    {
#if DF_PIXUI_PROFILER
		PxpTickTotal item_total(e_tick_cost_tick_type_total);
#endif //DF_PIXUI_PROFILER

		{
			//imp tick
			PixImpMgr::PixImpTick(f_DeltaTime);
		}


		{
#if DF_PIXUI_PROFILER
			PxpTickTotal item_sub(e_tick_cost_tick_type_pxtime);
#endif //DF_PIXUI_PROFILER

			if (!PixUI_GetDebugNoCoreTick())
			{
				static int32 s_n_cur_tick_cont = 0;

				if (s_n_cur_tick_cont >= PixUI_GetCoreTickDura())
				{
					//lib tick
					//px_plugin::pxTimeTick(f_DeltaTime);	//removed
					s_n_cur_tick_cont = 0;
				}
				else
				{
					s_n_cur_tick_cont++;
				}
			}
		}

		{
#if DF_PIXUI_PROFILER
			PxpTickTotal item_sub(e_tick_cost_tick_type_wiget);
#endif //DF_PIXUI_PROFILER

			//widget tick
			UPixUIWidget::Tick(f_DeltaTime);
		}


		{
#if DF_PIXUI_PROFILER
			PxpTickTotal item_sub(e_tick_cost_tick_type_input);
#endif //DF_PIXUI_PROFILER

			//input tick
			UPixUIInput::Tick(f_DeltaTime);
		}
    }

#if DF_PIXUI_PROFILER
	if (PixUI_IsShowTick())
	{
		PxpTickCount::PrfPrfTotal_LogOutAll();
	}
#endif //DF_PIXUI_PROFILER
}


void UPixUIBPLibrary::PixUI_LogEnable(bool b_Enagble)
{
    if (BeStartupRef)
    {
        px_plugin::pxCatchDebugTrace(b_Enagble);
    }
    else
    {
        PxLog_Error("UPixUIBPLibrary::PixUI_LogEable error makesure startup first");
    }
}


bool UPixUIBPLibrary::PixUI_IsStartUp()
{
    return BeStartupRef;
}


void UPixUIBPLibrary::PixUI_AddSystemFont(const FString& fstr_FontName, const FString& fstr_FontPath)
{
    PixImpFont::AddFontPath(fstr_FontName, fstr_FontPath);
}


void UPixUIBPLibrary::PixUI_RemoveSystemFont(const FString& fstr_FontName)
{
    PixImpFont::RemoveFontPath(fstr_FontName);
}


void UPixUIBPLibrary::PixUI_SetDefaultFont(const FString& fstr_FontName)
{
    PixImpFont::SetDefaultFont(fstr_FontName);
}


void UPixUIBPLibrary::PixUI_SetDefaultFontSize(int n_FontSize)
{
    PixImpFont::SetDefaultFontSize(n_FontSize);
}


void UPixUIBPLibrary::PixUI_GetDefaultFont(FString& fstr_FontName)
{
    fstr_FontName = PixImpFont::GetDefaultFont();
}


void UPixUIBPLibrary::PixUI_GetDefaultFontSize(int& n_FontSize)
{
    n_FontSize = PixImpFont::GetDefaultFontSize();
}


bool UPixUIBPLibrary::PixUI_GetFontPath(const FString& fstr_FontName, FString& fstr_FontPath)
{
    return PixImpFont::GetFontPath(fstr_FontName, fstr_FontPath);
}


UPixUIViewPortWidget* UPixUIBPLibrary::PixUI_CreateViewPortWidget()
{
    UPixUIViewPortWidget* p_PixUIPortWidget = nullptr;
    if (GEngine)
    {
        UGameInstance* gameInstance = nullptr;
#if WITH_EDITOR
        UUnrealEdEngine* engine = Cast<UUnrealEdEngine>(GEngine);
        if (engine && engine->PlayWorld)
            gameInstance = engine->PlayWorld->GetGameInstance();
#else
        UGameEngine* engine = Cast<UGameEngine>(GEngine);
        if (engine) 
            gameInstance = engine->GameInstance;
#endif //WITH_EDITOR

        if (!gameInstance)
            PxLog_Warning("gameinstance missing");

        p_PixUIPortWidget = CreateWidget<UPixUIViewPortWidget>(gameInstance);
    }
    else
    {
        PxLog_Error("PixUI_AddToViewPortEx GEngine error");
    }
    return p_PixUIPortWidget;
}


UPixUIViewPortWidget* UPixUIBPLibrary::PixUI_CreateViewPortAddToCanvasEx(UCanvasPanel* p_ParentCanvas)
{
    return PixUI_CreateViewPortAddToCanvas(p_ParentCanvas, FAnchors(0.0f, 0.0f, 1.0f, 1.0f), FMargin(0.0f, 0.0f, 0.0f, 0.0f));
}


UPixUIViewPortWidget* UPixUIBPLibrary::PixUI_CreateViewPortAddToCanvas(UCanvasPanel* p_ParentCanvas, const FAnchors &anchors, const FMargin& margin)
{
    UPixUIViewPortWidget* p_PixUIPortWidget = PixUI_CreateViewPortWidget();
    if (p_PixUIPortWidget && p_ParentCanvas)
    {
        UCanvasPanelSlot* p_SlotPanle = p_ParentCanvas->AddChildToCanvas(p_PixUIPortWidget);
        p_SlotPanle->SetAnchors(anchors);
        p_SlotPanle->SetOffsets(margin);
    }
    return p_PixUIPortWidget;
}

UPixUIWidget* UPixUIBPLibrary::PixUI_CreateWidget()
{
    auto px_widget=NewObject<UPixUIWidget>();
    return px_widget;
}


UPixUIWidget* UPixUIBPLibrary::PixUI_CreateAddToCanvasEx(UCanvasPanel* p_ParentCanvas)
{
    return PixUI_CreateAddToCanvas(p_ParentCanvas, FAnchors(0.0f, 0.0f, 1.0f, 1.0f), FMargin(0.0f, 0.0f, 0.0f, 0.0f));
}


UPixUIWidget* UPixUIBPLibrary::PixUI_CreateAddToCanvas(UCanvasPanel* p_ParentCanvas, const FAnchors &anchors, const FMargin& margin)
{
    auto px_widget = PixUI_CreateWidget();
    if (px_widget && p_ParentCanvas)
    {
        UCanvasPanelSlot* p_SlotPanle = p_ParentCanvas->AddChildToCanvas(px_widget);
        p_SlotPanle->SetAnchors(anchors);
        p_SlotPanle->SetOffsets(margin);
    }
    return px_widget;
}

UPixUIWidget* UPixUIBPLibrary::PixUI_FindByWindowID(int windowID)
{
    return UPixUIWidget::FindPixUIWidgetByID(windowID);
}


UObject* UPixUIBPLibrary::PixUI_GetWindowSlotObject(int windowID, const FString& strTagId)
{
	UObject* pSlotObject = nullptr;
	UPixUIWidget* pWidget = PixUI_FindByWindowID(windowID);
	if (pWidget)
	{
		pSlotObject = pWidget->GetSlotObjectByTagId(strTagId);
	}
	return pSlotObject;
}


void UPixUIBPLibrary::PixUI_SetDynamicFixFontSize(bool b_OpenDynamicFix)
{
    BeDynamicFixFontSizeRef = b_OpenDynamicFix;
}


bool UPixUIBPLibrary::PixUI_IsDynamicFixFontSize()
{
    return BeDynamicFixFontSizeRef;
}


FString UPixUIBPLibrary::PixUI_GetMatRootPath()
{
	return MatRootPath() + PixUI_GetMatBasePath();
}


void UPixUIBPLibrary::PixUI_SetMatRootPath(const FString& fstr_root_path)
{
	if (!fstr_root_path.EndsWith(TEXT("/")))
	{
		MatRootPath() = FString::Printf(TEXT("%s/"), *fstr_root_path);
	}
	else
	{
		MatRootPath() = fstr_root_path;
	}
}


FString UPixUIBPLibrary::PixUI_GetMatBasePath()
{
	return MatBasePath();
}



void UPixUIBPLibrary::PixUI_SetMatBasePath(const FString& fstr_base_path)
{
	if (!fstr_base_path.EndsWith(TEXT("/")))
	{
		MatBasePath() = FString::Printf(TEXT("%s/"), *fstr_base_path);
	}
	else
	{
		MatBasePath() = fstr_base_path;
	}
}


void UPixUIBPLibrary::PixUI_ShowTick(bool b_show)
{
	BeShowTick() = b_show;

#if DF_PIXUI_PROFILER
	if (BeShowTick())
	{
		PxpTickCount::PrfTotal_ClearTick();
	}
#endif //DF_PIXUI_PROFILER
}


bool UPixUIBPLibrary::PixUI_IsShowTick()
{
	return BeShowTick();
}


void UPixUIBPLibrary::PixUI_ShowMousePos(bool b_show)
{
	BeShowMousePos() = b_show;
}

bool UPixUIBPLibrary::PixUI_IsShowMousePos()
{
	return BeShowMousePos();
}


bool UPixUIBPLibrary::PixUI_IsMobileUseTouchEvent()
{
	return BeMobileUseTouchEvent();
}

void UPixUIBPLibrary::PixUI_SetMobileUseTouchEvent(bool b_used)
{
	BeMobileUseTouchEvent() = b_used;
}

void UPixUIBPLibrary::PixUI_ShowResInfor()
{
#if DF_PIXUI_PROFILER
	ResItemCount::ShowResCount();
#endif //DF_PIXUI_PROFILER
}

void UPixUIBPLibrary::PixUI_OnBackground()
{
	if (BeStartupRef)
	{
		px_plugin::pxEnterBackground();
	}
}

void UPixUIBPLibrary::PixUI_OnForeground()
{
	if (BeStartupRef)
	{
		px_plugin::pxEnterForeground();
	}
}

FString UPixUIBPLibrary::PixUI_Platform()
{
#if PLATFORM_WINDOWS
	return TEXT("window");
#elif PLATFORM_ANDROID
	return TEXT("android");
#elif PLATFORM_IOS
	return TEXT("ios");
#elif PLATFORM_MAC
	return TEXT("mac");
#else
	return TEXT("other");
#endif
}

int UPixUIBPLibrary::PixUI_PlatformCode()
{
#if PLATFORM_WINDOWS
	return e_px_platform_code_win;
#elif PLATFORM_MAC
	return e_px_platform_code_mac;
#elif PLATFORM_IOS
	return e_px_platform_code_ios;
#elif PLATFORM_ANDROID
	return e_px_platform_code_android;
#else
	return e_px_platform_code_other;
#endif
}

FString UPixUIBPLibrary::PixUI_PlatformOSVersion()
{
	return PixUtil::OSversion();
}

float UPixUIBPLibrary::PixUI_PlatformOSVersionCode()
{
	return PixUtil::OSversionCode();
}


int UPixUIBPLibrary::PixUI_RHIShaderPlatform()
{
	return GMaxRHIShaderPlatform;
}


int UPixUIBPLibrary::PixUI_RHIShaderLevel()
{
	return GMaxRHIFeatureLevel;
}

bool UPixUIBPLibrary::PixUI_IsRHIShaderOpenGL()
{
	return IsOpenGLPlatform(GMaxRHIShaderPlatform);
}

bool UPixUIBPLibrary::PixUI_IsRHIShaderMetal()
{
	return IsMetalPlatform(GMaxRHIShaderPlatform);
}

bool UPixUIBPLibrary::PixUI_IsRHIShaderVulkan()
{
	return IsVulkanPlatform(GMaxRHIShaderPlatform);
}

bool UPixUIBPLibrary::PixUI_IsRHIShaderDX()
{
	return GMaxRHIShaderPlatform == SP_PCD3D_SM5 || 
#if ENGINE_MAJOR_VERSION < 5

		/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION < 24	//after 24.SP_PCD3D_SM4 / SP_PCD3D_ES2 change to ----> SP_PCD3D_SM4_REMOVED / SP_PCD3D_ES2_REMOVED
		GMaxRHIShaderPlatform == SP_PCD3D_SM4 ||
		GMaxRHIShaderPlatform == SP_PCD3D_ES2 ||
#endif //ENGINE_MINOR_VERSION < 24
		/////////////////////////////////////////////////////////////////////for ue4

#endif //ENGINE_MAJOR_VERSION < 5
		GMaxRHIShaderPlatform == SP_PCD3D_ES3_1;
}


bool UPixUIBPLibrary::PixUI_IsRHIShaderOpenGLES2()
{
#if ENGINE_MAJOR_VERSION < 5

	/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION < 25	//after 25.ERHIFeatureLevel::ES2 change to ----> ERHIFeatureLevel::ES2_REMOVED
	if (PixUI_IsRHIShaderOpenGL())
	{
		if (GMaxRHIFeatureLevel == ERHIFeatureLevel::ES2)
		{
			return true;
		}
	}
#endif //ENGINE_MINOR_VERSION < 25
	/////////////////////////////////////////////////////////////////////for ue4

#endif //ENGINE_MAJOR_VERSION < 5
	return false;
}


bool UPixUIBPLibrary::PixUI_IsOsBit64()
{
	return sizeof(void*) == sizeof(int64);
}


bool UPixUIBPLibrary::PixUI_IsOsBit32()
{
	return sizeof(void*) == sizeof(int32);
}


float UPixUIBPLibrary::PixUI_CurrentGameFPS()
{
	return CurFps();
}


void UPixUIBPLibrary::PixUI_SetCoreTickDura(int32 n_duar_count)
{
	CoreTickDaru() = n_duar_count;
}


int32 UPixUIBPLibrary::PixUI_GetCoreTickDura()
{
	return CoreTickDaru();
}


void UPixUIBPLibrary::PixUI_SetPaintDura(int32 n_duar_count)
{
	PaintDaru() = n_duar_count;
}


int32 UPixUIBPLibrary::PixUI_GetPaintDura()
{
	return PaintDaru();
}


void UPixUIBPLibrary::PixUI_SetDebugTickDelay(float f_delay)
{
	DebugTickDelayTime() = f_delay;
}


float UPixUIBPLibrary::PixUI_GetDebugTickDelay()
{
	return DebugTickDelayTime();
}


void UPixUIBPLibrary::PixUI_SetDebugCPURunTime(int32 n_time)
{
	DebugCPUTRunTime() = (uint32)n_time;
}

int32 UPixUIBPLibrary::PixUI_GetDebugCPURunTime()
{
	return (int32)DebugCPUTRunTime();
}


void UPixUIBPLibrary::PixUI_SetDebugRetainDraw(bool b_retain)
{
	BeDebugRetainDraw() = b_retain;
}

bool UPixUIBPLibrary::PixUI_GetDebugRetainDraw()
{
	return BeDebugRetainDraw();
}


void UPixUIBPLibrary::PixUI_SetDebugNoCoreTick(bool b_no_tick)
{
	BeDebugNoCoreTick() = b_no_tick;
}

bool UPixUIBPLibrary::PixUI_GetDebugNoCoreTick()
{
	return BeDebugNoCoreTick();
}


bool& UPixUIBPLibrary::BeShowTick()
{
	static bool b_show_tick_s = false;
	return b_show_tick_s;
}


bool& UPixUIBPLibrary::BeShowMousePos()
{
	static bool b_show_mouse_pos_s = false;
	return b_show_mouse_pos_s;
}


bool& UPixUIBPLibrary::BeStartup()
{
    static bool b_Startup_s = false;
    return b_Startup_s;
}


FString& UPixUIBPLibrary::WriteCachePath()
{
    static FString fstr_WriteCachePath_s;
    return fstr_WriteCachePath_s;
}


FString& UPixUIBPLibrary::PixVersion()
{
    static FString fstr_PixVersion_s;
    return fstr_PixVersion_s;
}



bool& UPixUIBPLibrary::BeDynamicFixFontSize()
{
    /*
    ue4 slate ui When calculating the drawn font, 
    the drawn text size will be calculated according to the scale of the geometry (4 rounded to 5).
    There will be a discrepancy between the measured text size and the actual drawn size
    By default, we will enable the size of the fix it
    However, there may be changes or the first time the widget enters an uninitialized geometry.
    At this time, the font size measured for the first time is still different.
    b_DynamicFixFontSize It is used to dynamically calculate font drawing scaling when opening drawing to fix (this method has a certain performance consumption)
    no need to open it if there is no special requirement
    */
    static bool b_DynamicFixFontSize = false;
    return b_DynamicFixFontSize;
}


FString GetPixMatDefaultRootPath()
{
	if (UPixUIBPLibrary::PixUI_IsRHIShaderOpenGLES2())
	{
		return DF_MAT_ROOT_PATH_ES2;
	}
	return DF_MAT_ROOT_PATH;
}


FString& UPixUIBPLibrary::MatRootPath()
{
	static FString fstr_mat_root_path = GetPixMatDefaultRootPath();
	return fstr_mat_root_path;
}

FString GetPixMatDefaultBasePath()
{
	if (UPixUIBPLibrary::PixUI_IsRHIShaderOpenGLES2())
	{
		return DF_MAT_BASE_PATH_HEAD_ES2;
	}
	return DF_MAT_BASE_PATH_HEAD;
}


FString& UPixUIBPLibrary::MatBasePath()
{
	static FString fstr_mat_base_path = GetPixMatDefaultBasePath();
	return fstr_mat_base_path;
}


bool& UPixUIBPLibrary::BeMobileUseTouchEvent()
{
	static bool b_mobile_use_touch_event = false;
	return b_mobile_use_touch_event;
}


float& UPixUIBPLibrary::DebugTickDelayTime()
{
	static float f_debug_delay_time = 0.00000f;
	return f_debug_delay_time;
}


uint32& UPixUIBPLibrary::DebugCPUTRunTime()
{
	static uint32 un_debug_cpu_time = 0;
	return un_debug_cpu_time;
}

bool& UPixUIBPLibrary::BeDebugRetainDraw()
{
	static bool b_debug_reatain_draw = false;
	return b_debug_reatain_draw;
}


bool& UPixUIBPLibrary::BeDebugNoCoreTick()
{
	static bool b_debug_no_core_tick = false;
	return b_debug_no_core_tick;
}


uint32& UPixUIBPLibrary::CoreTickDaru()
{
	static uint32 un_core_tick_daru = 0;
	return un_core_tick_daru;
}


uint32& UPixUIBPLibrary::PaintDaru()
{
	static uint32 un_paint_daru = 0;
	return un_paint_daru;
}


float& UPixUIBPLibrary::CurFps()
{
	static float f_cur_fps = 30.0f;
	return f_cur_fps;
}


void UPixUIBPLibrary::CountFps(float f_DeltaTime)
{
	static int32 s_fps_count = 0;
	if (s_fps_count > 5)
	{
		CurFps() = 1.0f / f_DeltaTime;
		s_fps_count = 0;
	}
	else
	{
		s_fps_count++;
	}
}