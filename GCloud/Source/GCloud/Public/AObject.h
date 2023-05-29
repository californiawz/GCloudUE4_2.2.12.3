//
//  AObject.h
//  AContainer
//
//  Created by vforkk on 21/11/14.
//  Copyright (c) 2014 Apollo. All rights reserved.
//

#ifndef __GCloud__AObject__h__
#define __GCloud__AObject__h__

#include "GCloudPal.h"

namespace GCloud 
{
    class ADictionary;
    class AArray;

    typedef enum
    {
        AOT_Object,
        AOT_String,
        AOT_Number,
        AOT_Array,
        AOT_Dictionary,
        AOT_Data,
    }AObjectType;

    class EXPORT_CLASS AObject
    {
    public:
        AObject();
        virtual ~AObject();
        
    public:
        virtual bool IsEqual(const AObject* other)const
        {
            return other == this;
        }
        
        virtual AObject* Clone()const = 0;
        
    public:
        AObjectType m_xot;
        
    private:
        friend class ADictionary;
        friend class AArray;
        bool m_autoRelease;
    };
}

#endif /* defined(__GCloud__AObject__h__) */
