/*!
 * @Module MSDK
 *
 * @Header  MSDKLogin.h
 * @Author  developer
 * @date 2018/2/20
 * @abstract
 * 登录、绑定以及获取个人信息
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_LOGIN_H
#define MSDK_LOGIN_H

#include "MSDKDefine.h"
#include "MSDKAccount.h"

#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif


NS_MSDK_BEGIN

// 登录类型，默认：0，扫码：1
#define MSDK_LOGIN_TYPE "login_type"
#define MSDK_NORMAL_LOGIN 0
#define MSDK_SCAN_LOGIN 1

#if MSDK_PLATFORM_WINDOWS
        class MSDKQrCodeRet : public MSDKBaseRet
{
public:
	// 渠道ID
	int channelID;

	// 渠道名
	std::string channel;

	//二维码url
	std::string qrCodeUrl;

	MSDKQrCodeRet() : MSDKBaseRet()
	{
		channelID = 0;
	}
};

#endif // MSDK_PLATFORM_WINDOWS


// MSDK 登录结果类
        class MSDK_EXPORT MSDKLoginRet : public MSDKBaseRet
        {

        public:
            // 用户 ID
            std::string openID;


            // 用户 凭证
            std::string token;

            // 过期时间
            int64_t tokenExpire;

            // 是否首次登陆，未知-1，否0，是1
            int firstLogin;

            // 首次注册的分发渠道
            std::string regChannelDis;

            // 昵称
            std::string userName;

            // 性别(int) 0未定义,1男, 2女
            int gender;

            // 出生日期(1987-2-23 11:33:33)
            std::string birthdate;

            // 头像链接
            std::string pictureUrl;

            // pf 值
            std::string pf;

            // pf key
            std::string pfKey;

            // 是否需要实名认证
            bool realNameAuth;

            // 渠道ID
            int channelID;

            // 渠道名
            std::string channel;

            // 额外的渠道信息
            std::string channelInfo;

            // 确认码，绑定失败后返回
            std::string confirmCode;

            // 确认码过期时间戳
            int64_t confirmCodeExpireTime;

            //绑定信息(JSON 数据，数组类型)
            std::string bindList;

            // 构造函数
            MSDKLoginRet() : MSDKBaseRet()
            {
                tokenExpire = 0;
                gender = 0;
                firstLogin = 0;
                realNameAuth= false;
                channelID=0;
                confirmCodeExpireTime = 0;
            }

            MSDKLoginRet(int retCode) : MSDKBaseRet(retCode)
            {
                tokenExpire = 0;
                gender = 0;
                firstLogin = 0;
                realNameAuth= false;
                channelID =0 ;
                confirmCodeExpireTime = 0;
            }

        AutoParser("com.itop.gcloud.msdk.api.login.MSDKLoginRet",
                   A(thirdCode, "ret"), A(thirdMsg, "msg"),
                   A(openID, "openid"), A(tokenExpire, "token_expire_time"),
                   A(firstLogin, "first"), A(regChannelDis, "reg_channel_dis"), A(userName, "user_name"),
                   A(pictureUrl, "picture_url"), A(realNameAuth, "need_name_auth"),
                   A(channelInfo, "channel_info"), A(bindList, "bind_list"),A(confirmCode,"confirm_code"),
                   A(confirmCodeExpireTime, "confirm_code_expire_time"), A(channelID, "channelid"),
                   O(retCode, retMsg, token, gender, birthdate, pf, pfKey, channel,
                     methodNameID,extraJson));
        };


// 登录监听
        class MSDK_EXPORT MSDKLoginObserver
        {

        public:
            //新增一个虚析构函数 不然 UE4 报错
            virtual ~MSDKLoginObserver(){};

            // 登录回调，包括 login、bind、autologin、switchuser 等
            virtual void OnLoginRetNotify(const MSDKLoginRet &loginRet) {};

            // 登出回调、应用唤醒回调
            virtual void OnBaseRetNotify(const MSDKBaseRet &baseRet) {};

#if MSDK_PLATFORM_WINDOWS
            // PC端登录二维码回调
	virtual void OnQrCodeNotify(const MSDKQrCodeRet &qrCodeRet) {};
#endif // MSDK_PLATFORM_WINDOWS

        };

// 关联渠道监听
        class MSDK_EXPORT MSDKConnectObserver
        {

        public:
            //新增一个虚析构函数 不然 UE4 报错
            virtual ~MSDKConnectObserver(){};

            // 调用Connect关联渠道时，会拉起渠道登录授权，并将关联结果在此回调返回
            virtual void OnConnectRetNotify(const MSDKLoginRet &loginRet) {};
        };

// 登录处理类
        class MSDK_EXPORT MSDKLogin
        {

        private :

            static MSDKLoginObserver *mLoginObserver;

            static MSDKConnectObserver *mConnectObserver;

#if MSDK_PLATFORM_WINDOWS
            static void LoginRetObserver(const InnerLoginRet &loginRet, const char *seqID)
	{
		MSDKLoginRet ret;
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerLoginRet to MSDKLoginRet start");
		//MSDKCompatManager::compatConvert(ret, loginRet);
		ret.methodNameID = loginRet.methodNameID;
		ret.retCode = loginRet.retCode;
		ret.retMsg = loginRet.retMsg.c_str();
		ret.thirdCode = loginRet.thirdCode;
		ret.thirdMsg = loginRet.thirdMsg.c_str();
		ret.extraJson = loginRet.extraJson.c_str();
		ret.openID = loginRet.openID.c_str();
		ret.token = loginRet.token.c_str();
		ret.tokenExpire = loginRet.tokenExpire;
		ret.firstLogin = loginRet.firstLogin;
		ret.regChannelDis = loginRet.regChannelDis.c_str();
		ret.userName = loginRet.userName.c_str();
		ret.gender = loginRet.gender;
		ret.birthdate = loginRet.birthdate.c_str();
		ret.pictureUrl = loginRet.pictureUrl.c_str();
		ret.pf = loginRet.pf.c_str();
		ret.pfKey = loginRet.pfKey.c_str();
		ret.realNameAuth = loginRet.realNameAuth;
		ret.channelID = loginRet.channelID;
		ret.channel = loginRet.channel.c_str();
		ret.channelInfo = loginRet.channelInfo.c_str();
		ret.confirmCode = loginRet.confirmCode.c_str();
		ret.confirmCodeExpireTime = loginRet.confirmCodeExpireTime;
		ret.bindList = loginRet.bindList.c_str();
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerLoginRet to MSDKLoginRet finish then will notify user");
		if (mLoginObserver && CheckLoginNotify(loginRet, seqID))
		{
			mLoginObserver->OnLoginRetNotify(ret);
		}
		else
		{
			MSDKPIX_LOG_ERROR(seqID, "login observer is null or this seqID in cache");
		}
	}

	static void BaseRetObserver(const InnerBaseRet &baseRet, const char *seqID)
	{
		MSDKBaseRet ret;
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet start");
		//MSDKCompatManager::compatConvert(ret, baseRet);
		ret.methodNameID = baseRet.methodNameID;
		ret.retCode = baseRet.retCode;
		ret.retMsg = baseRet.retMsg.c_str();
		ret.thirdCode = baseRet.thirdCode;
		ret.thirdMsg = baseRet.thirdMsg.c_str();
		ret.extraJson = baseRet.extraJson.c_str();
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet finish then will notify user");
		if (mLoginObserver)
		{
			mLoginObserver->OnBaseRetNotify(ret);
		}
		else
		{
			MSDKPIX_LOG_ERROR(seqID, "login observer is null");
		}
	}

	static void QrCodeRetObserver(const InnerQrCodeRet &qrCodeRet, const char *seqID)
	{
		MSDKQrCodeRet ret;
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerQrCodeRet to MSDKQrCodeRet start");
		//MSDKCompatManager::compatConvert(ret, baseRet);
		ret.methodNameID = qrCodeRet.methodNameID;
		ret.channel = qrCodeRet.channel.c_str();
		ret.channelID = qrCodeRet.channelID;
		ret.qrCodeUrl = qrCodeRet.qrCodeUrl.c_str();
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerQrCodeRet to MSDKQrCodeRet finish then will notify user");
		if (mLoginObserver)
		{
			mLoginObserver->OnQrCodeNotify(ret);
		}
		else
		{
			MSDKPIX_LOG_ERROR(seqID, "login observer is null");
		}
	}

	static void ConnectRetObserver(const InnerLoginRet &loginRet, const char *seqID)
    {
        MSDKPIX_LOG_DEBUG(seqID, "ConnectRetObserver");
        MSDKLoginRet *pRet = new MSDKLoginRet();
        //MSDKCompatManager::compatConvert(*pRet, loginRet);

        if (mConnectObserver)
        {
            mConnectObserver->OnConnectRetNotify(*pRet);
            delete pRet;
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "connect observer is null");
            delete pRet;
        }
    }

	static void SetPRVLoginObserver(
		typename T<InnerLoginRet>::InnerRetCallback loginRetObserver,
		typename T<InnerBaseRet>::InnerRetCallback baseRetObserver,
		typename T<InnerQrCodeRet>::InnerRetCallback qrCodeRetObserver);
#else

            static void LoginRetObserver(const InnerLoginRet &loginRet, const char *seqID)
            {
                MSDKPIX_LOG_DEBUG(seqID, "LoginRetObserver");
                // 拦截Connect的登录结果
                if (loginRet.methodNameID == kMethodNameConnect) {
                    ConnectRetObserver(loginRet, seqID);
                    return;
                }

                if (!CheckLoginNotify(loginRet, seqID)) {
                    MSDKPIX_LOG_ERROR(seqID, "this seqID in cache");
                    return;
                }

                InnerLoginRet innertLoginRet = loginRet;

                // TODO: 注释
                if (GetBindUIEnable())
                {
                    MSDKPIX_LOG_DEBUG(seqID, "login ui enable");
                    if (CheckHandleInBindUI(innertLoginRet, seqID))
                    {
                        MSDKPIX_LOG_DEBUG(seqID, "this callback handle in UI");
                        return;
                    }
                }
                else
                {
                    MSDKPIX_LOG_DEBUG(seqID, "login ui dispable");
                }

                MSDKLoginRet *pRet = new MSDKLoginRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerLoginRet to MSDKLoginRet start");
                MSDKCompatManager::compatConvert(*pRet, innertLoginRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerLoginRet to MSDKLoginRet finish then will notify user");

                if(loginRet.retCode != MSDKError::SUCCESS){
                    // todo
                    // REPORT_Plugin_MONITOR_END(seqID, loginRet, "ByPlugin");
                }

                if (mLoginObserver)
                {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                        MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 LoginRetObserver");
                        mLoginObserver->OnLoginRetNotify(*pRet);
                        delete pRet;
                    });
#else
                    mLoginObserver->OnLoginRetNotify(*pRet);
                    delete pRet;
#endif
                }
                else
                {
                    MSDKPIX_LOG_ERROR(seqID, "login observer is null");
                    delete pRet;
                }
            }

            static void BaseRetObserver(const InnerBaseRet &baseRet, const char *seqID)
            {
                MSDKPIX_LOG_DEBUG(seqID, "BaseRetObserver");

                if (GetBindUIEnable()) {
                    MSDKPIX_LOG_DEBUG(seqID, "bind ui enable");
                    if (CheckHandleInBindUI(baseRet, seqID)) {
                        MSDKPIX_LOG_DEBUG(seqID, "this callback handle in Bind UI");
                        return;
                    }
                }
                else
                {
                    MSDKPIX_LOG_DEBUG(seqID, "bind ui dispable");
                }


                MSDKBaseRet *pRet = new MSDKBaseRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet start");
                MSDKCompatManager::compatConvert(*pRet, baseRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet finish then will notify user");
                if (mLoginObserver)
                {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                    MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 BaseRetObserver");
                    mLoginObserver->OnBaseRetNotify(*pRet);
                    delete pRet;
            });
#else
                    mLoginObserver->OnBaseRetNotify(*pRet);
                    delete pRet;
#endif
                }
                else
                {
                    MSDKPIX_LOG_ERROR(seqID, "login observer is null");
                    delete pRet;
                }
            }

            static void ConnectRetObserver(const InnerLoginRet &loginRet, const char *seqID)
            {
                MSDKPIX_LOG_DEBUG(seqID, "ConnectRetObserver");
                MSDKLoginRet *pRet = new MSDKLoginRet();
                MSDKCompatManager::compatConvert(*pRet, loginRet);
                if (mConnectObserver)
                {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                    MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 ConnectRetObserver");
                    mConnectObserver->OnConnectRetNotify(*pRet);
                    delete pRet;
    });
#else
                    mConnectObserver->OnConnectRetNotify(*pRet);
                    delete pRet;
#endif
                }
                else
                {
                    MSDKPIX_LOG_ERROR(seqID, "connect observer is null");
                    delete pRet;
                }
            }

            static void SetPRVLoginObserver(
                    typename T<InnerLoginRet>::InnerRetCallback loginRetObserver,
                    typename T<InnerBaseRet>::InnerRetCallback baseRetObserver);

#endif

            ~MSDKLogin();



            static void SetPRVConnectObserver( typename T<InnerLoginRet>::InnerRetCallback connectRetObserver);

            static bool GetLoginUIEnable();

            static bool GetBindUIEnable();

            static bool CheckLoginNotify(const InnerLoginRet &loginRet, const char *seqID);

            static bool CheckHandleInUI(InnerLoginRet &loginRet, const char *seqID);

            static bool CheckHandleInUI(const InnerBaseRet &baseRet, const char *seqID);

            static bool CheckHandleInBindUI(const InnerBaseRet &baseRet, const char *seqID);

            static bool CheckHandleAccountRetInUI(const InnerBaseRet &accountRet, const char *seqID);

        public:
            MSDK_EXPORT_UE static bool GetPRVLoginRet(InnerLoginRet &ret);

            static bool GetPRVConnectRet(InnerConnectRet &ret);



            /**
             * 设置登录回调
             * @param observer 登录回调
             */
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
            public:
    MSDK_EXPORT_UE  static void SetLoginObserver(MSDKLoginObserver *observer);
