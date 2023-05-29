// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PixUIAssetEditor/AssetTools/PixUIAsset.h"
#include "Widgets/SCompoundWidget.h"
#include "Templates/SharedPointer.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

/**
 * 
 */
class SPixUIWidgetEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPixUIWidgetEditor)
		{
		}

	SLATE_END_ARGS()

public:
	/** Virtual destructor. */
	virtual ~SPixUIWidgetEditor();

	/**
	 * Construct this widget
	 *
	 * @param InArgs The declaration data for this widget.
	 * @param InTextAsset The UTextAsset asset to edit.
	 */
	void Construct(const FArguments& InArgs, UPixUIAsset* InTextAsset);

private:
	/** Callback for committed text in the editable text box. */
	FReply HandleFlushPixUIView();

	/** Callback for property changes in the text asset. */
	void HandlePixUIAssetPropertySaved(UObject* Object);

private:
	/** Holds the editable text box widget. */
	TSharedPtr<SMultiLineEditableTextBox> EditableTextBox;
	UUserWidget* UserWidget;
	/** Pointer to the text asset that is being edited. */
	UPixUIAsset* PixUIAsset;
};
