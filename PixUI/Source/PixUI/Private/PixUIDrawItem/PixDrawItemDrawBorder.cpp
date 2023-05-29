/**************************************************

**** @file:     PixDrawItemDrawBorder.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/




#include "PixDrawItemDrawBorder.h"

#include "PixImp/PixBrush/PixMatBrush.h"

PixDrawItemDrawBorder::PixDrawItemDrawBorder()
	:PixDrawItem(e_px_draw_item_draw_border), slate_layoutTransform_(FVector2D::ZeroVector)
{
	sptr_pix_border_brush_ = nullptr;

	b_is_valid_ = false;
}


PixDrawItemDrawBorder::~PixDrawItemDrawBorder()
{

}


void PixDrawItemDrawBorder::UpdateParams(const TArray<void*>& aryParams)
{
	UpdateBorderParam(
		*((pixui::matrix*)(aryParams[0])),
		*((pixui::position*)(aryParams[1])),
		((unsigned int*)(aryParams[2])),
		((pixui::BorderStyle*)(aryParams[3])),
		((pixui::color*)(aryParams[4])),
		*((pixui::BorderRadiuses*)(aryParams[5])));
}


void PixDrawItemDrawBorder::UpdateBorderParam(
	const pixui::matrix&            mat,
	const pixui::position&          rcDraw,
	const unsigned int              nWidths[],
	const pixui::BorderStyle       eLineTypes[],
	const pixui::color              colors[],
	const pixui::BorderRadiuses&   radius)
{
	b_is_valid_ = false;
	//size invalid
	if (rcDraw.width <= 0.00001f || rcDraw.height <= 0.00001f)
		return;

	//border width invalid
	if (nWidths[EPxBoderIndex::e_px_boder_index_top] == 0
		&& nWidths[EPxBoderIndex::e_px_boder_index_bottom] == 0
		&& nWidths[EPxBoderIndex::e_px_boder_index_left] == 0
		&& nWidths[EPxBoderIndex::e_px_boder_index_right] == 0)
	{
		return;
	}

	//border style invalid
	if (eLineTypes[EPxBoderIndex::e_px_boder_index_top] <= pixui::border_style_hidden
		&& eLineTypes[EPxBoderIndex::e_px_boder_index_bottom] <= pixui::border_style_hidden
		&& eLineTypes[EPxBoderIndex::e_px_boder_index_left] <= pixui::border_style_hidden
		&& eLineTypes[EPxBoderIndex::e_px_boder_index_right] <= pixui::border_style_hidden)
	{
		return;
	}

	//border color invalid
	if (colors[EPxBoderIndex::e_px_boder_index_top].alpha() == 0
		&& colors[EPxBoderIndex::e_px_boder_index_bottom].alpha() == 0
		&& colors[EPxBoderIndex::e_px_boder_index_left].alpha() == 0
		&& colors[EPxBoderIndex::e_px_boder_index_right].alpha() == 0)
	{
		return;
	}

	b_is_valid_ = true;

	bool b_sameColor = false;
	if (colors[EPxBoderIndex::e_px_boder_index_top] == colors[EPxBoderIndex::e_px_boder_index_left]
		&& colors[EPxBoderIndex::e_px_boder_index_bottom] == colors[EPxBoderIndex::e_px_boder_index_right]
		&& colors[EPxBoderIndex::e_px_boder_index_top] == colors[EPxBoderIndex::e_px_boder_index_bottom])
	{
		b_sameColor = true;
	}

	if (radius.topLeftX <= 0.00001f && radius.topLeftY <= 0.00001f
		&& radius.topRightX <= 0.00001f && radius.topRightY <= 0.00001f
		&& radius.bottomLeftX <= 0.00001f && radius.bottomLeftY <= 0.00001f
		&& radius.bottomRightX <= 0.00001f && radius.bottomRightY <= 0.00001f)
	{
		//no radius
		if (b_sameColor)
		{
			//same color
			if (sptr_pix_border_brush_.IsValid())
			{
				sptr_pix_border_brush_->ResetParams(rcDraw, nWidths, colors[EPxBoderIndex::e_px_boder_index_top]);
			}
			else
			{
				sptr_pix_border_brush_ = PixImpMat::GetBorderBrush(rcDraw, nWidths, colors[EPxBoderIndex::e_px_boder_index_top]);
			}
		}
		else
		{
			if (sptr_pix_border_brush_.IsValid())
			{
				sptr_pix_border_brush_->ResetParams(rcDraw, nWidths, colors);
			}
			else
			{
				sptr_pix_border_brush_ = PixImpMat::GetBorderBrush(rcDraw, nWidths, colors);
			}
		}
	}
	else
	{
		//radius
		if (b_sameColor)
		{
			//same color
			if (sptr_pix_border_brush_.IsValid())
			{
				sptr_pix_border_brush_->ResetParams(rcDraw, nWidths, colors[EPxBoderIndex::e_px_boder_index_top], radius);
			}
			else
			{
				sptr_pix_border_brush_ = PixImpMat::GetBorderBrush(rcDraw, nWidths, colors[EPxBoderIndex::e_px_boder_index_top], radius);
			}
		}
		else
		{
			if (sptr_pix_border_brush_.IsValid())
			{
				sptr_pix_border_brush_->ResetParams(rcDraw, nWidths, colors, radius);
			}
			else
			{
				sptr_pix_border_brush_ = PixImpMat::GetBorderBrush(rcDraw, nWidths, colors, radius);
			}
		}
	}

	v2d_paintSize_.X = rcDraw.width;
	v2d_paintSize_.Y = rcDraw.height;

	//layoutTransform = pDrawParam->Geometry.GetAccumulatedLayoutTransform();
	pixui::matrix tmpMat;
	if (PX_LOFAT_EQUAL_ZERO(rcDraw.x) && PX_LOFAT_EQUAL_ZERO(rcDraw.y))
	{
		tmpMat = mat;
	}
	else
	{
		tmpMat.initTranslate(rcDraw.x, rcDraw.y);
		tmpMat = mat * tmpMat;
	}

	slate_renderTransform2D_ = FSlateRenderTransform(FMatrix2x2(tmpMat[0], tmpMat[1], tmpMat[2], tmpMat[3]), FVector2D(tmpMat[4], tmpMat[5]));

	if (sptr_pix_border_brush_.IsValid() && sptr_pix_border_brush_->GetBrush())
	{
		SetBatchType(e_px_batch_matiral);
	}
	else
	{
		SetBatchType(e_px_batch_box);
	}
}


uint32 PixDrawItemDrawBorder::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	if (b_is_valid_ && sptr_pix_border_brush_.IsValid() && sptr_pix_border_brush_->GetBrush())
	{
		FSlateDrawElement::MakeBox(
			draw_params.OutDrawElements,
			draw_params.Layer + n_cur_layer,
#if ENGINE_MAJOR_VERSION < 5

			/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 20 //ToPaintGeometry support
			draw_params.Geometry.ToPaintGeometry(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector),
#else
			draw_params.Geometry.MakeChild(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector).ToPaintGeometry(),
#endif //ENGINE_MINOR_VERSION > 20
			/////////////////////////////////////////////////////////////////////for ue4

#else
			/////////////////////////////////////////////////////////////////////for ue5
			draw_params.Geometry.ToPaintGeometry(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector),
			/////////////////////////////////////////////////////////////////////for ue5
#endif //ENGINE_MAJOR_VERSION < 5
			sptr_pix_border_brush_->GetBrush(),
			ESlateDrawEffect::None
		);
	}
	else
	{
		//draw border line
	}

	return 0;
}
