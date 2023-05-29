/**************************************************

**** @file:     PixMatBrush.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixMatBrush.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "PixUIDef.h"
#include "PixUILog.h"
#include "PixUtil.h"
#include "PixUIBPLibrary.h"
#include "PixImp/PixImpMat.h"

#include "px_plugindef.h"


#if DF_PIXUI_PROFILER
#include "PixUIProfiler/PxpResCount.h"
#endif //DF_PIXUI_PROFILER

//hpjy  资源flush宏，用于在同步资源加载时如果出现触发异步队列加载时的超时不上报告警信息
#ifndef ALLOW_FLUSHING
#define ALLOW_FLUSHING
#endif

//rectangle with radius
FString PixMatBrush::GetRadiusKey(const pixui::size& size_Rect, const pixui::BorderRadiuses& borderRadius)
{
    //format radius key
    return FString::Printf(TEXT("%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%.3f"),
        borderRadius.topLeftX / size_Rect.width, borderRadius.topLeftY / size_Rect.height,
        borderRadius.topRightX / size_Rect.width, borderRadius.topRightY / size_Rect.height,
        borderRadius.bottomLeftX / size_Rect.width, borderRadius.bottomLeftY / size_Rect.height,
        borderRadius.bottomRightX / size_Rect.width, borderRadius.bottomRightY / size_Rect.height);
}


//rectangle with radius color
FString PixMatBrush::GetMatBrushKey(const pixui::size& size_Rect, const pixui::color& color,
    const pixui::BorderRadiuses& borderRadius)
{
    //format rect radius key
    FString str_radius_key = FString::Printf(TEXT("rect_%x_"), color.toint());

    return str_radius_key + GetRadiusKey(size_Rect, borderRadius);
}


//same color rectangle border
FString PixMatBrush::GetMatBrushKey(const pixui::size& size_Rect, const unsigned int n_Widths[],
    const pixui::color& color)
{
    //format rect radius key
    return FString::Printf(TEXT("border_%.3f_%.3f_%.3f_%.3f_%x"),
        n_Widths[EPxBoderIndex::e_px_boder_index_top] / size_Rect.height, n_Widths[EPxBoderIndex::e_px_boder_index_left] / size_Rect.width,
        n_Widths[EPxBoderIndex::e_px_boder_index_bottom] / size_Rect.height, n_Widths[EPxBoderIndex::e_px_boder_index_right] / size_Rect.width,
        color.toint());
}


//different color rectangle border
FString PixMatBrush::GetMatBrushKey(const pixui::size& size_Rect, const unsigned int n_Widths[],
    const pixui::color colors[])
{
    return FString::Printf(TEXT("border_%.3f_%.3f_%.3f_%.3f_%x_%x_%x_%x"),
        n_Widths[EPxBoderIndex::e_px_boder_index_top] / size_Rect.height, n_Widths[EPxBoderIndex::e_px_boder_index_left] / size_Rect.width,
        n_Widths[EPxBoderIndex::e_px_boder_index_bottom] / size_Rect.height, n_Widths[EPxBoderIndex::e_px_boder_index_right] / size_Rect.width,
        colors[EPxBoderIndex::e_px_boder_index_top].toint(),
        colors[EPxBoderIndex::e_px_boder_index_left].toint(),
        colors[EPxBoderIndex::e_px_boder_index_bottom].toint(),
        colors[EPxBoderIndex::e_px_boder_index_right].toint());
}


//same color rectangle border with radius
FString PixMatBrush::GetMatBrushKey(const pixui::size& size_Rect, const unsigned int n_Widths[],
    const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
{
    return GetRadiusKey(size_Rect, borderRadius) + GetMatBrushKey(size_Rect, n_Widths, color);
}


// different color rectangle border with radius
FString PixMatBrush::GetMatBrushKey(const pixui::size& size_Rect, const unsigned int n_Widths[],
    const pixui::color colors[], const pixui::BorderRadiuses& borderRadius)
{
    return GetRadiusKey(size_Rect, borderRadius) + GetMatBrushKey(size_Rect, n_Widths, colors);
}


EPxMatBrushType PixMatBrush::MatBrushType(const pixui::size& size_Rect, const pixui::color& color,
	const pixui::BorderRadiuses& borderRadius)
{
	if(borderRadius.topLeftX == borderRadius.topRightX && borderRadius.topRightX == borderRadius.bottomLeftX &&
		borderRadius.topLeftX == borderRadius.bottomRightX && borderRadius.topLeftY == borderRadius.topRightY &&
		borderRadius.topLeftY == borderRadius.bottomLeftY && borderRadius.topLeftY == borderRadius.bottomRightY &&
		borderRadius.topLeftX == size_Rect.width / 2.0f && borderRadius.topLeftY == size_Rect.height / 2.0f)
	{
		return e_px_mat_brush_rect_round;
	}
	return e_px_mat_brush_rect_corner;
}


EPxMatBrushType PixMatBrush::MatBrushType(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color& color)
{
	return e_px_mat_brush_border_rect;
}


EPxMatBrushType PixMatBrush::MatBrushType(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color colors[])
{
	return e_px_mat_brush_border_rect_difcolor;
}


EPxMatBrushType PixMatBrush::MatBrushType(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
{
	return e_px_mat_brush_border_radius;
}


EPxMatBrushType PixMatBrush::MatBrushType(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color colors[], const pixui::BorderRadiuses& borderRadius)
{
	return e_px_mat_brush_border_radius_difcolor;
}

PixMatBrush::PixMatBrush(EPxMatBrushType e_type)
    : b_UsedMark_(false), wptr_brush_res_obj_(nullptr),
	sptr_SlateMatBrush_(nullptr), e_type_(e_type), n_used_ref_(0)
{
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixMatBrush new       %d", ++ResItemCount::PixMatBrushTotalCount());
	PxLog_Trace("PixMatBrush new type:%d count: %d", e_type_, ResItemCount::PixMatBrushAdd(e_type_));
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}


//rectangle with radius
PixMatBrush::PixMatBrush(const pixui::size& size_Rect, const pixui::color& color,
	const pixui::BorderRadiuses& borderRadius) : PixMatBrush(e_px_mat_brush_rect_corner)
{
    //different radius
    FString fstr_MatPath = UPixUIBPLibrary::PixUI_GetMatRootPath() + DF_MAT_RECT_RADIUS_CORNER_PATH;
    int n_MatType = 1;

    if (borderRadius.topLeftX == borderRadius.topRightX && borderRadius.topRightX == borderRadius.bottomLeftX &&
        borderRadius.topLeftX == borderRadius.bottomRightX && borderRadius.topLeftY == borderRadius.topRightY &&
        borderRadius.topRightY == borderRadius.bottomLeftY && borderRadius.topLeftY == borderRadius.bottomRightY &&
        borderRadius.topLeftX == size_Rect.width / 2.0f && borderRadius.topLeftY == size_Rect.height / 2.0f)
    {
        //same radius for all corner
        fstr_MatPath = UPixUIBPLibrary::PixUI_GetMatRootPath() + DF_MAT_RECT_RADIUS_PATH;
        n_MatType = 0;
    }
    
    UMaterialInstanceDynamic* pMatInter = CreateMatBrush(fstr_MatPath, FVector2D(size_Rect.width, size_Rect.height));
    if (pMatInter)
    {
        //the color will be set by FSlateBrush when it draw as box
        //pMatInter->SetVectorParameterValue("color", FColor(color.red(), color.green(), color.blue(), color.alpha()));
        if (n_MatType == 0)
        {
            // same radius
            pMatInter->SetScalarParameterValue("radius", 0.5f);
			e_type_ = e_px_mat_brush_rect_round;
        }
        else
        {
            //different radius,set each corner radius
            pMatInter->SetScalarParameterValue("radius_top_left_x", borderRadius.topLeftX / size_Rect.width);
            pMatInter->SetScalarParameterValue("radius_top_left_y", borderRadius.topLeftY / size_Rect.height);

            pMatInter->SetScalarParameterValue("radius_top_right_x", borderRadius.topRightX / size_Rect.width);
            pMatInter->SetScalarParameterValue("radius_top_right_y", borderRadius.topRightY / size_Rect.height);

            pMatInter->SetScalarParameterValue("radius_bottom_left_x", borderRadius.bottomLeftX / size_Rect.width);
            pMatInter->SetScalarParameterValue("radius_bottom_left_y", borderRadius.bottomLeftY / size_Rect.height);

            pMatInter->SetScalarParameterValue("radius_bottom_right_x", borderRadius.bottomRightX / size_Rect.width);
            pMatInter->SetScalarParameterValue("radius_bottom_right_y", borderRadius.bottomRightY / size_Rect.height);
        }
    }

	fstr_key_ = GetMatBrushKey(size_Rect, color, borderRadius);
}


//set border width
void SetBorderWidth(UMaterialInstanceDynamic* p_mat_inter, const unsigned int nWidths[], const pixui::size& size_rect)
{
    p_mat_inter->SetScalarParameterValue("width_top", nWidths[EPxBoderIndex::e_px_boder_index_top] / size_rect.height);
    p_mat_inter->SetScalarParameterValue("width_left", nWidths[EPxBoderIndex::e_px_boder_index_left] / size_rect.width);
    p_mat_inter->SetScalarParameterValue("width_right", nWidths[EPxBoderIndex::e_px_boder_index_right] / size_rect.width);
    p_mat_inter->SetScalarParameterValue("width_bottom", nWidths[EPxBoderIndex::e_px_boder_index_bottom] / size_rect.height);
}


//set border colors
void SetBorderColor(UMaterialInstanceDynamic* p_mat_inter, const pixui::color& color)
{
    p_mat_inter->SetVectorParameterValue("color", FColor(color.red(), color.green(), color.blue(), color.alpha()));
}


//set border radius
void SetBorderRadius(UMaterialInstanceDynamic* p_mat_inter, const pixui::BorderRadiuses& radius, const pixui::size& size_rect)
{
    p_mat_inter->SetScalarParameterValue("radius_top_left_x", radius.topLeftX / size_rect.width);
    p_mat_inter->SetScalarParameterValue("radius_top_left_y", radius.topLeftY / size_rect.height);
    p_mat_inter->SetScalarParameterValue("radius_bottom_left_x", radius.bottomLeftX / size_rect.width);
    p_mat_inter->SetScalarParameterValue("radius_bottom_left_y", radius.bottomLeftY / size_rect.height);

    p_mat_inter->SetScalarParameterValue("radius_top_right_x", radius.topRightX / size_rect.width);
    p_mat_inter->SetScalarParameterValue("radius_top_right_y", radius.topRightY / size_rect.height);
    p_mat_inter->SetScalarParameterValue("radius_bottom_right_x", radius.bottomRightX / size_rect.width);
    p_mat_inter->SetScalarParameterValue("radius_bottom_right_y", radius.bottomRightY / size_rect.height);
}


//set border colors
void SetBorderColors(UMaterialInstanceDynamic* p_mat_inter, const pixui::color colors[])
{
    p_mat_inter->SetVectorParameterValue("color_top", PixUtil::PixColor2FColor(colors[EPxBoderIndex::e_px_boder_index_top]));

    p_mat_inter->SetVectorParameterValue("color_left", PixUtil::PixColor2FColor(colors[EPxBoderIndex::e_px_boder_index_left]));

    p_mat_inter->SetVectorParameterValue("color_right", PixUtil::PixColor2FColor(colors[EPxBoderIndex::e_px_boder_index_right]));

    p_mat_inter->SetVectorParameterValue("color_bottom", PixUtil::PixColor2FColor(colors[EPxBoderIndex::e_px_boder_index_bottom]));
}


//same color rectangle border
PixMatBrush::PixMatBrush(const pixui::size& size_Rect, const unsigned int n_Widths[], const pixui::color& color)
    : PixMatBrush(e_px_mat_brush_border_rect)
{
    FString fstr_MatPath = UPixUIBPLibrary::PixUI_GetMatRootPath() + DF_MAT_BORDER_PATH;
    UMaterialInstanceDynamic* p_mat_inter = CreateMatBrush( fstr_MatPath, FVector2D(size_Rect.width, size_Rect.height));
    if (p_mat_inter)
    {
        SetBorderColor(p_mat_inter,color);
        SetBorderWidth(p_mat_inter, n_Widths, size_Rect);

		fstr_key_ = GetMatBrushKey(size_Rect, n_Widths, color);
    }
}

//different color rectangle border
PixMatBrush::PixMatBrush(const pixui::size& size_Rect, const unsigned int n_Widths[], const pixui::color colors[])
    : PixMatBrush(e_px_mat_brush_border_rect_difcolor)
{
    FString fstr_MatPath = UPixUIBPLibrary::PixUI_GetMatRootPath() + DF_MAT_BORDER_COLOR_PATH;
    UMaterialInstanceDynamic* p_mat_inter = CreateMatBrush(fstr_MatPath, FVector2D(size_Rect.width, size_Rect.height));
    if (p_mat_inter)
    {
        SetBorderColors(p_mat_inter, colors);
        SetBorderWidth(p_mat_inter, n_Widths, size_Rect);
        fstr_key_ = GetMatBrushKey(size_Rect, n_Widths, colors);
    }
}


//same color rectangle border with radius
PixMatBrush::PixMatBrush(const pixui::size& size_Rect, const unsigned int n_Widths[], const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
    : PixMatBrush(e_px_mat_brush_border_radius)
{
    FString fstr_MatPath = UPixUIBPLibrary::PixUI_GetMatRootPath() + DF_MAT_BORDER_RADIUS_PATH;
    UMaterialInstanceDynamic* p_mat_inter = CreateMatBrush(fstr_MatPath, FVector2D(size_Rect.width, size_Rect.height));
    if (p_mat_inter)
    {
        SetBorderColor(p_mat_inter, color);
        SetBorderWidth(p_mat_inter, n_Widths, size_Rect);
        SetBorderRadius(p_mat_inter, borderRadius, size_Rect);

		fstr_key_ = GetMatBrushKey(size_Rect, n_Widths, color, borderRadius);
    }
}


//different color rectangle border with radius
PixMatBrush::PixMatBrush(const pixui::size& size_Rect, const unsigned int n_Widths[], const pixui::color colors[], const pixui::BorderRadiuses& borderRadius)
    : PixMatBrush(e_px_mat_brush_border_radius_difcolor)
{
    FString fstr_MatPath = UPixUIBPLibrary::PixUI_GetMatRootPath() + DF_MAT_BORDER_COLOR_RADIUS_PATH;
    UMaterialInstanceDynamic* p_mat_inter = CreateMatBrush(fstr_MatPath, FVector2D(size_Rect.width, size_Rect.height));
    if (p_mat_inter)
    {
        SetBorderColors(p_mat_inter, colors);
        SetBorderWidth(p_mat_inter, n_Widths, size_Rect);
        SetBorderRadius(p_mat_inter, borderRadius, size_Rect);

		fstr_key_ = GetMatBrushKey(size_Rect, n_Widths, colors, borderRadius);
    }
}


PixMatBrush::~PixMatBrush()
{
    if (sptr_SlateMatBrush_.IsValid() && sptr_SlateMatBrush_->GetResourceObject() && wptr_brush_res_obj_.IsValid())
    {
        sptr_SlateMatBrush_->GetResourceObject()->RemoveFromRoot();
    }
	wptr_brush_res_obj_ = nullptr;
    sptr_SlateMatBrush_ = nullptr;

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixMatBrush delete    %d", --ResItemCount::PixMatBrushTotalCount());
	PxLog_Trace("PixMatBrush delete  type:%d   count:%d", e_type_, ResItemCount::PixMatBrushDec(e_type_));
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}


void PixMatBrush::AddRef()
{
	n_used_ref_++;
	//PxLog_Trace("PixMatBrush::AddRef cur use %p ref:%d  key:%s", this, n_used_ref_, TCHAR_TO_UTF8(*Key()));
}


bool PixMatBrush::DecRef() 
{
	//PxLog_Trace("PixMatBrush::DecRef cur use %p ref:%d  key:%s", this, n_used_ref_ - 1, TCHAR_TO_UTF8(*Key()));
	if ((--n_used_ref_) <= 0)
	{
		PixImpMat::RemoveMatBrush(Key());
		return true;
	}
	return false;
}

FString PixMatBrush::Key()
{
	return fstr_key_;
}

void PixMatBrush::SetKey(const FString& fstr_new_key) 
{
// 	auto wptr_bursh = PixImpMat::FindMatBrush(fstr_new_key);
// 	if (wptr_bursh.IsValid())
// 	{
// 		PxLog_Error("PixMatBrush::SetKey HAVE SAME KEY IN ARRAY!!!!!!!!!!!");
// 	}
	fstr_key_ = fstr_new_key;
}




#define DF_MAT_BRUSH_CHECK_TYPE(...) if (MatBrushType(__VA_ARGS__) != BrushType()){													\
	PxLog_Error("PixMatBrush::ResetParams brush type diffrent param type:%d cur type:%d", MatBrushType(__VA_ARGS__), BrushType());	\
	return;																															\
}


void PixMatBrush::ResetParams(const pixui::size& size_Rect, const pixui::color& color,
	const pixui::BorderRadiuses& borderRadius)
{
	DF_MAT_BRUSH_CHECK_TYPE(size_Rect, color, borderRadius);
	if (sptr_SlateMatBrush_.IsValid())
	{
		UMaterialInstanceDynamic* p_mat_inter = Cast<UMaterialInstanceDynamic>(sptr_SlateMatBrush_->GetResourceObject());
		if (p_mat_inter && wptr_brush_res_obj_.IsValid())
		{
			int n_MatType = 1;

			if (borderRadius.topLeftX == borderRadius.topRightX && borderRadius.topRightX == borderRadius.bottomLeftX &&
				borderRadius.topLeftX == borderRadius.bottomRightX && borderRadius.topLeftY == borderRadius.topRightY &&
				borderRadius.topRightY == borderRadius.bottomLeftY && borderRadius.topLeftY == borderRadius.bottomRightY &&
				borderRadius.topLeftX == size_Rect.width / 2.0f && borderRadius.topLeftY == size_Rect.height / 2.0f)
			{
				//same radius for all corner
				n_MatType = 0;
			}

			{
				//the color will be set by FSlateBrush when it draw as box
				//pMatInter->SetVectorParameterValue("color", FColor(color.red(), color.green(), color.blue(), color.alpha()));
				if (n_MatType == 0)
				{
					// same radius
					p_mat_inter->SetScalarParameterValue("radius", 0.5f);
				}
				else
				{
					//different radius,set each corner radius
					p_mat_inter->SetScalarParameterValue("radius_top_left_x", borderRadius.topLeftX / size_Rect.width);
					p_mat_inter->SetScalarParameterValue("radius_top_left_y", borderRadius.topLeftY / size_Rect.height);

					p_mat_inter->SetScalarParameterValue("radius_top_right_x", borderRadius.topRightX / size_Rect.width);
					p_mat_inter->SetScalarParameterValue("radius_top_right_y", borderRadius.topRightY / size_Rect.height);

					p_mat_inter->SetScalarParameterValue("radius_bottom_left_x", borderRadius.bottomLeftX / size_Rect.width);
					p_mat_inter->SetScalarParameterValue("radius_bottom_left_y", borderRadius.bottomLeftY / size_Rect.height);

					p_mat_inter->SetScalarParameterValue("radius_bottom_right_x", borderRadius.bottomRightX / size_Rect.width);
					p_mat_inter->SetScalarParameterValue("radius_bottom_right_y", borderRadius.bottomRightY / size_Rect.height);
				}
			}

			SetKey(GetMatBrushKey(size_Rect, color, borderRadius));
		}
		else
		{
			PxLog_Error("PixMatBrush::ResetParams error p_mat_inter invalid");
		}
	}
	else
	{
		PxLog_Error("PixMatBrush::ResetParams error brush invalid");
	}
}


void PixMatBrush::ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color& color)
{
	DF_MAT_BRUSH_CHECK_TYPE(size_Rect, n_Widths, color);

	if (sptr_SlateMatBrush_.IsValid())
	{
		UMaterialInstanceDynamic* p_mat_inter = Cast<UMaterialInstanceDynamic>(sptr_SlateMatBrush_->GetResourceObject());
		if (p_mat_inter && wptr_brush_res_obj_.IsValid())
		{
			SetBorderColor(p_mat_inter, color);
			SetBorderWidth(p_mat_inter, n_Widths, size_Rect);

			SetKey(GetMatBrushKey(size_Rect, n_Widths, color));
		}
		else
		{
			PxLog_Error("PixMatBrush::ResetParams error p_mat_inter invalid");
		}
	}
	else
	{
		PxLog_Error("PixMatBrush::ResetParams error brush invalid");
	}
}

void PixMatBrush::ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color colors[])
{
	DF_MAT_BRUSH_CHECK_TYPE(size_Rect, n_Widths, colors);

	if (sptr_SlateMatBrush_.IsValid())
	{
		UMaterialInstanceDynamic* p_mat_inter = Cast<UMaterialInstanceDynamic>(sptr_SlateMatBrush_->GetResourceObject());
		if (p_mat_inter && wptr_brush_res_obj_.IsValid())
		{
			SetBorderColors(p_mat_inter, colors);
			SetBorderWidth(p_mat_inter, n_Widths, size_Rect);

			SetKey(GetMatBrushKey(size_Rect, n_Widths, colors));
		}
		else
		{
			PxLog_Error("PixMatBrush::ResetParams error p_mat_inter invalid");
		}

	}
	else
	{
		PxLog_Error("PixMatBrush::ResetParams error brush invalid");
	}
}

void PixMatBrush::ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
{
	DF_MAT_BRUSH_CHECK_TYPE(size_Rect, n_Widths, color, borderRadius);

	if (sptr_SlateMatBrush_.IsValid())
	{
		UMaterialInstanceDynamic* p_mat_inter = Cast<UMaterialInstanceDynamic>(sptr_SlateMatBrush_->GetResourceObject());
		if (p_mat_inter && wptr_brush_res_obj_.IsValid())
		{
			SetBorderColor(p_mat_inter, color);
			SetBorderWidth(p_mat_inter, n_Widths, size_Rect);
			SetBorderRadius(p_mat_inter, borderRadius, size_Rect);

			SetKey(GetMatBrushKey(size_Rect, n_Widths, color, borderRadius));
		}
		else
		{
			PxLog_Error("PixMatBrush::ResetParams error p_mat_inter invalid");
		}
	}
	else
	{
		PxLog_Error("PixMatBrush::ResetParams error brush invalid");
	}
}

void PixMatBrush::ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color colors[], const pixui::BorderRadiuses& borderRadius)
{
	DF_MAT_BRUSH_CHECK_TYPE(size_Rect, n_Widths, colors, borderRadius);

	if (sptr_SlateMatBrush_.IsValid())
	{
		UMaterialInstanceDynamic* p_mat_inter = Cast<UMaterialInstanceDynamic>(sptr_SlateMatBrush_->GetResourceObject());
		if (p_mat_inter && wptr_brush_res_obj_.IsValid())
		{
			SetBorderColors(p_mat_inter, colors);
			SetBorderWidth(p_mat_inter, n_Widths, size_Rect);
			SetBorderRadius(p_mat_inter, borderRadius, size_Rect);

			SetKey(GetMatBrushKey(size_Rect, n_Widths, colors, borderRadius));
		}
		else
		{
			PxLog_Error("PixMatBrush::ResetParams error p_mat_inter invalid");
		}
	}
	else
	{
		PxLog_Error("PixMatBrush::ResetParams error brush invalid");
	}
}

FSlateBrush* PixMatBrush::GetBrush()
{
    if (sptr_SlateMatBrush_.IsValid())
    {
        //GetBrush Mark use 
        b_UsedMark_ = true;
        return sptr_SlateMatBrush_.Get();
    }
    return nullptr;
}


bool PixMatBrush::BeClearBrush()
{
    if (b_UsedMark_)
    {
        //reset mark for clear, if next check is unused and do clean;
        b_UsedMark_ = false;
        return false;
    }
    
    return true;
}


//create UMaterialInstance
UMaterialInstanceDynamic* PixMatBrush::CreateMatBrush(const FString& fstr_MatPath, const FVector2D& size_Rect)
{
	UMaterialInstanceDynamic* p_mat_inter = nullptr;
	sptr_SlateMatBrush_ = LoadSlateBrushFromMaterial(fstr_MatPath, size_Rect);

	if (sptr_SlateMatBrush_.IsValid())
	{
		p_mat_inter = Cast<UMaterialInstanceDynamic>(sptr_SlateMatBrush_->GetResourceObject());
		wptr_brush_res_obj_ = p_mat_inter;
		if (p_mat_inter)
		{
			p_mat_inter->AddToRoot();
		}
		else
		{
			PxLog_Error("PixMatBrush::CreateMatBrush error can not load p_mat_inter path:%s", TCHAR_TO_UTF8(*fstr_MatPath));
		}
	}
	else
	{
		PxLog_Error("PixMatBrush::CreateMatBrush error can not load mat by path:%s", TCHAR_TO_UTF8(*fstr_MatPath));
	}
//     UMaterialInterface* p_tmp_mat = nullptr;
// 	ALLOW_FLUSHING
//     p_tmp_mat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), NULL, *fstr_MatPath));
//     if (p_tmp_mat)
//     {
//         //UObject create and add to root
//         
// 		p_mat_inter = UMaterialInstanceDynamic::Create(p_tmp_mat, nullptr);
// 		wptr_brush_res_obj_ = p_mat_inter;
// 
//         p_mat_inter->AddToRoot();
// 
// 		MakeShareable(new FSlateMaterialBrush(*p_mat_inter, size_Rect));
//     }
//     else
//     {
//         PxLog_Error("PixMatBrush::CreateMatBrush error can not load mat by path:%s", TCHAR_TO_UTF8(*fstr_MatPath));
//     }

    return p_mat_inter;
}


//normal path: /PixUI/mat/mat_xxx
TSharedPtr<FSlateMaterialBrush> PixMatBrush::LoadSlateBrushFromMaterial(const FString& fst_url, const FVector2D& size_Rect)
{
	UMaterialInstanceDynamic* p_mat_inter = nullptr;
	UMaterialInterface* p_tmp_mat = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), NULL, *fst_url));
	if (p_tmp_mat)
	{
		p_mat_inter = UMaterialInstanceDynamic::Create(p_tmp_mat, nullptr);
	}

	if (p_mat_inter)
	{
		return MakeShareable(new FSlateMaterialBrush(*p_mat_inter, size_Rect));
	}
	return nullptr;
}

PixSharedMatBrush::PixSharedMatBrush(TWeakPtr<PixMatBrush>& wptr_pix_mat_brush)
{
	wptr_pix_mat_brush_ = wptr_pix_mat_brush;

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	PxLog_Trace("PixSharedMatBrush  new      %d", ++ResItemCount::PixSharedMatBrushCount());
#endif //UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
}


PixSharedMatBrush::~PixSharedMatBrush()
{
	if (wptr_pix_mat_brush_.IsValid())
	{
		wptr_pix_mat_brush_.Pin()->DecRef();
	}
	wptr_pix_mat_brush_ = nullptr;

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	PxLog_Trace("PixSharedMatBrush  delete    %d", --ResItemCount::PixSharedMatBrushCount());
#endif //UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
}



#define DF_RESET_MAT_BRUSH( ... )  FString fst_key = PixMatBrush::GetMatBrushKey(__VA_ARGS__);	\
	if (wptr_pix_mat_brush_.IsValid())															\
	{																							\
		/*same key*/																			\
		if (wptr_pix_mat_brush_.Pin()->Key() == fst_key)										\
		{																						\
			return;																				\
		}																						\
		/*smae brush in used array*/															\
		TWeakPtr<PixMatBrush> wptr_used_mat_brush = PixImpMat::FindMatBrush(fst_key);			\
		if (wptr_used_mat_brush.IsValid())														\
		{																						\
			wptr_used_mat_brush.Pin()->AddRef();												\
			wptr_pix_mat_brush_.Pin()->DecRef();												\
			wptr_pix_mat_brush_ = wptr_used_mat_brush;											\
			return;																				\
		}																						\
		/*same type*/																			\
		if (wptr_pix_mat_brush_.Pin()->BrushType() == PixMatBrush::MatBrushType(__VA_ARGS__))	\
		{																						\
			if (IsUsedBySelf())																	\
			{																					\
				wptr_pix_mat_brush_.Pin()->ResetParams(__VA_ARGS__);							\
				return;																			\
			}																					\
		}																						\
		/*need new one brush*/																	\
		wptr_pix_mat_brush_.Pin()->DecRef();													\
	}																							\
	/*try get used key*/																		\
	TWeakPtr<PixMatBrush> wptr_used_mat_brush = PixImpMat::FindMatBrush(fst_key);				\
	if (wptr_used_mat_brush.IsValid())															\
	{																							\
		wptr_used_mat_brush.Pin()->AddRef();													\
		wptr_pix_mat_brush_ = wptr_used_mat_brush;												\
		return;																					\
	}																							\
	/*new mat brush*/																			\
	TSharedPtr<PixMatBrush> sptr_MatBrush = PixImpMat::Get()->GetMatBrushFromPools(__VA_ARGS__);\
	if (sptr_MatBrush.IsValid())																\
	{																							\
		if (fst_key != sptr_MatBrush->Key())													\
		{																						\
			sptr_MatBrush->ResetParams(__VA_ARGS__);											\
		}																						\
		PixImpMat::AddMatBrush(sptr_MatBrush);													\
		sptr_MatBrush->AddRef();																\
		wptr_pix_mat_brush_ = sptr_MatBrush;													\
	}																							\
	else {																						\
		PxLog_Error("PixImpMat::Get()->GetMatBrushFromPools error");							\
	}



void PixSharedMatBrush::ResetParams(const pixui::size& size_Rect, const pixui::color& color,
	const pixui::BorderRadiuses& borderRadius)
{
	DF_RESET_MAT_BRUSH(size_Rect, color, borderRadius);
}


void PixSharedMatBrush::ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color& color)
{
	DF_RESET_MAT_BRUSH(size_Rect, n_Widths, color);
}


void PixSharedMatBrush::ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color colors[])
{
	DF_RESET_MAT_BRUSH(size_Rect, n_Widths, colors);
}


void PixSharedMatBrush::ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
{
	DF_RESET_MAT_BRUSH(size_Rect, n_Widths, color, borderRadius);
}


void PixSharedMatBrush::ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color colors[], const pixui::BorderRadiuses& borderRadius)
{
	DF_RESET_MAT_BRUSH(size_Rect, n_Widths, colors, borderRadius);
}