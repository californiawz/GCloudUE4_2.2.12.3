/**************************************************

**** @file:     PixUIEditorMenuCommond.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/14

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

//only for editor
#if WITH_EDITOR

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

#include "Slate.h"


/**  */
class FWindowPixUIStyle
{
public:
	static void Initialize();

	static void Shutdown();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:
	static TSharedRef<class FSlateStyleSet> Create();

private:
	static TSharedPtr<class FSlateStyleSet> StyleInstance;
};

class FPixUIMenuCommands : public TCommands<FPixUIMenuCommands>
{
public:
	FPixUIMenuCommands()
		: TCommands<FPixUIMenuCommands>(TEXT("PixUIMenu"), NSLOCTEXT("Contexts", "PixUIMenu", "PixUIMenu Plugin"), NAME_None, FWindowPixUIStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	static void Initialize();

	static void Shutdown();

	static void AddPixUIMenu();

	static void AddMenuExtension(FMenuBarBuilder& Builder);
	static void AddPullDownMenu(FMenuBuilder& Builder);

	static void AddToolbarExtension(FToolBarBuilder& Builder);

	static void OnPixUIMenuSrcPathSetting();
	static void OnPixUIMenuProfiler();
	static void OnPixUIMenuFlushAsset();
	static void OnPixUIMenuAbout();
	static void OnPixUIBarTransHtml();

	static bool ShellPixUIHtmlTransConsole(bool bWatch = true);
	static FString GetConfigFile();
	TSharedPtr<FUICommandInfo> SrcSetAction;
	TSharedPtr<FUICommandInfo> ProfilerAction;
	TSharedPtr<FUICommandInfo> FlushHtmlAsset;

	TSharedPtr<FUICommandInfo> AboutAction;
	TSharedPtr<FUICommandInfo> TransHtmlAction;
	TSharedPtr<FUICommandInfo> PixUIContentTab;
};

#endif	//WITH_EDITOR
