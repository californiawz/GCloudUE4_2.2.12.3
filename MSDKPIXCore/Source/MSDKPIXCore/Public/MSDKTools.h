///*
/*!
 * @Header MSDKTools.hpp
 * @Author Hillson Song
 * @Date 2018/8/24
 * @Abstract MSDK 工具类
 *
 * @Module MSDK
 *
 * Copyright © company. All rights reserved.
 */

#ifndef MSDKTools_hpp
#define MSDKTools_hpp

#include "MSDKDefine.h"

#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif
NS_MSDK_BEGIN

// deeplink & shorturl 请求回调结构体

        class MSDK_EXPORT MSDKToolsRet : public MSDKBaseRet {
        public:
            std::string link;

            MSDKToolsRet() : MSDKBaseRet() {}

        AutoParser("com.itop.gcloud.msdk.api.tools.MSDKToolsRet",
                   A(thirdCode, "ret"),
                   A(thirdMsg, "msg"),
                   A(link, "deeplink"),
                   O(retCode, retMsg, methodNameID, extraJson));

        };

        class MSDK_EXPORT MSDKToolsFreeFlowInfo {
        public:
            //全部免流IP列表
            std::string ipAll;

            //免流时返回配置信息对应的，否则返回入餐的 key
            std::string ipConnect;

            //1:免流，0:不免
            int isFree;

            //1: 中国联通，2: 中国电信，3:中国移动，99:其它
            int ccType;

        AutoParser("com.itop.gcloud.msdk.api.tools.MSDKToolsFreeFlowInfo",
                   A(ipAll, "ip_all"),
                   A(isFree, "is_free"),
                   A(ccType, "cc_type"),
                   O(ipConnect));


        };

        class MSDK_EXPORT MSDKToolsFreeFlowRet

                : public MSDKBaseRet {
        public:
            MSDKToolsFreeFlowInfo freeFlowInfo;

        AutoParser("com.itop.gcloud.msdk.api.tools.MSDKToolsFreeFlowRet",
                   A(thirdCode, "ret"),
                   A(thirdMsg, "msg"),
                   A(extraJson, "extra"),
                   A(freeFlowInfo, "freeflow_info"),
                   O(retCode, retMsg, methodNameID));


        };

// 登录监听
        class MSDK_EXPORT MSDKToolsObserver {
        public:
            // 短链接的回调
            virtual ~MSDKToolsObserver() {};

            virtual void OnToolsRetNotify(const MSDKToolsRet &toolsRet) {};

            virtual void OnToolsFreeFlowRetNotify(const MSDKToolsFreeFlowRet &toolsFreeFlowRet) {};

        };

// 工具类
        class MSDK_EXPORT MSDKTools {

        private:

            static MSDKToolsObserver *mToolsObserver;

            static void
            SetToolsObserverPRV(typename T<InnerToolsRet>::InnerRetCallback toolsRetObserver);

            static void SetToolsFrreFlowObserverPRV(
                    typename T<InnerToolsFreeFlowRet>::InnerRetCallback toolsFreeFlowRetObserver);


            static void ToolsRetObserver(const InnerToolsRet &toolsRet, const char *seqID) {
                MSDKToolsRet *pRet = new MSDKToolsRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerToolsRet to MSDKToolsRet start");
                MSDKCompatManager::compatConvert(*pRet, toolsRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerToolsRet to MSDKToolsRet finish then will notify user");
                if (mToolsObserver) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                        MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 ToolsRetObserver");
                        mToolsObserver->OnToolsRetNotify(*pRet);
                        delete pRet;
                    });
#else
                    mToolsObserver->OnToolsRetNotify(*pRet);
                    delete pRet;
#endif
                } else {
                    //fix codecc memory leak
                    delete pRet;
                }
            }

            static void
            ToolsFreeFlowRetObserver(const InnerToolsFreeFlowRet &innerRet, const char *seqID) {
                MSDKToolsFreeFlowRet *pRet = new MSDKToolsFreeFlowRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerToolsFreeFlowRet to MSDKToolsFreeFlowRet start");
                MSDKCompatManager::compatConvert(*pRet, innerRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert MSDKToolsFreeFlowRet to MSDKToolsFreeFlowRet finish then will notify user");
                if (mToolsObserver) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                        MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 ToolsFreeFlowRetObserver");
                        mToolsObserver->OnToolsFreeFlowRetNotify(*pRet);
                        delete pRet;
                    });
#else
                    mToolsObserver->OnToolsFreeFlowRetNotify(*pRet);
                    delete pRet;
