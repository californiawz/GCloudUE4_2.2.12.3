/**************************************************

**** @file:     SPixPaintWidgetOld.cpp

**** @brief:    pixui widget paint

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "SPixPaintWidgetOld.h"

#ifdef DF_PX_USE_OLD_WIDGET

#include "SlateOptMacros.h"
#include "UnrealEngine.h"
#include "Slate.h"
#include "CoreUObject.h"

#include "Engine/Texture2D.h"
#include "Engine/GameViewportClient.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#endif //WITH_EDITOR

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "TimerManager.h"
#include "RenderUtils.h"
#include "Engine/Font.h"
#include "Engine/FontFace.h"
#include "Engine/UserInterfaceSettings.h"


#include "PixUIDef.h"
#include "PixUIBPLibrary.h"
#include "PixUILog.h"
#include "PixUtil.h"
#include "PixImp/PixImpMat.h"
#include "PixImp/PixImpFileLoad.h"
#include "PixImp/PixImpImg.h" 
#include "PixImp/PixImpFont.h"

#include "PixUIWidgetOld.h"


#include "PixUIDrawItem/PixDrawItemDrawBorder.h"
#include "PixUIDrawItem/PixDrawItemDrawImage.h"
#include "PixUIDrawItem/PixDrawItemDrawLine.h"
#include "PixUIDrawItem/PixDrawItemDrawRect.h"
#include "PixUIDrawItem/PixDrawItemDrawText.h"
#include "PixUIDrawItem/PixDrawItemFillRect.h"
#include "PixUIDrawItem/PixDrawItemPopClip.h"
#include "PixUIDrawItem/PixDrawItemPushClip.h"
#include "PixUIDrawItem/PixDrawItemDrawSlot.h"


#if DF_PIXUI_PROFILER
#include "PixUIProfiler/PxpTickCount.h"
#endif //DF_PIXUI_PROFILER


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPixPaintWidgetOld::Construct(const FArguments& InArgs)
{
    /*
    ChildSlot
    [
        // Populate the widget
    ];
    */

    h_PxView_ = nullptr;

    e_LastBatchType_ = e_px_batch_none;
	p_last_batch_status_ = nullptr;

    ul_CurDrawBaseLayer_ = 0;

    array_clip_.Empty();
	un_virtual_clip_count_ = 0;

    v2d_DesiredSize_ = FVector2D(10.0f, 10.0f);

    b_GeometryInit_ = false;

	v2d_last_move_pos_ = FVector2D(-1.0f, -1.0f);

	b_ActiveInput_ = false;

	b_loack_mouse_ = false;

	n_custom_layer_ = 0;

    PxLog_Trace("SPixPaintWidgetOld::Construct");

	//TAttribute<EVisibility> EpxViewVisibility = TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateRaw(this, &SPixPaintWidgetOld::CheckPxWidgetVisible));
	//SetVisibility(EpxViewVisibility);
}


SPixPaintWidgetOld::~SPixPaintWidgetOld()
{
	FreeDrawItemPools();
    PxLog_Trace("SPixPaintWidgetOld::~SPixPaintWidgetOld");
}

#if !DF_MULTY_PAGE_SUPPORT
static bool b_OnePixUIView_S = false;
#endif //!DF_MULTY_PAGE_SUPPORT

void SPixPaintWidgetOld::CreatePxView(UPixUIWidgetOld* p_Parent)
{
#if !DF_MULTY_PAGE_SUPPORT
    if (b_OnePixUIView_S)
    {
        PxLog_Error("SPixPaintWidgetOld::CreatePxView PX_ViewCreate error Current version do not support multiple pages....");
        return;
    }
#endif //!DF_MULTY_PAGE_SUPPORT

    if (PixUI::BePixLibLoad())
    {
        h_PxView_ = PX_Plugin::PX_ViewCreate(p_Parent, this, 10, 10, i_PxWindowID);
        if (!h_PxView_)
        {
            PxLog_Error("SPixPaintWidgetOld::CreatePxView PX_ViewCreate error....");
        }
#if !DF_MULTY_PAGE_SUPPORT
        else
        {
            b_OnePixUIView_S = true;
        }
#endif //!DF_MULTY_PAGE_SUPPORT

		if (h_PxView_)
		{
#if DF_PIXUI_PROFILER
			PxpTickCount::PrfWindow_New(PxViewHandle());
#endif //DF_PIXUI_PROFILER

			PxLog_Log("SPixPaintWidgetOld::CreatePxView Page Create~~~ %p", h_PxView_);
		}
    }

}


void SPixPaintWidgetOld::DestroyPxView()
{
    if (PixUtil::IsGamePlay() && h_PxView_)
    {
        PX_Plugin::PX_ViewDestroy(h_PxView_);

#if !DF_MULTY_PAGE_SUPPORT
        b_OnePixUIView_S = false;
#endif

#if DF_PIXUI_PROFILER
		PxpTickCount::PrfWindow_Delete(PxViewHandle());
#endif //DF_PIXUI_PROFILER

        PxLog_Log("SPixPaintWidgetOld::DestroyPxView Page Destroy~~~  %p", h_PxView_);
    }

    h_PxView_ = nullptr;
}


void SPixPaintWidgetOld::OnSizeChange(const FVector2D& v2d_NewSize)
{
    b_GeometryInit_ = true;
    v2d_DesiredSize_ = v2d_NewSize;
    if (PxViewHandle())
    {
        PX_Plugin::PX_ViewWinSizeUpdate(PxViewHandle(), v2d_DesiredSize_.X, v2d_DesiredSize_.Y);
    }
}

