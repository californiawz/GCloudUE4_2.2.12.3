#pragma once
#include "hf_typedef.h"

namespace pixui
{
	class IHostDraw
	{
	public:
		virtual void queryCapability(Capability *cap) { memset(cap, 0, sizeof(Capability)); };

		virtual uint_ptr getContextPtr() = 0;
		/*
		before paint call

		@hDevice:   draw device
		*/
		virtual void onPrePaint() = 0;


		/*
		end paint call

		@hDevice:       draw device
		@nPaintCode:    reserved
		*/
		virtual void onEndPaint(const int nPaintCode) = 0;

		/************************************************************************/
		//Begin for slot resource
		virtual uint_ptr createSlot(const char *src) { return nullptr; }
		virtual void deleteSlot(uint_ptr attachment){};
		virtual void drawSlot(uint32 id, uint_ptr attachment, const matrix &mat, const position &rect){};
		virtual void pushSlot(uint32 id, uint_ptr attachment, const matrix &mat, const position &rect) { drawSlot(id, attachment, mat, rect); };
		virtual void popSlot(){};
		virtual void pushRenderLayer(uint32 id, const pixui::matrix &mat, const pixui::size &size) {}
		virtual void popRenderLayer() {}
		//End for slot resource
		/************************************************************************/

		/************************************************************************/
		//Begin for font resource
		struct RegisterFontArg {
			const char *fontFamily;
			const char *fontSrc;
			const char *fontWeight;
			const char *fontStyle;
			void *notifyCtx;
			void (*notify)(void *notifyCtx, bool);
		};
		virtual void registerFont(RegisterFontArg &arg){};

		/*
		Create font

		@pszFontName:   font name(If not found will use the default font)
		@nSize:         font size
		@nWeight:       font weight
		@italic:        emItalic
		@nDecoration:   reserved
		@stFontMetrics:

		return: Font handle
		*/
		virtual uint_ptr createFont(
				const char *pszFontName,
				const int nSize,
				const int nWeight,
				const unsigned int unDecoration,
				const font_style emItalic,
				FontMetrics *pStFontMetrics) = 0;


		/*
		Delete Font

		@hFont: Font handle
		*/
		virtual void delFont(uint_ptr hFont) = 0;


		/*
		measure text width

		@pszTest:   text content
		@hFont:     font handle

		@return:    text width
		*/
		virtual float textWidth(const char *pszText, uint_ptr hFont) = 0;
		/*
		virtual float charWidth(bxutil::ucode_t cp, uint_ptr hFont)
		{
			bxutil::ucode_t u32[] = {cp, 0};
			auto utf8 = FROM_UTF32(u32).string();
			return textWidth(utf8.c_str(), hFont);
		}
		*/
		virtual float charWidth(uint32_t unCharCode, uint_ptr hFont) = 0;

		/*
		get default Font Size

		return: Font Size
		*/
		virtual int getDefaultFontSize() = 0;


		/*
		get default Font name

		return: Font name
		*/
		virtual const char *getDefaultFontName() = 0;
		//End for font resource
		/************************************************************************/

		/*
		measure text width

		@nPt:   Convert point size to pixels

		return: pixels
		*/
		virtual int ptToPix(const int nPt) = 0;


		/*
		set cursor

		@pszCursor: cursor resource name
		*/
		virtual void setCursor(const char *pszCursor) = 0;


		/************************************************************************/
		//Begin for image resource
		virtual uint_ptr createImage(const char *pszName) = 0;
		virtual bool initImageByRawData(uint_ptr hImage, const int nWidth, const int nHeight, const int nImageFlag, const EPixelFormat emPixelFormat, const uint8 *pRawData, size_t nDataSize) = 0;
		virtual void updateImageByRawData(uint_ptr hImage, const EPixelFormat emPixel, const uint8 *pRawData, size_t nDataSize) = 0;
		virtual void getImageSize(uint_ptr hImage, size &sz) = 0;
		virtual bool isExternalImage(uint_ptr hImage) = 0;
		virtual bool delImage(uint_ptr hImage) = 0;
		//End for image resource
		/************************************************************************/


		/*
		Set Clip polygon

		@hDevice:       draw device
		@polygon:       clip polygon
		*/
		virtual void pushClip(pixui::uint32 id, const ClipRegion &polygon) = 0;

		/*
		Push clip rect

		@hDevice:       draw device
		@rcClip:    clip rect
		*/
		virtual void pushClip(uint32 id, const matrix &mat, const position &rcClip) = 0;


		/*
		Pop clip rect

		@hDevice:   draw device
		*/
		virtual void popClip() = 0;


		/*
		Push ui group

		@hDevice:       draw device
		*/
		virtual void pushGroup(uint32 id, const pixui::matrix &mat, const pixui::size &size){};


		/*
		Pop ui group

		@hDevice:   draw device
		*/
		virtual void popGroup(){};


		/*
		next rendering layer

		@hDevice:   draw device
		*/
		virtual void nextRenderLayer() = 0;

		/*
		get rendering layer

		@hDevice:   draw device
		return:     current render layer
		*/
		virtual int getCurrentRenderLayer() = 0;

		/*
		fill rect area

		@stDrawPos: draw position
		@stColor:   color
		@stRadius:  reserved
		*/
		virtual void fillBackgroundRect(
				uint32 id,
				const matrix &mat,
				const position &rcDrawPos,
				const color &stColor,
				const BorderRadiuses &radius) = 0;

