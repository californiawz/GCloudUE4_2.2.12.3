/**************************************************

**** @file:     SPixUIWidget.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/04/11

**** @group:    PixUI

**** @copyright: Copyright 2022 PixUI. All Rights Reserved.

***************************************************/




#include "SPixUIWidget.h"

#include "PixUIWidget.h"


/*
FText src_ = FText::FromString(TEXT("G://my_html//demo.html"));

return SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[
		// Put your tab content here!
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SPixUIWidget)
			.Src(src_)
		]
	];

*/

void SPixUIWidget::Construct(const FArguments& InArgs)
{
	sptr_widget_ = NewObject<UPixUIWidget>();
	sptr_widget_->AddToRoot();

	BoundText = InArgs._Src;

    ChildSlot
    [
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			sptr_widget_.Get()->TakeWidget()
		]
        // Populate the widget
    ];
	//open url
	sptr_widget_->OpenPageFromUrl(BoundText.Get().ToString());
}


SPixUIWidget::~SPixUIWidget()
{
	if (sptr_widget_.IsValid())
	{
		sptr_widget_->RemoveFromRoot();
	}
}


void SPixUIWidget::LoadPage(const TAttribute< FString >& InText)
{
	if (InText.IsSet() && !InText.IsBound())
	{
		LoadPage(InText.Get());
		return;
	}

	struct Local
	{
		static FText PassThroughAttribute(TAttribute< FString > InString)
		{
			return FText::FromString(InString.Get(TEXT("")));
		}
	};

	BoundText = TAttribute< FText >::Create(TAttribute<FText>::FGetter::CreateStatic(&Local::PassThroughAttribute, InText));

	Invalidate(EInvalidateWidget::LayoutAndVolatility);
}


void SPixUIWidget::LoadPage(const FString& InText)
{
	LoadPage(FText::FromString(InText));
}


void SPixUIWidget::LoadPage(const TAttribute< FText >& InText)
{
	if (InText.IsSet() && !InText.IsBound())
	{
		LoadPage(InText.Get());
		return;
	}

	BoundText = InText;
	Invalidate(EInvalidateWidget::LayoutAndVolatility);
}


void SPixUIWidget::LoadPage(const FText& InText)
{
	BoundText = InText;
	Invalidate(EInvalidateWidget::LayoutAndVolatility);
}
