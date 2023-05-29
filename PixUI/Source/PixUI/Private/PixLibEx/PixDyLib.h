/**************************************************

**** @file:     PixDyLib.h

**** @brief:    Use dynamic loading to load the core library of pixui (ios was not supported)

**** @author:   tianzelei

**** @date:     2020/12/09

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#include "hf_idraw.h"
#include "hf_iwindow.h"
#include "px_plugindef.h"



namespace px_plugin
{
    //lib load
    bool PxDyLibLoad();

    //lib unload
    bool PxDyLibUnLoad();

#if defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
	/******************************************************************************************/
	//for px mgr
	const char* pxVersion();
	const char* pxExternalAgent();
	bool pxStartup(px_plugin::IPluginImp* pPluginImp, const char* pszWritePath = nullptr, const char* externalAgent = nullptr);
	void pxSetCachePath(const char* pszCachePath);
	void pxDebugPauseResume(const bool bPause);
	void pxCatchDebugTrace(bool bCatch);
	void pxTimeTick(float fDuration);
	void pxEnterBackground();
	void pxEnterForeground();
	bool pxShutdown();
	//for px mgr
	/******************************************************************************************/

	/******************************************************************************************/
	//for px view
	pixui::PxViewHandle pxViewCreate(uint32_t id = 0);
	void pxViewInit(pixui::PxViewHandle hView, pixui::IHostWindow* pIWinEvent, pixui::IHostDraw* pIWinDraw, const int nWidth, const int nHeight,
		const pixui::PxViewDeviceParam* pDeviceParam = nullptr);
	void* pxViewGetContext(pixui::PxViewHandle hView);
	int pxViewLoadPageFromData(pixui::PxViewHandle hView, const unsigned char* pData, const unsigned int unDataSize,
		const char* pszBasePath);
	int pxViewLoadPageFromUrl(pixui::PxViewHandle hView, const char* pszPageUrl);
	bool pxViewHitTest(pixui::PxViewHandle hView, const int nXpos, const int nYpos);
	bool pxViewMouseEvent(pixui::PxViewHandle hView, const int nXpos, const int nYpos, const int nZpos,
		const pixui::MouseButton emBtnEvent, const bool bDown);
	bool pxViewTouchEvent(pixui::PxViewHandle hView, const int nXpos, const int nYpos, const pixui::int32 nTouchPoint,
		const pixui::ETouchPhase emTouchPhase);
	bool pxViewKeyEvent(pixui::PxViewHandle hView, const pixui::EKeyCode emKey, const unsigned char ucModifiers, const bool bDown);
	int pxViewKeyboardInput(pixui::PxViewHandle hView, const char* szInput, const bool bEndInput, const bool bLostFocus,
		const bool bReplace);
	int pxViewWinSizeUpdate(pixui::PxViewHandle hView, const int nNewWidth, const int nNewHeight);
	void pxViewResetRenderScale(pixui::PxViewHandle hView, float scale);
	void pxViewScreenSizeUpdate(pixui::PxViewHandle hView, int screenWidth, int screenHeight);
	bool pxViewTick(pixui::PxViewHandle hView);
	int pxViewPaint(pixui::PxViewHandle hView, int nParam = DF_PAINT_MODE_NONE);
	int pxViewRenderFrame(pixui::PxViewHandle hView);
	int pxViewRenderReset(pixui::PxViewHandle hView, int nStatus = 0, void* pParams = nullptr);
	int pxViewPostMessage(pixui::PxViewHandle hView, const char* pszMessage, const pixui::PxViewHandle h_src_view = 0);
	pixui::PxViewHandle pxViewGetScriptVM(pixui::PxViewHandle hView);
	int pxViewClose(pixui::PxViewHandle hView);
	int pxViewDestroy(pixui::PxViewHandle hView);
	//for px view
	/******************************************************************************************/


	/******************************************************************************************/
	//for embedded
	void pxSetEngineOpenPageDelegate(pixui::EngineOpenPageDelegate callback);
	int pxExecuteEngineOpenPageDelegate(int winId, pixui::LoadPageArg* loadPageArg);

	void pxSetEngineClosePageDelegate(pixui::EngineClosePageDelegate callback);
	bool pxExecuteEngineClosePageDelegate(int winId);

	void pxSetEnginePostMessageDelegate(pixui::EnginePostMessageDelegate callback);
	bool pxExecuteEnginePostMessageDelegate(int winId, const char* message);

	void pxSetNativePostMessageDelegate(pixui::NativePostMessageDelegate callback);

	void pxExecuteNativePostMessageDelegate(int winId, int type, int code, const char* message);

	const char* pxLoadAppletConfig(const char* appletAssetsPath, const char* appletName);
	//for embedded
	/******************************************************************************************/

	/******************************************************************************************/
	//for inner render
	void pxInnerRenderSetSystemFontParam(bool beLoadSystemFonts, bool beAsyncLoadSystemFonts);
	int pxInnerRenderCount();
	const char* pxInnerRenderName(int nIndex);
	int pxInnerRenderSetFontDefaultName(int nIndexRender, const char* pFontName);
	const char* pxInnerRenderGetFontDefaultName(int nIndexRender);
	int pxInnerRenderAddFontByBuffer(int nIndexRender, const char* pFontName, const char* pData, size_t nSize);
	int pxInnerRenderAddFontByPath(int nIndexRender, const char* pFontName, const char* pszFontPath, const bool bAsset);
	//for inner render
	/******************************************************************************************/

	/******************************************************************************************/
	//for pixui script
	pixui::PxViewHandle pxsCreate(pixui::IHostWindow* pHostWindow = nullptr, bool bWait = false);
	void pxsDestroy(pixui::PxViewHandle vm, bool wait = false);
	void pxsDoFile(pixui::PxViewHandle vm, const char* url);
	void pxsDoBuffer(pixui::PxViewHandle vm, const void* buffer, size_t len, const char* name);
	const char* pxsSendMessage(pixui::PxViewHandle vm, const char* msg, int waitMS);
	void pxsFreeMessage(const char* msg);
	//for pixui script
	/******************************************************************************************/

	/******************************************************************************************/
	//for android init
	void pxInitAndroid(pixui::uint_ptr jMainActivity, pixui::uint_ptr jAssetManager, pixui::uint_ptr jVm = nullptr);
	//for android init
	/******************************************************************************************/
#endif //defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
}
