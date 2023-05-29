/**************************************************

**** @file:     PixImpImg.h

**** @brief:    pixui Image Brush manager implementation

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once
#include "CoreMinimal.h"

#include "PixImpBase.h"
#include "PixUIExInterface.h"

class PixImgBrush;

class PixImpImg : public PixImpBase
{
    //register imp
    DF_REG_PX_IMP(PixImpImg)

protected:
    PixImpImg();

public:
    virtual ~PixImpImg();

protected:
    /************************************************************************/
    /** PixImpBase implementation */
    virtual void OnStartup() override;
    virtual void OnTick(const float f_DeltaTime) override;
	virtual void OnClear() override;
    virtual void OnShutdown() override;
    /** PixImpBase implementation */
    /************************************************************************/
    
    void ClearAllImg();

public:
    //create brush image by url
    static PixImgBrush* CreatePixImg(const FString& fst_Url, int32 nWinId, const FString& fstrTagId);

    //find image by url
    static TWeakPtr<PixImgBrush> FindPixImg(const FString& fst_Url);

    static TWeakPtr<PixImgBrush> FindPixImgByWin(int32 nWinId, const FString& fstrTagId);

    //find image by PixImgBrush*
    static TWeakPtr<PixImgBrush> FindPixImgByHandle(void* h_img_handle);

    //delete brush image
    static bool RemovePixImg(PixImgBrush* p_ImgBrush);

    //external brush load delegate,for game module to load brush itself
    static void SetExternalBrushLoadDelegate(PFun_PixBrushLoad fun_BrushLoad);

    static TSharedPtr<FSlateBrush> TryLoadExternalBrush(const FString& fstrImagePath);

protected:
    TMap<FString, TSharedPtr<PixImgBrush>>& ImageBrushs() {
        return map_ImgBrushs_;
    }

private:
    //Brush map
    TMap<FString, TSharedPtr<PixImgBrush>> map_ImgBrushs_;


    //external brush Load delegate
    static PFun_PixBrushLoad& ExternalLoad();
};