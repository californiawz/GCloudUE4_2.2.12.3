/*!
 * @Module MSDK
 *
 * @Header  MSDKPush.h
 * @Author  developer
 * @date 2018/6/4
 * @abstract
 * 推送模块对外接口声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */


#ifndef MSDK_PUSH_H
#define MSDK_PUSH_H

#include "MSDKDefine.h"
#include "MSDKSingleton.h"

#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif
NS_MSDK_BEGIN

#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
        class MSDKLocalNotification
        {
        public:
            int type;
            int actionType;
            int iconType;
            int lights;
            int ring;
            int vibrate;
            int styleID;
            int64_t builderID;
            std::string content;
            std::string customContent;
            std::string activity;
            std::string packageDownloadUrl;
            std::string packageName;
            std::string iconRes;
            std::string date;
            std::string hour;
            std::string intent;
            std::string min;
            std::string title;
            std::string url;
            std::string ringRaw;
            std::string smallIcon;
            InnerLocalNotification convertToInner() const
            {
                InnerLocalNotification notification;
                MSDKCompatManager::compatConvert(notification, *this);
                return notification;
            }
        };
#else
#ifdef __APPLE__

        class MSDKLocalNotification
        {
        public:
            /*!
                *  推送重复发送周期。 1-分钟，2-小时，3-天，4-星期，5-月，6-年，默认是0代表不重复。
                *  如果设、、置此属性, 那么调度池不会用完释放改推送！需要手动删除通知对象
                */
            int repeatType;
            /*!本地推送触发的时间*/
            int64_t fireTime;
            /** 角标 */
            int badge;
            /** 推送的内容 */
            String alertBody;
            /** 替换弹框的按钮文字内容（默认为"启动"）*/
            String alertAction;
            /** 自定义参数，可以用来标识推送和增加附加信息 */
            std::map<std::string, std::string> userInfo;

            MSDKLocalNotification():repeatType(0),fireTime(0),badge(0){
            }

            InnerLocalNotification convertToInner() const {
                InnerLocalNotification localNotification;
                localNotification.repeatType = this->repeatType;
                localNotification.fireTime = this->fireTime;
                localNotification.badge = this->badge;
                localNotification.alertBody = this->alertBody;
                localNotification.alertAction = this->alertAction;

                std::map<std::string, std::string>::const_iterator it = this->userInfo.begin();
                for (; it != this->userInfo.end(); it++) {
                    KVPair kvPair;
                    kvPair.key = (*it).first;
                    kvPair.value = (*it).second;
                    localNotification.userInfo.push_back(kvPair);
                    MSDKPIX_LOG_DEBUG("", "key is:[%s] value is: [%s]", kvPair.key.c_str(),kvPair.value.c_str());
                }
                return localNotification;
            }

            AutoParser("com.itop.gcloud.msdk.api.push.MSDKLocalNotification", O(repeatType, fireTime,badge, alertBody,alertAction,userInfo));
        };
#endif

#ifdef ANDROID

        class MSDK_EXPORT MSDKLocalNotification {
        public:
            int type;
            int actionType;
            int iconType;
            int lights;
            int ring;
            int vibrate;
            int styleID;
            int64_t builderID;
            std::string content;
            std::string customContent;
            std::string activity;
            std::string packageDownloadUrl;
            std::string packageName;
            std::string iconRes;
            std::string date;
            std::string hour;
            std::string intent;
            std::string min;
            std::string title;
            std::string url;
            std::string ringRaw;
            std::string smallIcon;

            MSDKLocalNotification() : type(0), actionType(0), iconType(0), lights(0), ring(0),
                                      vibrate(0), styleID(0), builderID(0) {
            }

            InnerLocalNotification convertToInner() const {
                InnerLocalNotification notification;
                MSDKCompatManager::compatConvert(notification, *this);
                return notification;
            }

        AutoParser("com.itop.gcloud.msdk.api.push.MSDKLocalNotification",
                   O(type, actionType, iconType, lights, ring, vibrate,
                     styleID, builderID, content, customContent, activity,
                     packageDownloadUrl, packageName, iconRes, date, hour,
                     intent, min, title, url, ringRaw, smallIcon));
        };

