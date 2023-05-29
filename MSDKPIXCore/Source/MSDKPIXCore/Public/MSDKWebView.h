/*!
 * @Module MSDK
 *
 * @Header  MSDKWebView.h
 * @Author  developer
 * @date 2018/6/11
 * @abstract
 * 1. 打开 Url
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDKWebView_h
#define MSDKWebView_h

#include <stdio.h>
#include "MSDKDefine.h"

#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif
NS_MSDK_BEGIN


        class MSDK_EXPORT MSDKWebViewRet : public MSDKBaseRet {
        public:
            /** 100：关闭, 101:js 调用Native, 102：js 调用share 接口、103：js 调用sendMessage、104：嵌入式浏览器加载进度*/
            int msgType;

            /** js 调用 native 携带的参数 */
            std::string msgJsonData;
            /** 嵌入式浏览器的加载进度 */
            float embedProgress;

            /** 嵌入式浏览器加载进度对应的 URL*/
            std::string embedUrl;


        AutoParser("com.itop.gcloud.msdk.api.webview.MSDKWebViewRet",
                   A(thirdCode, "ret"),
                   A(thirdMsg, "msg"),
                   A(extraJson, "extra"),
                   O(retCode, retMsg, methodNameID, msgType, msgJsonData, embedProgress, embedUrl))

        };

/**
 * MSDK WebView observer interface
 */
        class MSDK_EXPORT MSDKWebViewObserver {
        public:
            virtual ~MSDKWebViewObserver() {};

            virtual void OnWebViewOptNotify(const MSDKWebViewRet &webViewRet) {};
        };


        class MSDK_EXPORT MSDKWebView {
        private :

            // Observer for Common API call
            static MSDKWebViewObserver *mWebViewObserver;

            ~MSDKWebView();

            static String GetPRVEncodeURL(const String &url);

            static void WebViewOptNotify(MSDKWebViewObserver *observer, MSDKWebViewRet *pRet) {
                if (observer) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, observer]() {
                        MSDKPIX_LOG_DEBUG("", "Async Task In UE4 WebViewRetObserver");
                        observer->OnWebViewOptNotify(*pRet);
                        delete pRet;
                    });
#else
                    observer->OnWebViewOptNotify(*pRet);
                    delete pRet;
#endif
                } else {
                    MSDKPIX_LOG_ERROR("", "WebView observer is null");
                    delete pRet;
                }
            }

        protected:
            static void WebViewRetObserver(const InnerWebViewRet &WebViewRet, const char *seqID);

            // Observer for GCloud plugin API call
            static MSDKWebViewObserver *mGCloudWebViewObserver;

            static void SetPRVWebviewObserver(T<InnerWebViewRet>::InnerRetCallback webViewObserver);

        public:
#if MSDK_PLATFORM_WINDOWS
            MSDK_EXPORT_UE static void SetWebViewObserver(MSDKWebViewObserver *webViewObserver);
#else

            static void SetWebViewObserver(MSDKWebViewObserver *webViewObserver) {
                if (!webViewObserver) {
                    MSDKPIX_LOG_ERROR("", "MSDKWebViewObserver cant not be NULL");
                } else {
                    mWebViewObserver = webViewObserver;
                    SetPRVWebviewObserver(WebViewRetObserver);
                }
            }

