/**************************************************

**** @file:     PixImpMat.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixImpMat.h"

#include "PixBrush/PixMatBrush.h"

#include "PixUILog.h"
#include "px_plugindef.h"

#include "PixUIDef.h"



PixImpMat::PixImpMat()
    : PixImpBase(TEXT("PixImpMat"))
{

}


PixImpMat::~PixImpMat()
{

}


void PixImpMat::OnStartup()
{

}


void PixImpMat::OnClear()
{
	//do something stuff
	AllClear();
}


void PixImpMat::OnTick(const float f_DeltaTime)
{
	//PxLog_Trace("PixImpMat::OnTick brushs number:%04d", Brushs().Num());
}


void PixImpMat::OnShutdown()
{
	AllClear();
}


void PixImpMat::PutMatBrushToFreePool(TSharedPtr<PixMatBrush>& sptr_mat_brush)
{
	if (sptr_mat_brush.IsValid())
	{
		EPxMatBrushType e_mat_brush_type = sptr_mat_brush->BrushType();
		ary_free_mat_brush_pools_[e_mat_brush_type].Add(sptr_mat_brush);
	}
	else
	{
		PxLog_Error("PixImpMat::PutMatBrushToFreePool error brush error");
	}
}


void PixImpMat::ShowPixImpMatInfor()
{
	if (Get())
	{
		PxLog_Log("PixImpMat brush used array total count: %d", Get()->Brushs().Num());

		int n_used_arry_count[e_px_mat_brush_count] = { 0 };
		for (auto brush : Get()->Brushs())
		{
			n_used_arry_count[brush->BrushType()]++;
		}

		for (auto i = 0; i < e_px_mat_brush_count; i++)
		{
			PxLog_Log("    PixImpMat brush used type:%d count: %d", i, n_used_arry_count[i]);
		}

		for (auto i = 0; i < e_px_mat_brush_count; i++)
		{
			PxLog_Log("    PixImpMat brush pools type:%d count: %d", i, Get()->ary_free_mat_brush_pools_[i].Num());
		}
	}
}


#define DF_GET_MAT_Pools( ... ) TSharedPtr<PixMatBrush> sptr_mat_brush = nullptr;	\
	EPxMatBrushType e_mat_brush_type = PixMatBrush::MatBrushType(__VA_ARGS__);	\
	if (ary_free_mat_brush_pools_[e_mat_brush_type].Num() > 0)						\
	{																				\
		sptr_mat_brush = ary_free_mat_brush_pools_[e_mat_brush_type].Pop();			\
		sptr_mat_brush->ResetParams(__VA_ARGS__);									\
	}																				\
	else																			\
	{																				\
		sptr_mat_brush = MakeShareable(new PixMatBrush(__VA_ARGS__));				\
	}																				\
	return sptr_mat_brush;


TSharedPtr<PixMatBrush> PixImpMat::GetMatBrushFromPools(const pixui::size& size_Rect, const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
{
	DF_GET_MAT_Pools(size_Rect, color, borderRadius);
}


TSharedPtr<PixMatBrush> PixImpMat::GetMatBrushFromPools(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color& color)
{
	DF_GET_MAT_Pools(size_Rect, n_Widths, color);
}


TSharedPtr<PixMatBrush> PixImpMat::GetMatBrushFromPools(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color colors[])
{
	DF_GET_MAT_Pools(size_Rect, n_Widths, colors);
}


TSharedPtr<PixMatBrush> PixImpMat::GetMatBrushFromPools(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
{
	DF_GET_MAT_Pools(size_Rect, n_Widths, color, borderRadius);
}


TSharedPtr<PixMatBrush> PixImpMat::GetMatBrushFromPools(const pixui::size& size_Rect, const unsigned int n_Widths[],
	const pixui::color colors[], const pixui::BorderRadiuses& borderRadius)
{
	DF_GET_MAT_Pools(size_Rect, n_Widths, colors, borderRadius);
}


void PixImpMat::AllClear()
{
    Brushs().Empty();

	for (auto i=0; i < e_px_mat_brush_count ;i++)
	{
		ary_free_mat_brush_pools_[i].Empty();
	}
}


#define DF_GET_MAT_Brush( ... ) if (Get())														\
	{																							\
		FString fstr_Key = PixMatBrush::GetMatBrushKey( __VA_ARGS__ );							\
		TWeakPtr<PixMatBrush> wptr_mat_brush = FindMatBrush(fstr_Key);							\
		if (!wptr_mat_brush.IsValid())															\
		{																						\
			TSharedPtr<PixMatBrush> sptr_MatBrush = Get()->GetMatBrushFromPools(__VA_ARGS__);	\
			AddMatBrush(sptr_MatBrush);															\
			wptr_mat_brush = sptr_MatBrush;														\
		}																						\
		wptr_mat_brush.Pin()->AddRef();															\
		return MakeShareable(new PixSharedMatBrush(wptr_mat_brush));							\
	}


TSharedPtr<PixSharedMatBrush> PixImpMat::GetRectBrush(const pixui::size& size_Rect, const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
{
	DF_GET_MAT_Brush(size_Rect, color, borderRadius);
	return nullptr;
}


TSharedPtr<PixSharedMatBrush> PixImpMat::GetBorderBrush(const pixui::size& size_Rect, const unsigned int n_Widths[],
    const pixui::color& color)
{
	DF_GET_MAT_Brush(size_Rect, n_Widths, color);
	return nullptr;
}


TSharedPtr<PixSharedMatBrush> PixImpMat::GetBorderBrush(const pixui::size& size_Rect, const unsigned int n_Widths[],
    const pixui::color colors[])
{
	DF_GET_MAT_Brush(size_Rect, n_Widths, colors);
	return nullptr;
}


TSharedPtr<PixSharedMatBrush> PixImpMat::GetBorderBrush(const pixui::size& size_Rect, const unsigned int n_Widths[],
    const pixui::color& color, const pixui::BorderRadiuses& borderRadius)
{
	DF_GET_MAT_Brush(size_Rect, n_Widths, color, borderRadius);
	return nullptr;
}


TSharedPtr<PixSharedMatBrush> PixImpMat::GetBorderBrush(const pixui::size& size_Rect, const unsigned int n_Widths[],
    const pixui::color colors[], const pixui::BorderRadiuses& borderRadius)
{
	DF_GET_MAT_Brush(size_Rect, n_Widths, colors, borderRadius);
	return nullptr;
}


void PixImpMat::AddMatBrush(TSharedPtr<PixMatBrush>& sptr_mat_brush)
{
	auto pImp = Get();
	if (pImp)
	{
		//PxLog_Trace("PixImpMat:: Brushs add ----> %p  %s", sptr_mat_brush.Get(), TCHAR_TO_UTF8(*(sptr_mat_brush->Key())));
#if DF_PX_BUILD_NO_SHIPPING
		auto wptr_brush = FindMatBrush(sptr_mat_brush->Key());
		if (wptr_brush.IsValid())
		{
			PxLog_Error("HAVE SAME BRUSH IN ARRAY!!!!!!!!!!!!!!");
		}
#endif //DF_PX_BUILD_NO_SHIPPING
		pImp->Brushs().Add(sptr_mat_brush);
	}
	else
	{
		PxLog_Warning("PixImpMat::AddMatBrush not init!!!!!!");
	}
}


TWeakPtr<PixMatBrush> PixImpMat::FindMatBrush(const FString& fstr_key)
{
	TWeakPtr<PixMatBrush> wptr_mat_brush = nullptr;
	auto pImp = Get();
	if (pImp)
	{
		for (auto brush : pImp->Brushs())
		{
			if (brush->Key() == fstr_key)
			{
				wptr_mat_brush = brush;

#if DF_PX_BUILD_NO_SHIPPING
				if (wptr_mat_brush.Pin()->UsedRef() < 1)
				{
					PxLog_Error("PixImpMat::FindMatBrush USED REF ERROR!!!!!!!!!");
				}
#endif //DF_PX_BUILD_NO_SHIPPING
				break;
			}
		}
	}
	return wptr_mat_brush;
}


void PixImpMat::RemoveMatBrush(const FString& fstr_key)
{
	auto pImp = Get();
	if (pImp)
	{
		for (auto brush : Get()->Brushs())
		{
			if (brush->Key() == fstr_key)
			{
				pImp->Brushs().Remove(brush);
				pImp->PutMatBrushToFreePool(brush);
#if DF_PX_BUILD_NO_SHIPPING
				//PxLog_Trace("PixImpMat:: Brushs remove ----> %s", TCHAR_TO_UTF8(*fstr_key));
#endif //DF_PX_BUILD_NO_SHIPPING
				return;
			}
		}
	}
	PxLog_Warning("PixImpMat::RemoveMatBrush warning can not found brush %s", TCHAR_TO_UTF8(*fstr_key));
}