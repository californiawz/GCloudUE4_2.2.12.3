/**************************************************

**** @file:     PixDrawItem.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/09/27

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/



#pragma once
#include "PixUIDef.h"

#include "Slate.h"
#include "SlateCore.h"

#include "PixUtil.h"


#include "px_plugindef.h"

struct PX_FOnPaintHandlerParams
{
	//SPixPaintWidget::OnPaint params
	const FPaintArgs& Args;
	const FGeometry& Geometry;
	const FSlateRect& ClippingRect;
	FSlateWindowElementList& OutDrawElements;
	const int32 Layer;
	const bool bEnabled;

	PX_FOnPaintHandlerParams(const FPaintArgs& InArgs, const FGeometry& InGeometry,
		const FSlateRect& InClippingRect, FSlateWindowElementList& InOutDrawElements,
		int32 InLayer, bool bInEnabled)
		: Args(InArgs)
		, Geometry(InGeometry)
		, ClippingRect(InClippingRect)
		, OutDrawElements(InOutDrawElements)
		, Layer(InLayer)
		, bEnabled(bInEnabled)
	{

	}
};

class PixDrawItem
{
public:
	static PixDrawItem* NewDrawItem(EPxDrawItem e_type);


	static PixDrawItem* NewDrawItemFromPools(EPxDrawItem e_type);
	static void FreeDrawItemToPools(PixDrawItem* pDrawItem);

	static void FreeAllDrawItem();

public:
	PixDrawItem(EPxDrawItem e_type);
	virtual ~PixDrawItem();

public:
	EPxDrawItem Type() {
		return e_type_;
	}

	EPxBatchType BatchType() {
		return e_batch_type_;
	}

	void SetBatchType(EPxBatchType e_batch_type) {
		e_batch_type_ = e_batch_type;
	}

	PixDrawItem* Next() {
		return p_next_;
	}

	void SetNext(PixDrawItem* p_next) {
		p_next_ = p_next;
	}

public:
	virtual void* BatchStatus() {
		return this;
	}
	virtual uint32 DrawItem(PX_FOnPaintHandlerParams& draw_params, int32 n_cur_layer) = 0;
	virtual void UpdateParams(const TArray<void*>& aryParams) = 0;

private:
	static TArray<PixDrawItem*> gArrayItemPools[e_px_draw_item_count];

private:
	EPxDrawItem e_type_;
	EPxBatchType e_batch_type_;
	PixDrawItem* p_next_;
};

