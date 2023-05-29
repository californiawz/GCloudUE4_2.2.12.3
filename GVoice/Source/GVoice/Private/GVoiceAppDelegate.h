//
//  GVoiceAppDelegate.h
//  GVoiceSample
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//

#ifndef GVoiceAppDelegate_h
#define GVoiceAppDelegate_h

class GVoiceAppDelegate
{
public:
    GVoiceAppDelegate();
    static GVoiceAppDelegate& GetInstance();
    
public:
    void Initialize();
};

#endif /* GVoiceAppDelegate_h */
