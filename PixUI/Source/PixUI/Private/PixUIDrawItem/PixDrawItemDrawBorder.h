/**************************************************

**** @file:     PixDrawItemDrawBorder.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/

#pragma once
#include "PixDrawItem.h"

#include "PixImp/PixImpMat.h"


class PixDrawItemDrawBorder : public PixDrawItem
{
public:
	PixDrawItemDrawBorder();
	virtual ~PixDrawItemDrawBorder();

public:
	void UpdateBorderParam(
		const pixui::matrix&            mat,
		const pixui::position&          rcDraw,
		const unsigned int              nWidths[],
		const pixui::BorderStyle       eLineTypes[],
		const pixui::color              colors[],
		const pixui::BorderRadiuses&   radius);

	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) override;
	virtual void UpdateParams(const TArray<void*>& aryParams) override;

private:
	TSharedPtr<PixSharedMatBrush> sptr_pix_border_brush_;

	FVector2D v2d_paintSize_;
	FSlateLayoutTransform slate_layoutTransform_;
	FSlateRenderTransform slate_renderTransform2D_;

	bool b_is_valid_;
};