void SPixPaintWidgetOld::OnScreenChange(const FVector2D& v2d_NewSize)
{
    v2d_ScreenSize_ = v2d_NewSize;
    if (PxViewHandle())
    {
        PX_Plugin::PX_ViewScreenSizeUpdate(PxViewHandle(), v2d_ScreenSize_.X, v2d_ScreenSize_.Y);
    }
}


void SPixPaintWidgetOld::BatchElement(PixDrawItem* p_batch_item)
{
	EPxBatchType e_batch_type = p_batch_item->BatchType();
	void* p_batch_status = p_batch_item->BatchStatus();

	if (e_batch_type != e_px_batch_none)
	{
		if (e_LastBatchType_ != e_batch_type ||
			e_LastBatchType_ == e_px_batch_rect_mat ||
			e_LastBatchType_ == e_px_batch_matiral ||
			e_LastBatchType_ == e_px_batch_image)
		{
			if (e_LastBatchType_ == e_px_batch_image && e_batch_type == e_px_batch_image && p_last_batch_status_ == p_batch_status)
			{
				//to check draw status
				return;
			}

			//em_draw_rect_mat or em_draw_matiral need to add layer,
			//Make sure the same brush rendering level is correct
			if (e_LastBatchType_ != e_px_batch_none)
			{
				ul_CurDrawBaseLayer_++;
			}
			e_LastBatchType_ = e_batch_type;
			p_last_batch_status_ = p_batch_status;
		}
	}
}


void SPixPaintWidgetOld::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{

#if DF_PIXUI_PROFILER
	PxpWindowTimeTick tick_time(PxViewHandle());
#endif //DF_PIXUI_PROFILER

    auto tmp_size = AllottedGeometry.GetLocalSize();
    
    if (tmp_size != v2d_DesiredSize_)
    {
        OnSizeChange(tmp_size);
    }
    if (PixUtil::GameWorld() && PixUtil::GameWorld()->GetGameViewport())
    {
		FVector2D screen_size = PixUtil::GameWorld()->GetGameViewport()->Viewport->GetSizeXY();
		screen_size = screen_size / (AllottedGeometry.Scale > 0 ? AllottedGeometry.Scale : 1.0f);
        if (screen_size != v2d_ScreenSize_)
        {
            OnScreenChange(screen_size);
        }
    }
}


int32 SPixPaintWidgetOld::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaint tickItme(PxViewHandle());
#endif //DF_PIXUI_PROFILER

    int32 n_layer_id = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    //playing
    if (PxViewHandle())
    {
		const_cast<SPixPaintWidgetOld*>(this)->PreAllPaint();

		int n_draw_layer = LayerId + GetCustomLayer();

		PX_FOnPaintHandlerParams paint_Param(Args, AllottedGeometry, MyClippingRect, OutDrawElements, n_draw_layer, bParentEnabled);

		int n_ret = 0;
		if (!UPixUIBPLibrary::PixUI_GetDebugRetainDraw())
		{
			static int32 s_n_cur_paint_cont = 0;
			if (s_n_cur_paint_cont >= UPixUIBPLibrary::PixUI_GetPaintDura())
			{
				n_ret = PX_Plugin::PX_ViewPaint(PxViewHandle(), (px_ptr)&paint_Param, (px_ptr)this);
				s_n_cur_paint_cont = 0;
			}
			else
			{
				s_n_cur_paint_cont++;
			}
		}
		if (n_ret == 0)
		{
			//remove const
			const_cast<SPixPaintWidgetOld*>(this)->RetainDraw(paint_Param);
		}

		const_cast<SPixPaintWidgetOld*>(this)->EndAllPaint();
    }
    else
    {
        bool b_InEditor = false;

#if WITH_EDITOR
        if (!PixUtil::IsGamePlay())
        {
            b_InEditor = true;
            //in editor draw pixui widget 
            const bool bIsEnabled = ShouldBeEnabled(bParentEnabled);

            const ESlateDrawEffect DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
            const FLinearColor FinalColorAndOpacity(1.0, 1.0, 1.0, 0.5);
            static const FSlateColorBrush s_stBrushWhite = FSlateColorBrush(FColorList::White);

            FSlateDrawElement::MakeBox(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), &s_stBrushWhite, ESlateDrawEffect::None, FinalColorAndOpacity);
        }
#endif //WITH_EDITOR

        if (!b_InEditor)
        {
            if (!UPixUIBPLibrary::PixUI_IsStartUp())
            {
                auto localFont = FCoreStyle::Get().GetFontStyle("NormalFont");
                localFont.Size = 32;
                FString tip = TEXT("Pix UI Do not Startup!!!!");
                FSlateDrawElement::MakeText(
                    OutDrawElements,
                    LayerId,
                    AllottedGeometry.ToPaintGeometry(),
                    tip,
                    localFont,
                    ESlateDrawEffect::None,
                    FColor::Red
                );
            }
            else
            {
                auto localFont = FCoreStyle::Get().GetFontStyle("NormalFont");
                localFont.Size = 32;

                FString tip;

#if !DF_MULTY_PAGE_SUPPORT
                if (b_OnePixUIView_S)
                {
                    TArray<FStringFormatArg> strArgs;
                    strArgs.Add(FStringFormatArg(UPixUIBPLibrary::PixUI_Version()));
                    tip = FString::Format(TEXT("Current Pixui Version{0} do not support Mutiple Page"), strArgs);
                }
                else
                {
                    tip = TEXT("PixUI View Was InValid..Please ReOpen!!");
                }
#else
                tip = TEXT("PixUI View Was InValid..Please ReOpen!!");
#endif //!DF_MULTY_PAGE_SUPPORT

                FSlateDrawElement::MakeText(
                    OutDrawElements,
                    LayerId,
                    AllottedGeometry.ToPaintGeometry(),
                    tip,
                    localFont,
                    ESlateDrawEffect::None,
                    FColor::Red
                );
            }
        }
    }


    return n_layer_id + ul_CurDrawBaseLayer_;
}


