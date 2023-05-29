#pragma once
//for base type define

#include "hf.h"

#include <math.h>
#include <string.h>
#include <algorithm>

#define LINK_EXTERNAL_DEF(name) int link_symbel_##name = 0;
#define LINK_EXTERNAL_DECLARE(name) extern int link_symbel_##name;
#define LINK_SYMBOL(name) link_symbel_##name

#define FLOAT_EPSILON 1.192092896e-07F
#define FLOAT_MAX 3.402823466e+38F
#define FLOAT_MIN 1.175494351e-38F
#define PIX_PI 3.1415926f
#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr)   \
	{                      \
		if (ptr)           \
		{                  \
			delete ptr;    \
			ptr = nullptr; \
		}                  \
	}
#endif
#define FLOAT_EQ(a, b) (fabs(a - b) < FLOAT_EPSILON)

#define HF_MACRO_EXPAND(va_args) va_args
#define HF_FIRST_ARG_1(FIRST, ...) FIRST
#define HF_FIRST_ARG(...) HF_MACRO_EXPAND(HF_FIRST_ARG_1(__VA_ARGS__))

namespace pixui
{
	//for project common types define
	//byte
	typedef unsigned char byte;

	//int8
	typedef char int8;

	//uint8
	typedef unsigned char uint8;

	typedef short int16;
	typedef unsigned short uint16;

	//uint
	typedef unsigned int uint;

	//uint32
	typedef unsigned int uint32;
	typedef int int32;

	//uint64
	typedef unsigned long long uint64;

	//int64
	typedef long long int64;

	//uint_ptr
	typedef uint *uint_ptr;

#ifdef _WIN32
	typedef float float16;
#else
	//#define WITH_FP16
	//typedef __fp16 float16;
	typedef float float16;
#endif


	//log level
	enum ELogLevel
	{
		em_ll_log,
		em_ll_debug,
		em_ll_warning,
		em_ll_error,

		//for count
		em_ll_count
	};

	//log group
	enum ELogGroup
	{
		em_lg_generic,
		em_lg_script,
	};

	enum ImageFlag
	{
		IMAGE_OWNDATA = 1 << 0,// data in CreateFunction is owned by you, need not copy again
	};

	///////////////////////////////////////////////////////
	enum MouseButton
	{
		MB_None = 0,
		MB_Left = 1,
		MB_Middle = 2,
		MB_Right = 4,
		MB_Count
	};

	struct MouseEvent {
		float mx, my, mz, mw;
		int button;

		MouseEvent() : mx(0.0f), my(0.0f), mz(0.0f), mw(0.0f), button(0) {}
		MouseEvent(float x, float y, float z, float w, int b) : mx(x), my(y), mz(z), mw(w), button(b) {}

		bool isLeftDown() const { return (button & MB_Left) != 0; }
		bool isRightDown() const { return (button & MB_Right) != 0; }
		bool isDown() const
		{
			return (button & (MB_Left | MB_Right)) != 0;
		};
	};

	enum ETouchPhase
	{
		em_touch_phase_began,
		em_touch_phase_moved,
		em_touch_phase_stationary,
		em_touch_phase_ended,
		em_touch_phase_canceld,
	};

	struct TouchData {
		enum
		{
			max_touch_count = 10,
		};
		int fingerId;
		float x, y;
		ETouchPhase phase;

		static int toPointerId(int fingerId)
		{
			return fingerId + 1;
		}
	};

	enum EKeyModifier
	{
		KM_None = 0,
		KM_LeftAlt = 0x01,
		KM_RightAlt = 0x02,
		KM_LeftCtrl = 0x04,
		KM_RightCtrl = 0x08,
		KM_LeftShift = 0x10,
		KM_RightShift = 0x20,
		KM_LeftMeta = 0x40,
		KM_RightMeta = 0x80,
	};

	enum EKeyCode
	{
		None = 0,

		Backspace = 8,//Backspace
		Tab = 9,	  //Tab
		Enter = 13,	  //Enter or mac Return

		Pause = 19,	  //Pause / Break
		CapsLock = 20,//Caps Lock
		Esc = 27,	  //Esc
		Space = 32,	  //Space
		PageUp = 33,  //Page Up
		PageDown = 34,//Page Down
		End = 35,	  //End
		Home = 36,	  //Home
		Left = 37,	  //Left Arrow
		Up = 38,	  //Up Arrow
		Right = 39,	  //Right Arrow
		Down = 40,	  //Down Arrow

		PrintScreen = 44,//Print Screen / SysRq
		Insert = 45,	 //insert
		Delete = 46,	 //Delete

		Key0 = 48,//key code:48
		Key1,
		Key2,
		Key3,
		Key4,
		Key5,
		Key6,
		Key7,
		Key8,
		Key9,//key code:57

		KeyA = 65,//key code:65
		KeyB,
		KeyC,
		KeyD,
		KeyE,
		KeyF,
		KeyG,
		KeyH,
		KeyI,
		KeyJ,
		KeyK,
		KeyL,
		KeyM,
		KeyN,
		KeyO,
		KeyP,
		KeyQ,
		KeyR,
		KeyS,
		KeyT,
		KeyU,
		KeyV,
		KeyW,
		KeyX,
		KeyY,
		KeyZ,//key code:90

		CommandKeyLeft = 91, // Left Windows Key /  mac left Command ⌘
		CommandKeyRight = 92,// Right Windows Key /  mac Right Command ⌘
		MenuKeyRight = 93,	 // Windows Menu

		PadNum0 = 96,//key code:96
		PadNum1,
		PadNum2,
		PadNum3,
		PadNum4,
		PadNum5,
		PadNum6,
		PadNum7,
		PadNum8,
		PadNum9,//key code:105

		PadMultiply = 106,//Numpad *
		PadPlus = 107,	  //Numpad +
		PadEnter = 13,	  //Numpad Enter
		PadMinus = 109,	  //Numpad Minus (-)
		PadDecimal = 110, //Numpad Decimal Point (.)
		PadDivide = 111,  //Numpad Divide (/)

		F1 = 112,//key code:112
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,//key code:123
		F13,//key code:124
		F14,//key code:125
		F15,//key code:126
		F16,//key code:127
		F17,//key code:128
		F18,//key code:129
		F19,//key code:130
		F20,//key code:131

		PadClear = 136, // mac keypad clear (pixui made)
		PadEquals = 137,// mac keypad equals (pixui made)

		NumLock = 144,	 //NumLock
		ScrollLock = 145,//ScrollLock

		Shift = 160,	 //left shift
		RightShift = 161,//right shift

