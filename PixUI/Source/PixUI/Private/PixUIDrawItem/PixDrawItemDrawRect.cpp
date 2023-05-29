/**************************************************

**** @file:     PixDrawItemDrawRect.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/



#include "PixDrawItemDrawRect.h"

PixDrawItemDrawRect::PixDrawItemDrawRect()
	:PixDrawItem(e_px_draw_item_draw_rect), slate_layoutTransform_(FVector2D::ZeroVector)
{
	v2d_paintSize_ = FVector2D(1, 1);
	b_valid_ = false;
	f_Thickness_ = 1.0f;

	SetBatchType(e_px_batch_box);
}


PixDrawItemDrawRect::~PixDrawItemDrawRect()
{

}


void PixDrawItemDrawRect::UpdateParams(const TArray<void*>& aryParams)
{
	UpdateRectParam(
		*((pixui::matrix*)(aryParams[0])),
		*((pixui::position*)(aryParams[1])),
		*((unsigned int*)(aryParams[2])),
		*((pixui::BorderStyle*)(aryParams[3])),
		*((pixui::color*)(aryParams[4])),
		*((pixui::BorderRadiuses*)(aryParams[5])));
}


void PixDrawItemDrawRect::UpdateRectParam(
	const pixui::matrix&            mat,
	const pixui::position&          rcDraw,
	const unsigned int              unWidth,
	const pixui::BorderStyle       emLineType,
	const pixui::color&             color,
	const pixui::BorderRadiuses&   radius)
{
	b_valid_ = false;
	if (unWidth != 0 && emLineType > pixui::border_style_hidden)
	{
		b_valid_ = true;
		color_linear_ = FColor(color.red(), color.green(), color.blue(), color.alpha());
		
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

		float x = 0;
		float y = 0;
		float w = rcDraw.width;
		float h = rcDraw.height;
		f_Thickness_ = unWidth;

		if (unWidth == 1)
		{
			ary_linePath_.Add(FVector2D(x, y));
			ary_linePath_.Add(FVector2D(x, h));
			ary_linePath_.Add(FVector2D(w, h));
			ary_linePath_.Add(FVector2D(w, y));
			ary_linePath_.Add(FVector2D(x, y));
		}
		else
		{
			//width > 1 need to caculate offset of center
			float hfW = unWidth / 2;

			FVector2D topLeft(x - hfW, y);
			FVector2D topRight(x + w + hfW, y);
			FVector2D topRightEx(x + w, y);
			FVector2D bottomRight(x + w, y + h + hfW);
			FVector2D bottomRightEx(x + w, y + h);
			FVector2D bottomLeft(x - hfW, y + h);
			FVector2D bottomLeftEx(x, y + h);
			FVector2D topLeftEx(x, y);

			ary_linePath_.Add(topLeft);
			ary_linePath_.Add(topRight);
			ary_linePath_.Add(topRightEx);
			ary_linePath_.Add(bottomRight);
			ary_linePath_.Add(bottomRightEx);
			ary_linePath_.Add(bottomLeft);
			ary_linePath_.Add(bottomLeftEx);
			ary_linePath_.Add(topLeftEx);
		}
	}
}


uint32 PixDrawItemDrawRect::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	if (b_valid_ && ary_linePath_.Num() > 0)
	{
		FSlateDrawElement::MakeLines(
			draw_params.OutDrawElements,
			draw_params.Layer + n_cur_layer,
#if ENGINE_MAJOR_VERSION < 5

			/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 20 //ToPaintGeometry support
			draw_params.Geometry.ToPaintGeometry(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector),
#else
			draw_params.Geometry.MakeChild(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector).ToPaintGeometry(),
#endif  //ENGINE_MINOR_VERSION > 20
			/////////////////////////////////////////////////////////////////////for ue4

#else

			/////////////////////////////////////////////////////////////////////for ue5
			draw_params.Geometry.ToPaintGeometry(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector),
			/////////////////////////////////////////////////////////////////////for ue5

#endif	//ENGINE_MAJOR_VERSION < 5
			ary_linePath_,
			ESlateDrawEffect::None,
			color_linear_,
			false,
			f_Thickness_
		);
	}

	return 0;
}
