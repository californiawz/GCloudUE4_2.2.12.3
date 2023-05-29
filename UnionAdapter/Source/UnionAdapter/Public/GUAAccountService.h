//
//  GUAAccountService.h
//  GUASample
//
//  Created by weiqiangluo on 2022/5/9.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

// auth result class
class GUA_EXTERN GUALoginResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    // the open id
	std::string openid;

    // token
	std::string token;

    // the token expire time
    int64_t token_expire_time;

    // whether first time login, -1:unknown, 0:false, 1:true
    int32_t first_login = false;

    // the first time register from the distribute channel
	std::string reg_channel_dis;

    // user name
	std::string user_name;

    // gender, 0:unknown, 1:man, 2:woman
    int32_t gender = 0;

    // birthday (1987-2-23 11:33:33)
	std::string birthday;

    // user portrait picture url
	std::string picture_url;

    // pf value
	std::string pf;

    // pf key
	std::string pf_key;

    // whether need real name auth
    bool real_name_auth = false;

    // channel id
    int32_t channelid;

    // channel name
	std::string channel;

    // third channel info
	std::string channel_info;

    // confirm code, user for LoginWithConfirmCode
	std::string confirm_code;

    // confirm code expire time
    int64_t confirm_code_expire_time;

    // bind info(json format with array)
	std::string bind_list;

    // legal document version
	std::string legal_doc;

    // transfer code, used to transfer account
    std::string transfer_code;

    // transfer code expire time
    int64_t transfer_code_expire_time = 0;

    // -1 : Account deletion status query failed or backend didn't return the status
    // 0: No delete account records or delete request has been withdrawn
    // 1: Account deletion requested
    // 2: Account deletion succeeded
    // 3: Deleting an account
    // 4: Failed to delete an account
    int32_t del_account_status = -1;

    // Account deletion status info
    std::string del_account_info;

    // email for login with comfire code
    std::string email;
    
    GUALoginResult(){};
};

class GUA_EXTERN GUAAccountResult : public GUABaseResult
{
	using GUABaseResult::GUABaseResult;
public:
	// channel id
	int32_t channelid = -1;

	// channel name
	std::string channel;

	// seq id
	std::string seq_id;

	// user name
	std::string user_name;

	// the account uid
	std::string uid;

	// the account token
	std::string token;

	// expire time
	int64_t expire_time;

	// whether has registerd
	int32_t is_register = 0;

	// whether set passoword
	int32_t is_set_password = 0;

	// whether user receive email
	int32_t is_receive_email = 0;

	// verify code expire time
	int64_t verify_code_expire_time = 0;

	//username available
	int32_t is_user_name_available = 0;

	// whether can bind to current account
	int32_t can_bind = 0;

    //check this account already login days
    int32_t login_days = 0;

	//For pp_version_ and tos_acceptance_version_, backend returns empty string when
	// a user has not yet accepted any TOS and/or PP. "-" is to tell whether if backend is returning anything.

	// Version of pp and the time that the user accepted.
	std::string pp_version = "-";
	int64_t pp_acceptance_time = -1;

	// Version of tos and the time that the user accepted.
	std::string tos_version = "-";
	int64_t tos_acceptance_time = -1;
};

class GUA_EXTERN GUAAccountProfile {
public:
	std::string user_name = "";
	std::string birthday = "1970-01-01";
    int32_t is_receive_email;
	std::string region = "000";
	std::string lang_type = "";
	std::string extra_json;

    GUAAccountProfile(){};
    ~GUAAccountProfile(){};
};

class GUA_EXTERN GUAIDTokenResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    std::string idtoken;
};

class GUAQrCodeResult : public GUABaseResult
{
public:
    // channel ID
    int channelid;
    
    // channel name
    std::string channel;
    
    // QR code url
    std::string qr_code_url;
    
    GUAQrCodeResult() : GUABaseResult()
    {
        channelid = 0;
    }
    
    GUAQrCodeResult(const GUAQrCodeResult &qrCodeRet) : GUABaseResult(qrCodeRet)
    {
        channelid = qrCodeRet.channelid;
        channel = qrCodeRet.channel;
        qr_code_url = qrCodeRet.qr_code_url;
    }
};

