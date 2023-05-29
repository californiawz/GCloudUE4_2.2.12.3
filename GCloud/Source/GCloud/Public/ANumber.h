//
//  ANumber.h
//  AContainer
//
//  Created by vforkk on 21/11/14.
//  Copyright (c) 2014 Apollo. All rights reserved.
//

#ifndef __GCloud__ANumber__h__
#define __GCloud__ANumber__h__
#include "AObject.h"

namespace GCloud
{

    class EXPORT_CLASS ANumber : public AObject
    {
    public:
        ~ANumber();
        ANumber();
        ANumber(const ANumber& other);
        ANumber(bool v);
        ANumber(unsigned char v);
        ANumber(int i);
        ANumber(long long l);
        ANumber(float f);
        ANumber(double f);
        virtual AObject* Clone()const;
        
    public:
        ANumber& operator= (const ANumber& other);
        ANumber& operator= (bool v);
        ANumber& operator= (unsigned char v);
        ANumber& operator= (int i);
        ANumber& operator= (long long l);
        ANumber& operator= (float f);
        ANumber& operator= (double f);
        
        // equal operator
        bool operator!= (const ANumber& v);
        bool operator!= (const ANumber& v) const;
        bool operator== (const ANumber& v);
        bool operator== (const ANumber& v) const;
        
    public:
        bool BoolValue()const;
        unsigned char ByteValue()const;
        int IntValue()const;
        long long LongLongValue()const;
        float FloatValue()const;
        double DoubleValue()const;
        
    public:
        //AString ToString()const;
        
        //bool FromString(const char* v);
        
    public:
        enum Type
        {
            NONE = 0,
            BOOLEAN,
            BYTE,
            INTEGER,
            INT64,
            FLOAT,
            DOUBLE,
        };
        Type GetType()const;
        const char*GetTypeString()const;
        
        bool IsNull()const;
        
        // Override AObject Methods
    public:
        virtual bool IsEqual(const AObject* other)const;
        
    private:
        void clear();
        void reset(Type type);
        union
        {
            unsigned char byteVal;
            int intVal;
            long long int64Val;
            float floatVal;
            double doubleVal;
            bool boolVal;
        }m_field;
        
        Type m_type;
        
    };

    // extern bool BoolVal(const AObject*);
    // extern bool BoolVal(const AObject&);
    // extern unsigned char ByteVal(const AObject*);
    // extern unsigned char ByteVal(const AObject&);
    // extern int IntVal(const AObject*);
    // extern int IntVal(const AObject&);
    // extern long long LongLongVal(const AObject*);
    // extern long long LongLongVal(const AObject&);
    // extern float FloatVal(const AObject*);
    // extern float FloatVal(const AObject&);
    // extern double DoubleVal(const AObject*);
    // extern double DoubleVal(const AObject&);
}

#endif /* defined(__GCloud__ANumber__h__) */
