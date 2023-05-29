/**************************************************

**** @file:     PixDrawItemDrawImage.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/



#pragma once
#include "PixDrawItem.h"

#include "Styling/SlateBrush.h"

#include "PixImp/PixBrush/PixImgBrush.h"


class PixDrawItemDrawImage : public PixDrawItem
{
public:
	PixDrawItemDrawImage();
	~PixDrawItemDrawImage();

public:
	void UpdateImageParam(
		pixui::uint_ptr            pImage,
		const pixui::matrix&                mat,
		const pixui::position&              rcDraw,
		const pixui::position&              rcImageSrc,
		const pixui::BackgroundRepeat      emRepeat,
		const pixui::BackgroundAttachment  emAttachment,
		const pixui::ImageSlice&           sliceImage,
		const pixui::color&                 tintColor,
		const pixui::BorderRadiuses&       radius);

	virtual void* BatchStatus() override;
	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) override;
	virtual void UpdateParams(const TArray<void*>& aryParams) override;

protected:
	FSlateBrush* DrawBrush();

	TSharedPtr<FSlateBrush> MakeMultiBrush();

	void DrawUVImageBox_Repeat(const PX_FOnPaintHandlerParams& draw_context, int32 n_cur_lay, FSlateBrush* p_slate_brush,
		const FBox2D& boxUvReginon, const FVector2D& paintSize, const FVector2D& imageSize,
		const pixui::matrix& drawMat, FSlateBrush* p_slate_brush_ex_1 = nullptr, FSlateBrush* p_slate_brush_ex_2 = nullptr, FSlateBrush* p_slate_bottom_3 = nullptr);

	void DrawUVImageBox(const PX_FOnPaintHandlerParams& draw_context, int32 n_cur_lay, FSlateBrush* p_slate_brush,
		const FBox2D& boxUvReginon, const FVector2D& paintSize,
		const pixui::matrix& drawMat);

private:
	bool b_IsExternal_;

	TWeakPtr<PixImgBrush> wptr_piximg_brush_;
	TWeakPtr<FSlateBrush> wptr_img_brush_;

#if DF_USED_CUSTOM_MULTI_BRUSH
	TSharedPtr<FSlateBrush> sptr_multi_brush_;
#endif //DF_USED_CUSTOM_MULTI_BRUSH

	bool b_valid_;
	bool b_is_slice_;

	FVector2D v2d_image_org_;
	pixui::position uvregin_image_;
	pixui::ImageSlice slice_image_;

	FVector2D v2d_paintSize_;
	FSlateLayoutTransform slate_layoutTransform_;
	FSlateRenderTransform slate_renderTransform2D_;

	FLinearColor color_linear;


	enum EPix_Image_Slice
	{
		e_slice_topleft,
		e_slice_top,
		e_slice_topright,
		e_slice_left,
		e_slice_center,
		e_slice_right,
		e_slice_bottomleft,
		e_slice_bottom,
		e_slice_bottomright,

		e_slice_count
	};

	struct ImageSliceInfor
	{
		bool					b_valid[e_slice_count];
		FVector2D				paint_size_slice[e_slice_count];
		FBox2D					uvregin_slice[e_slice_count];
		pixui::matrix			mat_slice[e_slice_count];
#if DF_USED_CUSTOM_MULTI_BRUSH
		TSharedPtr<FSlateBrush>	sptr_multi_brush_[e_slice_count];

		TSharedPtr<FSlateBrush> sptr_multi_center_ex_[3];
		TSharedPtr<FSlateBrush>	sptr_multi_left_ex_;
		TSharedPtr<FSlateBrush>	sptr_multi_right_ex_;
		TSharedPtr<FSlateBrush>	sptr_multi_top_ex_;
		TSharedPtr<FSlateBrush>	sptr_multi_bottom_ex_;
#endif //DF_USED_CUSTOM_MULTI_BRUSH
	};
	TSharedPtr<ImageSliceInfor> sptr_slice_infor_;

	bool mBeIsRadiusImage;
	ESlateBrushTileType::Type mEBrushTileType;
	FBox2D mUvRegin;
};
