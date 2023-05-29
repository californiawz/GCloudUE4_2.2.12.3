//
//  MSDKStructUtility.cpp
//  MSDKSample_Index
//
//  Created by tafflin on 2022/6/22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//


#include "MSDKStructUtility.h"
#include "UnionAdapterDefine.h"
#include "GUAAccountService.h"
#include <stdlib.h>
#include "MSDKFriend.h"
#include "MSDKLog.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

// region Common
void MSDKStructUtility::ConvertBaseRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKBaseRet &ret, GUABaseResult &gua_base_result)
{
	gua_base_result.method_id = MSDKStructUtility::ConvertMethodIdToGUA(GCloud::MSDKSpace::NoSTL::MethodName(ret.methodNameID));
	gua_base_result.ret_code = ret.retCode;
	gua_base_result.ret_msg = ret.retMsg.c_str();
	gua_base_result.third_code = ret.thirdCode;
	gua_base_result.third_msg = ret.thirdMsg.c_str();
	gua_base_result.extra_json = ret.extraJson.c_str();
}
// Common endregion

// region Login

void MSDKStructUtility::ConvertLoginRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKLoginRet &ret, GUALoginResult &gua_Login_ret)
{
    LOG_DEBUG("");
    MSDKStructUtility::ConvertBaseRetToGUA(ret, gua_Login_ret);

    gua_Login_ret.openid = ret.openID.c_str();
    gua_Login_ret.token = ret.token.c_str();
    gua_Login_ret.token_expire_time = ret.tokenExpire;
    gua_Login_ret.first_login = ret.firstLogin;
    gua_Login_ret.reg_channel_dis = ret.regChannelDis.c_str();
    gua_Login_ret.user_name = ret.userName.c_str();
    gua_Login_ret.gender = ret.gender;
    gua_Login_ret.birthday = ret.birthdate.c_str();
    gua_Login_ret.picture_url = ret.pictureUrl.c_str();
    gua_Login_ret.pf = ret.pf.c_str();
    gua_Login_ret.pf_key = ret.pfKey.c_str();
    gua_Login_ret.real_name_auth = ret.realNameAuth;
    gua_Login_ret.channelid = ret.channelID;
    gua_Login_ret.channel = ret.channel.c_str();
    gua_Login_ret.channel_info = ret.channelInfo.c_str();
    gua_Login_ret.confirm_code = ret.confirmCode.c_str();
    gua_Login_ret.confirm_code_expire_time = ret.confirmCodeExpireTime;
    gua_Login_ret.bind_list = ret.bindList.c_str();
    gua_Login_ret.legal_doc = "";
    gua_Login_ret.del_account_status = -1;
    gua_Login_ret.transfer_code = "";
    gua_Login_ret.transfer_code_expire_time = 0;
    gua_Login_ret.del_account_info = "";
    gua_Login_ret.email = "";
}

void MSDKStructUtility::ConvertAccountRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKAccountRet &ret, GUAAccountResult &gua_account_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(ret, gua_account_ret);

    gua_account_ret.channelid = ret.channelID;
    gua_account_ret.channel = ret.channel.c_str();
    gua_account_ret.seq_id = ret.seqID.c_str();
    gua_account_ret.user_name = ret.username.c_str();
    gua_account_ret.uid = ret.uid.c_str();
    gua_account_ret.token = ret.token.c_str();
    gua_account_ret.expire_time = atoll(ret.expiretime.c_str());
    gua_account_ret.is_register = ret.isRegister;
    gua_account_ret.is_set_password = ret.isSetPassword;
    gua_account_ret.is_receive_email = ret.isReceiveEmail;
    gua_account_ret.verify_code_expire_time = ret.verifyCodeExpireTime;
    gua_account_ret.can_bind = 0;
    gua_account_ret.is_user_name_available = 0;
    gua_account_ret.login_days = 0;
    gua_account_ret.pp_version = "";
    gua_account_ret.pp_acceptance_time = 0;
    gua_account_ret.tos_version = "";
    gua_account_ret.tos_acceptance_time = 0;

}

