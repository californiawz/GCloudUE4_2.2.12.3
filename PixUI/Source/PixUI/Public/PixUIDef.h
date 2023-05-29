/**************************************************

**** @file:     PixUIDef.h

**** @brief:    pixui Global macro definition header file

**** @author:   tianzelei

**** @date:     2020/12/10

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once

#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"

//plugin version
#define DF_PIXUI_PLUGIN_VERSION  TEXT("02.00.02")

#define DF_PIXUI_UE4_AGENT	"agent pixui ue4 0.4.1 02"

#if ENGINE_MAJOR_VERSION < 5

/////////////////////////////////////////////////////////////////////for ue4
//UE4.22 use multiple brushes
#define DF_SUPPORT_MUTIL_BRUSH_VERSION 22

//force use mutil brush
#define DF_FORE_USED_MUTIL_BRUSH 0

//4.21 and previous versions do not not support multiple brushes
#define DF_USED_CUSTOM_MULTI_BRUSH (ENGINE_MINOR_VERSION < DF_SUPPORT_MUTIL_BRUSH_VERSION || DF_FORE_USED_MUTIL_BRUSH)
/////////////////////////////////////////////////////////////////////for ue4

#else

/////////////////////////////////////////////////////////////////////for ue5
#define DF_SUPPORT_MUTIL_BRUSH_VERSION	0
#define DF_USED_CUSTOM_MULTI_BRUSH		1
/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5

//do or not support multiple pages
#define DF_MULTY_PAGE_SUPPORT 1

//ue4 roboto font path
#define DF_UE_ROBOTO_FONT_UASSET            TEXT("/Engine/EngineFonts/Roboto")


//pixui mat root path
#define DF_MAT_ROOT_PATH					TEXT("/PixUI/mat/")
#define DF_MAT_ROOT_PATH_ES2				TEXT("/PixUI/mat/es2/")


#define DF_MAT_BASE_PATH_HEAD_OLD			TEXT("Mat_")
#define DF_MAT_BASE_PATH_HEAD				TEXT("Mat_Pix_")
#define DF_MAT_BASE_PATH_HEAD_ES2			TEXT("Mat_Pix_es2_")

//pixui mat file path
#define DF_MAT_IMG_RADIUS_PATH              TEXT("Radius")
#define DF_MAT_IMG_RADIUS_CORNER_PATH       TEXT("Radius_corner")

#define DF_MAT_RECT_RADIUS_PATH             TEXT("Rect_Radius")
#define DF_MAT_RECT_RADIUS_CORNER_PATH      TEXT("Rect_Radius_corner")

#define DF_MAT_BORDER_PATH                  TEXT("Border")
#define DF_MAT_BORDER_COLOR_PATH            TEXT("Border_Color")
#define DF_MAT_BORDER_RADIUS_PATH           TEXT("Border_Radius")
#define DF_MAT_BORDER_COLOR_RADIUS_PATH     TEXT("Border_Color_Radius")


#define DF_PX_BUILD_NO_SHIPPING  (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT)

//pixui profiler tool for editor/debug/development
#define DF_PIXUI_PROFILER	DF_PX_BUILD_NO_SHIPPING


//pixui lib debug,set DF_USE_DEBUG_LIB to 1 to use debug library interface for test
//do not open it in shipping
#define DF_USE_DEBUG_LIB 0


enum EPxDrawItem
{
	e_px_draw_item_draw_border,
	e_px_draw_item_draw_image,
	e_px_draw_item_draw_line,
	e_px_draw_item_draw_rect,
	e_px_draw_item_draw_text,
	e_px_draw_item_fill_rect,
	e_px_draw_item_pop_clip,
	e_px_draw_item_push_clip,
	e_px_draw_item_draw_slot,

	e_px_draw_item_count
};

//E_PixDrawType: draw element type
enum EPxBatchType
{
	e_px_batch_none,
	e_px_batch_text,
	e_px_batch_box,
	e_px_batch_image,
	e_px_batch_rect_mat,
	e_px_batch_matiral
};

enum EPxBoderIndex
{
	e_px_boder_index_top,
	e_px_boder_index_bottom,
	e_px_boder_index_left,
	e_px_boder_index_right,
	e_px_boder_index_count
};


enum EPxPlatformCode
{
	e_px_platform_code_win,
	e_px_platform_code_mac,
	e_px_platform_code_ios,
	e_px_platform_code_android,
	e_px_platform_code_other,

	e_px_platform_code_count
};



#if UE_BUILD_SHIPPING

#undef DF_USE_DEBUG_LIB  //ps: shipping do not support debug lib

#endif //UE_BUILD_SHIPPING