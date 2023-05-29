/**************************************************

**** @file:     PixImgBrush.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixImgBrush.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "RenderUtils.h"

#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "RHI.h"

#if (defined(DF_SUPPORT_PAPER_SPRITE) && DF_SUPPORT_PAPER_SPRITE)
#include "PaperSprite.h"
#endif


#include "PixUIDef.h"
#include "PixUILog.h"
#include "PixImp/PixImpImg.h"
#include "PixUIBPLibrary.h"
#include "PixUtil.h"

#include "PixImp/PixBrush/PixMatBrush.h"


#include "PixUIProfiler/PxpResCount.h"


//Construct
PixImgBrush::PixImgBrush(const FString& fst_url, int32 nWinId, const FString& fstrTagId, TSharedPtr<FSlateBrush> sptr_SlateBrush /*= nullptr*/)
    : fstr_Url_(fst_url), mStrTagId(fstrTagId), mIntWindId(nWinId), size_Image_(0, 0), sptr_Brush_(nullptr),
    sptr_ExternalBrush_(sptr_SlateBrush)
{
	wptr_texture2d_ = nullptr;
    b_ExternalImage_ = false;

    if (sptr_ExternalBrush_.IsValid())
    {
        //load by external
        size_Image_ = sptr_ExternalBrush_->ImageSize;
        b_ExternalImage_ = true;
    }
    else
    {
        //material://xxx.xxx.xx?tex_xxxx1=/res/a.png&num_xxxx2=1&vec4_xxxx3=(1,2,3,4)&width=200&height=200
        if(fstr_Url_.StartsWith("material://"))
        {
            sptr_ActiveMaterialBrush_ = LoadImageBrushFromMaterial(fstr_Url_);
            if (sptr_ActiveMaterialBrush_.IsValid())
            {
				size_Image_ = sptr_ActiveMaterialBrush_->ImageSize;
				b_ExternalImage_ = true;
            }
        }
        else
        {
			if (fstr_Url_.StartsWith("/"))
			{
				sptr_ActiveMaterialBrush_ = PixMatBrush::LoadSlateBrushFromMaterial(fstr_Url_, FVector2D(32.0f, 32.0f));
				if (sptr_ActiveMaterialBrush_.IsValid())
				{
					UMaterialInstanceDynamic* p_mat_inter = Cast<UMaterialInstanceDynamic>(sptr_ActiveMaterialBrush_->GetResourceObject());
					if (p_mat_inter)
					{
						p_mat_inter->AddToRoot();
					}

					size_Image_ = sptr_ActiveMaterialBrush_->ImageSize;
					b_ExternalImage_ = true;
				}
			}
        }
    }

	b_need_flush_ = false;

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixImgBrush  new     %d      %s", ++ResItemCount::PixImgBrushCount(), TCHAR_TO_UTF8(*fst_url));
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}


//auto release by pixui core
PixImgBrush::~PixImgBrush()
{
    FreeTexture();

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixImgBrush  delete  %d      %s", --ResItemCount::PixImgBrushCount(), TCHAR_TO_UTF8(*fstr_Url_));
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}


void PixImgBrush::Tick(float f_DeltaTime)
{

}

bool PixImgBrush::IsExternalPaperSprite()
{
	if (IsExternal())
	{
#if (defined(DF_SUPPORT_PAPER_SPRITE) && DF_SUPPORT_PAPER_SPRITE)
		TWeakPtr<FSlateBrush> wptr_brush = GetResourceBrush();
		if (wptr_brush.IsValid())
		{
			UPaperSprite* p_sprite = Cast<UPaperSprite>(wptr_brush.Pin()->GetResourceObject());
			if (p_sprite)
			{
				return true;
			}
		}
#endif //(defined(DF_SUPPORT_PAPER_SPRITE) && DF_SUPPORT_PAPER_SPRITE)
	}
	return false;
}

FSlateBrush* PixImgBrush::GetImageSliceBrush(const pixui::ImageSlice& sliceImage)
{
    TSharedPtr<FSlateDynamicImageBrush> sptr_Brush = FindSliceImage(sliceImage);
    if (!sptr_Brush.IsValid())
    {
        sptr_Brush = CreateSliceImage(sliceImage);
    }
    return sptr_Brush.Get();
}