#if MSDK_PLATFORM_WINDOWS
void MSDKStructUtility::ConvertQrCodeToGUA(const GCloud::MSDKSpace::NoSTL::MSDKQrCodeRet &msdk_qrcode_ret, GUAQrCodeResult &gua_qrcode_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(msdk_qrcode_ret, gua_qrcode_ret);

    gua_qrcode_ret.channelid = msdk_qrcode_ret.channelID;
    gua_qrcode_ret.channel = msdk_qrcode_ret.channel;
    gua_qrcode_ret.qr_code_url = msdk_qrcode_ret.qrCodeUrl;
}
#endif

// Login endregion

// region Friend
void MSDKStructUtility::ConvertFriendRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKFriendRet &ret, GUAFriendResult &gua_fri_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(ret, gua_fri_ret);

    gua_fri_ret.friend_info_list.reserve(ret.friendInfoList.size());

	for (auto friendRetIter = ret.friendInfoList.begin(); friendRetIter != ret.friendInfoList.end(); friendRetIter ++) {
		GUAPersonInfo personInfo;
		personInfo.openid = friendRetIter -> openid.c_str();
		personInfo.user_name = friendRetIter -> userName.c_str();
		personInfo.gender = friendRetIter -> gender;
		personInfo.picture_url = friendRetIter -> pictureUrl.c_str();
		personInfo.country = friendRetIter -> country.c_str();
		personInfo.province = friendRetIter -> province.c_str();
		personInfo.city = friendRetIter -> city.c_str();
		personInfo.language = friendRetIter -> language.c_str();
		personInfo.extra_json = "";

		gua_fri_ret.friend_info_list.push_back(personInfo);
	}
}

int MSDKStructUtility::ConvertGUAFriReqTypeToMSDK(int gua_req_type)
{
	GUAFriendReqType gua_type = (GUAFriendReqType)gua_req_type;
	switch (gua_type)
	{
	case GUA::kGUAFriendReqTypeText:
		return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeText;
	case GUA::kGUAFriendReqTypeLink:
		return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeLink;
	case GUA::kGUAFriendReqTypeIMG:
		return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeIMG;
	case GUA::kGUAFriendReqTypeInvite:
		return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeInvite;
	case GUA::kGUAFriendReqTypeVideo:
		return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeVideo;
    case GUA::kGUAFriendReqTypeMusic:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeMusic;
    case GUA::kGUAFriendReqTypeMiniApp:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeMiniApp;
    case GUA::kGUAFriendReqTypePullUpMiniApp:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypePullUpMiniApp;
    case GUA::kGUAFriendReqTypeArk:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeArk;
    case GUA::kGUAFriendReqTypeOpenBusinessView:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeOpenBusinessView;
    case GUA::kGUAFriendReqTypeWXGameLine:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeWXGameLine;
    case GUA::kGUAFriendReqTypeWXChannelShareVideo:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeWXChannelShareVideo;
    case GUA::kGUAFriendReqTypeWXStateText:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeWXStateText;
    case GUA::kGUAFriendReqTypeWXStatePhoto:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeWXStatePhoto;
    case GUA::kGUAFriendReqTypeWXStateMusicVideo:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeWXStateMusicVideo;
    case GUA::kGUAFriendReqTypeWXChannelStartLive:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeWXChannelStartLive;
    case GUA::kGUAFriendReqTypeWithCommonShare:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeWithCommonShare;
    case (int)GUA::kGUAFriendReqTypeWXNativeGamePage:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeWXNativeGamePage;
    case GUA::kGUAFriendReqTypeTextSilent:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeTextSilent;
    case GUA::kGUAFriendReqTypeLinkSilent:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeLinkSilent;
    case GUA::kGUAFriendReqTypeIMGSilent:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeIMGSilent;
    case GUA::kGUAFriendReqTypeInviteSilent:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeInviteSilent;
    case GUA::kGUAFriendReqTypeMusicSilent:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeMusicSilent;
    case GUA::kGUAFriendReqTypeVideoSilent:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeVideoSilent;
    case GUA::kGUAFriendReqTypeMiniAppSilent:
        return (int)GCloud::MSDKSpace::NoSTL::kMSDKFriendReqTypeMiniAppSilent;
	default:
		return gua_req_type;
	}
}