// Account observer class
class GUA_EXTERN GUAAccountObserver
{
public:
    virtual ~GUAAccountObserver() {};
    
    virtual void OnLoginResultNotify(const GUALoginResult &auth_result) {};

    virtual void OnBaseResultNotify(const GUABaseResult &base_result) {};

    virtual void OnAccountResultNotify(const GUAAccountResult &account_result) {};

    // [INTL Only] Observer for QueryIDTokenResponse
    virtual void OnIDTokenResultNotify(const GUAIDTokenResult &id_result) {};

#if GUA_OS_WINDOWS
    // [MSDK Only] PC login QR code observer
    virtual void OnQrCodeNotify(const GUAQrCodeResult &id_result) {};
#endif
    
};

// [MSDK Only] The Observer for associated channels
class GUA_EXTERN GUAConnectObserver
{
    
public:
    // Add a virtual destructor otherwise UE4 will report an error
    virtual ~GUAConnectObserver(){};
    
    // When the connect associated channel is called, 
	// the channel login authorization will be pulled up, and the associated results will be returned here
    virtual void OnConnectResultNotify(const GUALoginResult &login_result) {};
};

class GUA_EXTERN GUAAccountService
{
    //Common API Start
public:
	/**
	* @brief Set auth observer
	*
	* @param observer			[required]GUAAccountObserver
	*/
	static void SetAccountObserver(GUAAccountObserver *observer);
    
    /**
    * @brief Set auth observer
    *
    * @param observer			[required]GUAConnectObserver
    */
    static void SetConnectObserver(GUAConnectObserver *observer);
    
