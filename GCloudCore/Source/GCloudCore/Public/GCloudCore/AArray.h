//
//  AList.h
//  AContainer
//
//  Created by vforkk on 21/11/14.
//  Copyright (c) 2014 Apollo. All rights reserved.
//

#ifndef __AContainer__AArray__
#define __AContainer__AArray__
#include "AObject.h"
#include "ANumber.h"
#include "AString.h"

namespace ABase
{

    class EXPORT_CLASS AArray : public AObject
    {
    public:
        AArray();
        AArray(const AArray* array);
        AArray(const AArray& array);
        ~AArray();
        
    public:
        virtual AObject* Clone()const;
        
    public:
        // Add Methods Without cloning
        void Add(const AObject* obj, bool autoRelease = false);
        
        // Add Methods, with clone
        void Add(const AObject& obj);
        void Add(const ANumber& number);
        void Add(const AArray* array);
        void Add(const char* str);
        
        // Remove Methods
        void RemoveObjectAtIndex(int index);
        void RemoveLastObject();
        void RemoveFirstObject();
        void RemoveAll();
        
        AObject* ObjectAtIndex(int index)const;
        AObject* FirstObject()const;
        AObject* LastObject()const;
        
        const char* CStringAtIndex(int index)const;
        const char* FirstCString()const;
        const char* LastCString()const;
        
        const AString& AStringAtIndex(int index)const;
        const AString& FirstAString()const;
        const AString& LastAString()const;
        
        int Count()const;
        
    public:
        AObject* operator[](int index)const;
        AArray& operator=(const AArray& array);
        
        // Override AObject Methods
    public:
        // discard
        //virtual bool IsEqual(const AObject* other)const;
        
    public:
        void* m_vecCollection;
    };

}
#endif /* defined(__AContainer__AArray__) */
