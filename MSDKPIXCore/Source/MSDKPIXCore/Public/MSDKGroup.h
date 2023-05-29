/*!
 * @Module MSDK
 *
 * @Header  MSDKPGroup.h
 * @Author  developer
 * @date 2018/5/14
 * @abstract
 * 群创建、添加以及绑定相关接口声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */


#ifndef MSDK_GROUP_H
#define MSDK_GROUP_H

#include "MSDKMacros.h"
#include "MSDKDefine.h"

#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif
NS_MSDK_BEGIN


class MSDK_EXPORT MSDKGroupMessage
{
public:
    /**【必填】消息类型，1：应用邀请 2：link链接分享 */
    int type;

    /**【必填】分享类型，邀请1，炫耀2，赠送3，索要4 */
    int actionReport;

    /**【必填】，标题*/
    String title;

    /**【必填】，概述，消息的介绍*/
    String desc;

    /**【选填】，链接地址，type等于1时不需要带；type等于2时必须要带*/
    String link;

    /**【选填】，扩展字段，默认为空*/
    String extraJson;

    AutoParser("com.itop.gcloud.msdk.api.group.MSDKGroupMessage", O(type,actionReport,title,desc,link,extraJson));

};

class MSDKGroupInfo {
public:
    /**【必填】，群 id*/
    std::string groupID;

    /**【必填】，群名称*/
    std::string groupName;

     /**【选填】，扩展字段，默认为空*/
    std::string extraJson;

    AutoParser("com.itop.gcloud.msdk.api.group.MSDKGroupInfo", A(groupID, "gc"), A(groupName, "group_name"), O(extraJson));

};

class MSDK_EXPORT MSDKGroupRet : public MSDKBaseRet {
public:
    /**
     * 1、查询群用户和群的关系
     */
    int status;

    /**
     **/
    std::string groupID;

    /**
     */
    std::string groupName;

    /**
     *  group_openid，保留字段
     **/
    std::string groupOpenID;
    
    /**
    **/
    std::vector<MSDKGroupInfo> groupInfo;

    AutoParser("com.itop.gcloud.msdk.api.group.MSDKGroupRet",
               A(groupInfo, "group_list"), A(thirdCode, "ret"), A(thirdMsg, "msg"), A(extraJson, "extra"),
               O(retCode, retMsg, thirdCode, thirdMsg, status, groupID, groupName, groupOpenID, methodNameID));

};

class MSDK_EXPORT MSDKGroupObserver {
public:
    virtual ~MSDKGroupObserver() {};
    virtual void OnLoadGroupData(const MSDKGroupRet &groupRet) {
    };
};

class MSDK_EXPORT MSDKGroup {
private:

    static void GroupRetObserver(const InnerGroupRet &groupRet, const char *seqID) {
        MSDKGroupRet *pRet = new MSDKGroupRet();
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerGroupRet to MSDKGroupRet start");
        MSDKCompatManager::compatConvert(*pRet, groupRet);
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerGroupRet to MSDKGroupRet finish, and notify user");
        if (mGroupObserver) {
#if MSDK_ENGINE_UE4
            AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 GroupRetObserver");
                mGroupObserver->OnLoadGroupData(*pRet);
                delete pRet;
            });
#else
            mGroupObserver->OnLoadGroupData(*pRet);
            delete pRet;
#endif
        } else {
            MSDKPIX_LOG_ERROR(seqID, "group observer is null");
            delete pRet;
        }
    }

    static MSDKGroupObserver *mGroupObserver;

	static void SetPRVGroupObserver(typename T<InnerGroupRet>::InnerRetCallback groupObserver);

public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
	MSDK_EXPORT_UE static void SetGroupObserver(MSDKGroupObserver *groupObserver);
#else
	static void SetGroupObserver(MSDKGroupObserver *groupObserver) {
        if (!groupObserver) {
            MSDKPIX_LOG_ERROR("", "MSDKNoticeObserver can not be NULL");
        } else {
            mGroupObserver = groupObserver;
            SetPRVGroupObserver(GroupRetObserver);
        }
    }
