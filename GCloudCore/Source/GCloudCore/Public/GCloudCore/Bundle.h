//
//  Bundle.h
//  GCloudCore
//
//  Created by cedarsun on 16-3-25.
//  Copyright (c) 2016ƒÍ. All rights reserved.
//


#ifndef _ABase_Bundle_
#define _ABase_Bundle_

#include "AString.h"
#include "AArray.h"
#include "AValue.h"

namespace ABase {
    
    class EXPORT_CLASS Bundle
    {
    public:
        Bundle();
		virtual ~Bundle();
        
    private:
        Bundle(const Bundle&);

    public:
        
        virtual bool Set(const char* section, const char* key, int value) = 0;
        virtual bool Set(const char* section, const char* key, int64_t value) = 0;
        virtual bool Set(const char* section, const char* key, const char* value) = 0;
        virtual bool Set(const char* section, const char* key, bool value) = 0;
        
        virtual bool Set(const char* key, int value) = 0;
        virtual bool Set(const char* key, int64_t value) = 0;
        virtual bool Set(const char* key, const char* value) = 0;
        virtual bool Set(const char* key, bool value) = 0;
        
        virtual int64_t Get(const char* section, const char* key, int64_t defaultvalue) = 0;
        virtual int Get(const char* section, const char* key, int defaultvalue) = 0;
        virtual AString Get(const char* section, const char* key, const char* defaultvalue) = 0;
        virtual bool Get(const char* section, const char* key, bool defaultvalue) = 0;
        
        virtual int64_t Get(const char* key, int64_t defaultvalue) = 0;
        virtual int Get(const char* key, int defaultvalue) = 0;
        virtual AString Get(const char* key, const char* defaultvalue) = 0;
        virtual bool Get(const char* key, bool defaultvalue) = 0;
        
        // AValue
        virtual bool Set(const Value& value) = 0;
        virtual bool Set(const char* section, const Value& value) = 0;
        virtual bool Get(const char* section, Value& value) = 0;
        virtual bool Get(const char* section, const char* key, Value& value) = 0;
        
        virtual bool RemoveSection(const char* section) = 0;
        virtual bool RemoveValueForKey(const char* section, const char* key) = 0;
        virtual void GetAllKeys( const char* section , AArray* keys) = 0;
        virtual bool IsContainKey(const char* section, const char* key) = 0;

        virtual bool RemoveAll() = 0;
        
        virtual bool SaveCacheToFile() = 0;
        virtual bool SetCache(const char* section, const char* key, int value) = 0;
        virtual bool SetCache(const char* section, const char* key, int64_t value) = 0;
        virtual bool SetCache(const char* section, const char* key, const char* value) = 0;
        virtual bool SetCache(const char* section, const char* key, bool value) = 0;
        virtual bool RemoveCacheSection(const char* section) = 0;
        virtual bool RemoveCacheAll() = 0;
        virtual bool RemoveCacheValueForKey(const char* section, const char* key) = 0;
        
        //meta-data/plist
        virtual AString GetMetaString(const char* section, const char* key, const char* defaultvalue);
    };
}

#endif

