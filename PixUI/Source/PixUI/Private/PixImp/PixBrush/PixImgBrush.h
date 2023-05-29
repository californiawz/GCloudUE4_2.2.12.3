/**************************************************

**** @file:     PixImgBrush.h

**** @brief:    for pixui IPluginImage

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "CoreMinimal.h"

#include "Slate.h"
#include "SlateCore.h"
#include "SlateMaterialBrush.h"
#include "Engine/Texture2D.h"

#include "PixUIDef.h"
#include "PixImp/PixObject.h"

#include "hf_typedef.h"

#include <string>
#include <functional>


class PixImgBrush : public PixObject
{
public:
    //sptr_ImageBrush create by external loaded brush,if sptr_ImageBrush was nullptr will be load by default
    PixImgBrush(const FString& fst_url, int32 nWinId, const FString& fstrTagId, TSharedPtr<FSlateBrush> sptr_SlateBrush = nullptr);
    virtual ~PixImgBrush();

public:
    void Tick(float f_DeltaTime);

    //image url
    const FString& GetUrl() {
        return fstr_Url_;
    }

	const FString& GetTagId() {
		return mStrTagId;
	}

	const int32 GetWinId() {
		return mIntWindId;
	}

	bool IsExternal() {
		return sptr_ExternalBrush_.IsValid();
	}

	bool IsExternalPaperSprite();

    //get slate brush
    TWeakPtr<FSlateBrush> GetImageBrush() {
		return GetResourceBrush();
    }

    //get slice brush
    FSlateBrush* GetImageSliceBrush(const pixui::ImageSlice& sliceImage);

    //get radius brush
	TWeakPtr<FSlateBrush> GetImageRadiusBrush(const pixui::BorderRadiuses& borderRadius, const pixui::size& size_rect,
        const FVector2D& v2d_ImageSize, const FVector2D& v2d_UVoffset, const pixui::BackgroundRepeat em_RepeatMode);

public:
    /************************************************************************************/
    /** IPixUIPlugin implementation */
    virtual bool CreateByData(const uint8* p_Data, const uint32 un_DataSize);
    virtual bool CreateByRawData(const int n_Width, const int n_Height, const int n_ImageFlag, const pixui::EPixelFormat em_PixelFormat, const pixui::uint8* p_RawData, const size_t nDataSize);
    virtual void GetImageSize(pixui::size& size_Image);
    virtual void UpdateByRawData(const pixui::EPixelFormat em_PixelFormat, const pixui::uint8* p_RawData, const size_t nDataSize);

    virtual bool IsExternalImage();
    /** IPixUIPlugin implementation */
    /************************************************************************************/

	bool FlushTexture();

public:
    static UTexture2D* LoadTextureFromGameRes(const FString& fstr_TexturePath);
    static UTexture2D* LoadTextureFromFilePath(const FString& fstr_TexturePath);
    static UTexture2D* LoadTextureFromData(const uint8* p_Data, const int32 n_DataSize);
    static UTexture2D* CreateTexture(const TArray<uint8>& ary_PixelData, int32 n_SizeX, int32 n_SizeY, EPixelFormat em_PixelFormat);
    static UTexture2D* CreateTextureByPixelData(const uint8* p_PixelData, const int32 n_DataSize, const int32 n_SizeX, const int32 n_SizeY, EPixelFormat em_PixelFormat);

    static TSharedPtr<FSlateDynamicImageBrush> LoadImageBrushFromData(const uint8* p_Data, const int32 n_DataSize, const FString& fstr_Url);
    static TSharedPtr<FSlateDynamicImageBrush> LoadImageBrushFromTexture(UTexture2D* p_Texture, const FString& fstr_Url);

    static TSharedPtr<FSlateMaterialBrush> LoadImageBrushFromMaterial(const FString& fst_url);

protected:
    /************************************************************************************/
    //Begin slice brush~

    //get slice key
    FString GetSliceKey(const pixui::ImageSlice& sliceImage);

    //find slice
    TSharedPtr<FSlateDynamicImageBrush> FindSliceImage(const pixui::ImageSlice& sliceImage);
    TSharedPtr<FSlateDynamicImageBrush> FindSliceImage(const FString& fstr_Mark);

    //create slice image
    TSharedPtr<FSlateDynamicImageBrush> CreateSliceImage(const pixui::ImageSlice& sliceImage);

    //End slice brush~
    /************************************************************************************/


    /************************************************************************************/
    //Begin radius brush~

    //get radius key
    FString GetRaidusKey(const pixui::BorderRadiuses& borderRadius, const pixui::size& size_Rect,
        const FVector2D& v2d_ImageSize = FVector2D::ZeroVector, const FVector2D& v2d_UVoffset = FVector2D::ZeroVector,
        const pixui::BackgroundRepeat em_RepeatMode = pixui::background_repeat_repeat);

    //find radius image brush
    TSharedPtr<FSlateMaterialBrush> FindRadiusImage(const pixui::BorderRadiuses& borderRadius, const pixui::size& size_Rect,
        const FVector2D& v2d_ImageSize, const FVector2D& v2d_UVoffset, const pixui::BackgroundRepeat em_RepeatMode);
    TSharedPtr<FSlateMaterialBrush> FindRadiusImage(const FString& fstr_radius);

    //create radius image
    TSharedPtr<FSlateMaterialBrush> CreateRadiusImage(const pixui::BorderRadiuses& borderRadius, const pixui::size& size_Rect,
        const FVector2D& v2d_ImageSize, const FVector2D& v2d_UVoffset, const pixui::BackgroundRepeat em_RepeatMode);

    //End radius brush~
    /************************************************************************************/

    void FreeTexture();

protected:
	TWeakPtr<FSlateBrush> GetResourceBrush()
    {
        //external brush first
        if (sptr_ExternalBrush_.IsValid())
            return sptr_ExternalBrush_;
        if(sptr_ActiveMaterialBrush_.IsValid())
          return sptr_ActiveMaterialBrush_;
        return sptr_Brush_;
    }

private:
    //image url
    FString fstr_Url_;

    FString mStrTagId;

    int32 mIntWindId;

	//UTexture2D
	TWeakObjectPtr<UTexture2D> wptr_texture2d_;

	//image format
	EPixelFormat em_ImgPixelFormat;

    //image original size
    FVector2D size_Image_;

    TSharedPtr<FSlateDynamicImageBrush> sptr_Brush_;

	//save for external Image Brush,shared 
	TSharedPtr<FSlateBrush> sptr_ExternalBrush_;

	TSharedPtr<FSlateMaterialBrush> sptr_ActiveMaterialBrush_;


	//if loaded or not by external delegate
	bool b_ExternalImage_;

    //map for Slice Brush(Maybe multiple)
    TMap<FString, TSharedPtr<FSlateDynamicImageBrush>> map_SliceBrush_;

    //map for Radius Brush(Maybe multiple)
    TMap<FString, TSharedPtr<FSlateMaterialBrush>> map_RadiusBrush_;

	bool b_need_flush_;
};

