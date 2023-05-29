//
// Created by lamarzhang(张庆贺) on 2019/1/7.
// Copyright (c) 2019 Epic Games, Inc. All rights reserved.
//

/************注意
* 每次更新此文件，请使用最新MSDKCore中的该文件
* 每次更新此文件，请使用最新MSDKCore中的该文件
* 每次更新此文件，请使用最新MSDKCore中的该文件
* 有问题联系lamar
*************
*/

#include "MSDKLogin.h"
#include "Serialization/JsonSerializer.h"
#include <Misc/FileHelper.h>
#include <Misc/Paths.h>

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

MSDKLoginObserver *MSDKLogin::mLoginObserver = NULL;

MSDKLoginRet getSimulateLoginRet(std::string channel, std::string subChannel) {
    std::string relativePath("TestPlugins/MSDKCore/Content/");
    relativePath.append(channel);
    relativePath.append(subChannel);
    relativePath.append("LoginData.txt");

    FString path = FPaths::ProjectPluginsDir() + relativePath.c_str();
    UE_LOG(LogTemp, Warning, TEXT("path:%s"), *path);

    FString jsonValue;
    FFileHelper::LoadFileToString(jsonValue, *path);
    UE_LOG(LogTemp, Warning, TEXT("path:%s"), *jsonValue);

	MSDKLoginRet loginRet(MSDKError::UNKNOWN);
    if (jsonValue.IsEmpty()) {
        UE_LOG(LogTemp, Warning, TEXT("couldn't read file: %s"), *path);
        loginRet.retMsg = "couldn't read file LoginData.txt";
    }

    if (!channel.empty()) {
        std::string tempRelativePath("TestPlugins/MSDKCore/Content/");
        tempRelativePath.append("LoginData.txt");
        FString tempPath = FPaths::ProjectPluginsDir() + tempRelativePath.c_str();
        FFileHelper::SaveStringToFile(jsonValue, *tempPath);
    }

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(jsonValue);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
        UE_LOG(LogTemp, Warning, TEXT("getSimulateLoginRet success"));

        //The person "object" that is retrieved from the given json file
        loginRet.thirdCode       = JsonObject->GetIntegerField("ret");
        loginRet.thirdMsg        = TCHAR_TO_UTF8(*JsonObject->GetStringField("msg"));
        loginRet.openID        = TCHAR_TO_UTF8(*JsonObject->GetStringField("openid"));
        loginRet.tokenExpire   = (long) JsonObject->GetNumberField("token_expire_time");
        loginRet.firstLogin    = JsonObject->GetIntegerField("first");
        loginRet.regChannelDis = TCHAR_TO_UTF8(*JsonObject->GetStringField("reg_channel_dis"));
        loginRet.userName      = TCHAR_TO_UTF8(*JsonObject->GetStringField("user_name"));
        loginRet.pictureUrl    = TCHAR_TO_UTF8(*JsonObject->GetStringField("picture_url"));
        loginRet.realNameAuth  = JsonObject->GetBoolField("need_name_auth");
        loginRet.channelInfo   = TCHAR_TO_UTF8(*JsonObject->GetStringField("channel_info"));
        loginRet.extraJson     = TCHAR_TO_UTF8(*JsonObject->GetStringField("extra"));
        loginRet.retCode     = JsonObject->GetIntegerField("retCode");
        loginRet.retMsg      = TCHAR_TO_UTF8(*JsonObject->GetStringField("retMsg"));
        // 伪造登录，使用特殊Token，到后台校验，目前token是所有游戏一样，后续改造
        loginRet.token         = "MSDKLOGINMOCKER_51433213c2e72a6304fb805b10a2201d";
        loginRet.gender        = JsonObject->GetIntegerField("gender");
        loginRet.birthdate     = TCHAR_TO_UTF8(*JsonObject->GetStringField("birthdate"));
        loginRet.pf            = TCHAR_TO_UTF8(*JsonObject->GetStringField("pf"));
        loginRet.pfKey         = TCHAR_TO_UTF8(*JsonObject->GetStringField("pfKey"));
        loginRet.channel       = TCHAR_TO_UTF8(*JsonObject->GetStringField("channel"));
        loginRet.channelID     = JsonObject->GetIntegerField("channelID");
        loginRet.methodNameID  = JsonObject->GetIntegerField("methodNameID");

    } else {
        UE_LOG(LogTemp, Warning, TEXT("couldn't deserialize"));
        loginRet.retMsg = "couldn't deserialize";
    }
    return loginRet;
}

bool MSDKLogin::GetPRVLoginRet(InnerLoginRet &ret) { return false; }

void MSDKLogin::SetLoginObserver(MSDKLoginObserver *observer) {
    UE_LOG(LogTemp, Warning, TEXT("SetLoginObserver"));
    mLoginObserver = observer;
}

void MSDKLogin::SetConnectObserver(MSDKConnectObserver *observer) {}

void MSDKLogin::AutoLogin() {
    UE_LOG(LogTemp, Warning, TEXT("AutoLogin"));
    MSDKLoginRet ret = getSimulateLoginRet("", "");
	if (mLoginObserver) {
		mLoginObserver->OnLoginRetNotify(ret);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("mLoginObserver is null"));
	}
}

void MSDKLogin::Login(const String &channel, const String &permissions, const String &subChannel, const String &extraJson) {
    UE_LOG(LogTemp, Warning, TEXT("Simulate Login"));
    MSDKLoginRet ret = getSimulateLoginRet(channel.c_str(), subChannel.c_str());
	if (mLoginObserver) {
		mLoginObserver->OnLoginRetNotify(ret);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("mLoginObserver is null"));
	}
}