bool SPixPaintWidgetOld::SupportsKeyboardFocus() const
{
    return PxViewHandle() != nullptr;
}


FReply SPixPaintWidgetOld::OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent)
{
    if (PxViewHandle() && BeActiveInput())
    {
        TCHAR tc_input_char = InCharacterEvent.GetCharacter();
        if (tc_input_char != TEXT('\t'))
        {
            switch (tc_input_char)
            {
                case TCHAR(8):        // Backspace
                case TCHAR('\n'):    // Newline (Ctrl+Enter), we handle adding new lines via HandleCarriageReturn rather than processing newline characters
                case 1:                // Swallow Ctrl+A, we handle that through OnKeyDown
                case 3:                // Swallow Ctrl+C, we handle that through OnKeyDown
                case 13:            // Swallow Enter, we handle that through OnKeyDown
                case 22:            // Swallow Ctrl+V, we handle that through OnKeyDown
                case 24:            // Swallow Ctrl+X, we handle that through OnKeyDown
                case 25:            // Swallow Ctrl+Y, we handle that through OnKeyDown
                case 26:            // Swallow Ctrl+Z, we handle that through OnKeyDown
                case 27:            // Swallow ESC, we handle that through OnKeyDown
                case 127:            // Swallow CTRL+Backspace, we handle that through OnKeyDown
                    break;
                default:
                    // Type the character, but only if it is allowed.
                    char szInput[2] = { 0 };
                    szInput[0] = (char)tc_input_char;
                    PX_Plugin::PX_ViewkeyBoardInput(PxViewHandle(), szInput, false, false, false);
                    break;
            }
        }
        return FReply::Handled();
    }
    return FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
    if (PxViewHandle())
    {
        if (PX_Plugin::PX_ViewKeyEvent(PxViewHandle()
            , PixUtil::UEKeyEventToPixUIKeyCode(InKeyEvent)
            , PixUtil::UEKeyEventToPixUIKeyModifier(InKeyEvent), true))
        {
            return FReply::Handled();
        }
    }
    return FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
    if (PxViewHandle())
    {
        //PxLog_Trace("SPixPaintWidgetOld::OnKeyUp keykocde:%d",InKeyEvent.GetKeyCode());
        if (PX_Plugin::PX_ViewKeyEvent(PxViewHandle(),
			PixUtil::UEKeyEventToPixUIKeyCode(InKeyEvent),
			PixUtil::UEKeyEventToPixUIKeyModifier(InKeyEvent), false))
        {
            return FReply::Handled();
        }
    }
    return FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	bool b_handle = false;
    if (PxViewHandle())
    {
		FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
        if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
        {
            // RIGHT BUTTON
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Right, true);
			//ue4 do not fire up when down unhandled
			if (!b_handle)
			{
				PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Right, false);
			}
        }
        else if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
        {
            //
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Left, true);
			if (!b_handle)
			{
				PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Left, false);
			}
        }
        else if (MouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton)
        {
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Middle, true);
			if (!b_handle)
			{
				PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Middle, false);
			}
        }
#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnMouseButtonDown handle:%d xpos:%f ypos:%f", b_handle, localPos.X, localPos.Y);
		}
#endif //DF_PIXUI_PROFILER
		
    }
	if (b_handle)
	{
		b_loack_mouse_ = true;
		return FReply::Handled().CaptureMouse(SharedThis(this));
	}
	return FReply::Unhandled();
}



FReply SPixPaintWidgetOld::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	bool b_handle = false;
    if (PxViewHandle())
    {
		//FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		//UE4 BUG----->up event use last pos,Because the current pos has a delay problem 
		FVector2D lastPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetLastScreenSpacePosition());
        if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
        {
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), lastPos.X, lastPos.Y, 0, pixui::MouseButton::MB_Right, false);
        }
        else if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
        {
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), lastPos.X, lastPos.Y, 0, pixui::MouseButton::MB_Left, false);
        }
        else if (MouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton)
        {
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), lastPos.X, lastPos.Y, 0, pixui::MouseButton::MB_Middle, false);
        }

#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnMouseButtonUp handle:%d xpos:%f ypos:%f  lastPos.x:%f  lastPos.y:%f", b_handle, 
				MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()).X, MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()).Y, lastPos.X, lastPos.Y);
		}
#endif //DF_PIXUI_PROFILER

    }
	if (b_loack_mouse_)
	{
		b_loack_mouse_ = false;
		return FReply::Handled().ReleaseMouseCapture();
	}
	return b_handle ? FReply::Handled() : FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