#endif

            /**
             * 按照指定格式打开网址
             *
             * @param url 网址链接
             * @param screenType 屏幕方向：1 默认 2 竖屏 3 横屏
             * @param isFullScreen 是否以全屏的方式打开
             * @param isUseURLEncode 链接进行 URL 编码
             * @param extraJson 扩展字段，默认为空
             * @param isBrowser 是否用浏览器打开
             */
            MSDK_EXPORT_UE static void
            OpenUrl(const String &url, int screenType = 1, bool isFullScreen = false,
                    bool isUseURLEncode = true, const String &extraJson = "",
                    bool isBrowser = false);


            /**
            *  打开AMS营销活动中心
            *
            *  @param gameName 业务代码缩写，每个业务不同，各业务在接入AMS平台时由系统分配。
            *  @param actChannelId 活动渠道ID，由活动管理端后台分配，各业务登录[互娱AMS]管理端自行获取。
            *  @param zoneId 用户区服信息，大区 1Q，2信
            *  @param platformId 平台ID：iOS（0），安卓（1）
            *  @param partitionId 小区ID
            *  @param roleId 角色ID
            * @param screenType 屏幕方向：1 横屏和竖屏 2 竖屏 3 横屏
            * @param  extraJson 扩展字段，默认为空
            */
            MSDK_EXPORT_UE static void OpenAmsCenter(const String &gameName,
                                                     const String &actChannelId,
                                                     const String &zoneId,
                                                     const String &platformId,
                                                     const String &partitionId,
                                                     const String &roleId,
                                                     int screenType = 1,
                                                     const String &extraJson = "");

            /**
             * 添加加密票据
             * @param url 需要加密票据的 URL
             */
            MSDK_EXPORT_UE static std::string GetEncodeUrl(const String &url) {
#ifdef ANDROID
                return GetPRVEncodeURL(url).c_str();
#endif

#ifdef __APPLE__
                return GetPRVEncodeURL(url).c_str();
#else
                return "";
#endif
            }

            /**
             * JS 调用
             * @param jsonJsPara json 格式数据调用
             */
            MSDK_EXPORT_UE static void CallJS(const String &jsonJsPara);
            /**
             * 关闭嵌入式浏览器，内置浏览器暂不支持
             */
            MSDK_EXPORT_UE static void Close();

            /**
             * 打开游戏数据授权页
             *
             * @param url 游戏数据授权页网址链接
             * @param screenType 屏幕方向：1 默认 2 竖屏 3 横屏
             * @param isFullScreen 是否以全屏的方式打开
             * @param extraJson 扩展字段，默认为空
             */
            MSDK_EXPORT_UE static void OpenGameDataAuthCenter(const String &url,
                                                              int screenType = 1,
                                                              bool isFullScreen = false,
                                                              const String &extraJson = "");

            /**
             * 打开注销账号的页面
             */
            MSDK_EXPORT_UE static void OpenDeleteAccountUrl(const String &url,
                                                            int screenType = 1,
                                                            bool isFullScreen = false,
                                                            const String &extraJson = "");
        };

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

            class MSDK_EXPORT MSDKWebViewRet : public MSDKBaseRet {
            public:
                /** 100：关闭, 101:js 调用Native, 102：js 调用share 接口、103：js 调用sendMessage、104：嵌入式浏览器加载进度*/
                int msgType;

                /** js 调用 native 携带的参数 */
                String msgJsonData;
                /** 嵌入式浏览器的加载进度 */
                float embedProgress;

                /** 嵌入式浏览器加载进度对应的 URL*/
                String embedUrl;

                MSDKWebViewRet(const MSDK::MSDKWebViewRet &webviewRet) : MSDKBaseRet(webviewRet) {
                    msgType = webviewRet.msgType;
                    msgJsonData = webviewRet.msgJsonData;
                    embedProgress = webviewRet.embedProgress;
                    embedUrl = webviewRet.embedUrl;
                }

            AutoParser("com.itop.gcloud.msdk.api.webview.MSDKWebViewRet",
                       A(thirdCode, "ret"),
                       A(thirdMsg, "msg"),
                       A(extraJson, "extra"),
                       O(retCode, retMsg, methodNameID, msgType, msgJsonData, embedProgress,
                         embedUrl))

            };

            class MSDK_EXPORT MSDKWebViewObserver {
            public:
                virtual ~MSDKWebViewObserver() {};

                virtual void OnWebViewOptNotify(const MSDKWebViewRet &webViewRet) {};
                // virtual void OnWebProgressChanged(std::string url, float progress) {};
            };

            class MSDK_EXPORT MSDKWebViewObserverAdapter : public MSDK::MSDKWebViewObserver {
            public:
                void OnWebViewOptNotify(const MSDK::MSDKWebViewRet &webViewRet);
                // virtual void OnWebProgressChanged(std::string url, float progress) {};

                MSDKSpace::NoSTL::MSDKWebViewObserver *mObserver = NULL;
            };

            class MSDK_EXPORT MSDKWebView {
            private:
                static MSDKWebViewObserverAdapter mWebviewObserverAdapter;
            public:
#if MSDK_PLATFORM_WINDOWS
                MSDK_EXPORT_UE static void SetWebViewObserver(MSDKWebViewObserver *webViewObserver);
#else

                static void SetWebViewObserver(MSDKWebViewObserver *webViewObserver) {
                    if (!webViewObserver) {
                        MSDKPIX_LOG_ERROR("", "MSDKWebViewObserver cant not be NULL");
                    } else {
                        mWebviewObserverAdapter.mObserver = webViewObserver;
                        MSDK::MSDKWebView::SetWebViewObserver(&mWebviewObserverAdapter);
                    }
                }

#endif

                /**
                 * 按照指定格式打开网址
                 *
                 * @param url 网址链接
                 * @param screenType 屏幕方向：1 默认 2 竖屏 3 横屏
                 * @param isFullScreen 是否以全屏的方式打开
                 * @param isUseURLEncode 链接进行 URL 编码
                 * @param extraJson 扩展字段，默认为空
                 * @param isBrowser 是否用浏览器打开
                 */
                MSDK_EXPORT_UE static void
                OpenUrl(const String &url, int screenType = 1, bool isFullScreen = false,
                        bool isUseURLEncode = true, const String &extraJson = "",
                        bool isBrowser = false);

                /**
                 *  打开AMS营销活动中心
                 *
                 *  @param gameName 业务代码缩写，每个业务不同，各业务在接入AMS平台时由系统分配。
                 *  @param actChannelId 活动渠道ID，由活动管理端后台分配，各业务登录[互娱AMS]管理端自行获取。
                 *  @param zoneId 用户区服信息，大区 1Q，2信
                 *  @param platformId 平台ID：iOS（0），安卓（1）
                 *  @param partitionId 小区ID
                 *  @param roleId 角色ID
                 * @param screenType 屏幕方向：1 横屏和竖屏 2 竖屏 3 横屏
                 * @param  extraJson 扩展字段，默认为空
                 */
                MSDK_EXPORT_UE static void OpenAmsCenter(const String &gameName,
                                                         const String &actChannelId,
                                                         const String &zoneId,
                                                         const String &platformId,
                                                         const String &partitionId,
                                                         const String &roleId,
                                                         int screenType = 1,
                                                         const String &extraJson = "");

                /**
                 * 添加加密票据
                 * @param url 需要加密票据的 URL
                 */
                MSDK_EXPORT_UE static String GetEncodeUrl(const String &url);

                /**
                 * JS 调用
                 * @param jsonJsPara json 格式数据调用
                 */
                MSDK_EXPORT_UE static void CallJS(const String &jsonJsPara);
                /**
                 * 关闭嵌入式浏览器，内置浏览器暂不支持
                 */
                MSDK_EXPORT_UE static void Close();

                /**
                 * 打开游戏数据授权页
                 *
                 * @param url 游戏数据授权页网址链接
                 * @param screenType 屏幕方向：1 默认 2 竖屏 3 横屏
                 * @param isFullScreen 是否以全屏的方式打开
                 * @param extraJson 扩展字段，默认为空
                 */
                MSDK_EXPORT_UE static void OpenGameDataAuthCenter(const String &url,
                                                                  int screenType = 1,
                                                                  bool isFullScreen = false,
                                                                  const String &extraJson = "");

                /**
                 * 打开注销账号的页面
                 */
                MSDK_EXPORT_UE static void OpenDeleteAccountUrl(const String &url,
                                                                int screenType = 1,
                                                                bool isFullScreen = false,
                                                                const String &extraJson = "");
            };

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDKWebView_h */
