/**************************************************

**** @file:     PixDrawItemFillRect.cpp

**** @brief:

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/





#include "PixDrawItemFillRect.h"

#include "PixImp/PixImpMat.h"

#include "PixUILog.h"



PixDrawItemFillRect::PixDrawItemFillRect()
	:PixDrawItem(e_px_draw_item_fill_rect) , slate_layoutTransform_(FVector2D::ZeroVector)
{
	b_radius_ = false;
	b_valid_ = false;

	sptr_pix_mat_brush_ = nullptr;
}


PixDrawItemFillRect::~PixDrawItemFillRect()
{

}

void PixDrawItemFillRect::UpdateParams(const TArray<void*>& aryParams)
{
	UpdateFillRectParam(
		*((pixui::matrix*)(aryParams[0])),
		*((pixui::position*)(aryParams[1])),
		*((pixui::color*)(aryParams[2])),
		*((pixui::BorderRadiuses*)(aryParams[3])));
}


void PixDrawItemFillRect::UpdateFillRectParam(
	const pixui::matrix&            mat,
	const pixui::position&          ptDraw,
	const pixui::color&             color,
	const pixui::BorderRadiuses&   radius)
{
	b_valid_ = false;
	if (ptDraw.width <= 0.00001f || ptDraw.height <= 0.00001f)
		return;

	b_valid_ = true;

	linear_color_ = FColor(color.red(), color.green(), color.blue(), color.alpha());

	v2d_paintSize_.X = ptDraw.width;
	v2d_paintSize_.Y = ptDraw.height;

	pixui::matrix tmpMat;
	if (PX_LOFAT_EQUAL_ZERO(ptDraw.x) && PX_LOFAT_EQUAL_ZERO(ptDraw.y))
	{
		tmpMat = mat;
	}
	else
	{
		tmpMat.initTranslate(ptDraw.x, ptDraw.y);
		tmpMat = mat * tmpMat;
	}
	

	slate_renderTransform2D_ = FSlateRenderTransform(FMatrix2x2(tmpMat[0], tmpMat[1], tmpMat[2], tmpMat[3]), FVector2D(tmpMat[4], tmpMat[5]));

	if (radius.bottomLeftX > 0.00001f || radius.bottomLeftY > 0.00001f ||
		radius.topLeftX > 0.00001f || radius.topLeftY > 0.00001f ||
		radius.topRightX > 0.00001f || radius.topRightY > 0.00001f ||
		radius.bottomRightX > 0.00001f || radius.bottomRightY > 0.00001f
		)
	{
		b_radius_ = true;
		//Contains radius information
		if (!sptr_pix_mat_brush_.IsValid())
		{
			sptr_pix_mat_brush_ = PixImpMat::GetRectBrush(ptDraw, color, radius);
		}

		if (sptr_pix_mat_brush_.IsValid())
		{
			sptr_pix_mat_brush_->ResetParams(ptDraw, color, radius);
			//DrawTypeElement(EM_VIEW_DRAW_TYPE::em_draw_rect_mat);
			SetBatchType(e_px_batch_rect_mat);
		}
		else
		{
			//DrawTypeElement(EM_VIEW_DRAW_TYPE::em_draw_box);
			SetBatchType(e_px_batch_box);
		}
	}
	else
	{
		b_radius_ = false;

		//sptr_pix_mat_brush_ = nullptr;
		//DrawTypeElement(EM_VIEW_DRAW_TYPE::em_draw_box);
		SetBatchType(e_px_batch_box);

		if (sptr_pix_mat_brush_.IsValid())
		{
			sptr_pix_mat_brush_->ResetMatBrush();
		}
	}
}


uint32 PixDrawItemFillRect::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	FSlateBrush* p_slate_brush = GetDrawBrush();
	if (b_valid_ && p_slate_brush)
	{
		FSlateDrawElement::MakeBox(
			draw_params.OutDrawElements,
			draw_params.Layer + n_cur_layer,
#if ENGINE_MAJOR_VERSION < 5
			/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 20
			draw_params.Geometry.ToPaintGeometry(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector),
#else
			draw_params.Geometry.MakeChild(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector).ToPaintGeometry(),
#endif //ENGINE_MINOR_VERSION > 20
			/////////////////////////////////////////////////////////////////////for ue4
#else
			/////////////////////////////////////////////////////////////////////for ue5
			draw_params.Geometry.ToPaintGeometry(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector),
			/////////////////////////////////////////////////////////////////////for ue5
#endif	//ENGINE_MAJOR_VERSION < 5
			GetDrawBrush(),
			ESlateDrawEffect::None,
			linear_color_
		);
	}
	return 0;
}


FSlateBrush* PixDrawItemFillRect::GetDrawBrush()
{
	if (b_radius_ && sptr_pix_mat_brush_.IsValid() && sptr_pix_mat_brush_->GetMatBrush().IsValid())
	{
		return sptr_pix_mat_brush_->GetMatBrush().Pin()->GetBrush();
	}

	static const FSlateColorBrush s_stBrushWhite = FSlateColorBrush(FColorList::White);
	return (FSlateBrush*)&s_stBrushWhite;
}
