/**************************************************

**** @file:     PixDrawItemDrawRect.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/



#pragma once
#include "PixDrawItem.h"


class PixDrawItemDrawRect : public PixDrawItem
{
public:
	PixDrawItemDrawRect();
	~PixDrawItemDrawRect();

public:
	void UpdateRectParam(
		const pixui::matrix&            mat,
		const pixui::position&          rcDraw,
		const unsigned int              unWidth,
		const pixui::BorderStyle       emLineType,
		const pixui::color&             color,
		const pixui::BorderRadiuses&   radius);

	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) override;
	virtual void UpdateParams(const TArray<void*>& aryParams) override;

private:
	FVector2D v2d_paintSize_;
	FSlateLayoutTransform slate_layoutTransform_;
	FSlateRenderTransform slate_renderTransform2D_;

	TArray<FVector2D> ary_linePath_;

	FLinearColor color_linear_;
	float f_Thickness_;
	bool b_valid_;
};