		Ctrl = 162,		//left Ctrl
		RightCtrl = 163,//right Ctrl

		Alt = 164,	   //left  window alt or mac option
		RightAlt = 165,//right window alt or mac option

		VolumeDown = 174,//Decrease Volume Level
		VolumeUp = 175,	 //Increase Volume Level
		Next = 176,		 //Next
		Previous = 177,	 //Previous
		Stop = 178,		 //Stop
		PlayPause = 179, //Play / Pause
		Mute = 181,		 //Mute / Unmute

		Semicolon = 186,   //Semi-colon (; :)
		EqualSign = 187,   //Equal Sign (= +)
		Comma = 188,	   //Comma (, <)
		Dash = 189,		   //Dash (- _)
		Period = 190,	   //Period (. >)
		ForwardSlash = 191,//Forward Slash (/ ?)
		GraveAccent = 192, //Grave Accent (` ~)

		OpenBracket = 219, //Open Bracket ([ {)
		Backslash = 220,   //Backslash (\ |)
		CloseBracket = 221,//Close Bracket (] })
		SingleQuote = 222, //Single Quote (” ‘)

		Function = 195,//mac fn/funtion (pixui made)

		//pixui custom define for Console Gamepad (pixui made)
		GamepadA = 201,
		GamepadB,
		GamepadX,
		GamepadY,
		GamepadThumbL,
		GamepadThumbR,
		GamepadShoulderL,
		GamepadShoulderR,
		GamepadUp,
		GamepadDown,
		GamepadLeft,
		GamepadRight,
		GamepadBack,
		GamepadStart,
		GamepadGuide,//key code:215

		//Count
	};

	//keyboard type for mobile platform
	enum EKeyboardType
	{
		em_Keyboard_Default,
		em_Keyboard_Number,
		em_Keyboard_Password
	};


	//image type default R8G8B8A8
	enum EPixelFormat
	{
		em_pf_rgba32
	};

	enum BackgroundAttachment
	{
		background_attachment_scroll,
		background_attachment_fixed
	};

	enum BackgroundRepeat
	{
		background_repeat_repeat,
		background_repeat_repeat_x,
		background_repeat_repeat_y,
		background_repeat_no_repeat
	};

	enum BorderStyle
	{
		border_style_none,
		border_style_hidden,
		border_style_dotted,
		border_style_dashed,
		border_style_solid,
		border_style_double,
		border_style_groove,
		border_style_ridge,
		border_style_inset,
		border_style_outset,
	};

	enum css_units
	{
		css_units_none,
		css_units_percentage,
		css_units_in,
		css_units_cm,
		css_units_mm,
		css_units_em,
		css_units_rem,
		css_units_ex,
		css_units_pt,
		css_units_pc,
		css_units_px,
		css_units_dpi,
		css_units_dpcm,
		css_units_vw,
		css_units_vh,
		css_units_vmin,
		css_units_vmax,
	};

	enum css_angle_units
	{
		css_angle_units_none,
		css_angle_units_deg,
		css_angle_units_grad,
		css_angle_units_rad,
		css_angle_units_turn
	};

	enum css_time_units
	{
		css_time_units_none,
		css_time_units_ms,
		css_time_units_s,
	};

	static float deg2rad(float degree)
	{
		return degree / 180.0f * PIX_PI;
	}

	static float rad2deg(float radian)
	{
		return radian / PIX_PI * 180.0f;
	}

	struct Margins {
		float16 left;
		float16 right;
		float16 top;
		float16 bottom;

		Margins()
		{
			left = right = top = bottom = 0;
		}

		Margins(float16 _left, float16 _right, float16 _top, float16 _bottom)
			: left(_left), right(_right), top(_top), bottom(_bottom) {}

		float width() const { return left + right; }
		float height() const { return top + bottom; }
	};


	// NOLINTNEXTLINE
	struct size {
		float16 width = 0;
		float16 height = 0;

		size(float w, float h)
		{
			set(w, h);
		}
		size()
		{
			clear();
		}

		bool isZero()
		{
			return width == 0 && height == 0;
		}

		void set(float w, float h)
		{
			width = w;
			height = h;
		}
		void contain(size &sz)
		{
			width = width > sz.width ? width : sz.width;
			height = height > sz.height ? height : sz.height;
		}
		void clear()
		{
			width = height = 0;
		}

		inline bool operator==(const size &in_size) const
		{
			return FLOAT_EQ(width, in_size.width) && FLOAT_EQ(height, in_size.height);
		}

		inline bool operator!=(const size &in_size) const
		{
			return !operator==(in_size);
		}

		size &operator+=(const size &v)
		{
			width += v.width;
			height += v.height;
			return *this;
		}

		friend size operator+(const size &lhs, const size &rhs)
		{
			return size(lhs.width + rhs.width, lhs.height + rhs.height);
		}
	};

	// NOLINTNEXTLINE
	struct point {
		point() : x(0.0f), y(0.0f)
		{
		}

		point(float inX, float inY) : x(inX), y(inY)
		{
		}

		float16 x, y;
	};

	// NOLINTNEXTLINE
	struct position : public point, public size {
		position()
		{
			x = y = width = height = 0;
		}

		position(float x, float y, float width, float height)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}

		float right() const { return x + width; }
		float bottom() const { return y + height; }
		float left() const { return x; }
		float top() const { return y; }

		inline bool operator==(const position &other)
		{
			return FLOAT_EQ(x, other.x) &&
				   FLOAT_EQ(y, other.y) &&
				   FLOAT_EQ(width, other.width) &&
				   FLOAT_EQ(height, other.height);
		}

		bool notOverlap(const position &other) const
		{
			return other.right() < left() || other.left() > right() || other.bottom() < top() || other.top() > bottom();
		}

		bool overlap(const position &other) const
		{
			return !notOverlap(other);
		}

		void operator+=(const Margins &mg)
		{
			x -= mg.left;
			y -= mg.top;
			width += mg.left + mg.right;
			height += mg.top + mg.bottom;
		}

		void operator-=(const Margins &mg)
		{
			x += mg.left;
			y += mg.top;
			width -= mg.left + mg.right;
			height -= mg.top + mg.bottom;
		}

		void clear()
		{
			x = y = width = height = 0;
		}

		void operator=(const size &sz)
		{
			width = sz.width;
			height = sz.height;
		}

		bool operator!=(const position &other)
		{
			return x != other.x || y != other.y || width != other.width || height != other.height;
		}

		void moveTo(float x_, float y_)
		{
			this->x = x_;
			this->y = y_;
		}


		bool containIn(const position *container) const
		{
			return (container->left() <= left()) &&
				   (container->right() >= right()) &&
				   (container->top() <= top()) &&
				   (container->bottom() >= bottom());
		}

