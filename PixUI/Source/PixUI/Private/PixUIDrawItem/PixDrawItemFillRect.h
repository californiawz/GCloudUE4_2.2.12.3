/**************************************************

**** @file:     PixDrawItemFillRect.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/




#pragma once
#include "PixDrawItem.h"

#include "PixImp/PixBrush/PixMatBrush.h"


class PixDrawItemFillRect : public PixDrawItem
{
public:
	PixDrawItemFillRect();
	~PixDrawItemFillRect();

public:
	void UpdateFillRectParam(
		const pixui::matrix&            mat,
		const pixui::position&          ptDraw,
		const pixui::color&             color,
		const pixui::BorderRadiuses&   radius);

	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) override;
	virtual void UpdateParams(const TArray<void*>& aryParams) override;

protected:
	FSlateBrush* GetDrawBrush();

private:
	FLinearColor linear_color_;
	bool b_radius_;

	FVector2D v2d_paintSize_;
	FSlateLayoutTransform slate_layoutTransform_;
	FSlateRenderTransform slate_renderTransform2D_;

	bool b_valid_;

	TSharedPtr<PixSharedMatBrush> sptr_pix_mat_brush_;
};
