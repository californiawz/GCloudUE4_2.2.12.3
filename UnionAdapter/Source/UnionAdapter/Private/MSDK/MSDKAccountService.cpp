//
//  MSDKAccountService.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/6/20.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//
#include "GUAAccountService.h"
#include "MSDKLogin.h"
#include "MSDKAccount.h"
#include "MSDKLog.h"
#include "MSDKStructUtility.h"
#include "MSDKCompatLayer.h"
#include "GUAErrorCode.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

#define ACCOUNT_TYPE_NONE   0
#define ACCOUNT_TYPE_EMAIL  1
#define ACCOUNT_TYPE_PHONE  2

int GetAccountType(const std::string &account)
{
    int account_type = ACCOUNT_TYPE_PHONE;
    if (account.find('@') != std::string::npos) {
        account_type = ACCOUNT_TYPE_EMAIL;
    }
    return account_type;
}

class MSDKAccountObserver : public GCloud::MSDKSpace::NoSTL::MSDKLoginObserver, public GCloud::MSDKSpace::NoSTL::MSDKAccountObserver
{
public:
    static MSDKAccountObserver Instance;
    GUAAccountObserver* account_observer_;
public:
    MSDKAccountObserver():account_observer_(nullptr){

    }

    void OnLoginRetNotify(const GCloud::MSDKSpace::NoSTL::MSDKLoginRet &msdk_login_ret)
    {
        GUALoginResult gua_login_ret;
        MSDKStructUtility::ConvertLoginRetToGUA(msdk_login_ret, gua_login_ret);

        if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
            MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
        }
        else
        {
            LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
        }

    }

    void OnBaseRetNotify(const GCloud::MSDKSpace::NoSTL::MSDKBaseRet &msdk_base_ret)
    {
        GUABaseResult gua_base_ret;
        MSDKStructUtility::ConvertBaseRetToGUA(msdk_base_ret, gua_base_ret);

        if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
            MSDKAccountObserver::Instance.account_observer_->OnBaseResultNotify(gua_base_ret);
        }
        else
        {
            LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
        }

    }

    void OnAccountNotify(const GCloud::MSDKSpace::NoSTL::MSDKAccountRet &msdk_account_ret)
    {
        GUAAccountResult gua_account_ret;
        MSDKStructUtility::ConvertAccountRetToGUA(msdk_account_ret, gua_account_ret);

        if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
            MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_ret);
        }
        else
        {
            LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
        }

    }

#if MSDK_PLATFORM_WINDOWS
    void OnQrCodeNotify(const GCloud::MSDKSpace::NoSTL::MSDKQrCodeRet &msdk_qrcode_ret)
    {
        GUAQrCodeResult gua_qrcode_ret;
        MSDKStructUtility::ConvertQrCodeToGUA(msdk_qrcode_ret, gua_qrcode_ret);

        if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
            MSDKAccountObserver::Instance.account_observer_->OnQrCodeNotify(gua_qrcode_ret);
        }
        else
        {
            LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
        }       

    }
#endif
};

class MSDKConnectObserver : public GCloud::MSDKSpace::NoSTL::MSDKConnectObserver
{
public:
    static MSDKConnectObserver Instance;
    GUAConnectObserver* connect_observer_;
public:
    MSDKConnectObserver():connect_observer_(nullptr){

    }

    void OnConnectRetNotify(const GCloud::MSDKSpace::NoSTL::MSDKLoginRet &msdk_login_ret)
    {
        GUALoginResult gua_login_ret;
        MSDKStructUtility::ConvertLoginRetToGUA(msdk_login_ret, gua_login_ret);

        if (MSDKConnectObserver::Instance.connect_observer_ != nullptr) {
            MSDKConnectObserver::Instance.connect_observer_->OnConnectResultNotify(gua_login_ret);
        }
        else
        {
            LOG_DEBUG("MSDKConnectObserver::Instance.connect_observer_ is nullptr");
        }

    }
};

MSDKAccountObserver MSDKAccountObserver::Instance;
void GUAAccountService::SetAccountObserver(GUAAccountObserver *observer)
{
	MSDKAccountObserver::Instance.account_observer_ = observer;
    GCloud::MSDKSpace::NoSTL::MSDKLogin::SetLoginObserver(&MSDKAccountObserver::Instance);
    GCloud::MSDKSpace::NoSTL::MSDKAccount::SetAccountObserver(&MSDKAccountObserver::Instance);
}

