/**************************************************

**** @file:     PixUtil.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/11

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixUtil.h"


#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#endif //WITH_EDITOR

#include "Engine/GameViewportClient.h"

#include "SlateOptMacros.h"
#include "Engine/Font.h"
#include "Engine/FontFace.h"
#include "Engine/UserInterfaceSettings.h"

#include "PixUILog.h"


UWorld* PixUtil::GameWorld()
{
#if WITH_EDITOR
    UUnrealEdEngine* GameEngine = Cast<UUnrealEdEngine>(GEngine);
    UWorld* World = GameEngine ? GameEngine->PlayWorld : nullptr;
#else
    UGameEngine* GameEngine = Cast<UGameEngine>(GEngine);
    UWorld* World = GameEngine ? GameEngine->GetGameWorld() : nullptr;
#endif //WITH_EDITOR

    return World;
}


bool PixUtil::IsGamePlay()
{
    return GameWorld() ? true : false;
}


bool PixUtil::IsInEditor()
{
#if WITH_EDITOR
    return true;
#else
    return false;
#endif //WITH_EDITOR
}


bool PixUtil::IsShippingEnv()
{
#if UE_BUILD_SHIPPING
    return true;
#else
    return false;
#endif //UE_BUILD_SHIPPING
}



bool PixUtil::IsDevEnv()
{
#if UE_BUILD_DEVELOPMENT
    return true;
#else
    return false;
#endif //UE_BUILD_SHIPPING
}


bool PixUtil::IsDebugEnv()
{
#if UE_BUILD_DEBUG
    return true;
#else
    return false;
#endif //UE_BUILD_SHIPPING
}


void PixUtil::EngineGC(bool bForcePurge /*= false*/)
{
    //GEngine GC
    if (GEngine)
    {
        GEngine->ForceGarbageCollection(bForcePurge);
    }
}


float PixUtil::SlateScaleRate()
{
	float slate_scale = 1.0f;

	if (GEngine && GEngine->GameViewport)
	{
		FIntPoint ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
		slate_scale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(ViewportSize);
	}
	return slate_scale;
#if ENGINE_MAJOR_VERSION < 5

	/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 20 //GetApplicationScale support
	return (GEngine && GEngine->GameViewport) ? GEngine->GameViewport->Viewport->GetClient()->GetDPIScale() : 1.0f;
#else
	return FSlateApplication::Get().GetApplicationScale();
#endif //ENGINE_MINOR_VERSION > 20
	/////////////////////////////////////////////////////////////////////for ue4

#else

	/////////////////////////////////////////////////////////////////////for ue5
	return (GEngine && GEngine->GameViewport) ? GEngine->GameViewport->Viewport->GetClient()->GetDPIScale() : 1.0f;
	/////////////////////////////////////////////////////////////////////for ue5

#endif //ENGINE_MAJOR_VERSION < 5
}



uint32 PixUtil::PtToPix(const uint32 unPt)
{
    //96 dpi 1px = 1/96inch 1pt=1/72inch  1px=0.75pt
    //slat Units is done at 96 dpi
    //px = pt * DPI / 72
    //UE4_96DPI_Scale = GEngine->GameViewport->Viewport->GetClient()->GetDPIScale();

    //UE4_FontSize = PS_72DPI_FontSize * 72DPI/96DPI / UE4_96DPI_Scale
    return  (uint32)(unPt / 0.75f);
}


uint32 PixUtil::PixToPt(const uint32 unPixel)
{
    //96 dpi 1px=1/96inch 1pt=1/72inch  1px=0.75pt
    //slat Units is done at 96 dpi
    //px = pt * DPI / 72
    //static float fScale = 1.0;
    //return  (int)(nPt / 0.75 * fScale);
    return (uint32)(unPixel * 0.75f);
}


FColor PixUtil::PixColor2FColor(const pixui::color& InColor)
{
    return FColor(InColor.red(), InColor.green(), InColor.blue(), InColor.alpha());
}


