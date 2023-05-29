/*!
 * @Module MSDK
 *
 * @Header  MSDKNotice.h
 * @Author  developer
 * @date 2018/2/20
 * @abstract
 * 获取公告信息
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */



#ifndef MSDK_NOTICE_H
#define MSDK_NOTICE_H

#include <stdio.h>
#include "MSDKDefine.h"
#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif

NS_MSDK_BEGIN

class MSDKNoticePictureInfo
{
public:
    std::string noticePicUrl;
    std::string noticePicHashcode;
    std::string noticePicTitle;
    std::string noticePicSize;
    int screenDir; //0-未知 1-竖向 2-横向

AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticePictureInfo",
           A(noticePicUrl, "pic_url"), A(noticePicHashcode, "pic_hash"),
           A(noticePicTitle, "pic_title"), A(noticePicSize, "pic_size"),
           A(screenDir, "pic_dir"));

};


class MSDKNoticeTextInfo
{
public:
    std::string noticeTitle;
    std::string noticeContent;
    std::string noticeRedirectUrl;

AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeTextInfo",
           A(noticeTitle, "notice_title"), A(noticeContent, "notice_content"),
           A(noticeRedirectUrl, "notice_redirect_url"));


};

class MSDKNoticeInfo
{
public:
    int noticeID;
    int noticeType;//公告类型，1000~1999表示登录前公告;2000~2999表示登录后公告
    std::string noticeGroup; //公告分组，游戏自定义使用
    int beginTime;
    int endTime;
    int updateTime;
    int order;

    int contentType;//1-文本，2-图片，3-网页
    std::string language; //语言类型

    MSDKNoticeTextInfo textInfo;
    std::vector<MSDKNoticePictureInfo> picUrlList;
    std::string webUrl;//网页公告链接
    std::string extraJson;

AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeInfo",
           A(noticeID, "notice_id"), A(noticeType, "notice_type"),
           A(noticeGroup, "notice_group"), A(beginTime, "start_time"),
           A(endTime, "end_time"), A(updateTime, "update_time"),
           A(contentType, "content_type"), A(textInfo, "notice_text_obj"),
           A(picUrlList, "notice_pic_list"), A(webUrl, "notice_web_url"),
           A(extraJson, "extra_data"), O(order, language));

};

class MSDK_EXPORT MSDKNoticeRet : public MSDKBaseRet
{
public:
    std::string reqID;
    std::vector<MSDKNoticeInfo> noticeInfoList;

AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeRet",
           A(thirdCode, "ret"), A(thirdMsg, "msg"),
           A(noticeInfoList, "notice_list"),
           O(retCode, retMsg, methodNameID, extraJson, reqID));

};


class MSDK_EXPORT MSDKNoticeObserver
{
public:
    virtual ~MSDKNoticeObserver() {};
    virtual void OnLoadNoticeData(const MSDKNoticeRet &noticeRet) {};
};

