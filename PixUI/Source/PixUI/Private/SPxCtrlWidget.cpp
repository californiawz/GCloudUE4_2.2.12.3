/**************************************************

**** @file:     SPxCtrlWidget.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2022/11/02

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/

#include "SPxCtrlWidget.h"

#include "PixUIDef.h"
#include "PixUILibMgr.h"
#include "PixUILog.h"
#include "PixUtil.h"
#include "PixUIBPLibrary.h"

#if (defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)
#include "PixUIProfiler/PxpTickCount.h"
#endif //(defined(DF_PIXUI_PROFILER) && DF_PIXUI_PROFILER)

void SPxCtrlWidget::Construct(const FArguments& InArgs)
{
	mBeloackMouse = false;
	mBeActiveInput = false;
}


SPxCtrlWidget::~SPxCtrlWidget()
{

}

int32 SPxCtrlWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 nLayerId = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	return nLayerId;
}


void SPxCtrlWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{

#if DF_PIXUI_PROFILER
	PxpWindowTimeTick tick_time(PxViewId());
#endif //DF_PIXUI_PROFILER

	auto tmp_size = AllottedGeometry.GetLocalSize();

	if (tmp_size != mV2dDesiredSize)
	{
		OnSizeChange(tmp_size);
	}
	if (PixUtil::GameWorld() && PixUtil::GameWorld()->GetGameViewport())
	{
		FVector2D screen_size = PixUtil::GameWorld()->GetGameViewport()->Viewport->GetSizeXY();
		screen_size = screen_size / (AllottedGeometry.Scale > 0 ? AllottedGeometry.Scale : 1.0f);
		if (screen_size != mV2dScreenSize)
		{
			OnScreenChange(screen_size);
		}
	}
}


bool SPxCtrlWidget::SupportsKeyboardFocus() const
{
	return PxViewId() > 0;
}


FReply SPxCtrlWidget::OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent)
{
	if (PxViewId() > 0 && BeActiveInput())
	{
		TCHAR tc_input_char = InCharacterEvent.GetCharacter();
		if (tc_input_char != TEXT('\t'))
		{
			switch (tc_input_char)
			{
			case TCHAR(8):      // Backspace
			case TCHAR('\n'):   // Newline (Ctrl+Enter), we handle adding new lines via HandleCarriageReturn rather than processing newline characters
			case 1:             // Swallow Ctrl+A, we handle that through OnKeyDown
			case 3:             // Swallow Ctrl+C, we handle that through OnKeyDown
			case 13:            // Swallow Enter, we handle that through OnKeyDown
			case 22:            // Swallow Ctrl+V, we handle that through OnKeyDown
			case 24:            // Swallow Ctrl+X, we handle that through OnKeyDown
			case 25:            // Swallow Ctrl+Y, we handle that through OnKeyDown
			case 26:            // Swallow Ctrl+Z, we handle that through OnKeyDown
			case 27:            // Swallow ESC, we handle that through OnKeyDown
			case 127:           // Swallow CTRL+Backspace, we handle that through OnKeyDown
				break;
			default:
				// Type the character, but only if it is allowed.
				char szInput[2] = { 0 };
				szInput[0] = (char)tc_input_char;
				px_plugin::pxViewKeyboardInput(PxViewId(), szInput, false, false, false);
				break;
			}
		}
		return FReply::Handled();
	}
	return FReply::Unhandled();
}


FReply SPxCtrlWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (PxViewId() > 0)
	{
		if (px_plugin::pxViewKeyEvent(PxViewId()
			, PixUtil::UEKeyEventToPixUIKeyCode(InKeyEvent)
			, PixUtil::UEKeyEventToPixUIKeyModifier(InKeyEvent), true))
		{
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}


FReply SPxCtrlWidget::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (PxViewId() > 0)
	{
		//PxLog_Trace("SPxCtrlWidget::OnKeyUp keykocde:%d",InKeyEvent.GetKeyCode());
		if (px_plugin::pxViewKeyEvent(PxViewId(),
			PixUtil::UEKeyEventToPixUIKeyCode(InKeyEvent),
			PixUtil::UEKeyEventToPixUIKeyModifier(InKeyEvent), false))
		{
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}


FReply SPxCtrlWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	bool b_handle = false;
	if (PxViewId() > 0)
	{
		FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			// RIGHT BUTTON
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Right, true);
			//ue4 do not fire up when down unhandled
			if (!b_handle)
			{
				px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Right, false);
			}
		}
		else if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			//
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Left, true);
			if (!b_handle)
			{
				px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Left, false);
			}
		}
		else if (MouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton)
		{
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Middle, true);
			if (!b_handle)
			{
				px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Middle, false);
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
		mBeloackMouse = true;
		return FReply::Handled().CaptureMouse(SharedThis(this));
	}
	return FReply::Unhandled();
}


FReply SPxCtrlWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	bool b_handle = false;
	if (PxViewId() > 0)
	{
		//FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		//UE4 BUG----->up event use last pos,Because the current pos has a delay problem 
		FVector2D lastPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetLastScreenSpacePosition());
		if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), lastPos.X, lastPos.Y, 0, pixui::MouseButton::MB_Right, false);
		}
		else if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), lastPos.X, lastPos.Y, 0, pixui::MouseButton::MB_Left, false);
		}
		else if (MouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton)
		{
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), lastPos.X, lastPos.Y, 0, pixui::MouseButton::MB_Middle, false);
		}

#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnMouseButtonUp handle:%d xpos:%f ypos:%f  lastPos.x:%f  lastPos.y:%f", b_handle,
				MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()).X, MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()).Y, lastPos.X, lastPos.Y);
		}
#endif //DF_PIXUI_PROFILER

	}
	if (mBeloackMouse)
	{
		mBeloackMouse = false;
		return FReply::Handled().ReleaseMouseCapture();
	}
	return b_handle ? FReply::Handled() : FReply::Unhandled();
}


FReply SPxCtrlWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
#if PLATFORM_WINDOWS || PLATFORM_MAC
	bool b_handle = false;
	// for android platform this function always call ----> ue4 bug
	if (PxViewId() > 0)
	{
		if (mV2dLastMoveScreenPos == MouseEvent.GetScreenSpacePosition())
		{
			return FReply::Handled();
		}
		mV2dLastMoveScreenPos = MouseEvent.GetScreenSpacePosition();

		FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		if (mV2dLastMovePos != localPos)
		{
			mV2dLastMovePos = localPos;
			if (px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_None, false))
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


FReply SPxCtrlWidget::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (PxViewId() > 0)
	{
		FVector2D localPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
		if (px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, MouseEvent.GetWheelDelta(), pixui::MouseButton::MB_None, false))
		{
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}


FReply SPxCtrlWidget::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	if (PxViewId() > 0)
	{
		//pixui have no doubleClick,deal with click
		bool b_handle = false;
		FVector2D localPos = InMyGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
		if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			// RIGHT BUTTON
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Right, false);
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			//
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Left, false);
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::MiddleMouseButton)
		{
			b_handle = px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Middle, false);
		}
		//PxLog_Trace("OnMouseButtonDoubleClick handle:%d xpos:%f ypos:%f", b_handle, localPos.X, localPos.Y);
		return b_handle ? FReply::Handled() : FReply::Unhandled();
	}

	return FReply::Unhandled();
}


FReply SPxCtrlWidget::OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent)
{
	FVector2D localPos = MyGeometry.AbsoluteToLocal(GestureEvent.GetScreenSpacePosition());
	//PxLog_Trace("OnTouchGesture xpos:%f ypos:%f", localPos.X, localPos.Y);

	if (PxViewId() > 0)
	{
		return FReply::Unhandled();
	}
	return FReply::Unhandled();
}


FReply SPxCtrlWidget::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	bool b_handle = false;
	if (PxViewId() > 0)
	{
		FVector2D localPos = MyGeometry.AbsoluteToLocal(InTouchEvent.GetScreenSpacePosition());

		if (UPixUIBPLibrary::PixUI_IsMobileUseTouchEvent())
		{
			b_handle = px_plugin::pxViewTouchEvent(PxViewId(), localPos.X, localPos.Y, InTouchEvent.GetPointerIndex(), pixui::ETouchPhase::em_touch_phase_began);
			//PxLog_Trace("OnTouchStarted index:%d handle:%d xpos:%f ypos:%f", InTouchEvent.GetPointerIndex(), b_handle, localPos.X, localPos.Y);
		}
		else
		{
			//0.4 do not need PX_ViewMouseEvent
			b_handle |= px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_Left, true);
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
		mBeloackMouse = true;
		return FReply::Handled().CaptureMouse(SharedThis(this));
	}
	return FReply::Unhandled();
}


FReply SPxCtrlWidget::OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	bool b_handle = false;
	if (PxViewId() > 0)
	{
		if (mV2dLastMoveScreenPos == InTouchEvent.GetScreenSpacePosition())
		{
			return FReply::Handled();
		}
		mV2dLastMoveScreenPos = InTouchEvent.GetScreenSpacePosition();

		FVector2D localPos = MyGeometry.AbsoluteToLocal(InTouchEvent.GetScreenSpacePosition());
		///////////////////////////////////////////////////
		if (mV2dLastMovePos != localPos)
		{
			mV2dLastMovePos = localPos;
			if (UPixUIBPLibrary::PixUI_IsMobileUseTouchEvent())
			{
				if (px_plugin::pxViewTouchEvent(PxViewId(), localPos.X, localPos.Y, InTouchEvent.GetPointerIndex(), pixui::ETouchPhase::em_touch_phase_moved))
				{
					b_handle = true;
				}
			}
			else
			{
				if (px_plugin::pxViewMouseEvent(PxViewId(), localPos.X, localPos.Y, 0, pixui::MouseButton::MB_None, false))
				{
					b_handle = true;
				}
			}
		}

#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnTouchMoved index:%d handle:%d xpos:%f ypos:%f  last.x:%f last.y:%f  mV2dLastMoveScreenPos.x %f mV2dLastMoveScreenPos.y: %f last_screen_pos.x:%f last_screen_pos.y:%f",
				InTouchEvent.GetPointerIndex(), b_handle, localPos.X, localPos.Y, mV2dLastMovePos.X, mV2dLastMovePos.Y,
				mV2dLastMoveScreenPos.X, mV2dLastMoveScreenPos.Y,
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


FReply SPxCtrlWidget::OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	bool b_handle = false;
	if (PxViewId() > 0)
	{
		//FVector2D localPos = MyGeometry.AbsoluteToLocal(InTouchEvent.GetScreenSpacePosition());
		//UE4 BUG----->up event use last pos,Because the current pos has a delay problem 
		FVector2D lastPos = MyGeometry.AbsoluteToLocal(InTouchEvent.GetLastScreenSpacePosition());

		if (UPixUIBPLibrary::PixUI_IsMobileUseTouchEvent())
		{
			b_handle = px_plugin::pxViewTouchEvent(PxViewId(), lastPos.X, lastPos.Y, InTouchEvent.GetPointerIndex(), pixui::ETouchPhase::em_touch_phase_ended);
			//PxLog_Trace("OnTouchEnded index:%d handle:%d lastPos xpos:%f lastPos ypos:%f", InTouchEvent.GetPointerIndex(), b_handle, lastPos.X, lastPos.Y);
		}
		else
		{
			//0.4 do not need PX_ViewMouseEvent
			b_handle |= px_plugin::pxViewMouseEvent(PxViewId(), lastPos.X, lastPos.Y, 0, pixui::MouseButton::MB_Left, false);
		}

#if DF_PIXUI_PROFILER
		if (UPixUIBPLibrary::PixUI_IsShowMousePos())
		{
			PxLog_Log("mousepos OnTouchEnded index:%d handle:%d lastPos xpos:%f lastPos ypos:%f", InTouchEvent.GetPointerIndex(), b_handle, lastPos.X, lastPos.Y);
		}
#endif //DF_PIXUI_PROFILER
	}

	if (mBeloackMouse)
	{
		mBeloackMouse = false;
		return FReply::Handled().ReleaseMouseCapture();
	}
	return b_handle ? FReply::Handled() : FReply::Unhandled();
}


FReply SPxCtrlWidget::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	SCompoundWidget::OnFocusReceived(MyGeometry, InFocusEvent);
	PxLog_Trace("SPxCtrlWidget::OnFocusReceived ~");
	return FReply::Handled();
}


void SPxCtrlWidget::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	SCompoundWidget::OnFocusLost(InFocusEvent);
	PxLog_Trace("SPxCtrlWidget::OnFocusLost ~");
}


void SPxCtrlWidget::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	SCompoundWidget::OnMouseEnter(MyGeometry, MouseEvent);
	// PxLog_Trace("SPxCtrlWidget::OnMouseEnter ~");
}


void SPxCtrlWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	SCompoundWidget::OnMouseLeave(MouseEvent);
	// PxLog_Trace("SPxCtrlWidget::OnMouseLeave ~");
}


bool SPxCtrlWidget::IsInteractable() const
{
	// PxLog_Trace("SPxCtrlWidget::IsInteractable ~");

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


void SPxCtrlWidget::OnSizeChange(const FVector2D& v2d_NewSize)
{
	//b_GeometryInit_ = true;
	mV2dDesiredSize = v2d_NewSize;
	if (PxViewId() > 0)
	{
		px_plugin::pxViewWinSizeUpdate(PxViewId(), mV2dDesiredSize.X, mV2dDesiredSize.Y);
	}
}

void SPxCtrlWidget::OnScreenChange(const FVector2D& v2d_NewSize)
{
	mV2dScreenSize = v2d_NewSize;
	if (PxViewId() > 0)
	{
		px_plugin::pxViewScreenSizeUpdate(PxViewId(), mV2dScreenSize.X, mV2dScreenSize.Y);
	}
}