#endif

    /**
     * @brief 创建群
     * @param unionID 工会 ID
     * @param unionName 工会名称
     * @param roleName 游戏中的角色名称
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param extraJson 扩展字段，默认为空
    */
	MSDK_EXPORT_UE static void CreateGroup(String unionID, String unionName ="", String roleName ="", String zoneID ="", String roleID = "", String extraJson= "");

    /**
     * @brief 绑定已经存在的群
     * @param unionID 工会 ID
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param groupID 群号，创建群时获得
     * @param groupName 群名，创建群时获得
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void BindGroup(String unionID, String zoneID, String roleID, String groupID, String groupName, String extraJson = "");

    /**
     * @brief 解绑群
     * @param unionID 工会 ID
     * @param unionName 工会名称
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void UnbindGroup(String unionID, String unionName = "", String zoneID = "", String roleID = "", String extraJson = "");

    /**
     * @brief 提醒会长建群，仅支持
     * @param unionID 工会信息
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param roleName 游戏角色名称，提醒的文案使用
     * @param leaderOpenID 会长 openID
     * @param leaderRoleID 会长角色 ID
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void RemindToBindGroup(String unionID, String zoneID, String roleID, String roleName, String leaderOpenID, String leaderRoleID, String extraJson = "");

    /**
     * @brief 获取会长的建群列表，仅支持
     */
	MSDK_EXPORT_UE static void GetGroupList();

    /**
     * 获取群状态
     * @param unionID 工会 ID
     * @param zoneID 游戏中的区服 ID
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void GetGroupState(String unionID, String zoneID = "", String extraJson = "") ;

    /**
     * 获取群关系
     * @param targetID 工会ID 或 群号
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void GetGroupRelation(String targetID, String extraJson = "");

    /**
     * @brief 加入群
     * @param unionID 工会 ID
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param groupID 群 ID
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void JoinGroup(String unionID, String zoneID = "", String roleID = "", String groupID = "", String extraJson = "");

    /**
     * @brief 发送群消息
     * @param groupMessage  群消息
     * @param unionID  工会 ID
     */
	MSDK_EXPORT_UE static void SendGroupMessage(const MSDKGroupMessage &groupMessage, String unionID);

};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

class MSDK_EXPORT MSDKGroupMessage
{
public:
    /**【必填】消息类型，1：应用邀请 2：link链接分享 */
    int type;
    
    /**【必填】分享类型，邀请1，炫耀2，赠送3，索要4 */
    int actionReport;
    
    /**【必填】，标题*/
    String title;
    
    /**【必填】，概述，消息的介绍*/
    String desc;
    
    /**【选填】，链接地址，type等于1时不需要带；type等于2时必须要带*/
    String link;
    
    /**【选填】，扩展字段，默认为空*/
    String extraJson;
    
    MSDK::MSDKGroupMessage convert() const {
        MSDK::MSDKGroupMessage message;
        message.type = type;
        message.actionReport = actionReport;
        message.title = title;
        message.desc = desc;
        message.link = link;
        message.extraJson = extraJson;
        return message;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.group.MSDKGroupMessage", O(type,actionReport,title,desc,link,extraJson));
    
};

class MSDKGroupInfo {
public:
    /**【必填】，群 id*/
    String groupID;
    
    /**【必填】，群名称*/
    String groupName;
    
    /**【选填】，扩展字段，默认为空*/
    String extraJson;
    
    MSDKGroupInfo(const MSDK::MSDKGroupInfo &groupInfo) {
        groupID = groupInfo.groupID;
        groupName = groupInfo.groupName;
        extraJson = groupInfo.extraJson;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.group.MSDKGroupInfo", A(groupID, "gc"), A(groupName, "group_name"), O(extraJson));
    
};

class MSDK_EXPORT MSDKGroupRet : public MSDKBaseRet {
public:
    /**
     * 1、查询群用户和群的关系
     */
    int status;
    
    /**
     **/
    String groupID;
    
    /**
     */
    String groupName;
    
    /**
     *  group_openid，保留字段
     **/
    String groupOpenID;
    
    /**
     **/
    Vector<MSDKGroupInfo> groupInfo;
    