#endif
#endif

        class MSDK_EXPORT MSDKPushRet : public MSDKBaseRet {
        public:
            /** 收到消息类型 -1：未知，0:应用在前台时收到的远程通知，1:应用在后台收收到的远程通知，2:应用在前台时收到的本地通知，3:应用在后台收收到的本地通知**/
            int type;
            /** 收到消息内容*/
            std::string notification;

        AutoParser("com.itop.gcloud.msdk.api.push.MSDKPushRet",
                   A(type, "type"),
                   A(notification, "notification"),
                   A(thirdCode, "ret"),
                   A(thirdMsg, "msg"),
//           A(extraJson, "extra"),
                   O(retCode, retMsg, methodNameID, extraJson));


        };


        class MSDK_EXPORT MSDKPushObserver {
        public:
            virtual ~MSDKPushObserver() {};

            virtual void OnPushOptNotify(const MSDKBaseRet &baseRet) {};

            virtual void OnReceiveNotification(const MSDKPushRet &pushRet) {};
        };

        class MSDK_EXPORT MSDKPush {
        private :
            static void PushBaseRetObserver(const InnerBaseRet &baseRet, const char *seqID) {
                MSDKBaseRet *pRet = new MSDKBaseRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet start");
                MSDKCompatManager::compatConvert(*pRet, baseRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet finish then will notify user");
                if (mPushObserver) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                        MSDKPIX_LOG_DEBUG(seqID, "Async Task In PushBaseRetObserver");
                        mPushObserver->OnPushOptNotify(*pRet);
                        delete pRet;
                    });
#else
                    mPushObserver->OnPushOptNotify(*pRet);
                    delete pRet;
#endif
                } else {
                    MSDKPIX_LOG_ERROR(seqID, "push observer is null");
                    delete pRet;
                }
            }

            static void PushRetObserver(const InnerPushRet &pushRet, const char *seqID) {
                MSDKPushRet *pRet = new MSDKPushRet();
                MSDKPIX_LOG_DEBUG(seqID, "add new login line for text Unity update");
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerPushRet to MSDKPushRet start change extra to extraJson");
                MSDKCompatManager::compatConvert(*pRet, pushRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerPushRet to MSDKBaseRet finish then will notify user");
                if (mPushObserver) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                        MSDKPIX_LOG_DEBUG(seqID, "Async Task In PushRetObserver");
                        mPushObserver->OnReceiveNotification(*pRet);
                        delete pRet;
                    });
#else
                    mPushObserver->OnReceiveNotification(*pRet);
                    delete pRet;
#endif
                } else {
                    MSDKPIX_LOG_ERROR(seqID, "push observer is null");
                    delete pRet;
                }
            }

            static MSDKPushObserver *mPushObserver;

            MSDK_EXPORT_UE static void AddLocalNotificationPRV(const String &channel,
                                                               const InnerLocalNotification &notification);

            static void
            SetPushObserverPRV(typename T<InnerBaseRet>::InnerRetCallback baseRetObserver,
                               typename T<InnerPushRet>::InnerRetCallback pushRetObserver);

            static void
            addLocalNotificationAtFrontPRV(const InnerLocalNotification &localNotification);

        public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
            MSDK_EXPORT_UE static void SetPushObserver(MSDKPushObserver *pushObserver);
#else

            static void SetPushObserver(MSDKPushObserver *pushObserver) {
                if (!pushObserver) {
                    MSDKPIX_LOG_ERROR("", "MSDKPushObserver cant not be NULL");
                } else {
                    mPushObserver = pushObserver;
                    SetPushObserverPRV(PushBaseRetObserver, PushRetObserver);
                }
            }

