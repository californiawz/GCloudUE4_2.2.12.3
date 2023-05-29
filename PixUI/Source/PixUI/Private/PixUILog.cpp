/**************************************************

**** @file:     PixUILog.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixUILog.h"

#include "PixUIDef.h"


//General Log
DEFINE_LOG_CATEGORY(PixUI_Module);  //ue4 macro

//log reference
#define PixUILogRef PixUILogWRef()

//log tmp buff size
#define DF_LOG_MAX 4096  //4k

void UPixUILog::LogOut(EPXLogTypes e_LogType, EPXLogLevels e_LogLevel, const char* psz_Fmt, ...)
{
    char sz_Buf[DF_LOG_MAX] = { 0 };
    va_list args;
    va_start(args, psz_Fmt);
    vsnprintf(sz_Buf, DF_LOG_MAX, psz_Fmt, args);
    va_end(args);

    DispatchLog(e_LogType, e_LogLevel, UTF8_TO_TCHAR(sz_Buf));
}


UPixUILog::UPixUILog(const FObjectInitializer& ObjectInitializer)
{
    PxLog_Trace("UPixUILog::UPixUILog Create");
}


void UPixUILog::BeginDestroy()
{
    Super::BeginDestroy();
    PxLog_Trace("UPixUILog::BeginDestroy Destroy");
}


UPixUILog* UPixUILog::Get()
{
    if (!PixUILogRef.IsValid())
    {
        PixUILogRef = NewObject<UPixUILog>();
        PixUILogRef->AddToRoot();
    }
    return PixUILogRef.Get();
}


void UPixUILog::Destroy()
{
    if (PixUILogRef.IsValid())
    {
        PixUILogRef->LogDelegate.Clear();

        PixUILogRef->RemoveFromRoot();
        PixUILogRef = nullptr;
    }
}


void UPixUILog::DispatchLog(EPXLogTypes e_LogType, EPXLogLevels e_LogLevel, const FString& fstr_LogContent)
{
    //make sure call SafeDispach in game thread
    if (IsInGameThread())
    {
        SafeDispatch(e_LogType, e_LogLevel, fstr_LogContent);
    }
    else
    {
        //call in game thread
        AsyncTask(ENamedThreads::GameThread, [=]()
            {
                SafeDispatch(e_LogType, e_LogLevel, fstr_LogContent);
            });
    }
}


void UPixUILog::SafeDispatch(EPXLogTypes e_LogType, EPXLogLevels e_LogLevel, const FString& fstr_LogContent)
{
    if (PixUILogRef.IsValid() && PixUILogRef->LogDelegate.IsBound())
    {// LogDelegate was bound,broadcast to LogDelegate
        PixUILogRef->LogDelegate.Broadcast(e_LogType, e_LogLevel, fstr_LogContent);
    }
    else
    {//no bound delegate,out put log to UE_LOG;
        check((int)e_LogType < 4 && (int)e_LogType >= 0);

        FString fstr_LogType[] = {
            TEXT("core  "),
            TEXT("plugin"),
            TEXT("trace "),
			TEXT("script"),
            TEXT("unknow")
        };

        switch (e_LogLevel)
        {
        case EPXLogLevels::em_px_log_level_log:
            UE_LOG(PixUI_Module, Log,    TEXT("Log:     pixui %s    -->    %s"), *fstr_LogType[(int)e_LogType], *fstr_LogContent);
            break;
        case EPXLogLevels::em_px_log_level_warning:
            UE_LOG(PixUI_Module, Warning,         TEXT("pixui %s    -->    %s"), *fstr_LogType[(int)e_LogType], *fstr_LogContent);
            break;
        case EPXLogLevels::em_px_log_level_error:
            UE_LOG(PixUI_Module, Error,         TEXT("  pixui %s    -->    %s"), *fstr_LogType[(int)e_LogType], *fstr_LogContent);
            break;
        default:
            UE_LOG(PixUI_Module, Log, TEXT("unknow log: pixui %s    -->    %s"), *fstr_LogType[(int)e_LogType], *fstr_LogContent);
            break;
        }
    }
}


TWeakObjectPtr<UPixUILog>& UPixUILog::PixUILogWRef()
{
    static TWeakObjectPtr<UPixUILog> sptr_PixUILog_s = nullptr;
    return sptr_PixUILog_s;
}