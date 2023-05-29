/**************************************************

**** @file:     PixDrawItemDrawImage.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/

#include "PixDrawItemDrawImage.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "PixImp/PixImpImg.h"

PixDrawItemDrawImage::PixDrawItemDrawImage()
	:PixDrawItem(e_px_draw_item_draw_image), slate_layoutTransform_(FVector2D::ZeroVector)
{
	wptr_piximg_brush_ = nullptr;
	wptr_img_brush_ = nullptr;
	b_valid_ = false;
	b_is_slice_ = false;

	color_linear = FColor::White;

	sptr_slice_infor_ = nullptr;

	b_IsExternal_ = false;

	mBeIsRadiusImage = false;
	mEBrushTileType = ESlateBrushTileType::NoTile;
	mUvRegin = FBox2D(FVector2D::ZeroVector, FVector2D::UnitVector);

	SetBatchType(e_px_batch_image);
}


PixDrawItemDrawImage::~PixDrawItemDrawImage()
{

}


void PixDrawItemDrawImage::UpdateParams(const TArray<void*>& aryParams)
{
	UpdateImageParam(
		((pixui::uint_ptr)(aryParams[0])),
		*((pixui::matrix*)(aryParams[1])),
		*((pixui::position*)(aryParams[2])),
		*((pixui::position*)(aryParams[3])),
		*((pixui::BackgroundRepeat*)(aryParams[4])),
		*((pixui::BackgroundAttachment*)(aryParams[5])),
		*((pixui::ImageSlice*)(aryParams[6])),
		*((pixui::color*)(aryParams[7])),
		*((pixui::BorderRadiuses*)(aryParams[8])));
}



void PixDrawItemDrawImage::UpdateImageParam(
	pixui::uint_ptr						pImage,
	const pixui::matrix&                mat,
	const pixui::position&              rcDraw,
	const pixui::position&              uvregin_image,
	const pixui::BackgroundRepeat      emRepeat,
	const pixui::BackgroundAttachment  emAttachment,
	const pixui::ImageSlice&           slice_image,
	const pixui::color&                 tintColor,
	const pixui::BorderRadiuses&       radius)
{
	b_valid_ = false;
	b_IsExternal_ = false;
	b_is_slice_ = false;

	if (pImage)
	{
		wptr_piximg_brush_ = PixImpImg::FindPixImgByHandle(pImage);
		if (wptr_piximg_brush_.IsValid())
		{
			uvregin_image_ = uvregin_image;
			slice_image_ = slice_image;
			pixui::size size_image_org;
			wptr_piximg_brush_.Pin()->GetImageSize(size_image_org);
			v2d_image_org_ = FVector2D(size_image_org.width, size_image_org.height);

			if (size_image_org.width > 0.00001f && size_image_org.height > 0.00001f &&
				rcDraw.width > 0.00001f && rcDraw.height > 0.00001f)
			{
				b_valid_ = true;
				color_linear = FColor(255.0f, 255.0f, 255.0f, tintColor.alpha());
				if (IS_SLICE_VALID(slice_image))
				{//is 9-slice image

					b_is_slice_ = true;

					if (!sptr_slice_infor_.IsValid())
					{
						sptr_slice_infor_ = MakeShareable(new ImageSliceInfor());
					}

					if (wptr_img_brush_.IsValid())
					{
						if (wptr_piximg_brush_.Pin().Get()->GetImageBrush() != wptr_img_brush_)
						{
							wptr_img_brush_ = wptr_piximg_brush_.Pin().Get()->GetImageBrush();
							wptr_img_brush_.Pin().Get()->Tiling = ESlateBrushTileType::NoTile;

							b_IsExternal_ = wptr_piximg_brush_.Pin()->IsExternal();
#if DF_USED_CUSTOM_MULTI_BRUSH
							sptr_multi_brush_ = nullptr;
							for (auto i = 0; i < EPix_Image_Slice::e_slice_count; i++)
							{
								sptr_slice_infor_->sptr_multi_brush_[i] = MakeMultiBrush();
							}

							for (auto i=0; i<3 ;i++)
							{
								sptr_slice_infor_->sptr_multi_center_ex_[i] = MakeMultiBrush();
							}
							sptr_slice_infor_->sptr_multi_left_ex_ = MakeMultiBrush();
							sptr_slice_infor_->sptr_multi_right_ex_ = MakeMultiBrush();
							sptr_slice_infor_->sptr_multi_top_ex_ = MakeMultiBrush();
							sptr_slice_infor_->sptr_multi_bottom_ex_ = MakeMultiBrush();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
						}
						else
						{
							wptr_img_brush_.Pin().Get()->Tiling = ESlateBrushTileType::NoTile;
#if DF_USED_CUSTOM_MULTI_BRUSH
							if (!sptr_slice_infor_->sptr_multi_left_ex_.IsValid() || 
								sptr_slice_infor_->sptr_multi_left_ex_->GetResourceObject() != wptr_img_brush_.Pin()->GetResourceObject())
							{
								sptr_multi_brush_ = nullptr;
								for (auto i = 0; i < EPix_Image_Slice::e_slice_count; i++)
								{
									sptr_slice_infor_->sptr_multi_brush_[i] = MakeMultiBrush();
								}

								for (auto i = 0; i < 3; i++)
								{
									sptr_slice_infor_->sptr_multi_center_ex_[i] = MakeMultiBrush();
								}
								sptr_slice_infor_->sptr_multi_left_ex_ = MakeMultiBrush();
								sptr_slice_infor_->sptr_multi_right_ex_ = MakeMultiBrush();
								sptr_slice_infor_->sptr_multi_top_ex_ = MakeMultiBrush();
								sptr_slice_infor_->sptr_multi_bottom_ex_ = MakeMultiBrush();
							}
#endif //DF_USED_CUSTOM_MULTI_BRUSH
						}
					}
					else
					{
						wptr_img_brush_ = wptr_piximg_brush_.Pin().Get()->GetImageBrush();
						wptr_img_brush_.Pin().Get()->Tiling = ESlateBrushTileType::NoTile;

						b_IsExternal_ = wptr_piximg_brush_.Pin()->IsExternal();
#if DF_USED_CUSTOM_MULTI_BRUSH
						sptr_multi_brush_ = nullptr;
						for (auto i = 0; i < EPix_Image_Slice::e_slice_count; i++)
						{
							sptr_slice_infor_->sptr_multi_brush_[i] = MakeMultiBrush();
						}
						for (auto i = 0; i < 3; i++)
						{
							sptr_slice_infor_->sptr_multi_center_ex_[i] = MakeMultiBrush();
						}
						sptr_slice_infor_->sptr_multi_left_ex_ = MakeMultiBrush();
						sptr_slice_infor_->sptr_multi_right_ex_ = MakeMultiBrush();
						sptr_slice_infor_->sptr_multi_top_ex_ = MakeMultiBrush();
						sptr_slice_infor_->sptr_multi_bottom_ex_ = MakeMultiBrush();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					}

					//make slice informations
					{
						float w_topleft = slice_image.slice_top_x;
						float h_topleft = slice_image.slice_top_y;
						if (w_topleft > rcDraw.width)
						{
							w_topleft = rcDraw.width;
						}

						if (h_topleft > rcDraw.height)
						{
							h_topleft = rcDraw.height;
						}
						sptr_slice_infor_->b_valid[e_slice_topleft] = true;
						sptr_slice_infor_->paint_size_slice[e_slice_topleft] = FVector2D(w_topleft, h_topleft);
						pixui::matrix tmpMat;
						tmpMat.initTranslate(rcDraw.x, rcDraw.y);
						sptr_slice_infor_->mat_slice[e_slice_topleft] = mat * tmpMat;
						FVector2D StartUV_topleft = FVector2D(uvregin_image.x / size_image_org.width, uvregin_image.y / size_image_org.height);
						FVector2D size_topleft = FVector2D(w_topleft / size_image_org.width, h_topleft / size_image_org.height);
						sptr_slice_infor_->uvregin_slice[e_slice_topleft] = FBox2D(StartUV_topleft, StartUV_topleft + size_topleft);
						//DrawUVImageBox(hDevice, pImageBrush, uvRegin_topleft, paintSize_topleft, tmpMat, fstColor);

						//draw top
						if (rcDraw.width - slice_image.slice_top_x - slice_image.slice_bottom_x > 0 && uvregin_image.width - slice_image.slice_top_x - slice_image.slice_bottom_x > 0)
						{
							sptr_slice_infor_->b_valid[e_slice_top] = true;

							float w_draw_top = rcDraw.width - slice_image.slice_top_x - slice_image.slice_bottom_x;
							float h_draw_top = slice_image.slice_top_y;

							float w_uv_top = uvregin_image.width - slice_image.slice_top_x - slice_image.slice_bottom_x;
							float h_uv_top = slice_image.slice_top_y;


							sptr_slice_infor_->paint_size_slice[e_slice_top] = FVector2D(w_draw_top, h_draw_top);
							pixui::matrix tmpMat_top;
							tmpMat_top.initTranslate(rcDraw.x + slice_image.slice_top_x, rcDraw.y);
							sptr_slice_infor_->mat_slice[e_slice_top] = mat * tmpMat_top;

							FVector2D StartUV_top = FVector2D((uvregin_image.x + slice_image.slice_top_x) / size_image_org.width, uvregin_image.y / size_image_org.height);
							FVector2D size_top = FVector2D(w_uv_top / size_image_org.width, h_uv_top / size_image_org.height);
							sptr_slice_infor_->uvregin_slice[e_slice_top] = FBox2D(StartUV_top, StartUV_top + size_top);

							if (slice_image.repeat == pixui::image_stretch)
							{
								//DrawUVImageBox(hDevice, pImageBrush, uvRegin_top, paintSize_top, tmpMat_top, fstColor);
							}
							else
							{
								//DrawUVImageBox_Repeat(hDevice, pImageBrush, uvRegin_top, paintSize_top, FVector2D(size_image_org.width, size_image_org.height), tmpMat_top, fstColor);
							}
						}
						else
						{
							sptr_slice_infor_->b_valid[e_slice_top] = false;
						}

						//draw top right
						float w_topright = slice_image.slice_bottom_x;
						float h_topright = slice_image.slice_top_y;
						if (w_topright > rcDraw.width)
						{
							w_topright = rcDraw.width;
						}

						if (h_topright > rcDraw.height)
						{
							h_topright = rcDraw.height;
						}
						sptr_slice_infor_->b_valid[e_slice_topright] = true;
						sptr_slice_infor_->paint_size_slice[e_slice_topright] = FVector2D(w_topright, h_topright);
						pixui::matrix tmpMat_topright;
						tmpMat_topright.initTranslate(rcDraw.x + rcDraw.width - w_topright, rcDraw.y);
						sptr_slice_infor_->mat_slice[e_slice_topright] = mat * tmpMat_topright;

						FVector2D StartUV_topright = FVector2D((uvregin_image.x + uvregin_image.width - w_topright) / size_image_org.width, uvregin_image.y / size_image_org.height);
						FVector2D size_topright = FVector2D(w_topright / size_image_org.width, h_topright / size_image_org.height);
						sptr_slice_infor_->uvregin_slice[e_slice_topright] = FBox2D(StartUV_topright, StartUV_topright + size_topright);
						//DrawUVImageBox(hDevice, pImageBrush, uvRegin_topright, paintSize_topright, tmpMat_topright, fstColor);

						//draw left   //draw right
						if (rcDraw.height - slice_image.slice_top_y - slice_image.slice_bottom_y > 0 && uvregin_image.height - slice_image.slice_top_y - slice_image.slice_bottom_y > 0)
						{
							float w_draw_left = slice_image.slice_top_x;
							float h_draw_left = rcDraw.height - slice_image.slice_top_y - slice_image.slice_bottom_y;

							float w_draw_right = slice_image.slice_bottom_x;
							float h_draw_right = h_draw_left;

							float w_uv_left = slice_image.slice_top_x;
							float h_uv_left = uvregin_image.height - slice_image.slice_top_y - slice_image.slice_bottom_y;

							float w_uv_right = slice_image.slice_bottom_x;
							float h_uv_right = h_uv_left;

							//left
							sptr_slice_infor_->b_valid[e_slice_left] = true;
							sptr_slice_infor_->paint_size_slice[e_slice_left] = FVector2D(w_draw_left, h_draw_left);
							pixui::matrix tmpMat_left;
							tmpMat_left.initTranslate(rcDraw.x, rcDraw.y + slice_image.slice_top_y);
							sptr_slice_infor_->mat_slice[e_slice_left] = mat * tmpMat_left;

							FVector2D StartUV_left = FVector2D(uvregin_image.x / size_image_org.width, (uvregin_image.y + slice_image.slice_top_y) / size_image_org.height);
							FVector2D size_left = FVector2D(w_uv_left / size_image_org.width, h_uv_left / size_image_org.height);
							sptr_slice_infor_->uvregin_slice[e_slice_left] = FBox2D(StartUV_left, StartUV_left + size_left);
							if (slice_image.repeat == pixui::image_stretch)
							{
								//DrawUVImageBox(hDevice, pImageBrush, uvRegin_left, paintSize_left, tmpMat_left, fstColor);
							}
							else
							{
								//DrawUVImageBox_Repeat(hDevice, pImageBrush, uvRegin_left, paintSize_left, FVector2D(size_image_org.width, size_image_org.height), tmpMat_left, fstColor);
							}

							//right
							sptr_slice_infor_->b_valid[e_slice_right] = true;
							sptr_slice_infor_->paint_size_slice[e_slice_right] = FVector2D(w_draw_right, h_draw_right);
							pixui::matrix tmpMat_right;
							tmpMat_right.initTranslate(rcDraw.x + rcDraw.width - slice_image.slice_bottom_x, rcDraw.y + slice_image.slice_top_y);
							sptr_slice_infor_->mat_slice[e_slice_right] = mat * tmpMat_right;

							FVector2D StartUV_right = FVector2D((uvregin_image.x + uvregin_image.width - slice_image.slice_bottom_x) / size_image_org.width, (uvregin_image.y + slice_image.slice_top_y) / size_image_org.height);
							FVector2D size_right = FVector2D(w_uv_right / size_image_org.width, h_uv_right / size_image_org.height);
							sptr_slice_infor_->uvregin_slice[e_slice_right] = FBox2D(StartUV_right, StartUV_right + size_right);
							if (slice_image.repeat == pixui::image_stretch)
							{
								//DrawUVImageBox(hDevice, pImageBrush, uvRegin_right, paintSize_right, tmpMat_right, fstColor);
							}
							else
							{
								//DrawUVImageBox_Repeat(hDevice, pImageBrush, uvRegin_right, paintSize_right, FVector2D(size_image_org.width, size_image_org.height), tmpMat_right, fstColor);
							}
						}
						else
						{
							sptr_slice_infor_->b_valid[e_slice_left] = false;
							sptr_slice_infor_->b_valid[e_slice_right] = false;
						}


						//draw bottom left
						float w_bottomleft = slice_image.slice_top_x;
						float h_bottomleft = slice_image.slice_bottom_y;
						if (w_bottomleft > rcDraw.width)
						{
							w_bottomleft = rcDraw.width;
						}

						if (h_bottomleft > rcDraw.height)
						{
							h_bottomleft = rcDraw.height;
						}

						sptr_slice_infor_->b_valid[e_slice_bottomleft] = true;
						sptr_slice_infor_->paint_size_slice[e_slice_bottomleft] = FVector2D(w_bottomleft, h_bottomleft);
						pixui::matrix tmpMat_bottomleft;
						tmpMat_bottomleft.initTranslate(rcDraw.x, rcDraw.y + rcDraw.height - slice_image.slice_bottom_y);
						sptr_slice_infor_->mat_slice[e_slice_bottomleft] = mat * tmpMat_bottomleft;

						FVector2D StartUV_bottomleft = FVector2D(uvregin_image.x / size_image_org.width, (uvregin_image.y + uvregin_image.height - slice_image.slice_bottom_y) / size_image_org.height);
						FVector2D size_bottomleft = FVector2D(w_topright / size_image_org.width, h_topright / size_image_org.height);
						sptr_slice_infor_->uvregin_slice[e_slice_bottomleft] = FBox2D(StartUV_bottomleft, StartUV_bottomleft + size_bottomleft);
						//DrawUVImageBox(hDevice, pImageBrush, uvRegin_bottomleft, paintSize_bottomleft, tmpMat_bottomleft, fstColor);

						//draw bottom
						float w_draw_bottom = rcDraw.width - slice_image.slice_top_x - slice_image.slice_bottom_x;
						float w_uv_bottom = uvregin_image.width - slice_image.slice_top_x - slice_image.slice_bottom_x;
						if (w_draw_bottom > 0 && w_uv_bottom > 0)
						{
							float h_draw_bottom = slice_image.slice_bottom_y;
							float h_uv_bottom = slice_image.slice_bottom_y;

							sptr_slice_infor_->b_valid[e_slice_bottom] = true;
							sptr_slice_infor_->paint_size_slice[e_slice_bottom] = FVector2D(w_draw_bottom, h_draw_bottom);
							pixui::matrix tmpMat_bottom;
							tmpMat_bottom.initTranslate(rcDraw.x + slice_image.slice_top_x, rcDraw.y + rcDraw.height - slice_image.slice_bottom_y);
							sptr_slice_infor_->mat_slice[e_slice_bottom] = mat * tmpMat_bottom;

							FVector2D StartUV_bottom = FVector2D((uvregin_image.x + slice_image.slice_top_x) / size_image_org.width, (uvregin_image.y + uvregin_image.height - slice_image.slice_bottom_y) / size_image_org.height);
							FVector2D size_bottom = FVector2D(w_uv_bottom / size_image_org.width, h_uv_bottom / size_image_org.height);
							sptr_slice_infor_->uvregin_slice[e_slice_bottom] = FBox2D(StartUV_bottom, StartUV_bottom + size_bottom);
							if (slice_image.repeat == pixui::image_stretch)
							{
								//DrawUVImageBox(hDevice, pImageBrush, uvRegin_bottom, paintSize_bottom, tmpMat_bottom, fstColor);
							}
							else
							{
								//DrawUVImageBox_Repeat(hDevice, pImageBrush, uvRegin_bottom, paintSize_bottom, FVector2D(size_image_org.width, size_image_org.height), tmpMat_bottom, fstColor);
							}
						}
						else
						{
							sptr_slice_infor_->b_valid[e_slice_bottom] = false;
						}

						//draw bottom right
						float w_bottomright = slice_image.slice_bottom_x;
						float h_bottomright = slice_image.slice_bottom_y;
						if (w_bottomright > rcDraw.width)
						{
							w_bottomright = rcDraw.width;
						}

						if (h_bottomright > rcDraw.height)
						{
							h_bottomright = rcDraw.height;
						}

						sptr_slice_infor_->b_valid[e_slice_bottomright] = true;
						sptr_slice_infor_->paint_size_slice[e_slice_bottomright] = FVector2D(w_bottomright, h_bottomright);
						pixui::matrix tmpMat_bottomright;
						tmpMat_bottomright.initTranslate(rcDraw.x + rcDraw.width - slice_image.slice_bottom_x, rcDraw.y + rcDraw.height - slice_image.slice_bottom_y);
						sptr_slice_infor_->mat_slice[e_slice_bottomright] = mat * tmpMat_bottomright;

						FVector2D StartUV_bottomright = FVector2D((uvregin_image.x + uvregin_image.width - slice_image.slice_bottom_x) / size_image_org.width, (uvregin_image.y + uvregin_image.height - slice_image.slice_bottom_y) / size_image_org.height);
						FVector2D size_bottomright = FVector2D(w_topright / size_image_org.width, h_topright / size_image_org.height);
						sptr_slice_infor_->uvregin_slice[e_slice_bottomright] = FBox2D(StartUV_bottomright, StartUV_bottomright + size_bottomright);
						//DrawUVImageBox(hDevice, pImageBrush, uvRegin_bottomright, paintSize_bottomright, tmpMat_bottomright, fstColor);

						//draw center
						if (slice_image.model == pixui::image_fill)
						{
							if (rcDraw.width - slice_image.slice_top_x - slice_image.slice_bottom_x > 0
								&& uvregin_image.width - slice_image.slice_top_x - slice_image.slice_bottom_x > 0
								&& rcDraw.height - slice_image.slice_top_y - slice_image.slice_bottom_y > 0
								&& uvregin_image.height - slice_image.slice_top_y - slice_image.slice_bottom_y > 0)
							{
								sptr_slice_infor_->b_valid[e_slice_center] = true;
								float w_draw_center = rcDraw.width - slice_image.slice_top_x - slice_image.slice_bottom_x;
								float h_draw_center = rcDraw.height - slice_image.slice_top_y - slice_image.slice_bottom_y;

								float w_uv_center = uvregin_image.width - slice_image.slice_top_x - slice_image.slice_bottom_x;
								float h_uv_center = uvregin_image.height - slice_image.slice_top_y - slice_image.slice_bottom_y;


								sptr_slice_infor_->paint_size_slice[e_slice_center] = FVector2D(w_draw_center, h_draw_center);
								pixui::matrix tmpMat_center;
								tmpMat_center.initTranslate(rcDraw.x + slice_image.slice_top_x, rcDraw.y + slice_image.slice_top_y);
								sptr_slice_infor_->mat_slice[e_slice_center] = mat * tmpMat_center;

								FVector2D StartUV_center = FVector2D((uvregin_image.x + slice_image.slice_top_x) / size_image_org.width, (uvregin_image.y + slice_image.slice_top_y) / size_image_org.height);
								FVector2D size_center = FVector2D(w_uv_center / size_image_org.width, h_uv_center / size_image_org.height);
								sptr_slice_infor_->uvregin_slice[e_slice_center] = FBox2D(StartUV_center, StartUV_center + size_center);
								if (slice_image.repeat == pixui::image_stretch)
								{
									//DrawUVImageBox(hDevice, pImageBrush, uvRegin_center, paintSize_center, tmpMat_center, fstColor);
								}
								else
								{
									//DrawUVImageBox_Repeat(hDevice, pImageBrush, uvRegin_center, paintSize_center, FVector2D(size_image_org.width, size_image_org.height), tmpMat_center, fstColor);
								}
							}
							else
							{
								sptr_slice_infor_->b_valid[e_slice_center] = false;
							}
						}
						else
						{
							sptr_slice_infor_->b_valid[e_slice_center] = false;
						}
					}
				}
				else
				{
					if (wptr_img_brush_.IsValid())
					{
						if (wptr_piximg_brush_.Pin().Get()->GetImageBrush() != wptr_img_brush_)
						{
							wptr_img_brush_ = wptr_piximg_brush_.Pin().Get()->GetImageBrush();
							b_IsExternal_ = wptr_piximg_brush_.Pin()->IsExternal();
#if DF_USED_CUSTOM_MULTI_BRUSH
							sptr_multi_brush_ = MakeMultiBrush();
#endif // DF_USED_CUSTOM_MULTI_BRUSH
						}
#if DF_USED_CUSTOM_MULTI_BRUSH
						else 
						{
							if (!sptr_multi_brush_.IsValid() || sptr_multi_brush_->GetResourceObject() != wptr_img_brush_.Pin()->GetResourceObject())
							{
								sptr_multi_brush_ = MakeMultiBrush();
							}
						}
#endif // DF_USED_CUSTOM_MULTI_BRUSH
					}
					else
					{
						wptr_img_brush_ = wptr_piximg_brush_.Pin().Get()->GetImageBrush();
						b_IsExternal_ = wptr_piximg_brush_.Pin()->IsExternal();
#if DF_USED_CUSTOM_MULTI_BRUSH
						sptr_multi_brush_ = MakeMultiBrush();
#endif // DF_USED_CUSTOM_MULTI_BRUSH

					}

					FSlateBrush* pImageBrush = DrawBrush();

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


					float widthScaleRate = rcDraw.width / uvregin_image.width;
					float heightScaleRate = rcDraw.height / uvregin_image.height;
					float fWidthScale = size_image_org.width * widthScaleRate;
					float fHeightScale = size_image_org.height * heightScaleRate;
					//pImageBrush->SetImageSize(FVector2D(fWidthScale, fHeightScale));

					if (widthScaleRate > 0.00001f && heightScaleRate > 0.00001f &&
						!(widthScaleRate == 1.0f && heightScaleRate == 1.0f))
					{
						pixui::matrix tmpMatScale;
						tmpMatScale.initTranslate(0, 0);
						tmpMatScale.scale(widthScaleRate, heightScaleRate);
						tmpMat = tmpMat * tmpMatScale;

						v2d_paintSize_ = FVector2D(rcDraw.width / widthScaleRate, rcDraw.height / heightScaleRate);
					}

					mBeIsRadiusImage = false;

					if (radius.bottomLeftX > 0.00001f || radius.bottomLeftY > 0.00001f ||
						radius.topLeftX > 0.00001f || radius.topLeftY > 0.00001f ||
						radius.topRightX > 0.00001f || radius.topRightY > 0.00001f ||
						radius.bottomRightX > 0.00001f || radius.bottomRightY > 0.00001f
						)
					{
						//set by brush
						FVector2D image_size(fWidthScale / rcDraw.width, fHeightScale / rcDraw.height);
						FVector2D uv_offset(rcDraw.x / rcDraw.width, rcDraw.y / rcDraw.height);

						mBeIsRadiusImage = true;
						if (wptr_piximg_brush_.IsValid())
						{
							wptr_img_brush_ = wptr_piximg_brush_.Pin().Get()->GetImageRadiusBrush(radius, rcDraw, image_size, uv_offset, emRepeat);
							b_IsExternal_ = wptr_piximg_brush_.Pin()->IsExternal();
							if (wptr_img_brush_.IsValid())
							{
#if DF_USED_CUSTOM_MULTI_BRUSH
								sptr_multi_brush_ = nullptr;
#endif	//DF_USED_CUSTOM_MULTI_BRUSH
							}
						}
					}
					else
					{
						if (pImageBrush && wptr_piximg_brush_.IsValid() && !(wptr_piximg_brush_.Pin().Get()->IsExternalPaperSprite()))
						{
							FVector2D StartUV = FVector2D(uvregin_image.x / size_image_org.width, uvregin_image.y / size_image_org.height);
							FVector2D SizeUV = FVector2D(1.0f, 1.0f);

							switch (emRepeat)
							{
							case pixui::background_repeat_repeat:
								//ue4 bug? if is repeat uv offset is not OrgSize but is draw size
								StartUV = FVector2D(uvregin_image.x / uvregin_image.width, uvregin_image.y / uvregin_image.height);
								SizeUV = FVector2D(1.0f, 1.0f);
								//pImageBrush->Tiling = ESlateBrushTileType::Both;
								mEBrushTileType = ESlateBrushTileType::Both;
								break;
							case pixui::background_repeat_repeat_x:
								//ue4 bug? if is repeat uv offset is not OrgSize but is draw size
								StartUV.X = uvregin_image.x / uvregin_image.width;
								SizeUV = FVector2D(1.0f, uvregin_image.height / size_image_org.height);
								//pImageBrush->Tiling = ESlateBrushTileType::Horizontal;
								mEBrushTileType = ESlateBrushTileType::Horizontal;
								break;
							case pixui::background_repeat_repeat_y:
								//ue4 bug? if is repeat uv offset is not OrgSize but is draw size
								StartUV.Y = uvregin_image.y / uvregin_image.height;
								SizeUV = FVector2D(uvregin_image.width / size_image_org.width, 1.0f);
								//pImageBrush->Tiling = ESlateBrushTileType::Vertical;
								mEBrushTileType = ESlateBrushTileType::Vertical;
								break;
							default:
								pImageBrush->Tiling = ESlateBrushTileType::NoTile;
								mEBrushTileType = ESlateBrushTileType::NoTile;
								SizeUV = FVector2D(uvregin_image.width / size_image_org.width, uvregin_image.height / size_image_org.height);
								break;
							}
							mUvRegin = FBox2D(StartUV, StartUV + SizeUV);
							//pImageBrush->SetUVRegion(FBox2D(StartUV, StartUV + SizeUV));
						}
					}

					slate_renderTransform2D_ = FSlateRenderTransform(FMatrix2x2(tmpMat[0], tmpMat[1], tmpMat[2], tmpMat[3]), FVector2D(tmpMat[4], tmpMat[5]));
				}
			}
		}
	}
}


void* PixDrawItemDrawImage::BatchStatus()
{
	return wptr_piximg_brush_.Pin().Get();
}


uint32 PixDrawItemDrawImage::DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer)
{
	if (wptr_piximg_brush_.IsValid())
	{
		wptr_piximg_brush_.Pin().Get()->FlushTexture();
	}

	FSlateBrush* p_draw_brush = DrawBrush();
	UTexture* p_texture_obj = p_draw_brush ? Cast<UTexture>(p_draw_brush->GetResourceObject()) : nullptr;
	UMaterialInstance* p_material_obj = p_draw_brush ? Cast<UMaterialInstance>(p_draw_brush->GetResourceObject()) : nullptr;

#if ENGINE_MAJOR_VERSION < 5
	/////////////////////////////////////////////////////////////////////for ue4
#if (ENGINE_MINOR_VERSION < 22)
	if (b_valid_ && ((p_texture_obj && p_texture_obj->Resource) || (p_material_obj && p_material_obj->Resources[0])))
#else
	if (b_valid_ && ((p_texture_obj && p_texture_obj->Resource) || (p_material_obj && p_material_obj->Resource)))
#endif //(ENGINE_MINOR_VERSION < 22)
		/////////////////////////////////////////////////////////////////////for ue4
#else
	/////////////////////////////////////////////////////////////////////for ue5
	if (b_valid_ && ((p_texture_obj && p_texture_obj->GetResource()) || (p_material_obj && p_material_obj->Resource)))
		/////////////////////////////////////////////////////////////////////for ue5
#endif	//ENGINE_MAJOR_VERSION < 5
	{
		if (b_is_slice_)
		{
			//draw slice
			FSlateBrush* p_slate_ex_1 = nullptr;

#if DF_USED_CUSTOM_MULTI_BRUSH
			p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_topleft].Get();
#else
			p_draw_brush->Tiling = ESlateBrushTileType::NoTile;
#endif //DF_USED_CUSTOM_MULTI_BRUSH

			//top left
			DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
				sptr_slice_infor_->uvregin_slice[e_slice_topleft],
				sptr_slice_infor_->paint_size_slice[e_slice_topleft],
				sptr_slice_infor_->mat_slice[e_slice_topleft]);

			//top
			if (sptr_slice_infor_->b_valid[e_slice_top])
			{
				if (slice_image_.repeat == pixui::image_stretch)
				{
#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_top].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_top],
						sptr_slice_infor_->paint_size_slice[e_slice_top],
						sptr_slice_infor_->mat_slice[e_slice_top]);
				}
				else
				{
#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_top].Get();
					p_slate_ex_1 = sptr_slice_infor_->sptr_multi_top_ex_.Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox_Repeat(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_top],
						sptr_slice_infor_->paint_size_slice[e_slice_top],
						v2d_image_org_,
						sptr_slice_infor_->mat_slice[e_slice_top],
						nullptr, nullptr, p_slate_ex_1);
				}
			}

#if DF_USED_CUSTOM_MULTI_BRUSH
			p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_topright].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
			//top right
			DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
				sptr_slice_infor_->uvregin_slice[e_slice_topright],
				sptr_slice_infor_->paint_size_slice[e_slice_topright],
				sptr_slice_infor_->mat_slice[e_slice_topright]);

			//left right
			if (sptr_slice_infor_->b_valid[e_slice_left])
			{
				if (slice_image_.repeat == pixui::image_stretch)
				{
#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_left].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_left],
						sptr_slice_infor_->paint_size_slice[e_slice_left],
						sptr_slice_infor_->mat_slice[e_slice_left]);

#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_right].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_right],
						sptr_slice_infor_->paint_size_slice[e_slice_right],
						sptr_slice_infor_->mat_slice[e_slice_right]);
				}
				else
				{
					

#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_left].Get();
					p_slate_ex_1 = sptr_slice_infor_->sptr_multi_left_ex_.Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox_Repeat(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_left],
						sptr_slice_infor_->paint_size_slice[e_slice_left],
						v2d_image_org_,
						sptr_slice_infor_->mat_slice[e_slice_left],
						nullptr, nullptr, p_slate_ex_1);

#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_right].Get();
					p_slate_ex_1 = sptr_slice_infor_->sptr_multi_right_ex_.Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox_Repeat(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_right],
						sptr_slice_infor_->paint_size_slice[e_slice_right],
						v2d_image_org_,
						sptr_slice_infor_->mat_slice[e_slice_right],
						nullptr, nullptr, p_slate_ex_1);
				}
			}

#if DF_USED_CUSTOM_MULTI_BRUSH
			p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_bottomleft].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
			//bottom left 
			DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
				sptr_slice_infor_->uvregin_slice[e_slice_bottomleft],
				sptr_slice_infor_->paint_size_slice[e_slice_bottomleft],
				sptr_slice_infor_->mat_slice[e_slice_bottomleft]);

			//bottom
			if (sptr_slice_infor_->b_valid[e_slice_bottom])
			{
				if (slice_image_.repeat == pixui::image_stretch)
				{
#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_bottom].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_bottom],
						sptr_slice_infor_->paint_size_slice[e_slice_bottom],
						sptr_slice_infor_->mat_slice[e_slice_bottom]);
				}
				else
				{
#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_bottom].Get();
					p_slate_ex_1 = sptr_slice_infor_->sptr_multi_bottom_ex_.Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox_Repeat(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_bottom],
						sptr_slice_infor_->paint_size_slice[e_slice_bottom],
						v2d_image_org_,
						sptr_slice_infor_->mat_slice[e_slice_bottom],
						nullptr, nullptr, p_slate_ex_1);
				}
			}

#if DF_USED_CUSTOM_MULTI_BRUSH
			p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_bottomright].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
			//bottom right
			DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
				sptr_slice_infor_->uvregin_slice[e_slice_bottomright],
				sptr_slice_infor_->paint_size_slice[e_slice_bottomright],
				sptr_slice_infor_->mat_slice[e_slice_bottomright]);

			//center
			if (sptr_slice_infor_->b_valid[e_slice_center])
			{
				if (slice_image_.repeat == pixui::image_stretch)
				{
#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_center].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_center],
						sptr_slice_infor_->paint_size_slice[e_slice_center],
						sptr_slice_infor_->mat_slice[e_slice_center]);
				}
				else
				{
					FSlateBrush* p_slate_ex_2 = nullptr;
					FSlateBrush* p_slate_ex_3 = nullptr;
#if DF_USED_CUSTOM_MULTI_BRUSH
					p_draw_brush = sptr_slice_infor_->sptr_multi_brush_[e_slice_center].Get();
					p_slate_ex_1 = sptr_slice_infor_->sptr_multi_center_ex_[0].Get();
					p_slate_ex_2 = sptr_slice_infor_->sptr_multi_center_ex_[1].Get();
					p_slate_ex_3 = sptr_slice_infor_->sptr_multi_center_ex_[2].Get();
#endif //DF_USED_CUSTOM_MULTI_BRUSH
					DrawUVImageBox_Repeat(draw_params, n_cur_layer, p_draw_brush,
						sptr_slice_infor_->uvregin_slice[e_slice_center],
						sptr_slice_infor_->paint_size_slice[e_slice_center],
						v2d_image_org_,
						sptr_slice_infor_->mat_slice[e_slice_center],
						p_slate_ex_1,
						p_slate_ex_2,
						p_slate_ex_3);
				}
			}
		}
		else
		{
			if (!mBeIsRadiusImage)
			{
				p_draw_brush->Tiling = mEBrushTileType;
				p_draw_brush->SetUVRegion(mUvRegin);
			}

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
				color_linear
			);
		}
	}
	return 0;
}


FSlateBrush* PixDrawItemDrawImage::DrawBrush()
{
#if DF_USED_CUSTOM_MULTI_BRUSH
	if (sptr_multi_brush_.IsValid())
	{
		return sptr_multi_brush_.Get();
	}
#endif
	if (wptr_img_brush_.IsValid())
	{
		return wptr_img_brush_.Pin().Get();
	}
	return nullptr;
}


TSharedPtr<FSlateBrush> PixDrawItemDrawImage::MakeMultiBrush()
{
	TSharedPtr<FSlateBrush> sptr_slate_brush = nullptr;
	if (wptr_img_brush_.IsValid())
	{
		sptr_slate_brush = MakeShareable(new FSlateBrush());
		sptr_slate_brush->SetResourceObject(wptr_img_brush_.Pin().Get()->GetResourceObject());
		sptr_slate_brush->ImageSize = wptr_img_brush_.Pin().Get()->ImageSize;

		if (b_IsExternal_)
		{
			sptr_slate_brush->Tiling = wptr_img_brush_.Pin()->Tiling;
			sptr_slate_brush->SetUVRegion(wptr_img_brush_.Pin()->GetUVRegion());
		}
		else
		{
			sptr_slate_brush->Tiling = ESlateBrushTileType::NoTile;
			sptr_slate_brush->SetUVRegion(FBox2D(FVector2D(0.0f, 0.0f), FVector2D(1.0f, 1.0f)));
		}
	}
	return sptr_slate_brush;
}


void PixDrawItemDrawImage::DrawUVImageBox_Repeat(const PX_FOnPaintHandlerParams& draw_context, int32 n_cur_lay, FSlateBrush* p_slate_brush,
	const FBox2D& boxUvReginon, const FVector2D& paintSize, const FVector2D& imageSize,
	const pixui::matrix& drawMat, FSlateBrush* p_slate_brush_ex_w, FSlateBrush* p_slate_brush_ex_h, FSlateBrush* p_slate_brush_ex_wc)
{
	float w_draw = paintSize.X;
	float h_draw = paintSize.Y;
	float w_uv = boxUvReginon.GetSize().X * imageSize.X;
	float h_uv = boxUvReginon.GetSize().Y * imageSize.Y;

	float colCount = w_draw / w_uv;
	float rowCount = h_draw / h_uv;

	colCount = (0.999999 <= colCount && colCount <= 1.000001f) ? 1.0f : colCount;
	rowCount = (0.999999 <= rowCount && rowCount <= 1.000001f) ? 1.0f : rowCount;

	FSlateBrush* P_slate_draw_brush = p_slate_brush;

	bool b_row_last = false;
	bool b_col_last = false;

	for (float r = 0.0f; r < rowCount; r++)
	{
		P_slate_draw_brush = p_slate_brush;
		float rOffset = rowCount - r > 1.0f ? 1.0f : rowCount - r;

#if DF_USED_CUSTOM_MULTI_BRUSH
		if (r + 1.0f >= rowCount)
		{
			b_row_last = true;
			P_slate_draw_brush = p_slate_brush_ex_w ? p_slate_brush_ex_w : p_slate_brush;
		}
		else
		{
			P_slate_draw_brush = p_slate_brush;
		}
		b_col_last = false;
#endif //DF_USED_CUSTOM_MULTI_BRUSH
		
		for (float c = 0.0f; c < colCount; c++)
		{
			float cOffset = colCount - c > 1.0f ? 1.0f : colCount - c;
			FVector2D paintSize_temp = FVector2D(w_uv * cOffset, h_uv * rOffset);
			pixui::matrix tmpMat_temp;
			tmpMat_temp.initTranslate(c * w_uv, r * h_uv);
			tmpMat_temp = drawMat * tmpMat_temp;

			FVector2D start_uv(boxUvReginon.Min);
			FVector2D size_uv(w_uv * cOffset / imageSize.X, h_uv * rOffset / imageSize.Y);
			FBox2D uvRegin_temp(start_uv, start_uv + size_uv);

#if DF_USED_CUSTOM_MULTI_BRUSH
			if (c + 1.0f >= colCount)
			{
				b_col_last = true;
			}

			if (b_row_last)
			{
				if (b_col_last)
				{
					P_slate_draw_brush = p_slate_brush_ex_wc ? p_slate_brush_ex_wc : P_slate_draw_brush;
				}
			}
			else
			{
				if (b_col_last)
				{
					P_slate_draw_brush = p_slate_brush_ex_h ? p_slate_brush_ex_h : P_slate_draw_brush;
				}
			}
#endif //DF_USED_CUSTOM_MULTI_BRUSH

			DrawUVImageBox(draw_context, n_cur_lay, P_slate_draw_brush, uvRegin_temp, paintSize_temp, tmpMat_temp);
		}
	}
}


void PixDrawItemDrawImage::DrawUVImageBox(const PX_FOnPaintHandlerParams& draw_context, int32 n_cur_lay, FSlateBrush* p_slate_brush,
	const FBox2D& boxUvReginon, const FVector2D& paintSize,
	const pixui::matrix& drawMat)
{
	if (p_slate_brush)
	{
		p_slate_brush->SetUVRegion(boxUvReginon);

		FSlateLayoutTransform layoutTransform(FVector2D::ZeroVector);
		//layoutTransform = pDrawParam->Geometry.GetAccumulatedLayoutTransform();

		FSlateRenderTransform renderTransform2D(FMatrix2x2(drawMat[0], drawMat[1], drawMat[2], drawMat[3]), FVector2D(drawMat[4], drawMat[5]));

		FSlateDrawElement::MakeBox(
			draw_context.OutDrawElements,
			draw_context.Layer + n_cur_lay,
#if ENGINE_MINOR_VERSION > 20
			draw_context.Geometry.ToPaintGeometry(paintSize, layoutTransform, renderTransform2D, FVector2D::ZeroVector),
#else
			draw_context.Geometry.MakeChild(paintSize, layoutTransform, renderTransform2D, FVector2D::ZeroVector).ToPaintGeometry(),
#endif //ENGINE_MINOR_VERSION > 20
			p_slate_brush,
			ESlateDrawEffect::None,
			color_linear
		);
	}
}


