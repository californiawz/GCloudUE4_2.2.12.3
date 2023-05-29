/**************************************************

**** @file:     PixImpFont.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/11

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/




#include "PixImpFont.h"

#include "SlateOptMacros.h"
#include "UnrealEngine.h"
#include "Slate.h"
#include "Engine/Font.h"
#include "Engine/FontFace.h"

#include "PixUILog.h"
#include "PixUIDef.h"
#include "PixUtil.h"
#include "PixImpFileLoad.h"

#include "PixUIProfiler/PxpResCount.h"



PixFont::PixFont()
{
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	//for debug
	PxLog_Trace("PixFont new    %d   %p", ++ResItemCount::PixFontCount(), this);
#endif  //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}

PixFont::~PixFont()
{
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	//for debug
	PxLog_Trace("PixFont delete %d   %p", --ResItemCount::PixFontCount(), this);
#endif  //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}


PixImpFont::PixImpFont()
    : PixImpBase(TEXT("PixImpFont"))
{

}


PixImpFont::~PixImpFont()
{

}


void PixImpFont::OnStartup()
{
    if (DefaultFontRef().empty())
    {
        //default font
        SetDefaultFont(TEXT("Roboto"));
        SetDefaultFontSize(16);

        //uasset roboto font path
        //FString fstr_DefaultFontPath = FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf");
        AddFontPath(TEXT("Roboto"), DF_UE_ROBOTO_FONT_UASSET);
    }
}


void PixImpFont::OnTick(const float f_DeltaTime)
{
    //do something stuff
}


void PixImpFont::OnClear()
{
	//do something stuff
}


void PixImpFont::OnShutdown()
{
    map_PixFont_.Empty();

    DefaultFontRef().clear();

    //clear font
    FontPaths().Empty();
}

//hpjy  资源flush宏，用于在同步资源加载时如果出现触发异步队列加载时的超时不上报告警信息
#ifndef ALLOW_FLUSHING
#define ALLOW_FLUSHING
#endif

pixui::uint_ptr PixImpFont::CreateFont(
    const char*             pszFontName,
    const int               nSize,
    const int               nWeight,
    const unsigned int      unDecoration,
    const pixui::font_style emItalic,
    pixui::FontMetrics*    pFontMetrics)
{
    if (!Get())
    {
        PxLog_Error("PixImpFont::CreateFont error PixImpFont Do Not Startup!!!");
        return nullptr;
    }

	ALLOW_FLUSHING

    FString fstrFontName = UTF8_TO_TCHAR(pszFontName);
    FString fstrFontPath;// = FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"); //for test
    uint32 unFontSize = PixUtil::PixToPt(nSize); //ue4 font size was point

    FString fstr_TypeFaceName;
    MakeFontTypeFaceName(nWeight, (emItalic == pixui::fontStyleItalic) ? TEXT("Italic") : TEXT(""), fstr_TypeFaceName);

    if (!GetFontPath(pszFontName, fstrFontPath))
    {
        FString fstrTmpFontName = GetDefaultFont();
        GetFontPath(fstrTmpFontName, fstrFontPath);
        PxLog_Warning(" SPixPaintWidget::CreateFont can not found font:%s ,use default font:%s", TCHAR_TO_UTF8(*fstrFontName), TCHAR_TO_UTF8(*fstrTmpFontName));

        fstrFontName = fstrTmpFontName;
    }

    //UE4_FontSize = PS_72DPI_FontSize * 72DPI/96DPI / UE4_96DPI_Scale
    //pix font size as pixel size,but ue4 use pt;

    FString fstr_Key = GetPixFontKey(fstrFontName, fstr_TypeFaceName, unFontSize);

    TSharedPtr<PixFont> sptr_PixFont = Get()->FindFontByKey(fstr_Key);
    if (sptr_PixFont.IsValid())
    {
        sptr_PixFont->AddRef();
        PxLog_Trace("PixImpFont::CreateFont found same font:%s %p",TCHAR_TO_UTF8(*fstr_Key), sptr_PixFont.Get());
    }
    else
    {
        sptr_PixFont = MakeShareable(new PixFont());
        sptr_PixFont->wptr_FontObject_ = nullptr;

        //
        if (FPaths::FileExists(fstrFontPath))
        {//load file path
            sptr_PixFont->sptr_SlatFont_ = MakeShareable(new FSlateFontInfo(fstrFontPath, unFontSize));
            //custom font create .ttf or .otf file path,typeface use font name
            sptr_PixFont->sptr_SlatFont_->TypefaceFontName = FName(*fstr_TypeFaceName);
        }
        else
        {
            UFont* p_fontObj = nullptr;
            if (fstrFontPath.IsEmpty())
            {
                PxLog_Warning("SPixPaintWidget::CreateFont can not load font:%s path:%s ,use system default font roboto", TCHAR_TO_UTF8(*fstrFontName), TCHAR_TO_UTF8(*fstrFontPath));
                fstrFontPath = DF_UE_ROBOTO_FONT_UASSET;
                p_fontObj = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL, *fstrFontPath));
            }
            else
            {
                p_fontObj = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL, *fstrFontPath));
                if (!p_fontObj)
                {
                    PxLog_Warning(" SPixPaintWidget::CreateFont can not load font:%s path:%s ,use system default font roboto", TCHAR_TO_UTF8(*fstrFontName), TCHAR_TO_UTF8(*fstrFontPath));
                    fstrFontPath = DF_UE_ROBOTO_FONT_UASSET;
                    p_fontObj = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL, *fstrFontPath));
                }
            }

            if (p_fontObj)
            {
                p_fontObj->AddToRoot();
                sptr_PixFont->wptr_FontObject_ = p_fontObj;
                sptr_PixFont->sptr_SlatFont_ = MakeShareable(new FSlateFontInfo(p_fontObj, unFontSize));
                sptr_PixFont->sptr_SlatFont_->TypefaceFontName = FName(*fstr_TypeFaceName);
            }
        }
        Get()->map_PixFont_.Add(fstr_Key, sptr_PixFont);
        PxLog_Trace("PixImpFont::CreateFont Create Font key:%s  %p", TCHAR_TO_UTF8(*fstr_Key), sptr_PixFont.Get());
    }

    if (sptr_PixFont->sptr_SlatFont_.IsValid())
    {
        //Measure font size
        const TSharedRef< FSlateFontMeasure > FontMeasureService = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
#if 0
		uint16 nBaseLine = abs(FontMeasureService->GetBaseline(*(sptr_PixFont->sptr_SlatFont_.Get())));
		uint16 nFontHeight = FontMeasureService->GetMaxCharacterHeight(*(sptr_PixFont->sptr_SlatFont_.Get()));
		pFontMetrics->height = nFontHeight;										//height
		pFontMetrics->descent = nBaseLine;										//bottom to baseline
		pFontMetrics->ascent = pFontMetrics->height - pFontMetrics->descent;	//baseline to top
#else
		////////////////////////////////////UE4 font scale////////////////////////////////////////
		float f_GeomeryScale = PixUtil::SlateScaleRate();

		uint16 nBaseLine = abs(FontMeasureService->GetBaseline(*(sptr_PixFont->sptr_SlatFont_.Get()), f_GeomeryScale));
		uint16 nFontHeight = FontMeasureService->GetMaxCharacterHeight(*(sptr_PixFont->sptr_SlatFont_.Get()), f_GeomeryScale);

		uint16 us_font_height = ceil(nFontHeight / f_GeomeryScale);
		uint16 us_base_line = ceil(nBaseLine / f_GeomeryScale);
		////////////////////////////////////UE4 font scale////////////////////////////////////////


		pFontMetrics->height = us_font_height;									//height
		pFontMetrics->descent = us_base_line;									//bottom to baseline
		pFontMetrics->ascent = pFontMetrics->height - pFontMetrics->descent;	//baseline to top
#endif
    }
    else
    {
        PxLog_Error("Can not found any valid font for use!!!");
    }
    return (pixui::uint_ptr)sptr_PixFont.Get();
}


bool PixImpFont::RegisterFont(
    const char* pszFileUrl,
    const char* pszFontName,
    const char* pszWeight,
    const char* pszFontStyle,
    void* pContext,
    void(*PfunCallBack)(void* pContext, bool bSucess))
{
    FString fstr_FileUrl;
    FString fstr_FontName = UTF8_TO_TCHAR(pszFontName);

    PxLog_Trace(" SPixPaintWidget::RegisterFont pszFontName:%s  pszFileUrl:%s", pszFontName, pszFileUrl);

    if (!GetFontPath(fstr_FontName, fstr_FileUrl))
    {
        fstr_FileUrl = UTF8_TO_TCHAR(pszFileUrl);
        //if pszFileUrl is local file load font,if it was net file ,download file and load font
        if (fstr_FileUrl.StartsWith(TEXT("http")))
        {
            PixImpFileLoad::StartLoadFile(fstr_FileUrl, [=](const TArray<uint8>& arry_Data) {

                bool b_ret = false;
                FString fstr_FontSavePath;
                if (arry_Data.Num() > 0)
                {
                    FString fstr_fileName = FPaths::GetCleanFilename(fstr_FileUrl);
                    if (fstr_fileName.IsEmpty())
                    {
                        uint32 un_CyclesMum = FPlatformTime::Cycles();
                        fstr_fileName = FString::FromInt(un_CyclesMum) + TEXT(".ttf");
                    }

                    FString fstr_FileDir;
                    if (PixImpFileLoad::CreateRegFontDir(fstr_FileDir))
                    {
                        fstr_FontSavePath = fstr_FileDir / fstr_fileName;
                        b_ret = PixImpFileLoad::SaveFileToPath(fstr_FileDir, arry_Data);
                    }
                }

                if (b_ret)
                {
                    PxLog_Log("SPixPaintWidget::RegisterFont load success url:%s save Path:%s",
                        TCHAR_TO_UTF8(*fstr_FileUrl),TCHAR_TO_UTF8(*fstr_FontSavePath));

                    AddFontPath(fstr_FontName, fstr_FontSavePath);
                }
                else
                {
                    PxLog_Error("SPixPaintWidget::RegisterFont load Error url:%s",
                        TCHAR_TO_UTF8(*fstr_FileUrl));
                }


                if (PfunCallBack)
                {
                    PfunCallBack(pContext, b_ret);
                }
            });
        }
        else
        {

            //默认注册所有字体,待加载不到字体的时候在回滚
			AddFontPath(fstr_FontName, fstr_FileUrl);
			PxLog_Log("SPixPaintWidget::RegisterFont load success name:%s path:%s", pszFontName, pszFileUrl);
			if (PfunCallBack)
			{
				PfunCallBack(pContext, true);
			}

            /*
            bool b_fontExist = false;
            if (FPaths::FileExists(fstr_FileUrl))
            {
                b_fontExist = true;
            }
			else
            {
                //Maybe it's a game asset
                FString fstr_AssetFileUrl = FPaths::ProjectContentDir() + fstr_FileUrl;
                if (FPaths::FileExists(fstr_AssetFileUrl))
                {
                    b_fontExist=true;
                    fstr_FileUrl=fstr_AssetFileUrl;
                }
            }

            if(b_fontExist)
            {
                AddFontPath(fstr_FontName, fstr_FileUrl);

                PxLog_Log("SPixPaintWidget::RegisterFont load success name:%s path:%s", pszFontName, pszFileUrl);
                if (PfunCallBack)
                {
                    PfunCallBack(pContext, true);
                }
            }
			else
            {
                 PxLog_Error("SPixPaintWidget::RegisterFont load error name:%s path:%s", pszFontName, pszFileUrl);
                 if (PfunCallBack)
                 {
                     PfunCallBack(pContext, false);
                 }
            }
            */
        }
    }
    else
    {
        PxLog_Log("SPixPaintWidget::RegisterFont was loaded success name:%s path:%s", pszFontName, pszFileUrl);

        if (PfunCallBack)
        {
            PfunCallBack(pContext, true);
        }
    }

    return false;
}


