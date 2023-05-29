/**************************************************

**** @file:     PixUIEditorMgr.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/14

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


//for editor only
#if WITH_EDITOR
#include "PixUIEditorMgr.h"

#include "PixUIEditorSettings/PixUIEditorSettings.h"
#include "PixUIEditorMenuCommond/PixUIEditorMenuCommond.h"
#include "PixUIAssetEditor/PixUIAssetEditor.h"
#include "PixUIContentBrowserExtensions/PixUIContentBrowserExtensions.h"

#define LOCTEXT_NAMESPACE "FPixUIModule"


PixUIEditorMgr* PixUIEditorMgr::p_PixUIMgrEditor_s = nullptr;

PixUIEditorMgr::PixUIEditorMgr()
{
}

PixUIEditorMgr::~PixUIEditorMgr()
{
}

void PixUIEditorMgr::StartUp()
{
	if (!p_PixUIMgrEditor_s)
	{
		p_PixUIMgrEditor_s = new PixUIEditorMgr();
	}

	p_PixUIMgrEditor_s->OnStartUp();
}


void PixUIEditorMgr::Shutdown()
{
	if (p_PixUIMgrEditor_s)
	{
		p_PixUIMgrEditor_s->OnShutdown();
		delete p_PixUIMgrEditor_s;
		p_PixUIMgrEditor_s = nullptr;
	}
}

void PixUIEditorMgr::OnStartUp()
{
	// Registered editor plugin style
	FPixUIMenuCommands::Initialize();
	FPixUIAssetEditor::Initialize();
	UPixUIEditorSettings::Initialize();

	FPixUIContentBrowserExtensions::InstallHooks();
}


void PixUIEditorMgr::OnShutdown()
{
	// Anti-registration editor plugin style
	FPixUIMenuCommands::Shutdown();
	FPixUIAssetEditor::Shutdown();
	UPixUIEditorSettings::Shutdown();
}

#undef LOCTEXT_NAMESPACE

#endif //WITH_EDITOR only for editor
