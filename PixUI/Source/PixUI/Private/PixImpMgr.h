/**************************************************

**** @file:     PixImpMgr.h

**** @brief:    PixUI Core abstract factory implementation

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once

#include "CoreMinimal.h"

#include "px_plugindef.h"

class UPixUIWidget;

class PixImpMgr
{
public:
    static PixImpMgr& Get();
    static PixImpMgr* GetPtr();

    static px_plugin::IPluginImp* GetImpProxy();

    //PixUI Module call startup
    static void PixImpStartup();

    //PixUI Module call timer tick
    static void PixImpTick(const float f_DeltaTime);


	static void PixImpClear();

    //PixUI Module call shutdown
    static void PixImpShutdown();

protected:
    PixImpMgr();

public:
    virtual ~PixImpMgr();

public:
    /************************************************************************/
    /** PX_Plugin::IPluginImpCreator implementation */
    //for image factory
    pixui::uint_ptr CreateImage(const char* pszUrl);
	bool InitImageByRawData(
        pixui::uint_ptr hImage,
        const int nWidth,
        const int nHeight, 
        const int nImageFlag,
        const pixui::EPixelFormat emPixelFormat,
        const uint8* pRawData,
        size_t nDataSize);
	void updateImageByRawData(
        pixui::uint_ptr hImage,
        const pixui::EPixelFormat emPixel,
        const uint8* pRawData,
        size_t nDataSize);
	void GetImageSize(pixui::uint_ptr hImage, pixui::size& sz);
	bool IsExternalImage(pixui::uint_ptr hImage);
    bool DeleteImage(pixui::uint_ptr p_PluginImage);

    pixui::uint_ptr CreateSlot(const char *pszUrl, int32 winId, const char* pszTagId);
    bool DeleteSlot(pixui::uint_ptr pSlot);

    //for font factory
    pixui::uint_ptr CreateFont(
        const char*             pszFontName,
        const int               nSize,
        const int               nWeight,
        const unsigned int      unDecoration,
        const pixui::font_style emItalic,
        pixui::FontMetrics*    pFontMetrics);
    bool RegisterFont(
        const char* pszFileUrl,
        const char* pszFontName,
        const char* pszWeight,
        const char* pszFontStyle,
        void* pContext,
        void(*PfunCallBack)(void* pContext, bool bSucess));
    bool DeleteFont(pixui::uint_ptr hFont);
    int GetDefaultFontSize();
    const char* GetDefaultFontName();

    //for file load factory
    bool StartLoadeFile(int windowID, const char* pszUrl,
        void(*funOnLoadedCall)(int windowID, const char* pszUrl, const unsigned char* pData, unsigned int unSize));
    bool StopLoadeFile(const char* pszUrl);

	/*
    //for net factory
    virtual pixui::net::WebSocketClient* CreateWebSocket(const pixui::net::WebSocketCreatorInfo& WsInfo) override;
    virtual bool DestroyWebSocket(pixui::net::WebSocketClient* p_WebSocket) override;

    virtual pixui::net::XMLHttpRequestBase* CreateXMLHttpRequest(pixui::net::XHRCallbacks& fun_XhrCall) override;
    virtual bool DestroyXMLHttpRequest(pixui::net::XMLHttpRequestBase* p_XMLHttpRequest) override;
    */


    //for log out put
    void OnPixPluginLog(pixui::ELogGroup e_LogGroup, pixui::ELogLevel e_LogLevel, const char* psz_Log);
    /** PX_Plugin::IPluginImpCreator implementation */
    /************************************************************************/
private:
    px_plugin::IPluginImp mIplguinProxy;
};