pixui::EKeyCode PixUtil::UEKeyEventToPixUIKeyCode(const FKeyEvent& InKeyEvent)
{
#if PLATFORM_MAC
    return pixui::EKeyCode(PixUtil::MacKeyCodeToPixKeyCode(InKeyEvent.GetKeyCode()));
#elif PLATFORM_WINDOWS
    return pixui::EKeyCode(PixUtil::WinKeyCodeToPixKeyCode(InKeyEvent.GetKeyCode()));
#elif PLATFORM_ANDROID
    return pixui::EKeyCode(PixUtil::AndroidKeyCodeToPixKeyCode(InKeyEvent.GetKeyCode()));
#else
    return pixui::EKeyCode(InKeyEvent.GetKeyCode());
#endif
}


unsigned char PixUtil::UEKeyEventToPixUIKeyModifier(const FKeyEvent& InKeyEvent)
{
    unsigned char uc_PxKeyModify = 0;

    if (InKeyEvent.IsLeftCommandDown())
    {
        uc_PxKeyModify |= pixui::EKeyModifier::KM_LeftMeta;
    }
    if (InKeyEvent.IsRightCommandDown())
    {
        uc_PxKeyModify |= pixui::EKeyModifier::KM_RightMeta;
    }
    if (InKeyEvent.IsLeftAltDown())
    {
        uc_PxKeyModify |= pixui::EKeyModifier::KM_LeftAlt;
    }
    if (InKeyEvent.IsRightAltDown())
    {
        uc_PxKeyModify |= pixui::EKeyModifier::KM_RightAlt;
    }
    if (InKeyEvent.IsLeftControlDown())
    {
        uc_PxKeyModify |= pixui::EKeyModifier::KM_LeftCtrl;
    }
    if (InKeyEvent.IsRightControlDown())
    {
        uc_PxKeyModify |= pixui::EKeyModifier::KM_RightCtrl;
    }
    return uc_PxKeyModify;
}


uint32 PixUtil::WinKeyCodeToPixKeyCode(const uint32 unWinKeyCode)
{
    return unWinKeyCode;
}


