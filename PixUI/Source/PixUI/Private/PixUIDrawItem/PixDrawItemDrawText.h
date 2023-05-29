/**************************************************

**** @file:     PixDrawItemDrawText.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/




#pragma once
#include "PixDrawItem.h"

#include "PixImp/PixImpFont.h"


class PixDrawItemDrawText : public PixDrawItem
{
public:
	PixDrawItemDrawText();
	~PixDrawItemDrawText();

public:
	void UpdateTextParam(
		pixui::uint_ptr                  hFont,
		const pixui::matrix&    mat,
		const char*             pszTextDraw,
		const pixui::color&     color,
		const pixui::position&  ptPos,
		const float             fBlur);

	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) override;
	virtual void UpdateParams(const TArray<void*>& aryParams) override;

private:
	TWeakPtr<PixFont> wptr_pix_font_;
	FString fstr_Text_;

	FLinearColor linear_color_;

	FVector2D v2d_paintSize_;
	FSlateLayoutTransform slate_layoutTransform_;
	FSlateRenderTransform slate_renderTransform2D_;

	bool b_valid_;
};
