/**************************************************

**** @file:     PixImpSlot.h

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

#include "PixUIDef.h"
#include "PixUILog.h"

#if DF_PIXUI_PROFILER
#include "PixUIProfiler/PxpResCount.h"
#endif //DF_PIXUI_PROFILER

class PixImgBrush;

class PixSlot
{
public:
    PixSlot(const FString& fstrPath, const TWeakObjectPtr<UWidget>& weakWidget, const TSharedPtr<FSlateBrush>& slateBrush, int32 nWindId, const FString& fstrTagId, const bool beExternal);
    ~PixSlot();

public:
    UObject* GetInnerObject();
    const TWeakObjectPtr<UWidget>& GetWidget()
    {
        return mWeakWidget;
    }
    const TSharedPtr<FSlateBrush>& GetBrush()
    {
        return mSlateBrush;
    }
    int32 GetWinId()
    {
        return mIntWinID;
    }
    bool IsWidget()
    {
        return mWeakWidget.IsValid();
    }
    bool IsBrush()
    {
        return mSlateBrush.IsValid();
    }

    const FString& TagId()
    {
        return mStrTagId;
    }

private:
    TWeakObjectPtr<UWidget> mWeakWidget;
    TSharedPtr<FSlateBrush> mSlateBrush;

    FString mStrPath;
    FString mStrTagId;
    int32 mIntWinID;
    bool mBeExternal;

    bool mBeAddToRoot;
};

class PixImpSlot : public PixImpBase
{
    //register imp
    DF_REG_PX_IMP(PixImpSlot)

protected:
    PixImpSlot();

public:
    virtual ~PixImpSlot();

protected:
    /************************************************************************/
    /** PixImpBase implementation */
    virtual void OnStartup() override;
    virtual void OnTick(const float f_DeltaTime) override;
	virtual void OnClear() override;
    virtual void OnShutdown() override;
    /** PixImpBase implementation */
    /************************************************************************/
    
    void ClearAllSlot();

public:
    //create brush image by url
    static TWeakPtr<PixSlot> CreatePixSlot(const FString& fst_Url, int32 winId, const FString& fstrTagId);

    //find slot by PixImgBrush*
    static TSharedPtr<PixSlot> FindPixSlotByHandle(void* hSlotHandle);

    static TSharedPtr<PixSlot> FindPixSlotByWidget(TWeakObjectPtr<UWidget> weakWidget);

    static TSharedPtr<PixSlot> FindPixSlotByWinIdTagId(int32 winId, const FString& fstrTagId);

    //delete brush image
    static bool RemovePixSlot(PixSlot* pSlot);

    //external brush load delegate,for game module to load brush itself
    static void SetExternalSlotLoadDelegate(PFun_PixWidgetLoad fun_BrushLoad);


protected:
    TArray<TSharedPtr<PixSlot>>& Slots() {
        return mapSlot;
    }

private:
    //slot map
    TArray<TSharedPtr<PixSlot>> mapSlot;


    //external brush Load delegate
    static PFun_PixWidgetLoad& ExternalLoad();
};