#else
            static void SetLoginObserver(MSDKLoginObserver *observer)
            {
                if (!observer) {
                    MSDKPIX_LOG_ERROR("", "MSDKLoginObserver can not be NULL");
                } else {
                    mLoginObserver = observer;
                    SetPRVLoginObserver(LoginRetObserver, BaseRetObserver);
                }
            }
#endif

            /**
             * 设置登录回调
             * @param observer 登录回调
             */
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
            public:
    MSDK_EXPORT_UE  static void SetConnectObserver(MSDKConnectObserver *observer);
#else
            static void SetConnectObserver(MSDKConnectObserver *observer)
            {
                if (!observer) {
                    MSDKPIX_LOG_ERROR("", "MSDKConnectObserver can not be NULL");
                } else {
                    mConnectObserver = observer;
                    SetPRVConnectObserver(ConnectRetObserver);
                }
            }
#endif

            /**
             * 自动登录&刷新票据
             */
            MSDK_EXPORT_UE static void AutoLogin();

            /**
            * 带 UI 的登录
            * @param extraJson 预留字段
            */
            static void LoginUI(const String &extraJson = "");


            /**
             * 带 UI 的绑定
             * @param extraJson 预留字段
             */
            static void BindUI(const String &extraJson = "");

            /**
             * 登录指定渠道
             * @param channel 渠道信息，比如“Facebook”
             * @param permissions 登录授权权限列表，多个权限用逗号分隔，比如 user_info,inapp_friends
             * @param subChannel 子渠道
             */
            MSDK_EXPORT_UE static void  Login(const String &channel, const String &permissions = "",
                                              const String &subChannel = "", const String &extraJson = "");


            /**
             * 视频号授权
             * @param channel 渠道信息
             * @param permissions 视频号授权权限列表，多个权限用逗号分隔，视频号授权需传入“snsapi_channels_livestream”
             * @param subChannel 子渠道
             */

            MSDK_EXPORT_UE static void  ChannelPermissionAuth(const String &channel, const String &permissions = "",
                                                              const String &subChannel = "", const String &extraJson = "");

            /**
             * 绑定指定渠道
             * @param channel 渠道信息，比如“Facebook”
             * @param permissions 登录授权权限列表
             */
            MSDK_EXPORT_UE static void Bind(const String &channel, const String &permissions = "",
                                            const String &subChannel = "", const String &extraJson = "");

            /**
             * 关联指定渠道
             * @param channel 渠道信息，比如“Facebook”
             * @param permissions 登录授权权限列表，多个权限用逗号分隔，比如 user_info,inapp_friends
            */
            MSDK_EXPORT_UE static void Connect(const String &channel, const String &permissions = "",
                                               const String &subChannel = "", const String &extraJson = "");

            /**
             * 解除关联的渠道
             * @param channel 渠道信息，比如“Facebook”
            */
            MSDK_EXPORT_UE static void UnConnect(const String &channel);


            /**
             * 获取本地登录态
             * @param loginRet 登录态结构体
             * @return 操作成功标志；如本地无登录态等情况会返回 false
             */