uint32 PixUtil::MacKeyCodeToPixKeyCode(const uint32 unMacKeyCode)
{
    //unMacKeyCode mac keycode
    uint32 unOutKeyCode = pixui::None;
    switch (unMacKeyCode)
    {
    case 0: //0 0x00 ANSI_A
        unOutKeyCode = pixui::KeyA;
        break;
    case 1: //1 0x01 ANSI_S
        unOutKeyCode = pixui::KeyS;
        break;
    case 2: //2 0x02 ANSI_D
        unOutKeyCode = pixui::KeyD;
        break;
    case 3: //3 0x03 ANSI_F
        unOutKeyCode = pixui::KeyF;
        break;
    case 4: //4 0x04 ANSI_H
        unOutKeyCode = pixui::KeyH;
        break;
    case 5: //5 0x05 ANSI_G
        unOutKeyCode = pixui::KeyG;
        break;
    case 6: //6 0x06 ANSI_Z
        unOutKeyCode = pixui::KeyZ;
        break;
    case 7: //7 0x07 ANSI_X
        unOutKeyCode = pixui::KeyX;
        break;
    case 8: //8 0x08 ANSI_C
        unOutKeyCode = pixui::KeyC;
        break;
    case 9: //9 0x09 ANSI_V
        unOutKeyCode = pixui::KeyV;
        break;
    case 10: //10 0x0A ISO_Section
        unOutKeyCode = 0;
        break;
    case 11: //11 0x0B ANSI_B
        unOutKeyCode = pixui::KeyB;
        break;
    case 12: //12 0x0C ANSI_Q
        unOutKeyCode = pixui::KeyQ;
        break;
    case 13: //13 0x0D ANSI_W
        unOutKeyCode = pixui::KeyW;
        break;
    case 14: //14 0x0E ANSI_E
        unOutKeyCode = pixui::KeyE;
        break;
    case 15: //15 0x0F ANSI_R
        unOutKeyCode = pixui::KeyR;
        break;
    case 16: //16 0x10 ANSI_Y
        unOutKeyCode = pixui::KeyY;
        break;
    case 17: //17 0x11 ANSI_T
        unOutKeyCode = pixui::KeyT;
        break;
    case 18: //18 0x12 ANSI_1
        unOutKeyCode = pixui::Key1;
        break;
    case 19: //19 0x13 ANSI_2
        unOutKeyCode = pixui::Key2;
        break;
    case 20: //20 0x14 ANSI_3
        unOutKeyCode = pixui::Key3;
        break;
    case 21: //21 0x15 ANSI_4
        unOutKeyCode = pixui::Key4;
        break;
    case 22: //22 0x16 ANSI_6
        unOutKeyCode = pixui::Key6;
        break;
    case 23: //23 0x17 ANSI_5
        unOutKeyCode = pixui::Key5;
        break;
    case 24: //24 0x18 ANSI_Equal
        unOutKeyCode = pixui::EqualSign;
        break;
    case 25: //25 0x19 ANSI_9
        unOutKeyCode = pixui::Key9;
        break;
    case 26: //26 0x1A ANSI_7
        unOutKeyCode = pixui::Key7;
        break;
    case 27: //27 0x1B ANSI_Minus
        unOutKeyCode = pixui::Dash;
        break;
    case 28: //28 0x1C ANSI_8
        unOutKeyCode = pixui::Key8;
        break;
    case 29: //29 0x1D ANSI_0
        unOutKeyCode = pixui::Key0;
        break;
    case 30: //30 0x1E ANSI_RightBracket
        unOutKeyCode = pixui::CloseBracket;
        break;
    case 31: //31 0x1F ANSI_O
        unOutKeyCode = pixui::KeyO;
        break;
    case 32: //32 0x20 ANSI_U
        unOutKeyCode = pixui::KeyU;
        break;
    case 33: //33 0x21 ANSI_LeftBracket
        unOutKeyCode = pixui::OpenBracket;
        break;
    case 34: //34 0x22 ANSI_I
        unOutKeyCode = pixui::KeyI;
        break;
    case 35: //35 0x23 ANSI_P
        unOutKeyCode = pixui::KeyP;
        break;
    case 36: //36 0x24 Return
        unOutKeyCode = pixui::Enter;
        break;
    case 37: //37 0x25 ANSI_L
        unOutKeyCode = pixui::KeyL;
        break;
    case 38: //38 0x26 ANSI_J
        unOutKeyCode = pixui::KeyJ;
        break;
    case 39: //39 0x27 ANSI_Quote
        unOutKeyCode = pixui::SingleQuote;
        break;
    case 40: //40 0x28 ANSI_K
        unOutKeyCode = pixui::KeyK;
        break;
    case 41: //41 0x29 ANSI_Semicolon
        unOutKeyCode = pixui::Semicolon;
        break;
    case 42: //42 0x2A ANSI_Backslash
        unOutKeyCode = pixui::Backslash;
        break;
    case 43: //43 0x2B ANSI_Comma
        unOutKeyCode = pixui::Comma;
        break;
    case 44: //44 0x2C ANSI_Slash
        unOutKeyCode = pixui::ForwardSlash;
        break;
    case 45: //45 0x2D ANSI_N
        unOutKeyCode = pixui::KeyN;
        break;
    case 46: //46 0x2E ANSI_M
        unOutKeyCode = pixui::KeyM;
        break;
    case 47: //47 0x2F ANSI_Period
        unOutKeyCode = pixui::Period;
        break;
    case 48: //48 0x30 Tab
        unOutKeyCode = pixui::Tab;
        break;
    case 49: //49 0x31 Space
        unOutKeyCode = pixui::Space;
        break;
    case 50: //50 0x32 ANSI_Grave
        unOutKeyCode = pixui::GraveAccent;
        break;
    case 51: //51 0x33 Delete
        unOutKeyCode = pixui::Backspace;
        break;
    case 53: //53 0x35 Escape
        unOutKeyCode = pixui::Esc;
        break;
    case 55: //55 0x37(test is 63317) Command
        unOutKeyCode = pixui::CommandKeyLeft;
        break;
    case 63317: //(test is 63317) Command
        unOutKeyCode = pixui::CommandKeyLeft;
        break;
    case 63316: //(test is 63316) Right Command
        unOutKeyCode = pixui::CommandKeyRight;
        break;
    case 56: //56 0x38(test is 63318) Shift
        unOutKeyCode = pixui::Shift;
        break;
    case 63318: //(test is 63318) Shift
        unOutKeyCode = pixui::Shift;
        break;
    case 57: //57 0x39(test is 63319) CapsLock
        unOutKeyCode = pixui::CapsLock;
        break;
    case 63319: //(test is 63319) CapsLock
        unOutKeyCode = pixui::CapsLock;
        break;
    case 58: //58 0x3A(test is 63320) Option
        unOutKeyCode = pixui::Alt;
        break;
    case 63320: //(test is 63320) Option
        unOutKeyCode = pixui::Alt;
        break;
    case 59: //59 0x3B(test is 63321) Control
        unOutKeyCode = pixui::Ctrl;
        break;
    case 63321: //(test is 63321) Control
        unOutKeyCode = pixui::Ctrl;
        break;
    case 60: //60 0x3C(test is 63328) RightShift
        unOutKeyCode = pixui::RightShift;
        break;
    case 63328: //(test is 63328) RightShift
        unOutKeyCode = pixui::RightShift;
        break;
    case 61: //61 0x3D(test is 63329) RightOption
        unOutKeyCode = pixui::RightAlt;
        break;
    case 63329: //(test is 63329) RightOption
        unOutKeyCode = pixui::RightAlt;
        break;
    case 62: //62 0x3E(test is 63330) RightControl
        unOutKeyCode = pixui::RightCtrl;
        break;
    case 63330: //(test is 63330) RightControl
        unOutKeyCode = pixui::RightCtrl;
        break;
    case 63: //63 0x3F Function
        unOutKeyCode = pixui::Function;
        break;
    case 64: //64 0x40 F17
        unOutKeyCode = pixui::F17;
        break;
    case 65: //65 0x41 ANSI_KeypadDecimal
        unOutKeyCode = pixui::PadDecimal;
        break;
    case 67: //67 0x43 ANSI_KeypadMultiply
        unOutKeyCode = pixui::PadMultiply;
        break;
    case 69: //69 0x45 ANSI_KeypadPlus
        unOutKeyCode = pixui::PadPlus;
        break;
    case 71: //71 0x47 ANSI_KeypadClear
        unOutKeyCode = pixui::PadClear;
        break;
    case 72: //72 0x48 VolumeUp
        unOutKeyCode = pixui::VolumeUp;
        break;
    case 73: //73 0x49 VolumeDown
        unOutKeyCode = pixui::VolumeDown;
        break;
    case 74: //74 0x4A Mute
        unOutKeyCode = pixui::Mute;
        break;
    case 75: //75 0x4B ANSI_KeypadDivide
        unOutKeyCode = pixui::PadDivide;
        break;
    case 76: //76 0x4C ANSI_KeypadEnter
        unOutKeyCode = pixui::PadEnter;
        break;
    case 78: //78 0x4E ANSI_KeypadMinus
        unOutKeyCode = pixui::PadMinus;
        break;
    case 79: //79 0x4F F18
        unOutKeyCode = pixui::F18;
        break;
    case 80: //80 0x50 F19
        unOutKeyCode = pixui::F19;
        break;
    case 81: //81 0x51 ANSI_KeypadEquals
        unOutKeyCode = pixui::PadEquals;
        break;
    case 82: //82 0x52 ANSI_Keypad0
        unOutKeyCode = pixui::PadNum0;
        break;
    case 83: //83 0x53 ANSI_Keypad1
        unOutKeyCode = pixui::PadNum1;
        break;
    case 84: //84 0x54 ANSI_Keypad2
        unOutKeyCode = pixui::PadNum2;
        break;
    case 85: //85 0x55 ANSI_Keypad3
        unOutKeyCode = pixui::PadNum3;
        break;
    case 86: //86 0x56 ANSI_Keypad4
        unOutKeyCode = pixui::PadNum4;
        break;
    case 87: //87 0x57 ANSI_Keypad5
        unOutKeyCode = pixui::PadNum5;
        break;
    case 88: //88 0x58 ANSI_Keypad6
        unOutKeyCode = pixui::PadNum6;
        break;
    case 89: //89 0x59 ANSI_Keypad7
        unOutKeyCode = pixui::PadNum7;
        break;
    case 90: //90 0x5A F20
        unOutKeyCode = pixui::F20;
        break;
    case 91: //91 0x5B ANSI_Keypad8
        unOutKeyCode = pixui::PadNum8;
        break;
    case 92: //92 0x5C ANSI_Keypad9
        unOutKeyCode = pixui::PadNum9;
        break;
    case 93: //93 0x5D JIS_Yen
        unOutKeyCode = 0;
        break;
    case 94: //94 0x5E JIS_Underscore
        unOutKeyCode = 0;
        break;
    case 95: //95 0x5F JIS_KeypadComma
        unOutKeyCode = 0;
        break;
    case 96: //96 0x60 F5
        unOutKeyCode = pixui::F5;
        break;
    case 97: //97 0x61 F6
        unOutKeyCode = pixui::F6;
        break;
    case 98: //98 0x62 F7
        unOutKeyCode = pixui::F7;
        break;
    case 99: //99 0x63 F3
        unOutKeyCode = pixui::F3;
        break;
    case 100: //100 0x64 F8
        unOutKeyCode = pixui::F8;
        break;
    case 101: //101 0x65 F9
        unOutKeyCode = pixui::F9;
        break;
    case 102: //102 0x66 JIS_Eisu
        unOutKeyCode = 0;
        break;
    case 103: //103 0x67 F11
        unOutKeyCode = pixui::F11;
        break;
    case 104: //104 0x68 JIS_Kana
        unOutKeyCode = 0;
        break;
    case 105: //105 0x69 F13
        unOutKeyCode = pixui::F13;
        break;
    case 106: //106 0x6A F16
        unOutKeyCode = pixui::F16;
        break;
    case 107: //107 0x6B F14
        unOutKeyCode = pixui::F14;
        break;
    case 109: //109 0x6D F10
        unOutKeyCode = pixui::F10;
        break;
    case 111: //111 0x6F F12
        unOutKeyCode = pixui::F12;
        break;
    case 113: //113 0x71 F15
        unOutKeyCode = pixui::F15;
        break;
    case 114: //114 0x72 Help
        unOutKeyCode = 0;
        break;
    case 115: //115 0x73 Home
        unOutKeyCode = pixui::Home;
        break;
    case 116: //116 0x74 PageUp
        unOutKeyCode = pixui::PageUp;
        break;
    case 117: //117 0x75 ForwardDelete
        unOutKeyCode = pixui::Delete;
        break;
    case 118: //118 0x76 F4
        unOutKeyCode = pixui::F4;
        break;
    case 119: //119 0x77 End
        unOutKeyCode = pixui::End;
        break;
    case 120: //120 0x78 F2
        unOutKeyCode = pixui::F2;
        break;
    case 121: //121 0x79 PageDown
        unOutKeyCode = pixui::PageDown;
        break;
    case 122: //122 0x7A F1
        unOutKeyCode = pixui::F1;
        break;
    case 123: //123 0x7B LeftArrow
        unOutKeyCode = pixui::Left;
        break;
    case 124: //124 0x7C RightArrow
        unOutKeyCode = pixui::Right;
        break;
    case 125: //125 0x7D DownArrow
        unOutKeyCode = pixui::Down;
        break;
    case 126: //126 0x7E UpArrow
        unOutKeyCode = pixui::Up;
        break;
    default:
        //unOutKeyCode = pixui::None;
        {
            PxLog_Warning("TransformMacKeyCodeToPixKeyCode unknow mac keycode:%d", unMacKeyCode);
        }
        break;
    }

    return unOutKeyCode;
}

