//
//  AStringBuilder.h
//  AContainer
//
//  Created by vforkk on 21/11/14.
//  Copyright (c) 2014 Apollo. All rights reserved.
//

#ifndef __AContainer__AStringBuilder__
#define __AContainer__AStringBuilder__

#include "AString.h"

namespace ABase
{


    class EXPORT_CLASS AStringBuilder : public AObject
    {
    public:
        AStringBuilder();
        AStringBuilder(const char* s);
        AStringBuilder(const AString& s);
        AStringBuilder(const AString* s);
        AStringBuilder(const AStringBuilder* s);
        
    public:
        virtual AObject* Clone()const;
        
    public:
        void Append(const char* s);
        void Append(const AString& s);
        void Append(const AString* s);
        
    public:
        void Clear();
        
    public:
        AStringBuilder& operator=(const AString& data);
        AStringBuilder& operator=(const AStringBuilder& data);
        AStringBuilder& operator=(const char* str);
        
        AStringBuilder& operator+=(const AString& data);
        AStringBuilder& operator+=(const char* data);
        
    public:
        //void Replace(const char c);
        
    public:
        const char* ToString()const;
        
        // Override AObject Methods
    public:
        virtual bool IsEqual(const AObject* other)const;
        
    private:
        void resize(int needSize);
    private:
        AData m_data;
    };
}

#endif /* defined(__AContainer__AStringBuilder__) */