TWeakPtr<FSlateBrush> PixImgBrush::GetImageRadiusBrush(const pixui::BorderRadiuses& borderRadius, const pixui::size& size_rect,
    const FVector2D& v2d_ImageSize, const FVector2D& v2d_UVoffset, const pixui::BackgroundRepeat em_RepeatMode)
{
    if (size_rect.width <= 0 || size_rect.height <= 0)
    {
        //image size was invalid
        PxLog_Error("PixImgBrush::GetImageRadiusBrush image size was invalid w:%f h:%f", size_rect.width, size_rect.height);
        return nullptr;
    }

    TSharedPtr<FSlateMaterialBrush> sptr_Brush = FindRadiusImage(borderRadius, size_rect, v2d_ImageSize, v2d_UVoffset, em_RepeatMode);
    if (!sptr_Brush.IsValid())
    {
        sptr_Brush = CreateRadiusImage(borderRadius, size_rect, v2d_ImageSize, v2d_UVoffset, em_RepeatMode);
    }
    return sptr_Brush;
}


//create image;The data contains the entire file and image header data information
bool PixImgBrush::CreateByData(const uint8* p_Data, const uint32 un_DataSize)
{
    check(IsInGameThread());

    if (!p_Data || un_DataSize == 0)
    {
        PxLog_Error("PixImgBrush::CreateByData Failed to p_Data:%p un_DataSize: %d", p_Data, un_DataSize);
        return false;
    }

    if (sptr_Brush_.IsValid())
    {
        //for safe,brush do not support Created multiple times
        PxLog_Warning("PixImgBrush::CreateByData sptr_Brush_ was created;do not support Created multiple times");
        return false;
    }

    bool b_Ret = false;
    sptr_Brush_ = LoadImageBrushFromData(p_Data, un_DataSize, fstr_Url_);
    if (sptr_Brush_.IsValid())
    {
		wptr_texture2d_ = Cast<UTexture2D>(sptr_Brush_->GetResourceObject());
        size_Image_ = sptr_Brush_->ImageSize;
        b_Ret = true;
    }
    else
    {
        PxLog_Error("PixImgBrush::CreateByData error image path:%s", TCHAR_TO_UTF8(*fstr_Url_));
    }
    return b_Ret;
}


//create image;The data only contains color information
bool PixImgBrush::CreateByRawData(const int n_Width, const int n_Height, const int n_ImageFlag, const pixui::EPixelFormat em_PixelFormat, const pixui::uint8* p_RawData, const size_t nDataSize)
{
    check(IsInGameThread());
    
    if (n_Width <= 0 || n_Height <= 0 || !p_RawData)
    {
        PxLog_Error("CreateByRawData Failed to nWidth:%p nHeight: %d  pRawData:%p", n_Width, n_Height, p_RawData);
        return false;
    }

    if (wptr_texture2d_.IsValid())
    {
        PxLog_Warning("PixImgBrush::CreateByRawData p_Texture2d_ was created;do not support Created multiple times");
        //for safe,p_Texture2d_ do not support Created multiple times
        return false;
    }

    bool b_Ret = false;
	em_ImgPixelFormat = PixUtil::PixUIPixelFormatToUEPixelFormat(em_PixelFormat);
	if(em_ImgPixelFormat == EPixelFormat::PF_Unknown)
	{
		PxLog_Warning("PixImgBrush::CreateByRawData em_PixelFormat: %d is Unsupported Format",em_PixelFormat);
		return false;
	}
	int GpuWidth, GpuHeight, GpuDataSize;
    PixUtil::CalcTextureGpuSize(em_ImgPixelFormat, n_Width, n_Height, GpuWidth, GpuHeight, GpuDataSize);
	if(nDataSize<GpuDataSize)
	{
		PxLog_Warning("PixImgBrush::CreateByRawData has not enough data, format:{%d}, size:{%dx%d}, gpuSize:{%dx%d}, dataSize:{%d}, gpuDataSize:{%d}",
		              em_ImgPixelFormat, n_Width, n_Height, GpuWidth, GpuHeight, nDataSize, GpuDataSize);
		return false;
	}
	wptr_texture2d_ = CreateTextureByPixelData(p_RawData, GpuDataSize, GpuWidth, GpuHeight, em_ImgPixelFormat);
    if (wptr_texture2d_.IsValid())
    {
		wptr_texture2d_->AddToRoot();
        
        sptr_Brush_ = LoadImageBrushFromTexture(wptr_texture2d_.Get(), fstr_Url_);
        if (sptr_Brush_.IsValid())
        {
            b_Ret = true;
        	/* 需要返回图片的原始大小而不是texture的真实大小 */
            // size_Image_ = sptr_Brush_->ImageSize;
        	size_Image_ = FVector2D(n_Width, n_Height);
        }
    }
    return b_Ret;
}


void PixImgBrush::GetImageSize(pixui::size& size_Image)
{
    if (sptr_Brush_.IsValid() || sptr_ExternalBrush_.IsValid() || sptr_ActiveMaterialBrush_.IsValid())
    {
        size_Image.width = size_Image_.X;
        size_Image.height = size_Image_.Y;
    }
}


