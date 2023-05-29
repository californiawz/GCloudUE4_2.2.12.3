/**************************************************

**** @file:     PixUIEditorMenuCommond.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/14

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/
#if WITH_EDITOR
#include "PixUIEditorMenuCommond.h"
#include "Interfaces/IPluginManager.h"
#include "AssetToolsModule.h"
#include "DesktopPlatformModule.h"
#include "LevelEditor.h"
#include "PixUIBPLibrary.h"
#include "PixUIEditorSettings/PixUIEditorSettings.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FPixUIEditorModule"
static const FName EditorWindowPixHtmlSrcTabName("PixUI Html Source Path Setting");

TSharedPtr<FSlateStyleSet> FWindowPixUIStyle::StyleInstance = NULL;

void FWindowPixUIStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FWindowPixUIStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FWindowPixUIStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ExtendedPixUIWindowStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon128x128(128.0f, 128.0f);

TSharedRef<FSlateStyleSet> FWindowPixUIStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("ExtendedPixUIWindowStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("PixUI")->GetBaseDir() / TEXT("Resources"));

	Style->Set("PixUIMenu.TransHtmlAction", new IMAGE_BRUSH(TEXT("Icon128"), Icon40x40));

	return Style;
}


#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

const ISlateStyle& FWindowPixUIStyle::Get()
{
	return *StyleInstance;
}


void FPixUIMenuCommands::RegisterCommands()
{
	UI_COMMAND(SrcSetAction, "HtmlSrc", "Setting Html Src Path", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ProfilerAction, "Profiler", "Profiler about pixui", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(FlushHtmlAsset, "FlushHtml", "Profiler about pixui", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AboutAction, "Version", "PixUI Version", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(TransHtmlAction, "PxTransHtml", "PixUI Translation Html File to Bitcode", EUserInterfaceActionType::Button, FInputChord());
}

void FPixUIMenuCommands::Initialize()
{
	FWindowPixUIStyle::Initialize();
	Register();

	//Add menu
	AddPixUIMenu();
}

void FPixUIMenuCommands::Shutdown()
{
	FWindowPixUIStyle::Shutdown();
	Unregister();

	//Clear window
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EditorWindowPixHtmlSrcTabName);
}

void FPixUIMenuCommands::AddPixUIMenu()
{
	//initialization FUICommandList
	TSharedPtr<class FUICommandList> PluginCommands;
	PluginCommands = MakeShareable(new FUICommandList);

	//Binding action
	PluginCommands->MapAction(
		FPixUIMenuCommands::Get().SrcSetAction,
		FExecuteAction::CreateStatic(&FPixUIMenuCommands::OnPixUIMenuSrcPathSetting),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FPixUIMenuCommands::Get().ProfilerAction,
		FExecuteAction::CreateStatic(&FPixUIMenuCommands::OnPixUIMenuProfiler),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FPixUIMenuCommands::Get().FlushHtmlAsset,
		FExecuteAction::CreateStatic(&FPixUIMenuCommands::OnPixUIMenuFlushAsset),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FPixUIMenuCommands::Get().AboutAction,
		FExecuteAction::CreateStatic(&FPixUIMenuCommands::OnPixUIMenuAbout),
		FCanExecuteAction());


	PluginCommands->MapAction(
		FPixUIMenuCommands::Get().TransHtmlAction,
		FExecuteAction::CreateStatic(&FPixUIMenuCommands::OnPixUIBarTransHtml),
		FCanExecuteAction());


	//LevelEditorModule Add extended menu
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	//Create PixUI menu
	{
		TSharedPtr<FExtender> MenuBarExtend = MakeShareable(new FExtender());
		MenuBarExtend->AddMenuBarExtension("Help", EExtensionHook::After, PluginCommands,
		                                   FMenuBarExtensionDelegate::CreateStatic(&FPixUIMenuCommands::AddMenuExtension));
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtend);
	}
	//Bind the bar button
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Compile", EExtensionHook::After, PluginCommands,
		                                     FToolBarExtensionDelegate::CreateStatic(&FPixUIMenuCommands::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FPixUIMenuCommands::AddMenuExtension(FMenuBarBuilder& Builder)
{
	Builder.AddPullDownMenu(FText::FromString("PixUI"), FText::FromString("PixUI"),
	                        FNewMenuDelegate::CreateStatic(&FPixUIMenuCommands::AddPullDownMenu));
}

void FPixUIMenuCommands::AddPullDownMenu(FMenuBuilder& Builder)
{
	Builder.BeginSection(FName("PixUIEditor"));
	Builder.AddMenuEntry(FPixUIMenuCommands::Get().SrcSetAction);
	Builder.AddMenuEntry(FPixUIMenuCommands::Get().ProfilerAction);
	Builder.AddMenuEntry(FPixUIMenuCommands::Get().FlushHtmlAsset);
	Builder.AddMenuSeparator();
	Builder.AddMenuEntry(FPixUIMenuCommands::Get().AboutAction);
	Builder.EndSection();
}

void FPixUIMenuCommands::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FPixUIMenuCommands::Get().TransHtmlAction);
}

void FPixUIMenuCommands::OnPixUIMenuSrcPathSetting()
{
	//pop-up window
	//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Working here!! Stay Tuned!!"));
	ShellPixUIHtmlTransConsole(true);
}

void FPixUIMenuCommands::OnPixUIMenuProfiler()
{
	//pop-up window
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Working here!! Stay Tuned!!"));
}

void FPixUIMenuCommands::OnPixUIMenuFlushAsset()
{
	FString WriteCachePathRef = FPaths::ProjectContentDir();
#if PLATFORM_ANDROID
	WriteCachePathRef = IAndroidPlatformFile::GetPlatformPhysical().FileRootPath(*WriteCachePathRef);
#elif PLATFORM_IOS
	WriteCachePathRef = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*WriteCachePathRef);
#else
	WriteCachePathRef = FPaths::ConvertRelativePathToFull(WriteCachePathRef);
#endif
	FString PixUIAssetCachePath = WriteCachePathRef / "PixUIAsset";
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!FPaths::DirectoryExists(PixUIAssetCachePath))
	{
		if (!PlatformFile.CreateDirectory(*PixUIAssetCachePath))
		{
		}
	}
	else
	{
		PlatformFile.DeleteDirectory(*PixUIAssetCachePath);
		if (!PlatformFile.CreateDirectory(*PixUIAssetCachePath))
		{
			// IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
			// AssetTools.CreateAsset(Fuke);
		}
	}
	for (auto DirPath : GetDefault<UPixUIEditorSettings>()->arrHtmlFilePath)
	{
		if (!DirPath.Path.IsEmpty())
		{
			TArray<FString> AssetName;
			PlatformFile.FindFilesRecursively(AssetName, *DirPath.Path, TEXT(".html"));
			IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
			AssetTools.ImportAssets(AssetName,TEXT("/Game/PixUIAsset"));
		}
	}
}

void FPixUIMenuCommands::OnPixUIMenuAbout()
{
	//pop-up about window
	FText PixTitle = FText::FromString("PixUI");
	FString PixVersion = TEXT("PixUI Version    ") + UPixUIBPLibrary::PixUI_Version();
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(PixVersion), &PixTitle);
}

void FPixUIMenuCommands::OnPixUIBarTransHtml()
{
	auto fstr_SrcPath_s = GetDefault<UPixUIEditorSettings>()->PixUIHtmlSrcDir.Path;
	auto fstr_DstPath_s = GetDefault<UPixUIEditorSettings>()->PixUIHtmlDstDir.Path;
	if (!FPaths::DirectoryExists(fstr_SrcPath_s))
	{
		FString fstrTip = TEXT("Source Directory ") + fstr_SrcPath_s + TEXT(" dose not Exists");
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(fstrTip));
		return;
	}

	if (!FPaths::DirectoryExists(fstr_DstPath_s))
	{
		FString fstrTip = TEXT("Destination Directory ") + fstr_DstPath_s + TEXT(" dose not Exists");
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(fstrTip));
		return;
	}

	ShellPixUIHtmlTransConsole(true);
}

bool FPixUIMenuCommands::ShellPixUIHtmlTransConsole(bool bWatch)
{
	bool b_ret = false;
	auto fstr_SrcPath_s = GetDefault<UPixUIEditorSettings>()->PixUIHtmlSrcDir.Path;
	auto fstr_DstPath_s = GetDefault<UPixUIEditorSettings>()->PixUIHtmlDstDir.Path;
#if PLATFORM_WINDOWS

	FString fstr_AppName = TEXT("pfbs.exe");
#if PLATFORM_64BITS
	FString fstr_Platform = TEXT("Win64");
#else
	FString fstr_Platform = TEXT("Win32");
#endif

#elif PLATFORM_MAC
	FString fstr_AppName = TEXT("pfbs");
	FString fstr_Platform = TEXT("Mac");
#else
	FString fstr_AppName = TEXT("pfbs.exe");
	FString fstr_Platform = TEXT("");
#endif
	FString fstr_BaseDir = FPaths::ConvertRelativePathToFull(IPluginManager::Get().FindPlugin("PixUI")->GetBaseDir());
	FString fstr_MoudeTransAppPath = fstr_BaseDir / TEXT("Source/PixUI/ThirdParty/Libraries") / fstr_Platform / fstr_AppName;
	//fstr_SrcPath_s fstr_DstPath_s
	if (FPaths::FileExists(fstr_MoudeTransAppPath))
	{
		FString fst_param = (bWatch ? TEXT("-w ") : TEXT("--src ")) + fstr_SrcPath_s + TEXT(" --out ") + fstr_DstPath_s;
#if PLATFORM_MAC
		FString fstr_sh = fstr_BaseDir / TEXT("Source/ThirdParty/Libraries") / fstr_Platform / TEXT("pfbs.sh");
		FString fstr_shData=fstr_MoudeTransAppPath+TEXT(" ")+fst_param;
		FFileHelper::SaveStringToFile(fstr_shData,*fstr_sh, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
		::system(TCHAR_TO_UTF8(*(TEXT("chmod +x ")+fstr_sh)));
		::system(TCHAR_TO_UTF8(*(TEXT("open -a Terminal ")+fstr_sh)));
#else
		FPlatformProcess::LaunchFileInDefaultExternalApplication(*fstr_MoudeTransAppPath, *fst_param, ELaunchVerb::Open);
#endif
		b_ret = true;
	}
	else
	{
		FString fstrTip = TEXT("File ") + fstr_MoudeTransAppPath + TEXT(" dose not Exists");
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(fstrTip));
	}

	return b_ret;
}

FString FPixUIMenuCommands::GetConfigFile()
{
	FString fstr_GameEditorIniFile = FPaths::ProjectConfigDir() / TEXT("DefaultEditor.ini");
	if (!FPaths::FileExists(fstr_GameEditorIniFile))
	{
		TArray<uint8> arry_Data;
		FFileHelper::SaveArrayToFile(arry_Data, *fstr_GameEditorIniFile);
	}
	return fstr_GameEditorIniFile;
}

#undef LOCTEXT_NAMESPACE

#endif	//WITH_EDITOR