MSDKConnectObserver MSDKConnectObserver::Instance;
void GUAAccountService::SetConnectObserver(GUAConnectObserver *observer)
{
    MSDKConnectObserver::Instance.connect_observer_ = observer;
    GCloud::MSDKSpace::NoSTL::MSDKLogin::SetConnectObserver(&MSDKConnectObserver::Instance);
}

void GUAAccountService::Login(const std::string &channel, const std::string &permissions, const std::string &sub_channel, const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::Login(channel, permissions, sub_channel, extra_json);
}

void GUAAccountService::Logout(const std::string &channel, const std::string &sub_channel, bool channel_only)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::Logout(channel, sub_channel, channel_only);
}

void GUAAccountService::Bind(const std::string &channel, const std::string &permissions, const std::string &sub_channel, const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::Bind(channel, permissions, sub_channel, extra_json);
}

void GUAAccountService::CanBind(const std::string &channel, const std::string &channel_info, const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::CanBind(channel, channel_info, extra_json);
}

bool GUAAccountService::GetLoginResult(GUALoginResult& login_result)
{
    GCloud::MSDKSpace::NoSTL::MSDKLoginRet msdk_login_ret;
    bool status = GCloud::MSDKSpace::NoSTL::MSDKLogin::GetLoginRet(msdk_login_ret);
    MSDKStructUtility::ConvertLoginRetToGUA(msdk_login_ret, login_result);
    return status;
}
void GUAAccountService::AutoLogin()
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::AutoLogin();
}
bool GUAAccountService::SwitchUser(bool use_launch_user)
{
    return GCloud::MSDKSpace::NoSTL::MSDKLogin::SwitchUser(use_launch_user);
}
void GUAAccountService::QueryUserInfo()
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::QueryUserInfo();
}
void GUAAccountService::LoginWithConfirmCode(int32_t action_type, const std::string &confirm_code, const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::LoginWithConfirmCode(action_type, confirm_code, extra_json);
}
void GUAAccountService::ResetGuest()
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::ResetGuest();
}

void GUAAccountService::LaunchAccountUI(int32_t type, const std::string &extra_json)
{
    LOG_ERROR("LoginUI, function not support");
}

void GUAAccountService::QueryVerifyCodeStatus(
    const std::string &account,
    const std::string &verify_code,
    const int code_type,
    const std::string &channel,
    const std::string &lang_type,
    const std::string &phone_area_code,
    const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKAccount::GetVerifyCodeStatus(channel, account, GetAccountType(account), atoi(verify_code.c_str()), code_type, lang_type, phone_area_code, extra_json);
}

void GUAAccountService::QueryRegisterStatus(
    const std::string &account,
    const std::string &channel,
    const std::string &lang_type,
    const std::string &phone_area_code,
    const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKAccount::GetRegisterStatus(channel, account, GetAccountType(account), lang_type, phone_area_code, extra_json);
}

void GUAAccountService::QueryReceiveEmail(
    const std::string &account,
    const std::string &channel,
    const std::string &lang_type,
    const std::string &phone_area_code,
    const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKAccount::GetReceiveEmail(channel, account, GetAccountType(account), lang_type, phone_area_code, extra_json);
}

void GUAAccountService::ModifyAccountWithPassword(
    const std::string &old_account,
    const std::string &old_phone_area_code,
    const std::string &password,
    const std::string &new_account,
    const std::string &new_account_verify_code,
    const std::string &new_phone_area_code,
    const std::string &channel,
    const std::string &lang_type,
    const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKAccount::Modify(channel, 2, old_account, GetAccountType(old_account), -1, atoi(new_account_verify_code.c_str()), password, new_account, GetAccountType(new_account), new_phone_area_code, lang_type, old_phone_area_code, extra_json);
}

void GUAAccountService::ModifyAccountWithVerifyCode(
    const std::string &old_account,
    const std::string &old_account_verify_code,
    const std::string &old_phone_area_code,
    const std::string &new_account,
    const std::string &new_account_verify_code,
    const std::string &new_phone_area_code,
    const std::string &channel,
    const std::string &lang_type,
    const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKAccount::Modify(channel, 1, old_account, GetAccountType(old_account), atoi(old_account_verify_code.c_str()), atoi(new_account_verify_code.c_str()), "", new_account, GetAccountType(new_account), new_phone_area_code, lang_type, old_phone_area_code, extra_json);
}

