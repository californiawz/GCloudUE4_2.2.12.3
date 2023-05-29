//
//  GUANoticeService.h
//  GUASample
//
//  Created by tafflin on 2022/6/9.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

class GUA_EXTERN GUANoticePictureInfo
{
public:
    // Picture url
    std::string pic_url;

    // Picture hash code
    std::string pic_hash;

    // [MSDK Only] Picture title
    std::string pic_title;

    // [MSDK Only] Picture size
    std::string pic_size;

    // [MSDK Only] 0-unknown 1-partrial 2-landscape
    int screen_dir; 

    // [INTLSDK Only] Redirected picture url
    std::string pic_redirect_url;

    // [INTLSDK Only] Extra data if needed, customized at the Manager then posted to game
    std::string extra_data;
};

class GUA_EXTERN GUANoticeTextInfo
{
public:
    // Notice title
    std::string title;

    // Notice content
    std::string content;

    // [MSDK Only] Redirected url
    std::string redirect_url;

    // [INTLSDK Only] ID for content
    int content_id = 0;

    // [INTLSDK Only] Notice from distribute system id
    std::string app_content_id;

    // [INTLSDK Only] Notice language type
    std::string lang_type;

    // [INTLSDK Only] Notice update time
    int update_time = 0;

    // [INTLSDK Only] Extra data if needed, customized at the Manager then posted to game
    std::string extra_data;

    // [INTLSDK Only] Notice picture list
    std::vector<GUANoticePictureInfo> picture_list;
};

class GUA_EXTERN GUANoticeInfo
{
public:
    // Notice ID
    int notice_id;

    // Notice take effect time
    int begin_time;

    // Notice expire time
    int end_time;

    // Last update time
    int update_time;

    // Notice picture list
    std::vector<GUANoticePictureInfo> pic_url_list;

    // [MSDK Only] Notice type : 1000~1999 pre-login announcement;2000~2999 Announcement after login
    int notice_type;

    // [MSDK Only] Notice group : game customization
    std::string notice_group;

    // [MSDK Only] Order
    int order;

    // [MSDK Only] Content type : 1-text，2-texture，3-web
    int content_type;

    // [MSDK Only] Content language
    std::string language;

    // [MSDK Only] Notice text
    GUANoticeTextInfo text_info;

    // [MSDK Only] Web page announcement link
    std::string web_url;

    // [INTLSDK Only] App ID
    std::string app_id;

    // [INTLSDK Only] Notice ID from distribute system
    std::string app_notice_id;

    // [INTLSDK Only] Notice status
    int status;

    // [INTLSDK Only] The are list of the notice
    std::string area_list;

    // [INTLSDK Only] Notice text list
    std::vector<GUANoticeTextInfo> content_list;

    // [INTLSDK Only] Extra data for customize
    std::string extra_json;
};

class GUA_EXTERN GUANoticeResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    std::string req_id;
    std::vector<GUANoticeInfo> notice_info_list;
};

class GUA_EXTERN GUANoticeObserver
{
public:
    virtual ~GUANoticeObserver() {};
    virtual void OnLoadNoticeData(const GUANoticeResult &notice_result) {};
};

class GUA_EXTERN GUANoticeService
{
// Common API
public:

	/**
	 * @brief set Notice module Observer
	 * @param observer       [required] object implements from NoticeObserver
	 */
    static void SetNoticeObserver(GUANoticeObserver *notice_observer);

	/**
   * @brief  request notice data
   *
   * @param notice_group  [required] you can pull the announcement information with notice_group accordingly,this parameter is not used in INTLSDK
   * @param language      [required] get notice data with the language
   * @param region        [required] get notice data from the region
   * @param partition     [required] game zone,this parameter is not used in INTLSDK
   * @param extra_json    [optional] extra params with json format
   * 
   * @return notice data
   */
    static std::string LoadNoticeData(
		const std::string &notice_group, 
		const std::string &language, 
		const std::string &region,
		const std::string &partition, 
		const std::string &extra_json = GUA_DEFAULT_JSON_STRING);
// Common API End
};

GUA_NAMESPACE_END