void MSDKStructUtility::ConvertFriendReqToMSDK(const GUAFriendReqInfo &gua_req_info, GCloud::MSDKSpace::NoSTL::MSDKFriendReqInfo &msdk_req_info)
{
	msdk_req_info.type = ConvertGUAFriReqTypeToMSDK(gua_req_info.type);
	msdk_req_info.user = gua_req_info.user.c_str();
	msdk_req_info.title = gua_req_info.title.c_str();
	msdk_req_info.desc = gua_req_info.description.c_str();
	msdk_req_info.imagePath = gua_req_info.image_path.c_str();
	msdk_req_info.thumbPath = gua_req_info.thumb_path.c_str();
	msdk_req_info.mediaPath = gua_req_info.media_path.c_str();
	msdk_req_info.link = gua_req_info.link.c_str();
	msdk_req_info.extraJson = gua_req_info.extra_json.c_str();
}

// Friend endregion

// region Crash

void MSDKStructUtility::ConvertCrashRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKCrashRet &ret, GUACrashRet &gua_crash_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(ret, gua_crash_ret);

    gua_crash_ret.max_data_len = ret.maxDataLen;
    gua_crash_ret.data = ret.data;
}

// Crash endregion

// region WebView

void MSDKStructUtility::ConvertWebViewRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKWebViewRet &msdk_webview_ret, GUAWebViewRet &gua_webview_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(msdk_webview_ret, gua_webview_ret);

    gua_webview_ret.msg_type = msdk_webview_ret.msgType;
    gua_webview_ret.msg_json_data = msdk_webview_ret.msgJsonData;
    gua_webview_ret.embed_progress = msdk_webview_ret.embedProgress;
    gua_webview_ret.embed_url = msdk_webview_ret.embedUrl;
}

// WebView endregion

// region Extend

void MSDKStructUtility::ConvertExtendRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKExtendRet &msdk_extend_ret, GUAExtendResult &gua_extend_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(msdk_extend_ret, gua_extend_ret);

    gua_extend_ret.channel = msdk_extend_ret.channel;
    gua_extend_ret.extend_method_name = msdk_extend_ret.extendMethodName;
}

// Extend endregion

// region Push

void MSDKStructUtility::ConvertPushRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKPushRet &msdk_push_ret, GUAPushResult &gua_push_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(msdk_push_ret, gua_push_ret);

    gua_push_ret.type = msdk_push_ret.type;
    gua_push_ret.notification = msdk_push_ret.notification;
}