//The data only contains color information
void PixImgBrush::UpdateByRawData(const pixui::EPixelFormat em_PixelFormat, const pixui::uint8* p_RawData, const size_t nDataSize)
{
    check(IsInGameThread());

    if (!p_RawData || PixUtil::PixUIPixelFormatToUEPixelFormat(em_PixelFormat) != em_ImgPixelFormat)
    {
        PxLog_Error("PixImgBrush::UpdateByRawData Failed pRawData is null or format do not same:%d", em_PixelFormat);
        return;
    }

    if (sptr_Brush_.IsValid())
    {
        //uint32 StartCycles = FPlatformTime::Cycles();
        auto p_Texture = Cast<UTexture2D>(sptr_Brush_->GetResourceObject());
        if (p_Texture)
        {
#if ENGINE_MAJOR_VERSION < 5
			/////////////////////////////////////////////////////////////////////for ue4
			uint8* MipData = (uint8*)(p_Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
			/////////////////////////////////////////////////////////////////////for ue4
#else
			/////////////////////////////////////////////////////////////////////for ue5
			uint8* MipData = (uint8*)(p_Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
			/////////////////////////////////////////////////////////////////////for ue5
#endif  //ENGINE_MAJOR_VERSION < 5

            FMemory::Memcpy(MipData, p_RawData, nDataSize);

#if ENGINE_MAJOR_VERSION < 5
			/////////////////////////////////////////////////////////////////////for ue4
			p_Texture->PlatformData->Mips[0].BulkData.Unlock();
			/////////////////////////////////////////////////////////////////////for ue4
#else
			/////////////////////////////////////////////////////////////////////for ue5
			p_Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
			/////////////////////////////////////////////////////////////////////for ue5
#endif  //ENGINE_MAJOR_VERSION < 5

			b_need_flush_ = true;
			//p_Texture->UpdateResource();
        }

        //uint32 EndCycles = FPlatformTime::Cycles();
        //UE_LOG(PixUI_Module, Log, TEXT("PixImgBrush::UpdateByRawData cost time:%fms"), FPlatformTime::ToMilliseconds(EndCycles - StartCycles));
    }
}


bool PixImgBrush::IsExternalImage()
{
    return b_ExternalImage_;
}


bool PixImgBrush::FlushTexture()
{
	bool b_ret = false;
	if (b_need_flush_)
	{
		if (sptr_Brush_.IsValid())
		{
			auto p_Texture = Cast<UTexture2D>(sptr_Brush_->GetResourceObject());
			if (p_Texture)
			{
				p_Texture->UpdateResource();
			}
		}
		b_need_flush_ = false;
	}
	return b_ret;
}

//hpjy  资源flush宏，用于在同步资源加载时如果出现触发异步队列加载时的超时不上报告警信息
#ifndef ALLOW_FLUSHING
#define ALLOW_FLUSHING
#endif

UTexture2D* PixImgBrush::LoadTextureFromGameRes(const FString& fstr_TexturePath)
{
	ALLOW_FLUSHING
    return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(fstr_TexturePath)));
}


UTexture2D* PixImgBrush::LoadTextureFromFilePath(const FString& fstr_TexturePath)
{
    UTexture2D* p_Texture2D = nullptr;

    if (!FPaths::FileExists(fstr_TexturePath))
    {
        PxLog_Error("LoadImageFromFilePath File not found: %s", TCHAR_TO_UTF8(*fstr_TexturePath));
        return p_Texture2D;
    }

    // Load the compressed byte data from the file
    TArray<uint8> ary_FileData;
    if (!FFileHelper::LoadFileToArray(ary_FileData, *fstr_TexturePath))
    {
        PxLog_Error("LoadImageFromFilePath Failed to load file: %s", TCHAR_TO_UTF8(*fstr_TexturePath));
        return p_Texture2D;
    }

    return LoadTextureFromData(ary_FileData.GetData(), ary_FileData.Num());
}


UTexture2D* PixImgBrush::LoadTextureFromData(const uint8* p_Data, const int32 n_DataSize)
{
    if (p_Data == nullptr || n_DataSize <= 0)
    {
        PxLog_Error("LoadImageFromData Failed to load Data error p_Data:%p n_DataSize:%d", p_Data, n_DataSize);
        return nullptr;
    }

    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));

    // Detect the image type using the ImageWrapper module
    EImageFormat em_ImageFormat = ImageWrapperModule.DetectImageFormat(p_Data, n_DataSize);
    if (em_ImageFormat == EImageFormat::Invalid)
    {
        PxLog_Error("LoadImageFromData Failed image format error");
        return nullptr;
    }

    // Create an image wrapper for the detected image format
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(em_ImageFormat);
    if (!ImageWrapper.IsValid())
    {
        PxLog_Error("LoadImageFromData Failed to create image CreateImageWrapper ");
        return nullptr;
    }

    // Decompress the image data

