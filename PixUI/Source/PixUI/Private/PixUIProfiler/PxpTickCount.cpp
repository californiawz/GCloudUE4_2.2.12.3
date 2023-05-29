/**************************************************

**** @file:     PxpTickCount.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/10/29

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/


#include "PxpTickCount.h"

#if DF_PIXUI_PROFILER
#include "PixUILog.h"



PxpTimeBase::PxpTimeBase()
{
	un_time_cycles = FPlatformTime::Cycles();
}

PxpTimeBase::~PxpTimeBase()
{
	CountCycles();
}

void PxpTimeBase::CountCycles()
{
	un_time_cycles = FPlatformTime::Cycles() - un_time_cycles;
}



PxpTimeLogOut::PxpTimeLogOut(FString fst_name)
{
	fst_name_ = fst_name;
}


PxpTimeLogOut::~PxpTimeLogOut()
{
	CountCycles();
	PxLog_Log("PxpTimeLogOut %s cost %fms", TCHAR_TO_UTF8(*fst_name_), FPlatformTime::ToMilliseconds(GetCycles()));
}




PxpTickTotal::PxpTickTotal(ETimeCostType_CurFrame e_type)
	:PxpTimeBase()
{
	e_type_ = e_type;
}


PxpTickTotal::~PxpTickTotal()
{
	CountCycles();
	PxpTickCount::PrfTotal_AddCurTick(e_type_, GetCycles());
}




PxpWindowTimeBase::PxpWindowTimeBase(int32 h_id)
	:PxpTimeBase()
{
	h_id_ = h_id;
}



PxpWindowTimePaint::PxpWindowTimePaint(int32 h_id)
	:PxpWindowTimeBase(h_id)
{

}

PxpWindowTimePaint::~PxpWindowTimePaint()
{
	CountCycles();
	PxpTickCount::PrfWindow_TotalPaintTick(WinId(), GetCycles());
}



PxpWindowTimeTick::PxpWindowTimeTick(int32 n_id)
	:PxpWindowTimeBase(n_id)
{

}

PxpWindowTimeTick::~PxpWindowTimeTick()
{
	CountCycles();
	PxpTickCount::PrfWindow_WidgitTick(WinId(), GetCycles());
}


PxpWindowTimePaintItem::PxpWindowTimePaintItem(int32 h_id, EPxDrawItem e_draw_type)
	:PxpWindowTimeBase(h_id)
{
	e_type_ = e_draw_type;
}

PxpWindowTimePaintItem::~PxpWindowTimePaintItem()
{
	CountCycles();
	PxpTickCount::PrfWindow_AddDrawItemTick(WinId(), e_type_, GetCycles());
}


static char s_tpye_name[][15] = {
	"total        :",
	"plugin_tick  :",
	"core_tick    :",
	"plugin_paint :",
	"core_paint   :"
};

static char s_draw_item_name[][15] = {
	"draw_border :",
	"draw_image  :",
	"draw_line   :",
	"draw_rect   :",
	"draw_text   :",
	"fill_rect   :",
	"pop_clip    :",
	"push_clip   :",
	"item_count  :"
};



struct TimeCost
{
	TimeCost(ETimeCostType e_type)
	{
		e_type_ = e_type;
		clear();
	}

	void clear() {
		un_count = 0;
		un_avg = 0;
		un_total = 0;
		un_max = 0;
		un_cnt_low = 0;
		un_cnt_over_0 = 0;
		un_cnt_over_10 = 0;
		un_cnt_over_20 = 0;
		un_cnt_over_30 = 0;
		un_cnt_over_40 = 0;
		un_cnt_over_50 = 0;
	}

	void Add(uint32 un_tick)
	{
		un_count++;
		if (un_tick > un_max)
		{
			un_max = un_tick;
		}

		un_total += un_tick;
		un_avg = un_total / un_count;

		if (un_tick >= un_avg * 15 / 10)
		{
			un_cnt_over_50++;
		} 
		else if (un_tick >= un_avg * 14 / 10)
		{
			un_cnt_over_40++;
		}
		else if (un_tick >= un_avg * 13 / 10)
		{
			un_cnt_over_30++;
		}
		else if (un_tick >= un_avg * 12 / 10)
		{
			un_cnt_over_20++;
		}
		else if (un_tick >= un_avg * 11 / 10)
		{
			un_cnt_over_10++;
		}
		else if (un_tick > un_avg)
		{
			un_cnt_over_0++;
		}
		else
		{
			un_cnt_low++;
		}
	}

	void LogOut() 
	{
		PxLog_Log("AllFrame PixUI Tick cost  %s  count:%03d  avg:%fms  max:%fms   low_avg:%03d(%2.2f)  over_0:%03d(%0.2f)  over_10:%03d(%0.2f)  over_20:%03d(%0.2f)  over_30:%03d(%0.2f)  over_40:%03d(%0.2f)  over_50:%03d(%0.2f)  ",
			s_tpye_name[e_type_], un_count,FPlatformTime::ToMilliseconds(un_avg), FPlatformTime::ToMilliseconds(un_max), (un_cnt_low), (float)(un_cnt_low / (float)un_count),
			(un_cnt_over_0), (float)(un_cnt_over_0 / (float)un_count), (un_cnt_over_10), (float)(un_cnt_over_10 / (float)un_count), (un_cnt_over_20), (float)(un_cnt_over_20 / (float)un_count),
			(un_cnt_over_30), (float)(un_cnt_over_30 / (float)un_count), (un_cnt_over_40), (float)(un_cnt_over_40 / (float)un_count), (un_cnt_over_50), (float)(un_cnt_over_50 / (float)un_count));
	}

	ETimeCostType e_type_;

	uint32 un_count;
	uint32 un_avg;
	uint32 un_total;
	uint32 un_max;
	uint32 un_cnt_low;
	uint32 un_cnt_over_0;
	uint32 un_cnt_over_10;
	uint32 un_cnt_over_20;
	uint32 un_cnt_over_30;
	uint32 un_cnt_over_40;
	uint32 un_cnt_over_50;
};


struct TimeTickWindow
{
	TimeTickWindow(int32 n_id) {
		n_win_id = n_id;
		Reset();
	}
	int32 Id() {
		return n_win_id;
	}
	void Reset() {
		for (int i=0; i < e_px_draw_item_count; i++)
		{
			n_paint_count[i] = 0;
			n_paint_time[i] = 0;
		}
		//n_tick_time = 0;
		n_total_paint_time = 0;
	}

	void AddTotalPaint(uint32 n_tick) {
		n_total_paint_time = n_tick;
	}

	void AddPaint(EPxDrawItem e_draw_type, uint32 n_tick) {
		n_paint_count[e_draw_type]++;
		n_paint_time[e_draw_type] += n_tick;
	}
	void AddTick(uint32 n_tick) {
		n_tick_time = n_tick;
	}

	uint32 PluginPaintTick() {
		uint32 n_win_total_paint_cost = 0;
		for (auto i = 0; i < e_px_draw_item_count; i++)
		{
			n_win_total_paint_cost += n_paint_time[i];
		}
		return n_win_total_paint_cost;
	}

	uint32 TotalTick() {
		return TotalPaintTick() + TickTime();
	}

	uint32 TickTime() {
		return n_tick_time;
	}

	uint32 TotalPaintTick() {
		return n_total_paint_time;
	}

	uint32 CorePaintTick() {
		return TotalTick() - PluginPaintTick();
	}

	void LogOut() {
		PxLog_Log("CurFrame PixUI Tick cost   Window wind_id:%p  total paint time: %fms (plugin_paint:%fms + core_paint:%fms)   widget time: %fms", 
			n_win_id,
			FPlatformTime::ToMilliseconds(TotalPaintTick()),
			FPlatformTime::ToMilliseconds(PluginPaintTick()),
			FPlatformTime::ToMilliseconds(CorePaintTick()),
			FPlatformTime::ToMilliseconds(n_tick_time));

		for (auto i = 0; i < e_px_draw_item_count; i++)
		{
			PxLog_Log("     Window Paint time element %s   type:%d   count:%03d  total time:%fms", 
				s_draw_item_name[i],
				i, 
				n_paint_count[i],
				FPlatformTime::ToMilliseconds(n_paint_time[i]));
		}
	}

	int32 n_win_id;
	uint32 n_paint_count[e_px_draw_item_count];
	uint32 n_paint_time[e_px_draw_item_count];
	uint32 n_tick_time;
	uint32 n_total_paint_time;
};


static TimeCost s_tick_count_item[e_tick_cost_count] = {
	e_time_cost_type_total,
	e_time_cost_type_plugin_tick,
	e_time_cost_type_core_tick,
	e_time_cost_type_plugin_paint,
	e_time_cost_type_core_paint,
};


static uint32 s_cur_tick[e_tick_cost_tick_count] = { 0 };


namespace PxpTickCount
{
	void PrfTotal_ClearTick()
	{
		for (auto i = 0; i < e_tick_cost_count; i++)
		{
			s_tick_count_item[i].clear();
		}
	}

	void PrfTotal_AddTickCount(ETimeCostType e_tpye, uint32 un_tick)
	{
		if (e_tpye < e_tick_cost_count)
		{
			s_tick_count_item[e_tpye].Add(un_tick);
		}
	}

	void PrfTotal_AddCurTick(ETimeCostType_CurFrame e_sub_type, uint32 un_tick)
	{
		s_cur_tick[e_sub_type] = un_tick;

		if (e_sub_type == e_tick_cost_tick_type_total)
		{
			PxpTickCount::PrfTotal_AddTickCount(e_time_cost_type_total, PxpTickCount::PrfTotal_GetCurTick(e_tick_cost_tick_type_total) + PxpTickCount::PrfWindow_GetTotalPluginPaintTime() + PxpTickCount::PrfWindow_GetTotalCorePaintTime());
			PxpTickCount::PrfTotal_AddTickCount(e_time_cost_type_plugin_tick, PxpTickCount::PrfTotal_GetCurTick(e_tick_cost_tick_type_total) - PxpTickCount::PrfTotal_GetCurTick(e_tick_cost_tick_type_pxtime));
			PxpTickCount::PrfTotal_AddTickCount(e_time_cost_type_core_tick, PxpTickCount::PrfTotal_GetCurTick(e_tick_cost_tick_type_pxtime));

			PxpTickCount::PrfTotal_AddTickCount(e_time_cost_type_plugin_paint, PxpTickCount::PrfWindow_GetTotalPluginPaintTime());
			PxpTickCount::PrfTotal_AddTickCount(e_time_cost_type_core_paint, PxpTickCount::PrfWindow_GetTotalCorePaintTime());
		}
	}

	uint32 PrfTotal_GetCurTick(ETimeCostType_CurFrame e_sub_type)
	{
		return s_cur_tick[e_sub_type];
	}

	TArray<TimeTickWindow*>& PrfTimeWinAry() {
		static TArray<TimeTickWindow*> s_ary_win;
		return s_ary_win;
	}
	TimeTickWindow* PrfTimeWinFind(uint32 n_id)
	{
		for (auto win : PrfTimeWinAry())
		{
			if (win->Id() == n_id)
			{
				return win;
			}
		}
		return nullptr;
	}
	void PrfWindow_New(int32 n_id)
	{
		PrfTimeWinAry().Add(new TimeTickWindow(n_id));
	}

	void PrfWindow_Reset(int32 n_id)
	{
		auto p_win = PrfTimeWinFind(n_id);
		if (p_win)
		{
			p_win->Reset();
		}
	}
	void PrfWindow_TotalPaintTick(int32 n_id, uint32 un_tick)
	{
		auto p_win = PrfTimeWinFind(n_id);
		if (p_win)
		{
			p_win->AddTotalPaint(un_tick);
		}
	}
	void PrfWindow_WidgitTick(int32 n_id, uint32 un_tick)
	{
		auto p_win = PrfTimeWinFind(n_id);
		if (p_win)
		{
			p_win->AddTick(un_tick);
		}
	}
	void PrfWindow_AddDrawItemTick(int32 n_id, EPxDrawItem e_draw_type, uint32 un_tick)
	{
		auto p_win = PrfTimeWinFind(n_id);
		if (p_win)
		{
			p_win->AddPaint(e_draw_type, un_tick);
		}
	}
	void PrfWindow_Delete(int32 n_id)
	{
		for (auto win : PrfTimeWinAry())
		{
			if (win->Id() == n_id)
			{
				PrfTimeWinAry().Remove(win);
				break;
			}
		}
	}

	uint32 PrfWindow_GetTotalTime()
	{
		uint32 n_total_time = 0;
		for (auto win : PrfTimeWinAry())
		{
			n_total_time += win->TotalTick();
		}
		return n_total_time;
	}

	uint32 PrfWindow_GetTotalPluginPaintTime()
	{
		uint32 n_total_time = 0;
		for (auto win : PrfTimeWinAry())
		{
			n_total_time += win->PluginPaintTick();
		}
		return n_total_time;
	}
	
	uint32 PrfWindow_GetTotalCorePaintTime()
	{
		uint32 n_total_time = 0;
		for (auto win : PrfTimeWinAry())
		{
			n_total_time += win->CorePaintTick();
		}
		return n_total_time;
	}

	void PrfPrfTotal_LogOutAll()
	{
		//count frame
		for (auto i = 0; i < e_tick_cost_count; i++)
		{
			s_tick_count_item[i].LogOut();
		}


		//Cur frame
		PxLog_Log("CurFrame PixUI Tick cost           Total time:%f ms", FPlatformTime::ToMilliseconds(s_cur_tick[e_tick_cost_tick_type_total]));
		PxLog_Log("     PixUI Tick PixImpTick           cost time:%f ms", FPlatformTime::ToMilliseconds(s_cur_tick[e_tick_cost_tick_type_imp]));
		PxLog_Log("     PixUI Tick PX_TimeTick          cost time:%f ms", FPlatformTime::ToMilliseconds(s_cur_tick[e_tick_cost_tick_type_pxtime]));
		PxLog_Log("     PixUI Tick UPixUIWidget::Tick   cost time:%f ms", FPlatformTime::ToMilliseconds(s_cur_tick[e_tick_cost_tick_type_wiget]));
		PxLog_Log("     PixUI Tick UPixUIInput::Tick    cost time:%f ms", FPlatformTime::ToMilliseconds(s_cur_tick[e_tick_cost_tick_type_input]));

		for (auto win : PrfTimeWinAry())
		{
			win->LogOut();
		}
	}
}

#endif //DF_PIXUI_PROFILER