#if PLATFORM_WINDOWS || PLATFORM_MAC
	bool b_handle = false;
    // for android platform this function always call ----> ue4 bug
    if (PxViewHandle())
    {
		if (v2d_last_move_screen_pos_ == MouseEvent.GetScreenSpacePosition())
		{
			return FReply::Handled();
		}
		v2d_last_move_screen_pos_ = MouseEvent.GetScreenSpacePosition();

        FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		if (v2d_last_move_pos_ != localPos)
		{
			v2d_last_move_pos_ = localPos;
			if (PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_None, false))
			{
				b_handle = true;
			}
		}
#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnMouseMove handle:%d xpos:%f ypos:%f", b_handle, localPos.X, localPos.Y);
		}
#endif //DF_PIXUI_PROFILER
    }
	return b_handle ? FReply::Handled() : FReply::Unhandled();
#endif
    return FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
    if (PxViewHandle())
    {
        FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
        if (PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, MouseEvent.GetWheelDelta(), pixui::MouseButton::MB_None, false))
        {
            return FReply::Handled();
        }
    }
    return FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
    if (PxViewHandle())
    {
        //pixui have no doubleClick,deal with click
        bool b_handle = false;
		FVector2D localPos = InMyGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
        if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
        {
            // RIGHT BUTTON
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Right, false);
        }
        else if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
        {
            //
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Left, false);
        }
        else if (InMouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton)
        {
            b_handle = PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Middle, false);
        }
		//PxLog_Trace("OnMouseButtonDoubleClick handle:%d xpos:%f ypos:%f", b_handle, localPos.X, localPos.Y);
        return b_handle ? FReply::Handled(): FReply::Unhandled();
    }

    return FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent)
{
	FVector2D localPos = MyGeometry.AbsoluteToLocal(GestureEvent.GetScreenSpacePosition());
	//PxLog_Trace("OnTouchGesture xpos:%f ypos:%f", localPos.X, localPos.Y);

    if (PxViewHandle())
    {
        return FReply::Unhandled();
    }
    return FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	bool b_handle = false;
    if (PxViewHandle())
    {
        FVector2D localPos = MyGeometry.AbsoluteToLocal(InTouchEvent.GetScreenSpacePosition());

		if (UPixUIBPLibrary::PixUI_IsMobileUseTouchEvent())
		{
			b_handle = PX_Plugin::PX_ViewTouchEvent(PxViewHandle(), localPos.X, localPos.Y, InTouchEvent.GetPointerIndex(),pixui::ETouchPhase::em_touch_phase_began);
			//PxLog_Trace("OnTouchStarted index:%d handle:%d xpos:%f ypos:%f", InTouchEvent.GetPointerIndex(), b_handle, localPos.X, localPos.Y);
		}
		else
		{
			//0.4 do not need PX_ViewMouseEvent
			b_handle |= PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Left, true);
		}
		
#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnTouchStarted index:%d handle:%d xpos:%f ypos:%f", InTouchEvent.GetPointerIndex(), b_handle, localPos.X, localPos.Y);
		}
#endif //DF_PIXUI_PROFILER
    }

	if (b_handle)
	{
		b_loack_mouse_ = true;
		return FReply::Handled().CaptureMouse(SharedThis(this));
	}
	return FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	bool b_handle = false;
    if (PxViewHandle())
    {
		if (v2d_last_move_screen_pos_ == InTouchEvent.GetScreenSpacePosition())
		{
			return FReply::Handled();
		}
		v2d_last_move_screen_pos_ = InTouchEvent.GetScreenSpacePosition();

		FVector2D localPos = MyGeometry.AbsoluteToLocal(InTouchEvent.GetScreenSpacePosition());
		///////////////////////////////////////////////////
		if (v2d_last_move_pos_ != localPos)
		{
			v2d_last_move_pos_ = localPos;
			if (UPixUIBPLibrary::PixUI_IsMobileUseTouchEvent())
			{
				if (PX_Plugin::PX_ViewTouchEvent(PxViewHandle(), localPos.X, localPos.Y, InTouchEvent.GetPointerIndex(), pixui::ETouchPhase::em_touch_phase_moved))
				{
					b_handle = true;
				}
			}
			else
			{
				if (PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_None, false))
				{
					b_handle = true;
				}
			}
		}
			
#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnTouchMoved index:%d handle:%d xpos:%f ypos:%f  last.x:%f last.y:%f  v2d_last_move_screen_pos_.x %f v2d_last_move_screen_pos_.y：%f last_screen_pos.x:%f last_screen_pos.y:%f",
				InTouchEvent.GetPointerIndex(), b_handle, localPos.X, localPos.Y, v2d_last_move_pos_.X, v2d_last_move_pos_.Y,
				v2d_last_move_screen_pos_.X, v2d_last_move_screen_pos_.Y,
				InTouchEvent.GetLastScreenSpacePosition().X, InTouchEvent.GetLastScreenSpacePosition().Y);
		}
#endif //DF_PIXUI_PROFILER

		//////////////////////////////////////////////////
		// b_handle = PX_Plugin::PX_ViewTouchEvent(PxViewHandle(), localPos.X, localPos.Y, InTouchEvent.GetPointerIndex(), pixui::ETouchPhase::em_touch_phase_moved);
		

		//0.4 do not need PX_ViewMouseEvent
		//b_handle |= PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_None, false);
	}
	return b_handle ? FReply::Handled() : FReply::Unhandled();
}


