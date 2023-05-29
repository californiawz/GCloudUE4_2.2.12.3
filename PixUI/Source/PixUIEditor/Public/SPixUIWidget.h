/**************************************************

**** @file:     SPixUIWidget.h

**** @brief:

**** @author:   tianzelei

**** @date:     2022/04/11

**** @group:    PixUI

**** @copyright: Copyright 2022 PixUI. All Rights Reserved.

***************************************************/


#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UPixUIWidget;

/**
 * 
 */
class PIXUIEDITOR_API SPixUIWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS( SPixUIWidget )
		: _Src()
		{

		}
		/** src of pixui page */
		SLATE_ATTRIBUTE(FText, Src)
    SLATE_END_ARGS()

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);

	const FText& GetText() const
	{
		return BoundText.Get();
	}

	void LoadPage(const TAttribute< FString >& InText);
	void LoadPage(const FString& InText);
	void LoadPage(const TAttribute< FText >& InText);
	void LoadPage(const FText& InText);
public:
    ~SPixUIWidget();

private:
	/** The text displayed in this pixui url */
	TAttribute< FText > BoundText;

	TWeakObjectPtr< UPixUIWidget > sptr_widget_;
};