#endif

            /**
            * @brief 注册指定渠道推送模块，包括注销设备后，重新注册设备的情况
            *
            * @param channel 渠道信息，比如“XG”、“Firebase" 等
            * @param account  用户的帐号（别名）。上报用户的帐号（别名），以便支持按帐号（别名）推送。如果填 NULL，使用登录成功的openID 作为账号（别名）
            */
            MSDK_EXPORT_UE static void
            RegisterPush(const String &channel, const String &account = "");

            /**
            * @brief 注销设备,此台设备不接收推送
            *
            * @param channel 渠道信息，比如“XG”、“Firebase" 等
            */
            MSDK_EXPORT_UE static void UnregisterPush(const String &channel);

            /**
            * @brief 设置标签，针对不同用户设置不同标签
            *
            * @param channel 渠道信息，比如“XG”、“Firebase" 等
            * @param tag 标签内容
            */
            MSDK_EXPORT_UE static void SetTag(const String &channel, const String &tag);

            /**
            * @brief 删除标签，删除设置过的标签
            *
            * @param channel 渠道信息，比如“XG”、“Firebase" 等
            * @param tag 标签内容
            */
            MSDK_EXPORT_UE static void DeleteTag(const String &channel, const String &tag);

            /**
             * @brief 设置账号，针对不同用户设置不同账号
             *
             * @param channel 渠道信息，比如“XG”、“Firebase" 等
             * @param account 标签内容
             */
            MSDK_EXPORT_UE static void SetAccount(const String &channel, const String &account);

            /**
             * @brief 设置账号，针对不同用户设置不同账号
             *
             * @param channel 渠道信息，比如“XG”、“Firebase" 等
             * @param account 标签内容
             */
            MSDK_EXPORT_UE static void DeleteAccount(const String &channel, const String &account);

            /**
            * @brief 新增本地推送
            * 本地通知的数量是有限制的，最近的本地通知最多只能有64个，超过将被系统忽略
            *
            * @param channel 渠道信息，比如“XG”、“Firebase" 等
            * @param localNotification 本地推送对象
            */
            MSDK_EXPORT_UE static void AddLocalNotification(const String &channel,
                                                            const MSDKLocalNotification &localNotification) {
                MSDKPIX_LOG_DEBUG("", "MSDKLocalNotification begin convert");
                AddLocalNotificationPRV(channel, localNotification.convertToInner());
            }

            /**
            * @brief 清空全部本地推送
            *
            * @param channel 渠道信息，比如“XG”、“Firebase" 等
            */
            MSDK_EXPORT_UE static void ClearLocalNotifications(const String &channel);

            /**
             * @brief 接收到推送的回调
             */
            MSDK_EXPORT_UE static void SetPushReceiveObserver();


#ifdef __APPLE__
            /**
             * @brief 删除指定本地推送
             *
             * @param key 设置通知参数时userInfo指定的key
             */
            static void deleteLocalNotifications(const String &key);

            /**
             * @brief 添加前台可显示的本地推送
             *
             * @param localNotification 本地推送对象
             */
            static void addLocalNotificationAtFront(MSDKLocalNotification localNotification){
                addLocalNotificationAtFrontPRV(localNotification.convertToInner());
            }

            /**
            * @brief 清除图标推送条目
            */
            static void cleanBadgeNumber();
#endif
        };


NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
            class MSDKLocalNotification
            {
            public:
                int type;
                int actionType;
                int iconType;
                int lights;
                int ring;
                int vibrate;
                int styleID;
                int64_t builderID;
                String content;
                String customContent;
                String activity;
                String packageDownloadUrl;
                String packageName;
                String iconRes;
                String date;
                String hour;
                String intent;
                String min;
                String title;
                String url;
                String ringRaw;
                String smallIcon;
                MSDK::InnerLocalNotification convertToInner() const
                {
                    MSDK::InnerLocalNotification notification;
                    MSDKCompatManager::compatConvert(notification, *this);
                    return notification;
                }

                MSDK::MSDKLocalNotification convert() const {
                    MSDK::MSDKLocalNotification notification;
                    notification.type = type;
                    notification.actionType = actionType;
                    notification.iconType = iconType;
                    notification.lights = lights;
                    notification.ring = ring;
                    notification.vibrate = vibrate;
                    notification.styleID = styleID;
                    notification.builderID = builderID;
                    notification.content = content;
                    notification.customContent = customContent;
                    notification.activity = activity;
                    notification.packageDownloadUrl = packageDownloadUrl;
                    notification.packageName = packageName;
                    notification.iconRes = iconRes;
                    notification.date = date;
                    notification.hour = hour;
                    notification.intent = intent;
                    notification.min = min;
                    notification.title = title;
                    notification.url = url;
                    notification.ringRaw = ringRaw;
                    notification.smallIcon = smallIcon;
                    return notification;
                }
            };
