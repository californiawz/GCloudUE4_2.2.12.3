/**************************************************

**** @file:     PixUIExInterface.h

**** @brief:    Used to set external files load in the game and texture brushes. do not support blueprint

                For example, the game has its own file management method and loading method of texture brushes

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once

#include "CoreMinimal.h"
#include "Slate.h"
#include "SlateCore.h"
#include "Components/Widget.h"

#include <functional>

//
typedef std::function<void(const TArray<uint8>& array_Data)> PFun_Load;
typedef std::function<bool(const FString& fstr_FilePath, PFun_Load fun_Delegate)> PFun_PixFileLoad;
typedef std::function<TSharedPtr<FSlateBrush>(const FString& fstr_ImagePath)> PFun_PixBrushLoad;
typedef std::function<TWeakObjectPtr<UWidget>(const FString& fstrWidgetPath)> PFun_PixWidgetLoad;

namespace PixUI 
{
    //set file load delegate
    PIXUI_API void SetExternalAssetFileLoadDelegate(PFun_PixFileLoad fun_FileLoad);

    //set brush load delegate
    PIXUI_API void SetExternalBrushLoadDelegate(PFun_PixBrushLoad fun_BrushLoad);

    //set widget load delegate
    PIXUI_API void SetExternalWidgetLoadDelegate(PFun_PixWidgetLoad fun_WidgetLoad);
};