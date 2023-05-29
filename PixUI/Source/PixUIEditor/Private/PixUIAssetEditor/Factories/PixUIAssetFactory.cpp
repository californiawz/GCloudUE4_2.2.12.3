// Fill out your copyright notice in the Description page of Project Settings.


#include "PixUIAssetFactory.h"

#include "PixUILog.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "PixUIAssetEditor/AssetTools/PixUIAsset.h"

UPixUIAssetFactory::UPixUIAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Formats.Add(TEXT("html;html File"));
	Formats.Add(TEXT("js;javaScript File"));
	SupportedClass = UPixUIAsset::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}

void UPixUIAssetFactory::TransformToPfbs(FString FilePath, FString& PFBS_Path)
{
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
	FString WriteCachePathRef = FPaths::ProjectSavedDir();
#if PLATFORM_ANDROID
	WriteCachePathRef = IAndroidPlatformFile::GetPlatformPhysical().FileRootPath(*WriteCachePathRef);
#elif PLATFORM_IOS
	WriteCachePathRef = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*WriteCachePathRef);
#else
	WriteCachePathRef = FPaths::ConvertRelativePathToFull(WriteCachePathRef);
#endif
	FString PixUIAssetCachePath = WriteCachePathRef / "PixUIAssetCache";
	if (!FPaths::DirectoryExists(PixUIAssetCachePath))
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		if (!PlatformFile.CreateDirectory(*PixUIAssetCachePath))
		{
			PxLog_Error("Create Pixui Cache dir error :%s", TCHAR_TO_UTF8(*PixUIAssetCachePath));
		}
	}
	FString FileName;
	int lastPos;
	if (FilePath.FindLastChar('/', lastPos))
	{
		FileName = FilePath.Mid(lastPos + 1, FilePath.Len() - lastPos - 1);
	}
	else if (FilePath.FindLastChar('\\', lastPos))
	{
		FileName = FilePath.Mid(lastPos + 1, FilePath.Len() - lastPos - 1);
	}
	else
	{
		FileName = FilePath;
	}
	PFBS_Path = PixUIAssetCachePath / FileName;
	if (FPaths::FileExists(fstr_MoudeTransAppPath))
	{
		FString fst_param = (TEXT("--src ")) + FilePath +
			TEXT(" --out ") + PFBS_Path;
#if PLATFORM_MAC
		FString fstr_sh = fstr_BaseDir / TEXT("Source/ThirdParty/Libraries") / fstr_Platform / TEXT("pfbs.sh");
		FString fstr_shData=fstr_MoudeTransAppPath+TEXT(" ")+fst_param;
		FFileHelper::SaveStringToFile(fstr_shData,*fstr_sh, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
		::system(TCHAR_TO_UTF8(*(TEXT("chmod +x ")+fstr_sh)));
		::system(TCHAR_TO_UTF8(*(TEXT("open -a Terminal ")+fstr_sh)));
#else
		FPlatformProcess::LaunchFileInDefaultExternalApplication(*fstr_MoudeTransAppPath, *fst_param, ELaunchVerb::Open);
#endif
	}
}

UObject* UPixUIAssetFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UPixUIAsset* PixUIAsset = nullptr;
	FString TextString;
	bOutOperationCanceled = false;
	if (FFileHelper::LoadFileToString(TextString, *Filename))
	{
		PixUIAsset = NewObject<UPixUIAsset>(InParent, InClass, InName, Flags);
		PixUIAsset->Text = FText::FromString(TextString);
		if (Filename.Contains(".html"))
		{
			PixUIAsset->AssetType = UPixUIAsset::Html;
		}
		else if (Filename.Contains(".js"))
		{
			PixUIAsset->AssetType = UPixUIAsset::JavaScript;
		}
		PixUIAsset->Name = *(InName.ToString());
		PixUIAsset->Path = Filename;

		if (PixUIAsset->NeedPfbsData)
		{
			TransformToPfbs(PixUIAsset->Path, PixUIAsset->PFBS_Path);
		}
	}
	else
	{
		bOutOperationCanceled = true;
	}
	return PixUIAsset;
}

UObject* UPixUIAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UPixUIAsset* PixUIAsset = nullptr;

	PixUIAsset = NewObject<UPixUIAsset>(InParent, InClass, InName, Flags);

	return PixUIAsset;
}