#if ENGINE_MAJOR_VERSION < 5

	/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION >= 25
	TArray<uint8> ary_RawData;
	ImageWrapper->SetCompressed(p_Data, n_DataSize);

	if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, ary_RawData))
	{
		PxLog_Error("LoadImageFromData Failed to decompress image RawData");
		return nullptr;
}
	//ary_RawData was temp array,will be auto release end of return
	return CreateTexture(ary_RawData, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), EPixelFormat::PF_B8G8R8A8);
#else
	const TArray<uint8>* ary_RawData = nullptr;
	ImageWrapper->SetCompressed(p_Data, n_DataSize);

	if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, ary_RawData))
	{
		PxLog_Error("LoadImageFromData Failed to decompress image RawData");
		return nullptr;
	}
	//ary_RawData was temp array,will be auto release end of return
	check(ary_RawData != nullptr);
	return CreateTexture(*ary_RawData, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), EPixelFormat::PF_B8G8R8A8);
#endif //ENGINE_MINOR_VERSION >= 25
	/////////////////////////////////////////////////////////////////////for ue4
#else
	/////////////////////////////////////////////////////////////////////for ue5
	TArray<uint8> ary_RawData;
	ImageWrapper->SetCompressed(p_Data, n_DataSize);

	if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, ary_RawData))
	{
		PxLog_Error("LoadImageFromData Failed to decompress image RawData");
		return nullptr;
	}
	//ary_RawData was temp array,will be auto release end of return
	return CreateTexture(ary_RawData, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), EPixelFormat::PF_B8G8R8A8);
	/////////////////////////////////////////////////////////////////////for ue5
#endif  //ENGINE_MAJOR_VERSION < 5
}


UTexture2D* PixImgBrush::CreateTexture(const TArray<uint8>& ary_PixelData, int32 n_SizeX, int32 n_SizeY, EPixelFormat em_PixelFormat)
{
    return CreateTextureByPixelData(ary_PixelData.GetData(), ary_PixelData.Num(), n_SizeX, n_SizeY, em_PixelFormat);
}


