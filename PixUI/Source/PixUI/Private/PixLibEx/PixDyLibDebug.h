/**************************************************

**** @file:     PixDyLibDebug.h

**** @brief:    Used for debug the library interface, 
                this function is not needed for the release version. 
                Open the macro DF_USE_DEBUG_LIB when need testing ;same as px_plugin.h file

**** @author:   tianzelei

**** @date:     2020/12/21

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#if defined(DF_USE_DEBUG_LIB) && (DF_USE_DEBUG_LIB)

#include "px_plugindef.h"
#include "px_plugininterface.h"

namespace PX_Plugin
{
    /*
    get version

    @ return: current pixui version
    */
    PX_API const char* PX_Version();


    /*
    startup for pixui lib

    @pszCachePath:  base work path for write cache file(if is null,use default path.ps:some platform default maybe failed to load)

    return: be ok
    */
    PX_API bool PX_Startup(IPluginImp *pImp, const char *pszWritePath = nullptr);


    /*
    change cache path

    @ pszCachePath: new cache path

    @ return:
    */
    PX_API void PX_SetCachePath(const char* pszCachePath);


    /*
    for debug module to pause or resume pixui

    @ bPause: be pause

    @ return:
    */
    PX_API void PX_DebugPauseResume(const bool bPause);


    /*
    for debug module to catch debug trace,and trace will be call back in PX_RegLogImpl delegate; ps type is: em_lg_core em_ll_debug

    @ bCatch: is or not Catch debug trace

    @ return:
    */
    PX_API void PX_CatchDebugTrace(bool bCatch);

    /*
    time tick call

    @ fDuration: time duration

    @ return:
    */
    PX_API void PX_TimeTick(float fDuration);


    /*
    shutdown for pixui lib

    return: be ok
    */
    PX_API bool PX_Shutdown();


    /*
    create h5 view for draw

    @pIPluginWin:   window interface inheritance on IPluginWindow class
    @pIPluginDraw:  draw interface inheritance on IPluginDraw class
    @nWidth:        win width
    @nHeight:       win height

    return: handle of Pixui view
    */
    PX_API px_ptr PX_ViewCreate(IPluginWindow* pIPluginWin, IPluginDraw* pIPluginDraw, const int nWidth, const int nHeight, int& n_out_id);


    /*
    Load html page for view

    @hView:         handle of Pixui view
    @pData:         html load data
    @unDataSize:    size of html data
    @pszBasePath:   base path for load other resource

    return: 0 is ok,other see the error code
    */
    PX_API int PX_ViewLoadPageFromData(px_ptr hView, const unsigned char* pData, const unsigned int unDataSize, const char* pszBasePath);


    /*
    Load html page for view

    @hView:         handle of Pixui view
    @pszPageUrl:    html url

    return: 0 is ok,other see the error code
    */
    PX_API int PX_ViewLoadPageFromUrl(px_ptr hView, const char* pszPageUrl);



	PX_API bool PX_ViewHitTest(px_ptr hView, const int nXpos, const int nYpos);


    /*
    mouse event for view page

    @hView:     handle of Pixui view
    @nXpos:     x pos
    @nYpos:     y pos
    @nZpos:     wheel offset pos
    @emBtnEvent:    button status
    @bDown: be button down

    */
    PX_API bool PX_ViewMouseEvent(px_ptr hView, const int nXpos, const int nYpos, const int nZpos, const pixui::MouseButton emBtnEvent, const bool bDown);


	/*
	touch event for view page

	@hView:     handle of Pixui view
	@nXpos:     x pos
	@nYpos:     y pos
	@unTouchPoint: touch index
	@emTouchPhase: touch type

	*/
	PX_API bool PX_ViewTouchEvent(px_ptr hView, const int nXpos, const int nYpos, const pixui::int32 nTouchPoint, const pixui::ETouchPhase emTouchPhase);


    /*
    keyboard event for view page

    @hView:         handle of Pixui view
    @emKey:         key
    @ucModifiers:   combination of key
    @bDown:         be key down

    */
    PX_API bool PX_ViewKeyEvent(px_ptr hView, const pixui::EKeyCode emKey, const unsigned char ucModifiers, const bool bDown);


    /*
    input event for view page

    @ hView:        handle of Pixui view
    @ szInput:      input text
    @ bEndInput:    is end input or not

    return: 0 is ok,other see the error code
    */
    PX_API int PX_ViewkeyBoardInput(px_ptr hView, const char *szInput, const bool bEndInput, const bool bLostFocus, const bool bReplace);


    /*
    Call the function to update the entire view page when the window size changes

    @hView:         handle by PX_ViewCreate Create
    @nNewWidth:     new Width
    @nNewHeight:    new Height

    return: 0 is ok,other see the error code
    */
    PX_API int PX_ViewWinSizeUpdate(px_ptr hView, const int nNewWidth, const int nNewHeight);


    /*
    Call the function to draw the entire view page

    @hView:         handle by PX_ViewCreate Create
    @hDevice:       draw device
    @pParam:        Reserved

    return: 0 is ok,other see the error code
    */
    PX_API int PX_ViewPaint(px_ptr hView, px_ptr hDevice, px_ptr pParam);


    /*
    post message to script

    @ hView:
    @ nEventId: handle by PX_ViewCreate Create
    @ nParam1: param1
    @ nParam2: param2
    @ pszMessage: message

    return: 0 is ok,other see the error code
    */
    PX_API int PX_ViewPostMessage(px_ptr hView, const char* pszMessage, const px_ptr h_src_view = nullptr);


    /*
    Clean view page

    @hView: handle by PX_ViewCreate Create

    return: 0 is ok,other see the error code
    */
    PX_API int PX_ViewClose(px_ptr hView);

    /*
    destroy view handle

    @hView: handle by PX_ViewCreate Create

    return: 0 is ok,other see the error code
    */
    PX_API int PX_ViewDestroy(int windowID);
}

#endif //defined(DF_USE_DEBUG_LIB) && (DF_USE_DEBUG_LIB)