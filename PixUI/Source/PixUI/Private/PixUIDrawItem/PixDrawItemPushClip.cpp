/**************************************************

**** @file:     PixDrawItemPushClip.cpp

**** @brief:

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/





#include "PixDrawItemPushClip.h"

#include "PixUILog.h"

PixDrawItemPushClip::PixDrawItemPushClip()
	:PixDrawItem(e_px_draw_item_push_clip)
{

}


PixDrawItemPushClip::~PixDrawItemPushClip()
{

}

void PixDrawItemPushClip::UpdateParams(const TArray<void*>& aryParams)
{
	UpdateClipParam(
		*((pixui::matrix*)(aryParams[0])),
		*((pixui::position*)(aryParams[1])));
}


void PixDrawItemPushClip::UpdateClipParam(
	const pixui::matrix& mat,
	const pixui::position& rectClip)
{
	FVector2D paintPosition = FVector2D(rectClip.x, rectClip.y);

	v2d_paintSize_ = FVector2D(rectClip.width, rectClip.height);
	//clipBox_ = FBox2D(paintPosition + FVector2D(mat[4], mat[5]), paintPosition + FVector2D(mat[4], mat[5]) + v2d_paintSize_);

	auto rect_aabb = mat.getAABB(rectClip);
	clipBox_ = FBox2D(FVector2D(rect_aabb.x, rect_aabb.y), FVector2D(rect_aabb.width, rect_aabb.height));


	slate_layoutTransform_ = FSlateLayoutTransform(paintPosition);
	//layoutTransform = draw_params.Geometry.GetAccumulatedLayoutTransform();
	slate_renderTransform2D_ = FSlateRenderTransform(FMatrix2x2(mat[0], mat[1], mat[2], mat[3]), FVector2D(mat[4], mat[5]));
}

int32 PixDrawItemPushClip::CheckClipType(const FGeometry& Geometry)
{
	FVector2D viewPosition(0.0f, 0.0f);
	FVector2D viewSize = Geometry.GetLocalSize();
	FBox2D viewBox(viewPosition, viewSize);

	if (viewBox.Intersect(clipBox_))
	{
		return 0;
	}
	return 1;
}


uint32 PixDrawItemPushClip::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	//0, 0 w h RectView
	FVector2D viewPosition(0.0f, 0.0f);
	FVector2D viewSize = draw_params.Geometry.GetLocalSize();
	FBox2D viewBox(viewPosition, viewSize);

	if (viewBox.Intersect(clipBox_))
	{
#if ENGINE_MAJOR_VERSION < 5

		/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 20  //ToPaintGeometry support
		FSlateClippingZone clipZone(draw_params.Geometry.ToPaintGeometry(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector));
#else
		FSlateClippingZone clipZone(draw_params.Geometry.MakeChild(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector).ToPaintGeometry());
#endif //ENGINE_MINOR_VERSION > 20
		/////////////////////////////////////////////////////////////////////for ue4
#else
		/////////////////////////////////////////////////////////////////////for ue5
		FSlateClippingZone clipZone(draw_params.Geometry.ToPaintGeometry(v2d_paintSize_, slate_layoutTransform_, slate_renderTransform2D_, FVector2D::ZeroVector));
		/////////////////////////////////////////////////////////////////////for ue5
#endif	//ENGINE_MAJOR_VERSION < 5

		clipZone.SetShouldIntersectParent(true);
		clipZone.SetAlwaysClip(false);
		draw_params.OutDrawElements.PushClip(clipZone);
	}
	else
	{
		//PxLog_Trace("PixDrawItemPushClip::DrawItem push invalid clip.....");
		return 1;
	}

	return 0;
}