void GUAAccountService::RequestVerifyCode(
    const std::string &account,
    const int code_type,
    const std::string &phone_area_code,
    const std::string &channel,
    const std::string &lang_type,
    const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKAccount::RequestVerifyCode(channel, account, code_type, GetAccountType(account), lang_type, phone_area_code, extra_json);
}

void GUAAccountService::ResetPasswordWithOldPassword(
    const std::string &account,
    const std::string &old_password,
    const std::string &phone_area_code,
    const std::string &new_password,
    const std::string &channel,
    const std::string &lang_type,
    const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKAccount::ResetPassword(channel, 2, account, new_password, old_password, GetAccountType(account), -1, lang_type, phone_area_code, extra_json);
}

void GUAAccountService::ResetPasswordWithVerifyCode(
    const std::string &account,
    const std::string &verify_code,
    const std::string &phone_area_code,
    const std::string &new_password,
    const std::string &channel,
    const std::string &lang_type,
    const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKAccount::ResetPassword(channel, 1, account, new_password, "", GetAccountType(account), atoi(verify_code.c_str()), lang_type, phone_area_code, extra_json);
}

// MSDK API Start
void GUAAccountService::CheckUniversalLink(
	const std::string &channel, 
	const std::string &subChannel, 
	const std::string &extra)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::CheckUniversalLink(channel, subChannel, extra);
}

void GUAAccountService::BindUI(const std::string &extra_json)
{
    LOG_ERROR("BindUI, function not support");
}

void GUAAccountService::Connect(const std::string &channel,
        const std::string &permissions,
        const std::string &sub_channel,
        const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::Connect(channel, permissions, sub_channel, extra_json);
}

void GUAAccountService::UnConnect(const std::string &channel)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::UnConnect(channel);
}

bool GUAAccountService::GetConnectResult(GUALoginResult &login_result)
{
    GCloud::MSDKSpace::NoSTL::MSDKLoginRet msdk_login_ret;
    bool status = GCloud::MSDKSpace::NoSTL::MSDKLogin::GetConnectRet(msdk_login_ret);
    MSDKStructUtility::ConvertLoginRetToGUA(msdk_login_ret, login_result);
    return status;
}

#if MSDK_PLATFORM_WINDOWS

void GUAAccountService::SetInstallChannel(const std::string &channel)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::SetInstallChannel(channel);
}

void GUAAccountService::UnInstall()
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::UnInstall();
}

#endif

void GUAAccountService::CheckLogin(
		const std::string &channel, 
		const std::string &permissions, 
		const std::string &sub_channel,
		const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::CheckLogin(channel, permissions, sub_channel, extra_json);
}

void GUAAccountService::Check(
		const std::string &channel, 
		const std::string &permissions, 
		const std::string &sub_channel, 
		const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::Check(channel, permissions, sub_channel, extra_json);
}

void GUAAccountService::BindWithConfirmCode(
		const std::string &confirmCode, 
		int channelid, 
		const std::string &extra_json)
{
    GCloud::MSDKSpace::NoSTL::MSDKLogin::BindWithConfirmCode(confirmCode, channelid, extra_json);
}

void GUAAccountService::ChannelPermissionAuth(
		const std::string &channel, 
		const std::string &permissions,
		const std::string &sub_channel, 
		const std::string &extra_json)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    GCloud::MSDKSpace::NoSTL::MSDKLogin::ChannelPermissionAuth(channel, permissions, sub_channel, extra_json);
#endif
}
// MSDK API End