    MSDKGroupRet(const MSDK::MSDKGroupRet &groupRet) : MSDKBaseRet(groupRet) {
        status = groupRet.status;
        groupID = groupRet.groupID;
        groupName = groupRet.groupName;
        groupOpenID = groupRet.groupOpenID;
        
        std::vector<MSDK::MSDKGroupInfo>::const_iterator it;
        for (it = groupRet.groupInfo.begin(); it != groupRet.groupInfo.end(); ++it) {
            groupInfo.push_back(*it);
        }
    }
    
    AutoParser("com.itop.gcloud.msdk.api.group.MSDKGroupRet",
               A(groupInfo, "group_list"), A(thirdCode, "ret"), A(thirdMsg, "msg"), A(extraJson, "extra"),
               O(retCode, retMsg, thirdCode, thirdMsg, status, groupID, groupName, groupOpenID, methodNameID));
};

class MSDK_EXPORT MSDKGroupObserver {
public:
    virtual ~MSDKGroupObserver() {};
    virtual void OnLoadGroupData(const MSDKGroupRet &groupRet) {
    };
};

class MSDKGroupObserverAdapter : public MSDK::MSDKGroupObserver {
public:
    void OnLoadGroupData(const MSDK::MSDKGroupRet &groupRet);
    MSDKSpace::NoSTL::MSDKGroupObserver *mObserver = NULL;
};

class MSDK_EXPORT MSDKGroup {
private:
    static MSDKGroupObserverAdapter mGroupObserverAdapter;

public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    MSDK_EXPORT_UE static void SetGroupObserver(MSDKGroupObserver *groupObserver);
#else
    static void SetGroupObserver(MSDKGroupObserver *groupObserver) {
        if (!groupObserver) {
            MSDKPIX_LOG_ERROR("", "MSDKNoticeObserver can not be NULL");
        } else {
            mGroupObserverAdapter.mObserver = groupObserver;
            MSDK::MSDKGroup::SetGroupObserver(&mGroupObserverAdapter);
        }
    }
#endif

    /**
     * @brief 创建群
     * @param unionID 工会 ID
     * @param unionName 工会名称
     * @param roleName 游戏中的角色名称
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void CreateGroup(String unionID, String unionName ="", String roleName ="", String zoneID ="", String roleID = "", String extraJson= "");
    
    /**
     * @brief 绑定已经存在的群
     * @param unionID 工会 ID
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param groupID 群号，创建群时获得
     * @param groupName 群名，创建群时获得
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void BindGroup(String unionID, String zoneID, String roleID, String groupID, String groupName, String extraJson = "");
    
    /**
     * @brief 解绑群
     * @param unionID 工会 ID
     * @param unionName 工会名称
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void UnbindGroup(String unionID, String unionName = "", String zoneID = "", String roleID = "", String extraJson = "");
    
    /**
     * @brief 提醒会长建群，仅支持
     * @param unionID 工会信息
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param roleName 游戏角色名称，提醒的文案使用
     * @param leaderOpenID 会长 openID
     * @param leaderRoleID 会长角色 ID
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void RemindToBindGroup(String unionID, String zoneID, String roleID, String roleName, String leaderOpenID, String leaderRoleID, String extraJson = "");
    
    /**
     * @brief 获取会长的建群列表，仅支持
     */
    MSDK_EXPORT_UE static void GetGroupList();

    /**
     * 获取群状态
     * @param unionID 工会 ID
     * @param zoneID 游戏中的区服 ID
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void GetGroupState(String unionID, String zoneID = "", String extraJson = "") ;
    
    /**
     * 获取群关系
     * @param targetID 工会ID 或 群号
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void GetGroupRelation(String targetID, String extraJson = "");
    
    /**
     * @brief 加入群
     * @param unionID 工会 ID
     * @param zoneID 游戏区服 ID
     * @param roleID 游戏角色 ID
     * @param groupID 群 ID
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void JoinGroup(String unionID, String zoneID = "", String roleID = "", String groupID = "", String extraJson = "");
    
    /**
     * @brief 发送群消息
     * @param groupMessage  群消息
     * @param unionID  工会 ID
     */
    MSDK_EXPORT_UE static void SendGroupMessage(const MSDKGroupMessage &groupMessage, String unionID);
};

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDKGroup_hpp */
