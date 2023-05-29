/**************************************************

**** @file:     PixImpFont.h

**** @brief:    pixui font manager implementation

**** @author:   tianzelei

**** @date:     2020/12/11

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "CoreMinimal.h"
#include "Engine/Font.h"
#include "Engine/FontFace.h"

#include "PixImpBase.h"
#include "PixObject.h"
#include "PixUILog.h"



#include <string>

#include "hf_typedef.h"


//PixFont object
class PixFont : public PixObject
{
public:
	PixFont();

	~PixFont();

	//slate font
	TSharedPtr<FSlateFontInfo>  sptr_SlatFont_;

	//UFont object
	TWeakObjectPtr<UFont>       wptr_FontObject_;
};

class PixImpFont : public PixImpBase
{
    //register imp
    DF_REG_PX_IMP(PixImpFont)

protected:
    PixImpFont();

public:
    virtual ~PixImpFont();

protected:
    /************************************************************************/
    /** PixImpBase implementation */
    virtual void OnStartup() override;
    virtual void OnTick(const float f_DeltaTime) override;
	virtual void OnClear() override;
    virtual void OnShutdown() override;
    /** PixImpBase implementation */
    /************************************************************************/

public:
    //pixui core font create
    static pixui::uint_ptr CreateFont(
        const char*             pszFontName,
        const int               nSize,
        const int               nWeight,
        const unsigned int      unDecoration,
        const pixui::font_style emItalic,
        pixui::FontMetrics*    pFontMetrics);

    //pixui core font register
    static bool RegisterFont(
        const char* pszFileUrl,
        const char* pszFontName,
        const char* pszWeight,
        const char* pszFontStyle,
        void* pContext,
        void(*PfunCallBack)(void* pContext, bool bSucess));

    //pixui core font delete
    static bool DeleteFont(pixui::uint_ptr hFont);

    //get slate font by handle
    static TWeakPtr<PixFont> GetSlateFont(pixui::uint_ptr h_Font);

    //font path manager
    static void AddFontPath(const FString& fstr_FontName, const FString& fstr_FontPath);
    static void RemoveFontPath(const FString& fstr_FontName);

    static void SetDefaultFontSize(int32 n_FontSize);
    static int32 GetDefaultFontSize();

    static const char* GetDefaultFont();
    static void SetDefaultFont(const FString& fstr_FontName);

    static bool GetFontPath(const FString& fstr_FontName, FString& fst_OutPath);

protected:
    //make font type face name,such as: Thin/Regular/Bold Italic
    static void MakeFontTypeFaceName(int nWeight, const FString& fstr_FontStyle, FString& fstr_OutName);
    static void MakeFontTypeFaceName(const FString& fstr_Weight, const FString& fstr_FontStyle, FString& fstr_OutName);

    static FString GetPixFontKey(const FString& fstr_FontName, const FString& fstr_FontFace, const uint32 un_FontSize);

protected:
    //find PixFont
    TSharedPtr<PixFont> FindFontByKey(const FString& fstr_FontKey);
    TSharedPtr<PixFont> FindFontByHandle(pixui::uint_ptr h_Font);

private:
    //PixFont map
    TMap<FString, TSharedPtr<PixFont>> map_PixFont_;

private:
    static std::string& DefaultFontRef();
    static int&     DefaultFontSizeRef();
    static TMap<FString, FString>& FontPaths();
};