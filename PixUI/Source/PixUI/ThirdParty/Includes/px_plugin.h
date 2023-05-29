
/*
注意这个文件的接口不能随意修改，需要保持对外提供api的版本兼容性
任何修改对需要保持版本向下兼容
*/

#pragma once

#include "px_plugindef.h"

#include "hf_idraw.h"
#include "hf_iwindow.h"

namespace px_plugin
{
	using pixui::PxViewHandle;
	/******************************************************************************************/
	//for px mgr
	/*
    get version

    @ return: current pixui version
    */
	PX_C_API const char *pxVersion();


	PX_C_API const char *pxExternalAgent();

	/*
    startup for pixui lib

    @pszCachePath:  base work path for write cache file(if is null,use default path.ps:some platform default maybe failed to load)

    return: be ok
    */
	PX_C_API bool pxStartup(IPluginImp *pPluginImp, const char *pszWritePath = nullptr, const char *externalAgent = nullptr);

	// for itest
	PX_C_API bool pxStartupSimple(IPluginImp *pPluginImp, const char *pszWritePath = nullptr, const char *externalAgent = nullptr);


	/*
    change cache path

    @ pszCachePath: new cache path

    @ return:
    */
	PX_C_API void pxSetCachePath(const char *pszCachePath);


	/*
    for debug module to pause or resume pixui

    @ bPause: be pause

    @ return:
    */
	PX_C_API void pxDebugPauseResume(const bool bPause);


	class PxWindow;
	PxWindow *findPxWinFromMap(PxViewHandle hView);
	/*
    for debug module to catch debug trace,and trace will be call back in px_RegLogImpl delegate; ps type is: em_lg_core em_ll_debug

    @ bCatch: is or not Catch debug trace

    @ return:
    */
	PX_C_API void pxCatchDebugTrace(bool bCatch);

	PX_C_API void pxEnterBackground();

	PX_C_API void pxEnterForeground();
	/*
    shutdown for pixui lib

    return: be ok
    */
	PX_C_API bool pxShutdown();
	//for px mgr
	/******************************************************************************************/


	/******************************************************************************************/
	//for px view
	/*
    create h5 view for draw

    @pIPluginWin:   window interface inheritance on IPluginWindow class
    @pIPluginDraw:  draw interface inheritance on IPluginDraw class
    @nWidth:        win width
    @nHeight:       win height

    return: handle of Pixui view
    */
	PX_C_API PxViewHandle pxViewCreate(uint32_t id = 0);


	PX_C_API void pxViewInit(PxViewHandle hView, pixui::IHostWindow *pIWinEvent, pixui::IHostDraw *pIWinDraw, const int nWidth, const int nHeight,
							 const pixui::PxViewDeviceParam *pDeviceParam = nullptr);


	//get core context
	PX_C_API void *pxViewGetContext(PxViewHandle hView);

	PX_C_API void pxViewHistoryGo(PxViewHandle hView, int step);

	/*
    Load html page for view

    @hView:         handle of Pixui view
    @pData:         html load data
    @unDataSize:    size of html data
    @pszBasePath:   base path for load other resource

    return: 0 is ok,other see the error code
    */
	PX_C_API int pxViewLoadPageFromData(PxViewHandle hView, const unsigned char *pData, const unsigned int unDataSize,
										const char *pszBasePath);


	/*
    Load html page for view

    @hView:         handle of Pixui view
    @pszPageUrl:    html url

    return: 0 is ok,other see the error code
    */
	PX_C_API int pxViewLoadPageFromUrl(PxViewHandle hView, const char *pszPageUrl);


	/*
    Do script buffer for view

	@hView:         handle of Pixui view
	@buffer:        js buffer
	@len:           js buffer len
	@name:          js module name
	*/
	PX_C_API int pxViewDoScriptBuffer(PxViewHandle hView, const void *buffer, size_t len, const char *name);


	/*
    Do script file for view

	@hView:          handle of Pixui view
	@pszFilePath:    js file path
	@name:           js module name
	*/
	PX_C_API int pxViewDoScriptFile(PxViewHandle hView, const char *pszFilePath, const char *name);


