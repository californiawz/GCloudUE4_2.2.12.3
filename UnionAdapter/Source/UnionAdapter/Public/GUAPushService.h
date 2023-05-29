//
//  GUAPushService.h
//  GUASample
//
//  Created by weiqiangluo on 2022/5/9.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

#if GUA_OS_WINDOWS || WITH_EDITOR

class GUA_EXTERN GUALocalNotification
{
public:
    int type;
    int64_t builderID;
    int action_type;
    int icon_type;
    int ring;
    int lights;
    int vibrate;
    int styleID;
    std::string title;
    std::string content;
	std::string custom_content;
    std::string action_parameter;
    std::string package_download_url;
    std::string icon_res;
    std::string date;
    std::string hour;
    std::string min;
    std::string ring_raw;
    std::string small_icon;

    GUALocalNotification(): type(0), builderID(0), action_type(0), icon_type(0), ring(0), lights(0), vibrate(0), styleID(0) {
    }

};

#elif GUA_OS_IOS || GUA_OS_MAC

class GUA_EXTERN GUALocalNotification
{
public:
    /**
    *  notification repeat type, 0:default, don't repeat  1:repeat every minute, 2:hour, 3:day 4:week, 5:month 6:year
    *  Once been set, you need to remove by yourself.
    */
    int repeat_type;
    
    // [INTL only] Short push description
    std::string alert_title;

    // local notification fire time
    int64_t fire_time;
    
    // the badge for the notification
    int badge;
    
    // notification's content
    std::string alert_body;
    
    // the alert dialog's action button conent, default is Start
    std::string alert_action;

    /**
    * [INTL only] Specifies the notification ID.
    * When a notification with the same ID has already been displayed, the older notification is overwritten.
    */
	std::string notification_id;
    
    // custom parmas, add more messages
    std::map<std::string, std::string> user_info;

    GUALocalNotification():repeat_type(0),fire_time(0),badge(0){
    }
};
#elif GUA_OS_ANDROID

class GUA_EXTERN GUALocalNotification
{
public:
    
    // Specifies the notification ID.
    int64_t builderID;
    
    // Sets action type. 1: Open activity or app; 2: Open browser; 3: Open Intent; 4: Open app through package name;
    int action_type;
    
    // Whether to play sound. 0: No; 1: Yes; Default: 1;
    int ring;
    
    // Whether to light up. 0: No; 1: Yes; Default: 0;
    int lights;
    
    // Whether to vibrate. 0: No; 1: Yes; Default: 0;
    int vibrate;
    
    // Sets the notification trigger time, long type (timestamp in UTC time, units: seconds).
    int64_t fire_time;
    
    // Sets the message title.
    std::string title;
    
    // Sets message content.
    std::string content;
    
    // Sets ticker text content.
    std::string ticker_text;
    
    /**
     * When ActionType=1, ActionParameter can be the class name of the in-app activity.Example: com.intl.TestActivity
     * When ActionType=2, ActionParameter is a URL. When the user clicks the notification, this URL is directly opened in the browser.
     * When ActionType=3, ActionParameter is a serial Intent.
     * When ActionType=4, ActionParameter is the app package name.
     */
    std::string action_parameter;
    
    /**
     * Specifies the in-app sound (raw/ring.mp3).
     * Example: android.resource://intlgame.demo/raw/ring
     */
    std::string ring_raw;
    
    /**
     * Specifies the small icon of the status bar (test.png).
     * Example: test
     */
    std::string small_icon;

    // [MSDK Only] begin
    
    // configure local message type, 1: notification, 2: message
    int type;
    
    // Is the notification bar icon an in-app icon or an upload icon? (0 is an in-app icon , 1 is an upload icon , default 0)
    int icon_type;
    
    // Whether to overwrite the original configuration saved by build_id. 1 overwrite, 0 not overwrite
    int styleID;
    
    // custom the message, key-value
    std::string custom_content;
    
    // configure the URL for downloading app
    std::string package_download_url;
    
    // in-app icon file name (xg.png) or the URL for downloading the icon, such as: xg or image url
    std::string icon_res;
    
