/**************************************************

**** @file:     SPixPaintWidgetOld.h

**** @brief:    PixUI SPixPaintWidgetOld for call FSlateDrawElement to draw widget

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#ifdef DF_PX_USE_OLD_WIDGET

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Slate.h"
#include "SlateCore.h"
#include "Engine/Texture2D.h"

#include "PixInputSystem/IPixInputSystem.h"
#include "PixUILibMgr.h"
#include "PixUIDrawItem/PixDrawItem.h"


class UPixUIWidgetOld;

/**
 * 
 */
class SPixPaintWidgetOld : public SCompoundWidget, public pixui::IHostDraw
{
public:
    SLATE_BEGIN_ARGS(SPixPaintWidgetOld)
    {}
    SLATE_END_ARGS()

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);

public:
    ~SPixPaintWidgetOld();

public:
    void CreatePxView(UPixUIWidgetOld* p_Parent);
    void DestroyPxView();

    const pixui::PxViewHandle& pxViewHandle() const {
        return h_PxView_;
    }
    
    int PxWindowID() const {
        return i_PxWindowID;
    }

    void OnSizeChange(const FVector2D& v2d_NewSize);

    void OnScreenChange(const FVector2D& v2d_NewSize);

protected:
    void BatchElement(PixDrawItem* p_batch_item);

public:
    /************************************************************************/
    //Begin SWidget implementation
    virtual void   Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
    virtual int32  OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

    virtual bool SupportsKeyboardFocus() const override;

    virtual FReply OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) override;

    virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
    virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

    virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
    virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
    virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

    virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
    virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;

    virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent) override;
    virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
    virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
    virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;


	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;

	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

	virtual bool IsInteractable() const override;


private:
    virtual FVector2D ComputeDesiredSize(float) const override;
    //End SWidget implementation
    /************************************************************************/

public:
    FVector2D CaculateGeometryTextSize(const FString& fst_Text, const FSlateFontInfo& SlateFont);
    float CaculateGeometryScaleOfText(const FString& fst_Text, float f_GeomeryScale, 
        const FSlateFontInfo& SlateFont);

public:
    /************************************************************************/
    //Begin PX_Plugin::IPluginDraw implementation
	bool QueryPixelFormatSupport(pixui::EPixelFormat emPixelFormat);
	
    pixui::PxViewHandle GetContextPtr();

    /*
    called before paint

    @hDevice:   draw device

    @return:
    */
    virtual void OnPrePaint(pixui::PxViewHandle hDevice);

    /*
    called when paint end

    @hDevice:   draw device
    @nPaintCode: reserve

    @return:
    */
    virtual void OnEndPaint(pixui::PxViewHandle hDevice, const int nPaintCode);


    /*
    push a clip polygon

    @hDevice:   draw device
    @polygon:   clip polygon

    @return:
    */
    virtual void PushClip(pixui::PxViewHandle hDevice, const pixui::ClipRegion& polygon);


    /*
    push a clip rectangle

    @hDevice:   draw device
    @mat:       clip rectangle matrix
    @rectClip:  clip rectangle

    @return:
    */
    virtual void PushClip(pixui::PxViewHandle hDevice, const pixui::matrix& mat, const pixui::position& rectClip);


    /*
    pop clip

    @hDevice:   draw device

    @return:
    */
    virtual void PopClip(pixui::PxViewHandle hDevice);


    /*
    measure text width

    @hDevice:   draw device
    @pszTest:   text content
    @hFont:     font handle

    @return:    text width
    */
    virtual float TextWidth(pixui::PxViewHandle hDevice, const char* pszText, pixui::PxViewHandle hFont);


    /*
    Convert font size(point) to pixels

    @nPt:   size(point)

    return: pixels size
    */
    virtual int PtToPix(const int nPt);


    /*
    set cursor

    @pszCursor: cursor resource name
    */
    virtual void SetCursor(const char * pszCursor);


    /*
    draw text on device

    @hDevice:       draw device
    @hFont:         font content
    @mat:           transform matrix
    @pszTextDraw:   text
    @color:         color for draw text
    @ptPos:         draw pixui::position
    @fBlur:         reserved
    */
    virtual void DrawText(
        pixui::PxViewHandle     hDevice,
        pixui::PxViewHandle     hFont,
        const pixui::matrix&    mat,
        const char*             pszTextDraw,
        const pixui::color&     color,
        const pixui::position&  ptPos,
        const float             fBlur);

    /*
    draw element border

    @hDevice:       draw device
    @mat:           transform matrix
    @rcDraw:        border rectangle size
    @nWidths:       line Width for top left bottom right
    @eLineTypes:    Line Types for top left bottom right
    @colors:        color for top left bottom right
    @radius:        radius
    */
    virtual void DrawBorder(
        pixui::PxViewHandle             hDevice,
        const pixui::matrix&            mat,
        const pixui::position&          rcDraw,
        const unsigned int              nWidths[],
        const pixui::BorderStyle       eLineTypes[],
        const pixui::color              colors[],
        const pixui::BorderRadiuses&   radius);

    /*
    draw element border with same width

    @hDevice:       draw device
    @mat:           transform matrix
    @rcDraw:        border rectangle size
    @unWidth:       line Width for top left bottom right
    @emLineType:    Line Types for top left bottom right
    @color:         color for top left bottom right
    @radius:        radius
    */
    virtual void DrawRect(
        pixui::PxViewHandle                          hDevice,
        const pixui::matrix&            mat,
        const pixui::position&          rcDraw,
        const unsigned int              unWidth,
        const pixui::BorderStyle       emLineType,
        const pixui::color&             color,
        const pixui::BorderRadiuses&   radius);


    /*
    fill rectangle area

    @hDevice:       draw device
    @mat:           transform matrix
    @rcDraw:        rectangle size
    @color:         color for rectangle
    @radius:        radius
    */
    virtual void FillRect(
        pixui::PxViewHandle                          hDevice,
        const pixui::matrix&            mat,
        const pixui::position&          ptDraw,
        const pixui::color&             color,
        const pixui::BorderRadiuses&   radius);


    /*
    draw image on device

    @hDevice:       draw device
    @pImage:        image information
    @mat:           transform matrix
    @rcDraw:        image size
    @rcImageSrc:    image uv
    @emRepeat:      repeat model
    @emAttachment   reserved
    @sliceImage     slice for draw image
    @color:         tiling color
    @radius:        radius

    */
    virtual void DrawImage(
        pixui::PxViewHandle                              hDevice,
        pixui::PxViewHandle*            pImage,
        const pixui::matrix&                mat,
        const pixui::position&              rcDraw,
        const pixui::position&              rcImageSrc,
        const pixui::BackgroundRepeat      emRepeat,
        const pixui::BackgroundAttachment  emAttachment,
        const pixui::ImageSlice&           sliceImage,
        const pixui::color&                 color,
        const pixui::BorderRadiuses&       radius);

    /*
    draw line

    @hDevice:       draw device
    @mat:           transform matrix
    @unWidth:       line Width
    @emLineType:    Line Types
    @color:         color for top left bottom right
    @ptStart:       start point
    @ptEnd:         end point
    */
    virtual void DrawLine(
        pixui::PxViewHandle                      hDevice,
        const pixui::matrix&        mat,
        const unsigned int          unWidth,
        const pixui::BorderStyle   emLineType,
        const pixui::color          color,
        const pixui::point&         ptStart,
        const pixui::point&         ptEnd) override;

	virtual void DrawSlot(
        pixui::PxViewHandle hDevice,
        pixui::PxViewHandle pSlot,
				const pixui::matrix &mat,
				const pixui::position &rect) override;

    //End PX_Plugin::IPluginDraw implementation
    /************************************************************************/