	/*
    hit test for view page,

    @hView:     handle of Pixui view
    @nXpos:     x pos
    @nYpos:     y pos

    return: ture or false
    */
	PX_C_API bool pxViewHitTest(PxViewHandle hView, const int nXpos, const int nYpos);


	/*
    mouse event for view page

    @hView:     handle of Pixui view
    @nXpos:     x pos
    @nYpos:     y pos
    @nZpos:     wheel offset pos
    @emBtnEvent:    button status
    @bDown: be button down

    */
	PX_C_API bool pxViewMouseEvent(PxViewHandle hView, const int nXpos, const int nYpos, const int nZpos,
								   const pixui::MouseButton emBtnEvent, const bool bDown);


	/*
    touch event for view page

    @hView:     handle of Pixui view
    @nXpos:     x pos
    @nYpos:     y pos
    @unTouchPoint: touch index
    @emTouchPhase: touch type

    */
	PX_C_API bool pxViewTouchEvent(PxViewHandle hView, const int nXpos, const int nYpos, const pixui::int32 nTouchPoint,
								   const pixui::ETouchPhase emTouchPhase);


	/*
    keyboard event for view page

    @hView:         handle of Pixui view
    @emKey:         key
    @ucModifiers:   combination of key
    @bDown:         be key down

    */
	PX_C_API bool
	pxViewKeyEvent(PxViewHandle hView, const pixui::EKeyCode emKey, const unsigned char ucModifiers, const bool bDown);


	/*
    input event for view page

    @ hView:        handle of Pixui view
    @ szInput:      input text
    @ bEndInput:    is end input or not

    return: 0 is ok,other see the error code
    */
	PX_C_API int pxViewKeyboardInput(PxViewHandle hView, const char *szInput, const bool bEndInput, const bool bLostFocus,
									 const bool bReplace);


	/*
    Call the function to update the entire view page when the window size changes

    @hView:         handle by PX_ViewCreate Create
    @nNewWidth:     new Width
    @nNewHeight:    new Height

    return: 0 is ok,other see the error code
    */
	PX_C_API int pxViewWinSizeUpdate(PxViewHandle hView, const int nNewWidth, const int nNewHeight);

	PX_C_API void pxViewScreenSizeUpdate(PxViewHandle hView, int screenWidth, int screenHeight);

	PX_C_API void pxViewResetRenderScale(PxViewHandle hView, float scale);

	PX_C_API bool pxViewTick(PxViewHandle hView);

	/*
    Call the function to draw the entire view page

    @hView:         handle by PX_ViewCreate Create
    @pParam:        Reserved

    return: 0 is ok,other see the error code
    */
	PX_C_API int pxViewPaint(PxViewHandle hView, int nParam = DF_PAINT_MODE_NONE);

	PX_C_API int pxViewRenderFrame(PxViewHandle hView);
	/*
    post message to script

    @ hView: handle by PX_ViewCreate Create
    @ pszMessage: message
    @ h_src_view: source of message, null for default...

    return: 0 is ok,other see the error code
    */
	PX_C_API int pxViewPostMessage(PxViewHandle hView, const char *pszMessage, const PxViewHandle h_src_view = 0);


	PX_C_API PxViewHandle pxViewGetScriptVM(PxViewHandle hView);

	/*
    Clean view page

    @hView: handle by PX_ViewCreate Create

    return: 0 is ok,other see the error code
    */
	PX_C_API int pxViewClose(PxViewHandle hView);

	/*
    destroy view handle

    @hView: handle by PX_ViewCreate Create

    return: 0 is ok,other see the error code
    */
	PX_C_API int pxViewDestroy(PxViewHandle hView);

	PX_C_API void *pxViewGetScriptState(PxViewHandle hView);
#ifdef WITH_H5WINDOW_SIGNAL
	PX_C_API pixui::IWindowSignal *pxViewGetSignals(PxViewHandle hView);
#endif
	//for px view
	/******************************************************************************************/

