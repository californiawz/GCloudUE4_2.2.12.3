/**************************************************

**** @file:     PxUIView.h

**** @brief:    

**** @author:   tianzelei@pixui.com

**** @date:     2022/06/08

**** @group:    PixUI

**** @copyright: Copyright 2019 pandora.pixui. All Rights Reserved.

***************************************************/

#ifndef PxUIView_h
#define PxUIView_h

//for ios
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


typedef NS_ENUM(NSUInteger, EPxKeyboardType) {
	EPxKeyboardDefault = 0,
	EPxKeyboardNumber,
	EPxKeyboardPassword,

	EPxKeyboardCount
};

@protocol PxInputDelegate <NSObject>
- (bool)OnActivateInput:(EPxKeyboardType)nType defaultText:(NSString *)defaultText hintText:(NSString *)hintText;
- (bool)OnDeativateInput;
@end


@protocol PxScriptDelegate <NSObject>
- (void)OnLoadComplete:(NSString *)url code:(int)code;
- (void)OnInternalError:(int)code msg:(NSString *)msg;
- (void)OnMessage:(NSString *)msg;
- (void)OnEventClose;
- (void)OnEventOpen:(NSString *)url title:(NSString *)title features:(NSString *)features bReplace:(bool)bReplace;
@end


typedef NS_ENUM(NSUInteger, EPxViewTransformType) {
	EPxViewTransformMoveBy = 0,
	EPxViewTransformMoveTo,
	EPxViewTransformSizeBy,
	EPxViewTransformSizeTo,
	EPxViewTransformScrollBy,
	EPxViewTransformScrollTo,
	EPxViewTransformCount
};

@protocol PxViewDelegate <NSObject>
- (void)OnViewLoaded:(int)nCode msg:(NSString *)msg;
- (void)OnLoadComplete:(NSString *)url code:(int)code;
- (void)OnInternalError:(int)code msg:(NSString *)msg;
- (void)OnMessage:(NSString *)msg;
- (void)OnEventClose;

- (void)OnEventOpen:(NSString *)url title:(NSString *)title features:(NSString *)features bReplace:(bool)bReplace;
- (void)OnEventAlert:(NSString *)message;
- (bool)OnEventConfirm:(NSString *)message;
- (NSString *)OnEventPrompt:(NSString *)strText message:(NSString *)message;
- (void)OnEventTransform:(EPxViewTransformType)eType x:(int)xInfor y:(int)yInfor;
@end


//native render
__attribute__((visibility("default")))
@interface PxView : UIView
//for update
- (void)OnPxViewNeedUpdate;

- (void)SetPageEventDelegate:(id<PxViewDelegate>)pxViewDelegate;
- (id<PxViewDelegate>)GetPageEventDelegate;

- (void)SetTouchSupport:(bool)bUseTouch;

- (int)PageLoadUrl:(NSString *)url;
- (int)PageLoadInStrictMode:(NSString *)nsZipBundleUrl
			 nsZipSavedPath:(NSString *)nsZipSavedPath
		 nsPresetAssetsPath:(NSString *)nsPresetAssetsPath
				nsEntryName:(NSString *)nsEntryName
			   nsAppletName:(NSString *)nsAppletName;
- (int)PageSendMessage:(NSString *)message;
- (int)PageClose;
@end


//metal render
__attribute__((visibility("default")))
@interface PxViewHD : PxView

@end


//px script
__attribute__((visibility("default")))
@interface PxScriptVM : NSObject

- (void)SetEventDelegate:(id<PxScriptDelegate>)pxScriptDelegate;

- (int)LoadUrl:(NSString *)url;
- (int)RunBuffer:(NSData *)nsBuffer;
- (int)SendMessage:(NSString *)message;
- (int)Close;
@end


typedef NS_ENUM(NSUInteger, EPxLogGroup) {
	EPxLogGroupCore = 0,
	EPxLogGroupScipte,
	EPxLogGroupEmbedded,

	EPxLogGroupCount
};

typedef NS_ENUM(NSUInteger, EPxLogType) {
	EPxLogLog = 0,
	EPxLogWarn,
	EPxLogError,
	EPxLogDebug,

	EPxLogCount
};
typedef void (^PxLogBlock)(EPxLogGroup eLogGroup, EPxLogType eLogType, NSString *strLog);
typedef void (^PxEngineMessageBlock)(int winId, int type, int code, const char *message);


__attribute__((visibility("default")))
@interface PxEmbdMgr : NSObject

+ (int)StartUp:(PxLogBlock)pxLogBlock agent:(NSString *)agent;
+ (bool)IsStartUp;
+ (NSString *)Version;

+ (int)ForeGround;
+ (int)BackGround;

+ (void)SetInputDelegate:(id<PxInputDelegate>)inputDelegate;
+ (void)KeyboardInput:(NSString *)inputText bEndInput:(bool)bEndInput bLostFocus:(bool)bLostFocus bReplace:(bool)bReplace;

+ (int)SetDefaultFont:(int)nRenderIndex fontName:(NSString *)fontName;
+ (int)AddFontByPath:(int)nRenderIndex fontName:(NSString *)fontName fontPath:(NSString *)fontPath bAsset:(bool)bAsset;
+ (int)AddFontByBuffer:(int)nRenderIndex fontName:(NSString *)fontName pBuffer:(const char *)pBuffer nSize:(size_t)nSize;

+ (int)AddNativeFontByPath:(NSString *)fontName fontPath:(NSString *)fontPath bAsset:(bool)bAsset;
+ (int)AddNativeFontByBuffer:(NSString *)fontName pBuffer:(const char *)pBuffer nSize:(size_t)nSize;

+ (int)ShutDown;

+ (PxView *)CreatePxView:(CGRect)rect;
+ (PxViewHD *)CreatePxViewHD:(CGRect)rect;

+ (bool)IsEngineRender;
+ (void)SetEngineMessageCallback:(PxEngineMessageBlock)pxEngineMessageBlock;
+ (NSData *)LoadAppletConfig:(NSString *)nsAppletAssetsPath nsAppletName:(NSString *)nsAppletName;
+ (int)EngineOpenPage:(int)nPxHandle
			nsZipBundleUrl:(NSString *)nsZipBundleUrl
			nsZipSavedPath:(NSString *)nsZipSavedPath
		nsPresetAssetsPath:(NSString *)nsPresetAssetsPath
			   nsEntryName:(NSString *)nsEntryName
			  nsAppletName:(NSString *)nsAppletName;
+ (int)EngineClosePage:(int)nPxHandle;
@end

#endif /* PxUIView_h */