public:
	/*
    bool OnActivateInput(pixui::EKeyboardType emKeyboardType, const char* pszDefaultText, const char* pszHintText);
    bool OnDeativateInput();

    //Begin IInputSystem implementation
    virtual FText GetInputText() override;
    virtual FText GetInputHintText() override;
    virtual EKeyboardType GetVirtualKeyboardType() override;

#if ENGINE_MINOR_VERSION > 20    //ue4 minor version < 20 do not support GetVirtualKeyboardOptions
    virtual FVirtualKeyboardOptions GetVirtualKeyboardOptions() override;
#endif //ENGINE_MINOR_VERSION > 20

    virtual bool IsMultilineEntry() override;
    virtual TSharedPtr<SWidget> GetWidget() override;
	*/

public:
    void OnInputText(const FString& fstrInsert, const bool b_end_input, const bool b_lost_focus, const bool b_replace);

	bool BeActiveInput() {
		return b_ActiveInput_;
	}

	void SetActiveInput(bool b_active) {
		b_ActiveInput_ = b_active;
	}

	void RetainDraw(PX_FOnPaintHandlerParams& paint_param);


	void ShowDrawItemInfor();

	const int32 GetCustomLayer() const {
		return n_custom_layer_;
	}
	void SetCustomLayer(int32 n_custom_layer) {
		n_custom_layer_ = n_custom_layer;
	}

protected:
	void PreAllPaint();
	void EndAllPaint();

	void DealwithNewItem(PixDrawItem* p_new_item);

	PixDrawItem* DrawItemFromPools(EPxDrawItem e_type);
	void FreeDrawItemPools();

private:
    //draw layer type
	EPxBatchType e_LastBatchType_;

	//batch status
	void* p_last_batch_status_;

    //draw layer count
    uint64 ul_CurDrawBaseLayer_;

    //clip array
    TArray<uint32> array_clip_;
	uint32 un_virtual_clip_count_;

    //desired size
    FVector2D v2d_DesiredSize_;

    //screen size
    FVector2D v2d_ScreenSize_;

    //pixui view handle
    pixui::PxViewHandle  h_PxView_;

    //pixui windowID
    int i_PxWindowID;

    //Has Geometry been initialized,Because if the first time opened on Construct event from blueprint the Geometry was not initialized
    bool b_GeometryInit_;

	//move position
	FVector2D v2d_last_move_pos_;


	FVector2D v2d_last_move_screen_pos_;

	bool b_ActiveInput_;

	bool b_loack_mouse_;


	PixDrawItem* p_root_draw_item;
	PixDrawItem* p_cur_draw_item;

	TArray<PixDrawItem*> ary_draw_item_pools[e_px_draw_item_count];
	uint32 un_draw_item_pools_index[e_px_draw_item_count];

	int32 n_custom_layer_;
};


#endif // DF_PX_USE_OLD_WIDGET