class MSDK_EXPORT MSDKNotice
{
private:
    static MSDKNoticeObserver *mNoticeObserver;
#if MSDK_PLATFORM_WINDOWS
	static void NoticeRetObserver(const InnerNoticeRet &noticeRet, const char *seqID)
	{
		MSDKNoticeRet *pRet = new MSDKNoticeRet();
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerNoticeRet to MSDKNoticeRet start");
		//MSDKCompatManager::compatConvert(*pRet, noticeRet);
		pRet->methodNameID = noticeRet.methodNameID;
		pRet->retCode = noticeRet.retCode;
		pRet->retMsg = noticeRet.retMsg.c_str();
		pRet->thirdCode = noticeRet.thirdCode;
		pRet->thirdMsg = noticeRet.thirdMsg.c_str();
		pRet->extraJson = noticeRet.extraJson.c_str();
		pRet->reqID = noticeRet.reqID.c_str();
		std::vector<MSDKNoticeInfo> notice_info_list;
		for (unsigned int i = 0; i < noticeRet.noticeInfoList.size(); i++)
		{
			InnerNoticeInfo inner_notice_info = noticeRet.noticeInfoList[i];
			MSDKNoticeInfo notice_info;
			notice_info.noticeID = inner_notice_info.noticeID;
			notice_info.noticeType = inner_notice_info.noticeType;
			notice_info.noticeGroup = inner_notice_info.noticeGroup.c_str();
			notice_info.beginTime = inner_notice_info.beginTime;
			notice_info.endTime = inner_notice_info.endTime;
			notice_info.updateTime = inner_notice_info.updateTime;
			notice_info.order = inner_notice_info.order;
			notice_info.contentType = inner_notice_info.contentType;
			notice_info.language = inner_notice_info.language.c_str();
			MSDKNoticeTextInfo text_info;
			text_info.noticeContent = inner_notice_info.textInfo.noticeContent.c_str();
			text_info.noticeRedirectUrl = inner_notice_info.textInfo.noticeRedirectUrl.c_str();
			text_info.noticeTitle = inner_notice_info.textInfo.noticeTitle.c_str();
			notice_info.textInfo = text_info;
			std::vector<MSDKNoticePictureInfo> pic_info_list;
			for (unsigned int j = 0; j < inner_notice_info.picUrlList.size(); j++)
			{
				InnerNoticePictureInfo inner_picture_info = inner_notice_info.picUrlList[j];
				MSDKNoticePictureInfo pic_info;
				pic_info.noticePicHashcode = inner_picture_info.noticePicHashcode.c_str();
				pic_info.noticePicSize = inner_picture_info.noticePicSize.c_str();
				pic_info.noticePicTitle = inner_picture_info.noticePicTitle.c_str();
				pic_info.noticePicUrl = inner_picture_info.noticePicUrl.c_str();
				pic_info.screenDir = inner_picture_info.screenDir;
				pic_info_list.push_back(pic_info);
			}
			notice_info.picUrlList = pic_info_list;
			notice_info.webUrl = inner_notice_info.webUrl.c_str();
			notice_info.extraJson = inner_notice_info.extraJson.c_str();
			notice_info_list.push_back(notice_info);
		}
		pRet->noticeInfoList = notice_info_list;
		MSDKPIX_LOG_DEBUG(seqID, "convert InnerNoticeRet to MSDKNoticeRet finish then will notify user");

		if (mNoticeObserver)
		{
			mNoticeObserver->OnLoadNoticeData(*pRet);
			delete pRet;
		}
		else
		{
			MSDKPIX_LOG_ERROR(seqID, "notice observer is null");
			delete pRet;
		}

	}
#else
    static void NoticeRetObserver(const InnerNoticeRet &noticeRet, const char *seqID)
    {
        MSDKNoticeRet *pRet = new MSDKNoticeRet();
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerNoticeRet to MSDKNoticeRet start");
        MSDKCompatManager::compatConvert(*pRet, noticeRet);
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerNoticeRet to MSDKNoticeRet finish then will notify user");

        if (mNoticeObserver)
        {
#if MSDK_ENGINE_UE4
            AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                MSDKPIX_LOG_DEBUG(seqID, "Async Task In NoticeRetObserver");
                mNoticeObserver->OnLoadNoticeData(*pRet);
                delete pRet;
            });
#else
            mNoticeObserver->OnLoadNoticeData(*pRet);
            delete pRet;
#endif
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "notice observer is null");
            delete pRet;
        }

    }
#endif

    static void SetPRVNoticeObserver(typename T<InnerNoticeRet>::InnerRetCallback noticeObserver);

	MSDK_EXPORT_UE static String LoadPRVNoticeData(const String &noticeGroup, const String &language, int region,
                                 const String &partition, const String &extra);
public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
	MSDK_EXPORT_UE static void SetNoticeObserver(MSDKNoticeObserver *noticeObserver);
#else
	static void SetNoticeObserver(MSDKNoticeObserver *noticeObserver)
    {
        if (!noticeObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKNoticeObserver cant not be NULL");
            return;
        }

        mNoticeObserver = noticeObserver;

        SetPRVNoticeObserver(NoticeRetObserver);
    }
#endif

    /**
    * 拉取公告信息
    *
    * @param noticeGroup 公告群号，指定公告属于哪个群组
    * @param language    需要拉取的公告语种
    * @param region      公告的地区
    * @param partition   游戏大区
    * @param extra   扩展字段
    */

	MSDK_EXPORT_UE static std::string LoadNoticeData(const String &noticeGroup, const String &language, int region,
		const String &partition, const String &extra)
    {
        MSDKPIX_LOG_DEBUG("", "LoadNoticeData, noticeGroup:%s, language:%s, region:%d, partition:%s, extra:%s",
                          noticeGroup.c_str(), language.c_str(), region, partition.c_str(), extra.c_str());
        return LoadPRVNoticeData(noticeGroup, language,region, partition, extra).c_str();
    }

};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

class MSDKNoticePictureInfo
{
public:
    String noticePicUrl;
    String noticePicHashcode;
    String noticePicTitle;
    String noticePicSize;
    int screenDir; //0-未知 1-竖向 2-横向
    
    MSDKNoticePictureInfo(const MSDK::MSDKNoticePictureInfo &pictureInfo) {
        noticePicUrl = pictureInfo.noticePicUrl;
        noticePicHashcode = pictureInfo.noticePicHashcode;
        noticePicTitle = pictureInfo.noticePicTitle;
        noticePicSize = pictureInfo.noticePicSize;
        screenDir = pictureInfo.screenDir;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticePictureInfo",
               A(noticePicUrl, "pic_url"), A(noticePicHashcode, "pic_hash"),
               A(noticePicTitle, "pic_title"), A(noticePicSize, "pic_size"),
               A(screenDir, "pic_dir"));
    
};


class MSDKNoticeTextInfo
{
public:
    String noticeTitle;
    String noticeContent;
    String noticeRedirectUrl;
    
