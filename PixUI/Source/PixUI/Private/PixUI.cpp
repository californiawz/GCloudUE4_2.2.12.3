// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PixUI.h"

#include "Projects.h"
#include "Runtime/Core/Public/Containers/Ticker.h"
#include "Misc/CoreDelegates.h"

#include "PixUIBPLibrary.h"

#include "PixUIDef.h"
#include "PixUILog.h"

#define LOCTEXT_NAMESPACE "FPixUIModule"        //ue4 macro

#if !defined(DF_DY_LOAD_PX) || (!DF_DY_LOAD_PX)
//static load model WINDOWS and Mac need dynamic load lib file
    #if PLATFORM_WINDOWS || PLATFORM_MAC
        #include "PixLibEx/PixDyLib.h"
    #endif //PLATFORM_WINDOWS || PLATFORM_MAC
#endif //!defined(DF_DY_LOAD_PX) || (!DF_DY_LOAD_PX)


#if DF_PIXUI_PROFILER
#include "PixUIProfiler/PxpTickCount.h"
#endif



void FPixUIModule::StartupModule()
{

	// register delegate if not registered
	if (!m_hResumeHandle.IsValid())
	{
		m_hResumeHandle = FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddRaw(this, &FPixUIModule::HandleApplicationHasEnteredForeground);
	}

	if (!m_hPauseHandle.IsValid())
	{
		m_hPauseHandle = FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddRaw(this, &FPixUIModule::HandleApplicationWillEnterBackground);
	}


    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if !defined(DF_DY_LOAD_PX) || (!DF_DY_LOAD_PX)
    #if PLATFORM_WINDOWS || PLATFORM_MAC
        //window and mac need PublicDelayLoadDLLs,so must be call dy load here
        px_plugin::PxDyLibLoad();
    #endif //PLATFORM_WINDOWS || PLATFORM_MAC
#endif //!defined(DF_DY_LOAD_PX) || (!DF_DY_LOAD_PX)

#if UE_EDITOR
    //shiping do not call PixUI_Startup here,just for test
    //UPixUIBPLibrary::PixUI_Startup(TEXT(""));
#endif //UE_EDITOR
}

#if DF_PIXUI_PROFILER
static float f_count_s = 1.0f;
static int32 n_count_s = 1.0f;
#endif //DF_PIXUI_PROFILER

void FPixUIModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.

    //Module shutdown
    UPixUIBPLibrary::PixUI_Shutdown();

#if !defined(DF_DY_LOAD_PX) || (!DF_DY_LOAD_PX)
    #if PLATFORM_WINDOWS || PLATFORM_MAC
        //window and mac need PublicDelayLoadDLLs,so must be call dy unload here
        px_plugin::PxDyLibUnLoad();
    #endif //PLATFORM_WINDOWS || PLATFORM_MAC
#endif //!defined(DF_DY_LOAD_PX) || (!DF_DY_LOAD_PX)
	
	// remove delegates if registered
	if (m_hResumeHandle.IsValid())
	{
		FCoreDelegates::ApplicationHasEnteredForegroundDelegate.Remove(m_hResumeHandle);
		m_hResumeHandle.Reset();
	}

	if (m_hPauseHandle.IsValid())
	{
		FCoreDelegates::ApplicationWillEnterBackgroundDelegate.Remove(m_hPauseHandle);
		m_hPauseHandle.Reset();
	}

#if DF_PIXUI_PROFILER
	PxLog_Log("FPixUIModule run time cost %d %f", n_count_s, f_count_s);
#endif //DF_PIXUI_PROFILER
}


void FPixUIModule::Tick(float f_DeltaTime)
{
    UPixUIBPLibrary::Tick(f_DeltaTime);

#if DF_PIXUI_PROFILER
	//for debug
	if (UPixUIBPLibrary::PixUI_GetDebugTickDelay() > 0.001f)
	{
		FPlatformProcess::Sleep(UPixUIBPLibrary::PixUI_GetDebugTickDelay()); //s
	}

	//for debug
	if (UPixUIBPLibrary::PixUI_GetDebugCPURunTime() > 0)
	{
		//PxpTimeLogOut tmp_time(TEXT("DebugCPURunTime"));
		for (auto i = 0; i < UPixUIBPLibrary::PixUI_GetDebugCPURunTime(); i++)
		{
			//for debug
			f_count_s = 10.0f / 3.0f;
			f_count_s *= 324.54f;

			//for debug
			n_count_s += 10;
			n_count_s -= 9;
		}
		//PxLog_Log("FPixUIModule run time cost %d %f", a_1, f_1);
	}
#endif //DF_PIXUI_PROFILER
}


TStatId FPixUIModule::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(FPixUIModule, STATGROUP_Tickables);
}


bool FPixUIModule::IsTickable() const
{
    return true;
}


bool FPixUIModule::IsTickableInEditor() const
{
    return true;
}

void FPixUIModule::HandleApplicationHasEnteredForeground()
{
	// check state in case changed before ticked
	PxLog_Log("FPixUIModule HandleApplicationHasEnteredForeground......");
	UPixUIWidget::NotifyAppForeground();
	UPixUIBPLibrary::PixUI_OnBackground();
}


void FPixUIModule::HandleApplicationWillEnterBackground()
{
	PxLog_Log("FPixUIModule HandleApplicationWillEnterBackground......");
	UPixUIWidget::NotifyAppBackground();
	UPixUIBPLibrary::PixUI_OnForeground();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FPixUIModule, PixUI)
