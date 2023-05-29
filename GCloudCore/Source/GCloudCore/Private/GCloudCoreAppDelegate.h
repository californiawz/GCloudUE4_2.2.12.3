//
//  GCloudCoreAppDelegate.h
//  GCloudSample
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//

#ifndef GCloudCoreAppDelegate_h
#define GCloudCoreAppDelegate_h

class GCloudCoreAppDelegate
{
public:
    GCloudCoreAppDelegate();
    static GCloudCoreAppDelegate& GetInstance();
    
public:
    void Initialize();
    void InitializeOpenUrl();
};

#endif /* GCloudCoreAppDelegate_h */
