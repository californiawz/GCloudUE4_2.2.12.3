/**************************************************

**** @file:     PixImpMat.h

**** @brief:    pixui material brush manager implementation

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once
#include "CoreMinimal.h"
#include "Slate.h"
#include "SlateCore.h"

#include "PixImpBase.h"

#include "hf_typedef.h"

class PixSharedMatBrush;
//class PixMatBrush;

#include "PixBrush/PixMatBrush.h"

class PixImpMat : public PixImpBase
{
    //register imp
    DF_REG_PX_IMP(PixImpMat)

protected:
    PixImpMat();

public:
    virtual ~PixImpMat();

protected:
    /************************************************************************/
    /** PixImpBase implementation */
    virtual void OnStartup() override;
    virtual void OnTick(const float f_DeltaTime) override;
	virtual void OnClear() override;
    virtual void OnShutdown() override;
    /** PixImpBase implementation */
    /************************************************************************/

protected:
	TArray<TSharedPtr<PixMatBrush>>& Brushs() {
        return ary_mat_brush_;
    }

	void PutMatBrushToFreePool(TSharedPtr<PixMatBrush>& sptr_mat_brush);

public:
	static void ShowPixImpMatInfor();

public:
	TSharedPtr<PixMatBrush> GetMatBrushFromPools(const pixui::size& size_Rect, const pixui::color& color, const pixui::BorderRadiuses& borderRadius);
	TSharedPtr<PixMatBrush> GetMatBrushFromPools(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color& color);
	TSharedPtr<PixMatBrush> GetMatBrushFromPools(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color colors[]);
	TSharedPtr<PixMatBrush> GetMatBrushFromPools(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color& color, const pixui::BorderRadiuses& borderRadius);
	TSharedPtr<PixMatBrush> GetMatBrushFromPools(const pixui::size& size_Rect, const unsigned int n_Widths[],
		const pixui::color colors[], const pixui::BorderRadiuses& borderRadius);

    void AllClear();

public:
    //get rect brush
    static TSharedPtr<PixSharedMatBrush> GetRectBrush(const pixui::size& size_Rect, const pixui::color& color, const pixui::BorderRadiuses& borderRadius);

    //get border brush
    static TSharedPtr<PixSharedMatBrush> GetBorderBrush(const pixui::size& size_Rect, const unsigned int n_Widths[],
        const pixui::color& color);

    //get border brush
    static TSharedPtr<PixSharedMatBrush> GetBorderBrush(const pixui::size& size_Rect, const unsigned int n_Widths[],
        const pixui::color colors[]);

    //get border brush
    static TSharedPtr<PixSharedMatBrush> GetBorderBrush(const pixui::size& size_Rect, const unsigned int n_Widths[],
        const pixui::color& color, const pixui::BorderRadiuses& borderRadius);

    //get border brush
    static TSharedPtr<PixSharedMatBrush> GetBorderBrush(const pixui::size& size_Rect, const unsigned int n_Widths[],
        const pixui::color colors[], const pixui::BorderRadiuses& borderRadius);

	static void AddMatBrush(TSharedPtr<PixMatBrush>& sptr_mat_brush);
	static TWeakPtr<PixMatBrush> FindMatBrush(const FString& fstr_key);
	static void RemoveMatBrush(const FString& fstr_key);

private:
    //mat brush map
    TArray<TSharedPtr<PixMatBrush>> ary_mat_brush_;
	TArray<TSharedPtr<PixMatBrush>> ary_free_mat_brush_pools_[e_px_mat_brush_count];
};