		bool empty() const
		{
			if (width == 0 && height == 0)
			{
				return true;
			}
			return false;
		}

		bool isPointInside(float x_, float y_) const
		{
			if (empty()) return false;
			if (x_ >= left() && x_ <= right() && y_ >= top() && y_ <= bottom())
			{
				return true;
			}
			return false;
		}

		bool isValid() const
		{
			return !isnan(x) && !isnan(y) && !isnan(width) && !isnan(height);
		}
	};

	struct IHFFrameBuffer {
		int image;
	};

	struct BoundingBox {
	private:
		float16 mLeft, mTop, mRight, mBottom;

	public:
		BoundingBox()
		{
			mLeft = mTop = mRight = mBottom = 0;
		}

		void reset()
		{
			mLeft = mTop = FLOAT_MAX;
			mRight = mBottom = -FLOAT_MAX;
		}

		inline float16 left() const { return isValid() ? mLeft : 0; }
		inline float16 right() const { return isValid() ? mRight : 0; }
		inline float16 top() const { return isValid() ? mTop : 0; }
		inline float16 bottom() const { return isValid() ? mBottom : 0; }

		float16 width() const
		{
			return isValid() ? mRight - mLeft : 0;
		}

		float16 height() const
		{
			return isValid() ? mBottom - mTop : 0;
		}

		void merge(const position &rt)
		{
			if (rt.x < mLeft)
				mLeft = rt.x;
			if (rt.y < mTop)
				mTop = rt.y;

			if (rt.x + rt.width > mRight)
				mRight = rt.x + rt.width;
			if (rt.y + rt.height > mBottom)
				mBottom = rt.y + rt.height;
		}

		inline bool isValid() const
		{
			return mLeft < FLOAT_MAX && mTop < FLOAT_MAX && mRight > -FLOAT_MAX && mBottom > -FLOAT_MAX;
		}
	};

	enum font_decoration
	{
		font_decoration_none = 0x00,
		font_decoration_underline = 0x01,
		font_decoration_linethrough = 0x02,
		font_decoration_overline = 0x04,
	};

	enum font_style
	{
		fontStyleNormal,
		fontStyleItalic
	};

	struct FontMetrics {
		int16 height;
		int16 ascent;
		int16 descent;
		int16 x_height;
		bool draw_spaces;

		FontMetrics()
		{
			height = 0;
			ascent = 0;
			descent = 0;
			x_height = 0;
			draw_spaces = true;
		}
		int baseLine() { return descent; }
	};


	struct BorderRadiuses {
		float16 topLeftX;
		float16 topLeftY;

		float16 topRightX;
		float16 topRightY;

		float16 bottomRightX;
		float16 bottomRightY;

		float16 bottomLeftX;
		float16 bottomLeftY;

		BorderRadiuses(float16 r = 0)
		{
			topLeftX = r;
			topLeftY = r;
			topRightX = r;
			topRightY = r;
			bottomRightX = r;
			bottomRightY = r;
			bottomLeftX = r;
			bottomLeftY = r;
		}

		BorderRadiuses(const BorderRadiuses &val)
		{
			topLeftX = val.topLeftX;
			topLeftY = val.topLeftY;
			topRightX = val.topRightX;
			topRightY = val.topRightY;
			bottomRightX = val.bottomRightX;
			bottomRightY = val.bottomRightY;
			bottomLeftX = val.bottomLeftX;
			bottomLeftY = val.bottomLeftY;
		}
		BorderRadiuses &operator=(const BorderRadiuses &val)
		{
			topLeftX = val.topLeftX;
			topLeftY = val.topLeftY;
			topRightX = val.topRightX;
			topRightY = val.topRightY;
			bottomRightX = val.bottomRightX;
			bottomRightY = val.bottomRightY;
			bottomLeftX = val.bottomLeftX;
			bottomLeftY = val.bottomLeftY;
			return *this;
		}
		void operator+=(const Margins &mg)
		{
			topLeftX += mg.left;
			topLeftY += mg.top;
			topRightX += mg.right;
			topRightY += mg.top;
			bottomRightX += mg.right;
			bottomRightY += mg.bottom;
			bottomLeftX += mg.left;
			bottomLeftY += mg.bottom;
			fixValues();
		}
		void operator-=(const Margins &mg)
		{
			topLeftX -= mg.left;
			topLeftY -= mg.top;
			topRightX -= mg.right;
			topRightY -= mg.top;
			bottomRightX -= mg.right;
			bottomRightY -= mg.bottom;
			bottomLeftX -= mg.left;
			bottomLeftY -= mg.bottom;
			fixValues();
		}
		void fixValues()
		{
			if (topLeftX < 0) topLeftX = 0;
			if (topLeftY < 0) topLeftY = 0;
			if (topRightX < 0) topRightX = 0;
			if (bottomRightX < 0) bottomRightX = 0;
			if (bottomRightY < 0) bottomRightY = 0;
			if (bottomLeftX < 0) bottomLeftX = 0;
			if (bottomLeftY < 0) bottomLeftY = 0;
		}
		bool isValid()
		{
			return (bottomLeftX > 0.00001f || bottomLeftY > 0.00001f ||
					topLeftX > 0.00001f || topLeftY > 0.00001f ||
					topRightX > 0.00001f || topRightY > 0.00001f ||
					bottomRightX > 0.00001f || bottomRightY > 0.00001f);
		}
	};


	enum border_image_repeat
	{
		image_stretch,
		image_repeat
	};

	enum border_image_model
	{
		image_fill,
		image_border
	};


	struct ImageSlice {
		border_image_repeat repeat;
		border_image_model model;
		int slice_top_x;
		int slice_top_y;
		int slice_bottom_x;
		int slice_bottom_y;


		ImageSlice()
		{
			repeat = image_stretch;
			model = image_fill;
			slice_top_x = 0;
			slice_top_y = 0;
			slice_bottom_x = 0;
			slice_bottom_y = 0;
		}

		ImageSlice(const ImageSlice &val)
		{
			repeat = val.repeat;
			model = val.model;
			slice_top_x = val.slice_top_x;
			slice_top_y = val.slice_top_y;
			slice_bottom_x = val.slice_bottom_x;
			slice_bottom_y = val.slice_bottom_y;
		}

		ImageSlice &operator=(const ImageSlice &val)
		{
			repeat = val.repeat;
			model = val.model;
			slice_top_x = val.slice_top_x;
			slice_top_y = val.slice_top_y;
			slice_bottom_x = val.slice_bottom_x;
			slice_bottom_y = val.slice_bottom_y;
			return *this;
		}
	};

