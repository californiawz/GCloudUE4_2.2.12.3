/**************************************************

**** @file:     PixImpMgr.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixImpMgr.h"

#include "PixUILog.h"

#include "PixImp/PixImpFileLoad.h"
#include "PixImp/PixImpMat.h"
#include "PixImp/PixImpImg.h"
#include "PixImp/PixImpFont.h"
#include "PixImp/PixImpNet.h"
#include "PixImp/PixImpSlot.h"

#include "PixImp/PixBrush/PixImgBrush.h"
#include "PixUIDrawItem/PixDrawItem.h"

#include "PixUIWidget.h"


bool PxImgMgrStartLoaderFile(int windowID, const char* pszUrl,
    void(*funOnLoadedCall)(int windowId, const char* pszUrl,
        const unsigned char* pData,
        unsigned int unSize))
{
    return PixImpMgr::Get().StartLoadeFile(windowID, pszUrl, funOnLoadedCall);
}

bool PxImgMgrStopLoaderFile(const char* pszUrl)
{
    return PixImpMgr::Get().StopLoadeFile(pszUrl);
}

void PxImgMgrOnPixPluginLog(pixui::ELogGroup emLogGroup, pixui::ELogLevel emLogLevel, const char* pszLog)
{
    PixImpMgr::Get().OnPixPluginLog(emLogGroup, emLogLevel, pszLog);
}

PixImpMgr& PixImpMgr::Get()
{
    static PixImpMgr PixImpMgr_S;
    return PixImpMgr_S;
}


PixImpMgr* PixImpMgr::GetPtr()
{
    return &(Get());
}


px_plugin::IPluginImp* PixImpMgr::GetImpProxy()
{
    return &(PixImpMgr::Get().mIplguinProxy);
}


void PixImpMgr::PixImpStartup()
{
    //Register sub imp module
    PixImpFileLoad::Register();
    PixImpMat::Register();
    PixImpImg::Register();
    PixImpFont::Register();
    PixImpSlot::Register();
    //PixImpNet::Register();   //Obsolete interface
    //Register sub imp module


    //for each imp
    for (auto imp : PixImpBase::Imps())
    {
        imp->Startup();
    }
}


void PixImpMgr::PixImpTick(const float f_DeltaTime)
{
    //for each imp
    for (auto imp : PixImpBase::Imps())
    {
        imp->Tick(f_DeltaTime);
    }
}


void PixImpMgr::PixImpClear()
{
	PxLog_Trace("PixImpMgr::PixImpClear !!!");
	//for each imp
	for (auto imp : PixImpBase::Imps())
	{
		imp->Clear();
	}
}


void PixImpMgr::PixImpShutdown()
{
    //for each imp
    for (auto imp : PixImpBase::Imps())
    {
        // call shutdown
        imp->Shutdown();
        
        //It is not safe if there is a situation where modules call each other
        //so do not delete here
        //delete imp;     <--------bad bad!!!!
    }

    //delete each imp for safe
    for (auto imp : PixImpBase::Imps())
    {
        //Each module has nearly completed the shutdown operation, we can delete imp here
        delete imp;
    }

    PixDrawItem::FreeAllDrawItem();

    //clear imps
    PixImpBase::Imps().Empty();
}


PixImpMgr::PixImpMgr()
{
    mIplguinProxy.StartLoaderFile = PxImgMgrStartLoaderFile;
    mIplguinProxy.StopLoaderFile = PxImgMgrStopLoaderFile;
    mIplguinProxy.OnPixPluginLog = PxImgMgrOnPixPluginLog;
}


PixImpMgr::~PixImpMgr()
{

}


pixui::uint_ptr PixImpMgr::CreateImage(const char* pszUrl)
{
    check(IsInGameThread());
    return (pixui::uint_ptr)PixImpImg::CreatePixImg(UTF8_TO_TCHAR(pszUrl), 0, TEXT(""));
}

bool PixImpMgr::InitImageByRawData(
    pixui::uint_ptr hImage,
    const int nWidth,
    const int nHeight,
    const int nImageFlag,
    const pixui::EPixelFormat emPixelFormat,
    const uint8* pRawData,
    size_t nDataSize)
{
    auto pImage = PixImpImg::FindPixImgByHandle(hImage);
    if (pImage.IsValid())
    {
        return pImage.Pin()->CreateByRawData(nWidth, nHeight, nImageFlag, emPixelFormat, pRawData, nDataSize);
    }
    else
    {
        PxLog_Error("PixImpMgr::InitImageByRawData not found image:%p", hImage);
    }
    return false;
}

void PixImpMgr::updateImageByRawData(
    pixui::uint_ptr hImage,
    const pixui::EPixelFormat emPixel,
    const uint8* pRawData,
    size_t nDataSize)
{
	auto pImage = PixImpImg::FindPixImgByHandle(hImage);
	if (pImage.IsValid())
	{
		pImage.Pin()->UpdateByRawData(emPixel, pRawData, nDataSize);
	}
	else
	{
		PxLog_Error("PixImpMgr::updateImageByRawData not found image:%p", hImage);
	}
}

void PixImpMgr::GetImageSize(pixui::uint_ptr hImage, pixui::size& sz)
{
	auto pImage = PixImpImg::FindPixImgByHandle(hImage);
	if (pImage.IsValid())
	{
		pImage.Pin()->GetImageSize(sz);
	}
	else
	{
		PxLog_Error("PixImpMgr::GetImageSize not found image:%p", hImage);
	}
}

bool PixImpMgr::IsExternalImage(pixui::uint_ptr hImage)
{
	auto pImage = PixImpImg::FindPixImgByHandle(hImage);
	if (pImage.IsValid())
	{
		return pImage.Pin()->IsExternalImage();
	}
	else
	{
		PxLog_Error("PixImpMgr::IsExternalImage not found image:%p", hImage);
	}
    return false;
}


bool PixImpMgr::DeleteImage(pixui::uint_ptr p_PluginImage)
{
    check(IsInGameThread());
    return PixImpImg::RemovePixImg((PixImgBrush*)p_PluginImage);
}

pixui::uint_ptr PixImpMgr::CreateSlot(const char *pszUrl, int32 winId, const char* pszTagId)
{
    check(IsInGameThread());
    TWeakPtr<PixSlot> weakSlot = PixImpSlot::CreatePixSlot(UTF8_TO_TCHAR(pszUrl), winId, UTF8_TO_TCHAR(pszTagId));
    if (weakSlot.IsValid())
    {
        if (weakSlot.Pin().Get()->IsWidget())
        {
			UPixUIWidget* pWidget = UPixUIWidget::FindPixUIWidgetByID(winId);
			if (pWidget)
			{
				pWidget->AddSlotWidget(weakSlot.Pin().Get()->GetWidget());
			}
        }
        return (pixui::uint_ptr)(weakSlot.Pin().Get());
    }
    return nullptr;
}

bool PixImpMgr::DeleteSlot(pixui::uint_ptr pSlot)
{
    check(IsInGameThread());
    TWeakPtr<PixSlot> weakSlot = PixImpSlot::FindPixSlotByHandle((void* )pSlot);
    if (weakSlot.IsValid())
    {
        if (weakSlot.Pin().Get()->IsWidget())
        {
			UPixUIWidget* pWidget = UPixUIWidget::FindPixUIWidgetByID(weakSlot.Pin().Get()->GetWinId());
			if (pWidget && weakSlot.Pin().Get()->IsWidget())
			{
				pWidget->RemoveSlotWidget(weakSlot.Pin().Get()->GetWidget());
			}
        }
        return PixImpSlot::RemovePixSlot(weakSlot.Pin().Get());
    }
    return false;
}

pixui::uint_ptr PixImpMgr::CreateFont(
    const char*             pszFontName,
    const int               nSize,
    const int               nWeight,
    const unsigned int      unDecoration,
    const pixui::font_style emItalic,
    pixui::FontMetrics*    pFontMetrics)
{
    check(IsInGameThread());
    return PixImpFont::CreateFont(pszFontName,nSize,nWeight,unDecoration,emItalic,pFontMetrics);
}


bool PixImpMgr::RegisterFont(
    const char* pszFileUrl,
    const char* pszFontName,
    const char* pszWeight,
    const char* pszFontStyle,
    void* pContext,
    void(*PfunCallBack)(void* pContext, bool bSucess))
{
    check(IsInGameThread());
    return PixImpFont::RegisterFont(pszFileUrl,pszFontName,pszWeight,pszFontStyle,pContext,PfunCallBack);
}


bool PixImpMgr::DeleteFont(pixui::uint_ptr hFont)
{
    check(IsInGameThread());
    return PixImpFont::DeleteFont(hFont);
}


int PixImpMgr::GetDefaultFontSize()
{
    check(IsInGameThread());
    return PixImpFont::GetDefaultFontSize();
}


const char* PixImpMgr::GetDefaultFontName()
{
    static std::string str_FontName_S;
    str_FontName_S = TCHAR_TO_UTF8(PixImpFont::GetDefaultFont());
    return str_FontName_S.c_str();
}


bool PixImpMgr::StartLoadeFile(int windowID, const char* pszUrl, void (*funOnLoadedCall) (int windowID, const char* pszUrl, const unsigned char* pData, unsigned int unSize))
{
    //Allow other threads to called,PixImpFileLoad::StartLoadFile will be make safe
    //check(IsInGameThread());
    FString fstr_FilePath = UTF8_TO_TCHAR(pszUrl);
	if (fstr_FilePath.StartsWith(TEXT("data:image/")) || fstr_FilePath.Len() > 1024)
	{
		//do not i/o base64
		return false;
	}
    return PixImpFileLoad::StartLoadFile(fstr_FilePath, [=](const TArray<uint8>& ary_Data) {
        //load file call back
        if (funOnLoadedCall)
        {
            funOnLoadedCall(windowID, TCHAR_TO_UTF8(*fstr_FilePath), ary_Data.GetData(), ary_Data.Num());
        }
    });
}


bool PixImpMgr::StopLoadeFile(const char* pszUrl)
{
    check(IsInGameThread());
    return PixImpFileLoad::StopLoadFile(UTF8_TO_TCHAR(pszUrl));
}

/*
pixui::net::WebSocketClient* PixImpMgr::CreateWebSocket(const pixui::net::WebSocketCreatorInfo& WsInfo)
{
    check(IsInGameThread());
    return PixImpNet::CreateWebSocket(WsInfo);
}


bool PixImpMgr::DestroyWebSocket(pixui::net::WebSocketClient* p_WebSocket)
{
    check(IsInGameThread());
    return PixImpNet::DestroyWebSocket((PixWebSocket*)p_WebSocket);
}


pixui::net::XMLHttpRequestBase* PixImpMgr::CreateXMLHttpRequest(pixui::net::XHRCallbacks& fun_XhrCall)
{
    check(IsInGameThread());
    return PixImpNet::CreateXMLHttpRequest(fun_XhrCall);
}


bool PixImpMgr::DestroyXMLHttpRequest(pixui::net::XMLHttpRequestBase* p_XMLHttpRequest)
{
    check(IsInGameThread());
    return PixImpNet::DestroyXMLHttpRequest((PixXmlRequest*)p_XMLHttpRequest);
}
*/

void PixImpMgr::OnPixPluginLog(pixui::ELogGroup e_LogGroup, pixui::ELogLevel e_LogLevel, const char* psz_Log)
{
    //translate pixui core log to Plugin
    FString fstr_Log = UTF8_TO_TCHAR(psz_Log);

    EPXLogTypes  e_TmpType = EPXLogTypes::em_px_log_type_core;
	if (e_LogGroup == pixui::em_lg_script)
	{
		e_TmpType = EPXLogTypes::em_px_log_type_script;
	}

    EPXLogLevels e_TmpLevel = EPXLogLevels::em_px_log_level_log;

    switch (e_LogLevel)
    {
    case pixui::ELogLevel::em_ll_debug:
        e_TmpType = EPXLogTypes::em_px_log_type_trace;
        break;
    case pixui::ELogLevel::em_ll_warning:
        e_TmpLevel = EPXLogLevels::em_px_log_level_warning;
        break;
    case pixui::ELogLevel::em_ll_error:
        e_TmpLevel = EPXLogLevels::em_px_log_level_error;
        break;
    default:
        break;
    }
    UPixUILog::DispatchLog(e_TmpType, e_TmpLevel, fstr_Log);
}