uint32 PixUtil::AndroidKeyCodeToPixKeyCode(const uint32 unAndroidKeyCode)
{
    uint32 unOutKeyCode = pixui::None;
    switch (unAndroidKeyCode)
    {
        case 66:
            unOutKeyCode = pixui::Enter;
            break;
        default:
            //unOutKeyCode = pixui::None;
            {
                PxLog_Warning("TransformMacKeyCodeToPixKeyCode unknow mac keycode:%d", unAndroidKeyCode);
            }
            break;;
    }
    return unOutKeyCode;
}

EPixelFormat PixUtil::PixUIPixelFormatToUEPixelFormat(const pixui::EPixelFormat em_PixelFormat)
{
	switch (em_PixelFormat)
	{
	case pixui::em_pf_rgba32:
		return EPixelFormat::PF_R8G8B8A8;
// 	case pixui::em_pf_rgb24:
// 		return EPixelFormat::PF_Unknown;
// 	case pixui::em_pf_etc1_rgb:
// 		return EPixelFormat::PF_ETC2_RGB;
// 	case pixui::em_pf_etc2_rgba:
// 		return EPixelFormat::PF_ETC2_RGBA;
// 	case pixui::em_pf_bc1_rgb:
// 		return EPixelFormat::PF_DXT1;
// 	case pixui::em_pf_bc3_rgba:
// 		return EPixelFormat::PF_DXT5;
// 	case pixui::em_pf_bc7_rgba:
// 		return EPixelFormat::PF_BC7;
// 	case pixui::em_pf_astc_4x4_rgba:
// 		return EPixelFormat::PF_ASTC_4x4;
// 	case pixui::em_pf_invalid: ;
	default:
		return EPixelFormat::PF_Unknown;
	}
}