void MSDKLogin::Bind(const String &channel, const String &permissions,
                     const String &subChannel, const String &extraJson) {
    UE_LOG(LogTemp, Warning, TEXT("Simulate Bind"));
    MSDKLoginRet ret(MSDKError::NOT_SUPPORT);
	if (mLoginObserver) {
		mLoginObserver->OnLoginRetNotify(ret);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("mLoginObserver is null"));
	}
}

void MSDKLogin::Connect(const String &channel, const String &permissions, const String &subChannel, const String &extraJson) {}

void MSDKLogin::UnConnect(const String &channel) {}

bool MSDKLogin::GetLoginRet(MSDKLoginRet &loginRet) {
    UE_LOG(LogTemp, Warning, TEXT("Simulate GetLoginRet"));
    loginRet = getSimulateLoginRet("", "");
    return true;
}

bool MSDKLogin::GetConnectRet(MSDKLoginRet &loginRet) { return false; }

bool MSDKLogin::SwitchUser(bool useLaunchUser) {
    UE_LOG(LogTemp, Warning, TEXT("Simulate SwitchUser"));
    return false;
}

void MSDKLogin::CanBind(const String &channel, const String &channelInfo, const String &extraJson) {}

void MSDKLogin::QueryUserInfo() {
    UE_LOG(LogTemp, Warning, TEXT("Simulate QueryUserInfo"));
    MSDKLoginRet ret = getSimulateLoginRet("", "");
	if (mLoginObserver) {
		mLoginObserver->OnLoginRetNotify(ret);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("mLoginObserver is null"));
	}
}

void MSDKLogin::Logout(const String &channel, const String &subChannel, const bool channelOnly) {
    UE_LOG(LogTemp, Warning, TEXT("Simulate Logout"));
    MSDKBaseRet ret(MSDKError::SUCCESS);
	if (mLoginObserver) {
		mLoginObserver->OnBaseRetNotify(ret);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("mLoginObserver is null"));
	}
}

void MSDKLogin::LoginWithConfirmCode(const int actionType, const String &confirmCode, const String &extraJson) {
	UE_LOG(LogTemp, Warning, TEXT("Simulate LoginWithConfirmCode"));
    MSDKLoginRet ret(MSDKError::NOT_SUPPORT);
	if (mLoginObserver) {
		mLoginObserver->OnLoginRetNotify(ret);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("mLoginObserver is null"));
	}
}

void MSDKLogin::ResetGuest(){
    UE_LOG(LogTemp, Warning, TEXT("Simulate ResetGuest"));
    MSDKLoginRet ret(MSDKError::NOT_SUPPORT);
    if (mLoginObserver) {
        mLoginObserver->OnLoginRetNotify(ret);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("mLoginObserver is null"));
    }
}

void MSDKLogin::CheckUniversalLink(const String &channel, const String &subChannel, const String &extra) {}

void MSDKLogin::CheckLogin(const String &channel, const String &permissions, const String &subChannel, const String &extraJson) {}
    
void MSDKLogin::Check(const String &channel, const String &permissions, const String &subChannel, const String &extraJson) {}
    
void MSDKLogin::BindWithConfirmCode(const String &confirmCode, int channelID, const String &extraJson) {}

NS_MSDK_END


NS_MSDK_SPACE_NO_STL_BEGIN

bool MSDKLogin::GetPRVLoginRet(InnerLoginRet &ret) { return false; }

void MSDKLogin::SetLoginObserver(MSDKLoginObserver *observer) {
}

void MSDKLogin::SetConnectObserver(MSDKConnectObserver *observer) {}

void MSDKLogin::AutoLogin() {
}

void MSDKLogin::Login(const String &channel, const String &permissions, const String &subChannel, const String &extraJson) {
}

void MSDKLogin::Bind(const String &channel, const String &permissions,
                     const String &subChannel, const String &extraJson) {
}

void MSDKLogin::Connect(const String &channel, const String &permissions, const String &subChannel, const String &extraJson) {}

void MSDKLogin::UnConnect(const String &channel) {}

bool MSDKLogin::GetLoginRet(MSDKLoginRet &loginRet) {
    return true;
}

bool MSDKLogin::GetConnectRet(MSDKLoginRet &loginRet) { return false; }

bool MSDKLogin::SwitchUser(bool useLaunchUser) {
    return false;
}

void MSDKLogin::CanBind(const String &channel, const String &channelInfo, const String &extraJson) {}

void MSDKLogin::QueryUserInfo() {
}

void MSDKLogin::Logout(const String &channel, const String &subChannel, const bool channelOnly) {
}

void MSDKLogin::LoginWithConfirmCode(const int actionType, const String &confirmCode, const String &extraJson) {
}

void MSDKLogin::ResetGuest(){
}

void MSDKLogin::CheckUniversalLink(const String &channel, const String &subChannel, const String &extra) {}

void MSDKLogin::CheckLogin(const String &channel, const String &permissions, const String &subChannel, const String &extraJson) {}

void MSDKLogin::Check(const String &channel, const String &permissions, const String &subChannel, const String &extraJson) {}

void MSDKLogin::BindWithConfirmCode(const String &confirmCode, int channelID, const String &extraJson) {}


NS_MSDK_SPACE_NO_STL_END

#endif