#define IS_SLICE_VALID(slice) (slice.slice_top_x != 0 && slice.slice_top_y != 0 && slice.slice_bottom_x != 0 && slice.slice_bottom_y != 0)

	// NOLINTNEXTLINE
	struct color {
		byte m[4];

		color()
		{
			m[2] = 0;
			m[1] = 0;
			m[0] = 0;
			m[3] = 0xFF;
		}

		color(const color &val)
		{
			m[2] = val.m[2];
			m[1] = val.m[1];
			m[0] = val.m[0];
			m[3] = val.m[3];
		}

		color &operator=(const color &val)
		{
			m[2] = val.m[2];
			m[1] = val.m[1];
			m[0] = val.m[0];
			m[3] = val.m[3];
			return *this;
		}

		inline bool operator==(const color &val) const
		{
			for (int i = 0; i < 4; i++)
			{
				if (m[i] != val.m[i])
					return false;
			}
			return true;
		}

		inline byte red() const
		{
			return m[2];
		}

		inline byte &red()
		{
			return m[2];
		}

		inline byte green() const
		{
			return m[1];
		}

		inline byte &green()
		{
			return m[1];
		}

		inline byte blue() const
		{
			return m[0];
		}

		inline byte &blue()
		{
			return m[0];
		}

		inline byte alpha() const
		{
			return m[3];
		}

		inline byte &alpha()
		{
			return m[3];
		}

		inline int32 toint() const
		{
			return ((red() << 24) | (green() << 16) | (blue() << 8) | alpha());
		}
	};

#define VECTOR2_ELEMENT_COUNT 2
	// NOLINTNEXTLINE
	class vector2
	{
	public:
		/*
		m[ 0] m[ 1] m[ 2] m[ 3]
		*/
		vector2()
		{
			m[0] = 0;
			m[1] = 0;
		}

		vector2(float x_, float y_)
		{
			m[0] = x_;
			m[1] = y_;
		}

		vector2(float *v)
		{
			memcpy(this->m, v, sizeof(m[0]) * VECTOR2_ELEMENT_COUNT);
		}

		vector2(const vector2 &val)
		{
			memcpy(this->m, val.m, sizeof(m[0]) * VECTOR2_ELEMENT_COUNT);
		}

		// element
		operator const float *() const
		{
			return this->m;
		}

		operator float *()
		{
			return this->m;
		}

		const float &operator[](int i) const
		{
			// hf_ensure(i >= 0 && i < VECTOR2_ELEMENT_COUNT);

			return this->m[i];
		}

		float &operator[](int i)
		{
			// hf_ensure(i >= 0 && i < VECTOR2_ELEMENT_COUNT);

			return this->m[i];
		}

		// assignment
		vector2 &operator=(const vector2 &v)
		{
			memcpy(this->m, v.m, sizeof(m[0]) * VECTOR2_ELEMENT_COUNT);

			return *this;
		}

		// comparison
		inline bool operator==(const vector2 &other) const
		{
			return FLOAT_EQ(m[0], other.m[0]) && FLOAT_EQ(m[1], other.m[1]);
		}

		inline bool operator!=(const vector2 &other) const
		{
			return !operator==(other);
		}

		// Coordinate access.
		float x() const
		{
			return m[0];
		}

		float &x()
		{
			return m[0];
		}

		float y() const
		{
			return m[1];
		}

		float &y()
		{
			return m[1];
		}

		// arithmetic operations.
		vector2 operator+(const vector2 &other) const
		{
			return vector2(
					m[0] + other.m[0],
					m[1] + other.m[1]);
		}

		vector2 operator-(const vector2 &other) const
		{
			return vector2(
					m[0] - other.m[0],
					m[1] - other.m[1]);
		}

		vector2 operator*(float value) const
		{
			return vector2(
					m[0] * value,
					m[1] * value);
		}

		vector2 operator/(float value) const
		{
			if (fabs(value) > FLOAT_EPSILON)
			{
				return vector2(
						m[0] / value,
						m[1] / value);
			}
			else
			{
				return vector2(
						FLOAT_MAX,
						FLOAT_MAX);
			}
		}

		vector2 operator-() const
		{
			return vector2(
					-m[0],
					-m[1]);
		}

		// arithmetic updates.
		vector2 &operator+=(const vector2 &other)
		{
			this->m[0] += other.m[0];
			this->m[1] += other.m[1];

			return *this;
		}

		vector2 &operator-=(const vector2 &other)
		{
			this->m[0] -= other.m[0];
			this->m[1] -= other.m[1];

			return *this;
		}

		vector2 &operator*=(float value)
		{
			this->m[0] *= value;
			this->m[1] *= value;

			return *this;
		}

		vector2 &operator/=(float value)
		{
			if (fabs(value) > FLOAT_EPSILON)
			{
				m[0] /= value;
				m[1] /= value;
			}
			else
			{
				m[0] = FLOAT_MAX;
				m[1] = FLOAT_MAX;
			}

			return *this;
		}

		// operations
		float dot(const vector2 &v) const
		{
			return m[0] * v.m[0] + m[1] * v.m[1];
		}

		vector2 perpendicular() const
		{
			// i j k
			// m[0] m[1] m[2]
			// v.m[0] v.m[1] v.m[2]
			return vector2(
					-m[1],
					m[0]);
		}

		//----------------------------------------------------------------------------
		vector2 unitPerpendicular() const
		{
			vector2 result(perpendicular());

			result.normalize();
			return result;
		}

		float sqrlength() const
		{
			return m[0] * m[0] + m[1] * m[1];
		}

		float length() const
		{
			return sqrtf(sqrlength());
		}

		float normalize()
		{
			float l = length();

			if (fabs(l) > FLOAT_EPSILON)
			{
				m[0] /= l;
				m[1] /= l;

				return l;
			}
			else
			{
				m[0] = 0.0f;
				m[1] = 0.0f;
				return 0.0f;
			}
		}

	protected:
		// NOLINTNEXTLINE
		float m[VECTOR2_ELEMENT_COUNT];
	};

