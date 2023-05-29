/**************************************************

**** @file:     PixUIExInterface.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixUIExInterface.h"

#include "PixImp/PixImpFileLoad.h"
#include "PixImp/PixImpImg.h"
#include "PixImp/PixImpSlot.h"

namespace PixUI
{
    void SetExternalAssetFileLoadDelegate(PFun_PixFileLoad fun_FileLoad)
    {
        PixImpFileLoad::SetExternalFileLoadDelegate(fun_FileLoad);
    }

    void SetExternalBrushLoadDelegate(PFun_PixBrushLoad fun_BrushLoad)
    {
        PixImpImg::SetExternalBrushLoadDelegate(fun_BrushLoad);
    }

    void SetExternalWidgetLoadDelegate(PFun_PixWidgetLoad fun_WidgetLoad)
    {
        PixImpSlot::SetExternalSlotLoadDelegate(fun_WidgetLoad);
    }
};