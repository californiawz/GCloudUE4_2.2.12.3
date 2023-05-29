/**************************************************

**** @file:     PxpTickCount.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/29

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/




#pragma once

#include "CoreMinimal.h"
#include "PixUIDef.h"

#if DF_PIXUI_PROFILER
#include "PixUIDrawItem/PixDrawItem.h"

enum ETimeCostType
{
	e_time_cost_type_total,			//(plugin_tick + core_tick + plugin_paint + core_paint)
	e_time_cost_type_plugin_tick,	//(un_tick_imp + un_tick_input + un_tick_widget)
	e_time_cost_type_core_tick,		//(un_tick_pxtime)
	e_time_cost_type_plugin_paint,	//(plugin paint)
	e_time_cost_type_core_paint,		//(core paint)

	e_tick_cost_count
};



enum ETimeCostType_CurFrame
{
	e_tick_cost_tick_type_total,
	e_tick_cost_tick_type_imp,
	e_tick_cost_tick_type_pxtime,
	e_tick_cost_tick_type_wiget,
	e_tick_cost_tick_type_input,

	e_tick_cost_tick_count
};


class PxpTimeBase
{
public:
	PxpTimeBase();
	virtual ~PxpTimeBase();

public:
	void CountCycles();

	const uint32& GetCycles() {
		return un_time_cycles;
	}
protected:
	uint32 un_time_cycles;
};


class PxpTimeLogOut : public PxpTimeBase
{
public:
	PxpTimeLogOut(FString fst_name);
	virtual ~PxpTimeLogOut();
private:
	FString fst_name_;
};



class PxpTickTotal : public PxpTimeBase
{
public:
	PxpTickTotal(ETimeCostType_CurFrame e_type);
	virtual ~PxpTickTotal();

protected:
	ETimeCostType_CurFrame e_type_;
};




class PxpWindowTimeBase : public PxpTimeBase
{
public:
	PxpWindowTimeBase(int32 h_id);
	virtual ~PxpWindowTimeBase() {};

public:
	int32 WinId() {
		return h_id_;
	}

protected:
	int32 h_id_;
};


class PxpWindowTimePaint : public PxpWindowTimeBase
{
public:
	PxpWindowTimePaint(int32 h_id);
	virtual ~PxpWindowTimePaint();
};



class PxpWindowTimeTick : public PxpWindowTimeBase
{
public:
	PxpWindowTimeTick(int32 n_id);
	virtual ~PxpWindowTimeTick();
};


class PxpWindowTimePaintItem : public PxpWindowTimeBase
{
public:
	PxpWindowTimePaintItem(int32 h_id, EPxDrawItem e_draw_type);
	virtual ~PxpWindowTimePaintItem();

protected:
	EPxDrawItem e_type_;
};

namespace PxpTickCount
{
	void PrfTotal_ClearTick();
	void PrfTotal_AddTickCount(ETimeCostType e_tpye, const uint32 un_tick);

	void PrfTotal_AddCurTick(ETimeCostType_CurFrame e_sub_type, const uint32 un_tick);
	uint32 PrfTotal_GetCurTick(ETimeCostType_CurFrame e_sub_type);

	void PrfWindow_New(int32 n_id);
	void PrfWindow_Reset(int32 n_id);
	void PrfWindow_TotalPaintTick(int32 n_id, const uint32 un_tick);
	void PrfWindow_WidgitTick(int32 n_id, const uint32 un_tick);
	void PrfWindow_AddDrawItemTick(int32 n_id, EPxDrawItem e_draw_type, const uint32 un_tick);
	void PrfWindow_Delete(int32 n_id);

	uint32 PrfWindow_GetTotalTime();
	uint32 PrfWindow_GetTotalPluginPaintTime();
	uint32 PrfWindow_GetTotalCorePaintTime();

	void PrfPrfTotal_LogOutAll();
};

#endif //DF_PIXUI_PROFILER