UTexture2D* PixImgBrush::CreateTextureByPixelData(const uint8* p_PixelData, const int32 n_DataSize, const int32 n_SizeX, const int32 n_SizeY, EPixelFormat em_PixelFormat)
{
    // Shamelessly copied from UTexture2D::CreateTransient with a few modifications
    if (!p_PixelData || n_DataSize <= 0)
    {
        PxLog_Error("CreateTextureByPixelData Invalid parameters pPixelData:%#x  nDataSize:%d", p_PixelData, n_DataSize);
        return nullptr;
    }

    // Shamelessly copied from UTexture2D::CreateTransient with a few modifications
    if (n_SizeX <= 0 || n_SizeY <= 0 ||
        (n_SizeX % GPixelFormats[em_PixelFormat].BlockSizeX) != 0 ||
        (n_SizeY % GPixelFormats[em_PixelFormat].BlockSizeY) != 0)
    {
        PxLog_Error("PixImgBrush::CreateTexture Invalid size or is not BlockSize; n_SizeX:%d n_SizeY:%d em_PixelFormat:%d BlockSizeX:%d BlockSizeY:%d",
            n_SizeX, n_SizeY, em_PixelFormat, GPixelFormats[em_PixelFormat].BlockSizeX, GPixelFormats[em_PixelFormat].BlockSizeY);
        return nullptr;
    }

    UTexture2D* p_NewTexture = UTexture2D::CreateTransient(n_SizeX, n_SizeY, em_PixelFormat);

    check(p_NewTexture != nullptr);

#if ENGINE_MAJOR_VERSION < 5
	/////////////////////////////////////////////////////////////////////for ue4
	uint8* p_MipData = (uint8*)(p_NewTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	/////////////////////////////////////////////////////////////////////for ue4
#else
	/////////////////////////////////////////////////////////////////////for ue5
	uint8* p_MipData = (uint8*)(p_NewTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	/////////////////////////////////////////////////////////////////////for ue5
#endif  //ENGINE_MAJOR_VERSION < 5

    //copy data from texture2d
    FMemory::Memcpy(p_MipData, p_PixelData, n_DataSize);

#if ENGINE_MAJOR_VERSION < 5
	/////////////////////////////////////////////////////////////////////for ue4
	p_NewTexture->PlatformData->Mips[0].BulkData.Unlock();
	/////////////////////////////////////////////////////////////////////for ue4
#else
	/////////////////////////////////////////////////////////////////////for ue5
	p_NewTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
	/////////////////////////////////////////////////////////////////////for ue5
#endif  //ENGINE_MAJOR_VERSION < 5

    p_NewTexture->UpdateResource();
    return p_NewTexture;
}


TSharedPtr<FSlateDynamicImageBrush> PixImgBrush::LoadImageBrushFromData(const uint8* p_Data, const int32 n_DataSize, const FString& fstr_Url)
{
    if (p_Data == nullptr || n_DataSize <= 0)
    {
        PxLog_Error("LoadImageBrushFromData Failed to load Data error p_Data:%p n_DataSize:%d", p_Data, n_DataSize);
        return nullptr;
    }

    TSharedPtr<FSlateDynamicImageBrush> sptr_SlateBrush = nullptr;

    UTexture2D* p_Texutre = LoadTextureFromData(p_Data, n_DataSize);
    if (p_Texutre)
    {
        p_Texutre->AddToRoot();
        sptr_SlateBrush = LoadImageBrushFromTexture(p_Texutre, fstr_Url);
        if (!sptr_SlateBrush.IsValid())
        {
            p_Texutre->RemoveFromRoot();
        }
    }
    return sptr_SlateBrush;
}


TSharedPtr<FSlateDynamicImageBrush> PixImgBrush::LoadImageBrushFromTexture(UTexture2D* p_Texture, const FString& fstr_Url)
{
    TSharedPtr<FSlateDynamicImageBrush> sptr_SlateBrush = nullptr;
    if (p_Texture && p_Texture->IsRooted())
    {
        //pTexture must be add to root
        //the URL of Base64 will exceed the length limit of FName(1024),So we hash url
        sptr_SlateBrush = MakeShareable(new FSlateDynamicImageBrush(p_Texture, FVector2D(p_Texture->GetSizeX(), p_Texture->GetSizeY()), FName(*FMD5::HashAnsiString(*fstr_Url))));
    }
    else
    {
        PxLog_Error("LoadImageBrushFromTexture error texture must valid and add to root");
    }
    return sptr_SlateBrush;
}

TSharedPtr<FSlateMaterialBrush> PixImgBrush::LoadImageBrushFromMaterial(const FString& fst_url)
{
    UMaterialInterface* PixMaterial;
    UMaterialInstanceDynamic* ActiveMaterial;
    FVector2D image_size(32,32);
    int prefix_Len=10;
    FString args_url;
    FString material_url=fst_url.Mid(prefix_Len+1,fst_url.Find("?",ESearchCase::IgnoreCase,ESearchDir::FromStart)-1-prefix_Len);
    PixMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), NULL, *material_url));
    TSharedPtr<FSlateMaterialBrush> sptr_SlateMatBrush = nullptr;
    if(PixMaterial)
    {
        ActiveMaterial = UMaterialInstanceDynamic::Create(PixMaterial, nullptr);
        ActiveMaterial->AddToRoot();
    }else
    {
        PxLog_Warning("LoadImageBrushFromMaterial error: The material of path was not found");
        return nullptr;
    }
    args_url=fst_url.RightChop(fst_url.Find("?",ESearchCase::IgnoreCase,ESearchDir::FromStart)+1);
    TArray<FString> material_argv;
    args_url.ParseIntoArray(material_argv, TEXT("&"), true);
    TMap<FString,FString> material_map;
    for (auto arg:material_argv)
    {
        TArray<FString> temp_array;
        FString arg_name;
        FString arg_value;
        if(arg.StartsWith("width="))//width
        {
            arg=arg.RightChop(6);
            image_size.X= FCString::Atof(*arg);
        }
        else if(arg.StartsWith("height="))//height
        {
            arg=arg.RightChop(7);
            image_size.Y=FCString::Atof(*arg);
        }
        else if(arg.StartsWith("tex_"))//Texture info: tex_name=Texture-Path
        {
            arg=arg.RightChop(4);
            arg.ParseIntoArray(temp_array, TEXT("="), true);
            arg_name=temp_array[0];
            arg_value=temp_array[1];
            UTexture2D* p_Texutre=LoadTextureFromGameRes(arg_value);
            if (p_Texutre)
            {
                ActiveMaterial->SetTextureParameterValue(FName(*arg_name), p_Texutre);
                continue;
            }
            p_Texutre=LoadTextureFromFilePath(arg_value);
            if (p_Texutre)
            {
                ActiveMaterial->SetTextureParameterValue(FName(*arg_name), p_Texutre);
                continue;
            }
            FString fstr_game_file_path = FPaths::ProjectContentDir() + arg_value;
            p_Texutre=LoadTextureFromFilePath(fstr_game_file_path);
            if (p_Texutre)
            {
                ActiveMaterial->SetTextureParameterValue(FName(*arg_name), p_Texutre);
                continue;
            }
            PxLog_Warning("LoadImageBrushFromMaterial error: The Texutre(%s=%s) was not found",*arg_name,*arg_value);
        }else if(arg.StartsWith("num_"))//num info: num_name=a
        {
            arg=arg.RightChop(4);
            arg.ParseIntoArray(temp_array, TEXT("="), true);
            arg_name=temp_array[0];
            arg_value=temp_array[1];
            float arg_float_value=FCString::Atof(*arg_value);
            ActiveMaterial->SetScalarParameterValue(FName(*arg_name), arg_float_value);
        }else if(arg.StartsWith("vec4_"))//vec4 info: vec4_name=(a,b,c,d)
        {
            arg=arg.RightChop(5);
            arg.ParseIntoArray(temp_array, TEXT("="), true);
            arg_name=temp_array[0];
            arg_value=temp_array[1];
            int arg_value_len=arg_value.Len();
            //check format
            if(arg_value[0]!='['||arg_value[arg_value_len-1]!=']')
            {
                PxLog_Warning("LoadImageBrushFromMaterial error: The vec4(%s=%s) have the wrong format",*arg_name,*arg_value);
                continue;
            }
            arg_value=arg_value.RightChop(1).LeftChop(1);
            arg_value.ParseIntoArray(temp_array, TEXT(","), true);
            if(temp_array.Num()!=4)
            {
                PxLog_Warning("LoadImageBrushFromMaterial error: The vec4(%s=%s) have the wrong format",*arg_name,*arg_value);
                continue;
            }
            FLinearColor arg_vector_value(FCString::Atof(*temp_array[0]),FCString::Atof(*temp_array[1]),
                                            FCString::Atof(*temp_array[2]),FCString::Atof(*temp_array[3]));
            ActiveMaterial->SetVectorParameterValue(FName(*arg_name), arg_vector_value);
        }
    }
    TSharedPtr<FSlateMaterialBrush> ActiveMaterialBrush = MakeShareable(new FSlateMaterialBrush(*ActiveMaterial, image_size));
    return ActiveMaterialBrush;
}



