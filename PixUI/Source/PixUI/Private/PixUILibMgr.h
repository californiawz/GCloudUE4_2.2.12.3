/**************************************************

**** @file:     PixUILibMgr.h

**** @brief:    pixui plugin library manager

**** @author:   tianzelei

**** @date:     2020/12/09

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once

#include "CoreMinimal.h"

#if defined(DF_USE_DEBUG_LIB) && (DF_USE_DEBUG_LIB)
//for debug
#include "PixLibEx/PixDyLibDebug.h"
#elif defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
//dynamic load lib file
#include "PixLibEx/PixDyLib.h"
#else
//static link lib
#include "px_plugin.h"
#endif

//
namespace PixUI
{
    //check lib be loaded
    bool& BePixLibLoad();

    //load lib
    bool PixLibLoad();

    //unload lib
    bool PixLibUnLoad();
};