void MSDKStructUtility::ConvertLocalNotificationToMSDK(const GUALocalNotification &gua_local_notification, GCloud::MSDKSpace::NoSTL::MSDKLocalNotification &msdk_local_notification)
{
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    msdk_local_notification.type = gua_local_notification.type;
    msdk_local_notification.actionType = gua_local_notification.action_type;
    msdk_local_notification.iconType = gua_local_notification.icon_type;
    msdk_local_notification.lights = gua_local_notification.lights;
    msdk_local_notification.ring = gua_local_notification.ring;
    msdk_local_notification.vibrate = gua_local_notification.vibrate;
    msdk_local_notification.styleID = gua_local_notification.styleID;
    msdk_local_notification.builderID = gua_local_notification.builderID;
    msdk_local_notification.content = gua_local_notification.content;
    msdk_local_notification.customContent = gua_local_notification.custom_content;

    msdk_local_notification.activity = "";
    msdk_local_notification.packageName = "";
    msdk_local_notification.intent = "";
    msdk_local_notification.url = "";

    switch (gua_local_notification.action_type)
    {
    case 1:
        msdk_local_notification.activity = gua_local_notification.action_parameter;
        break;
    case 2:
        msdk_local_notification.packageName = gua_local_notification.action_parameter;
        break;
    case 3:
        msdk_local_notification.intent = gua_local_notification.action_parameter;
        break;
    case 4:
        msdk_local_notification.url = gua_local_notification.action_parameter;
        break;
    default:
        break;
    }

    msdk_local_notification.packageDownloadUrl = gua_local_notification.package_download_url;
    msdk_local_notification.iconRes = gua_local_notification.icon_res;
    msdk_local_notification.date = gua_local_notification.date;
    msdk_local_notification.hour = gua_local_notification.hour;
    msdk_local_notification.min = gua_local_notification.min;
    msdk_local_notification.title = gua_local_notification.title;
    msdk_local_notification.ringRaw = gua_local_notification.ring_raw;
    msdk_local_notification.smallIcon = gua_local_notification.small_icon;

#else
#ifdef __APPLE__
    msdk_local_notification.repeatType = gua_local_notification.repeat_type;
    msdk_local_notification.fireTime = gua_local_notification.fire_time;
    msdk_local_notification.badge = gua_local_notification.badge;
    msdk_local_notification.alertBody = gua_local_notification.alert_body;
    msdk_local_notification.alertAction = gua_local_notification.alert_action;
    msdk_local_notification.userInfo = gua_local_notification.user_info;

#endif

#ifdef ANDROID

    msdk_local_notification.type = gua_local_notification.type;
    msdk_local_notification.actionType = gua_local_notification.action_type;
    msdk_local_notification.iconType = gua_local_notification.icon_type;
    msdk_local_notification.lights = gua_local_notification.lights;
    msdk_local_notification.ring = gua_local_notification.ring;
    msdk_local_notification.vibrate = gua_local_notification.vibrate;
    msdk_local_notification.styleID = gua_local_notification.styleID;
    msdk_local_notification.builderID = gua_local_notification.builderID;
    msdk_local_notification.content = gua_local_notification.content;
    msdk_local_notification.customContent = gua_local_notification.custom_content;

    msdk_local_notification.activity = "";
    msdk_local_notification.packageName = "";
    msdk_local_notification.intent = "";
    msdk_local_notification.url = "";

    switch (gua_local_notification.action_type)
    {
    case 1:
        msdk_local_notification.activity = gua_local_notification.action_parameter;
        break;
    case 2:
        msdk_local_notification.packageName = gua_local_notification.action_parameter;
        break;
    case 3:
        msdk_local_notification.intent = gua_local_notification.action_parameter;
        break;
    case 4:
        msdk_local_notification.url = gua_local_notification.action_parameter;
        break;
    default:
        break;
    }
    msdk_local_notification.packageDownloadUrl = gua_local_notification.package_download_url;
    msdk_local_notification.iconRes = gua_local_notification.icon_res;
    msdk_local_notification.date = gua_local_notification.date;
    msdk_local_notification.hour = gua_local_notification.hour;
    msdk_local_notification.min = gua_local_notification.min;
    msdk_local_notification.title = gua_local_notification.title;
    msdk_local_notification.ringRaw = gua_local_notification.ring_raw;
    msdk_local_notification.smallIcon = gua_local_notification.small_icon;

#endif
#endif
}

// Push endregion

// region Tool

void MSDKStructUtility::ConvertToolsRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKToolsRet &msdk_tools_ret, GUAToolsResult &gua_tools_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(msdk_tools_ret, gua_tools_ret);
    gua_tools_ret.deep_link_url = msdk_tools_ret.link;
    gua_tools_ret.short_link_url = "";
}

void MSDKStructUtility::ConvertToolsFreeFlowRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKToolsFreeFlowRet &msdk_tools_free_flow_ret, GUAToolsFreeFlowRet &gua_tools_free_flow_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(msdk_tools_free_flow_ret, gua_tools_free_flow_ret);

    MSDKStructUtility::ConvertToolsFreeFlowInfoToGUA(msdk_tools_free_flow_ret.freeFlowInfo, gua_tools_free_flow_ret.free_flow_info);

}

void MSDKStructUtility::ConvertToolsFreeFlowInfoToGUA(const GCloud::MSDKSpace::NoSTL::MSDKToolsFreeFlowInfo &msdk_tools_free_flow_ret, GUAToolsFreeFlowInfo &gua_tools_free_flow_info)
{
    gua_tools_free_flow_info.ip_all = msdk_tools_free_flow_ret.ipAll;
    gua_tools_free_flow_info.ip_connect = msdk_tools_free_flow_ret.ipConnect;
    gua_tools_free_flow_info.is_free = msdk_tools_free_flow_ret.isFree;
    gua_tools_free_flow_info.cc_type = msdk_tools_free_flow_ret.ccType;
}

// Tool endregion

// region Notice