FString PixImgBrush::GetSliceKey(const pixui::ImageSlice& sliceImage)
{
    return FString::Printf(TEXT("%d_%d_%d_%d_%d_%d"),sliceImage.slice_top_x,sliceImage.slice_top_y,
        sliceImage.slice_bottom_x,sliceImage.slice_bottom_y, (int32)sliceImage.model,(int32)sliceImage.repeat);
}


TSharedPtr<FSlateDynamicImageBrush> PixImgBrush::FindSliceImage(const pixui::ImageSlice& sliceImage)
{
    return FindSliceImage(GetSliceKey(sliceImage));
}


TSharedPtr<FSlateDynamicImageBrush> PixImgBrush::FindSliceImage(const FString& fstr_Mark)
{
    auto pp_MapBrush = map_SliceBrush_.Find(fstr_Mark);
    TSharedPtr<FSlateDynamicImageBrush> sptr_SlateBrush = pp_MapBrush ? *pp_MapBrush : nullptr;
    return sptr_SlateBrush;
}


TSharedPtr<FSlateDynamicImageBrush> PixImgBrush::CreateSliceImage(const pixui::ImageSlice& sliceImage)
{
    TSharedPtr<FSlateDynamicImageBrush> sptr_SlateBrush = nullptr;
    
	TWeakPtr<FSlateBrush> wptr_slate_brush = GetResourceBrush();
    if (wptr_slate_brush.IsValid())
    {
        UTexture2D* p_Texture = Cast<UTexture2D>(wptr_slate_brush.Pin()->GetResourceObject());
#if (defined(DF_SUPPORT_PAPER_SPRITE) && DF_SUPPORT_PAPER_SPRITE)
		if (!p_Texture)
		{
			UPaperSprite* p_sprite = Cast<UPaperSprite>(wptr_slate_brush.Pin()->GetResourceObject());
			if (p_sprite)
			{
				p_Texture = p_sprite->GetBakedTexture();
			}
		}
#endif //(defined(DF_SUPPORT_PAPER_SPRITE) && DF_SUPPORT_PAPER_SPRITE)
        if (p_Texture)
        {
            sptr_SlateBrush = LoadImageBrushFromTexture(p_Texture, fstr_Url_);
        }
        else
        {
            //try to load by name
            sptr_SlateBrush = MakeShareable(new FSlateDynamicImageBrush(*fstr_Url_, wptr_slate_brush.Pin()->ImageSize));
        }

        if (sptr_SlateBrush.IsValid())
        {
            if (sliceImage.repeat == pixui::image_stretch)
            {
                sptr_SlateBrush->DrawAs = ESlateBrushDrawType::Box;
            }
            else
            {
                sptr_SlateBrush->DrawAs = ESlateBrushDrawType::Border;
            }

            sptr_SlateBrush->Margin.Top = (float)sliceImage.slice_top_y * 1.0f / (float)wptr_slate_brush.Pin()->ImageSize.Y;
            sptr_SlateBrush->Margin.Bottom = (float)sliceImage.slice_bottom_y * 1.0f / (float)wptr_slate_brush.Pin()->ImageSize.Y;
            sptr_SlateBrush->Margin.Left = (float)sliceImage.slice_top_x * 1.0f / (float)wptr_slate_brush.Pin()->ImageSize.X;
            sptr_SlateBrush->Margin.Right = (float)sliceImage.slice_top_y * 1.0f / (float)wptr_slate_brush.Pin()->ImageSize.X;

            map_SliceBrush_.Add(GetSliceKey(sliceImage), sptr_SlateBrush);
        }
        else
        {
            PxLog_Error("CreateSliceImage error texture must valid or brush was create by data");
        }
    }
    return sptr_SlateBrush;
}