    MSDKNoticeTextInfo(const MSDK::MSDKNoticeTextInfo &textInfo) {
        noticeTitle = textInfo.noticeTitle;
        noticeContent = textInfo.noticeContent;
        noticeRedirectUrl = textInfo.noticeRedirectUrl;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeTextInfo",
               A(noticeTitle, "notice_title"), A(noticeContent, "notice_content"),
               A(noticeRedirectUrl, "notice_redirect_url"));
    
    
};

class MSDKNoticeInfo
{
public:
    int noticeID;
    int noticeType;//公告类型，1000~1999表示登录前公告;2000~2999表示登录后公告
    String noticeGroup; //公告分组，游戏自定义使用
    int beginTime;
    int endTime;
    int updateTime;
    int order;
    
    int contentType;//1-文本，2-图片，3-网页
    String language; //语言类型
    
    MSDKNoticeTextInfo textInfo;
    Vector<MSDKNoticePictureInfo> picUrlList;
    String webUrl;//网页公告链接
    String extraJson;
    
    MSDKNoticeInfo(const MSDK::MSDKNoticeInfo &noticeInfo) : textInfo(noticeInfo.textInfo) {
        noticeID = noticeInfo.noticeID;
        noticeType = noticeInfo.noticeType;
        noticeGroup = noticeInfo.noticeGroup;
        beginTime = noticeInfo.beginTime;
        endTime = noticeInfo.endTime;
        updateTime = noticeInfo.updateTime;
        order = noticeInfo.order;
        contentType = noticeInfo.contentType;
        language = noticeInfo.language;
        webUrl = noticeInfo.webUrl;
        extraJson = noticeInfo.extraJson;
        
        std::vector<MSDK::MSDKNoticePictureInfo>::const_iterator it;
        for (it = noticeInfo.picUrlList.begin(); it != noticeInfo.picUrlList.end(); ++it) {
            picUrlList.push_back(MSDKNoticePictureInfo(*it));
        }
    }
    
    AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeInfo",
               A(noticeID, "notice_id"), A(noticeType, "notice_type"),
               A(noticeGroup, "notice_group"), A(beginTime, "start_time"),
               A(endTime, "end_time"), A(updateTime, "update_time"),
               A(contentType, "content_type"), A(textInfo, "notice_text_obj"),
               A(picUrlList, "notice_pic_list"), A(webUrl, "notice_web_url"),
               A(extraJson, "extra_data"), O(order, language));
    
};

class MSDK_EXPORT MSDKNoticeRet : public MSDKBaseRet
{
public:
    String reqID;
    Vector<MSDKNoticeInfo> noticeInfoList;
    
    MSDKNoticeRet(const MSDK::MSDKNoticeRet &noticeRet) : MSDKBaseRet(noticeRet) {
        reqID = noticeRet.reqID;
        std::vector<MSDK::MSDKNoticeInfo>::const_iterator it;
        for (it = noticeRet.noticeInfoList.begin(); it != noticeRet.noticeInfoList.end(); ++it) {
            noticeInfoList.push_back(MSDKNoticeInfo(*it));
        }
    }
    
    AutoParser("com.itop.gcloud.msdk.api.notice.MSDKNoticeRet",
               A(thirdCode, "ret"), A(thirdMsg, "msg"),
               A(noticeInfoList, "notice_list"),
               O(retCode, retMsg, methodNameID, extraJson, reqID));
    
};

class MSDK_EXPORT MSDKNoticeObserver
{
public:
    virtual ~MSDKNoticeObserver() {};
    virtual void OnLoadNoticeData(const MSDKNoticeRet &noticeRet) {};
};

class MSDKNoticeObserverAdapter : public MSDK::MSDKNoticeObserver
{
public:
    void OnLoadNoticeData(const MSDK::MSDKNoticeRet &noticeRet);
    
    MSDKSpace::NoSTL::MSDKNoticeObserver *mObserver = NULL;
};

class MSDK_EXPORT MSDKNotice
{
private:
    static MSDKNoticeObserverAdapter mNoticeObserverAdapter;
public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    MSDK_EXPORT_UE static void SetNoticeObserver(MSDKNoticeObserver *noticeObserver);
#else
    static void SetNoticeObserver(MSDKNoticeObserver *noticeObserver)
    {
        if (!noticeObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKNoticeObserver cant not be NULL");
            return;
        }
        
        mNoticeObserverAdapter.mObserver = noticeObserver;
        MSDK::MSDKNotice::SetNoticeObserver(&mNoticeObserverAdapter);
    }
#endif
    
    /**
     * 拉取公告信息
     *
     * @param noticeGroup 公告群号，指定公告属于哪个群组
     * @param language    需要拉取的公告语种
     * @param region      公告的地区
     * @param partition   游戏大区
     * @param extra   扩展字段
     */
    
    MSDK_EXPORT_UE static String LoadNoticeData(const String &noticeGroup, const String &language, int region,
                                                const String &partition, const String &extra);
    
};

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDK_NOTICE_H */