void MSDKStructUtility::ConvertNoticeRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKNoticeRet &msdk_notice_ret, GUANoticeResult &gua_notice_ret)
{
    MSDKStructUtility::ConvertBaseRetToGUA(msdk_notice_ret, gua_notice_ret);

    gua_notice_ret.req_id = msdk_notice_ret.reqID;
    gua_notice_ret.notice_info_list.reserve(msdk_notice_ret.noticeInfoList.size());
    for(auto iter = msdk_notice_ret.noticeInfoList.begin(); iter != msdk_notice_ret.noticeInfoList.end(); iter ++)
    {
        GUANoticeInfo info;
        MSDKStructUtility::ConvertNoticeInfoToGUA(&*iter, info);
        gua_notice_ret.notice_info_list.push_back(info);
    }
}

void MSDKStructUtility::ConvertNoticeInfoToGUA(const GCloud::MSDKSpace::NoSTL::MSDKNoticeInfo *msdk_notice_info, GUANoticeInfo &gua_notice_info)
{
    gua_notice_info.notice_id = msdk_notice_info -> noticeID;
    gua_notice_info.notice_type = msdk_notice_info -> noticeType;
    gua_notice_info.notice_group = msdk_notice_info -> noticeGroup;
    gua_notice_info.app_id = "";
    gua_notice_info.app_notice_id = "";
    gua_notice_info.status = 0;
    gua_notice_info.begin_time = msdk_notice_info -> beginTime;
    gua_notice_info.end_time = msdk_notice_info -> endTime;
    gua_notice_info.update_time = msdk_notice_info->updateTime;
    gua_notice_info.area_list = "";
    gua_notice_info.order = msdk_notice_info -> order;
    gua_notice_info.content_type = msdk_notice_info -> contentType;
    gua_notice_info.language = msdk_notice_info -> language;
    MSDKStructUtility::ConvertNoticeTextInfoToGUA(&msdk_notice_info->textInfo, gua_notice_info.text_info);

    gua_notice_info.pic_url_list.reserve(msdk_notice_info->picUrlList.size());
    for(auto iter = msdk_notice_info->picUrlList.begin(); iter != msdk_notice_info->picUrlList.end(); iter ++)
    {
        GUANoticePictureInfo pic;
        MSDKStructUtility::ConvertNoticePicToGUA(&*iter, pic);
        gua_notice_info.pic_url_list.push_back(pic);
    }

    std::vector<GUANoticeTextInfo> defaultContent;
    gua_notice_info.content_list = defaultContent;
    gua_notice_info.web_url = msdk_notice_info->webUrl;
    gua_notice_info.extra_json = msdk_notice_info->extraJson;
}

void MSDKStructUtility::ConvertNoticeTextInfoToGUA(const GCloud::MSDKSpace::NoSTL::MSDKNoticeTextInfo *msdk_notice_text_info, GUANoticeTextInfo &gua_notice_text_info)
{
    gua_notice_text_info.title = msdk_notice_text_info -> noticeTitle;
    gua_notice_text_info.content = msdk_notice_text_info -> noticeContent;
    gua_notice_text_info.redirect_url = msdk_notice_text_info -> noticeRedirectUrl;
    gua_notice_text_info.content_id = 0;
    gua_notice_text_info.app_content_id = "";
    gua_notice_text_info.lang_type = "";
    gua_notice_text_info.update_time = 0;
    gua_notice_text_info.extra_data = "";

    std::vector<GUANoticePictureInfo> defaultInfo;
    gua_notice_text_info.picture_list = defaultInfo;
}

void MSDKStructUtility::ConvertNoticePicToGUA(const GCloud::MSDKSpace::NoSTL::MSDKNoticePictureInfo *msdk_pic, GUANoticePictureInfo &gua_pic)
{
    gua_pic.pic_url = msdk_pic->noticePicUrl;
    gua_pic.pic_hash = msdk_pic->noticePicHashcode;
    gua_pic.pic_title = msdk_pic->noticePicTitle;
    gua_pic.pic_size = msdk_pic->noticePicSize;
    gua_pic.screen_dir = msdk_pic->screenDir;
    gua_pic.pic_redirect_url = "";
    gua_pic.extra_data = "";
}

// Notice endregion

// region MethodId