bool PixImpFont::DeleteFont(pixui::uint_ptr hFont)
{
    if (!Get())
    {
        PxLog_Error("PixImpFont::DeleteFont error PixImpFont Do Not Startup!!!");
        return false;
    }

    for (auto font : Get()->map_PixFont_)
    {
        if (font.Value.Get() == (PixFont*)hFont)
        {
            if (font.Value.IsValid())
            {
                if (font.Value->DecRef())
                {
                    if (font.Value->wptr_FontObject_.IsValid())
                    {
                        font.Value->wptr_FontObject_->RemoveFromRoot();
                    }
                    PxLog_Trace("PixImpFont::DeleteFont Create Font key:%s %p", TCHAR_TO_UTF8(*font.Key), font.Value.Get());
                    Get()->map_PixFont_.Remove(font.Key);
                }
            }
            else
            {
                Get()->map_PixFont_.Remove(font.Key);
            }
            return true;
        }
    }

    PxLog_Error("PixImpFont::DeleteFont error Do Not Found font:%p", hFont);
    return false;
}


TWeakPtr<PixFont> PixImpFont::GetSlateFont(pixui::uint_ptr h_Font)
{
    if (Get())
    {
        auto sptr_PixFont = Get()->FindFontByHandle(h_Font);
        if (sptr_PixFont.IsValid())
        {
            return sptr_PixFont;
        }
    }
    PxLog_Error("PixImpFont::GetSlateFont Can Not Found Font:%p",h_Font);
    return nullptr;
}