#define MATRIX_ELEMENT_COUNT 6
	/*
    x      y    t
	m[ 0] m[ 2] m[ 4]
	m[ 1] m[ 3] m[ 5]
	*/
	/*
	a c e
	b d f
	*/
	// NOLINTNEXTLINE
	class matrix
	{
	public:
		// NOLINTNEXTLINE
		class decomposition
		{
		public:
			float scaleX, scaleY;
			float angle;
			float remainderA, remainderB, remainderC, remainderD;
			float translateX, translateY;
		};

		static const matrix &identity()
		{
			static matrix mat;
			mat.initIdentity();
			return mat;
		}

		matrix()
		{
			// Mac: no initializtion for performance reason!!!!!!!!!
			// memset(m, 0, sizeof(float) * MATRIX_ELEMENT_COUNT);
		}

		matrix(float a_, float b_, float c_, float d_, float e_, float f_)
		{
			init(a_, b_, c_, d_, e_, f_);
		}

		matrix(const float16 *v)
		{
			memcpy(this->m, v, sizeof(m[0]) * MATRIX_ELEMENT_COUNT);
			mTurn = 0.f;
		}

		matrix(const matrix &val)
		{
			memcpy(this->m, val.m, sizeof(m[0]) * MATRIX_ELEMENT_COUNT);
			this->mTurn = val.mTurn;
		}

		~matrix()
		{
		}

		void init(float a_, float b_, float c_, float d_, float e_, float f_)
		{
			m[0] = a_;
			m[1] = b_;
			m[2] = c_;
			m[3] = d_;
			m[4] = e_;
			m[5] = f_;
			mTurn = 0.f;
		}

		void initZero()
		{
			init(0, 0, 0, 0, 0, 0);
		}

		void initIdentity()
		{
			init(1, 0, 0, 1, 0, 0);
		}

		void initTranslate(float x, float y)
		{
			init(1, 0, 0, 1, x, y);
		}

		void initRotate(float radian)
		{
			float c = cosf(radian);
			float s = sinf(radian);

			init(c, s, -s, c, 0, 0);
			mTurn = roundf(radian / (PIX_PI * 2));
		}

		void initRotateDeg(float deg)
		{
			float radian = deg / 180 * PIX_PI;
			float c = cosf(radian);
			float s = sinf(radian);

			init(c, s, -s, c, 0, 0);
			mTurn = roundf(deg / 360.f);
		}

		void initScale(float x, float y)
		{
			init(x, 0, 0, y, 0, 0);
		}

		void initFlipx()
		{
			initScale(-1, 1);
		}

		void initFlipy()
		{
			initScale(1, -1);
		}

		void initShear(float shearx, float sheary)
		{
			init(1, sheary, shearx, 1, 0, 0);
		}

		void initSkew(float angle_x, float angle_y)
		{
			float radianX = angle_x / 180 * PIX_PI;
			float radianY = angle_y / 180 * PIX_PI;

			initShear(tanf(radianX), tanf(radianY));
		}

		void initSkewX(float angle_x)
		{
			float radianX = angle_x / 180 * PIX_PI;

			initShear(tanf(radianX), 0);
		}

		void initSkewY(float angle_y)
		{
			float radianY = angle_y / 180 * PIX_PI;

			initShear(0, tanf(radianY));
		}

		inline float16 &a() { return m[0]; }
		inline float16 &b() { return m[1]; }
		inline float16 &c() { return m[2]; }
		inline float16 &d() { return m[3]; }
		inline float16 &e() { return m[4]; }
		inline float16 &f() { return m[5]; }
		inline const float16 &a() const { return m[0]; }
		inline const float16 &b() const { return m[1]; }
		inline const float16 &c() const { return m[2]; }
		inline const float16 &d() const { return m[3]; }
		inline const float16 &e() const { return m[4]; }
		inline const float16 &f() const { return m[5]; }

		// element
		operator const float16 *() const
		{
			return this->m;
		}

		operator float16 *()
		{
			return this->m;
		}

		const float16 &operator[](int i) const
		{
			// hf_ensure(i >= 0 && i < MATRIX_ELEMENT_COUNT);

			return m[i];
		}

		float16 &operator[](int i)
		{
			// hf_ensure(i >= 0 && i < MATRIX_ELEMENT_COUNT);

			return m[i];
		}

		// assignment
		matrix &operator=(const matrix &other)
		{
			memcpy(this->m, other.m, sizeof(m[0]) * MATRIX_ELEMENT_COUNT);
			this->mTurn = other.mTurn;
			return *this;
		}

		// Comparison.
		inline bool operator==(const matrix &other) const
		{
			for (int i = 0; i < MATRIX_ELEMENT_COUNT; i++)
			{
				if (!FLOAT_EQ(m[i], other.m[i]))
					return false;
			}
			return mTurn == other.mTurn;
		}

		inline bool operator!=(const matrix &other) const
		{
			return !operator==(other);
		}

		// arithmetic operations.
		matrix operator*(const matrix &other) const
		{
			auto ret = *this;
			return ret.multiply(other);
		}

		// arithmetic updates.
		matrix &operator*=(const matrix &other)
		{
			return multiply(other);
		}

		matrix &multiply(const matrix &other)
		{
			int turn = mTurn;
			init(m[0] * other.m[0] + m[2] * other.m[1],
				 m[1] * other.m[0] + m[3] * other.m[1],
				 m[0] * other.m[2] + m[2] * other.m[3],
				 m[1] * other.m[2] + m[3] * other.m[3],
				 m[0] * other.m[4] + m[2] * other.m[5] + m[4],
				 m[1] * other.m[4] + m[3] * other.m[5] + m[5]);
			mTurn = turn + other.mTurn;
			return *this;
		}

		vector2 getXaxis() const
		{
			return vector2(m[0], m[1]);
		}

		vector2 getYaxis() const
		{
			return vector2(m[2], m[3]);
		}

		position getAABB(const pixui::position &p) const
		{
			vector2 p1 = vector2(p.x, p.y);
			vector2 p2 = vector2(p.x + p.width, p.y);
			vector2 p3 = vector2(p.x + p.width, p.y + p.height);
			vector2 p4 = vector2(p.x, p.y + p.height);

			p1 = mulPosition(p1);
			p2 = mulPosition(p2);
			p3 = mulPosition(p3);
			p4 = mulPosition(p4);

			float x = (std::min)({p1.x(), p2.x(), p3.x(), p4.x()});
			float y = (std::min)({p1.y(), p2.y(), p3.y(), p4.y()});
			float xm = (std::max)({p1.x(), p2.x(), p3.x(), p4.x()});
			float ym = (std::max)({p1.y(), p2.y(), p3.y(), p4.y()});

			return position(x, y, xm - x, ym - y);
		}

		float getXaxisLength() const
		{
			return sqrtf(m[0] * m[0] + m[1] * m[1]);
		}

		float getYaxisLength() const
		{
			return sqrtf(m[2] * m[2] + m[3] * m[3]);
		}

		matrix &rotate(float angle)
		{
			float radian = deg2rad(angle);
			float c = cosf(radian);
			float s = sinf(radian);
			matrix matRotate(c, s, -s, c, 0, 0);

			*this = matRotate * *this;

			return *this;
		}

		matrix &scale(float s)
		{
			return scale(s, s);
		}

		matrix &scale(float sx, float sy)
		{
			m[0] *= sx;
			m[1] *= sx;
			m[2] *= sy;
			m[3] *= sy;

			return *this;
		}

		matrix &scale(const vector2 &s)
		{
			return scale(s.x(), s.y());
		}

		// *this = *this * translation
		matrix &translate(float tx, float ty)
		{
			if (isIdentityOrTranslation())
			{
				m[4] += tx;
				m[5] += ty;
				return *this;
			}

			m[4] += tx * m[0] + ty * m[2];
			m[5] += tx * m[1] + ty * m[3];
			return *this;
		}

		matrix &translate(const vector2 &t)
		{
			return translate(t.x(), t.y());
		}

		matrix &flipX()
		{
			return scale(-1, 1);
		}

		matrix &flipY()
		{
			return scale(1, -1);
		}

		matrix &shear(float sx, float sy)
		{
			float a = m[0];
			float b = m[1];

			m[0] += sy * m[2];
			m[1] += sy * m[3];
			m[2] += sx * a;
			m[3] += sx * b;

			return *this;
		}

		matrix &skew(float angleX, float angleY)
		{
			return shear(tanf(deg2rad(angleX)), tanf(deg2rad(angleY)));
		}

		matrix &skewX(float angle)
		{
			return shear(tanf(deg2rad(angle)), 0);
		}

		matrix &skewY(float angle)
		{
			return shear(0, tanf(deg2rad(angle)));
		}

		float determinant() const
		{
			return m[0] * m[3] - m[1] * m[2];
		}

		bool isInvertible() const
		{
			return fabs(determinant()) >= FLOAT_EPSILON;
		}

		matrix inverse() const
		{
			float d = determinant();
			if (!(fabs(determinant()) >= FLOAT_EPSILON))// not invertible
				return matrix(0, 0, 0, 0, 0, 0);

			matrix result;

			result.m[0] = m[3] / d;
			result.m[1] = -m[1] / d;
			result.m[2] = -m[2] / d;
			result.m[3] = m[0] / d;
			result.m[4] = (m[2] * m[5] - m[3] * m[4]) / d;
			result.m[5] = (m[1] * m[4] - m[0] * m[5]) / d;

			return result;
		}

		// operations
		static matrix interpolate(const matrix &from, const matrix &to, float alpha)
		{
			decomposition srA, srB;

			from.decompose(srA);
			to.decompose(srB);

			// If x-axis of one is flipped, and y-axis of the other, convert to an unflipped rotation.
			if ((srA.scaleX < 0 && srB.scaleY < 0) || (srA.scaleY < 0 && srB.scaleX < 0))
			{
				srA.scaleX = -srA.scaleX;
				srA.scaleY = -srA.scaleY;
				srA.angle += srA.angle < 0 ? 180 : -180;
			}

			// Don't rotate the long way around.
			// srA.angle = (float) fmod(srA.angle, 2.0f * 180.0f);
			// srB.angle = (float) fmod(srB.angle, 2.0f * 180.0f);
			// if (fabs(srA.angle - srB.angle) > 180.0f)
			// {
			// 	if (srA.angle > srB.angle)
			// 		srA.angle -= 180.0f * 2.0f;
			// 	else
			// 		srB.angle -= 180.0f * 2.0f;
			// }

			srA.scaleX += alpha * (srB.scaleX - srA.scaleX);
			srA.scaleY += alpha * (srB.scaleY - srA.scaleY);
			srA.angle += alpha * (srB.angle - srA.angle);
			srA.remainderA += alpha * (srB.remainderA - srA.remainderA);
			srA.remainderB += alpha * (srB.remainderB - srA.remainderB);
			srA.remainderC += alpha * (srB.remainderC - srA.remainderC);
			srA.remainderD += alpha * (srB.remainderD - srA.remainderD);
			srA.translateX += alpha * (srB.translateX - srA.translateX);
			srA.translateY += alpha * (srB.translateY - srA.translateY);

			matrix result;
			result.recompose(srA);

			return result;
		}

		void decompose(decomposition &decomp) const
		{
			matrix mat(*this);

			// Compute scaling factors
			float sx = getXaxisLength();
			float sy = getYaxisLength();

			// Compute cross product of transformed unit vectors. If negative,
			// one axis was flipped.
			if (mat.a() * mat.d() - mat.c() * mat.b() < 0)
			{
				// Flip axis with minimum unit vector dot product
				if (mat.a() < mat.d())
					sx = -sx;
				else
					sy = -sy;
			}

			// Remove scale from matrix
			if (sx)
			{
				mat.a() *= 1 / sx;
				mat.b() *= 1 / sx;
			}
			if (sy)
			{
				mat.c() *= 1 / sy;
				mat.d() *= 1 / sy;
			}

			// Compute rotation
			float rad = atan2f(mat.b(), mat.a());
			float angle = rad2deg(rad);
			float turn = mat.mTurn;

			// Remove rotation from matrix
			if (rad)
				mat.rotate(-angle);

			// Return results
			decomp.scaleX = sx;
			decomp.scaleY = sy;
			decomp.angle = angle + turn * 360;
			decomp.remainderA = mat.a();
			decomp.remainderB = mat.b();
			decomp.remainderC = mat.c();
			decomp.remainderD = mat.d();
			decomp.translateX = mat.e();
			decomp.translateY = mat.f();
		}

		void recompose(const decomposition &decomp)
		{
			a() = decomp.remainderA;
			b() = decomp.remainderB;
			c() = decomp.remainderC;
			d() = decomp.remainderD;
			e() = decomp.translateX;
			f() = decomp.translateY;

			rotate(decomp.angle);

			scale(decomp.scaleX, decomp.scaleY);
		}

		vector2 operator*(const vector2 &v) const
		{
			return this->mulPosition(v);
		}

		vector2 mulPosition(const vector2 &v) const
		{
			return vector2(
					m[0] * v[0] + m[2] * v[1] + m[4],
					m[1] * v[0] + m[3] * v[1] + m[5]);
		}

		vector2 mulDirection(const vector2 &v) const
		{
			return vector2(
					m[0] * v[0] + m[2] * v[1],
					m[1] * v[0] + m[3] * v[1]);
		}

		void mulPosition(float *x, float *y, int count) const
		{
			for (int i = 0; i < count; i++)
			{
				float xx = x[i];
				float yy = y[i];
				x[i] = m[0] * xx + m[2] * yy + m[4];
				y[i] = m[1] * xx + m[3] * yy + m[5];
			}
		}

		void mulDirection(float *x, float *y, int count) const
		{
			for (int i = 0; i < count; i++)
			{
				float xx = x[i];
				float yy = y[i];
				x[i] = m[0] * xx + m[2] * yy;
				y[i] = m[1] * xx + m[3] * yy;
			}
		}

		inline bool isIdentity() const
		{
			return m[0] == 1 && m[1] == 0 && m[2] == 0 && m[3] == 1 && m[4] == 0 && m[5] == 0;
		}

		inline bool isIdentityOrTranslation() const
		{
			return m[0] == 1 && m[1] == 0 && m[2] == 0 && m[3] == 1;
		}

		inline bool isTranslation() const
		{
			return m[4] != 0 || m[5] != 0;
		}

		inline bool hasRotationScaleShear() const
		{
			return m[1] != 0 || m[2] != 0;
		}

		static float pi()
		{
			return PIX_PI;
		}

	protected:
	private:
	protected:
		// NOLINTNEXTLINE
		float16 m[MATRIX_ELEMENT_COUNT];
		// if rotate greater than 180deg, mTurn record number of turn to rotate
		int mTurn;
	};


