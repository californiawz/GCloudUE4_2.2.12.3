//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKAccount.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

void MSDKAccount::SetAccountObserver(MSDKAccountObserver *observer) {}

void MSDKAccount::RequestVerifyCode(
        const String& channel,
        const String& account,
        int codeType,
        int accountType,
        const String& langType,
        const String& areaCode,
        const String& extraJson) {}
		
void MSDKAccount::ResetPassword(
        const String& channel,
        int verifyType,
        const String& account,
        const String& password,
        const String& oldPassword,
        int accountType,
        int verifyCode,
        const String& langType,
        const String& areaCode,
        const String& extraJson) {}
		
void MSDKAccount::Modify(
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
        const String& areaCode,
        const String& extraJson) {}
		
void MSDKAccount::GetRegisterStatus(
        const String& channel,
        const String& account,
        int accountType,
        const String& langType,
        const String& areaCode,
        const String& extraJson) {}
		
void MSDKAccount::GetVerifyCodeStatus(
        const String& channel,
        const String& account,
        int accountType,
        int verifyCode,
        int codeType,
        const String& langType,
        const String& areaCode,
        const String& extraJson) {}
		
void MSDKAccount::GetReceiveEmail(
        const String& channel,
        const String& account,
        int accountType,
        const String& langType,
        const String& areaCode,
        const String& extraJson) {}
		
void MSDKAccount::VerifyPassword(
        const String& channel,
        const String& account,
        const String& password,
        int accountType,
        const String& langType,
        const String& areaCode,
        const String& extraJson) {}


NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKAccount::SetAccountObserver(MSDKAccountObserver *observer) {}

void MSDKAccount::RequestVerifyCode(
                                    const String& channel,
                                    const String& account,
                                    int codeType,
                                    int accountType,
                                    const String& langType,
                                    const String& areaCode,
                                    const String& extraJson) {}

void MSDKAccount::ResetPassword(
                                const String& channel,
                                int verifyType,
                                const String& account,
                                const String& password,
                                const String& oldPassword,
                                int accountType,
                                int verifyCode,
                                const String& langType,
                                const String& areaCode,
                                const String& extraJson) {}

void MSDKAccount::Modify(
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
                         const String& areaCode,
                         const String& extraJson) {}

void MSDKAccount::GetRegisterStatus(
                                    const String& channel,
                                    const String& account,
                                    int accountType,
                                    const String& langType,
                                    const String& areaCode,
                                    const String& extraJson) {}

void MSDKAccount::GetVerifyCodeStatus(
                                      const String& channel,
                                      const String& account,
                                      int accountType,
                                      int verifyCode,
                                      int codeType,
                                      const String& langType,
                                      const String& areaCode,
                                      const String& extraJson) {}

void MSDKAccount::GetReceiveEmail(
                                  const String& channel,
                                  const String& account,
                                  int accountType,
                                  const String& langType,
                                  const String& areaCode,
                                  const String& extraJson) {}

void MSDKAccount::VerifyPassword(
                                 const String& channel,
                                 const String& account,
                                 const String& password,
                                 int accountType,
                                 const String& langType,
                                 const String& areaCode,
                                 const String& extraJson) {}


NS_MSDK_SPACE_NO_STL_END

#endif