GUAMethodID MSDKStructUtility::ConvertMethodIdToGUA(const GCloud::MSDKSpace::NoSTL::MethodName msdk_method_id)
{
    switch(msdk_method_id)
    {
        case GCloud::MSDKSpace::NoSTL::kMethodNameUndefine:
            return GUA::kMethodIDUndefine;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAutoLogin:
            return GUA::kMethodIDAccountAutoLogin;
        case GCloud::MSDKSpace::NoSTL::kMethodNameLogin:
            return GUA::kMethodIDAccountLogin;
        case GCloud::MSDKSpace::NoSTL::kMethodNameBind:
            return GUA::kMethodIDAccountBind;
        case GCloud::MSDKSpace::NoSTL::kMethodNameGetLoginRet:
            return GUA::kMethodIDAccountGetLoginRet;
        case GCloud::MSDKSpace::NoSTL::kMethodNameSwitchUser:
            return GUA::kMethodIDAccountSwitchUser;
        case GCloud::MSDKSpace::NoSTL::kMethodNameQueryUserInfo:
            return GUA::kMethodIDAccountQueryUserInfo;
        case GCloud::MSDKSpace::NoSTL::kMethodNameLogout:
            return GUA::kMethodIDAccountLogout;
        case GCloud::MSDKSpace::NoSTL::kMethodNameLoginWithConfirmCode:
            return GUA::kMethodIDAccountLoginWithConfirmCode;
        case GCloud::MSDKSpace::NoSTL::kMethodNameWakeUp:
            return GUA::kMethodIDAccountWakeUp;
        case GCloud::MSDKSpace::NoSTL::KMethodNameScheme:
            return GUA::KMethodIDAccountScheme;

        case GCloud::MSDKSpace::NoSTL::kMethodNameResetGuest:
            return GUA::kMethodIDAccountResetGuest;

        case GCloud::MSDKSpace::NoSTL::kMethodNameLoginUI:
            return GUA::kMethodIDAccountLaunchAccountUI;
        case GCloud::MSDKSpace::NoSTL::kMethodNameConnect:
            return GUA::kMethodIDAccountConnect;
        case GCloud::MSDKSpace::NoSTL::kMethodNameUnConnect:
            return GUA::kMethodIDAccountUnconnect;
        case GCloud::MSDKSpace::NoSTL::kMethodNameGetConnectRet:
            return GUA::kMethodIDAccountGetConnectResult;
        case GCloud::MSDKSpace::NoSTL::kMethodNameBindUI:
            return GUA::kMethodIDAccountBindUI;
        case GCloud::MSDKSpace::NoSTL::kMethodNameCanBind:
		    return GUA::kMethodIDAccountQueryCanBind;
#if MSDK_PLATFORM_WINDOWS
        case GCloud::MSDKSpace::NoSTL::kMethodNameQrCode:
            return GUA::kMethodIDAccountQRCode;
        case GCloud::MSDKSpace::NoSTL::kMethodNameRefreshToken:
            return GUA::KMethodIDAccountRefreshToken;
#endif
        case GCloud::MSDKSpace::NoSTL::kMethodNameCheckUniversalLink:
            return GUA::kMethodIDAccountCheckUL;
        case GCloud::MSDKSpace::NoSTL::kMethodNameCheckAndLogin:
            return GUA::kMethodIDAccountCheckAndLogin;
        case GCloud::MSDKSpace::NoSTL::kMethodNameCheck:
            return kMethodIDAccountCheck;
        case GCloud::MSDKSpace::NoSTL::kMethodNameBindWithConfirmCode:
            return kMethodIDAccountBindWithConfirmCode;
        case GCloud::MSDKSpace::NoSTL::kMethodNamePermissionAuth:
            return GUA::kMethodIDAccountPermissionAuth;
        case GCloud::MSDKSpace::NoSTL::kMethodNameChannelPermissionAuth:
            return GUA::kMethodIDAccountChannelPermissionAuth;

        case GCloud::MSDKSpace::NoSTL::kMethodNameShareToWall:
            return GUA::kMethodIDFriendShare;
        case GCloud::MSDKSpace::NoSTL::kMethodNameSendMessageToFriend:
            return GUA::kMethodIDFriendSendMessage;
        case GCloud::MSDKSpace::NoSTL::kMethodNameQueryFriend:
            return GUA::kMethodIDFriendQueryFriends;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAddFriend:
            return GUA::kMethodIDFriendAddFriend;

        case GCloud::MSDKSpace::NoSTL::kMethodNameCloseWebViewURL:
            return GUA::kMethodIDWebviewCloseURL;
        case GCloud::MSDKSpace::NoSTL::kMethodNameGetEncodeURL:
            return GUA::kMethodIDWebviewGetEncryptUR;
        case GCloud::MSDKSpace::NoSTL::kMethodNameWebViewJsCall:
            return GUA::kMethodIDWebviewJSCall;
        case GCloud::MSDKSpace::NoSTL::kMethodNameWebViewJsShare:
            return GUA::kMethodIDWebviewJSShare;
        case GCloud::MSDKSpace::NoSTL::kMethodNameWebViewJsSendMessage:
            return GUA::kMethodIDWebviewJSSendMessage;
        case GCloud::MSDKSpace::NoSTL::kMethodNameWebViewEmbedProgress:
            return GUA::KMethodIDWebviewEmbeddedProgress;
        
        case GCloud::MSDKSpace::NoSTL::kMethodNameRegisterPush:
            return GUA::kMethodIDPushRegister;
        case GCloud::MSDKSpace::NoSTL::kMethodNameUnregisterPush:
            return GUA::kMethodIDPushUnregister;
        case GCloud::MSDKSpace::NoSTL::kMethodNameSetTagForPush:
            return GUA::kMethodIDPushSetTag;
        case GCloud::MSDKSpace::NoSTL::kMethodNameDeleteTagForPush:
            return GUA::kMethodIDPushDeleteTag;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAddLocalNotify:
            return GUA::kMethodIDPushAddLocalNotification;
        case GCloud::MSDKSpace::NoSTL::kMethodNameClearLocalNotify:
            return GUA::kMethodIDPushClearLocalNotification;
        case GCloud::MSDKSpace::NoSTL::kMethodNameNotifyCallback:
            return GUA::kMethodIDPushNotificationCallback;
        case GCloud::MSDKSpace::NoSTL::kMethodNameNotifyShow:
            return GUA::kMethodIDPushNotificationShow;
        case GCloud::MSDKSpace::NoSTL::kMethodNameNotifyClick:
            return GUA::kMethodIDPushNotificationClick;
        case GCloud::MSDKSpace::NoSTL::kMethodNameSetAccountPush:
            return GUA::kMethodIDPushSetAccount;
        case GCloud::MSDKSpace::NoSTL::kMethodNameDeleteAccountPush:
            return GUA::kMethodIDPushDeleteAccount;
        
        case GCloud::MSDKSpace::NoSTL::kMethodNameLoadNoticeData:
            return GUA::kMethodIDNoticeRequestData;

        
        case GCloud::MSDKSpace::NoSTL::KMethodNameToolsOpenDeepLink:
            return GUA::kMethodIDToolsOpenDeepLink;
        case GCloud::MSDKSpace::NoSTL::KMethodNameToolsConvertShortUrl:
            return GUA::kMethodIDToolsConvertShortURL;
        case GCloud::MSDKSpace::NoSTL::KMethodNameToolsGetFreeFlowInfo:
            return GUA::kMethodIDToolsFreeFlow;
        
        case GCloud::MSDKSpace::NoSTL::kMethodNameCrashExtraData:
            return GUA::kMethodIDAnalyticsCrashExtraData;
        case GCloud::MSDKSpace::NoSTL::kMethodNameCrashExtraMessage:
            return GUA::kMethodIDAnalyticsCrashExtraMessage;

        case GCloud::MSDKSpace::NoSTL::kMethodNameExtend:
            return GUA::kMethodIDExtendInvoke;
        
        case GCloud::MSDKSpace::NoSTL::kMethodNameAccountVerifyCode:
            return GUA::kMethodIDAccountRequestVerifyCode;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAccountResetPassword:
            return GUA::kMethodIDAccountResetPassword;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAccountModify:
            return GUA::kMethodIDAccountModifyAccount;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAccountLoginWithCode:
            return GUA::kMethodIDAccountLoginWithCode;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAccountGetRegisterStatus:
            return GUA::kMethodIDAccountQueryRegisterStatus;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAccountGetVerifyCodeStatus:
            return GUA::kMethodIDAccountQueryVerifyCodeStatus;
        case GCloud::MSDKSpace::NoSTL::kMethodNameAccountGetReceiveEmail:
            return GUA::kMethodIDAccountQueryIsReceiveEmail;

        default:
            return kMethodIDUndefine;
    }
}
// MethodId endregion

GUA_NAMESPACE_END