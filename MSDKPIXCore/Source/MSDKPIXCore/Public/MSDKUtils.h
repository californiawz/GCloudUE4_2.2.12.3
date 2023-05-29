/*!
 * @header MSDKUtils.h 
 * @author developer
 * @date 2018/4/26
 * @abstract
 * (内部使用)简单的工具类声明，目前包含：
 * 1. 生成通用唯一识别码
 * 2. 格式化输出 Json 字符串
 * 3. 字符串跟数字连接工具
 * 4. 类型转换工具，将一个类型的值 <InType> 转换为另一个类型 <OutType>
 * 
 * @copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_UTILS_H
#define MSDK_UTILS_H

#include <sstream>
#include "MSDKDefine.h"
#include "MSDKError.h"

#define VALID_GUEST_ID_LENGTH 36

NS_MSDK_BEGIN

        class MSDK_EXPORT MSDKUtils {
        public:

            // 获取游客ID
            static std::string GetGuestID(const std::string &seqId);

            // 设置错误提示信息语言（遵守ISO 639-1标准）
            static void SetRetMsgLan(const std::string &lan);

            // 根据错误码返回，默认使用设备语言
            static std::string GetRetMsg(int retCode);

            // 时间戳(单位秒)
            static long GetTimestamp();

            // 时间戳(单位毫秒)
            static int64_t GetTimestampMilliSecond();

            // 时间戳（返回 string 类型）
            static std::string GetTimestampString();

            // 格式输出 Json 字符串，主要用于控制台打
            static String FormatJson(const String &jsonStr);

            // 字符串指定位置插入空格
            static void AddIndentBlank(std::string str, int indent);

            // 判断字符串前綴
            static bool StartWith(const char *prefix, const char *str);

            // 判断字符串后綴
            static bool EndWith(const char *str, const char *suffix);

            // 移除空格
            static const char *Trim(const char *name);

            static String ParseMethodName(MethodName methodID);

            static int StringToInt(const std::string &sSour) {
                return (atoi(sSour.c_str()));
            }

            static std::string IntToString(int nSour) {
                //  itoa 不是c的标准库函数，依赖编译器的实现
                char tempChars[32] = {0};
                int chars_written = snprintf(tempChars, sizeof(tempChars), "%d", nSour);
                if (chars_written < 0) {
                    chars_written = 0;
                }
                return std::string(tempChars, chars_written);
            }

            static long StringToLong(const std::string &sSour) {
                return atol(sSour.c_str());
            }

            static std::string LongToString(long nSour) {
                char tempChars[32] = {0};
                int chars_written = snprintf(tempChars, sizeof(tempChars), "%ld", nSour);
                if (chars_written < 0) {
                    chars_written = 0;
                }
                return std::string(tempChars, chars_written);
            }

            static long long StringToLongLong(const std::string &sSour) {
                return atoll(sSour.c_str());
            }

            static std::string LongLongToString(long long nSour) {
                char tempChars[64] = {0};
                int chars_written = snprintf(tempChars, sizeof(tempChars), "%lld", nSour);
                if (chars_written < 0) {
                    chars_written = 0;
                }
                return std::string(tempChars, chars_written);
            }

            static bool StringToBool(const std::string &sSour) {
                return (sSour.compare("1") == 0) ? true : false;
            }

            static std::string BoolToString(bool nSour) {
                return nSour ? "1" : "0";
            }

            /**
             * 字符串拼接工具
             *
             * @sample
             * std::string str = concat<long>("test", 10L);
             *
             */
            template<class Type>
            static std::string concat(const char *src, Type num) {
                // 有一个使用到concat的地方，被其他函数替换
                return "";
//        std::stringstream stream;
//        stream << num;
//        std::string tmp(src);
//        tmp += stream.str();
//        return tmp;
            }

            /**
             * 类型转换工具
             *
             * @sample
             * 将字符串 “11” 转换为整形 11
             * int num = typeConvert<int,std::string>("11");
             */


