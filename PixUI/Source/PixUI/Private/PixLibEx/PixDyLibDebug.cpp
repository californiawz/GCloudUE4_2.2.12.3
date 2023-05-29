/**************************************************

**** @file:     PixDyLibDebug.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/21

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixDyLibDebug.h"

#if defined(DF_USE_DEBUG_LIB) && (DF_USE_DEBUG_LIB)

namespace PX_Plugin
{
    const char* PX_Version()
    {
        return "test_version_0.0.1";
    }

	bool PX_Startup(IPluginImp *pImp, const char *pszWritePath /*= nullptr*/);
    {
        return true;
    }

    void PX_SetCachePath(const char* pszCachePath)
    {

    }

    void PX_DebugPauseResume(const bool bPause)
    {

    }


    void PX_CatchDebugTrace(bool bCatch)
    {

    }



    void PX_TimeTick(float fDuration)
    {

    }


    bool PX_Shutdown()
    {
        return true;
    }



    px_ptr PX_ViewCreate(IPluginWindow* pIPluginWin, IPluginDraw* pIPluginDraw, const int nWidth, const int nHeight, int& n_out_id)
    {
        return nullptr;
    }


    int PX_ViewLoadPageFromData(px_ptr hView, const unsigned char* pData, const unsigned int unDataSize, const char* pszBasePath)
    {
        return 0;
    }


    int PX_ViewLoadPageFromUrl(px_ptr hView, const char* pszPageUrl)
    {
        return 0;
    }

	bool PX_ViewHitTest(px_ptr hView, const int nXpos, const int nYpos)
	{
		return false;
	}


    bool PX_ViewMouseEvent(px_ptr hView, const int nXpos, const int nYpos, const int nZpos, const pixui::MouseButton emBtnEvent, const bool bDown)
    {
        return false;
    }

	bool PX_ViewTouchEvent(px_ptr hView, const int nXpos, const int nYpos, const pixui::int32 nTouchPoint, const pixui::ETouchPhase emTouchPhase)
	{
		return false;
	}


    bool PX_ViewKeyEvent(px_ptr hView, const pixui::EKeyCode emKey, const unsigned char ucModifiers, const bool bDown)
    {
        return false;
    }


    int PX_ViewkeyBoardInput(px_ptr hView, const char *szInput, const bool bEndInput, const bool bLostFocus, const bool bReplace)
    {
        return 0;
    }


    int PX_ViewWinSizeUpdate(px_ptr hView, const int nNewWidth, const int nNewHeight)
    {
        return 0;
    }


    int PX_ViewPaint(px_ptr hView, px_ptr hDevice, px_ptr pParam)
    {
        return 0;
    }


    int PX_ViewPostMessage(px_ptr hView, const char* pszMessage, const px_ptr h_src_view)
    {
        return 0;
    }


    int PX_ViewClose(px_ptr hView)
    {
        return 0;
    }

    int PX_ViewDestroy(int windowID)
    {
        return 0;
    }
}

#endif //defined(DF_USE_DEBUG_LIB) && (DF_USE_DEBUG_LIB)