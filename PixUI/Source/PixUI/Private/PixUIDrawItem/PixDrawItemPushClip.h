/**************************************************

**** @file:     PixDrawItemPushClip.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/






#pragma once
#include "PixDrawItem.h"


class PixDrawItemPushClip : public PixDrawItem
{
public:
	PixDrawItemPushClip();
	~PixDrawItemPushClip();

public:
	void UpdateClipParam(
		const pixui::matrix& mat,
		const pixui::position& rectClip);

	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) override;
	virtual void UpdateParams(const TArray<void*>& aryParams) override;

	int32 CheckClipType(const FGeometry& Geometry);

private:
	FVector2D v2d_paintSize_;
	FSlateLayoutTransform slate_layoutTransform_;
	FSlateRenderTransform slate_renderTransform2D_;

	FBox2D clipBox_;
};