FReply SPixPaintWidgetOld::OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	bool b_handle = false;
    if (PxViewHandle())
    {
        //FVector2D localPos = MyGeometry.AbsoluteToLocal(InTouchEvent.GetScreenSpacePosition());
		//UE4 BUG----->up event use last pos,Because the current pos has a delay problem 
		FVector2D lastPos = MyGeometry.AbsoluteToLocal(InTouchEvent.GetLastScreenSpacePosition());

		if (UPixUIBPLibrary::PixUI_IsMobileUseTouchEvent())
		{
			b_handle = PX_Plugin::PX_ViewTouchEvent(PxViewHandle(), lastPos.X, lastPos.Y, InTouchEvent.GetPointerIndex(), pixui::ETouchPhase::em_touch_phase_ended);
			//PxLog_Trace("OnTouchEnded index:%d handle:%d lastPos xpos:%f lastPos ypos:%f", InTouchEvent.GetPointerIndex(), b_handle, lastPos.X, lastPos.Y);
		}
		else
		{
			//0.4 do not need PX_ViewMouseEvent
			b_handle |= PX_Plugin::PX_ViewMouseEvent(PxViewHandle(), lastPos.X, lastPos.Y, 0, pixui::MouseButton::MB_Left, false);
		}

#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnTouchEnded index:%d handle:%d lastPos xpos:%f lastPos ypos:%f", InTouchEvent.GetPointerIndex(), b_handle, lastPos.X, lastPos.Y);
		}
#endif //DF_PIXUI_PROFILER
	}

	if (b_loack_mouse_)
	{
		b_loack_mouse_ = false;
		return FReply::Handled().ReleaseMouseCapture();
	}
	return b_handle ? FReply::Handled() : FReply::Unhandled();
}



FReply SPixPaintWidgetOld::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	SCompoundWidget::OnFocusReceived(MyGeometry, InFocusEvent);
	PxLog_Trace("SPixPaintWidgetOld::OnFocusReceived ~");
	return FReply::Handled();
}


void SPixPaintWidgetOld::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	SCompoundWidget::OnFocusLost(InFocusEvent);
	PxLog_Trace("SPixPaintWidgetOld::OnFocusLost ~");
}



void SPixPaintWidgetOld::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	SCompoundWidget::OnMouseEnter(MyGeometry, MouseEvent);
	// PxLog_Trace("SPixPaintWidgetOld::OnMouseEnter ~");
}


void SPixPaintWidgetOld::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	SCompoundWidget::OnMouseLeave(MouseEvent);
	// PxLog_Trace("SPixPaintWidgetOld::OnMouseLeave ~");
}


bool SPixPaintWidgetOld::IsInteractable() const
{
	// PxLog_Trace("SPixPaintWidgetOld::IsInteractable ~");

// 	if (PxViewHandle())
// 	{
// 		//get current cursor position
// 		FVector2D cur_pos = FSlateApplication::Get().GetCursorPos();
// 		FVector2D local_Pos = GetCachedGeometry().AbsoluteToLocal(cur_pos);
// 
// 		//hit test be or not visible
// 		bool b_hit = PX_Plugin::PX_ViewHitTest(PxViewHandle(), local_Pos.X, local_Pos.Y);
// 		return b_hit;
// 	}
	return true;
}

FVector2D SPixPaintWidgetOld::CaculateGeometryTextSize(const FString& fst_Text, const FSlateFontInfo& SlateFont)
{
	float f_GameUIScale = 1.0f;
	auto Geometry = GetCachedGeometry();
	if (b_GeometryInit_)
	{
		f_GameUIScale = Geometry.Scale;
	}
	else
	{
		//maybe widget opened on begin event and the Geometry was not Cached Geometry
		if (GEngine && GEngine->GameViewport)
		{
			FIntPoint ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
			f_GameUIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(ViewportSize);
		}
		else
		{
			f_GameUIScale = Geometry.Scale;
		}
	}
    const TSharedRef< FSlateFontMeasure > FontMeasureService = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
    FVector2D v2d_TextSize = FontMeasureService->Measure(fst_Text, SlateFont, f_GameUIScale);
    if (UPixUIBPLibrary::PixUI_IsDynamicFixFontSize())
    {
        //fix font size on paint
        return v2d_TextSize;
    }

    
    //fix font size on create
	//return v2d_TextSize / CaculateGeometryScaleOfText(fst_Text, f_GameUIScale, SlateFont);
	return v2d_TextSize / f_GameUIScale;
}


float CaculateFixScale(const int32 n_TextWith, const int32 n_TextNum, const float f_GeomeryScale)
{
    check(n_TextNum != 0);
    float fAvgTextWidth = n_TextWith / n_TextNum;
    float fScaleTextWidth = f_GeomeryScale * fAvgTextWidth;
    //rounding
    int32 nFixTextSize = (fScaleTextWidth > 0.0f) ? (fScaleTextWidth + 0.5f) : (fScaleTextWidth - 0.5f);
    check(nFixTextSize != 0);
    return fScaleTextWidth / nFixTextSize;
}


