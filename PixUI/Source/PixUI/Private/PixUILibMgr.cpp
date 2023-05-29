/**************************************************

**** @file:     PixUILibMgr.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/09

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixUILibMgr.h"

#include "PixUILog.h"

//for PixExtBpCall
namespace UE4_PixUI
{
	const char* reg();
}


namespace PixUI
{
#define BePixLibLoadRef BePixLibLoad()
    bool& BePixLibLoad()
    {
        static bool b_PixLibLoad_s = false;
        return b_PixLibLoad_s;
    }


    bool PixLibLoad()
    {
        // do something stuff for lib load
        BePixLibLoadRef = true;

#if defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
        //Dynamic way to load library files
        BePixLibLoadRef = px_plugin::PxDyLibLoad();
#endif
		//for PixExtBpCall
		UE4_PixUI::reg();

        return BePixLibLoadRef;
    }

    bool PixLibUnLoad()
    {
        // do something stuff for lib unload
        bool b_ret = true;

#if defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
        //Dynamic way to load library files
        b_ret = px_plugin::PxDyLibUnLoad();
#endif
        if (b_ret)
            BePixLibLoadRef = false;

        return b_ret;
    }
};