FString PixImgBrush::GetRaidusKey(const pixui::BorderRadiuses& borderRadius, const pixui::size& size_Rect,
    const FVector2D& v2d_ImageSize /*= FVector2D::ZeroVector*/, const FVector2D& v2d_UVoffset /*= FVector2D::ZeroVector*/,
    const pixui::BackgroundRepeat em_RepeatMode /*= pixui::BackgroundRepeat_no_repeat*/)
{
    return FString::Printf(TEXT("%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%.3f_%d"),
        borderRadius.topLeftX / size_Rect.width, borderRadius.topLeftY / size_Rect.height,
        borderRadius.topRightX / size_Rect.width, borderRadius.topRightY / size_Rect.height,
        borderRadius.bottomLeftX / size_Rect.width, borderRadius.bottomLeftY / size_Rect.height,
        borderRadius.bottomRightX / size_Rect.width, borderRadius.bottomRightY / size_Rect.height,
        v2d_ImageSize.X, v2d_ImageSize.Y, v2d_UVoffset.X, v2d_UVoffset.Y, (int32)em_RepeatMode);
}


TSharedPtr<FSlateMaterialBrush> PixImgBrush::FindRadiusImage(const pixui::BorderRadiuses& borderRadius, const pixui::size& size_Rect,
    const FVector2D& v2d_ImageSize, const FVector2D& v2d_UVoffset, const pixui::BackgroundRepeat em_RepeatMode)
{
    return FindRadiusImage(GetRaidusKey(borderRadius, size_Rect, v2d_ImageSize, v2d_UVoffset, em_RepeatMode));
}


TSharedPtr<FSlateMaterialBrush> PixImgBrush::FindRadiusImage(const FString& fstr_radius)
{
    auto pp_MapBrush = map_RadiusBrush_.Find(fstr_radius);
    TSharedPtr<FSlateMaterialBrush> sptr_SlateBrush = pp_MapBrush ? *pp_MapBrush : nullptr;
    return sptr_SlateBrush;
}


