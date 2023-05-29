/**************************************************

**** @file:     PixImpSlot.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixImpSlot.h"

#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/UserWidget.h"

#include "PixUtil.h"
#include "PixUILog.h"
#include "PixImp/PixImpImg.h"
#include "PixBrush/PixImgBrush.h"
#include "PixBrush/PixMatBrush.h"

#include "PixUIWidget.h"



PixSlot::PixSlot(const FString& fstrPath, const TWeakObjectPtr<UWidget>& weakWidget, const TSharedPtr<FSlateBrush>& slateBrush, int32 nWindId, const FString& fstrTagId, const bool beExternal)
{
	mStrPath = fstrPath;
	mWeakWidget = weakWidget;
    mSlateBrush = slateBrush;
	mIntWinID = nWindId;
	mBeExternal = beExternal;
	mStrTagId = fstrTagId;

	if (mBeExternal && mWeakWidget.IsValid() && !mWeakWidget->IsRooted())
	{
		mWeakWidget->AddToRoot();
		mBeAddToRoot = true;
	}
	else
	{
		mBeAddToRoot = false;
	}
#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixSlot new       %d", ++ResItemCount::PixSlotCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)

}

PixSlot::~PixSlot()
{
	if (mBeExternal && mWeakWidget.IsValid() && mWeakWidget->IsRooted())
	{
		mWeakWidget->RemoveFromRoot();
	}
	else
	{
		if (mBeAddToRoot)
		{
			PxLog_Warning("PixSlot delete not call RemoveFromRoot %s", TCHAR_TO_UTF8(*mStrPath));
		}
	}

	if (mBeExternal && mSlateBrush.IsValid() && mSlateBrush->GetResourceObject() && mSlateBrush->GetResourceObject()->IsRooted())
	{
		mSlateBrush->GetResourceObject()->RemoveFromRoot();
	}

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
	PxLog_Trace("PixSlot delete    %d", --ResItemCount::PixSlotCount());
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
}


UObject* PixSlot::GetInnerObject()
{
    if (mWeakWidget.IsValid())
    {
        return mWeakWidget.Get();
    }

    if (mSlateBrush.IsValid())
    {
        return mSlateBrush->GetResourceObject();
    }

    return nullptr;
}


#define ExternalLoadDelegate ExternalLoad()

PixImpSlot::PixImpSlot()
    : PixImpBase(TEXT("PixImpSlot"))
{

}


PixImpSlot::~PixImpSlot()
{

}


void PixImpSlot::OnStartup()
{
    //do something stuff
}


void PixImpSlot::OnTick(const float f_DeltaTime)
{
    //do something stuff
}

void PixImpSlot::OnClear()
{
	//do something stuff
}


void PixImpSlot::OnShutdown()
{
    ClearAllSlot();
}


void PixImpSlot::ClearAllSlot()
{
    Slots().Empty();
}


TWeakPtr<PixSlot> PixImpSlot::CreatePixSlot(const FString& fstr_Url, int32 winId, const FString& fstrTagId)
{
	if (fstr_Url.IsEmpty())
	{
        return nullptr;
	}

	TSharedPtr<PixSlot> sptrSlot = nullptr;
    //do not found PixImpSlot,need to create one
    if (Get())
    {
        //check external brush load first
        TWeakObjectPtr<UWidget> weakWidgetEx = nullptr;
        TSharedPtr<FSlateBrush> sharedBrush = nullptr;
        if (ExternalLoadDelegate)
        {
        	weakWidgetEx = ExternalLoadDelegate(fstr_Url);
            if (weakWidgetEx.IsValid())
            {
                sptrSlot = MakeShareable(new PixSlot(fstr_Url, weakWidgetEx, sharedBrush, winId, fstrTagId, true));
            }
        }

        if (!weakWidgetEx.IsValid())
        {
            //try to load inside
            UWorld* World = PixUtil::GameWorld();
            if (World)
            {
                FString fstrClassWidgetPath = fstr_Url;
                if (!fstrClassWidgetPath.StartsWith(TEXT("Blueprint'")))
                {
                    fstrClassWidgetPath = TEXT("Blueprint'") + fstrClassWidgetPath;
                }

                if (!fstrClassWidgetPath.EndsWith(TEXT("_C'")))
                {
                    FString fileName = FPaths::GetBaseFilename(fstr_Url);
                    FString fileExternal = TEXT(".") + fileName;
                    if (fstrClassWidgetPath.EndsWith(fileExternal))
                    {
                        fstrClassWidgetPath = fstrClassWidgetPath + TEXT("_C'");
                    }
                    else
                    {
                        fstrClassWidgetPath = fstrClassWidgetPath + TEXT(".") + fileName + TEXT("_C'");
                    }
                    
                }
                //TEXT("Blueprint'/Game/UMG/umg_test.umg_test_C'")
                UClass* widgetClass = LoadClass<UUserWidget>(NULL, *fstrClassWidgetPath);
                if (widgetClass)
                {
                    UUserWidget* pLoadWidget = CreateWidget<UUserWidget>(World, widgetClass);
                    if (pLoadWidget)
                    {
                        sptrSlot = MakeShareable(new PixSlot(fstr_Url, pLoadWidget, sharedBrush, winId, fstrTagId, false));
                    }
                }
            }
        }

        if (sptrSlot.IsValid())
        {
            //is widget
            Get()->Slots().Add(sptrSlot);

            // add to widget
			UPixUIWidget* pWidget = UPixUIWidget::FindPixUIWidgetByID(winId);
			if (pWidget)
			{
				pWidget->AddSlotWidget(sptrSlot->GetWidget());
			}
            else
            {
                PxLog_Error("PixImpSlot::CreatePixSlot error not found window:%d  path:%s  fstrTagId:%S", winId, TCHAR_TO_UTF8(*fstr_Url), TCHAR_TO_UTF8(*fstrTagId));
            }
        }
        else
        {
            //try load brush
            bool bExternal = true;
            sharedBrush = PixImpImg::TryLoadExternalBrush(fstr_Url);
            if (!sharedBrush.IsValid())
            {
                bExternal = false;
				sharedBrush = PixImgBrush::LoadImageBrushFromMaterial(fstr_Url);
				if (!sharedBrush.IsValid())
				{
					sharedBrush = PixMatBrush::LoadSlateBrushFromMaterial(fstr_Url, FVector2D(32, 32));

                    if (sharedBrush.IsValid())
                    {
						UMaterialInstanceDynamic* p_mat_inter = Cast<UMaterialInstanceDynamic>(sharedBrush->GetResourceObject());
						if (p_mat_inter)
						{
							p_mat_inter->AddToRoot();
						}
                    }
				}
            }
			if (sharedBrush.IsValid())
			{
				sptrSlot = MakeShareable(new PixSlot(fstr_Url, weakWidgetEx, sharedBrush, winId, fstrTagId, bExternal));
			}

			if (sptrSlot.IsValid())
			{
				Get()->Slots().Add(sptrSlot);
			}
        }
    }
    else
    {
        PxLog_Error("PixImpSlot do not register,please Register PixImpSlot in PixImpMgr::PixImpStartup");
    }
    return sptrSlot;
}


TSharedPtr<PixSlot> PixImpSlot::FindPixSlotByHandle(void* hSlotHandle)
{
    TSharedPtr<PixSlot> psptr_slot = nullptr;
    if (Get())
    {
        for (auto slotItem : Get()->Slots())
        {
            if (slotItem.Get() == hSlotHandle)
            {
                psptr_slot = slotItem;
                break;
            }
        }
    }
    else
    {
        PxLog_Error("PixImpSlot do not register,please Register PixImpSlot in PixImpMgr::PixImpStartup");
    }
    return psptr_slot;
}

TSharedPtr<PixSlot> PixImpSlot::FindPixSlotByWidget(TWeakObjectPtr<UWidget> weakWidget)
{
	TSharedPtr<PixSlot> psptr_slot = nullptr;
	if (Get())
	{
		for (auto slotItem : Get()->Slots())
		{
			if (slotItem->GetWidget() == weakWidget)
			{
				psptr_slot = slotItem;
				break;
			}
		}
	}
	else
	{
		PxLog_Error("PixImpSlot do not register,please Register PixImpSlot in PixImpMgr::PixImpStartup");
	}
	return psptr_slot;
}


TSharedPtr<PixSlot> PixImpSlot::FindPixSlotByWinIdTagId(int32 winId, const FString& fstrTagId)
{
	TSharedPtr<PixSlot> psptr_slot = nullptr;
	if (Get())
	{
		for (auto slotItem : Get()->Slots())
		{
			if (slotItem->GetWinId() == winId && slotItem->TagId() == fstrTagId)
			{
				psptr_slot = slotItem;
				break;
			}
		}
	}
	else
	{
		PxLog_Error("PixImpSlot do not register,please Register PixImpSlot in PixImpMgr::PixImpStartup");
	}
	return psptr_slot;
}


bool PixImpSlot::RemovePixSlot(PixSlot* pSlot)
{
    if (Get() && pSlot)
    {
        TSharedPtr<PixSlot> sptr_Slot = FindPixSlotByHandle(pSlot);
        if (sptr_Slot.IsValid())
        {
            Get()->Slots().Remove(sptr_Slot);
        }
        else
        {
            PxLog_Error("PixImpSlot::RemovePixSlot error,can not found brush pSlot:%p", pSlot);
        }
    }
    else
    {
        if (!pSlot)
        {
            PxLog_Error("PixImpSlot::RemovePixSlot error,PixSlot was invalid");
        }
        else
        {
            PxLog_Error("PixImpSlot do not register,please Register PixImpSlot in PixImpMgr::PixImpStartup");
        }
    }
    return false;
}


void PixImpSlot::SetExternalSlotLoadDelegate(PFun_PixWidgetLoad fun_BrushLoad)
{
    ExternalLoadDelegate = fun_BrushLoad;
}


PFun_PixWidgetLoad& PixImpSlot::ExternalLoad()
{
    static PFun_PixWidgetLoad fun_ExternalBrushLoad_S = nullptr;
    return fun_ExternalBrushLoad_S;
}