float SPixPaintWidgetOld::CaculateGeometryScaleOfText(const FString& fst_Text, float f_GeomeryScale,
    const FSlateFontInfo& SlateFont)
{
    float fTextScale = 1.0f;
    int32 n_TextNum = FCString::Strlen(*fst_Text);

    const TSharedRef< FSlateFontMeasure > FontMeasureService = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
    FVector2D v2d_TextSize = FontMeasureService->Measure(fst_Text, SlateFont);
    int32 n_TextWith = v2d_TextSize.X;
    //If the char cannot be measured in the font,return default size
    if(n_TextWith<=0)
    {
        return SlateFont.Size;
    }
    //Count the size and number of different character types  e.g.:character a/A/啊 was different
    TMap<float, int32> MapCharCounts;
    for (auto i = 0; i < n_TextNum; i++)
    {
        FVector2D vctFontSize = FontMeasureService->Measure(fst_Text.Mid(i, 1), SlateFont);

        int32* p_Count = MapCharCounts.Find(vctFontSize.X);
        if (p_Count)
        {
            (*p_Count) += 1;
        }
        else
        {
            MapCharCounts.Add(vctFontSize.X, 1);
        }

    }

    if (MapCharCounts.Num() == 1)
    {
        fTextScale = CaculateFixScale(n_TextWith, n_TextNum, f_GeomeryScale);
    }
    else
    {
        float f_SrcWidth = n_TextWith * f_GeomeryScale;
        float f_DstWidth = 0.0f;
        for (auto CharInfo : MapCharCounts)
        {
            float fScaleTextWidth = f_GeomeryScale * CharInfo.Key;
            //rounding
            int32 nFixTextSize = floor(fScaleTextWidth + 0.5f);

            f_DstWidth += (nFixTextSize * CharInfo.Value);
        }

        if (f_DstWidth > 0.00001f)
        {
            fTextScale = f_SrcWidth / f_DstWidth;
        }
    }
    check(fTextScale > 0.00001f);
    return fTextScale;
}

bool SPixPaintWidgetOld::QueryPixelFormatSupport(pixui::EPixelFormat emPixelFormat)
{
	if (GPixelFormats[PixUtil::PixUIPixelFormatToUEPixelFormat(emPixelFormat)].Supported)
	{
		return true;
	}
	return false;
}

px_ptr SPixPaintWidgetOld::GetContextPtr()
{
	if (pxViewHandle())
	{
		return PX_Plugin::PX_ViewGetContextPtr(pxViewHandle());
	}
	PxLog_Error(" GetContextPtr PxViewHandle() inValid");
	return nullptr;
}


FVector2D SPixPaintWidgetOld::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
    // When there is no widget in the button, it sizes itself based on
    // the border image specified by the style.
    if (PxViewHandle())
    {
        return v2d_DesiredSize_;
    }
    else
    {
        //Super
        return SCompoundWidget::ComputeDesiredSize(LayoutScaleMultiplier);
    }
}


void SPixPaintWidgetOld::OnPrePaint(pixui::PxViewHandle hDevice)
{
	
	for (int i = 0; i < e_px_draw_item_count; i++)
	{
		un_draw_item_pools_index[i] = 0;
	}
	p_root_draw_item = nullptr;
	p_cur_draw_item = nullptr;

	//PxLog_Trace("frame start............................................");
}


void SPixPaintWidgetOld::OnEndPaint(pixui::PxViewHandle hDevice, const int nPaintCode)
{
    //do some stuff on end paint
	//UE_LOG(PixUI_Module, Error, TEXT(" OnEndPaint x:%d"), m_nClicpCount);

	//PxLog_Trace("frame end............................................");
}


void SPixPaintWidgetOld::PushClip(pixui::PxViewHandle hDevice, const pixui::ClipRegion& polygon)
{
    PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
    if (pDrawParam)
    {
        PushClip(hDevice, polygon.getMatrix(), polygon.getPosition());
    }
}


void SPixPaintWidgetOld::PushClip(pixui::PxViewHandle hDevice, const pixui::matrix& mat, const pixui::position& rectClip)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewHandle(), e_px_draw_item_push_clip);
#endif //DF_PIXUI_PROFILER


	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_push_clip);
		if (p_item)
		{
			DealwithNewItem(p_item);

			((PixDrawItemPushClip*)(p_item))->UpdateClipParam(mat, rectClip);

			//0 valid ,1 invalid
			auto un_clip_type = p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);

			array_clip_.Add(un_clip_type);
			if (un_clip_type == 1)
			{
				un_virtual_clip_count_++;
			}
		}
	}
}


void SPixPaintWidgetOld::PopClip(pixui::PxViewHandle hDevice)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(PxViewHandle(), e_px_draw_item_pop_clip);
#endif //DF_PIXUI_PROFILER


	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_pop_clip);
		if (p_item)
		{
			DealwithNewItem(p_item);
			auto un_clip_type = array_clip_.Pop();

			((PixDrawItemPopClip*)(p_item))->UpdatePopClipParam(un_clip_type == 0);

			p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);
			if (un_clip_type == 1)
			{
				un_virtual_clip_count_--;
			}
		}
	}
}


float SPixPaintWidgetOld::TextWidth(pixui::PxViewHandle hDevice, const char* pszText, pixui::PxViewHandle hFont)
{
    float f_Width = 0.0f;
    TWeakPtr<PixFont> wptr_pix_font = PixImpFont::GetSlateFont(hFont);
    FString fstr_Tmp = UTF8_TO_TCHAR(pszText);

    //replace \n
    fstr_Tmp = fstr_Tmp.Replace(TEXT("\n"), TEXT("  "));

    if (wptr_pix_font.IsValid() && wptr_pix_font.Pin()->sptr_SlatFont_.Get())
    {
		if (!fstr_Tmp.IsEmpty())
		{
			FVector2D vctFontSize = CaculateGeometryTextSize(fstr_Tmp, *(wptr_pix_font.Pin()->sptr_SlatFont_.Get()));
			f_Width = vctFontSize.X;
		}
    }
    else
    {
        PxLog_Error("SPixPaintWidgetOld::TextWidth Error,can not found font:%p ", hFont);
    }
    return f_Width;
}


