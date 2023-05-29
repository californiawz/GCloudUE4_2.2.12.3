/**************************************************

**** @file:     PixUtil.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/11

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "PixelFormat.h"

#include "PixUIDef.h"

#include "hf_typedef.h"

#include "UnrealEngine.h"
#include "Slate.h"


const float PX_PLUGIN_EPSINON = 0.00001f;

#define PX_LOFAT_EQUAL_ZERO(val_) (val_ >= -PX_PLUGIN_EPSINON) && (val_ <= PX_PLUGIN_EPSINON)


class PixUtil
{
public:
    //get the game player world,If the game is not started, it will be return a null value
    static UWorld* GameWorld();

    //be game is playing
    static bool IsGamePlay();

    //be or not in editor
    static bool IsInEditor();

    //be or not shipping
    static bool IsShippingEnv();

    //be or not development
    static bool IsDevEnv();

    //be or not debug
    static bool IsDebugEnv();

    //Force GarbageCollection
    static void EngineGC(bool bForcePurge = false);

    //ue4 current scale rate
    static float  SlateScaleRate();

    //point to pixel
    static uint32 PtToPix(const uint32 unPt);

    //pixel to point
    static uint32 PixToPt(const uint32 unPixel);

    //trans pixui color to FColor
    static FColor PixColor2FColor(const pixui::color& InColor);

    //ue4 KeyEvent trans to PixUI KeyCode
    static pixui::EKeyCode UEKeyEventToPixUIKeyCode(const FKeyEvent& InKeyEvent);

    //ue4 KeyEvent trans to PixUI KeyModifier
    static unsigned char UEKeyEventToPixUIKeyModifier(const FKeyEvent& InKeyEvent);

    //windows keycode translate to pixui keycode
    static uint32 WinKeyCodeToPixKeyCode(const uint32 unWinKeyCode);

    //Mac keycode translate to pixui keycode
    static uint32 MacKeyCodeToPixKeyCode(const uint32 unMacKeyCode);

    //Android keycode translate to pixui keycode
    static uint32 AndroidKeyCodeToPixKeyCode(const uint32 unAndroidKeyCode);

	//PixUI PixelFormat translate to UE pixelFormat
	static EPixelFormat PixUIPixelFormatToUEPixelFormat(const pixui::EPixelFormat em_PixelFormat);

	static int GetBitsPerBlock(EPixelFormat Format);

	static int GetBlockSize(EPixelFormat Format);

	//根据纹理格式和传入的w/h，计算出经过宽度对齐的gpu w/h，和所需要的字节长度
	static void CalcTextureGpuSize(EPixelFormat Format, int Width, int Height, int& GpuWidth, int& GpuHeight, int& GpuDataSize);
	
    static uint32 NewId();

	static void FreeId(uint32 un_id);
	
	static FString OSversion();
	static float OSversionCode();

    static size_t UTF32toUTF8(uint32 un_utf32_char, uint8* p_out_utf8);
};