//    template<class OutType, class InType>
//    static OutType typeConvert(InType a)
//    {
//        std::stringstream ss;
//        OutType ret;
//        ss << a;
//        ss >> ret;
//        return ret;
//    };
//
            // 通过 url 打开 app
            static void openAPP(const std::string &url);

            // 获取设备ID
            static std::string GetUUID();

            // 获取设备语言
            static std::string GetDeviceLanguage();

            // 获取 APP 版本
            static std::string GetAppVersion();

            // 屏幕 DPI
            static float GetScreenDPI();

            // 设备分辨率
            static std::string GetScreenResolution();

            // 品牌
            static std::string GetBrand();

            // 厂商
            static std::string GetManufacturer();

            // 设备型号
            static std::string GetModel();

            // 网络型号
            static std::string GetAPN();

            // RAM 信息
            static std::string GetRAMInfo();

            // ROM 信息
            static std::string GetROMInfo();

            // CPU 信息
            static std::string GetCPUInfo();

            // 游戏 versionName
            static std::string GetGameVersionName();

            // 游戏 versionCode
            static std::string GetGameVersionCode();

            // 手机硬件信息获取接口
            static String GetDeviceInfoWrapper();

            static String GetDeviceInfoWrapperForNotice();

            static String GetDeviceInfoWrapperForConfig();

            static bool IsValidPassword(std::string password);

            // extra, Android-包名，iOS-URLScheme
            static bool IsChannelInstalled(const char *channel, const char *extra = "");

            /*! 将多个字符char转成16进制的表示形式
            * c 源字符
            * 源字符的16进制string
            * CharsToHex
            */
            static std::string CharsToHex(const char *ptr, unsigned long size);

            /*
             * 将文案展示到屏幕上
             */
            static void ShowAlert(const std::string &alertString);

            // map<std::string, std::string> 类型转 string
            static std::string MapToString(std::map<std::string, std::string> val) {
                std::string result = "";
                typename std::map<std::string, std::string>::iterator it = val.begin();
                for (; it != val.end(); it++) {
                    result.append("<")
                            .append(it->first)
                            .append(",")
                            .append(it->second)
                            .append(">\n\r");
                }

                if (result.empty()) {
                    result = "no value";
                }
                return result;
            };

            // map 类型转 string
            template<typename TypeOne, typename TypeSecond>
            static std::string MapToString(std::map<TypeOne, TypeSecond> val) {
                // 被上面的函数替代
                return "";
//        std::string result = "";
//        typename std::map<TypeOne, TypeSecond>::iterator it = val.begin();
//        for (; it != val.end(); it++)
//        {
//            result.append("<")
//                    .append(typeConvert<std::string, TypeOne>(it->first))
//                    .append(",")
//                    .append(typeConvert<std::string, TypeSecond>(it->second))
//                    .append(">\n\r");
//        }
//
//        if(result.empty())
//        {
//            result = "no value";
//        }
//        return result;
            };

            static String GetVersion();

            // 获取MSDK1.0的游客ID等信息
            static std::string GetMSDKV1GuestidInfo();

            // 通过 TDM 获取 beacon qimei36
            static std::string GetQIMEI36();

#ifdef __APPLE__

            // 获取MSDK的游客ID等信息，MSDK的Android没有游客
            static std::string GetMSDKV3GuestidInfo();

            // 获取 IDFA 数据
            static std::string GetIDFA();

            // 获取 iOS 原始设备型号
            static std::string GetHWMachine();

            // 通过 TDM 获取 TGPA TGToken
            static std::string GetTGToken();

#endif

            // 通过 Seq ID 设定 JSON 结构的参数数据
            static void SetParamJson(std::string seq, std::string json);

            // 通过 Seq ID 获取 JSON 结构的参数数据
            static std::string GetParamJson(std::string seq);

            // 通过 Seq ID 清理 JSON 结构的参数数据
            static void CleanParamJson(std::string seq);

            // Deeplink链接跳转
            // 可支持分别跳转至游戏中心原生页面，和活动页面，具体表现方案和显示入口可以根据游戏的实际情况来定制。
            // 游戏中心原生页面包括：游戏中心首页、游戏中心详情页、游戏中心游戏库等；通过游戏后台参数设定来实现
            // 活动页面包括:游戏的H5页面，通过游戏后台配置跳转地址来实现
            // 具体跳转deeplink，可填写为：
            // INDEX：跳转游戏中心首页
            // DETAIL：跳转游戏中心详情页
            // LIBRARY：跳转游戏中心游戏库
            // 具体跳转的url
            static void OpenDeepLink(const std::string url);

            // 游客专用，从外置存储卡里面读取和写入GuestId
            static std::string GetGuestIdFromExternal(bool report, const std::string &seqId);

            static bool SaveGuestIdToExternal(const std::string &guestId, const std::string &seqId);

#ifdef ANDROID

            static std::string GetDeviceInfo(const char *methodName);

            // 纯净的Base64编码，去除MSDK标志
            static std::string Base64Encode(const std::string &text);

            // 通过 TDM 获取 IMEI，权限/系统E判断交由 TDM 负责
            static std::string GetIMEI();

            // 通过 TDM 获取 beacon qimei
            static std::string GetQIMEI();

            // 通过 TDM 获取 OAID
            static std::string GetOAID();

            // 通过 TDM 获取 TGPA XID
            static std::string GetXID();

            // 获取云游戏cgToken
            static std::string GetChannelExtra(const std::string &paras);

#endif

#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else

            // TDM 获取字符串类型的设备信息
            static std::string
            GetStringDeviceInfo(bool *isGetTDMServiceSucc, const std::string deviceInfoName);

            // TDM 获取长整型类型的设备信息
            static int64_t
            GetLongDeviceInfo(bool *isGetTDMServiceSucc, const std::string deviceInfoName);

#endif
        };

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN
            using MSDKUtils = MSDK::MSDKUtils;

NS_MSDK_SPACE_NO_STL_END
#endif //MSDK_UTILS_H
