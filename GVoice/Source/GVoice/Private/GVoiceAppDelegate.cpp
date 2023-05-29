//
//  GVoiceAppDelegate.m
//  GVoiceSample_Index
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//
#include "GVoiceAppDelegate.h"



GVoiceAppDelegate& GVoiceAppDelegate::GetInstance()
{
    static GVoiceAppDelegate instance;
    return instance;
}

GVoiceAppDelegate::GVoiceAppDelegate()
{
}

#if !defined(__APPLE__) || defined(__GVOICE_MAC__)
void GVoiceAppDelegate::Initialize()
{

}
#endif

