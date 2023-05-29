/**************************************************

**** @file:     SPxPaintWidget.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/11/01

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/

#include "SPxPaintWidget.h"

#include "PixUIDef.h"
#include "PixUILibMgr.h"
#include "PixUtil.h"
#include "PixUILog.h"
#include "PixUIBPLibrary.h"
#include "PixUIWidget.h"

#if DF_PIXUI_PROFILER
#include "PixUIProfiler/PxpTickCount.h"
#endif //DF_PIXUI_PROFILER


void SPxPaintWidget::Construct(const FArguments& InArgs)
{
	mPtrRootDrawItem = nullptr;
	mPtrLastDrawItem = nullptr;

	mBeBaseLayer = false;
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
	//TAttribute<EVisibility> EpxViewVisibility = TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateRaw(this, &SPixPaintWidget::CheckPxWidgetVisible));
	//SetVisibility(EpxViewVisibility);

	PxLog_Trace("SPxPaintWidget::Construct");
}


SPxPaintWidget::~SPxPaintWidget()
{
	PxLog_Trace("SPxPaintWidget::~SPxPaintWidget");
}


int32 SPxPaintWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 nLayerId = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	if (mBeBaseLayer)
	{
		//painting
		if (PxViewId() > 0)
		{
#if DF_PX_BUILD_NO_SHIPPING
			if (!UPixUIBPLibrary::PixUI_GetDebugRetainDraw())
#endif	//DF_PX_BUILD_NO_SHIPPING
			{
				static int32 s_n_cur_paint_cont = 0;
				if (s_n_cur_paint_cont >= UPixUIBPLibrary::PixUI_GetPaintDura())
				{
					if (px_plugin::pxViewTick(PxViewId()))
					{
						px_plugin::pxViewPaint(PxViewId(), 0);
					}
					s_n_cur_paint_cont = 0;
				}
				else
				{
					s_n_cur_paint_cont++;
				}
			}
		}
	}

	bool beInEditor = false;

	int32 nBaseLayer = 0;

#if WITH_EDITOR
	if (!PixUtil::IsGamePlay())
	{
		beInEditor = true;
		//in editor draw pixui widget 
		const bool bIsEnabled = ShouldBeEnabled(bParentEnabled);

		const ESlateDrawEffect DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
		const FLinearColor FinalColorAndOpacity(1.0, 1.0, 1.0, 0.5);
		static const FSlateColorBrush s_stBrushWhite = FSlateColorBrush(FColorList::White);

		FSlateDrawElement::MakeBox(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), &s_stBrushWhite, ESlateDrawEffect::None, FinalColorAndOpacity);
	}
#endif //WITH_EDITOR

	if (!beInEditor)
	{
		if (!UPixUIBPLibrary::PixUI_IsStartUp())
		{
			auto localFont = FCoreStyle::Get().GetFontStyle("NormalFont");
			localFont.Size = 32;
			FString tip = TEXT("Pix UI Do not Startup!!!!");
			FSlateDrawElement::MakeText(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				tip,
				localFont,
				ESlateDrawEffect::None,
				FColor::Red
			);
		}
		else
		{
			//draw
			PixDrawItem* ptrNext = mPtrRootDrawItem;

			uint32 unPaintCount = 0;

			PX_FOnPaintHandlerParams paint_Param(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, bParentEnabled);

			while (ptrNext)
			{

#if DF_PIXUI_PROFILER
				PxpWindowTimePaintItem draw_item(PxViewId(), ptrNext->Type());
#endif //DF_PIXUI_PROFILER

				if (mWptrParent.IsValid())
				{
					nBaseLayer = mWptrParent->BatchElement(ptrNext);
				}
				ptrNext->DrawItem(paint_Param, nBaseLayer);
				ptrNext = ptrNext->Next();

				unPaintCount++;

				if (unPaintCount > 100000)
				{
					PxLog_Warning("SPxPaintWidget::RetainDraw paint element count over 100000!!!!!!");
					break;
				}
			}
		}
	}
	return nLayerId + nBaseLayer;
}

pixui::PxViewHandle SPxPaintWidget::PxViewId() const
{
	if (mWptrParent.IsValid())
	{
		return mWptrParent->PxViewId();
	}
	return 0;
}


void SPxPaintWidget::PushDrawItem(PixDrawItem* ptrNewDrawItem)
{
	ptrNewDrawItem->SetNext(nullptr);
	if (!mPtrRootDrawItem)
	{
		mPtrRootDrawItem = ptrNewDrawItem;
		mPtrLastDrawItem = ptrNewDrawItem;
	}
	else
	{
		if (mPtrLastDrawItem)
		{
			mPtrLastDrawItem->SetNext(ptrNewDrawItem);
			mPtrLastDrawItem = ptrNewDrawItem;
		}
		else
		{
			PxLog_Error("SPxPaintWidget::PushDrawItem error mPtrLastDrawItem nullptr");
		}
	}
}


PixDrawItem* SPxPaintWidget::PopAllDrawItem()
{
	PixDrawItem* ptrTmpItem = mPtrRootDrawItem;
	mPtrRootDrawItem = nullptr;
	mPtrLastDrawItem = nullptr;
	return ptrTmpItem;
}