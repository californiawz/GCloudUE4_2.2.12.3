#pragma once
#include "CoreMinimal.h"

class PixUIProfilerMgr
{
public:
    PixUIProfilerMgr();
    ~PixUIProfilerMgr();


public:
    static void StartUp();
    static void Tick(float f_DeltaTime);
    static void ShutDown();

    static PixUIProfilerMgr* Get();

public:
    //page
    void OpenPage(int h_PageHandle);
    void OnStartTickPage(int h_PageHandle);
    void OnEndTickPage(int h_PageHandle, uint32 un_cost, bool b_valid = true);

    void OnStartPagePaint(int h_PageHandle);
    void OnEndPagePaint(int h_PageHandle, uint32 un_cost, bool b_valid = true);

    void OnPushClicp(int h_PageHandle, uint32 un_cost, bool b_valid = true);
    void OnPopClicp(int h_PageHandle, uint32 un_cost, bool b_valid = true);

    //draw command
    void DrawText(int h_PageHandle, uint32 un_cost, bool b_valid = true);
    void DrawBorder(int h_PageHandle, uint32 un_cost, bool b_valid = true);
    void DrawImage(int h_PageHandle, uint32 un_cost, bool b_valid = true);
    void DrawRect(int h_PageHandle, uint32 un_cost, bool b_valid = true);
    void FillRect(int h_PageHandle, uint32 un_cost, bool b_valid = true);
    void DrawLine(int h_PageHandle, uint32 un_cost, bool b_valid = true);

    //image
    void CreateImage(intptr_t h_ImgHandle, uint32 un_cost, bool b_valid = true);
    void UpdateImageData(intptr_t h_ImgHandle, uint32 un_cost, bool b_valid = true);
    void DeleteImage(intptr_t h_ImgHandle, uint32 un_cost, bool b_valid = true);

    //font
    void CreateFont(intptr_t h_ImgHandle, uint32 un_cost, bool b_valid = true);
    void MeasureFont(intptr_t h_ImgHandle, uint32 un_cost, bool b_valid = true);
    void DeleteFont(intptr_t h_ImgHandle, uint32 un_cost, bool b_valid = true);

private:
    struct PageProfiler
    {
        int h_Page_Id;

        //for paint time
        uint32 un_Cur_All_Paint_Cost;
        uint32 un_Cur_Pix_Paint_Cost;

        uint32 un_Avg_All_Paint_Cost;
        uint32 un_Avg_Pix_Paint_Cost;

        TArray<uint32> array_All_Paint_Cost;
        TArray<uint32> array_Pix_Paint_Cost;

        //for paint time
        uint32 un_Cur_All_Tick_Cost;
        uint32 un_Cur_Pix_Tick_Cost;

        uint32 un_Avg_All_Tick_Cost;
        uint32 un_Avg_Pix_Tick_Cost;

        TArray<uint32> array_All_Tick_Cost;
        TArray<uint32> array_Pix_Tick_Cost;

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

    struct ImgFontProfiler
    {
        intptr_t h_Img_Id;

        uint32 un_Update_Count;
        uint32 un_Update_Time;
    };

    TArray<int32> array_page_id_;
};