#if MSDK_PLATFORM_WINDOWS
            MSDK_EXPORT_UE static bool GetLoginRet(MSDKLoginRet &loginRet) {
	  InnerLoginRet innerRet;
	  bool status = GetPRVLoginRet(innerRet);
	  loginRet.methodNameID = innerRet.methodNameID;
	  loginRet.retCode = innerRet.retCode;
	  loginRet.retMsg = innerRet.retMsg.c_str();
	  loginRet.thirdCode = innerRet.thirdCode;
	  loginRet.thirdMsg = innerRet.thirdMsg.c_str();
	  loginRet.extraJson = innerRet.extraJson.c_str();
	  loginRet.openID = innerRet.openID.c_str();
	  loginRet.token = innerRet.token.c_str();
	  loginRet.tokenExpire = innerRet.tokenExpire;
	  loginRet.firstLogin = innerRet.firstLogin;
	  loginRet.regChannelDis = innerRet.regChannelDis.c_str();
	  loginRet.userName = innerRet.userName.c_str();
	  loginRet.gender = innerRet.gender;
	  loginRet.birthdate = innerRet.birthdate.c_str();
	  loginRet.pictureUrl = innerRet.pictureUrl.c_str();
	  loginRet.pf = innerRet.pf.c_str();
	  loginRet.pfKey = innerRet.pfKey.c_str();
	  loginRet.realNameAuth = innerRet.realNameAuth;
	  loginRet.channelID = innerRet.channelID;
	  loginRet.channel = innerRet.channel.c_str();
	  loginRet.channelInfo = innerRet.channelInfo.c_str();
	  loginRet.confirmCode = innerRet.confirmCode.c_str();
	  loginRet.confirmCodeExpireTime = innerRet.confirmCodeExpireTime;
	  loginRet.bindList = innerRet.bindList.c_str();

	  return status;
  }
