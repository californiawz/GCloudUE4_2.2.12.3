/**************************************************

**** @file:     ResItem.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/13

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/


#pragma once

#include "PixUIDef.h"

#if DF_PIXUI_PROFILER

#include "CoreMinimal.h"

class ResItemCount
{
public:
	static void ShowResCount();

public:
	// PixMatBrush
	static uint32& PixMatBrushTotalCount();
	static uint32& PixMatBrushTypeCount(int n_type);
	static uint32 PixMatBrushAdd(int n_type);
	static uint32 PixMatBrushDec(int n_type);

	//PixSharedMatBrush
	static uint32& PixSharedMatBrushCount();
	static uint32& PixSharedMatBrushTypeCount(int n_type);
	static uint32 PixSharedMatBrushAdd(int n_type);
	static uint32 PixSharedMatBrushDec(int n_type);

	//PixDrawItem
	static uint32& PixDrawItemTotalCount();
	static uint32& PixDrawItemTypeCount(int n_type);
	static uint32 PixDrawItemBrushAdd(int n_type);
	static uint32 PixDrawItemBrushDec(int n_type);

	//PixFont
	static uint32& PixFontCount();

	//PixImgBrush
	static uint32& PixImgBrushCount();

	//PixWidget
	static uint32& PixWidgetCount();

	//PixSlot
	static uint32& PixSlotCount();
};

#endif //DF_PIXUI_PROFILER
