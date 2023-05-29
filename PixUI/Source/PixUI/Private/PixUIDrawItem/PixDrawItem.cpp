/**************************************************

**** @file:     PixDrawItem.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/



#include "PixDrawItem.h"
#include "PixUILog.h"


#include "PixDrawItemDrawBorder.h"
#include "PixDrawItemDrawImage.h"
#include "PixDrawItemDrawLine.h"
#include "PixDrawItemDrawRect.h"
#include "PixDrawItemDrawText.h"
#include "PixDrawItemFillRect.h"
#include "PixDrawItemPopClip.h"
#include "PixDrawItemPushClip.h"
#include "PixDrawItemDrawSlot.h"

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
#include "PixUIProfiler/PxpResCount.h"
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)


TArray<PixDrawItem*> PixDrawItem::gArrayItemPools[e_px_draw_item_count];

PixDrawItem* PixDrawItem::NewDrawItem(EPxDrawItem e_type)
{
	PixDrawItem* p_item = nullptr;
	switch (e_type)
	{
	case e_px_draw_item_draw_border:
		p_item = new PixDrawItemDrawBorder();
		break;
	case e_px_draw_item_draw_image:
		p_item = new PixDrawItemDrawImage();
		break;
	case e_px_draw_item_draw_line:
		p_item = new PixDrawItemDrawLine();
		break;
	case e_px_draw_item_draw_rect:
		p_item = new PixDrawItemDrawRect();
		break;
	case e_px_draw_item_draw_text:
		p_item = new PixDrawItemDrawText();
		break;
	case e_px_draw_item_fill_rect:
		p_item = new PixDrawItemFillRect();
		break;
	case e_px_draw_item_pop_clip:
		p_item = new PixDrawItemPopClip();
		break;
	case e_px_draw_item_push_clip:
		p_item = new PixDrawItemPushClip();
		break;
	case e_px_draw_item_draw_slot:
		p_item = new PixDrawItemDrawSlot();
		break;
	default:
		PxLog_Error("PixDrawItem::NewDrawItem ERROR TYPE:%d", e_type);
		break;
	}
	return p_item;
}

PixDrawItem* PixDrawItem::NewDrawItemFromPools(EPxDrawItem e_type)
{
	PixDrawItem* p_draw_item = nullptr;
	if (e_type < e_px_draw_item_count)
	{
		if (gArrayItemPools[e_type].Num() > 0)
		{
			return  gArrayItemPools[e_type].Pop();
		}
		else
		{
			p_draw_item = PixDrawItem::NewDrawItem(e_type);
		}
	}
	else
	{
		PxLog_Error("PixDrawItem::NewDrawItemFromPools e_type error %d", e_type);
	}
	return p_draw_item;
}

void PixDrawItem::FreeDrawItemToPools(PixDrawItem* pDrawItem)
{
	if (pDrawItem)
	{
		gArrayItemPools[pDrawItem->Type()].Add(pDrawItem);
	}
}

void PixDrawItem::FreeAllDrawItem()
{
	for (int i = 0; i < e_px_draw_item_count ; i++)
	{
		for (auto item : gArrayItemPools[i])
		{
			delete item;
		}
		gArrayItemPools[i].Empty();
	}
}


PixDrawItem::PixDrawItem(EPxDrawItem e_type)
	:e_type_(e_type)
{
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixDrawItem new  type:%d   total count:%d", Type() , ++ResItemCount::PixDrawItemTotalCount());
	PxLog_Trace("    PixDrawItem new  type:%d   count:%d", Type(), ResItemCount::PixDrawItemBrushAdd(Type()));
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	SetBatchType(e_px_batch_none);
}


PixDrawItem::~PixDrawItem()
{
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixDrawItem delete type:%d   total count:%d", Type(), --ResItemCount::PixDrawItemTotalCount());
	PxLog_Trace("    PixDrawItem delete  type:%d   count:%d", Type(), ResItemCount::PixDrawItemBrushDec(Type()));
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}