	/******************************************************************************************/
	//for embedded
	PX_C_API void pxSetEngineOpenPageDelegate(pixui::EngineOpenPageDelegate callback);
	PX_C_API int pxExecuteEngineOpenPageDelegate(int winId, pixui::LoadPageArg *loadPageArg);

	PX_C_API void pxSetEngineClosePageDelegate(pixui::EngineClosePageDelegate callback);
	PX_C_API bool pxExecuteEngineClosePageDelegate(int winId);

	PX_C_API void pxSetEnginePostMessageDelegate(pixui::EnginePostMessageDelegate callback);
	PX_C_API bool pxExecuteEnginePostMessageDelegate(int winId, const char *message);

	PX_C_API void pxSetNativePostMessageDelegate(pixui::NativePostMessageDelegate callback);

	PX_C_API void pxExecuteNativePostMessageDelegate(int winId, int type, int code, const char *message);

	PX_C_API const char *pxLoadAppletConfig(const char *appletAssetsPath, const char *appletName);
	//for embedded
	/******************************************************************************************/

	/******************************************************************************************/
	//for inner render
	PX_C_API void pxInnerRenderSetSystemFontParam(bool beLoadSystemFonts, bool beAsyncLoadSystemFonts);
	PX_C_API int pxInnerRenderCount();
	PX_C_API const char *pxInnerRenderName(int nIndex);
	PX_C_API int pxInnerRenderSetFontDefaultName(int nIndexRender, const char *pFontName);
	PX_C_API const char *pxInnerRenderGetFontDefaultName(int nIndexRender);
	PX_C_API int pxInnerRenderAddFontByBuffer(int nIndexRender, const char *pFontName, const char *pData, size_t nSize);
	PX_C_API int pxInnerRenderAddFontByPath(int nIndexRender, const char *pFontName, const char *pszFontPath, const bool bAsset);
	//for inner render
	/******************************************************************************************/

	/******************************************************************************************/
	//for pixui script
	PX_C_API PxViewHandle pxsCreate(pixui::IHostWindow *pHostWindow = nullptr, bool bWait = false);
	PX_C_API void pxsDestroy(PxViewHandle vm, bool wait = false);
	PX_C_API bool pxsExist(PxViewHandle vm);
	PX_C_API void pxsDoFile(PxViewHandle vm, const char *url);
	PX_C_API void pxsDoBuffer(PxViewHandle vm, const void *buffer, size_t len, const char *name);
	PX_C_API void pxsDoFileInStrictMode(PxViewHandle vm, pixui::LoadPageArg arg, bool isHotUpload = false);
	PX_C_API const char *pxsSendMessage(PxViewHandle vm, const char *msg, int waitMS = -1);
	PX_C_API void pxsFreeMessage(const char *msg);
	//for pixui script
	/******************************************************************************************/

	/******************************************************************************************/
	//for android
	/**
    初始化PixUI的Android环境,需要在pxStartup前调用,且只需要调用一次.
    @jMainActivity: Java的Activity对象,用于初始化PixUI网络库的DNS解析能力
    @jAssetManager: Java的AssetManager对象,用于读取应用内资源
    @jVm:           Java虚拟机对象,如果调用过PixUI的JNI_OnLoad可以传nullptr,否则一定要传,不然PixUI将无法正常启动
    */
	PX_C_API void pxInitAndroid(pixui::uint_ptr jMainActivity, pixui::uint_ptr jAssetManager, pixui::uint_ptr jVm = nullptr);

	/**
    释放PixUI的Android的相关引用,在不需要使用PixUI时调用
    */
	PX_C_API void pxUnInitAndroid();
	//for android
	/******************************************************************************************/

	/******************************************************************************************/
	//for pixui hot update
	// HOTUPDATE TODO: HotUpdateWindow or IHostWindow
	class HotUpdateWindow;
	PX_C_API void pxHotUpdate(pixui::LoadPageArg arg, HotUpdateWindow *window = nullptr);
	//for pixui hot update
	/******************************************************************************************/
}// namespace px_plugin