int PixUtil::GetBitsPerBlock(EPixelFormat Format)
{
	switch (Format)
	{
	case PF_R8G8B8A8:
		return 32;
	case PF_ASTC_4x4:
	case PF_DXT5:
	case PF_BC7:
	case PF_ETC2_RGBA:
		return 128;
	case PF_ETC2_RGB:
	case PF_DXT1:
		return 64;
	default:
		return 32;
	}
}

int PixUtil::GetBlockSize(EPixelFormat Format)
{
	switch (Format)
	{
	case PF_R8G8B8A8:
		return 1;
	case PF_ASTC_4x4:
	case PF_DXT5:
	case PF_BC7:
	case PF_ETC2_RGBA:
	case PF_ETC2_RGB:
	case PF_DXT1:
		return 4;
	default:
		return 1;
	}
}

void PixUtil::CalcTextureGpuSize(EPixelFormat Format, int Width, int Height, int& GpuWidth, int& GpuHeight, int& GpuDataSize)
{
	int blockSize = GetBlockSize(Format);
	int xBlocks = (Width + (blockSize - 1)) / blockSize;
	int yBlocks = (Height + (blockSize - 1)) / blockSize;
	GpuWidth = xBlocks * blockSize;
	GpuHeight = yBlocks * blockSize;
	int bitsPerBlock = GetBitsPerBlock(Format);
	int bytesPerBlock = bitsPerBlock / 8;
	GpuDataSize = xBlocks * yBlocks * bytesPerBlock;
}