#elif MSDK_ENGINE_UE4_SIMULATE_LOGIN
            MSDK_EXPORT_UE static bool GetLoginRet(MSDKLoginRet &loginRet);
#else
            MSDK_EXPORT static bool GetLoginRet(MSDKLoginRet &loginRet)
            {
                InnerLoginRet innerRet;
                bool status = GetPRVLoginRet(innerRet);
                MSDKCompatManager::compatConvert(loginRet, innerRet);
                return status;
            }
#endif

            /**
             * 获取本地登录态
             * @param connectRet 关联登录态结构体
             * @return 操作成功标志；如本地无登录态等情况会返回 false
             */
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
            MSDK_EXPORT_UE static bool GetConnectRet(MSDKLoginRet &loginRet);
#else
            MSDK_EXPORT static bool GetConnectRet(MSDKLoginRet &loginRet)
            {
                InnerConnectRet innerRet;
                bool status = GetPRVConnectRet(innerRet);
                InnerLoginRet innerLoginRet = (InnerLoginRet)innerRet;
                MSDKCompatManager::compatConvert(loginRet, innerRet);
                return status;
            }
#endif

            /**
             * 出现异账号情况下，选择是否切换异账号登录
             * @param useLaunchUser 是否切换账号登录
             * @return 操作成功标志；不符合异账号切换的情况下会返回 false
             */
            MSDK_EXPORT_UE static bool SwitchUser(bool useLaunchUser);



            /**
             * 查询是否可绑定，仅支持自建账号的查询
             */
            MSDK_EXPORT_UE static void CanBind(const String &channel, const String &channelInfo, const String &extraJson = "");

            /**
             * 查询个人账号信息
             */
            MSDK_EXPORT_UE  static void QueryUserInfo();

            /**
             * 登出
             */
            MSDK_EXPORT_UE  static void Logout(const String &channel = "", const String &subChannel = "", const bool channelOnly = false);

            /**
             * 登录或者绑定失败后，通过确认码再次尝试登录
             * @param actionType 操作类型：0 一般登录（暂不支持）（配合 Bind 接口）；1 恢复渠道账号绑定的游客 (配合 bind 接口)，并登录到游客; 2  用于一般登录（配合 Check 接口）
             * @param confirmCode 确认码；绑定失败的情况下，由后台返回。缺省值为上次绑定失败时 后台的返回值
             * @param extraJson 扩展 JSON 数据
             */
            MSDK_EXPORT_UE static void LoginWithConfirmCode(const int actionType = 0, const String &confirmCode = "", const String &extraJson = "");



            /**
             * 重置游客账号
             */
            MSDK_EXPORT_UE static void ResetGuest();

            MSDK_EXPORT_UE static void CheckUniversalLink(const String &channel, const String &subChannel = "", const String &extra = "");


