#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

struct GUAErrorCode
{
public:
    static const int UNKNOWN = -1;              // No need to handle.
    static const int SUCCESS = 0;               // Success
    static const int NO_ASSIGN = 1;             // input arguments without assignment,
    static const int CANCEL = 2;                // cancel by user
    static const int SYSTEM_ERROR = 3;          // system error,mainly not supported by system
    static const int NETWORK_ERROR = 4;         // network error,check network state
    static const int SERVER_ERROR = 5;          // check server error code
    static const int TIMEOUT = 6;               // request time out, try it later
    static const int NOT_SUPPORT = 7;           // this function is not support, use other
    static const int OPERATION_SYSTEM_ERROR = 8;// os error
    static const int NEED_PLUGIN = 9;           // the called plugin is not packaged, please check the plugin
    static const int NEED_LOGIN = 10;           // should be called after login
    static const int INVALID_ARGUMENT = 11;     // wrong arguments
    static const int NEED_SYSTEM_PERMISSION = 12; // need system permission,check permission list for each plugin
    static const int NEED_CONFIG = 13;          // wrong configuration, check configs
    static const int SERVICE_REFUSE = 14;       // system service is not supported
    static const int NEED_INSTALL_APP = 15;     // need install the app that plugin required
    static const int APP_NEED_UPGRADE = 16;     // third-party app version is too old,need update app
    static const int INITIALIZE_FAILED = 17;    // plugin initialized failed, check configs
    static const int EMPTY_CHANNEL = 18;        // channel arguments is wrong
    static const int FUNCTION_DISABLE = 19;     // function is forbidden to call, check config
    static const int NEED_REALNAME = 20;        // need real-name authentication
    static const int REALNAME_FAIL = 21;        // real-name authentication failed
    static const int IN_PROGRESS = 22;          // The last operation has not been completed, try again later
    static const int API_DEPRECATED = 23;       // API has been obsoleted, update the plugin
    static const int LIBCURL_ERROR = 24;        // libcurl network error, check libcurl error code
    static const int FREQUENCY_LIMIT = 25;      // Frequency limit
    static const int DINED_BY_APP = 26;         // Rejected by three parties, need to check the specific error
    static const int NEED_LOGIN_ACCOUNT = 27;   // Need pull up account login/register UI to login/register account
    static const int NEED_SET_ACCOUNT_INFO = 28;   // Need call SetAccountInfo first
    static const int BUILD_MAP_FAILED = 29;		// Build map failed, need to login with other account
    static const int NEED_RIGHT_ACCOUNT = 30;		// Current loggedin account is not the mapped account, please check and login with the right one
    static const int NEED_LOGIN_AND_QUERY_ID_TOKEN = 31;           // should be called if user didnt login or query ID Token

     /** 1000 ~ 1099 field is the error code related to Auth module */
    static const int LOGIN_UNKNOWN_ERROR = 1000;            // unknown login error,check thirdCode and thirdMsg
    static const int LOGIN_NO_CACHED_DATA = 1001;           // There is no login cache data locally
    static const int LOGIN_CACHED_DATA_EXPIRED = 1002;      // There is a cache locally, but the cache is invalid
    static const int LOGIN_KEY_STORE_VERIFY_ERROR = 1004;   // check the android keyStore config file
    static const int LOGIN_NEED_USER_DATA = 1005;           // need login first
     /* In strict login mode, the return value of the verification code is returned */
    static const int LOGIN_CODE_FOR_CONNECT = 1006;           // need login first

    static const int LOGIN_NEED_USER_DATA_SERVER = 1010;
    static const int LOGIN_URL_USER_LOGIN = 1011;       // Different account: successful login using URL
    static const int LOGIN_NEED_LOGIN = 1012;           // Different accounts: need to enter the landing page
    static const int LOGIN_NEED_SELECT_ACCOUNT = 1013;  // Different account: need to pop up different account prompt
    static const int LOGIN_ACCOUNT_REFRESH = 1014;      // Different account: Refresh the ticket via URL

    static const int CONNECT_NO_CACHED_DATA = 1021;         // There is no local channel login cache data
    static const int CONNECT_CACHED_DATA_EXPIRED = 1022;    // There is a cache locally, but the cache is invalid
    static const int CONNECT_NO_MATCH_MAIN_OPENID = 1023;   // The associated account is inconsistent with the main account

    /** 1100 ~ 1199 field is the error code related to FRIEND module */
    static const int FRIEND_UNKNOWN_ERROR = 1100;

    /** 1200 ~ 1299 field is the error code related to GROUP module */
    static const int GROUP_UNKNOWN_ERROR = 1200;

    /** 1300 ~ 1399 field is the error code related to NOTICE module */
    static const int NOTICE_UNKNOWN_ERROR = 1300;

    /** Fields 1400 ~ 1499 are error codes related to the Push module */
    static const int PUSH_RECEIVER_TEXT = 1400; // Receive a push message
    static const int PUSH_NOTIFICATION_CLICK = 1401;    // Received a message that the notification bar clicked
    static const int PUSH_NOTIFICATION_SHOW = 1402;     // After receiving the notification, the notification bar displays
    static const int BIND_OPENID_HAS_BIND = 1403; // Repeat binding error

    /** 1500 ~ 1599 field is the error code related to WEBVIEW module */
    static const int WEBVIEW_UNKNOWN_ERROR = 1500;

    /** 1600 ~ 1699 field is the error code related to Account module */
    static const int INVALID_PASSWORD = 1600;

    /** 1700 ~ 1799 field is the error code related to Update module */
    static const int UPDATE_UNKNOWN_ERROR = 1700;

    static const int THIRD_ERROR = 9999;// Third-party error conditions, refer to third-party error codes
};

GUA_NAMESPACE_END