/**************************************************

**** @file:     SPxPaintWidget.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/11/01

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "CoreMinimal.h"
#include "hf_iwindow.h"
#include "Widgets/SCompoundWidget.h"
#include "Slate.h"
#include "SlateCore.h"

#include "PixUIDrawItem/PixDrawItem.h"

class UPixUIWidget;

class SPxPaintWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPxPaintWidget)
	{
	}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

public:
	~SPxPaintWidget();

public:
	/************************************************************************/
	//Begin SWidget implementation
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	//End SWidget implementation
	/************************************************************************/

public:
	void SetParentWidget(TWeakObjectPtr<UPixUIWidget> wptrParent)
	{
		mWptrParent = wptrParent;
	}

	pixui::PxViewHandle PxViewId() const;

	void PushDrawItem(PixDrawItem* ptrNewDrawItem);
	PixDrawItem* PopAllDrawItem();

	void SetRootLayer(bool beBaseLayer) {
		mBeBaseLayer = beBaseLayer;
	}

private:
	PixDrawItem* mPtrRootDrawItem;
	PixDrawItem* mPtrLastDrawItem;
	bool mBeBaseLayer;

	TWeakObjectPtr<UPixUIWidget> mWptrParent;
};

