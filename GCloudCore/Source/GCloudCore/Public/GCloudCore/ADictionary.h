//
//  ADictionary.h
//  AContainer
//
//  Created by vforkk on 21/11/14.
//  Copyright (c) 2014 Apollo. All rights reserved.
//

#ifndef __AContainer__ADictionary__
#define __AContainer__ADictionary__

#include "AObject.h"
#include "ANumber.h"

namespace ABase
{


    class EXPORT_CLASS ADictionary : public AObject
    {
    public:
        ADictionary();
        ADictionary(const ADictionary& other);
        ~ADictionary();
        virtual AObject* Clone()const;
        
    public:
        // Set Methods, without copying
        void Set(AObject* key, AObject* value);
        void Set(const AObject& key, AObject* value);
        void Set(const ANumber& key, AObject* value);
        void Set(const char* key, AObject* value);
        
        // Set Methods, With copying
        void Set(const AObject& key, const AObject& value);
        void Set(const ANumber& key, const AObject& value);
        void Set(const ANumber& key, const ANumber& value);
        void Set(const ANumber& key, const char* value);
        void Set(const char* key, const AObject& value);
        void Set(const char* key, const char* value);
        
        void Set(const ADictionary& other);
        
        // Get Methods
        AObject* ObjectForKey(const AObject* key)const;
        AObject* ObjectForKey(const AObject& key)const;
        AObject* ObjectForKey(const ANumber& key)const;
        AObject* ObjectForKey(const char* key)const;
        
        const char* CStringForKey(const AObject* key)const;
        const char* CStringForKey(const AObject& key)const;
        const char* CStringForKey(const ANumber& key)const;
        const char* CStringForKey(const char* key)const;
        
        const AString& AStringForKey(const AObject* key)const;
        const AString& AStringForKey(const AObject& key)const;
        const AString& AStringForKey(const ANumber& key)const;
        const AString& AStringForKey(const char* key)const;
        
        
        
        AObject* KeyAt(int index)const;
        const char* CStringKeyAt(int index)const;
        const AString& AStringKeyAt(int index)const;
        
        
        
        // Remove Methods
        void Remove(const AObject* key);
        void Remove(const ANumber& key);
        void RemoveAll();
        
        // Others
        int Count()const;
        
    public:
        ADictionary& operator=(const ADictionary& dict);
        
        // Override AObject Methods
    private:
        virtual bool IsEqual(const AObject* other)const;
        
    private:
        void* m_collection;
        void* m_keyCollection;
    };
}

#endif /* defined(__AContainer__ADictionary__) */
