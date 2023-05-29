#pragma once
#include "CoreMinimal.h"

//work here...

struct PixUIProfilerPageFrame
{
    PixUIProfilerPageFrame()
    {
        un_All_Paint_Cost = 0;
        un_All_Tick_Cost = 0;

        //for paint command
        un_DrawText_Count = 0;
        un_DrawBorder_Count = 0;
        un_DrawImage_Count = 0;
        un_DrawRect_Count = 0;
        un_FillRect_Count = 0;
        un_DrawLine_Count = 0;

        un_DrawText_All_Time = 0;
        un_DrawBorder_All_Time = 0;
        un_DrawImage_All_Time = 0;
        un_DrawRect_All_Time = 0;
        un_FillRect_All_Time = 0;
        un_DrawLine_All_Time = 0;
    }

    uint32 un_All_Paint_Cost;
    uint32 un_All_Tick_Cost;

    //for paint command
    uint32 un_DrawText_Count;
    uint32 un_DrawBorder_Count;
    uint32 un_DrawImage_Count;
    uint32 un_DrawRect_Count;
    uint32 un_FillRect_Count;
    uint32 un_DrawLine_Count;

    uint32 un_DrawText_All_Time;
    uint32 un_DrawBorder_All_Time;
    uint32 un_DrawImage_All_Time;
    uint32 un_DrawRect_All_Time;
    uint32 un_FillRect_All_Time;
    uint32 un_DrawLine_All_Time;
};

