/**************************************************

**** @file:     PxSubLayerWidget.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/11/01

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#include "CoreMinimal.h"
#include "hf_typedef.h"
#include "Components/Widget.h"
#include "Engine/Font.h"

#include "PxSubLayerWidget.generated.h"

/**
 *
 */
class UPixUIWidget;
class SPxPaintWidget;
class PixDrawItem;

UCLASS()
class UPxSubLayerWidget : public UWidget
{
	GENERATED_BODY()

public:
	UPxSubLayerWidget(const FObjectInitializer& ObjectInitializer);


protected:
	/************************************************************************/
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface
	/************************************************************************/

public:
	/************************************************************************/
	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool beReleaseChildren) override;
	//~ End UVisual Interface
	/************************************************************************/

	/************************************************************************/
	//~ Begin UObject Interface
	virtual void BeginDestroy() override;
	//~ End UObject Interface
	/************************************************************************/

public:
	void SetWidgetParent(TWeakObjectPtr<UPixUIWidget> wptrParent);
	void SetRootLayer(bool beBaseLayer);
	void PushDrawItem(PixDrawItem* ptrNewDrawItem);
	PixDrawItem* PopAllDrawItem();
	float TextWidth(const char* pszText, pixui::uint_ptr hFont);

protected:
	FVector2D CaculateGeometryTextSize(const FString& fst_Text, const FSlateFontInfo& SlateFont);

protected:
	//SPxPaintWidget for draw page
	bool mBeRootLayer;
	TSharedPtr<SPxPaintWidget> mSptrPxPaintWidget;
	TWeakObjectPtr<UPixUIWidget> mWptrParent;
};