TSharedPtr<FSlateMaterialBrush> PixImgBrush::CreateRadiusImage(const pixui::BorderRadiuses& borderRadius, const pixui::size& size_Rect,
    const FVector2D& v2d_ImageSize, const FVector2D& v2d_UVoffset, const pixui::BackgroundRepeat em_RepeatMode)
{
	ALLOW_FLUSHING
    TSharedPtr<FSlateMaterialBrush> sptr_SlateMatBrush = nullptr;

	TWeakPtr<FSlateBrush> wptr_SlateBrush = GetResourceBrush();
    if (wptr_SlateBrush.IsValid())
    {
        UTexture2D* p_Texture = Cast<UTexture2D>(wptr_SlateBrush.Pin()->GetResourceObject());
#if (defined(DF_SUPPORT_PAPER_SPRITE) && DF_SUPPORT_PAPER_SPRITE)
		if (!p_Texture)
		{
			UPaperSprite* p_sprite = Cast<UPaperSprite>(wptr_SlateBrush.Pin()->GetResourceObject());
			if (p_sprite)
			{
				p_Texture = p_sprite->GetBakedTexture();
			}
		}
#endif //(defined(DF_SUPPORT_PAPER_SPRITE) && DF_SUPPORT_PAPER_SPRITE)
        UMaterialInstanceDynamic* p_MatInter = nullptr;

        FString fstr_MatPath = UPixUIBPLibrary::PixUI_GetMatRootPath() + DF_MAT_IMG_RADIUS_CORNER_PATH;
        int n_MatType = 1;

        if (borderRadius.topLeftX == borderRadius.topRightX && borderRadius.topRightX == borderRadius.bottomLeftX && 
            borderRadius.topLeftX == borderRadius.bottomRightX && borderRadius.topLeftY == borderRadius.topRightY && 
            borderRadius.topRightY == borderRadius.bottomLeftY && borderRadius.topLeftY == borderRadius.bottomRightY &&
            borderRadius.topLeftX == size_Rect.width / 2.0f && borderRadius.topLeftY == size_Rect.height / 2.0f)
        {
            fstr_MatPath = UPixUIBPLibrary::PixUI_GetMatRootPath() + DF_MAT_IMG_RADIUS_PATH;
            n_MatType = 0;
        }

        UMaterialInterface* p_MatTemp = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), NULL, *fstr_MatPath));
        if (p_MatTemp)
        {
            p_MatInter = UMaterialInstanceDynamic::Create(p_MatTemp, nullptr);
            p_MatInter->AddToRoot();
            sptr_SlateMatBrush = MakeShareable(new FSlateMaterialBrush(*p_MatInter, wptr_SlateBrush.Pin()->ImageSize));

            p_MatInter->SetTextureParameterValue("texture", p_Texture);

            p_MatInter->SetVectorParameterValue("imageuv",FLinearColor(v2d_ImageSize.X, v2d_ImageSize.Y, v2d_UVoffset.X, v2d_UVoffset.Y));
            p_MatInter->SetScalarParameterValue("x_repeat", (em_RepeatMode == pixui::background_repeat_repeat || em_RepeatMode == pixui::background_repeat_repeat_x) ? 1.0f : 0.0f);
            p_MatInter->SetScalarParameterValue("y_repeat", (em_RepeatMode == pixui::background_repeat_repeat || em_RepeatMode == pixui::background_repeat_repeat_y) ? 1.0f : 0.0f);

            if (n_MatType == 0)
            {
                p_MatInter->SetScalarParameterValue("radius", 0.5f);
            }
            else
            {
                p_MatInter->SetScalarParameterValue("radius_top_left_x", borderRadius.topLeftX / size_Rect.width);
                p_MatInter->SetScalarParameterValue("radius_top_left_y", borderRadius.topLeftY / size_Rect.height);

                p_MatInter->SetScalarParameterValue("radius_top_right_x", borderRadius.topRightX / size_Rect.width);
                p_MatInter->SetScalarParameterValue("radius_top_right_y", borderRadius.topRightY / size_Rect.height);

                p_MatInter->SetScalarParameterValue("radius_bottom_left_x", borderRadius.bottomLeftX / size_Rect.width);
                p_MatInter->SetScalarParameterValue("radius_bottom_left_y", borderRadius.bottomLeftY / size_Rect.height);

                p_MatInter->SetScalarParameterValue("radius_bottom_right_x", borderRadius.bottomRightX / size_Rect.width);
                p_MatInter->SetScalarParameterValue("radius_bottom_right_y", borderRadius.bottomRightY / size_Rect.height);
            }
        }
        else
        {
            PxLog_Error("PixImgBrush CreateRadiusImage error const not load mat by path:%s", TCHAR_TO_UTF8(*fstr_MatPath));
        }

        //
        if (sptr_SlateMatBrush.IsValid())
        {
            map_RadiusBrush_.Add(GetRaidusKey(borderRadius, size_Rect, v2d_ImageSize, v2d_UVoffset, em_RepeatMode), sptr_SlateMatBrush);
        }
    }
    else
    {
        PxLog_Error("CreateRadiusImage error texture must valid or brush was create by data");
    }
    return sptr_SlateMatBrush;
}


void PixImgBrush::FreeTexture()
{
    map_SliceBrush_.Empty();

    for (auto brush : map_RadiusBrush_)
    {
        if (brush.Value.IsValid() && brush.Value->GetResourceObject())
        {
            brush.Value->GetResourceObject()->RemoveFromRoot();
        }
    }

    map_RadiusBrush_.Empty();


    if (wptr_texture2d_.IsValid())
    {
        //free native texture resource
		wptr_texture2d_->ReleaseResource();

        //
		wptr_texture2d_->RemoveFromRoot();
		wptr_texture2d_ = nullptr;
    }

    if (sptr_ActiveMaterialBrush_.IsValid())
    {
        if (sptr_ActiveMaterialBrush_->GetResourceObject() && sptr_ActiveMaterialBrush_->GetResourceObject()->IsRooted())
        {
            sptr_ActiveMaterialBrush_->GetResourceObject()->RemoveFromRoot();
        }
        sptr_ActiveMaterialBrush_ = nullptr;
    }

    if (sptr_Brush_.IsValid())
    {
        sptr_Brush_->ReleaseResource();
    }

    sptr_Brush_ = nullptr;
    sptr_ExternalBrush_ = nullptr;
}