#define CLIP_REGION_MAX_VERTEX_COUNT 32

	class ClipRegion
	{
	public:
		ClipRegion()
		{
			clear();
		}

		ClipRegion(const pixui::matrix &mat, const position &pos)
		{
			set(mat, pos);
		}

		~ClipRegion()
		{
		}

		// assignment
		ClipRegion &operator=(const ClipRegion &other)
		{
			this->mBound = other.mBound;

			memcpy(this->mVertices, other.mVertices, CLIP_REGION_MAX_VERTEX_COUNT * sizeof(vector2));
			this->mVertexCount = other.mVertexCount;

			this->mMatrix = other.mMatrix;
			this->mPosition = other.mPosition;

			return *this;
		}

		void set(const pixui::matrix &mat, const position &pos)
		{
			clear();

			pixui::matrix matrix = mat;
			position p = pos;
			//p.x = 0;
			//p.y = 0;

			addVertex(matrix.mulPosition(vector2(p.x + 0, p.y + 0)));
			addVertex(matrix.mulPosition(vector2(p.x + pos.width, p.y + 0)));
			addVertex(matrix.mulPosition(vector2(p.x + pos.width, p.y + pos.height)));
			addVertex(matrix.mulPosition(vector2(p.x + 0, p.y + pos.height)));

			mMatrix = mat;
			mPosition = pos;
		}

		void addVertex(const pixui::vector2 &vertex)
		{
			// assume counter clock wise and convex
			updateBound(vertex);

			mVertices[mVertexCount++] = vertex;
		}

		bool isDegenerated() const
		{
			return mVertexCount == 0;
		}

		// for those platform does not support polygon clip region, just approx by bound
		const position &getBound() const
		{
			return mBound;
		}

		// for those platform support polygon clip region, by polygon vertices. e.g. Unity, Nano
		const vector2 *getVertices() const
		{
			return mVertices;
		}

		int getVerticesCount() const
		{
			return mVertexCount;
		}

		// for those platform support polygon clip region, by orginal matrix. e.g. UE4
		const pixui::matrix &getMatrix() const
		{
			return mMatrix;
		}

		const position &getPosition() const
		{
			return mPosition;
		}

		/*
		bool clip(const clip_region& other)
		{
			for (int i = 0; i < other.m_vertex_count; i++)
			{
				int i0 = i;
				int i1 = (i + 1) % other.m_vertex_count;
				if (!clip(other.m_vertices[i0], other.m_vertices[i1]))
					return false;
			}

			calc_bound();

			return true;
		}
		*/
	private:
		void updateBound(const pixui::vector2 &vertex)
		{
			float minx = mBound.x;
			float miny = mBound.y;
			float maxx = mBound.x + mBound.width;
			float maxy = mBound.x + mBound.height;

			minx = (minx < vertex.x() ? minx : vertex.x());
			miny = (miny < vertex.y() ? miny : vertex.y());
			maxx = (maxx > vertex.x() ? maxx : vertex.x());
			maxy = (maxy > vertex.y() ? maxy : vertex.y());

			mBound = position(minx, miny, maxx - minx, maxy - miny);
		}

		/*
		void calc_bound()
		{
			float minx = m_bound.x;
			float miny = m_bound.y;
			float maxx = -FLOAT_MAX;
			float maxy = -FLOAT_MAX;

			for (int i = 0; i < m_vertex_count; i++)
			{
				minx = (minx < m_vertices[i].x() ? minx : m_vertices[i].x());
				miny = (miny < m_vertices[i].y() ? miny : m_vertices[i].y());
				maxx = (maxx > m_vertices[i].x() ? maxx : m_vertices[i].x());
				maxy = (maxy > m_vertices[i].y() ? maxy : m_vertices[i].y());
			}

			m_bound = position(minx, miny, maxx - minx, maxy - miny);
		}
		*/

		void clear()
		{
			mBound = position(-FLOAT_MAX, -FLOAT_MAX, 0, 0);

			memset(mVertices, 0, CLIP_REGION_MAX_VERTEX_COUNT * sizeof(vector2));
			mVertexCount = 0;

			mMatrix.initIdentity();
			mPosition = position(-FLOAT_MAX, -FLOAT_MAX, 0, 0);
		}

		bool clip(const vector2 &start, const vector2 &end)
		{
			vector2 oldVertices[CLIP_REGION_MAX_VERTEX_COUNT];
			memcpy(oldVertices, mVertices, CLIP_REGION_MAX_VERTEX_COUNT * sizeof(vector2));
			int oldVerticesCount = mVertexCount;

			clear();

			for (int i = 0; i < oldVerticesCount; i++)
			{
				int i0 = i;
				int i1 = (i + 1) % oldVerticesCount;

				bool inside0 = getClipCase(oldVertices[i0], start, end);
				bool inside1 = getClipCase(oldVertices[i1], start, end);

				if (inside0 && inside1)// in, in
				{
					if (mVertexCount + 1 >= CLIP_REGION_MAX_VERTEX_COUNT)
					{
						clear();
						return false;
					}

					mVertices[mVertexCount++] = oldVertices[i0];
				}
				else if (inside0 && !inside1)// in, out
				{
					if (mVertexCount + 2 >= CLIP_REGION_MAX_VERTEX_COUNT)
					{
						clear();
						return false;
					}

					vector2 vc;
					clipLine(vc, oldVertices[i0], oldVertices[i1], start, end);
					mVertices[mVertexCount++] = oldVertices[i0];
					mVertices[mVertexCount++] = vc;
				}
				else if (!inside0 && inside1)// out in
				{
					if (mVertexCount + 1 >= CLIP_REGION_MAX_VERTEX_COUNT)
					{
						clear();
						return false;
					}

					vector2 vc;
					clipLine(vc, oldVertices[i0], oldVertices[i1], start, end);
					mVertices[mVertexCount++] = vc;
				}
				else// out out
				{
					// nothing
				}
			}

			return true;
		}

		void clipLine(vector2 &vc, const vector2 &p_start_0, const vector2 &p_end_0, const vector2 &p_start_1, const vector2 &p_end_1)
		{
			float a0 = p_end_0.y() - p_start_0.y();
			float b0 = p_start_0.x() - p_end_0.x();
			float c0 = a0 * p_start_0.x() + b0 * p_start_0.y();

			float a1 = p_end_1.y() - p_start_1.y();
			float b1 = p_start_1.x() - p_end_1.x();
			float c1 = a1 * p_start_1.x() + b1 * p_start_1.y();

			double det = (double) (a0 * b1 - a1 * b0);
			if (fabs(det) > FLOAT_EPSILON)
			{
				vc.x() = (float) ((b1 * c0 - b0 * c1) / det);
				vc.y() = (float) ((a0 * c1 - a1 * c0) / det);
			}
			else
			{
				vc.x() = 0;
				vc.y() = 0;
			}
		}

		bool getClipCase(const vector2 &p, const vector2 &clip_line_start, const vector2 &clip_line_end)
		{
			//                        clip_line_start
			//                    .  /  .
			//                   .  /  .
			//                  .  /  .
			//                 .  /  .
			//                .  /  .
			//               .  p  .       <-- in this case, p is here, distance = 0
			//              .  /  .
			//             .  /  p         <-- in this case, distance = -FLOAT_EPSILON
			//            .  /  .
			//           p  /  .           <-- in this case, distance =  FLOAT_EPSILON
			//          .  /  .
			//          ^  ^  ^
			//    It is becasue there is a limitation of precsion of float. if p is approx. laying on the clip line
			//    we should treat it as on the line, hence no clip.
			//    without this special treatment, the clipping is too sensitive for parallel polygon edge.
			vector2 clipline(clip_line_end - clip_line_start);
			if (clipline.normalize() < FLOAT_EPSILON)// if clip line is ver short
				clipline = vector2(1, 0);

			vector2 n(clipline.perpendicular());

			float distance = (p - clip_line_start).dot(n) >= 0;
			if (distance > -FLOAT_EPSILON)
				return true;
			else
				return false;
		}

	protected:
		position mBound;

		vector2 mVertices[CLIP_REGION_MAX_VERTEX_COUNT];
		int mVertexCount;

		pixui::matrix mMatrix;
		position mPosition;
	};

	const int kFakeWindowId = -1;


	// any class subclass this interface
	// will be a tickable object, TimeMgr will
	// call its tick function per frame once
	struct PX_API ITickable {
		ITickable() {}
		virtual ~ITickable() {}
		virtual void tick(float dt) = 0;
		virtual const char *name() = 0;

		// 不能直接继承使用，需要使用IWindowTickable或者IGlobalTickable
		virtual void cantBeInherateDirectly() = 0;
	};

	// 和H5Window绑定的可以tick的对象需要集成自这个类
	struct PX_API IWindowTickable : public ITickable {
		IWindowTickable(int windowID);
		virtual ~IWindowTickable();
		virtual void cantBeInherateDirectly() {}

	protected:
		int mWindowID;
	};

	struct Capability {
		bool supportRetainFrame;
		bool supportDrawTextWithLetterSpace;
	};

	struct LoadPageArg {
		const char *baseUrl;
		bool strictMode = false;	  /* 是否启用严格模式，严格校验加载资源有效性 */
		const char *zipBundleUrl;	  /* 启用严格模式，需要指定zip包下载路径 */
		const char *zipSavedPath;	  /* 启用严格模式，需要指定zip包保存路径 */
		const char *presetAssetsPath; /* 启用严格模式，需要指定预置资源位置路径 */
		const char *entryName;		  /* 启用严格模式，需要指定入口页面 */
		const char *appletName;		  /* applet小应用名称 */
		const char *deviceInfo;		  /* applet小应用所在的设备信息 */
	};

	typedef int (*EngineOpenPageDelegate)(int winId, LoadPageArg *loadPageArg);
	typedef bool (*EngineClosePageDelegate)(int winId);
	typedef bool (*EnginePostMessageDelegate)(int winId, const char *message);
	typedef bool (*NativePostMessageDelegate)(int winId, int type, int code, const char *message);