		/*
		draw background image on device

		@hDevice:       draw device
		@hImg:          image handle
		@stDrawPos:     draw position
		@stImageUV:     draw image uv
		@emRepeat:      repeat style
		@emAttachment:  attachment style
		@stColor:       image color and opacity

		*/
		virtual void drawBackgroundImage(
				uint32 id,
				uint_ptr pImage,
				const matrix &mat,
				const position &rcDraw,
				const position &rcImageSrc,
				const BackgroundRepeat emRepeat,
				const BackgroundAttachment emAttachment,
				const ImageSlice &sliceImage,
				const color &tintColor,
				const BorderRadiuses &radius) = 0;

		/*
		draw background image on device

		@hDevice:       draw device
		@hImg:          image handle
		@stDrawPos:     draw position
		@stImageUV:     draw image uv
		@emRepeat:      repeat style
		@emAttachment:  attachment style
		@stColor:       image color and opacity

		*/
		virtual void drawBorderImage(
				uint32 id,
				uint_ptr pImage,
				const matrix &mat,
				const position &rcDraw,
				const position &rcImageSrc,
				const BackgroundRepeat emRepeat,
				const BackgroundAttachment emAttachment,
				const ImageSlice &sliceImage,
				const color &tintColor,
				const BorderRadiuses &radius) = 0;

		/*
		draw text on device

		@hDevice:   draw device
		@pszText:   text
		@hFont:     font content
		@stColor:   color for draw text
		@stPos:     draw position
		*/
		virtual void drawBorderRect(
				uint32 id,
				const pixui::matrix &mat,
				const position &stDrawPos,
				const unsigned int nLeftWidth, const BorderStyle emLeftLineType, const color &stLeftColor,
				const unsigned int nRightWidth, const BorderStyle emRightLineType, const color &stRightColor,
				const unsigned int nTopWidth, const BorderStyle emTopLineType, const color &stTopColor,
				const unsigned int nBottomWidth, const BorderStyle emBottomLineType, const color &stBottomColor,
				const BorderRadiuses &radius) = 0;

		/*
		draw image on device

		@hDevice:       draw device
		@hImg:          image handle
		@stDrawPos:     draw position
		@stImageUV:     draw image uv
		@emRepeat:      repeat style
		@emAttachment:  attachment style
		@stColor:       image color and opacity

		*/
		virtual void drawContentImage(
				uint32 id,
				uint_ptr pImage,
				const matrix &mat,
				const position &rcDraw,
				const position &rcImageSrc,
				const BackgroundRepeat emRepeat,
				const BackgroundAttachment emAttachment,
				const ImageSlice &sliceImage,
				const color &drawColor,
				const BorderRadiuses &radius) = 0;

		/*
		draw text on device

		@hDevice:   draw device
		@pszText:   text
		@hFont:     font content
		@drawColor: color for draw text
		@stPos:     draw position
		*/
		virtual void drawContentText(
				uint32 id,
				uint_ptr hFont,
				const matrix &mat,
				const char *pszTextDraw,
				const color &drawColor,
				const position &rcDraw,
				const float fBlur,
				const float letterSpace) = 0;

		/*
		draw line on device

		@ hDevice:      draw device
		@ nWidth:       Line width
		@ emLineType:   Line type

		@ return:
		*/
		virtual void drawContentLine(
				uint32 id,
				const matrix &mat,
				const unsigned int unWidth,
				const BorderStyle emLineType,
				const color &tintColor,
				const point &ptStart,
				const point &ptEnd) = 0;

		/*
		return a VG render
		*/
		virtual void *createVG(int edgeAA, int viewId) { return nullptr; }
		// Delete a VG context
		virtual void deleteVG(void *nvg) {}

		virtual void beginPath(){};
		virtual void closePath(){};
		virtual void setStrokeWidth(float size){};
		virtual void moveTo(const point &target){};
		virtual void lineTo(const point &target){};
		virtual void stroke(){};
		virtual void fill(){};
		virtual void drawImage(uint64 handle, const position &pos, const pixui::matrix &mat, const position &offset, const size &sz, const BorderRadiuses &radius, bool texture2BackBuffer){};

		virtual IHFFrameBuffer *createFrameBuffer(int32_t width, int32_t height, int32_t flags) { return nullptr; }
		virtual void bindFrameBuffer(IHFFrameBuffer *fb){};
		virtual void deleteFrameBuffer(IHFFrameBuffer *fb){};
		virtual void beginFrame(int w, int h){};
		virtual void endFrame(){};
		virtual void save(){};
		virtual void restore(){};
		virtual void setFillStyle(float r, float g, float b, float a){};
		virtual void setStrokeStyle(float r, float g, float b, float a){};
		virtual void drawText(float x, float y, const char *text){};
		virtual void setLineCap(int value){};
		virtual void setLineJoin(int value){};
		virtual void setFont(uint_ptr fontId, int fontSize, float lineHeight){};
		virtual void rect(float x, float y, float w, float h){};
		virtual void bezierCurveTo(float x1, float y1, float x2, float y2, float x, float y){};
		virtual void quadraticCurveTo(float cx, float cy, float x, float y){};
		virtual void scale(float x, float y){};
		virtual void translate(float x, float y){};
		virtual void rotate(float angle){};
		virtual void setTransform(float a, float b, float c, float d, float e, float f){};

		virtual void strokeRect(
				uint32 id,
				const position &pos){};

		virtual void fillRect(
				uint32 id,
				const position &pos,
				const color &color){};

		virtual void clearRect(
				uint32 id,
				const position &pos,
				const color &color){};

		virtual void arc(
				float x,
				float y,
				float radius,
				float startAngle,
				float endAngle,
				int anticlockwise){};
		virtual void arcTo(float fromX, float fromY, float toX, float toY, float radius){};
	};
	typedef pixui::IHostDraw *IHostDrawPtr;
}// namespace pixui
