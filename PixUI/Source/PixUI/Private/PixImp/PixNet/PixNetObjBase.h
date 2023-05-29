/**************************************************

**** @file:     PixNetObjBase.h

**** @brief:    PixUI net base object class

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "CoreMinimal.h"


//use TSharedFromThis information
class PixNetObjBase : public TSharedFromThis<PixNetObjBase>
{
public:
    PixNetObjBase() {};

    virtual ~PixNetObjBase() {};

public:
    //called when destroy
    virtual void Destroy() {};
};