    /**
    * @brief Login with a specific channel
    *
    * @param channel			[required] channel name, "Facebook", "Twitter", etc.
    * @param permissions		[optional] it may request some permissions, use comma to concat permissions, such as user_info,inapp_friends
    * @param sub_channel		[optional] sub channel name
    * @param extra_json			[optional] extra params with json format
    */
    static void Login(
		const std::string &channel, 
		const std::string &permissions = GUA_DEFAULT_EMPTY_STRING,
		const std::string &sub_channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
    * @brief Logout with a specific channel
    *
    * @param channel			[required] channel name, "Facebook", "Twitter", etc.
    * @param sub_channel		[optional] sub channel name, "Facebook", "Twitter", etc. 
    * @param channel_only		[optional] only logout the specific channel
    */
    static void Logout(
		const std::string &channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &sub_channel = GUA_DEFAULT_EMPTY_STRING,
		bool channel_only = false);
    
    /**
    * @brief Bind with a specific channel
    *
    * @param channel			[required] channel name, "Facebook", "Twitter" etc
	* @param permissions		[optional] it may request some permissions, use comma to concat permissions, such as user_info, inapp_friends
    * @param sub_channel		[optional] sub channel name, "Facebook", "Twitter", etc. 
    * @param extra_json			[optional] extra params with json format
    */
    static void Bind(
		const std::string &channel, 
		const std::string &permissions = GUA_DEFAULT_EMPTY_STRING,
		const std::string &sub_channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

    /**
    * @brief Get login result, it is a synchronous interface
    *
    * @param login_result		[required] auth result
	*
    * @return op success, true for success, false for failed
    */
    static bool GetLoginResult(GUALoginResult& login_result);
    
    /**
    * @brief Auto login and refresh token
    */
    static void AutoLogin();
    
    /**
    * @brief In the case of account inconsistency, choose the launcher user or swith to   another user for login. This case happens in mobile platform.
    *
    * @param use_launch_user [required] true for the launcher user, false for another user
    * 
    * @return op success, if can not swith user, it will return false
    */
    static bool SwitchUser(bool use_launch_user);
    
    /**
    * @brief Query user info
    */
    static void QueryUserInfo();
    
    /**
    * @brief Login with a comfirm code after login or bind failed.
    *
    * @param action_type		[optional] action type : 0 normal login; 1 restore the guest account which binded to the channel, and login to the guest
    * @param confirm_code		[optional] the comfirm code given by the server, the default value is store in the SDK
    * @param extra_json			[optional] extra params with json format
    */
    static void LoginWithConfirmCode(
		int32_t action_type = 0, 
		const std::string &confirm_code = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
    * @brief Reset the guest account
    */
    static void ResetGuest();
    
    /**
    * @brief Launch website for Custom Account flows.
    *
    * @param type				[required] 1: auth, 2: user profile
    * @param extra_json			[optional] extra params with json format
    */
    static void LaunchAccountUI(
		int32_t type, 
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief Query the verify code status, it will return whether
     *
     * @param account			[required] the account, an email address or a phone number
     * @param verify_code		[required] the verify code get from RequestVerifyCode
     * @param code_type			[required] the type of the verify code, 0 register, 1: reset password, 2: register and login, 3: modify account
     * @param channel			[optional] channel name, support : "Passport", "EGame", "Self"
     * @param lang_type			[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
     * @param phone_area_code	[optional] when use phone number, the area code for this phone number, use empty string for email
     * @param extra_json		[optional] extra params with json format
     */
    static void QueryVerifyCodeStatus(
        const std::string &account,
        const std::string &verify_code,
        const int code_type,
        const std::string &channel = "Self",
        const std::string &lang_type = "en_US",
        const std::string &phone_area_code = "86",
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief Query the register status, whether has registered or not
     *
     * @param account			[required] the account, an email address or a phone number
     * @param channel			[optional] channel name, support : "Passport", "EGame", "Self"
     * @param lang_type			[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
     * @param phone_area_code	[optional] when use phone number, the area code for this phone number, use empty string for email
     * @param extra_json		[optional] extra params with json format
     */
    static void QueryRegisterStatus(
        const std::string &account,
        const std::string &channel = "Self",
        const std::string &lang_type = "en_US",
        const std::string &phone_area_code = "86",
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief Query whether user has selected to receive email from services
     *
     * @param account				[required] the account, an email address or a phone number
     * @param channel				[optional] channel name, support : "Passport", "EGame", "Self"
     * @param lang_type				[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
     * @param phone_area_code		[optional] when use phone number, the area code for this phone number, use empty string for email
     * @param extra_json			[optional] extra params with json format
     */
    static void QueryReceiveEmail(
        const std::string &account,
        const std::string &channel = "Self",
        const std::string &lang_type = "en_US",
        const std::string &phone_area_code = "86",
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief Modify the account
     *
     * @param old_account				[required] current account, an email address or a phone number
     * @param old_phone_area_code       [required] current account, when use phone number, the area code for this phone number, use empty string for email
     * @param password					[required when verify_type=2] current account password
     * @param new_account				[required] new account to modify, the new account
     * @param new_account_verify_code   [required] new account to modify, the verify code
     * @param new_phone_area_code       [required] new account to modify, when use phone number, the area code for this phone number, use empty string for email
     * @param channel					[optional] channel name, support : "Passport", "EGame", "Self"
     * @param lang_type					[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
     * @param extra_json				[optional] extra params with json format
     */
    static void ModifyAccountWithPassword(
        const std::string &old_account,
        const std::string &old_phone_area_code,
        const std::string &password,
        const std::string &new_account,
        const std::string &new_account_verify_code,
        const std::string &new_phone_area_code,
        const std::string &channel = "Self",
        const std::string &lang_type = "en_US",
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
   /**
    * @brief Modify the account
    *
    * @param old_account				[required] current account, an email address or a phone number
    * @param old_account_verify_code	[required] current account, the verify code
    * @param old_phone_area_code		[required] current account, when use phone number, the area code for this phone number, use empty string for email
    * @param new_account				[required] new account to modify, the new account
    * @param new_account_verify_code	[required] new account to modify, the verify code
    * @param new_phone_area_code		[required] new account to modify, when use phone number, the area code for this phone number, use empty string for email
    * @param channel					[optional] channel name, support : "Passport", "EGame", "Self"
    * @param lang_type					[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
    * @param extra_json					[optional] extra params with json format
    */
   static void ModifyAccountWithVerifyCode(
       const std::string &old_account,
       const std::string &old_account_verify_code,
       const std::string &old_phone_area_code,
       const std::string &new_account,
       const std::string &new_account_verify_code,
       const std::string &new_phone_area_code,
       const std::string &channel = "Self",
       const std::string &lang_type = "en_US",
       const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief Modify the account
     *
     * @param old_phone_area_code		[required] current account, when use phone number, the area code for this phone number, use empty string for email
     * @param new_account				[required] new account to modify, the new account
     * @param new_account_verify_code	[required] new account to modify, the verify code
     * @param new_phone_area_code		[required] new account to modify, when use phone number, the area code for this phone number, use empty string for email
     * @param extra_json				[optional] extra params with json format
     */
    static void ModifyAccountWithLoginState(
        const std::string &old_phone_area_code,
        const std::string &new_account,
        const std::string &new_account_verify_code,
        const std::string &new_phone_area_code,
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief Request the sever send a verify code to the user. this verify code will expire in 3 minutes
     *
     * @param account			[required] the account, an email address or a phone number
     * @param code_type			[required] the type of the verify code, 0 register, 1: reset password, 2: register and login, 3: modify account
     * @param phone_area_code	[required] when use phone number, the area code for this phone number, use empty string for email
     * @param channel			[optional] channel name, support : "Passport", "EGame", "Self"
     * @param lang_type			[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
     * @param extra_json		[optional] extra params with json format
     */
    static void RequestVerifyCode(
        const std::string &account,
        const int code_type,
        const std::string &phone_area_code,
        const std::string &channel = "Self",
        const std::string &lang_type = "en_US",
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief Reset password
     *
     * @param account			[required] the account, an email address or a phone number
     * @param old_password		[required] when verify_type=2] the old password
     * @param phone_area_code	[required] when use phone number, the area code for this phone number, use empty string for email
     * @param new_password		[required] the password, (0~9a-zA-z_![]-+())
     * @param channel			[optional] channel name, support : "Passport", "EGame", "Self"
     * @param lang_type			[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
     * @param extra_json		[optional] extra params with json format
     */
    static void ResetPasswordWithOldPassword(
        const std::string &account,
        const std::string &old_password,
        const std::string &phone_area_code,
        const std::string &new_password,
        const std::string &channel = "Self",
        const std::string &lang_type = "en_US",
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief Reset password
     *
     * @param account			[required] the account, an email address or a phone number
     * @param verify_code		[required] when verify_type=1] the verify code
     * @param phone_area_code	[required] when use phone number, the area code for this phone number, use empty string for email
     * @param new_password		[required] the password, (0~9a-zA-z_![]-+())
     * @param channel			[optional] channel name, support : "Passport", "EGame", "Self"
     * @param lang_type			[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
     * @param extra_json		[optional] extra params with json format
     */
    static void ResetPasswordWithVerifyCode(
        const std::string &account,
        const std::string &verify_code,
        const std::string &phone_area_code,
        const std::string &new_password,
        const std::string &channel = "Self",
        const std::string &lang_type = "en_US",
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

    //Common API End
    
//INTLSDK API Start
public:
    /**
    * @brief [INTLSDK Only] Query user channel bind info
    */
    static void QueryBindInfo();

	/**
	* @brief [INTLSDK Only] Query whether the account can be bound, only support the Self Account
	*
	* @param channelid			[required] channel id to be queried
	* @param account_plat_type	[required] account platform type
	* @param account			[required] email if account_type is 1, phone num if account_type is 2
	* @param phone_area_code	[required] if account is phone number, should specify area code too
	* @param extra_json			[optional] extra params with json format
	*/
	static void QueryCanBind(
		int32_t channelid,
		int32_t account_plat_type,
		const std::string &account,
		const std::string &phone_area_code,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
    * @brief [INTLSDK Only] Query account user profile
    */
    static void QueryAccountProfile();
    
    /**
    * @brief [INTLSDK Only] Set account basic info
    *
    * @param channel           [required] channel name of account, "Self" for custom account.
    * @param channelid         [required] channel id for the channel
    * @param lang_type         [required] the language type for sending email or message to the user
    * @param account_plat_type [required] the account platform type
    * @param extra_json        [optional] extra params with json format
    */
    static void SetAccountInfo(
		const std::string &channel, 
		int32_t channelid,
		const std::string &lang_type, 
		int32_t account_plat_type, 
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
    * @brief [INTLSDK Only] Register an account
    *
    * @param account           [required] the account, an email address or a phone number
    * @param password          [required] the password, (0~9a-zA-z_![]-+()), 8-20 characters
    * @param verify_code       [required] a verify code sent to the email or phone
    * @param phone_area_code   [required] when use phone number, the area code for this phone number, use empty string for email
    * @param user_profile      [required] user profile, including user name and so on
    * @param extra_json        [optional] extra params with json format
    */
    static void Register(
		const std::string &account, 
		const std::string &password, 
		const std::string &verify_code, 
		const std::string &phone_area_code, 
		const GUAAccountProfile &user_profile,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
    * @brief [INTLSDK Only] Modify the user profile
    *
    * @param user_profile		[required] including user name, birthday, region and so on
    */
    static void ModifyProfile(const GUAAccountProfile &profile);
    
    /**
    * @brief [INTLSDK Only] Checks if the current accepted TOS and/or PP version of a user is the latest
    */
    static void QueryDataProtectionAcceptance();
    
    /**
    * @brief [INTLSDK Only] Modifys the current accepted TOS and/or PP version of a user
	*
	* @param tos_version		[required] tos version
	* @param pp_version			[required] pp version
    */
    static void ModifyDataProtectionAcceptance(
		const std::string &tos_version, 
		const std::string &pp_version);
    
    /**
    * @brief [INTLSDK Only] Query current auth result and requests for an ID token.
    */
    static void QueryIDToken();
    
    /**
    * @brief [INTLSDK Only] Get ID token from QueryIDToken cache result.
	*
	* @param result				[required] ID Token result struct
	* @return If get result success, return true
    */
    static bool GetIDTokenResult(GUAIDTokenResult &result);
    
    /**
    * @brief [INTLSDK Only] Query whether the username can be used for account
    *
    * @param user_name         [required] username to check for validity
    */
    static void QueryUserNameStatus(const std::string &user_name);
    
    /**
    * @brief [INTLSDK Only] Login with a mapped channel.
    *
    * @param channel			[required] The specified channel to log in.
    * @param permission			[required] The authorized permissions list during login. Separate the permissions by commas
	* @param extra_json			[optional] extra params with json format
    */
    static void LoginWithMappedChannel(
		const std::string &channel, 
		const std::string &permission, 
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
    * @brief [INTLSDK Only] Build a map with the logged-in channel.
    */
    static void BuildMapWithLoggedinChannel();
    
    /**
    * @brief [INTLSDK Only] Query the current user's legal document acceptance version.
    */
    static void QueryLegalDocumentsAcceptedVersion();
    
    /**
    * @brief [INTLSDK Only] Modify the current user's legal document acceptance version.
	* 
	* @param version			[required] target version
    */
    static void ModifyLegalDocumentsAcceptedVersion(const std::string &version);
    
    /**
     * @brief [INTLSDK Only] Unbind a specific channel
     *
     * @param channelid			[required] channel id of the channel to unbind
     * @param uid				[optional] user identifier of the channel to unbind
     * @param extra_json		[optional] extra params with json format
     */
    static void Unbind(
        const int channelid,
        const std::string &uid = GUA_DEFAULT_EMPTY_STRING,
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

#if GUA_OS_XBOXONE
    /**
     * @brief [INTLSDK Only] Query the active users
	 * 
	 * @param extra_json		[optional] extra params with json format
     */
    static void QueryActiveUser(const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

    /**
     * @brief [INTLSDK Only] Show the account list to pick an account
	 *
	 * @param extra_json		[optional] extra params with json format
     */
    static void ShowAccountPicker(const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

    /**
     * @brief [INTLSDK Only] Check whether current user is active or not
	 *
	 * @param extra_json		[optional] extra params with json format
     */
    static void CheckActiveUser(const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
#endif

    /**
     * @brief [INTLSDK Only] Login custom-account with password
     * @brief Get result from asynchronous event: GUAAccountObserver::OnLoginResultNotify
     *
     * @param channel			[required] channel name, such as "Facebook", "Twitter" etc.
     * @param account			[required] custom-account such as an email address.
     * @param passWord			[required] custom-account password to login.
     * @param phone_area_code	[required] region code, set to "" if not concerned.
     * @param permission_list	[optional] account authorization list, set to "" if not concerned.     *
     */
    static void LoginWithPassword(
        const std::string &channel,
        const std::string &account,
        const std::string &password,
        const std::string &phone_area_code,
        const std::string &permission_list = GUA_DEFAULT_EMPTY_STRING);

    /**
     * @brief [INTLSDK Only] Login custom-account with verify code
     * @brief Get result from asynchronous event: GUAAccountObserver::OnLoginResultNotify
     *
     * @param channel			[required] channel name, such as "Facebook", "Twitter" etc.
     * @param account			[required] custom-account such as an email address.
     * @param password			[required] custom-account password for registration, set to "" if not concerned.
     * @param verify_code		[required] verify code from email or cellphone.
     * @param phone_area_code	[required] region code, set to "" if not concerned.
     * @param permission_list	[optional] account authorization list, set to "" if not concerned.
     */
    static void LoginWithVerifyCode(
        const std::string &channel,
        const std::string &account,
        const std::string &password,
        const std::string &verify_code,
        const std::string &phone_area_code,
        const std::string &permission_list = GUA_DEFAULT_EMPTY_STRING);

    /**
	 * @brief [INTLSDK Only] Generate a transfer code for the logged-in account
	 * @param password [required] password to use when transfer account
	 */
	static void GenerateTransferCode(const std::string &password);

    /**
	 * @brief [INTLSDK Only] Query the transfer code generated for the logged-in account
	 * 
	 */
	static void QueryTransferCode();

    /**
	 * @brief [INTLSDK Only] Transfer an account from another device to the current guest account
	 * 
	 * @param transfer_code [required] transfer code that specifies the account to be transferred
	 * @param password      [required] password that was set when generating the transfer code
	 */
	static void TransferAccount(const std::string &transfer_code, const std::string &password);

    /**
	 * @brief [INTLSDK Only] Revoke Apple channel token
	 * 
	 */
	static void RevokeChannelToken();

    /**
	 * @brief [INTLSDK Only] Query Login Records
	 */
    static void QueryLoginRecord();

	/**
     * @brief [INTLSDK Only] logining 3rd find this account had email address register in selfAccount,
     *
     * @param channel_id         [required] channel id for the channel
     * @param confirm_code       [required] gei last protocol got confirm code
     * @param extra_json         [optional] extra params in a json format
     */
    static void LoginWithConfirmCodeForMail(
		const std::string &channel_id,
		const std::string &confirm_code = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief [INTLSDK Only] RequestAccountInfo for get token,uid
     *
     * @param extra_json         [optional] extra params in a json format
     */
    static void RequestAccountInfo(const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
      
    /**
     * @brief [INTLSDK Only]  RequestAccountInfo for get token,uid
     *
     * @param uid                account info uid
     * @param token              account info token
     * @param extra_json         [optional] extra params in a json format
     */
    static void RequestBindDataForAccount(
        const std::string &uid, 
        const std::string &token, 
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
      
    /**
     * @brief [INTLSDK Only]  get recent login days
     *
     * @param recent_day        last days
     * @param extra_json    json string
     */
    static void RequestGetRecentLoginDays(
        const std::string &recent_day, 
        const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
//INTLSDK API End

// MSDK API Start
public:
    /**
     * @brief [MSDK Only] Detect the capability of UniversalLink
	 *
     * @param channel		    [optional] channel name, only for Facebook channel
     * @param subChannel		[optional] sub channel
     * @param extra		        [optional] extra params with json format
     */
    static void CheckUniversalLink(
		const std::string &channel, 
		const std::string &subChannel = GUA_DEFAULT_EMPTY_STRING, 
		const std::string &extra = GUA_DEFAULT_JSON_STRING);

    /**
     * @brief [MSDK Only] Bind UI
	 *
     * @param extra_json		[optional] reserved fields
     */
    static void BindUI(const std::string &extra_json = GUA_DEFAULT_JSON_STRING);

	/**
	 * @brief [MSDK Only] Query whether the account can be bound, only support the Self Account
	 *
	 * @param channel			[requred] channel name to be queried
	 * @param channel_indo		[requred] channel info
	 * @param extra_json		[optional] extra params with json format
	 */
	static void CanBind(
		const std::string &channel,
		const std::string &channel_info,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief [MSDK Only] Connect channel
	 *
     * @param channel			[required] channelInfo, only for Kwai channel
     * @param permissions		[optional] List of login authorization permissions, multiple permissions are separated by commas, for example "user_info, inapp_friends".
     * @param sub_channel		[optional] subChannel.
     * @param extra_json		[optional] extra params with json format.
     */
    static void Connect(
		const std::string &channel,
		const std::string &permissions = GUA_DEFAULT_EMPTY_STRING,
		const std::string &sub_channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief [MSDK Only] Disconnect channel
     * 
	 * @param channel			[required] channelInfo, only for Kwai channel
     */
    static void UnConnect(const std::string &channel);
    
    /**
	 * @brief [MSDK Only] Get local login status
	 * @param connectRet		[required] login result struct
	 * 
	 * @return Get local connect status, synchronous call
	 */
    static bool GetConnectResult(GUALoginResult &login_result);
    

    /**
     * @biref [MSDK Only] Set install channel
	 *
	 * @param channel			[required] the channel，such as "Facebook"
     */
    static void SetInstallChannel(const std::string &channel);

    /**
     * @biref [MSDK Only] Uninstall MSDK DLL
     */
    static void UnInstall();
    
    /**
     * @brief [MSDK Only] Check if the channel has generated an MSDK account, if yes, return the login result, otherwise return directly
	 *
	 * @param channel			[required] channel name, "Facebook", "Twitter", etc.
	 * @param permissions		[optional] it may request some permissions, use comma to concat permissions, for example "user_info, inapp_friends"
	 * @param sub_channel		[optional] sub channel
	 * @param extra_json		[optional] extra params with json format
     */
    static void CheckLogin(
		const std::string &channel, 
		const std::string &permissions = GUA_DEFAULT_EMPTY_STRING,
		const std::string &sub_channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
     * @brief [MSDK Only] Check whether the account can be bound, and return ConfirmCode if it can be bound
	 *
	 * @param channel			[required] channel name, "Facebook", "Twitter", etc.
	 * @param permissions		[optional] it may request some permissions, use comma to concat permissions, for example "user_info, inapp_friends"
     * @param sub_channel		[optional] sub channel
	 * @param extra_json		[optional] extra params with json format
     */
    static void Check(
		const std::string &channel, 
		const std::string &permissions = GUA_DEFAULT_EMPTY_STRING,
		const std::string &sub_channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
	 * @brief [MSDK Only] Bind MSDK channel with confirmCode
     * 
	 * @param confirmCode		[required] the unique confirm code
	 * @param channelid			[required] target channel id
	 * @param extra_json		[optional] extra params with json format
     */
    static void BindWithConfirmCode(
		const std::string &confirmCode, 
		int channelid, 
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
      * @brief [MSDK Only] Facebook secondary authorization
	  *
      * @param channel			[required] the channel，such as "Facebook"
      * @param permissions		[optional] permission list, separate permission lists with commas，video Number authorization needs to pass in "snsapi_channels_livestream"
      * @param sub_channel		[optional] sub channel
	  * @param extra_json		[optional] extra params with json format
      */
    static void ChannelPermissionAuth(
		const std::string &channel, 
		const std::string &permissions = GUA_DEFAULT_EMPTY_STRING,
		const std::string &sub_channel = GUA_DEFAULT_EMPTY_STRING,
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
    
    /**
    * @brief [MSDK Only] Verify password
    *
    * @param account			[required] the account, an email address or a phone number
    * @param password			[required] the password, (0~9a-zA-z_![]-+())
    * @param phone_area_code	[optional] when use phone number, the area code for this phone number, use empty string for email
    * @param channel			[optional] channel name, support : "Passport", "EGame", "Self"
    * @param lang_type			[optional] SDK language, the language type adopts RFC 4646 standard, such as: en, please refer to the language type definition for details
    * @param extra_json         [optional] extra params with json format
    */
    static void VerifyPassword(
        const std::string &account,
        const std::string &password,
        const std::string &phone_area_code = "86",
        const std::string &channel = "Self",
        const std::string &langType = "en_US",
        const std::string &extraJson = GUA_DEFAULT_JSON_STRING);
    
    // MSDK API End

};

GUA_NAMESPACE_END