void PixImpFont::AddFontPath(const FString& fstr_FontName, const FString& fstr_FontPath)
{
    if (FontPaths().Find(fstr_FontName))
    {
        PxLog_Error(" PixUI_AddSystemFont already exist name:%s path:%s", TCHAR_TO_UTF8(*fstr_FontName), TCHAR_TO_UTF8(*fstr_FontPath));
    }
    else
    {
        FontPaths().Add(fstr_FontName, fstr_FontPath);
    }
}


void PixImpFont::RemoveFontPath(const FString& fstr_FontName)
{
    if (FontPaths().Remove(fstr_FontName) < 0)
    {
        PxLog_Error("PixImpFont::RemoveFontPath not found font:%s",TCHAR_TO_UTF8(*fstr_FontName));
    }
}


void PixImpFont::SetDefaultFontSize(int32 n_FontSize)
{
    DefaultFontSizeRef() = n_FontSize;
}


int32 PixImpFont::GetDefaultFontSize()
{
    return  DefaultFontSizeRef();
}


const char* PixImpFont::GetDefaultFont()
{
    return PixImpFont::DefaultFontRef().c_str();
}


void PixImpFont::SetDefaultFont(const FString& fstr_FontName)
{
    DefaultFontRef() = TCHAR_TO_UTF8(*fstr_FontName);
}