#else
#ifdef __APPLE__

            class MSDKLocalNotification
            {
            public:
                /*!
                 *  推送重复发送周期。 1-分钟，2-小时，3-天，4-星期，5-月，6-年，默认是0代表不重复。
                 *  如果设、、置此属性, 那么调度池不会用完释放改推送！需要手动删除通知对象
                 */
                int repeatType;
                /*!本地推送触发的时间*/
                int64_t fireTime;
                /** 角标 */
                int badge;
                /** 推送的内容 */
                String alertBody;
                /** 替换弹框的按钮文字内容（默认为"启动"）*/
                String alertAction;
                /** 自定义参数，可以用来标识推送和增加附加信息 */
                StringMap userInfo;

                MSDKLocalNotification():repeatType(0),fireTime(0),badge(0){
                }

                MSDK::InnerLocalNotification convertToInner() const {
                    MSDK::InnerLocalNotification localNotification;
                    localNotification.repeatType = repeatType;
                    localNotification.fireTime = fireTime;
                    localNotification.badge = badge;
                    localNotification.alertBody = alertBody;
                    localNotification.alertAction = alertAction;
                    localNotification.userInfo = userInfo;

                    return localNotification;
                }

                MSDK::MSDKLocalNotification convert() const {
                    MSDK::MSDKLocalNotification notification;
                    notification.repeatType = repeatType;
                    notification.fireTime = fireTime;
                    notification.badge = badge;
                    notification.alertBody = alertBody;
                    notification.alertAction = alertAction;
                    notification.userInfo = userInfo;

                    return notification;
                }

                AutoParser("com.itop.gcloud.msdk.api.push.MSDKLocalNotification", O(repeatType, fireTime,badge, alertBody,alertAction,userInfo));
            };
#endif

#ifdef ANDROID

            class MSDK_EXPORT MSDKLocalNotification {
            public:
                int type;
                int actionType;
                int iconType;
                int lights;
                int ring;
                int vibrate;
                int styleID;
                int64_t builderID;
                String content;
                String customContent;
                String activity;
                String packageDownloadUrl;
                String packageName;
                String iconRes;
                String date;
                String hour;
                String intent;
                String min;
                String title;
                String url;
                String ringRaw;
                String smallIcon;

                MSDKLocalNotification() : type(0), actionType(0), iconType(0), lights(0), ring(0),
                                          vibrate(0), styleID(0), builderID(0) {
                }

                MSDK::InnerLocalNotification convertToInner() const {
                    MSDK::InnerLocalNotification notification;
                    MSDKCompatManager::compatConvert(notification, *this);
                    return notification;
                }

                MSDK::MSDKLocalNotification convert() const {
                    MSDK::MSDKLocalNotification notification;
                    MSDKCompatManager::compatConvert(notification, *this);
                    return notification;
                }

            AutoParser("com.itop.gcloud.msdk.api.push.MSDKLocalNotification",
                       O(type, actionType, iconType, lights, ring, vibrate,
                         styleID, builderID, content, customContent, activity,
                         packageDownloadUrl, packageName, iconRes, date, hour,
                         intent, min, title, url, ringRaw, smallIcon));
            };

