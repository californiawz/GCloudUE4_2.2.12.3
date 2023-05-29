/**************************************************

**** @file:     PixDrawItemDrawLine.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/



#include "PixDrawItemDrawLine.h"

PixDrawItemDrawLine::PixDrawItemDrawLine()
	:PixDrawItem(e_px_draw_item_draw_line), slate_layoutTransform_(FVector2D::ZeroVector)
{
	b_valid_ = false;
	f_Thickness_ = 1.0f;

	SetBatchType(e_px_batch_box);
}


PixDrawItemDrawLine::~PixDrawItemDrawLine()
{

}


void PixDrawItemDrawLine::UpdateParams(const TArray<void*>& aryParams)
{
	UpdateLineParam(
		*((pixui::matrix*)(aryParams[0])),
		*((unsigned int*)(aryParams[1])),
		*((pixui::BorderStyle*)(aryParams[2])),
		*((pixui::color*)(aryParams[3])),
		*((pixui::point*)(aryParams[4])),
		*((pixui::point*)(aryParams[5])));
}


void PixDrawItemDrawLine::UpdateLineParam(
	const pixui::matrix&        mat,
	const unsigned int          unWidth,
	const pixui::BorderStyle   emLineType,
	const pixui::color          color,
	const pixui::point&         ptStart,
	const pixui::point&         ptEnd)
{
	b_valid_ = false;
	if (unWidth != 0 && emLineType > pixui::border_style_hidden)
	{
		b_valid_ = true;

		v2d_paintSize_.X = unWidth; //FVector2D(unWidth, unWidth); draw_params.Geometry.Size;
		v2d_paintSize_.Y = unWidth;

		//layoutTransform = draw_params.Geometry.GetAccumulatedLayoutTransform();

		pixui::matrix tmpMat;
		tmpMat.initTranslate(ptStart.x, ptStart.y);
		tmpMat = mat * tmpMat;

		slate_renderTransform2D_ = FSlateRenderTransform(FMatrix2x2(tmpMat[0], tmpMat[1], tmpMat[2], tmpMat[3]), FVector2D(tmpMat[4], tmpMat[5]));
		FVector2D renderTransformPivot(FVector2D::ZeroVector);

		linePath.Reset(2);
		linePath.Add(FVector2D(0, 0));
		linePath.Add(FVector2D(ptEnd.x - ptStart.x, ptEnd.y - ptStart.y));

		color_linear_ = FColor(color.red(), color.green(), color.blue(), color.alpha());

		f_Thickness_ = unWidth;
	}
}


uint32 PixDrawItemDrawLine::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	if (b_valid_ && linePath.Num() > 0)
	{
		FSlateDrawElement::MakeLines(
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
			linePath,
			ESlateDrawEffect::None,
			color_linear_,
			false,
			f_Thickness_
		);
	}
	return 0;
}
