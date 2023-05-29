/**************************************************

**** @file:     PixDrawItemDrawText.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/





#include "PixDrawItemDrawText.h"


#include "PixImp/PixImpFont.h"


PixDrawItemDrawText::PixDrawItemDrawText()
	:PixDrawItem(e_px_draw_item_draw_text), slate_layoutTransform_(FVector2D::ZeroVector)
{
	wptr_pix_font_ = nullptr;

	b_valid_ = false;

	linear_color_ = FColor::White;

	SetBatchType(e_px_batch_text);
}


PixDrawItemDrawText::~PixDrawItemDrawText()
{

}

void PixDrawItemDrawText::UpdateParams(const TArray<void*>& aryParams)
{
	UpdateTextParam(
		((pixui::uint_ptr)(aryParams[0])),
		*((pixui::matrix*)(aryParams[1])),
		((const char*)(aryParams[2])),
		*((pixui::color*)(aryParams[3])),
		*((pixui::position*)(aryParams[4])),
		*((float*)(aryParams[5])));
}


void PixDrawItemDrawText::UpdateTextParam(
	pixui::uint_ptr                  hFont,
	const pixui::matrix&    mat,
	const char*             pszTextDraw,
	const pixui::color&     color,
	const pixui::position&  ptPos,
	const float             fBlur)
{
	b_valid_ = false;
	fstr_Text_ = pszTextDraw ? UTF8_TO_TCHAR(pszTextDraw) : TEXT("");

	//check valid
	if (fstr_Text_.TrimStartAndEnd().IsEmpty())
	{
		return;
	}

	//replace \n
	fstr_Text_ = fstr_Text_.Replace(TEXT("\n"), TEXT("  "));
	

	b_valid_ = true;
	
	wptr_pix_font_ = PixImpFont::GetSlateFont(hFont);

	linear_color_ = FColor(color.red(), color.green(), color.blue(), color.alpha());

	v2d_paintSize_.X = ptPos.width;
	v2d_paintSize_.Y = ptPos.height; //draw_params.Geometry.Size; //FVector2D(ptPos.width, ptPos.height);
																//FSlateLayoutTransform layoutTransform(FVector2D::ZeroVector);
																//layoutTransform = draw_params.Geometry.GetAccumulatedLayoutTransform();
	pixui::matrix tmpMat;
	if (PX_LOFAT_EQUAL_ZERO(ptPos.x) && PX_LOFAT_EQUAL_ZERO(ptPos.y))
	{
		tmpMat = mat;
	}
	else
	{
		tmpMat.initTranslate(ptPos.x, ptPos.y);
		tmpMat = mat * tmpMat;
	}
	slate_renderTransform2D_ = FSlateRenderTransform(FMatrix2x2(tmpMat[0], tmpMat[1], tmpMat[2], tmpMat[3]), FVector2D(tmpMat[4], tmpMat[5]));
}


uint32 PixDrawItemDrawText::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	if (b_valid_ && wptr_pix_font_.IsValid() && wptr_pix_font_.Pin()->sptr_SlatFont_.Get())
	{
		FSlateDrawElement::MakeText(
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
			fstr_Text_,
			*(wptr_pix_font_.Pin()->sptr_SlatFont_.Get()),
			ESlateDrawEffect::None,
			linear_color_
		);
	}
	return 0;
}