#endif
#endif

            class MSDK_EXPORT MSDKPushRet : public MSDKBaseRet {
            public:
                /** 收到消息类型 -1：未知，0:应用在前台时收到的远程通知，1:应用在后台收收到的远程通知，2:应用在前台时收到的本地通知，3:应用在后台收收到的本地通知**/
                int type;
                /** 收到消息内容*/
                String notification;

                MSDKPushRet(const MSDK::MSDKPushRet &pushRet) : MSDKBaseRet(pushRet) {
                    type = pushRet.type;
                    notification = pushRet.notification;
                }

            AutoParser("com.itop.gcloud.msdk.api.push.MSDKPushRet",
                       A(type, "type"),
                       A(notification, "notification"),
                       A(thirdCode, "ret"),
                       A(thirdMsg, "msg"),
            //           A(extraJson, "extra"),
                       O(retCode, retMsg, methodNameID, extraJson));


            };

            class MSDK_EXPORT MSDKPushObserver {
            public:
                virtual ~MSDKPushObserver() {};

                virtual void OnPushOptNotify(const MSDKBaseRet &baseRet) {};

                virtual void OnReceiveNotification(const MSDKPushRet &pushRet) {};
            };

            class MSDKPushObserverAdapter : public MSDK::MSDKPushObserver {
            public:

                void OnPushOptNotify(const MSDK::MSDKBaseRet &baseRet);

                void OnReceiveNotification(const MSDK::MSDKPushRet &pushRet);

                MSDKSpace::NoSTL::MSDKPushObserver *mObserver = NULL;
            };

            class MSDK_EXPORT MSDKPush {
            private:
                static MSDKPushObserverAdapter mPushObserverAdapter;
            public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
                MSDK_EXPORT_UE static void SetPushObserver(MSDKPushObserver *pushObserver);
#else

                static void SetPushObserver(MSDKPushObserver *pushObserver) {
                    if (!pushObserver) {
                        MSDKPIX_LOG_ERROR("", "MSDKPushObserver cant not be NULL");
                    } else {
                        mPushObserverAdapter.mObserver = pushObserver;
                        MSDK::MSDKPush::SetPushObserver(&mPushObserverAdapter);
                    }
                }

#endif

                /**
                 * @brief 注册指定渠道推送模块，包括注销设备后，重新注册设备的情况
                 *
                 * @param channel 渠道信息，比如“XG”、“Firebase" 等
                 * @param account  用户的帐号（别名）。上报用户的帐号（别名），以便支持按帐号（别名）推送。如果填 NULL，使用登录成功的openID 作为账号（别名）
                 */
                MSDK_EXPORT_UE static void
                RegisterPush(const String &channel, const String &account = "");

                /**
                 * @brief 注销设备,此台设备不接收推送
                 *
                 * @param channel 渠道信息，比如“XG”、“Firebase" 等
                 */
                MSDK_EXPORT_UE static void UnregisterPush(const String &channel);

                /**
                 * @brief 设置标签，针对不同用户设置不同标签
                 *
                 * @param channel 渠道信息，比如“XG”、“Firebase" 等
                 * @param tag 标签内容
                 */
                MSDK_EXPORT_UE static void SetTag(const String &channel, const String &tag);

                /**
                 * @brief 删除标签，删除设置过的标签
                 *
                 * @param channel 渠道信息，比如“XG”、“Firebase" 等
                 * @param tag 标签内容
                 */
                MSDK_EXPORT_UE static void DeleteTag(const String &channel, const String &tag);

                /**
                 * @brief 设置账号，针对不同用户设置不同账号
                 *
                 * @param channel 渠道信息，比如“XG”、“Firebase" 等
                 * @param account 标签内容
                 */
                MSDK_EXPORT_UE static void SetAccount(const String &channel, const String &account);

                /**
                 * @brief 设置账号，针对不同用户设置不同账号
                 *
                 * @param channel 渠道信息，比如“XG”、“Firebase" 等
                 * @param account 标签内容
                 */
                MSDK_EXPORT_UE static void
                DeleteAccount(const String &channel, const String &account);

                /**
                 * @brief 新增本地推送
                 * 本地通知的数量是有限制的，最近的本地通知最多只能有64个，超过将被系统忽略
                 *
                 * @param channel 渠道信息，比如“XG”、“Firebase" 等
                 * @param localNotification 本地推送对象
                 */
                MSDK_EXPORT_UE static void AddLocalNotification(const String &channel,
                                                                const MSDKLocalNotification &localNotification);

                /**
                 * @brief 清空全部本地推送
                 *
                 * @param channel 渠道信息，比如“XG”、“Firebase" 等
                 */
                MSDK_EXPORT_UE static void ClearLocalNotifications(const String &channel);

                /**
                 * @brief 接收到推送的回调
                 */
                MSDK_EXPORT_UE static void SetPushReceiveObserver();


#ifdef __APPLE__
                /**
                 * @brief 删除指定本地推送
                 *
                 * @param key 设置通知参数时userInfo指定的key
                 */
                static void deleteLocalNotifications(const String &key);

                /**
                 * @brief 添加前台可显示的本地推送
                 *
                 * @param localNotification 本地推送对象
                 */
                static void addLocalNotificationAtFront(MSDKLocalNotification localNotification);

                /**
                 * @brief 清除图标推送条目
                 */
                static void cleanBadgeNumber();
#endif
            };

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDK_PUSH_H */