static uint32 un_base_id_s = 0;

static TArray<uint32> ary_free_s;

uint32 PixUtil::NewId()
{
	if (ary_free_s.Num() > 0)
	{
		return ary_free_s.Pop();
	}
	return ++un_base_id_s;
}

void PixUtil::FreeId(uint32 un_id)
{
	ary_free_s.Push(un_id);
}


size_t PixUtil::UTF32toUTF8(uint32 un_utf32_char, uint8* p_out_utf8)
{
	if (un_utf32_char == 0)
		return 0;
	static const uint8 PREFIX[] = { 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
	static const uint32 CODE_UP[] =
	{
		0x80,           // U+00000000 - U+0000007F
		0x800,          // U+00000080 - U+000007FF
		0x10000,        // U+00000800 - U+0000FFFF
		0x200000,       // U+00010000 - U+001FFFFF
		0x4000000,      // U+00200000 - U+03FFFFFF
		0x80000000      // U+04000000 - U+7FFFFFFF
	};
	size_t i, len = sizeof(CODE_UP) / sizeof(uint32);
	for (i = 0; i < len; ++i)
		if (un_utf32_char < CODE_UP[i]) break;
	if (i == len) return 0; // the src is invalid
	len = i + 1;
	if (p_out_utf8)
	{
		for (; i > 0; --i)
		{
			p_out_utf8[i] = static_cast<uint8>((un_utf32_char & 0x3F) | 0x80);
			un_utf32_char >>= 6;
		}
		p_out_utf8[0] = static_cast<uint8>(un_utf32_char | PREFIX[len - 1]);
	}
	return len;
}