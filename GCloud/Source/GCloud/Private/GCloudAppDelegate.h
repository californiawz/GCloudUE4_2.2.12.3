//
//  GCloudAppDelegate.h
//  GCloudSample
//
//  Created by vforkk on 9/11/2017.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//

#ifndef GCloudAppDelegate_h
#define GCloudAppDelegate_h

class GCloudAppDelegate
{
public:
    GCloudAppDelegate();
    static GCloudAppDelegate& GetInstance();
    
public:
    void Initialize();
};

#endif /* GCloudAppDelegate_h */
