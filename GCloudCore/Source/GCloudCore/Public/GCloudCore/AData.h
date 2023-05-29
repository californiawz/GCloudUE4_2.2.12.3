//
//  AData.h
//  AContainer
//
//  Created by vforkk on 21/11/14.
//  Copyright (c) 2014 Apollo. All rights reserved.
//

#ifndef __AContainer__AData__
#define __AContainer__AData__
#include "AObject.h"

namespace ABase
{
    class EXPORT_CLASS AData : public AObject
    {
    public:
        AData();
        AData(const AData& data);
        AData(const unsigned char* data, int len);
        AData(int capacity);
        ~AData();
        virtual AObject* Clone()const;
        
    public:
        void Assign(const unsigned char* data, int len);
        
        void Append(const AData& data);
        void Append(const unsigned char* data, int len);
        void Append(const char* data);
        const unsigned char* Data()const;
        int Capacity()const;
        void SetCapacity(int size);
        int Size()const;
        int LeftSize()const;
        void Clear();
        bool Empty()const;
        
    public:
        int Find(int ch)const;
        
    public:
        AData& operator=(const AData& data);
        AData& operator=(const char* psz);
        
        // Todo:
        //AData* operator+(const AData& data);
        AData& operator+=(const AData& data);
        
        // Override AObject Methods
    public:
        virtual bool IsEqual(const AObject* other)const;
        
    private:
        unsigned char* m_pBuffer;
        int m_nCapacity;
        int m_nSize;
    };
}


#endif /* defined(__AContainer__AData__) */