bool PixImpFont::GetFontPath(const FString& fstr_FontName, FString& fst_OutPath)
{
    bool b_ret = false;
    auto p_FontPath = FontPaths().Find(fstr_FontName);
    if (p_FontPath)
    {
        b_ret = true;
        fst_OutPath = *p_FontPath;
    }
    return b_ret;
}


void PixImpFont::MakeFontTypeFaceName(int nWeight, const FString& fstr_FontStyle, FString& fstr_OutName)
{
    /*
    100 - Thin
    200 - Extra Light (Ultra Light)
    300 - Light
    400 - Regular (Normal、Book、Roman)
    500 - Medium
    600 - Semi Bold (Demi Bold)
    700 - Bold
    800 - Extra Bold (Ultra Bold)
    900 - Black (Heavy)
    */

    FString fstr_Weight;
    if (nWeight < 250)
    {
        //thin font  ps:have no thin font for roboto
        fstr_Weight = TEXT("Thin");
    }
    else if (nWeight < 350)
    {
        //light font
        fstr_Weight = TEXT("Light");
    }
    else if (nWeight < 450)
    {
        //regular Normal
        fstr_Weight = TEXT("Regular");
    }
    else if (nWeight < 550)
    {
        //Medium font ps:have no medium font for roboto
        fstr_Weight = TEXT("Medium");
    }
    else if (nWeight < 750)
    {
        //Bold font
        fstr_Weight = TEXT("Bold");
    }
    else
    {
        //Medium font ps:have no Black font for roboto
        fstr_Weight = TEXT("Black");
    }

    MakeFontTypeFaceName(fstr_Weight, fstr_FontStyle, fstr_OutName);
}


void PixImpFont::MakeFontTypeFaceName(const FString& fstr_Weight, const FString& fstr_FontStyle, FString& fstr_OutName)
{
    //TypeFace Name fstr_OutName
    /*
    e.g.:
    Thin
    Thin Italic
    Light
    Light Italic
    Regular
    Italic
    Medium
    Medium Italic
    Bold
    Bold Italic
    Black
    Black Italic
    */
    if (fstr_Weight.IsEmpty())
    {
        if (fstr_FontStyle.IsEmpty())
        {
            fstr_OutName = TEXT("Regular");
        }
        else
        {
            fstr_OutName = fstr_FontStyle;
        }
    }
    else
    {
        if (fstr_FontStyle.IsEmpty())
        {
            fstr_OutName = fstr_Weight;
        }
        else
        {
            if (fstr_Weight == TEXT("Regular"))
            {
                fstr_OutName = fstr_FontStyle;
            }
            else
            {
                fstr_OutName = fstr_Weight + TEXT(" ") + fstr_FontStyle;
            }
        }
    }
}


FString PixImpFont::GetPixFontKey(const FString& fstr_FontName, const FString& fstr_FontFace, const uint32 un_FontSize)
{
    return fstr_FontName + TEXT("_") + fstr_FontFace + TEXT("_") + FString::FromInt(un_FontSize);
}


TSharedPtr<PixFont> PixImpFont::FindFontByKey(const FString& fstr_FontKey)
{
    TSharedPtr<PixFont> sptr_PixFont = nullptr;

    auto psptr_PixFont = map_PixFont_.Find(fstr_FontKey);
    if (psptr_PixFont)
    {
        sptr_PixFont = *psptr_PixFont;
    }
    return sptr_PixFont;
}


TSharedPtr<PixFont> PixImpFont::FindFontByHandle(pixui::uint_ptr h_Font)
{
    TSharedPtr<PixFont> sptr_PixFont = nullptr;
    for (auto font : map_PixFont_)
    {
        if (font.Value.Get() == (PixFont*)h_Font)
        {
            return font.Value;
        }
    }
    return nullptr;
}


std::string& PixImpFont::DefaultFontRef()
{
    static std::string gStrDefaultFont_s;
    return gStrDefaultFont_s;
}


int& PixImpFont::DefaultFontSizeRef()
{
    static int n_DefaultFontSize_s = 16;
    return n_DefaultFontSize_s;
}


TMap<FString, FString>& PixImpFont::FontPaths()
{
    static TMap<FString, FString> map_FontPath_s;
    return map_FontPath_s;
}