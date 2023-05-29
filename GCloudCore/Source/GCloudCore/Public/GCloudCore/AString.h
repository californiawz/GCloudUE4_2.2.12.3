//
//  AString.h
//  AContainer
//
//  Created by vforkk on 21/11/14.
//  Copyright (c) 2014 Apollo. All rights reserved.
//

#ifndef __AContainer__AString__
#define __AContainer__AString__

#include "AObject.h"
#include "AData.h"

namespace ABase
{
    class AArray;
    class EXPORT_CLASS AString : public AObject
    {
    public:
        AString();
        AString(const char* str);
        AString(const char* str, int len);
        AString(const AString& str);
        ~AString();
        
    public:
        static bool IsNullOrEmpty(const char* str);
        static bool IsNullOrEmpty(const AString& str);
        static bool IsNullOrEmpty(const AString* str);
        
        static bool IsNumberic(const char* str);
        static bool IsReal(const char* str);
        
        static bool Split(AArray* out, const char* s, const char* delim);
        
    public:
        int GetLength()const;
        const char* CString()const;
        void Clear();
        bool Empty()const;
        int Find(int ch)const;
        
        // stl function
    public:
        int length()const;
        int size()const;
        const char* c_str()const;
        const char* data()const;
        void clear();
        bool empty();
        
        char at(int index)const;
        
        void assign(const char* value, int size);
        
        AString& append(const char* psz);
        AString& append(const char* psz, int size);
        AString& append(const AString& astring);
        
    public:
        
        AString& operator=(const AString& data);
        AString& operator=(const char* str);
        
        AString& operator+=(const AString& data);
        AString& operator+=(const char* pch);
        AString& operator+=(char ch);
        EXPORT_CLASS friend const AString operator+(const AString& s1, const AString& s2);
        
        bool operator!= (const AString& v);
        bool operator!= (const AString& v) const;
        bool operator== (const AString& v);
        bool operator== (const AString& v) const;
        
    public:
        bool IsNumberic()const;
        bool IsReal()const;
        bool AsBoolean()const;
        int32_t AsInt()const;
        int64_t AsInt64()const;
        double AsDouble()const;
        float AsFloat()const;
        
    public:
        static bool StartWith(const char*s, const char* prefix);
        static bool EndWith(const char*s, const char* subfix);
        bool StartWith(const char*);
        bool EndWith(const char*);
        
    public:
        AString Dump(const char* separator = 0)const;
        
        // Override AObject Methods
    public:
        virtual bool IsEqual(const AObject* other)const;
    public:
        virtual AObject* Clone()const;
        
    private:
        AData m_data;
    };


    inline void Ptr2String(AString& str, const char* ptr)
    {
        if (ptr) {
            str = ptr;
        }
        else
        {
            str = "";
        }
    }

    EXPORT_CLASS AString int2str(int i);
    EXPORT_CLASS void str2int(const char* intStr, int* pOutint);
    EXPORT_CLASS int str2int(const char* intStr);
    EXPORT_CLASS AString ll2str(long long i);
    EXPORT_CLASS AString ull2str(unsigned long long i);
    EXPORT_CLASS AString bool2str(bool b);
}

#endif /* defined(__AContainer__AString__) */