#if MSDK_PLATFORM_WINDOWS
            /**
	 * 预加载微信dll，可避免首次微信扫码延迟2s的问题
	 */
	MSDK_EXPORT_UE static void PreLoadWeChatLibrary();

	/**
	 * 设置安装渠道号
	 */
	MSDK_EXPORT_UE static void SetInstallChannel(const String &channel);

	/**
	 * 透传实名注册结果
	 */
	MSDK_EXPORT_UE static void OnRealNameAuthFinished(const String &channel, const String &openid, const String &token, bool result);

	/**
	 * 卸载MSDK DLL
	 */
	MSDK_EXPORT_UE static void UnInstall();

#endif
            /**
             * 先检查是渠道是否已经生成过 MSDK 账号，生成过，返回登录结果，没有生成过的话返回
             */
            MSDK_EXPORT_UE static void CheckLogin(const String &channel, const String &permissions = "", const String &subChannel = "",const String &extraJson = "");

            /**
             * 检查账号是否可以绑定，可以绑定的话返回 ConfirmCode，游戏查询用户信息之后，进行 BindWithConfirmCode 操作
             */
            MSDK_EXPORT_UE static void Check(const String &channel, const String &permissions = "", const String &subChannel = "", const String &extraJson = "");

            /**
             * 根据 confirmCode 绑定 MSDK 渠道
             */
            MSDK_EXPORT_UE static void BindWithConfirmCode(const String &confirmCode, int channelID, const String &extraJson = "");
        };

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

#if MSDK_PLATFORM_WINDOWS
            class MSDKQrCodeRet : public MSDKBaseRet
{
public:
    // 渠道ID
    int channelID;

    // 渠道名
    String channel;

    //二维码url
    String qrCodeUrl;

    MSDKQrCodeRet() : MSDKBaseRet()
    {
        channelID = 0;
    }

    MSDKQrCodeRet(const MSDK::MSDKQrCodeRet &qrCodeRet) : MSDKBaseRet(qrCodeRet)
    {
        channelID = qrCodeRet.channelID;
        channel = qrCodeRet.channel;
        qrCodeUrl = qrCodeRet.qrCodeUrl;
    }
};
#endif // MSDK_PLATFORM_WINDOWS

