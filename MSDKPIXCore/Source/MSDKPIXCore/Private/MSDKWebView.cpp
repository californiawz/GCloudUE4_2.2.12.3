//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKWebView.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

String MSDKWebView::GetPRVEncodeURL(const String &url) { return ""; }

void MSDKWebView::OpenUrl(const String &url, int screenType, bool isFullScreen,
                        bool isUseURLEncode, const String &extraJson,
                        bool isBrowser) {}
						
void MSDKWebView::OpenAmsCenter(const String& gameName,
                              const String& actChannelId,
                              const String& zoneId,
                              const String& platformId,
                              const String& partitionId,
                              const String& roleId,
                              int screenType,
                              const String &extraJson) {}
							  
void MSDKWebView::CallJS(const String &jsonJsPara) {}

void MSDKWebView::Close() {}

NS_MSDK_END


NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKWebView::OpenUrl(const String &url, int screenType, bool isFullScreen,
                          bool isUseURLEncode, const String &extraJson,
                          bool isBrowser) {}

void MSDKWebView::OpenAmsCenter(const String& gameName,
                                const String& actChannelId,
                                const String& zoneId,
                                const String& platformId,
                                const String& partitionId,
                                const String& roleId,
                                int screenType,
                                const String &extraJson) {}

void MSDKWebView::CallJS(const String &jsonJsPara) {}

void MSDKWebView::Close() {}

NS_MSDK_SPACE_NO_STL_END

#endif