//INTL API Start
void GUAAccountService::QueryCanBind(int32_t channelid, int32_t account_plat_type, const std::string &account,
        const std::string &phone_area_code, const std::string &extra_json)
{
    LOG_ERROR("QueryBind, function not support");
    GUAAccountResult gua_account_result;
    gua_account_result.method_id = GUAMethodID::kMethodIDAccountQueryCanBind;
    gua_account_result.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_account_result.ret_msg = "GUAAccountService::QueryCanBind is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_result);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}
void GUAAccountService::QueryBindInfo(){
    LOG_ERROR("QueryBindInfo, function not support");
    GUAAccountResult gua_account_result;
    gua_account_result.method_id = GUAMethodID::kMethodIDAccountQueryBindInfo;
    gua_account_result.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_account_result.ret_msg = "GUAAccountService::QueryBindInfo is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_result);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}
void GUAAccountService::QueryAccountProfile(){
    LOG_ERROR("QueryAccountProfile, function not support");
    GUAAccountResult gua_account_result;
    gua_account_result.method_id = GUAMethodID::kMethodIDAccountQueryAccountProfile;
    gua_account_result.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_account_result.ret_msg = "GUAAccountService::QueryAccountProfile is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_result);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }  
}

void GUAAccountService::SetAccountInfo(const std::string &channel, int32_t channelid, const std::string &lang_type
        , int32_t account_plat_type, const std::string &extra_json)
{
    LOG_ERROR("SetAccountInfo, function not support");
}

void GUAAccountService::Register(const std::string &account, const std::string &password, const std::string &verify_code
, const std::string &phone_area_code, const GUAAccountProfile& user_profile, const std::string &extra_json)
{
    LOG_ERROR("Register, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountRegister;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::Register is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::ModifyProfile(const GUAAccountProfile& profile)
{
    LOG_ERROR("ModifyProfile, function not support");
    GUAAccountResult gua_account_result;
    gua_account_result.method_id = GUAMethodID::kMethodIDAccountModifyProfile;
    gua_account_result.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_account_result.ret_msg = "GUAAccountService::ModifyProfile is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_result);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }    
}

void GUAAccountService::QueryDataProtectionAcceptance()
{
    LOG_ERROR("QueryDataProtectionAcceptance, function not support");
    GUAAccountResult gua_account_result;
    gua_account_result.method_id = GUAMethodID::kMethodIDAccountQueryDataProtectionAcceptance;
    gua_account_result.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_account_result.ret_msg = "GUAAccountService::QueryDataProtectionAcceptance is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_result);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }   
}

void GUAAccountService::ModifyDataProtectionAcceptance(const std::string &tos_version, const std::string &pp_version)
{
    LOG_ERROR("ModifyDataProtectionAcceptance, function not support");
    GUAAccountResult gua_account_result;
    gua_account_result.method_id = GUAMethodID::kMethodIDAccountModifyDataProtectionAcceptance;
    gua_account_result.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_account_result.ret_msg = "GUAAccountService::ModifyDataProtectionAcceptance is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_result);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }   
}

void GUAAccountService::QueryIDToken()
{
    LOG_ERROR("QueryIDToken, function not support");
}

bool GUAAccountService::GetIDTokenResult(GUAIDTokenResult& result)
{
    LOG_ERROR("GetIDTokenResult, function not support");
    return false;
}

void GUAAccountService::QueryUserNameStatus(const std::string &user_name)
{
    LOG_ERROR("QueryUserNameStatus, function not support");
    GUAAccountResult gua_account_result;
    gua_account_result.method_id = GUAMethodID::kMethodIDAccountQueryUserNameStatus;
    gua_account_result.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_account_result.ret_msg = "GUAAccountService::QueryUserNameStatus is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_result);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }   
}

void GUAAccountService::LoginWithMappedChannel(const std::string &channel, const std::string &permission, const std::string &extra_json)
{
    LOG_ERROR("LoginWithMappedChannel, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountLoginWithMappedChannel;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::LoginWithMappedChannel is not support";
    
    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::BuildMapWithLoggedinChannel()
{
    LOG_ERROR("BuildMapWithLoggedinChannel, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountBuildMapWithLoginChannel;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::BuildMapWithLoggedinChannel is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::QueryLegalDocumentsAcceptedVersion()
{
    LOG_ERROR("QueryLegalDocumentsAcceptedVersion, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountQueryLegalDocuments;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::QueryLegalDocumentsAcceptedVersion is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::ModifyLegalDocumentsAcceptedVersion(const std::string &version)
{
    LOG_ERROR("ModifyLegalDocumentsAcceptedVersion, function not support");
    GUABaseResult gua_base_ret;
    gua_base_ret.method_id = GUAMethodID::kMethodIDAccountModifyLegalDocuments;
    gua_base_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_base_ret.ret_msg = "GUAAccountService::ModifyLegalDocumentsAcceptedVersion is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnBaseResultNotify(gua_base_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::Unbind(
    const int channelid,
    const std::string &uid,
    const std::string &extra_json)
{
    LOG_ERROR("Unbind, function not support");
    GUABaseResult gua_base_ret;
    gua_base_ret.method_id = GUAMethodID::kMethodIDAccountQueryUserNameStatus;
    gua_base_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_base_ret.ret_msg = "GUAAccountService::Unbind is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnBaseResultNotify(gua_base_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

#if GUA_OS_XBOXONE
void GUAAccountService::QueryActiveUser(const std::string &extra_json)
{
    LOG_ERROR("QueryActiveUser, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountQueryActiveUser;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::QueryActiveUser is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::ShowAccountPicker(const std::string &extra_json)
{
    LOG_ERROR("ShowAccountPicker, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountShowAccountPicker;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::ShowAccountPicker is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::CheckActiveUser(const std::string &extra_json)
{
    LOG_ERROR("CheckActiveUser, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountNeedRefreshUser;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::CheckActiveUser is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}
#endif

void GUAAccountService::LoginWithPassword(
    const std::string &channel,
    const std::string &account,
    const std::string &password,
    const std::string &phone_area_code,
    const std::string &permission_list)
{
    LOG_ERROR("LoginWithPassword, function not support");
}

void GUAAccountService::LoginWithVerifyCode(
    const std::string &channel,
    const std::string &account,
    const std::string &password,
    const std::string &verify_code,
    const std::string &phone_area_code,
    const std::string &permission_list)
{
    LOG_ERROR("LoginWithVerifyCode, function not support");
}

void GUAAccountService::GenerateTransferCode(const std::string &password)
{
    LOG_ERROR("GenerateTransferCode, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountGenerateTransferCode;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::GenerateTransferCode is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::QueryTransferCode()
{
    LOG_ERROR("QueryTransferCode, function not support");
    GUALoginResult gua_login_ret;
    gua_login_ret.method_id = GUAMethodID::kMethodIDAccountQueryTransferCode;
    gua_login_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_login_ret.ret_msg = "GUAAccountService::QueryTransferCode is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnLoginResultNotify(gua_login_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::TransferAccount(const std::string &transfer_code, const std::string &password)
{
    LOG_ERROR("TransferAccount, function not support");
    GUABaseResult gua_base_ret;
    gua_base_ret.method_id = GUAMethodID::kMethodIDAccountTransferAccount;
    gua_base_ret.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_base_ret.ret_msg = "GUAAccountService::TransferAccount is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnBaseResultNotify(gua_base_ret);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }
}

void GUAAccountService::RevokeChannelToken()
{
    LOG_ERROR("RevokeChannelToken, function not support");
}

void GUAAccountService::ModifyAccountWithLoginState(
    const std::string &old_phone_area_code,
    const std::string &new_account,
    const std::string &new_account_verify_code,
    const std::string &new_phone_area_code,
    const std::string &extra_json)
{
    LOG_ERROR("ModifyAccountWithLoginState, function not support");
    GUAAccountResult gua_account_result;
    gua_account_result.method_id = GUAMethodID::kMethodIDAccountModifyAccount;
    gua_account_result.ret_code = GUAErrorCode::NOT_SUPPORT;
    gua_account_result.ret_msg = "GUAAccountService::ModifyAccountWithLoginState is not support";

    if (MSDKAccountObserver::Instance.account_observer_ != nullptr) {
        MSDKAccountObserver::Instance.account_observer_->OnAccountResultNotify(gua_account_result);
    }
    else
    {
        LOG_DEBUG("MSDKAccountObserver::Instance.account_observer_ is nullptr");
    }   
}

void GUAAccountService::QueryLoginRecord()
{
    LOG_ERROR("QueryLoginRecord, function not support");
}

void GUAAccountService::LoginWithConfirmCodeForMail(
    const std::string &channel_id,
    const std::string &confirm_code,
    const std::string &extra_json)
{
    LOG_ERROR("LoginWithConfirmCodeForMail, function not support");
}

void GUAAccountService::RequestAccountInfo(const std::string &extra_json)
{
    LOG_ERROR("RequestAccountInfo, function not support");
}

void GUAAccountService::RequestBindDataForAccount(
    const std::string &uid, 
    const std::string &token, 
    const std::string &extra_json)
{
    LOG_ERROR("RequestBindDataForAccount, function not support");
}

void GUAAccountService::RequestGetRecentLoginDays(       
    const std::string &recent_day, 
    const std::string &extra_json)
{
    LOG_ERROR("RequestGetRecentLoginDays, function not support");
}


//INTL API End

GUA_NAMESPACE_END
