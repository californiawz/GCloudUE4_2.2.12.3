#ifndef MSDK_Account_H
#define MSDK_Account_H


#include "MSDKDefine.h"
#include "MSDKMacros.h"
#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif


NS_MSDK_BEGIN

class MSDK_EXPORT MSDKAccountRet : public MSDKBaseRet
{
public:
    // 渠道ID
    int channelID;

    // 渠道名
    std::string channel;

    // 后台 seq 字段
    std::string seqID;

    std::string username;

    std::string uid;

    std::string token;

    std::string expiretime;

    int isRegister;

    int isSetPassword;

    int isReceiveEmail;

    int verifyCodeExpireTime;

    AutoParser("com.itop.gcloud.msdk.api.account.MSDKAccountRet",
               A(thirdCode, "ret"), A(thirdMsg, "msg"), A(username, "user_name"), A(seqID, "seq"), A(expiretime, "expire"),
               O(retCode, retMsg, channelID, channel, methodNameID, token, uid), A(isRegister, "is_register"), A(isSetPassword, "isset_pwd"),
               A(isReceiveEmail, "is_receive_email"), A(verifyCodeExpireTime, "expire_time"), A(extraJson, "retExtraJson"));

};


class MSDK_EXPORT MSDKAccountObserver
{
public:
    virtual ~MSDKAccountObserver() {};

    virtual void OnAccountNotify(const MSDKAccountRet &accountRet) {};
};

class MSDK_EXPORT MSDKAccount
{
public:
    friend class MSDKLogin;
private:
    static MSDKAccountObserver *mAccountObserver;
#if MSDK_PLATFORM_WINDOWS
	static void BaseRetObserver(const InnerAccountRet &accountRet, const char *seqID)
	{
		LOG_DEBUG(seqID, "BaseRetObserver");

		if (GetBindUIEnable()) {
			MSDKPIX_LOG_ERROR(seqID, "bind ui enable");
			if (CheckHandleAccountRetInBindUI(accountRet, seqID))
			{
				MSDKPIX_LOG_ERROR(seqID, "this callback handle in bind UI");
				return;
			}
		}
		else
		{
			MSDKPIX_LOG_ERROR(seqID, "bind ui dispable");
		}

		MSDKAccountRet ret;
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet start");
		//MSDKCompatManager::compatConvert(*pRet, accountRet);
		ret.channelID = accountRet.channelID;
		ret.channel = accountRet.channel.c_str();
		ret.seqID = accountRet.seqID.c_str();
		ret.username = accountRet.username.c_str();
		ret.uid = accountRet.uid.c_str();
		ret.token = accountRet.token.c_str();
		ret.expiretime = accountRet.expiretime.c_str();
		ret.isRegister = accountRet.isRegister;
		ret.isSetPassword = accountRet.isSetPassword;
		ret.isReceiveEmail = accountRet.isReceiveEmail;
		ret.verifyCodeExpireTime = accountRet.verifyCodeExpireTime;
		ret.methodNameID = accountRet.methodNameID;
		ret.retCode = accountRet.retCode;
		ret.retMsg = accountRet.retMsg.c_str();
		ret.thirdCode = accountRet.thirdCode;
		ret.thirdMsg = accountRet.thirdMsg.c_str();
		ret.extraJson = accountRet.extraJson.c_str();
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet finish then will notify user");
		if (mAccountObserver)
		{
			mAccountObserver->OnAccountNotify(ret);
		}
		else
		{
			MSDKPIX_LOG_ERROR(seqID, "account observer is null");
		}
	}
#else
    static void BaseRetObserver(const InnerAccountRet &accountRet, const char *seqID)
    {
        MSDKPIX_LOG_DEBUG(seqID, "BaseRetObserver");

        if (GetBindUIEnable()) {
            MSDKPIX_LOG_ERROR(seqID, "bind ui enable");
            if (CheckHandleAccountRetInBindUI(accountRet, seqID))
            {
                MSDKPIX_LOG_ERROR(seqID, "this callback handle in bind UI");
                return;
            }
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "bind ui dispable");
        }


