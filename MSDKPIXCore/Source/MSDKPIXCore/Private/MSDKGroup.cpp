//
// Created by mikefu on 2021/8/11.
// Copyright (c) 2021 Epic Games, Inc. All rights reserved.
//


#include "MSDKGroup.h"

#if MSDK_ENGINE_UE4_SIMULATE_LOGIN

NS_MSDK_BEGIN

void MSDKGroup::SetGroupObserver(MSDKGroupObserver *groupObserver) {}

void MSDKGroup::CreateGroup(String unionID, String unionName, String roleName, String zoneID, String roleID, String extraJson) {}

void MSDKGroup::BindGroup(String unionID, String zoneID, String roleID, String groupID, String groupName, String extraJson) {}

void MSDKGroup::UnbindGroup(String unionID, String unionName, String zoneID, String roleID, String extraJson) {}

void MSDKGroup::RemindToBindGroup(String unionID, String zoneID, String roleID, String roleName, String leaderOpenID, String leaderRoleID, String extraJson) {}

void MSDKGroup::GetGroupList() {}

void MSDKGroup::GetGroupState(String unionID, String zoneID, String extraJson) {}

void MSDKGroup::GetGroupRelation(String targetID, String extraJson) {}

void MSDKGroup::JoinGroup(String unionID, String zoneID, String roleID, String groupID, String extraJson) {}

void MSDKGroup::SendGroupMessage(const MSDKGroupMessage &groupMessage, String unionID) {}

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

void MSDKGroup::SetGroupObserver(MSDKGroupObserver *groupObserver) {}

void MSDKGroup::CreateGroup(String unionID, String unionName, String roleName, String zoneID, String roleID, String extraJson) {}

void MSDKGroup::BindGroup(String unionID, String zoneID, String roleID, String groupID, String groupName, String extraJson) {}

void MSDKGroup::UnbindGroup(String unionID, String unionName, String zoneID, String roleID, String extraJson) {}

void MSDKGroup::RemindToBindGroup(String unionID, String zoneID, String roleID, String roleName, String leaderOpenID, String leaderRoleID, String extraJson) {}

void MSDKGroup::GetGroupList() {}

void MSDKGroup::GetGroupState(String unionID, String zoneID, String extraJson) {}

void MSDKGroup::GetGroupRelation(String targetID, String extraJson) {}

void MSDKGroup::JoinGroup(String unionID, String zoneID, String roleID, String groupID, String extraJson) {}

void MSDKGroup::SendGroupMessage(const MSDKGroupMessage &groupMessage, String unionID) {}

NS_MSDK_SPACE_NO_STL_END
#endif