#endif
                } else {
                    //fix codecc memory leak
                    delete pRet;
                }
            }

            // 获取 deeplink 请求回调
            static void OnDeepLinkResp(int sessionId, unsigned int ret, const std::string &respBody,
                                       void *userData);

            // 短链转换请求回调
            static void OnShortURLResp(int sessionId, unsigned int ret, const std::string &respBody,
                                       void *userData);

            // 免流服务的回调
            static void OnFreeFlowResp(int sessionId, unsigned int ret, const std::string &respBody,
                                       void *userData);

        public:

            static void SetToolsObserver(MSDKToolsObserver *observer) {
                if (!observer) {
                    MSDKPIX_LOG_ERROR("", "MSDKToolsObserver cant not be NULL");
                } else {
                    mToolsObserver = observer;
                    SetToolsObserverPRV(ToolsRetObserver);
                    SetToolsFrreFlowObserverPRV(ToolsFreeFlowRetObserver);
                }
            }

            /**
             * 根据当前登录态，打开对应应用deeplink（deeplink功能的开通和配置请联系各平台）
             * @param link 具体跳转deeplink
             */
            static void OpenDeepLink(String link);

            /**
             * 判断渠道应用是否安装
             * @param channel 渠道名
             * @retunr 安装状态
             */
            static bool IsAppInstall(String channel, String extra = "");

            // 根据错误码返回，默认使用设备语言
            static std::string GetRetMsg(int retCode);

            /**
             * 转短链
             * @param url 目标 URL
             * @param typeMark urlTypeMark:url类型标记，支持A-Z中26个大写英文字母，与open管理后台相对应。获取短链跳转时，通过此参数获取正确的404跳转地址。默认值：A
             * @retunr 状态
             */
            static bool ConvertShortUrl(String url, String typeMark = "A");

            /**
             * 免流服务查询
             * @param key 根据 key（原IP） 返回，后台免流配置 对应的 value（对应的 svip）
             * @param extraJson 扩展字段，暂时没有使用
             */
            static bool GetFreeFlowInfo(String key, String extraJson = "");

#if MSDK_PLATFORM_WINDOWS
#else
#if defined (__APPLE__)
            /**
     * 应用评分提醒
     */
    static bool ShowRatingAlert();

    /**
     * 判断渠道应用是否安装
     * @param appid 应用 ID
     */
    static void ShowAppStoreProductView(String appid);

    // 获取渠道包打包信息
    static std::string GetConfigChannelID(const String &seqID = "");
#endif
#if defined (ANDROID)

            // 获取渠道包打包信息
            static String GetConfigChannelID(const String &seqID = "");

            static String GetGuestId();

            static void SetGuestId(String guestId);

#endif
#endif // MSDK_PLATFORM_WINDOWS

            /**
             * 中控上报，目前支持国内渠道，海外渠道暂不支持。
             * @param projnaJson 透传中控字段
             */
            static bool ReportPrajna(std::string projnaJson);

            /**
             * 用于打开WebView，提供给中控使用
             * @param jsonStr WebView配置
             * @return 触发打开返回true，否则返回false
             */
            static bool OpenPrajnaWebView(std::string jsonStr);

            static std::string GetConfig(const std::string &key, const std::string &defValue);

            static bool GetConfig(const std::string &key, const bool defValue);

            static int GetConfig(const std::string &key, const int defValue);

            static long GetConfig(const std::string &key, const long defValue);

            /**
            * 用于获取登录状态中第三方 openID
            * @param channel 渠道名称
            * @return 返回渠道的 openID
            */
            static std::string GetLoginChannelOpenID(const std::string &channel);
        };

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

            // deeplink & shorturl 请求回调结构体
            class MSDK_EXPORT MSDKToolsRet : public MSDKBaseRet {
            public:
                String link;

                MSDKToolsRet() : MSDKBaseRet() {}

                MSDKToolsRet(const MSDK::MSDKToolsRet &toolsRet) : MSDKBaseRet(toolsRet) {
                    link = toolsRet.link;
                }

            AutoParser("com.itop.gcloud.msdk.api.tools.MSDKToolsRet",
                       A(thirdCode, "ret"),
                       A(thirdMsg, "msg"),
                       A(extraJson, "extra"),
                       A(link, "deeplink"),
                       O(retCode, retMsg, methodNameID));

            };

            class MSDK_EXPORT MSDKToolsFreeFlowInfo {
            public:
                //全部免流IP列表
                String ipAll;

                //免流时返回配置信息对应的，否则返回入餐的 key
                String ipConnect;

                //1:免流，0:不免
                int isFree;

                //1: 中国联通，2: 中国电信，3:中国移动，99:其它
                int ccType;

                MSDKToolsFreeFlowInfo(const MSDK::MSDKToolsFreeFlowInfo &info) {
                    ipAll = info.ipAll;
                    ipConnect = info.ipConnect;
                    isFree = info.isFree;
                    ccType = info.ccType;
                }

            AutoParser("com.itop.gcloud.msdk.api.tools.MSDKToolsFreeFlowInfo",
                       A(ipAll, "ip_all"),
                       A(isFree, "is_free"),
                       A(ccType, "cc_type"),
                       O(ipConnect));
            };

            class MSDK_EXPORT MSDKToolsFreeFlowRet : public MSDKBaseRet {
            public:
                MSDKToolsFreeFlowInfo freeFlowInfo;

                MSDKToolsFreeFlowRet(const MSDK::MSDKToolsFreeFlowRet &freeFlowRet) : MSDKBaseRet(
                        freeFlowRet), freeFlowInfo(freeFlowRet.freeFlowInfo) {
                }

            AutoParser("com.itop.gcloud.msdk.api.tools.MSDKToolsFreeFlowRet",
                       A(thirdCode, "ret"),
                       A(thirdMsg, "msg"),
                       A(extraJson, "extra"),
                       A(freeFlowInfo, "freeflow_info"),
                       O(retCode, retMsg, methodNameID));
            };