// MSDK 登录结果类
            class MSDK_EXPORT MSDKLoginRet : public MSDKBaseRet
            {

            public:
                // 用户 ID
                String openID;

                // 用户 凭证
                String token;

                // 过期时间
                int64_t tokenExpire;

                // 是否首次登陆，未知-1，否0，是1
                int firstLogin;

                // 首次注册的分发渠道
                String regChannelDis;

                // 昵称
                String userName;

                // 性别(int) 0未定义,1男, 2女
                int gender;

                // 出生日期(1987-2-23 11:33:33)
                String birthdate;

                // 头像链接
                String pictureUrl;

                // pf 值
                String pf;

                // pf key
                String pfKey;

                // 是否需要实名认证
                bool realNameAuth;

                // 渠道ID
                int channelID;

                // 渠道名
                String channel;

                // 额外的渠道信息
                String channelInfo;

                // 确认码，绑定失败后返回
                String confirmCode;

                // 确认码过期时间戳
                int64_t confirmCodeExpireTime;

                //绑定信息(JSON 数据，数组类型)
                String bindList;

                // 构造函数
                MSDKLoginRet() : MSDKBaseRet()
                {
                    tokenExpire = 0;
                    gender = 0;
                    firstLogin = 0;
                    realNameAuth= false;
                    channelID=0;
                    confirmCodeExpireTime = 0;
                }

                MSDKLoginRet(int retCode) : MSDKBaseRet(retCode)
                {
                    tokenExpire = 0;
                    gender = 0;
                    firstLogin = 0;
                    realNameAuth= false;
                    channelID =0 ;
                    confirmCodeExpireTime = 0;
                }

                MSDKLoginRet(const MSDK::MSDKLoginRet &loginRet) : MSDKBaseRet(loginRet)
                {
                    openID = loginRet.openID;
                    token = loginRet.token;
                    tokenExpire = loginRet.tokenExpire;
                    firstLogin = loginRet.firstLogin;
                    regChannelDis = loginRet.regChannelDis;
                    userName = loginRet.userName;
                    gender = loginRet.gender;
                    birthdate = loginRet.birthdate;
                    pictureUrl = loginRet.pictureUrl;
                    pf = loginRet.pf;
                    pfKey = loginRet.pfKey;
                    realNameAuth = loginRet.realNameAuth;
                    channelID = loginRet.channelID;
                    channel = loginRet.channel;
                    channelInfo = loginRet.channelInfo;
                    confirmCode = loginRet.confirmCode;
                    confirmCodeExpireTime = loginRet.confirmCodeExpireTime;
                    bindList = loginRet.bindList;
                }

            AutoParser("com.itop.gcloud.msdk.api.login.MSDKLoginRet",
                       A(thirdCode, "ret"), A(thirdMsg, "msg"),
                       A(openID, "openid"), A(tokenExpire, "token_expire_time"),
                       A(firstLogin, "first"), A(regChannelDis, "reg_channel_dis"), A(userName, "user_name"),
                       A(pictureUrl, "picture_url"), A(realNameAuth, "need_name_auth"),
                       A(channelInfo, "channel_info"), A(bindList, "bind_list"),A(confirmCode,"confirm_code"),
                       A(confirmCodeExpireTime, "confirm_code_expire_time"), A(channelID, "channelid"),
                       O(retCode, retMsg, token, gender, birthdate, pf, pfKey, channel,
                         methodNameID,extraJson));
            };

// 登录监听
            class MSDK_EXPORT MSDKLoginObserver
            {
            public:
                //新增一个虚析构函数 不然 UE4 报错
                virtual ~MSDKLoginObserver(){};

                // 登录回调，包括 login、bind、autologin、switchuser 等
                virtual void OnLoginRetNotify(const MSDKLoginRet &loginRet) {};

                // 登出回调、应用唤醒回调
                virtual void OnBaseRetNotify(const MSDKBaseRet &baseRet) {};

#if MSDK_PLATFORM_WINDOWS
                // PC端登录二维码回调
    virtual void OnQrCodeNotify(const MSDKQrCodeRet &qrCodeRet) {};
#endif // MSDK_PLATFORM_WINDOWS

            };

