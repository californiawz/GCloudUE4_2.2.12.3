/**************************************************

**** @file:     PixMatBrush.h

**** @brief:    Material brush for shader,Used for special border rectangle and other effects

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "CoreMinimal.h"
#include "Slate.h"
#include "SlateCore.h"
#include "SlateMaterialBrush.h"

#include "hf_typedef.h"


enum EPxMatBrushType
{
	e_px_mat_brush_rect_round,
	e_px_mat_brush_rect_corner,
	e_px_mat_brush_border_rect,
	e_px_mat_brush_border_rect_difcolor,
	e_px_mat_brush_border_radius,
	e_px_mat_brush_border_radius_difcolor,

	e_px_mat_brush_count
};

class PixMatBrush
{
public:
    //rectangle with radius
    static FString GetRadiusKey(const pixui::size& size_Rect, const pixui::BorderRadiuses& borderRadius);

    //rectangle with radius color
    static FString GetMatBrushKey(const pixui::size& size_Rect, const pixui::color& color,
        const pixui::BorderRadiuses& borderRadius);

    //same color rectangle border
    static FString GetMatBrushKey(const pixui::size& size_Rect, const unsigned int n_Widths[],
        const pixui::color& color);

    //different color rectangle border
    static FString GetMatBrushKey(const pixui::size& size_Rect, const unsigned int n_Widths[],
        const pixui::color colors[]);

    //same color rectangle border with radius
    static FString GetMatBrushKey(const pixui::size& size_Rect, const unsigned int n_Widths[],
        const pixui::color& color, const pixui::BorderRadiuses& borderRadius);

    // different color rectangle border with radius
    static FString GetMatBrushKey(const pixui::size& size_Rect,const unsigned int n_Widths[],
        const pixui::color colors[], const pixui::BorderRadiuses& borderRadius);


	//rectangle with radius color
	static EPxMatBrushType MatBrushType(const pixui::size& size_Rect, const pixui::color& color,
		const pixui::BorderRadiuses& borderRadius);

	//same color rectangle border
	static EPxMatBrushType MatBrushType(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color& color);

	//different color rectangle border
	static EPxMatBrushType MatBrushType(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color colors[]);

	//same color rectangle border with radius
	static EPxMatBrushType MatBrushType(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color& color, const pixui::BorderRadiuses& borderRadius);

	// different color rectangle border with radius
	static EPxMatBrushType MatBrushType(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color colors[], const pixui::BorderRadiuses& borderRadius);

protected:
    //default protected
    PixMatBrush(EPxMatBrushType e_type);

public:
    ~PixMatBrush();

public:
	void AddRef();
	bool DecRef();
	int UsedRef() {
		return n_used_ref_;
	}

	FString Key();

	void SetKey(const FString& fstr_new_key);

public:
    //rectangle with radius
    PixMatBrush(const pixui::size& size_Rect, const pixui::color& color,
        const pixui::BorderRadiuses& borderRadius);

    //same color rectangle border
    PixMatBrush(const pixui::size& size_Rect,const unsigned int n_Widths[],
        const pixui::color& color);

    //different color rectangle border
    PixMatBrush(const pixui::size& size_Rect,const unsigned int n_Widths[],
        const pixui::color colors[]);

    //same color rectangle border with radius
    PixMatBrush(const pixui::size& size_Rect,const unsigned int n_Widths[],
        const pixui::color& color, const pixui::BorderRadiuses& borderRadius);

    //different color rectangle border with radius
    PixMatBrush(const pixui::size& size_Rect,const unsigned int n_Widths[],
        const pixui::color colors[], const pixui::BorderRadiuses& borderRadius);

public:
	void ResetParams(const pixui::size& size_Rect, const pixui::color& color,
		const pixui::BorderRadiuses& borderRadius);

	void ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color& color);

	void ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color colors[]);

	void ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color& color, const pixui::BorderRadiuses& borderRadius);

	void ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color colors[], const pixui::BorderRadiuses& borderRadius);

	EPxMatBrushType BrushType() {
		return e_type_;
	}
public:
    //get slate brush
    FSlateBrush* GetBrush();

    //Check if the brush is used
    //return true is used,false is not used
    bool BeClearBrush();

    //create UMaterialInstance
    UMaterialInstanceDynamic* CreateMatBrush(const FString& fstr_MatPath,const FVector2D& size_Rect);

public:
	//normal path: /PixUI/mat/mat_xxx
	static TSharedPtr<FSlateMaterialBrush> LoadSlateBrushFromMaterial(const FString& fst_url, const FVector2D& size_Rect);

private:
    //used mark,If it is not used, it will be automatically released
    bool b_UsedMark_;

	//slate brush resource object
	TWeakObjectPtr<UMaterialInstanceDynamic> wptr_brush_res_obj_;

    //slate material brush
    TSharedPtr<FSlateMaterialBrush>  sptr_SlateMatBrush_;

	EPxMatBrushType e_type_;

	int n_used_ref_;

	FString fstr_key_;
};



class PixSharedMatBrush
{
public:
	PixSharedMatBrush(TWeakPtr<PixMatBrush>& wptr_pix_mat_brush);
	~PixSharedMatBrush();

public:
	TWeakPtr<PixMatBrush> GetMatBrush() {
		return wptr_pix_mat_brush_;
	}
	FSlateBrush* GetBrush() {
		if (wptr_pix_mat_brush_.IsValid())
		{
			return wptr_pix_mat_brush_.Pin()->GetBrush();
		}
		return nullptr;
	}
	void SetMatBrush(TWeakPtr<PixMatBrush>& wptr_pix_mat_brush) {
		if (wptr_pix_mat_brush_.IsValid())
		{
			wptr_pix_mat_brush_.Pin()->DecRef();
		}
		wptr_pix_mat_brush_ = wptr_pix_mat_brush;
	}
	void ResetMatBrush() {
		if (wptr_pix_mat_brush_.IsValid())
		{
			wptr_pix_mat_brush_.Pin()->DecRef();
		}
		wptr_pix_mat_brush_ = nullptr;
	}

	bool IsUsedBySelf() 
	{
		if (wptr_pix_mat_brush_.IsValid())
		{
			return wptr_pix_mat_brush_.Pin()->UsedRef() == 1;
		}
		return false;
	}

public:
	void ResetParams(const pixui::size& size_Rect, const pixui::color& color,
		const pixui::BorderRadiuses& borderRadius);

	void ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color& color);

	void ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color colors[]);

	void ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color& color, const pixui::BorderRadiuses& borderRadius);

	void ResetParams(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color colors[], const pixui::BorderRadiuses& borderRadius);

private:
	TWeakPtr<PixMatBrush> wptr_pix_mat_brush_;
};