#define DF_PAINT_MODE_NONE 0		//无
#define DF_PAINT_MODE_FORCE (1 << 0)//绘制模式，强制当前帧绘制


#define DF_RENDER_TYPE_AUTO 0//自动根据平台选择渲染器
#define DF_RENDER_TYPE_OPENGL (1 << 0)
#define DF_RENDER_TYPE_OPENGL_ES2 (1 << 1)
#define DF_RENDER_TYPE_OPENGL_ES3 (1 << 2)
#define DF_RENDER_TYPE_DX11 (1 << 3)
#define DF_RENDER_TYPE_DX9 (1 << 4)
#define DF_RENDER_TYPE_VULKAN (1 << 5)
#define DF_RENDER_TYPE_METAL (1 << 6)
#define DF_RENDER_TYPE_BGFX (1 << 7)


#define DF_DEVICE_TYPE_NONE 0
#define DF_DEVICE_TYPE_DX11 1
#define DF_DEVICE_TYPE_DX9 2
#define DF_DEVICE_TYPE_GL 3
#define DF_DEVICE_TYPE_METAL 4
#define DF_DEVICE_TYPE_VULKAN 5
#define DF_DEVICE_TYPE_HWND 6//for windows hwnd and create dx device for render

	//PxView 内部绘制参数
	struct PxViewDeviceParam {
		int mDeviceType;
		int mRenderType;
		float mScale;
		int mKeep;
		void *mDevice;
		void *mExternal;
		Capability mCapability;

		PxViewDeviceParam()
		{
			mDeviceType = DF_DEVICE_TYPE_NONE;
			mRenderType = DF_RENDER_TYPE_AUTO;
			mScale = 1.0f;
			mKeep = 0;
			mDevice = nullptr;
			mExternal = nullptr;

			mCapability.supportRetainFrame = true;
			mCapability.supportDrawTextWithLetterSpace = true;
		};
	};
}// namespace pixui