    // configure message date, format: 20140502
    std::string date;
    
    // configure the hour when the message is triggered (24-hour system), such as: 22 indicates 10pm
    std::string hour;
    
    // The minute when message is triggered, such as: 05 indicates 05 minutes
    std::string min;
    
    // [MSDK Only] end

    GUALocalNotification(): type(0), builderID(0), action_type(0), icon_type(0), ring(0), lights(0), vibrate(0), fire_time(0), styleID(0) {
    }

};
#else
class GUA_EXTERN GUALocalNotification
{
public:
	int repeatType = 0;

	GUALocalNotification() {
	}
};
#endif

class GUA_EXTERN GUAPushResult : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:

    // push message type, -1:unknown, 1:get remote push when app is in background,
    // 2:get remote push when app is running, 3:get local push when app is  in background
    int type = -1;
    
    // notification content
    std::string notification;
};

class GUA_EXTERN GUAPushObserver
{
public:
    virtual ~GUAPushObserver() {};

    virtual void OnPushOptNotify(const GUABaseResult &base_ret) {};

    virtual void OnReceiveNotification(const GUAPushResult &push_ret) {};
};

class GUA_EXTERN GUAPushService
{
public:
    /**
    * @brief Set push module observer
    *
    * @param pushObserver [required] object implememted from PushObserver
    */
    static void SetPushObserver(GUAPushObserver *push_observer);

    /**
    * @brief Register the specific channel
    *
    * @param channel [required] channel name, such as "FireBase"
    * @param account [optional] It can be user's openid, user name or something can identify a user. If set NULL, it will be the login openid.
    */
    static void RegisterPush(
        const std::string &channel, 
        const std::string &account = GUA_DEFAULT_EMPTY_STRING);

    /**
    * @brief Unregister push, the device will not get push from this channel.
    *
    * @param channel [required] channel name, such as "FireBase"
    */
    static void UnregisterPush(const std::string &channel);

    /**
    * @brief Set a tag, push can be made based on tags
    *
    * @param channel [required] channel name, such as "FireBase"
    * @param tag     [required] tag content
    */
    static void SetTag(
        const std::string &channel, 
        const std::string &tag);

    /**
    * @brief Delete a tag that has been set
    *
    * @param channel [required] channel name, such as "FireBase"
    * @param tag     [required] tag content
    */
    static void DeleteTag(
        const std::string &channel, 
        const std::string &tag);
    
    /**
     * @brief [MSDK Only] Set account to support pushing message by account
     *
     * @param channel [required] channel name, such as "FireBase"
     * @param account [required] account info
     */
    static void SetAccount(
        const std::string &channel, 
        const std::string &account);
    
    /**
     * @brief [MSDK Only] Delete account that has been set
     *
     * @param channel [required] channel name, such as "FireBase"
     * @param account [required] account info
     */
    static void DeleteAccount(
        const std::string &channel, 
        const std::string &account);

    /**
    * @brief Add local push message
    * The amount of local pushes is limited, pushes can't be more than 64 for recently, otherwise the push will be ignored by system
    *
    * @param channel				 [required] channel name, such as "FireBase"
    * @param gua_local_notification  [required] local notification data struce
    */
	static void AddLocalNotification(
        const std::string &channel, 
        const GUALocalNotification &gua_local_notification);

    /**
    * @brief clear local pushes.
    *
    * @param channel [required] channel name, such as "FireBase"
    */
    static void ClearLocalNotifications(const std::string &channel);


#if GUA_OS_IOS || GUA_OS_MAC
    /**
    * @brief Delete local notification by its key, only support iOS & MAC
    *
    * @param key [required] the key set by AddLocalNotification
    */
    static void DeleteLocalNotifications(const std::string &key);

    /**
     * @brief [MSDK Only] Add local push that can be displayed in the foreground
     *
     * @param gua_local_notification [required] local push object
     */
    static void AddLocalNotificationAtFront(GUALocalNotification &gua_local_notification);
    
    /**
    * @brief [MSDK Only] Clear push badge number
    */
    static void CleanBadgeNumber();
#endif
};

GUA_NAMESPACE_END
