//
//  BundleFactory.h
//  GCloudCore
//
//  Created by cedarsun on 16-3-25.
//  Copyright (c) 2016ƒÍ. All rights reserved.
//


#ifndef _ABase_BundleFactory_
#define _ABase_BundleFactory_

#include <string>
#include <map>
#include "Bundle.h"
#include "AMutex.h"

namespace ABase {
    
    class EXPORT_CLASS BundleFactory
    {
    private:
        BundleFactory();
        
    public:
        static BundleFactory& GetInstance();
        static void ReleaseInstance();
		virtual ~BundleFactory();

    public:
        Bundle& GetDefaultBundle();
        Bundle& GetBundle(const char* path);
        void DestoryBundle(const char* path);
    private:
        std::map<std::string,Bundle*> _bundleCollection;
        CMutex _mutex;
        static BundleFactory* _Instance;
    };
}

#endif