        MSDKAccountRet *pRet = new MSDKAccountRet();
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet start");
        MSDKCompatManager::compatConvert(*pRet, accountRet);
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet finish then will notify user");
        if (mAccountObserver)
        {
#if MSDK_ENGINE_UE4
            AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
            MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 BaseRetObserver");
            mAccountObserver->OnAccountNotify(*pRet);
            delete pRet;
        });
#else
        mAccountObserver->OnAccountNotify(*pRet);
        delete pRet;
#endif
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "account observer is null");
            delete pRet;
        }
    }
#endif

    ~MSDKAccount();

    static bool CheckHandleAccountRetInUI(const InnerBaseRet &accountRet, const char *seqID);

    static bool CheckHandleAccountRetInBindUI(const InnerAccountRet &accountRet, const char *seqID);

    static void SetPRVAccountObserver(typename T<InnerAccountRet>::InnerRetCallback baseRetObserver);
    
    static bool GetLoginUIEnable();

    static bool GetBindUIEnable();

public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
	MSDK_EXPORT_UE static void SetAccountObserver(MSDKAccountObserver *observer);
#else
    static void SetAccountObserver(MSDKAccountObserver *observer)
    {
        mAccountObserver = observer;
        SetPRVAccountObserver(BaseRetObserver);
    }
