/**************************************************

**** @file:     PixUILog.h

**** @brief:    pixui log management system

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core.h"

#include "PixUILog.generated.h"

//pixui plugin log types
UENUM(BlueprintType)
enum class EPXLogTypes :uint8
{
    em_px_log_type_core     UMETA(DisplayName = "pix log tpye of pixui core"),
    em_px_log_type_plugin   UMETA(DisplayName = "pix log tpye of pixui ue4 plugin"),
    em_px_log_type_trace    UMETA(DisplayName = "pix log tpye of Debug trance"),
	em_px_log_type_script   UMETA(DisplayName = "pix log tpye of pixui core script"),

    em_px_log_type_count    UMETA(DisplayName = "pix log tpye of count"),
};


//pixui plugin log levels
UENUM(BlueprintType)
enum class EPXLogLevels :uint8
{
    em_px_log_level_log         UMETA(DisplayName = "pix log level of log"),
    em_px_log_level_warning     UMETA(DisplayName = "pix log level of warnning"),
    em_px_log_level_error       UMETA(DisplayName = "pix log level of error"),

    em_px_log_level_count       UMETA(DisplayName = "pix log level of count"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPXViewLogDelegate, EPXLogTypes, logType, EPXLogLevels, logLevel, FString, logContent);


#define _PX_TOSTRING1(_x) _PX_TOSTRING2(_x)
#define _PX_TOSTRING2(_x) #_x


//pixui log macro
#define PxLog_Log(fmt,...)     UPixUILog::LogOut(EPXLogTypes::em_px_log_type_plugin, EPXLogLevels::em_px_log_level_log,     fmt "      [" __FILE__ "(" _PX_TOSTRING1(__LINE__) ")]", ##__VA_ARGS__)
#define PxLog_Warning(fmt,...) UPixUILog::LogOut(EPXLogTypes::em_px_log_type_plugin, EPXLogLevels::em_px_log_level_warning, fmt "      [" __FILE__ "(" _PX_TOSTRING1(__LINE__) ")]", ##__VA_ARGS__)
#define PxLog_Error(fmt,...)   UPixUILog::LogOut(EPXLogTypes::em_px_log_type_plugin, EPXLogLevels::em_px_log_level_error,   fmt "      [" __FILE__ "(" _PX_TOSTRING1(__LINE__) ")]", ##__VA_ARGS__)

#if UE_BUILD_SHIPPING
//shipping do not trace out put
#define PxLog_Trace(fmt,...)
#else
#define PxLog_Trace(fmt,...)   UPixUILog::LogOut(EPXLogTypes::em_px_log_type_trace,  EPXLogLevels::em_px_log_level_log,     fmt "      [" __FILE__ "(" _PX_TOSTRING1(__LINE__) ")]", ##__VA_ARGS__)
#endif //UE_BUILD_SHIPPING


//General Log 
DECLARE_LOG_CATEGORY_EXTERN(PixUI_Module, Log, All);

/**
 * 
 */
UCLASS()
class PIXUI_API UPixUILog : public UObject
{
    GENERATED_BODY()

public:
    UPixUILog(const FObjectInitializer& ObjectInitializer);

    /************************************************************************/
    // UObject implementation
    virtual void BeginDestroy() override;
    // UObject implementation
    /************************************************************************/

public:
    //format log information and dispach log
    static void LogOut(EPXLogTypes e_LogType, EPXLogLevels e_LogLevel, const char* psz_Fmt, ...);

public:
    //log delegate
    UPROPERTY(BlueprintAssignable, Category = "PixUILog")
    FPXViewLogDelegate LogDelegate;

public:
    //get pixui log instance
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUILog Get", Keywords = "PixUILog Get"), Category = "PixUILog")
    static UPixUILog* Get();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PixUILog DispatchLog", Keywords = "PixUILog DispatchLog"), Category = "PixUILog")
    //out put or dispatch to log delegate(if delegate was bound)
    static void DispatchLog(EPXLogTypes e_LogType, EPXLogLevels e_LogLevel, const FString& fstr_LogContent);

	//destroy log instance
	static void Destroy();
    
protected:
    //make log safe dispatch in game thread
    static void SafeDispatch(EPXLogTypes e_LogType, EPXLogLevels e_LogLevel, const FString& fstr_LogContent);

    //log reference
    static TWeakObjectPtr<UPixUILog>& PixUILogWRef();
};
