/**************************************************

**** @file:     PxSubCtrlWidget.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/11/02

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"

#include "PxSubLayerWidget.h"

#include "PxSubCtrlWidget.generated.h"

/**
 *
 */

class SPxCtrlWidget;
class UPixUIWidget;

UCLASS()
class UPxSubCtrlWidget : public UPxSubLayerWidget
{
	GENERATED_BODY()

public:
	UPxSubCtrlWidget(const FObjectInitializer& ObjectInitializer);


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
	void SetActiveInput(bool bActiveInput);

private:
	//SPxPaintWidget for draw page
	TSharedPtr<SPxCtrlWidget> mSptrPxCtrlWidget;
};