#endif

    /**
     * 发送校验(注册)码接口（校验码有效期3分钟）
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param codeType          【必填】生成的验证码类型，0注册,1修改密码,2登录并注册,3修改主体注册账号
     * @param accountType       【必填】1 - email（5到50个字节）,2 - phone
     * @param areaCode          【选填】手机渠道时为国际区号，邮箱渠道可直接填""
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void RequestVerifyCode(
        const String& channel,
        const String& account,
        int codeType,
        int accountType,
        const String& langType,
        const String& areaCode = "86",
        const String& extraJson = "");

    /**
     * 重置密码接口
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param verifyType        【必填】验证方式，1：使用验证码，2：使用旧密码
     * @param account           【必填】注册的帐号
     * @param password          【必填】登录密码
     * @param oldPassword       【当verify_type=2时必填】旧密码
     * @param accountType       【必填】1 - email（5到50个字节）,2 - phone
     * @param verifyCode        【选填】验证码
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机渠道时为国际区号，邮箱渠道可直接填""
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
	MSDK_EXPORT_UE static void ResetPassword(
        const String& channel,
        int verifyType,
        const String& account,
        const String& password,
        const String& oldPassword,
        int accountType,
        int verifyCode,
        const String& langType,
        const String& areaCode = "",
        const String& extraJson = "");

    /**
     * 修改账号信息接口（verifyCode校验码）
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param verifyType        【必填】验证方式，1：使用验证码，2：使用旧密码
     * @param account           【必填】当前存在的账号
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param verifyCode        【必填】验证码
     * @param verifyCodeModify  【必填】要修改的账号接收到的验证码
     * @param password          【当verify_type=2时必填】密码
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param accountModify     【必填】要修改的帐号
     * @param accountTypeModify 【必填】要修改的账号类型，1 - email, 2 - phone
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCodeModify    【选填】要修改的账号是手机时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
	MSDK_EXPORT_UE static void Modify(
        const String& channel,
        int verifyType,
        const String& account,
        int accountType,
        int verifyCode,
        int verifyCodeModify,
        const String& password,
        const String& accountModify,
        int accountTypeModify,
        const String& areaCodeModify,
        const String& langType,
        const String& areaCode = "",
        const String& extraJson = "");


    /**
     * 用户账号是否注册查询接口
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
	MSDK_EXPORT_UE static void GetRegisterStatus(
        const String& channel,
        const String& account,
        int accountType,
        const String& langType,
        const String& areaCode = "",
        const String& extraJson = "");


    /**
     * 验证码有效期查询接口
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param verifyCode        【必填】验证码
     * @param codeType          【必填】生成的验证码类型，0注册,1修改密码,2登录并注册,3修改主体注册账号
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
	MSDK_EXPORT_UE static void GetVerifyCodeStatus(
        const String& channel,
        const String& account,
        int accountType,
        int verifyCode,
        int codeType,
        const String& langType,
        const String& areaCode = "",
        const String& extraJson = "");

    /**
     * 查询是否已勾选接收邮件推送
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void GetReceiveEmail(
        const String& channel,
        const String& account,
        int accountType,
        const String& langType,
        const String& areaCode = "",
        const String& extraJson = "");

    /**
     * 校验密码
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param password          【必填】密码
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void VerifyPassword(
        const String& channel,
        const String& account,
        const String& password,
        int accountType,
        const String& langType,
        const String& areaCode = "",
        const String& extraJson = "");
};


NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

class MSDK_EXPORT MSDKAccountRet : public MSDKBaseRet
{
public:
    // 渠道ID
    int channelID;
    
    // 渠道名
    String channel;
    
    // 后台 seq 字段
    String seqID;
    
    String username;
    
    String uid;
    
    String token;
    
    String expiretime;
    
    int isRegister;
    
    int isSetPassword;
    
    int isReceiveEmail;
    
    int verifyCodeExpireTime;
    
    MSDKAccountRet(const MSDK::MSDKAccountRet &accountRet) : MSDKBaseRet(accountRet) {
        channelID = accountRet.channelID;
        channel = accountRet.channel;
        seqID = accountRet.seqID;
        username = accountRet.username;
        uid = accountRet.uid;
        token = accountRet.token;
        expiretime = accountRet.expiretime;
        isRegister = accountRet.isRegister;
        isSetPassword = accountRet.isSetPassword;
        isReceiveEmail = accountRet.isReceiveEmail;
        verifyCodeExpireTime = accountRet.verifyCodeExpireTime;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.account.MSDKAccountRet",
               A(thirdCode, "ret"), A(thirdMsg, "msg"), A(username, "user_name"), A(seqID, "seq"), A(expiretime, "expire"),
               O(retCode, retMsg, channelID, channel, methodNameID, token, uid), A(isRegister, "is_register"), A(isSetPassword, "isset_pwd"),
               A(isReceiveEmail, "is_receive_email"), A(verifyCodeExpireTime, "expire_time"), A(extraJson, "retExtraJson"));
    
};

class MSDK_EXPORT MSDKAccountObserver
{
public:
    virtual ~MSDKAccountObserver() {};
    
    virtual void OnAccountNotify(const MSDKAccountRet &accountRet) {};
};

class MSDKAccountObserverAdapter : public MSDK::MSDKAccountObserver
{
public:
    void OnAccountNotify(const MSDK::MSDKAccountRet &accountRet);
    
    MSDKSpace::NoSTL::MSDKAccountObserver *mObserver = NULL;
};

class MSDK_EXPORT MSDKAccount
{
public:
    friend class MSDKLogin;
private:
    static MSDKAccountObserverAdapter mAccountObserverAdapter;
    
public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    MSDK_EXPORT_UE static void SetAccountObserver(MSDKAccountObserver *observer);
#else
    static void SetAccountObserver(MSDKAccountObserver *observer)
    {
        mAccountObserverAdapter.mObserver = observer;
        MSDK::MSDKAccount::SetAccountObserver(&mAccountObserverAdapter);
    }
#endif
    
    /**
     * 发送校验(注册)码接口（校验码有效期3分钟）
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param codeType          【必填】生成的验证码类型，0注册,1修改密码,2登录并注册,3修改主体注册账号
     * @param accountType       【必填】1 - email（5到50个字节）,2 - phone
     * @param areaCode          【选填】手机渠道时为国际区号，邮箱渠道可直接填""
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void RequestVerifyCode(
                                                 const String& channel,
                                                 const String& account,
                                                 int codeType,
                                                 int accountType,
                                                 const String& langType,
                                                 const String& areaCode = "86",
                                                 const String& extraJson = "");
    
    /**
     * 重置密码接口
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param verifyType        【必填】验证方式，1：使用验证码，2：使用旧密码
     * @param account           【必填】注册的帐号
     * @param password          【必填】登录密码
     * @param oldPassword       【当verify_type=2时必填】旧密码
     * @param accountType       【必填】1 - email（5到50个字节）,2 - phone
     * @param verifyCode        【选填】验证码
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机渠道时为国际区号，邮箱渠道可直接填""
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void ResetPassword(
                                             const String& channel,
                                             int verifyType,
                                             const String& account,
                                             const String& password,
                                             const String& oldPassword,
                                             int accountType,
                                             int verifyCode,
                                             const String& langType,
                                             const String& areaCode = "",
                                             const String& extraJson = "");
    
    /**
     * 修改账号信息接口（verifyCode校验码）
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param verifyType        【必填】验证方式，1：使用验证码，2：使用旧密码
     * @param account           【必填】当前存在的账号
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param verifyCode        【必填】验证码
     * @param verifyCodeModify  【必填】要修改的账号接收到的验证码
     * @param password          【当verify_type=2时必填】密码
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param accountModify     【必填】要修改的帐号
     * @param accountTypeModify 【必填】要修改的账号类型，1 - email, 2 - phone
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCodeModify    【选填】要修改的账号是手机时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void Modify(
                                      const String& channel,
                                      int verifyType,
                                      const String& account,
                                      int accountType,
                                      int verifyCode,
                                      int verifyCodeModify,
                                      const String& password,
                                      const String& accountModify,
                                      int accountTypeModify,
                                      const String& areaCodeModify,
                                      const String& langType,
                                      const String& areaCode = "",
                                      const String& extraJson = "");
    
    
    /**
     * 用户账号是否注册查询接口
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void GetRegisterStatus(
                                                 const String& channel,
                                                 const String& account,
                                                 int accountType,
                                                 const String& langType,
                                                 const String& areaCode = "",
                                                 const String& extraJson = "");
    
    
    /**
     * 验证码有效期查询接口
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param verifyCode        【必填】验证码
     * @param codeType          【必填】生成的验证码类型，0注册,1修改密码,2登录并注册,3修改主体注册账号
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void GetVerifyCodeStatus(
                                                   const String& channel,
                                                   const String& account,
                                                   int accountType,
                                                   int verifyCode,
                                                   int codeType,
                                                   const String& langType,
                                                   const String& areaCode = "",
                                                   const String& extraJson = "");
    
    /**
     * 查询是否已勾选接收邮件推送
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void GetReceiveEmail(
                                               const String& channel,
                                               const String& account,
                                               int accountType,
                                               const String& langType,
                                               const String& areaCode = "",
                                               const String& extraJson = "");
    
    /**
     * 校验密码
     * @param channel           【必填】支持"Passport"-统一账号，"EGame"-企鹅电竞, "Self"-自建账号三个渠道
     * @param account           【必填】注册的帐号
     * @param password          【必填】密码
     * @param accountType       【必填】1- email（5到50个字节）,2 - phone
     * @param langType          【必填】指定发送给用户的验证码短信或邮件所有语言
     * @param areaCode          【选填】手机登录时为必填参数， 这里填写的是手机区号字段
     * @param extraJson         【选填】扩展字段，默认为空，会透传到后台
     */
    MSDK_EXPORT_UE static void VerifyPassword(
                                              const String& channel,
                                              const String& account,
                                              const String& password,
                                              int accountType,
                                              const String& langType,
                                              const String& areaCode = "",
                                              const String& extraJson = "");
    
    
};


NS_MSDK_SPACE_NO_STL_END

#endif /* MSDK_Account_H */