int SPixPaintWidgetOld::PtToPix(const int nPt)
{
    return PixUtil::PtToPix(nPt);
}


void SPixPaintWidgetOld::SetCursor(const char * pszCursor)
{
    //do nothing
}


void SPixPaintWidgetOld::DrawText(
	pixui::PxViewHandle                      hDevice,
	pixui::PxViewHandle                      hFont,
    const pixui::matrix&        mat,
    const char*                 pszTextDraw,
    const pixui::color&         color,
    const pixui::position&      ptPos,
    const float                 fBlur)
{
	//PxLog_Trace("DrawText x pos:%f y pos:%f   text:%s                       ", mat[4], mat[5], pszTextDraw);
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(pxViewHandle(), e_px_draw_item_draw_text);
#endif //DF_PIXUI_PROFILER

	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam && un_virtual_clip_count_ <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_text);
		if (p_item)
		{
			DealwithNewItem(p_item);

			((PixDrawItemDrawText*)(p_item))->UpdateTextParam(hFont, mat, pszTextDraw, color, ptPos, fBlur);

			BatchElement(p_item);
			p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);
		}
	}

}


void SPixPaintWidgetOld::DrawBorder(
	pixui::PxViewHandle                          hDevice,
        const pixui::matrix&            mat,
        const pixui::position&          rcDraw,
        const unsigned int              nWidths[],
        const pixui::BorderStyle       eLineTypes[],
        const pixui::color              colors[],
        const pixui::BorderRadiuses&   radius)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(pxViewHandle(), e_px_draw_item_draw_border);
#endif //DF_PIXUI_PROFILER


	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam && un_virtual_clip_count_ <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_border);
		if (p_item)
		{
			DealwithNewItem(p_item);

			((PixDrawItemDrawBorder*)(p_item))->UpdateBorderParam(mat, rcDraw, nWidths, eLineTypes, colors, radius);
			BatchElement(p_item);
			p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);
		}
	}
}


void SPixPaintWidgetOld::DrawRect(
	pixui::PxViewHandle                          hDevice,
    const pixui::matrix&            mat,
    const pixui::position&          rcDraw,
    const unsigned int              unWidth,
    const pixui::BorderStyle       emLineType,
    const pixui::color&             color,
    const pixui::BorderRadiuses&   radius)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(pxViewHandle(), e_px_draw_item_draw_rect);
#endif //DF_PIXUI_PROFILER

	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam && un_virtual_clip_count_ <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_rect);
		if (p_item)
		{
			DealwithNewItem(p_item);

			((PixDrawItemDrawRect*)(p_item))->UpdateRectParam(mat, rcDraw, unWidth, emLineType, color, radius);
			BatchElement(p_item);
			p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);
		}
	}
}

void SPixPaintWidgetOld::FillRect(
	pixui::PxViewHandle				hDevice,
    const pixui::matrix&            mat,
    const pixui::position&          ptDraw,
    const pixui::color&             color,
    const pixui::BorderRadiuses&   radius)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(pxViewHandle(), e_px_draw_item_fill_rect);
#endif //DF_PIXUI_PROFILER

	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam && un_virtual_clip_count_ <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_fill_rect);
		if (p_item)
		{
			DealwithNewItem(p_item);

			((PixDrawItemFillRect*)(p_item))->UpdateFillRectParam(mat, ptDraw, color, radius);
			BatchElement(p_item);
			p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);
		}
	}

}


void SPixPaintWidgetOld::DrawImage(
	pixui::PxViewHandle                              hDevice,
	pixui::PxViewHandle            pImage,
    const pixui::matrix&                mat,
    const pixui::position&              rcDraw,
    const pixui::position&              rcImageSrc,
    const pixui::BackgroundRepeat      emRepeat,
    const pixui::BackgroundAttachment  emAttachment,
    const pixui::ImageSlice&           sliceImage,
    const pixui::color&                 tilinColor,
    const pixui::BorderRadiuses&       radius)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(pxViewHandle(), e_px_draw_item_draw_image);
#endif //DF_PIXUI_PROFILER


	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam && un_virtual_clip_count_ <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_image);
		if (p_item)
		{
			DealwithNewItem(p_item);

			((PixDrawItemDrawImage*)(p_item))->UpdateImageParam(pImage, mat, rcDraw, rcImageSrc, emRepeat, emAttachment, sliceImage, tilinColor, radius);
			BatchElement(p_item);
			p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);
		}
	}
}

void SPixPaintWidgetOld::DrawLine(
	pixui::PxViewHandle                      hDevice,
    const pixui::matrix&        mat,
    const unsigned int          unWidth,
    const pixui::BorderStyle   emLineType,
    const pixui::color          color,
    const pixui::point&         ptStart,
    const pixui::point&         ptEnd)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(pxViewHandle(), e_px_draw_item_draw_line);
#endif //DF_PIXUI_PROFILER


	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam && un_virtual_clip_count_ <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_line);
		if (p_item)
		{
			DealwithNewItem(p_item);

			((PixDrawItemDrawLine*)(p_item))->UpdateLineParam(mat, unWidth, emLineType, color, ptStart, ptEnd);
			BatchElement(p_item);
			p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);
		}
	}
}


