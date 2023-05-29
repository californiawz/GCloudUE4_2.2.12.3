/**************************************************

**** @file:     PxSubCtrlWidget.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/11/02

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PxSubCtrlWidget.h"

#include "PixUIWidget.h"
#include "SPxCtrlWidget.h"

//construct
UPxSubCtrlWidget::UPxSubCtrlWidget(const FObjectInitializer& ObjectInitializer)
	:UPxSubLayerWidget(ObjectInitializer), mSptrPxCtrlWidget(nullptr)
{
	//Visibility = ESlateVisibility::Visible;
}


TSharedRef<SWidget> UPxSubCtrlWidget::RebuildWidget()
{
	mSptrPxCtrlWidget = SNew(SPxCtrlWidget);
	mSptrPxCtrlWidget->SetParentWidget(mWptrParent);
	return mSptrPxCtrlWidget.ToSharedRef();
}


void UPxSubCtrlWidget::ReleaseSlateResources(bool beReleaseChildren)
{
	//clear
	Super::ReleaseSlateResources(beReleaseChildren);
	mSptrPxCtrlWidget.Reset();
}


void UPxSubCtrlWidget::BeginDestroy()
{
	Super::BeginDestroy();
}


void UPxSubCtrlWidget::SetWidgetParent(TWeakObjectPtr<UPixUIWidget> wptrParent)
{
	mWptrParent = wptrParent;
	if (mSptrPxCtrlWidget.IsValid())
	{
		mSptrPxCtrlWidget->SetParentWidget(wptrParent);
	}
}


void UPxSubCtrlWidget::SetActiveInput(bool bActiveInput)
{
	if (mSptrPxCtrlWidget.IsValid())
	{
		mSptrPxCtrlWidget->SetActiveInput(bActiveInput);
	}
}