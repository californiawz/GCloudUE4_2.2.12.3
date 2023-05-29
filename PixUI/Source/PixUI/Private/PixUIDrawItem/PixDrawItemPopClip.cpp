/**************************************************

**** @file:     PixDrawItemPopClip.cpp

**** @brief:

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/





#include "PixDrawItemPopClip.h"

PixDrawItemPopClip::PixDrawItemPopClip()
	:PixDrawItem(e_px_draw_item_pop_clip)
{
	b_pop_clip_ = true;
}


PixDrawItemPopClip::~PixDrawItemPopClip()
{

}


void PixDrawItemPopClip::UpdateParams(const TArray<void*>& aryParams)
{
	UpdatePopClipParam(
		*((bool*)(aryParams[0])));
}


void PixDrawItemPopClip::UpdatePopClipParam(bool b_pop)
{
	b_pop_clip_ = b_pop;
}


uint32 PixDrawItemPopClip::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	if (b_pop_clip_)
	{
		draw_params.OutDrawElements.PopClip();
	}
	return 0;
}