void SPixPaintWidgetOld::DrawSlot(
	pixui::PxViewHandle hDevice,
	pixui::PxViewHandle pSlot,
				const pixui::matrix &mat,
				const pixui::position &rect)
{
#if DF_PIXUI_PROFILER
	PxpWindowTimePaintItem draw_item(pxViewHandle(), e_px_draw_item_draw_slot);
#endif //DF_PIXUI_PROFILER


	PX_FOnPaintHandlerParams *pDrawParam = (PX_FOnPaintHandlerParams *)hDevice;
	if (pDrawParam && un_virtual_clip_count_ <= 0)
	{
		auto p_item = DrawItemFromPools(e_px_draw_item_draw_slot);
		if (p_item)
		{
			DealwithNewItem(p_item);

			((PixDrawItemDrawSlot*)(p_item))->UpdateImageParam(pSlot, mat, rect);
			BatchElement(p_item);
			p_item->DrawItem(*pDrawParam, ul_CurDrawBaseLayer_);
		}
	}
}

void SPixPaintWidgetOld::OnInputText(const FString& fstrInsert, const bool b_end_input, const bool b_lost_focus, const bool b_replace)
{
    if (PxViewHandle())
    {
        PX_Plugin::PX_ViewkeyBoardInput(PxViewHandle(), TCHAR_TO_UTF8(*fstrInsert), b_end_input, b_lost_focus, b_replace);
    }
    else
    {
        PxLog_Error(" OnTextInsert PxViewHandle() inValid");
    }
}


void SPixPaintWidgetOld::PreAllPaint()
{
	e_LastBatchType_ = e_px_batch_none;
	p_last_batch_status_ = nullptr;

	ul_CurDrawBaseLayer_ = 0;

	array_clip_.Empty();
	un_virtual_clip_count_ = 0;

#if DF_PIXUI_PROFILER
	PxpTickCount::PrfWindow_Reset(pxViewHandle());
#endif //DF_PIXUI_PROFILER
}


void SPixPaintWidgetOld::EndAllPaint()
{
	if (array_clip_.Num() > 0)
		PxLog_Error("clip number was not corect,please check!!!");
}


void SPixPaintWidgetOld::DealwithNewItem(PixDrawItem* p_new_item)
{
	if (!p_root_draw_item)
	{
		p_root_draw_item = p_new_item;
	}

	if (p_cur_draw_item)
	{
		p_cur_draw_item->SetNext(p_new_item);
	}
	p_new_item->SetNext(nullptr);
	p_cur_draw_item = p_new_item;
}


PixDrawItem* SPixPaintWidgetOld::DrawItemFromPools(EPxDrawItem e_type)
{
	PixDrawItem* p_draw_item = nullptr;
	if (e_type < e_px_draw_item_count)
	{
		if (un_draw_item_pools_index[e_type] < (uint32)(ary_draw_item_pools[e_type].Num()))
		{
			p_draw_item = ary_draw_item_pools[e_type][un_draw_item_pools_index[e_type]++];
		}
		else
		{
			p_draw_item = PixDrawItem::NewDrawItem(e_type);
			if (p_draw_item)
			{
				un_draw_item_pools_index[e_type]++;
				ary_draw_item_pools[e_type].Add(p_draw_item);
			}
		}
	}
	else
	{
		PxLog_Error("SPixPaintWidgetOld::DrawItemFromPools e_type error %d", e_type);
	}
	return p_draw_item;
}


void SPixPaintWidgetOld::FreeDrawItemPools()
{
	p_root_draw_item = nullptr;
	p_cur_draw_item = nullptr;

	for (int i = 0; i < e_px_draw_item_count; i++)
	{
		un_draw_item_pools_index[i] = 0;
		for (auto p_item : ary_draw_item_pools[i])
		{
			delete p_item;
		}
		ary_draw_item_pools[i].Empty();
	}
}


void SPixPaintWidgetOld::RetainDraw(PX_FOnPaintHandlerParams& paint_param)
{
	//retain draw
	PixDrawItem* p_next = p_root_draw_item;
	
	uint32 un_paint_count = 0;
	while (p_next)
	{
#if DF_PIXUI_PROFILER
		PxpWindowTimePaintItem draw_item(pxViewHandle(), p_next->Type());
#endif //DF_PIXUI_PROFILER

		BatchElement(p_next);

		p_next->DrawItem(paint_param, ul_CurDrawBaseLayer_);
		p_next = p_next->Next();

		un_paint_count++;

		if (un_paint_count > 100000)
		{
			PxLog_Warning("SPixPaintWidgetOld::RetainDraw paint element count over 100000!!!!!!");
			break;
		}
	}
}



void SPixPaintWidgetOld::ShowDrawItemInfor()
{
	uint32 un_total_count = 0;
	for (auto i=0;i<e_px_draw_item_count;i++)
	{
		un_total_count += ary_draw_item_pools[i].Num();
	}
	PxLog_Log("SPixPaintWidgetOld  draw item total count:%d ", un_total_count);
	for (auto i = 0; i < e_px_draw_item_count; i++)
	{
		PxLog_Log("    SPixPaintWidgetOld draw item pools type:%d count:%d ", i, ary_draw_item_pools[i].Num());
	}

	for (auto i = 0; i < e_px_draw_item_count; i++)
	{
		PxLog_Log("    SPixPaintWidgetOld draw item used type:%d count:%d ", i, un_draw_item_pools_index[i]);
	}
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION


#endif // DF_PX_USE_OLD_WIDGET
