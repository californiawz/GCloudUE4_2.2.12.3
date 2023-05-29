/**************************************************

**** @file:     PixDrawItemDrawSlot.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/06/28

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once
#include "PixDrawItem.h"

#include "PixImp/PixImpSlot.h"


class PixDrawItemDrawSlot : public PixDrawItem
{
public:
	PixDrawItemDrawSlot();
	~PixDrawItemDrawSlot();

public:
	void UpdateImageParam(
		pixui::uint_ptr						pSlot,
		const pixui::matrix&                mat,
		const pixui::position&              rcDraw);

	virtual void* BatchStatus() override;
	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) override;
	virtual void UpdateParams(const TArray<void*>& aryParams) override;

protected:
	FSlateBrush* DrawBrush();

private:
	FVector2D v2d_paintSize_;
	FSlateLayoutTransform slate_layoutTransform_;
	FSlateRenderTransform slate_renderTransform2D_;

	TWeakPtr<PixSlot> mWptrPxSlot;
};
