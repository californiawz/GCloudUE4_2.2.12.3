/**************************************************

**** @file:     PixImpImg.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixImpImg.h"

#include "PixUILog.h"
#include "PixBrush/PixImgBrush.h"


#define ExternalLoadDelegate ExternalLoad()

PixImpImg::PixImpImg()
    : PixImpBase(TEXT("PixImpImg"))
{

}


PixImpImg::~PixImpImg()
{

}


void PixImpImg::OnStartup()
{

}


void PixImpImg::OnTick(const float f_DeltaTime)
{
    for (auto ImgBrush : ImageBrushs())
    {
        if (ImgBrush.Value.IsValid())
        {
            ImgBrush.Value->Tick(f_DeltaTime);
        }
    }
}

void PixImpImg::OnClear()
{
	//do something stuff
}


void PixImpImg::OnShutdown()
{
    ClearAllImg();
}


void PixImpImg::ClearAllImg()
{
    ImageBrushs().Empty();
}


PixImgBrush* PixImpImg::CreatePixImg(const FString& fstr_Url, int32 nWinId, const FString& fstrTagId)
{
	FString fstr_FixUrl;
	if (fstr_Url.IsEmpty())
	{
		static unsigned int n_index_s = 0;
		//empty url,maybe create by video tag
		fstr_FixUrl = FString::Printf(TEXT("emprty_url_%d"), n_index_s);
		n_index_s++;
	}
	else
	{
		fstr_FixUrl = fstr_Url;
	}

    TWeakPtr<PixImgBrush> wptr_ImgBrush = FindPixImg(fstr_FixUrl);
    if (wptr_ImgBrush.IsValid())
    {
        PxLog_Warning("PixImpImg::CreatePixImg Warning, image:%s already loaded", TCHAR_TO_UTF8(*fstr_FixUrl));
		wptr_ImgBrush.Pin()->AddRef();
        return wptr_ImgBrush.Pin().Get();
    }


	TSharedPtr<PixImgBrush> sptr_ImgBrush = nullptr;
    //do not found PixImpImg,need to create one
    if (Get())
    {
        //check external brush load first
        if (ExternalLoadDelegate)
        {
            auto pBrushEx = ExternalLoadDelegate(fstr_FixUrl);
            if (pBrushEx.IsValid())
            {
                sptr_ImgBrush = MakeShareable(new PixImgBrush(fstr_FixUrl, nWinId, fstrTagId, pBrushEx));
            }
            else
            {
                sptr_ImgBrush = MakeShareable(new PixImgBrush(fstr_FixUrl, nWinId, fstrTagId));
            }
        }
        else
        {
            sptr_ImgBrush = MakeShareable(new PixImgBrush(fstr_FixUrl, nWinId, fstrTagId));
        }
        
        Get()->ImageBrushs().Add(fstr_FixUrl, sptr_ImgBrush);
    }
    else
    {
        PxLog_Error("PixImpImg do not register,please Register PixImpImg in PixImpMgr::PixImpStartup");
    }
    return sptr_ImgBrush.Get();
}


TWeakPtr<PixImgBrush> PixImpImg::FindPixImg(const FString& fst_Url)
{
    if (Get())
    {
        TSharedPtr<PixImgBrush>* psptr_ImgBrush = Get()->ImageBrushs().Find(fst_Url);
        if (psptr_ImgBrush)
            return *psptr_ImgBrush;
    }
    else
    {
        PxLog_Error("PixImpImg do not register,please Register PixImpImg in PixImpMgr::PixImpStartup");
    }
    return nullptr;
}


TWeakPtr<PixImgBrush> PixImpImg::FindPixImgByWin(int32 nWinId, const FString& fstrTagId)
{
    TSharedPtr<PixImgBrush> sptr_ImgBrush = nullptr;
	if (Get())
	{
		for (auto brush : Get()->ImageBrushs())
		{
			if (brush.Value.Get()->GetWinId() == nWinId && brush.Value.Get()->GetTagId() == fstrTagId)
			{
				sptr_ImgBrush = brush.Value;
				break;
			}
		}
	}
	else
	{
		PxLog_Error("PixImpImg do not register,please Register PixImpImg in PixImpMgr::PixImpStartup");
	}
	return sptr_ImgBrush;
}


TWeakPtr<PixImgBrush> PixImpImg::FindPixImgByHandle(void* h_img_handle)
{
    TSharedPtr<PixImgBrush> sptr_ImgBrush = nullptr;
    if (Get())
    {
        for (auto brush : Get()->ImageBrushs())
        {
            if (brush.Value.Get() == h_img_handle)
            {
                sptr_ImgBrush = brush.Value;
                break;
            }
        }
    }
    else
    {
        PxLog_Error("PixImpImg do not register,please Register PixImpImg in PixImpMgr::PixImpStartup");
    }
    return sptr_ImgBrush;
}


bool PixImpImg::RemovePixImg(PixImgBrush* p_ImgBrush)
{
    if (Get() && p_ImgBrush)
    {
		TWeakPtr<PixImgBrush> sptr_ImgBrush = FindPixImgByHandle(p_ImgBrush);
        if (sptr_ImgBrush.IsValid())
        {
            if (sptr_ImgBrush.Pin()->DecRef())
            {
                //reference was <= 0 and remove from map
                Get()->ImageBrushs().Remove(p_ImgBrush->GetUrl());
            }
        }
        else
        {
            PxLog_Error("PixImpImg::RemovePixImg error,can not found brush p_ImgBrush:%p", p_ImgBrush);
        }
    }
    else
    {
        if (!p_ImgBrush)
        {
            PxLog_Error("PixImpImg::RemovePixImg error,pImgBrush was invalid");
        }
        else
        {
            PxLog_Error("PixImpImg do not register,please Register PixImpImg in PixImpMgr::PixImpStartup");
        }
    }
    return false;
}


void PixImpImg::SetExternalBrushLoadDelegate(PFun_PixBrushLoad fun_BrushLoad)
{
    ExternalLoadDelegate = fun_BrushLoad;
}


TSharedPtr<FSlateBrush> PixImpImg::TryLoadExternalBrush(const FString& fstrImagePath)
{
    if (ExternalLoad())
    {
        return ExternalLoad()(fstrImagePath);
    }
    return nullptr;
}


PFun_PixBrushLoad& PixImpImg::ExternalLoad()
{
    static PFun_PixBrushLoad fun_ExternalBrushLoad_S = nullptr;
    return fun_ExternalBrushLoad_S;
}