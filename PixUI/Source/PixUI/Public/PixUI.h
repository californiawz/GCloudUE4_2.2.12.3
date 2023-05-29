// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Tickable.h"

class FPixUIModule : public IModuleInterface, FTickableGameObject
{ 
public:
    /************************************************************************/
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    /** IModuleInterface implementation */
    /************************************************************************/

public:
    /************************************************************************/
    /** FTickableGameObject implementation */
    virtual void Tick(float f_DeltaTime) override;
    virtual TStatId GetStatId() const override;
    virtual bool IsTickable() const override;
    virtual bool IsTickableInEditor() const override;
    /** FTickableGameObject implementation */
    /************************************************************************/

private:
	/** Callback for when the application resumed in the foreground. */
	void HandleApplicationHasEnteredForeground();

	/** Callback for when the application is being paused in the background. */
	void HandleApplicationWillEnterBackground();

	/** Foreground/background delegate for pause. */
	FDelegateHandle m_hPauseHandle;

	/** Foreground/background delegate for resume. */
	FDelegateHandle m_hResumeHandle;
};
