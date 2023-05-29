/**************************************************

**** @file:     PxLayerWidget.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/11/01

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PxSubLayerWidget.h"

#include "Engine/FontFace.h"
#include "Engine/UserInterfaceSettings.h"

#include "PixUIDef.h"
#include "PixUIBPLibrary.h"
#include "PixUILog.h"
#include "PixUtil.h"

#include "PixUIWidget.h"
#include "SPxPaintWidget.h"
#include "PixImp/PixImpFont.h"

//construct
UPxSubLayerWidget::UPxSubLayerWidget(const FObjectInitializer& ObjectInitializer)
	:mSptrPxPaintWidget(nullptr)
{
	mBeRootLayer = false;
	//Visibility = ESlateVisibility::Visible;
}


TSharedRef<SWidget> UPxSubLayerWidget::RebuildWidget()
{
	mSptrPxPaintWidget = SNew(SPxPaintWidget);
	mSptrPxPaintWidget->SetParentWidget(mWptrParent);
	mSptrPxPaintWidget->SetRootLayer(mBeRootLayer);
	return mSptrPxPaintWidget.ToSharedRef();
}


void UPxSubLayerWidget::ReleaseSlateResources(bool beReleaseChildren)
{
	//clear
	Super::ReleaseSlateResources(beReleaseChildren);
	mSptrPxPaintWidget.Reset();
}


void UPxSubLayerWidget::BeginDestroy()
{
	Super::BeginDestroy();
}

void UPxSubLayerWidget::SetWidgetParent(TWeakObjectPtr<UPixUIWidget> wptrParent)
{
	mWptrParent = wptrParent;
	if (mSptrPxPaintWidget.IsValid())
	{
		mSptrPxPaintWidget->SetParentWidget(wptrParent);
	}
}

void UPxSubLayerWidget::SetRootLayer(bool beRootLayer)
{
	mBeRootLayer = beRootLayer;
	if (mSptrPxPaintWidget.IsValid())
	{
		mSptrPxPaintWidget->SetRootLayer(mBeRootLayer);
	}
}


void UPxSubLayerWidget::PushDrawItem(PixDrawItem* ptrNewDrawItem)
{
	if (mSptrPxPaintWidget.IsValid())
	{
		mSptrPxPaintWidget->PushDrawItem(ptrNewDrawItem);
	}
}

PixDrawItem* UPxSubLayerWidget::PopAllDrawItem()
{
	if (mSptrPxPaintWidget.IsValid())
	{
		return mSptrPxPaintWidget->PopAllDrawItem();
	}
	return nullptr;
}


FVector2D UPxSubLayerWidget::CaculateGeometryTextSize(const FString& fst_Text, const FSlateFontInfo& SlateFont)
{
	float f_GameUIScale = 1.0f;
	auto Geometry = GetCachedGeometry();
	if (false)
	{
		f_GameUIScale = Geometry.Scale;
	}
	else
	{
		//maybe widget opened on begin event and the Geometry was not Cached Geometry
		if (GEngine && GEngine->GameViewport)
		{
			FIntPoint ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
			f_GameUIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(ViewportSize);
		}
		else
		{
			f_GameUIScale = Geometry.Scale;
		}
	}
	const TSharedRef< FSlateFontMeasure > FontMeasureService = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	FVector2D v2d_TextSize = FontMeasureService->Measure(fst_Text, SlateFont, f_GameUIScale);
	if (UPixUIBPLibrary::PixUI_IsDynamicFixFontSize())
	{
		//fix font size on paint
		return v2d_TextSize;
	}


	//fix font size on create
	//return v2d_TextSize / CaculateGeometryScaleOfText(fst_Text, f_GameUIScale, SlateFont);
	return v2d_TextSize / f_GameUIScale;
}


float UPxSubLayerWidget::TextWidth(const char* pszText, pixui::uint_ptr hFont)
{
	float f_Width = 0.0f;
	TWeakPtr<PixFont> wptr_pix_font = PixImpFont::GetSlateFont(hFont);
	FString fstr_Tmp = UTF8_TO_TCHAR(pszText);

	//replace \n
	fstr_Tmp = fstr_Tmp.Replace(TEXT("\n"), TEXT("  "));

	if (wptr_pix_font.IsValid() && wptr_pix_font.Pin()->sptr_SlatFont_.Get())
	{
		if (!fstr_Tmp.IsEmpty())
		{
			FVector2D vctFontSize = CaculateGeometryTextSize(fstr_Tmp, *(wptr_pix_font.Pin()->sptr_SlatFont_.Get()));
			f_Width = vctFontSize.X;
		}
	}
	else
	{
		PxLog_Error("SPixPaintWidget::TextWidth Error,can not found font:%p ", hFont);
	}
	return f_Width;
}