// 关联渠道监听
            class MSDK_EXPORT MSDKConnectObserver
            {

            public:
                //新增一个虚析构函数 不然 UE4 报错
                virtual ~MSDKConnectObserver(){};

                // 调用Connect关联渠道时，会拉起渠道登录授权，并将关联结果在此回调返回
                virtual void OnConnectRetNotify(const MSDKLoginRet &loginRet) {};
            };

            class MSDKLoginObserverAdapter : public MSDK::MSDKLoginObserver
            {
            public:
                // 登录回调，包括 login、bind、autologin、switchuser 等
                void OnLoginRetNotify(const MSDK::MSDKLoginRet &loginRet);

                // 登出回调、应用唤醒回调
                void OnBaseRetNotify(const MSDK::MSDKBaseRet &baseRet);

#if MSDK_PLATFORM_WINDOWS
                // PC端登录二维码回调
    void OnQrCodeNotify(const MSDK::MSDKQrCodeRet &qrCodeRet);
#endif // MSDK_PLATFORM_WINDOWS

                MSDKSpace::NoSTL::MSDKLoginObserver *mObserver = NULL;
            };

            class MSDKConnectObserverAdapter : public MSDK::MSDKConnectObserver
            {
            public:
                void OnConnectRetNotify(const MSDK::MSDKLoginRet &loginRet);

                MSDKSpace::NoSTL::MSDKConnectObserver *mObserver = NULL;
            };

            class MSDK_EXPORT MSDKLogin
            {
            private:
                static MSDKLoginObserverAdapter mLoginObserverAdapter;

                static MSDKConnectObserverAdapter mConnectObserverAdapter;

            public:

                MSDK_EXPORT_UE static bool GetPRVLoginRet(InnerLoginRet &ret);

                static bool GetPRVConnectRet(InnerConnectRet &ret);

                /**
                 * 设置登录回调
                 * @param observer 登录回调
                 */
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
                public:
    MSDK_EXPORT_UE  static void SetLoginObserver(MSDKLoginObserver *observer);
#else
                static void SetLoginObserver(MSDKLoginObserver *observer)
                {
                    if (!observer) {
                        MSDKPIX_LOG_ERROR("", "MSDKLoginObserver can not be NULL");
                    } else {
                        mLoginObserverAdapter.mObserver = observer;
                        MSDK::MSDKLogin::SetLoginObserver(&mLoginObserverAdapter);
                    }
                }
#endif

                /**
                 * 设置登录回调
                 * @param observer 登录回调
                 */
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
                public:
    MSDK_EXPORT_UE  static void SetConnectObserver(MSDKConnectObserver *observer);
#elif MSDK_ENGINE_UE4_PLATFORM_MAC
#else
                static void SetConnectObserver(MSDKConnectObserver *observer)
                {
                    if (!observer) {
                        MSDKPIX_LOG_ERROR("", "MSDKConnectObserver can not be NULL");
                    } else {
                        mConnectObserverAdapter.mObserver = observer;
                        MSDK::MSDKLogin::SetConnectObserver(&mConnectObserverAdapter);
                    }
                }
#endif

                /**
                 * 自动登录&刷新票据
                 */
                MSDK_EXPORT_UE static void AutoLogin();

                /**
                 * 带 UI 的登录
                 * @param extraJson 预留字段
                 */
                static void LoginUI(const String &extraJson = "");

                /**
                 * 带 UI 的绑定
                 * @param extraJson 预留字段
                 */
                static void BindUI(const String &extraJson = "");

                /**
                 * 登录指定渠道
                 * @param channel 渠道信息，比如“Facebook”
                 * @param permissions 登录授权权限列表，多个权限用逗号分隔，比如 user_info,inapp_friends
                 * @param subChannel 子渠道
                 */
                MSDK_EXPORT_UE static void  Login(const String &channel,
                                                  const String &permissions = "",
                                                  const String &subChannel = "",
                                                  const String &extraJson = "");

                /**
                 * 微信视频号授权
                 * @param channel 渠道信息，比如“WeChat”
                 * @param permissions 视频号授权权限列表，多个权限用逗号分隔，视频号授权需传入“snsapi_channels_livestream”
                 * @param subChannel 子渠道
                 */

                MSDK_EXPORT_UE static void ChannelPermissionAuth(const String &channel, const String &permissions = "",
                                                                 const String &subChannel = "", const String &extraJson = "");

                /**
                 * 绑定指定渠道
                 * @param channel 渠道信息，比如“Facebook”
                 * @param permissions 登录授权权限列表
                 */
                MSDK_EXPORT_UE static void Bind(const String &channel,
                                                const String &permissions = "",
                                                const String &subChannel = "",
                                                const String &extraJson = "");

                /**
                 * 关联指定渠道
                 * @param channel 渠道信息，比如“Facebook”
                 * @param permissions 登录授权权限列表，多个权限用逗号分隔，比如 user_info,inapp_friends
                 */
                MSDK_EXPORT_UE static void Connect(const String &channel,
                                                   const String &permissions = "",
                                                   const String &subChannel = "",
                                                   const String &extraJson = "");

                /**
                 * 解除关联的渠道
                 * @param channel 渠道信息，比如“Facebook”
                 */
                MSDK_EXPORT_UE static void UnConnect(const String &channel);

#if MSDK_PLATFORM_WINDOWS
                MSDK_EXPORT_UE static bool GetLoginRet(MSDKLoginRet &loginRet) {
        InnerLoginRet innerRet;
        bool status = GetPRVLoginRet(innerRet);
        loginRet.methodNameID = innerRet.methodNameID;
        loginRet.retCode = innerRet.retCode;
        loginRet.retMsg = innerRet.retMsg.c_str();
        loginRet.thirdCode = innerRet.thirdCode;
        loginRet.thirdMsg = innerRet.thirdMsg.c_str();
        loginRet.extraJson = innerRet.extraJson.c_str();
        loginRet.openID = innerRet.openID.c_str();
        loginRet.token = innerRet.token.c_str();
        loginRet.tokenExpire = innerRet.tokenExpire;
        loginRet.firstLogin = innerRet.firstLogin;
        loginRet.regChannelDis = innerRet.regChannelDis.c_str();
        loginRet.userName = innerRet.userName.c_str();
        loginRet.gender = innerRet.gender;
        loginRet.birthdate = innerRet.birthdate.c_str();
        loginRet.pictureUrl = innerRet.pictureUrl.c_str();
        loginRet.pf = innerRet.pf.c_str();
        loginRet.pfKey = innerRet.pfKey.c_str();
        loginRet.realNameAuth = innerRet.realNameAuth;
        loginRet.channelID = innerRet.channelID;
        loginRet.channel = innerRet.channel.c_str();
        loginRet.channelInfo = innerRet.channelInfo.c_str();
        loginRet.confirmCode = innerRet.confirmCode.c_str();
        loginRet.confirmCodeExpireTime = innerRet.confirmCodeExpireTime;
        loginRet.bindList = innerRet.bindList.c_str();

        return status;
    }
#elif MSDK_ENGINE_UE4_SIMULATE_LOGIN
                MSDK_EXPORT_UE static bool GetLoginRet(MSDKLoginRet &loginRet);
#else
                MSDK_EXPORT static bool GetLoginRet(MSDKLoginRet &loginRet) {
                    MSDK::MSDKLoginRet ret;
                    bool status = MSDK::MSDKLogin::GetLoginRet(ret);

                    loginRet = ret;
                    return status;
                }
#endif

                /**
                 * 获取本地登录态
                 * @param connectRet 关联登录态结构体
                 * @return 操作成功标志；如本地无登录态等情况会返回 false
                 */
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
                MSDK_EXPORT_UE static bool GetConnectRet(MSDKLoginRet &loginRet);
#else
                MSDK_EXPORT static bool GetConnectRet(MSDKLoginRet &loginRet) {
                    MSDK::MSDKLoginRet ret;
                    bool status = MSDK::MSDKLogin::GetConnectRet(ret);

                    loginRet = ret;
                    return status;
                }
#endif

                /**
                 * 出现异账号情况下，选择是否切换异账号登录
                 * @param useLaunchUser 是否切换账号登录
                 * @return 操作成功标志；不符合异账号切换的情况下会返回 false
                 */
                MSDK_EXPORT_UE static bool SwitchUser(bool useLaunchUser);

                /**
                 * 查询是否可绑定，仅支持自建账号的查询
                 */
                MSDK_EXPORT_UE static void CanBind(const String &channel, const String &channelInfo, const String &extraJson = "");

                /**
                 * 查询个人账号信息
                 */
                MSDK_EXPORT_UE  static void QueryUserInfo();

                /**
                 * 登出
                 */
                MSDK_EXPORT_UE  static void Logout(const String &channel = "", const String &subChannel = "", const bool channelOnly = false);

                /**
                 * 登录或者绑定失败后，通过确认码再次尝试登录
                 * @param actionType 操作类型：0 一般登录（暂不支持）（配合 Bind 接口）；1 恢复渠道账号绑定的游客 (配合 bind 接口)，并登录到游客; 2  用于一般登录（配合 Check 接口）
                 * @param confirmCode 确认码；绑定失败的情况下，由后台返回。缺省值为上次绑定失败时 后台的返回值
                 * @param extraJson 扩展 JSON 数据
                 */
                MSDK_EXPORT_UE static void LoginWithConfirmCode(const int actionType = 0, const String &confirmCode = "", const String &extraJson = "");

                /**
                 * 重置游客账号
                 */
                MSDK_EXPORT_UE static void ResetGuest();

                MSDK_EXPORT_UE static void CheckUniversalLink(const String &channel, const String &subChannel = "", const String &extra = "");

#if MSDK_PLATFORM_WINDOWS
                /**
	 * 预加载微信dll，可避免首次微信扫码延迟2s的问题
	 */
	MSDK_EXPORT_UE static void PreLoadWeChatLibrary();

	/**
	 * 设置安装渠道号
	 */
	MSDK_EXPORT_UE static void SetInstallChannel(const String &channel);

	/**
	 * 透传实名注册结果
	 */
	MSDK_EXPORT_UE static void OnRealNameAuthFinished(const String &channel, const String &openid, const String &token, bool result);

	/**
	 * 卸载MSDK DLL
	 */
	MSDK_EXPORT_UE static void UnInstall();

#endif

                /**
                 * 先检查是渠道是否已经生成过 MSDK 账号，生成过，返回登录结果，没有生成过的话返回
                 */
                MSDK_EXPORT_UE static void CheckLogin(const String &channel, const String &permissions = "", const String &subChannel = "", const String &extraJson = "");

                /**
                 * 检查账号是否可以绑定，可以绑定的话返回 ConfirmCode，游戏查询用户信息之后，进行 BindWithConfirmCode 操作
                 */
                MSDK_EXPORT_UE static void Check(const String &channel, const String &permissions = "", const String &subChannel = "", const String &extraJson = "");

                /**
                 * 根据 confirmCode 绑定 MSDK 渠道
                 */
                MSDK_EXPORT_UE static void BindWithConfirmCode(const String &confirmCode, int channelID, const String &extraJson = "");
            };

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDK_LOGIN_H */
