/**************************************************

**** @file:     PixUIEditorMgr.h

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

class PixUIEditorMgr : public TSharedFromThis<PixUIEditorMgr>
{
public:
	PixUIEditorMgr();
	~PixUIEditorMgr();

public:
	static void StartUp();
	static void Shutdown();

	static PixUIEditorMgr* p_PixUIMgrEditor_s;

public:
	void OnStartUp();
	void OnShutdown();
};

#endif //WITH_EDITOR only for editor