// 登录监听
            class MSDK_EXPORT MSDKToolsObserver {
            public:
                // 短链接的回调
                virtual ~MSDKToolsObserver() {};

                virtual void OnToolsRetNotify(const MSDKToolsRet &toolsRet) {};

                virtual void
                OnToolsFreeFlowRetNotify(const MSDKToolsFreeFlowRet &toolsFreeFlowRet) {};
            };

            class MSDKToolsObserverAdapter : public MSDK::MSDKToolsObserver {
            public:
                void OnToolsRetNotify(const MSDK::MSDKToolsRet &toolsRet);

                void OnToolsFreeFlowRetNotify(const MSDK::MSDKToolsFreeFlowRet &toolsFreeFlowRet);

                MSDKSpace::NoSTL::MSDKToolsObserver *mObserver = NULL;
            };

// 工具类
            class MSDK_EXPORT MSDKTools {
            private:
                static MSDKToolsObserverAdapter mToolsObserverAdapter;
            public:
                static void SetToolsObserver(MSDKToolsObserver *observer) {
                    if (!observer) {
                        MSDKPIX_LOG_ERROR("", "MSDKToolsObserver cant not be NULL");
                    } else {
                        mToolsObserverAdapter.mObserver = observer;
                        MSDK::MSDKTools::SetToolsObserver(&mToolsObserverAdapter);
                    }
                }

                /**
                 * 根据当前登录态，打开对应应用deeplink（deeplink功能的开通和配置请联系各平台）
                 * @param link 具体跳转deeplink
                 */
                static void OpenDeepLink(String link);

                /**
                 * 判断渠道应用是否安装
                 * @param channel 渠道名
                 * @retunr 安装状态
                 */
                static bool IsAppInstall(String channel, String extra = "");

                // 根据错误码返回，默认使用设备语言
                static String GetRetMsg(int retCode);

                /**
                 * 转短链
                 * @param url 目标 URL
                 * @param typeMark urlTypeMark:url类型标记，支持A-Z中26个大写英文字母，与open管理后台相对应。获取短链跳转时，通过此参数获取正确的404跳转地址。默认值：A
                 * @retunr 状态
                 */
                static bool ConvertShortUrl(String url, String typeMark = "A");

                /**
                 * 免流服务查询
                 * @param key 根据 key（原IP） 返回，后台免流配置 对应的 value（对应的 svip）
                 * @param extraJson 扩展字段，暂时没有使用
                 */
                static bool GetFreeFlowInfo(String key, String extraJson = "");

#if MSDK_PLATFORM_WINDOWS
#else
#if defined (__APPLE__)
                /**
     * 应用评分提醒
     */
    static bool ShowRatingAlert();

    /**
     * 判断渠道应用是否安装
     * @param appid 应用 ID
     */
    static void ShowAppStoreProductView(String appid);

    // 获取渠道包打包信息
    static String GetConfigChannelID(const String &seqID = "");
#endif
#if defined (ANDROID)

                // 获取渠道包打包信息
                static String GetConfigChannelID(const String &seqID = "");

                static String GetGuestId();

                static void SetGuestId(String guestId);

#endif
#endif // MSDK_PLATFORM_WINDOWS

                /**
                 * 中控上报，目前支持国内渠道，海外渠道暂不支持。
                 * @param projnaJson 透传中控字段
                 */
                static bool ReportPrajna(String projnaJson);

                /**
                 * 用于打开WebView，提供给中控使用
                 * @param jsonStr WebView配置
                 * @return 触发打开返回true，否则返回false
                 */
                static bool OpenPrajnaWebView(String jsonStr);

                static String GetConfig(const String &key, const String &defValue);

                static bool GetConfig(const String &key, const bool defValue);

                static int GetConfig(const String &key, const int defValue);

                static long GetConfig(const String &key, const long defValue);

                /**
                 * 用于获取登录状态中第三方 openID
                 * @param channel 渠道名称
                 * @return 返回渠道的 openID
                 */
                static String GetLoginChannelOpenID(const String &channel);
            };


NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDKTools_hpp */
