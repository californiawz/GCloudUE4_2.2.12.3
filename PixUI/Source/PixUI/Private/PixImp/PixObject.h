/**************************************************

**** @file:     PixObject.h

**** @brief:    pixui item object base

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#include "CoreMinimal.h"


class PixObject
{
public:
    PixObject() 
    {
        un_UsedRefCount_ = 1;
    }

    virtual ~PixObject() 
    {

    }

    void AddRef()
    {
        un_UsedRefCount_++;
    }

    bool DecRef()
    {
        return ((--un_UsedRefCount_) <= 0);
    }

    bool IsUsed()
    {
        return un_UsedRefCount_ > 0;
    }

private:
    uint32 un_UsedRefCount_;
};