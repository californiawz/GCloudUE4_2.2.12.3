//
//  MSDKStructUtility.h
//  MSDKSample
//
//  Created by tafflin on 2022/6/20.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"
#include "GUAAccountService.h"
#include "GUACrashService.h"
#include "GUAToolsService.h"
#include "GUAFriendService.h"
#include "GUANoticeService.h"
#include "GUAPushService.h"
#include "GUAReportService.h"
#include "GUAWebViewService.h"
#include "GUAExtendService.h"
#include "MSDKDefine.h"
#include "MSDKLogin.h"
#include "MSDKAccount.h"
#include "MSDKExtend.h"
#include "MSDKFriend.h"
#include "MSDKNotice.h"
#include "MSDKCrash.h"
#include "MSDKPush.h"
#include "MSDKWebView.h"
#include "MSDKTools.h"
#include "MSDKExtend.h"

using namespace GCloud::MSDKSpace::NoSTL;

GUA_NAMESPACE_BEGIN

class MSDKStructUtility{
public:
	//common
    static void ConvertBaseRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKBaseRet &ret, GUABaseResult &gua_base_ret);
    
	//Login
	static void ConvertLoginRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKLoginRet &ret, GUALoginResult &gua_login_ret);
	static void ConvertAccountRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKAccountRet &ret, GUAAccountResult &gua_account_ret);
#if MSDK_PLATFORM_WINDOWS
	static void ConvertQrCodeToGUA(const GCloud::MSDKSpace::NoSTL::MSDKQrCodeRet &ret, GUAQrCodeResult &gua_qrcode_ret);
#endif

	//friend
	static void ConvertFriendRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKFriendRet &ret, GUAFriendResult &gua_fri_ret);
	static int ConvertGUAFriReqTypeToMSDK(int gua_req_type);
	static void ConvertFriendReqToMSDK(const GUAFriendReqInfo &gua_req_info, GCloud::MSDKSpace::NoSTL::MSDKFriendReqInfo &msdk_req_info);

	//notice
	static void ConvertNoticeRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKNoticeRet &ret,GUANoticeResult &gua_notice_ret);
	static void ConvertNoticeInfoToGUA(const GCloud::MSDKSpace::NoSTL::MSDKNoticeInfo *info, GUANoticeInfo &gua_info);
	static void ConvertNoticeTextInfoToGUA(const GCloud::MSDKSpace::NoSTL::MSDKNoticeTextInfo *msdk_notice_text_info, GUANoticeTextInfo &gua_notice_text_info);
	static void ConvertNoticePicToGUA(const GCloud::MSDKSpace::NoSTL::MSDKNoticePictureInfo *pic, GUANoticePictureInfo &gua_pic);

	//crash
	static void ConvertCrashRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKCrashRet &ret, GUACrashRet &gua_crash_ret);

	//push
	static void ConvertPushRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKPushRet &push_ret, GUAPushResult &gua_push_ret);
	static void ConvertLocalNotificationToMSDK(const GUALocalNotification &gua_local_notification, GCloud::MSDKSpace::NoSTL::MSDKLocalNotification &msdk_local_notification);

	//webview
	static void ConvertWebViewRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKWebViewRet &webview_ret, GUAWebViewRet &gua_webview_ret);

	//tools
	static void ConvertToolsRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKToolsRet &ret, GUAToolsResult &gua_ret);
	static void ConvertToolsFreeFlowRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKToolsFreeFlowRet &ret, GUAToolsFreeFlowRet &gua_ret);
	static void ConvertToolsFreeFlowInfoToGUA(const GCloud::MSDKSpace::NoSTL::MSDKToolsFreeFlowInfo &info, GUAToolsFreeFlowInfo &gua_info);

	//extend
	static void ConvertExtendRetToGUA(const GCloud::MSDKSpace::NoSTL::MSDKExtendRet &ret, GUAExtendResult &gua_ret);

	//methodId
	static GUAMethodID ConvertMethodIdToGUA(const GCloud::MSDKSpace::NoSTL::MethodName msdk_method_id);
};
GUA_NAMESPACE_END
