/**************************************************

**** @file:     PxpResCount.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/13

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/



#include "PxpResCount.h"

#if DF_PIXUI_PROFILER

#include "PixImp/PixBrush/PixMatBrush.h"
#include "PixImp/PixImpMat.h"
#include "PixImp/PixImpFileLoad.h"
#include "PixUIDrawItem/PixDrawItem.h"
#include "PixUIWidget.h"
#include "PixUILog.h"


static uint32 un_pix_mat_brush_used_count_s[e_px_mat_brush_count] = { 0 };

static uint32 un_shared_mat_brush_used_count_s[e_px_mat_brush_count] = { 0 };

static uint32 un_draw_item_count_s[e_px_draw_item_count] = { 0 };


void ResItemCount::ShowResCount()
{
	PxLog_Log("");
	PxLog_Log("");
	PxLog_Log("=============================================ResItemCount::ShowResCount========================================");
	//show PixMatBrush
	PxLog_Log("PixMatBrush total count:%d", PixMatBrushTotalCount());
	for (auto i = 0; i < e_px_mat_brush_count; i++)
	{
		PxLog_Log("    PixMatBrush type:%d   count:%d", i, un_pix_mat_brush_used_count_s[i]);
	}

	//PixSharedMatBrush
	PxLog_Log("PixSharedMatBrush total count:%d", PixSharedMatBrushCount());

	//PixImpMat
	PixImpMat::ShowPixImpMatInfor();

	//PixDrawItem
	PxLog_Log("PixDrawItem total count:%d", PixDrawItemTotalCount());
	for (auto i = 0; i < e_px_draw_item_count; i++)
	{
		PxLog_Log("    PixDrawItem type:%d   count:%d", i, un_draw_item_count_s[i]);
	}

	//PixFont
	PxLog_Log("PixFont total count:%d", PixFontCount());

	//PixImpFileLoad
	PixImpFileLoad::ShowLoadFileInfor();

	//PixImgBrush
	PxLog_Log("PixImgBrush total count:%d", PixImgBrushCount());

	//PixSlot
	PxLog_Log("PixSlot total count:%d", PixSlotCount());

	//UPixUIWidget
	PxLog_Log("UPixUIWidget total count:%d", PixWidgetCount());
	UPixUIWidget::ShowWidgetsInfor();

	PxLog_Log("=============================================ResItemCount::ShowResCount========================================");
	PxLog_Log("");
	PxLog_Log("");
}

uint32& ResItemCount::PixMatBrushTotalCount()
{
	static uint32 un_pix_mat_count_s = 0;
	return un_pix_mat_count_s;
}


uint32& ResItemCount::PixMatBrushTypeCount(int n_type)
{
	return un_pix_mat_brush_used_count_s[n_type];
}


uint32 ResItemCount::PixMatBrushAdd(int n_type)
{
	return ++un_pix_mat_brush_used_count_s[n_type];
}


uint32 ResItemCount::PixMatBrushDec(int n_type)
{
	return --un_pix_mat_brush_used_count_s[n_type];
}


uint32& ResItemCount::PixSharedMatBrushCount()
{
	static uint32 un_pix_mat_shared_count_s = 0;
	return un_pix_mat_shared_count_s;
}

uint32& ResItemCount::PixDrawItemTotalCount()
{
	static uint32 un_pix_draw_item_total_count_s = 0;
	return un_pix_draw_item_total_count_s;
}


uint32& ResItemCount::PixDrawItemTypeCount(int n_type)
{
	return un_draw_item_count_s[n_type];
}


uint32 ResItemCount::PixDrawItemBrushAdd(int n_type)
{
	return ++un_draw_item_count_s[n_type];
}


uint32 ResItemCount::PixDrawItemBrushDec(int n_type)
{
	return --un_draw_item_count_s[n_type];
}



uint32& ResItemCount::PixFontCount()
{
	static uint32 un_font_total_count_s = 0;
	return un_font_total_count_s;
}


uint32& ResItemCount::PixImgBrushCount()
{
	static uint32 un_piximg_total_count_s = 0;
	return un_piximg_total_count_s;
}


uint32& ResItemCount::PixWidgetCount()
{
	static uint32 un_pixui_widget_count_s = 0;
	return un_pixui_widget_count_s;
}


uint32& ResItemCount::PixSlotCount()
{
	static uint32 un_pixui_slot_count_s = 0;
	return un_pixui_slot_count_s;
}


#endif //DF_PIXUI_PROFILER
