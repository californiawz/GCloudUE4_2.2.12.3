/**************************************************

**** @file:     PixDrawItemDrawSlot.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/06/28

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/






#include "PixDrawItemDrawSlot.h"
#include "PixImp/PixImpImg.h"

PixDrawItemDrawSlot::PixDrawItemDrawSlot()
	:PixDrawItem(e_px_draw_item_draw_slot), slate_layoutTransform_(FVector2D::ZeroVector)
{
	mWptrPxSlot = nullptr;

	SetBatchType(e_px_batch_rect_mat);
}


PixDrawItemDrawSlot::~PixDrawItemDrawSlot()
{

}


void PixDrawItemDrawSlot::UpdateParams(const TArray<void*>& aryParams)
{
	UpdateImageParam(
		((pixui::uint_ptr)(aryParams[0])),
		*((pixui::matrix*)(aryParams[1])),
		*((pixui::position*)(aryParams[2])));
}


void PixDrawItemDrawSlot::UpdateImageParam(
	pixui::uint_ptr						pSlot,
	const pixui::matrix&                mat,
	const pixui::position&              rcDraw)
{
	v2d_paintSize_.X = rcDraw.width;
	v2d_paintSize_.Y = rcDraw.height;

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

	mWptrPxSlot = PixImpSlot::FindPixSlotByHandle(pSlot);
}


void* PixDrawItemDrawSlot::BatchStatus()
{
	return mWptrPxSlot.Pin().Get();
}


FSlateBrush* PixDrawItemDrawSlot::DrawBrush()
{
	if (mWptrPxSlot.IsValid())
	{
		if (mWptrPxSlot.Pin().Get()->GetBrush().IsValid())
		{
			return mWptrPxSlot.Pin().Get()->GetBrush().Get();
		}
	}
	return nullptr;
}


uint32 PixDrawItemDrawSlot::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	FSlateBrush* p_draw_brush = DrawBrush();
	if (p_draw_brush)
	{
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
				p_draw_brush,
				ESlateDrawEffect::None,
				FLinearColor::White
			);
		}
	}
	return 0;
}
