// Copyright Epic Games, Inc. All Rights Reserved.

#include "PixUIContentBrowserExtensions.h"
#include "Modules/ModuleManager.h"
#include "Textures/SlateIcon.h"
#include "ContentBrowserModule.h"

#define LOCTEXT_NAMESPACE "FPixUIModule"

//////////////////////////////////////////////////////////////////////////

static FContentBrowserMenuExtender ContentBrowserExtenderDelegate;
static FDelegateHandle ContentBrowserExtenderDelegateHandle;
static bool IsShow = false;

class FPixUIContentBrowserExtensions_Impl
{
public:
	static void ToggleShowPluginContent()
	{
		IsShow = !IsShow;
		///=-=///
	}

	static bool IsShowingPluginContent()
	{
		return IsShow;
	}

	static void CreatePixUIContBrowserExtensionMenu(FMenuBuilder& MenuBuilder)
	{
		FUIAction(
				FExecuteAction::CreateStatic(&ToggleShowPluginContent),
				FCanExecuteAction(),
				FIsActionChecked::CreateStatic(&IsShowingPluginContent)
			),
			MenuBuilder.AddSubMenu(
				LOCTEXT("Show_PixUI_Assets", "Show PixUI Assets"),
				LOCTEXT("Show_PixUI_Assets_ToolTip", "Show PixUI content in the view?"),
				FNewMenuDelegate::CreateStatic(&FPixUIContentBrowserExtensions_Impl::PopulateSpriteActionsMenu),
				FUIAction(
					FExecuteAction::CreateStatic(&ToggleShowPluginContent),
					FCanExecuteAction(),
					FIsActionChecked::CreateStatic(&IsShowingPluginContent)
				),
				NAME_None,
				EUserInterfaceActionType::ToggleButton,
				false,
				FSlateIcon()
			);
	}

	static void PopulateSpriteActionsMenu(FMenuBuilder& MenuBuilder)
	{
		const FName PaperStyleSetName = "PixUI";

		MenuBuilder.AddMenuEntry(
			LOCTEXT("Show_Html", "Html"),
			LOCTEXT("Show_Html_Tooltip", "Show Html Asset"),
			FSlateIcon(PaperStyleSetName, "AssetActions.ShowHtml"),
			FUIAction(
				FExecuteAction::CreateStatic(&ToggleShowPluginContent),
				FCanExecuteAction(),
				FIsActionChecked::CreateStatic(&IsShowingPluginContent)
			),
			NAME_None,
			EUserInterfaceActionType::ToggleButton);

		MenuBuilder.AddMenuEntry(
			LOCTEXT("Show_JavaScript", "JavaScript"),
			LOCTEXT("Show_JavaScript_Tooltip", "Show JavaScript Asset"),
			FSlateIcon(PaperStyleSetName, "AssetActions.ShowJavaScript"),
			FUIAction(
				FExecuteAction::CreateStatic(&ToggleShowPluginContent),
				FCanExecuteAction(),
				FIsActionChecked::CreateStatic(&IsShowingPluginContent)
			),
			NAME_None,
			EUserInterfaceActionType::ToggleButton);
	}

	static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu()
	{
		TSharedRef<FExtender> Extender(new FExtender());

		// Add the sprite actions sub-menu extender
		Extender->AddMenuExtension(
			"Content",
			EExtensionHook::After,
			nullptr,
			FMenuExtensionDelegate::CreateStatic(&FPixUIContentBrowserExtensions_Impl::CreatePixUIContBrowserExtensionMenu));

		return Extender;
	}

	static TArray<FContentBrowserMenuExtender>& GetExtenderDelegates()
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
		return ContentBrowserModule.GetAllAssetViewViewMenuExtenders();
	}
};

//////////////////////////////////////////////////////////////////////////
// FPixUIContentBrowserExtensions

void FPixUIContentBrowserExtensions::InstallHooks()
{
	ContentBrowserExtenderDelegate = FContentBrowserMenuExtender::CreateStatic(&FPixUIContentBrowserExtensions_Impl::OnExtendContentBrowserAssetSelectionMenu);

	TArray<FContentBrowserMenuExtender>& CBMenuExtenderDelegates = FPixUIContentBrowserExtensions_Impl::GetExtenderDelegates();
	CBMenuExtenderDelegates.Add(ContentBrowserExtenderDelegate);
	ContentBrowserExtenderDelegateHandle = CBMenuExtenderDelegates.Last().GetHandle();
}

void FPixUIContentBrowserExtensions::RemoveHooks()
{
	TArray<FContentBrowserMenuExtender>& CBMenuExtenderDelegates = FPixUIContentBrowserExtensions_Impl::GetExtenderDelegates();
	CBMenuExtenderDelegates.RemoveAll([](const FContentBrowserMenuExtender& Delegate) { return Delegate.GetHandle() == ContentBrowserExtenderDelegateHandle; });
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
