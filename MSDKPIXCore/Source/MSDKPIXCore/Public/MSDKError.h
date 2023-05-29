/*!
 * @Module MSDK
 *
 * @Header  MSDKError.h
 * @Author  developer
 * @Date 2018/03/20
 * @Abstract
 * MSDK 客户端错误码声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_ERROR_H
#define MSDK_ERROR_H

#include "MSDKMacros.h"

NS_MSDK_BEGIN

class MSDKError
{
public:
    /** 未知错误 */
    static const int UNKNOWN = -1;
    static const int SUCCESS = 0;
    static const int NO_ASSIGN = 1; /** 没有赋值 */
    static const int CANCEL = 2;
    static const int SYSTEM_ERROR = 3;
    static const int NETWORK_ERROR = 4;
    static const int MSDK_SERVER_ERROR = 5; // MSDK 后台返回错误，参考第三方错误码
    static const int TIMEOUT = 6;
    static const int NOT_SUPPORT = 7;
    static const int OPERATION_SYSTEM_ERROR = 8;
    static const int NEED_PLUGIN = 9;
    static const int NEED_LOGIN = 10;
    static const int INVALID_ARGUMENT = 11;
    static const int NEED_SYSTEM_PERMISSION = 12;
    static const int NEED_CONFIG = 13;
    static const int SERVICE_REFUSE = 14;
    static const int NEED_INSTALL_APP = 15;
    static const int APP_NEED_UPGRADE = 16;
    static const int INITIALIZE_FAILED = 17;
    static const int EMPTY_CHANNEL = 18;
    static const int FUNCTION_DISABLE = 19;
    static const int NEED_REALNAME = 20; // 需实名认证
    static const int REALNAME_FAIL = 21; // 实名认证失败
    static const int IN_PROGRESS = 22; // 上次操作尚未完成，稍后再试
    static const int API_DEPRECATED = 23;
    static const int LIBCURL_ERROR = 24;
    static const int FREQUENCY_LIMIT = 25; //频率限制
    static const int DINED_BY_APP = 26; // 被三方拒绝，需要查看具体的错误
    static const int QRCODE_TIMEOUT = 27; //二维码超时

    /** 1000 ~ 1099 字段是 LOGIN 模块相关的错误码 */
    static const int LOGIN_UNKNOWN_ERROR = 1000;
    static const int LOGIN_NO_CACHED_DATA = 1001; // 本地没有登录缓存数据
    static const int LOGIN_CACHED_DATA_EXPIRED = 1002; //本地有缓存，但是该缓存已经失效
    static const int LOGIN_KEY_STORE_VERIFY_ERROR = 1004;
    static const int LOGIN_NEED_USER_DATA = 1005;
    static const int LOGIN_CODE_FOR_CONNECT = 1006;

    static const int LOGIN_NEED_USER_DATA_SERVER = 1010;
    static const int LOGIN_URL_USER_LOGIN = 1011; // 异账号：使用URL登陆成功
    static const int LOGIN_NEED_LOGIN = 1012;     // 异账号：需要进入登陆页
    static const int LOGIN_NEED_SELECT_ACCOUNT = 1013; // 异账号：需要弹出异帐号提示
    static const int LOGIN_ACCOUNT_REFRESH = 1014; // 异账号：通过URL将票据刷新

    static const int CONNECT_NO_CACHED_DATA = 1021; // 本地没有关联渠道登录缓存数据
    static const int CONNECT_CACHED_DATA_EXPIRED = 1022; //本地有缓存，但是该缓存已经失效
    static const int CONNECT_NO_MATCH_MAIN_OPENID = 1023; //关联账号与主账号不一致

    /** 1100 ~ 1199 字段是 FRIEND 模块相关的错误码 */
    static const int FRIEND_UNKNOWN_ERROR = 1100;

    /** 1200 ~ 1299 字段是 GROUP 模块相关的错误码 */
    static const int GROUP_UNKNOWN_ERROR = 1200;

    /** 1300 ~ 1399 字段是 NOTICE 模块相关的错误码 */
    static const int NOTICE_UNKNOWN_ERROR = 1300;

    /** 1400 ~ 1499 字段是 Push 模块相关的错误码 */
    static const int PUSH_RECEIVER_TEXT = 1400; // 收到推送消息
    static const int PUSH_NOTIFICATION_CLICK = 1401;    // 在通知栏点击收到的消息
    static const int PUSH_NOTIFICATION_SHOW = 1402;     // 收到通知之后，通知栏显示

    /** 1500 ~ 1599 字段是 WEBVIEW 模块相关的错误码 */
    static const int WEBVIEW_UNKNOWN_ERROR = 1500;

    static const int THIRD_ERROR = 9999;// 第三方错误情况，参考第三方错误码

    /** 1600 ~ 1699 字段是 Account 模块相关的错误码 */
    static const int INVALID_PASSWORD = 1600;
};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

using MSDKError = MSDK::MSDKError;

NS_MSDK_SPACE_NO_STL_END

#endif //MSDK_ERROR_H
