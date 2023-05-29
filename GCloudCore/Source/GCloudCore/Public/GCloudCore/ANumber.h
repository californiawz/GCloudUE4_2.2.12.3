//
//  ANumber.h
//  AContainer
//
//  Created by vforkk on 21/11/14.
//  Copyright (c) 2014 Apollo. All rights reserved.
//

#ifndef __AContainer__ANumber__
#define __AContainer__ANumber__
#include "AObject.h"
#include "AString.h"

namespace ABase
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
    	AString ToString()const;
    
    	bool FromString(const char* v);
        
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

	EXPORT_CLASS bool BoolVal(const AObject*);
	EXPORT_CLASS bool BoolVal(const AObject&);
	EXPORT_CLASS unsigned char ByteVal(const AObject*);
	EXPORT_CLASS unsigned char ByteVal(const AObject&);
	EXPORT_CLASS int IntVal(const AObject*);
	EXPORT_CLASS int IntVal(const AObject&);
	EXPORT_CLASS long long LongLongVal(const AObject*);
	EXPORT_CLASS long long LongLongVal(const AObject&);
	EXPORT_CLASS float FloatVal(const AObject*);
	EXPORT_CLASS float FloatVal(const AObject&);
	EXPORT_CLASS double DoubleVal(const AObject*);
	EXPORT_CLASS double DoubleVal(const AObject&);
}

#endif /* defined(__AContainer__ANumber__) */
