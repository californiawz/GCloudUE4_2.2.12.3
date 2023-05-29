/*!
 * @Module MSDK
 *
 * @Header  MSDKLBS.h
 * @Author  developer
 * @date 2019/5/14
 * @abstract
 * 获取位置、附近玩家和 IP 信息，以及清除位置
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */


#ifndef MSDK_LBS_H
#define MSDK_LBS_H

#include "MSDKDefine.h"
#include "MSDKFriend.h"

#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif

NS_MSDK_BEGIN

// MSDK LBS 定位结果
        class MSDK_EXPORT MSDKLBSLocationRet : public MSDKBaseRet {
        public:
            // 经度
            double longitude;

            // 纬度
            double latitude;

            MSDKLBSLocationRet() : MSDKBaseRet(), longitude(0.0), latitude(0.0) {}

            MSDKLBSLocationRet(int retCode) : MSDKBaseRet(retCode), longitude(0.0), latitude(0.0) {}

        AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSLocationRet",
                   A(thirdCode, "ret"), A(thirdMsg, "msg"),
                   O(longitude, latitude, retCode, retMsg, methodNameID, extraJson));

        };

// 附近用户信息
        class MSDK_EXPORT MSDKLBSPersonInfo : public MSDKPersonInfo {
        public:
            // 该附近用户距离当前用户的距离
            double distance;

            // 是否为好友，-1 未知，0 否，1 是
            int isFriend;

            // 设置位置的时间戳
            int64_t timestamp;


        AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSPersonInfo",
                   A(pictureUrl, "picture_url"), A(userName, "user_name"),
                   O(distance, isFriend, timestamp, gender, openid, language, country, province,
                     city));

        };

// MSDK LBS 获取附近用户返回结果
        class MSDK_EXPORT MSDKLBSRelationRet : public MSDKBaseRet {
        public:
            // 是否降级处理
            std::string isLost;
            // 附近用户列表
            std::vector<MSDKLBSPersonInfo> personList;

            MSDKLBSRelationRet() : MSDKBaseRet() {}

            MSDKLBSRelationRet(int retCode) : MSDKBaseRet(retCode) {}


        AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSRelationRet",
                   A(personList, "personList"), A(isLost, "is_lost"),
                   A(thirdCode, "ret"), A(thirdMsg, "msg"),
                   O(retCode, retMsg, methodNameID, extraJson));

        };

        class MSDK_EXPORT MSDKLBSIPInfoRet : public MSDKBaseRet {
        public:
            // 国家
            std::string country;
            int countryCode;

            // Province
            std::string province;
            int provinceCode;

            // City
            std::string city;
            int cityCode;

            // 时间戳
            int64_t timestamp;

            // 查询方式 is_query_by_request_header
            bool isByHeader;

            MSDKLBSIPInfoRet() : MSDKBaseRet() {}

            MSDKLBSIPInfoRet(int retCode) : MSDKBaseRet(retCode) {}


        AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSIPInfoRet",
                   A(isByHeader, "is_query_by_request_header"),
                   A(thirdCode, "ret"), A(thirdMsg, "msg"),
                   A(countryCode, "country_no"), A(provinceCode, "province_no"),
                   A(cityCode, "city_no"),
                   O(country, province, city, timestamp, retCode, retMsg, methodNameID, extraJson));

        };

        class MSDK_EXPORT MSDKLBSObserver {
        public:
            //新增一个虚析构函数 不然 UE4 报错
            virtual ~MSDKLBSObserver() {};

            // 获取位置信息回调
            virtual void OnLBSLocationRetNotify(const MSDKLBSLocationRet &locationRet) {};

            // 获取附近的人回调
            virtual void OnLBSRelationRetNotify(const MSDKLBSRelationRet &relationRet) {};

            // 获取 IP 信息回调
            virtual void OnLBSIPInfoRetNotify(const MSDKLBSIPInfoRet &ipInfoRet) {};

            // 基础回调：清除位置信息回调
            virtual void OnLBSBaseRetNotify(const MSDKBaseRet &baseRet) {};
        };


        class MSDK_EXPORT MSDKLBS {
        private:

            static MSDKLBSObserver *mLBSObserver;

            static void
            LocationRetObserver(const InnerLBSLocationRet &locationRet, const char *seqID) {
                MSDKLBSLocationRet *pRet = new MSDKLBSLocationRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerLBSLocationRet to MSDKLBSLocationRet start");
                MSDKCompatManager::compatConvert(*pRet, locationRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerLBSLocationRet to MSDKLBSLocationRet finish then will notify user");
                if (mLBSObserver) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                       MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 LBS LocationRetObserver");
                       mLBSObserver->OnLBSLocationRetNotify(*pRet);
                       delete pRet;
                   });
#else
                    mLBSObserver->OnLBSLocationRetNotify(*pRet);
                    delete pRet;
#endif
                } else {
                    MSDKPIX_LOG_ERROR(seqID, "LBS observer is null");
                    delete pRet;
                }
            }

            static void
            RelationRetObserver(const InnerLBSRelationRet &lbsRelationRet, const char *seqID) {
                MSDKLBSRelationRet *pRet = new MSDKLBSRelationRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerLBSRelationRet to MSDKLBSRelationRet start");
                MSDKCompatManager::compatConvert(*pRet, lbsRelationRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerLBSRelationRet to MSDKLBSRelationRet finish then will notify user");
                if (mLBSObserver) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                       MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 LBS RelationRetObserver");
                       mLBSObserver->OnLBSRelationRetNotify(*pRet);
                       delete pRet;
                   });
#else
                    mLBSObserver->OnLBSRelationRetNotify(*pRet);
                    delete pRet;
#endif
                } else {
                    MSDKPIX_LOG_ERROR(seqID, "LBS observer is null");
                    delete pRet;
                }
            }

            static void
            IPInfoRetObserver(const InnerLBSIPInfoRet &lbsIPInfoRet, const char *seqID) {
                MSDKLBSIPInfoRet *pRet = new MSDKLBSIPInfoRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerLBSIPInfoRet to MSDKLBSIPInfoRet start");
                MSDKCompatManager::compatConvert(*pRet, lbsIPInfoRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerLBSIPInfoRet to MSDKLBSIPInfoRet finish then will notify user");
                if (mLBSObserver) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                        MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 LBS IPInfoRetObserver");
                        mLBSObserver->OnLBSIPInfoRetNotify(*pRet);
                        delete pRet;
                    });
#else
                    mLBSObserver->OnLBSIPInfoRetNotify(*pRet);
                    delete pRet;
#endif
                } else {
                    MSDKPIX_LOG_ERROR(seqID, "LBS observer is null");
                    delete pRet;
                }
            }

            static void BaseRetObserver(const InnerBaseRet &baseRet, const char *seqID) {
                MSDKBaseRet *pRet = new MSDKBaseRet();
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet start");
                MSDKCompatManager::compatConvert(*pRet, baseRet);
                MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet finish then will notify user");
                if (mLBSObserver) {
#if MSDK_ENGINE_UE4
                    AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                        MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 LBS BaseRetObserver");
                        mLBSObserver->OnLBSBaseRetNotify(*pRet);
                        delete pRet;
                    });
#else
                    mLBSObserver->OnLBSBaseRetNotify(*pRet);
                    delete pRet;
#endif
                } else {
                    MSDKPIX_LOG_ERROR(seqID, "LBS observer is null");
                    delete pRet;
                }
            }

            ~MSDKLBS();

            static void SetPRVLBSObserver(
                    typename T<InnerLBSLocationRet>::InnerRetCallback lbsLocationRetObserver,
                    typename T<InnerLBSRelationRet>::InnerRetCallback lbsRelationRetObserver,
                    typename T<InnerLBSIPInfoRet>::InnerRetCallback lbsIPInfoRetObserver,
                    typename T<InnerBaseRet>::InnerRetCallback lbsBaseRetObserver);

        public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
            MSDK_EXPORT_UE static void SetLBSObserver(MSDKLBSObserver *lbsObserver);
#else

            static void SetLBSObserver(MSDKLBSObserver *lbsObserver) {
                if (!lbsObserver) {
                    MSDKPIX_LOG_ERROR("", "MSDKLBSObserver can not be null");
                } else {
                    mLBSObserver = lbsObserver;
                    SetPRVLBSObserver(LocationRetObserver, RelationRetObserver, IPInfoRetObserver,
                                      BaseRetObserver);
                }
            }

#endif

            /**
            * setLocation
            * 获取用户定位并设置位置信息
            * 通过回调 OnLBSLocationRetNotify 返回
            */
            MSDK_EXPORT_UE static void GetLocation();

            /**
            * ClearLocation
            * 清除位置信息
            * 通过回调 OnLBSBaseRetNotify 返回
            */
            MSDK_EXPORT_UE static void ClearLocation();

            /**
            * GetNearby
            * 获取用户的附近好友
            * 通过回调 OnLBSRelationRetNotify 返回
            */
            MSDK_EXPORT_UE static void GetNearby();

            /**
            * IP2Country
            * 查询 IP 对应的国家
            * 通过回调 OnLBSIPInfoRetNotify 返回
            */
            MSDK_EXPORT_UE static void GetIPInfo();

        };

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

            // MSDK LBS 定位结果
            class MSDK_EXPORT MSDKLBSLocationRet : public MSDKBaseRet {
            public:
                // 经度
                double longitude;

                // 纬度
                double latitude;

                MSDKLBSLocationRet() : MSDKBaseRet(), longitude(0.0), latitude(0.0) {}

                MSDKLBSLocationRet(int retCode) : MSDKBaseRet(retCode), longitude(0.0),
                                                  latitude(0.0) {}

                MSDKLBSLocationRet(const MSDK::MSDKLBSLocationRet &locationRet) : MSDKBaseRet(
                        locationRet) {
                    longitude = locationRet.longitude;
                    latitude = locationRet.latitude;
                }

            AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSLocationRet",
                       A(thirdCode, "ret"), A(thirdMsg, "msg"),
                       O(longitude, latitude, retCode, retMsg, methodNameID, extraJson));
            };

            // 附近用户信息
            class MSDK_EXPORT MSDKLBSPersonInfo : public MSDKPersonInfo {
            public:
                // 该附近用户距离当前用户的距离
                double distance;

                // 是否为好友，-1 未知，0 否，1 是
                int isFriend;

                // 设置位置的时间戳
                int64_t timestamp;

                MSDKLBSPersonInfo(const MSDK::MSDKLBSPersonInfo &personInfo) : MSDKPersonInfo(
                        personInfo) {
                    distance = personInfo.distance;
                    isFriend = personInfo.isFriend;
                    timestamp = personInfo.timestamp;
                }

            AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSPersonInfo",
                       A(pictureUrl, "picture_url"), A(userName, "user_name"),
                       O(distance, isFriend, timestamp, gender, openid, language, country, province,
                         city));

            };

            // MSDK LBS 获取附近用户返回结果
            class MSDK_EXPORT MSDKLBSRelationRet : public MSDKBaseRet {
            public:
                // 是否降级处理
                String isLost;
                // 附近用户列表
                Vector<MSDKLBSPersonInfo> personList;

                MSDKLBSRelationRet() : MSDKBaseRet() {}

                MSDKLBSRelationRet(int retCode) : MSDKBaseRet(retCode) {}

                MSDKLBSRelationRet(const MSDK::MSDKLBSRelationRet &relationRet) : MSDKBaseRet(
                        relationRet) {
                    isLost = relationRet.isLost;

                    personList.clear();
                    std::vector<MSDK::MSDKLBSPersonInfo>::const_iterator it;
                    for (it = relationRet.personList.begin();
                         it != relationRet.personList.end(); ++it) {
                        MSDKLBSPersonInfo info = MSDKLBSPersonInfo(*it);
                        personList.push_back(info);
                    }
                }

            AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSRelationRet",
                       A(personList, "personList"), A(isLost, "is_lost"),
                       A(thirdCode, "ret"), A(thirdMsg, "msg"),
                       O(retCode, retMsg, methodNameID, extraJson));

            };

            class MSDK_EXPORT MSDKLBSIPInfoRet : public MSDKBaseRet {
            public:
                // 国家
                String country;
                int countryCode;

                // Province
                String province;
                int provinceCode;

                // City
                String city;
                int cityCode;

                // 时间戳
                int64_t timestamp;

                // 查询方式 is_query_by_request_header
                bool isByHeader;

                MSDKLBSIPInfoRet() : MSDKBaseRet() {}

                MSDKLBSIPInfoRet(int retCode) : MSDKBaseRet(retCode) {}

                MSDKLBSIPInfoRet(const MSDK::MSDKLBSIPInfoRet &ipInfoRet) : MSDKBaseRet(ipInfoRet) {
                    country = ipInfoRet.country;
                    timestamp = ipInfoRet.timestamp;
                    isByHeader = ipInfoRet.isByHeader;
                }

            AutoParser("com.itop.gcloud.msdk.api.lbs.MSDKLBSIPInfoRet",
                       A(isByHeader, "is_query_by_request_header"),
                       A(thirdCode, "ret"), A(thirdMsg, "msg"),
                       A(countryCode, "country_no"), A(provinceCode, "province_no"), A(cityCode, "city_no"),
                       O(country, province, city, timestamp, retCode, retMsg, methodNameID, extraJson));

            };

            class MSDK_EXPORT MSDKLBSObserver {
            public:
                //新增一个虚析构函数 不然 UE4 报错
                virtual ~MSDKLBSObserver() {};

                // 获取位置信息回调
                virtual void OnLBSLocationRetNotify(const MSDKLBSLocationRet &locationRet) {};

                // 获取附近的人回调
                virtual void OnLBSRelationRetNotify(const MSDKLBSRelationRet &relationRet) {};

                // 获取 IP 信息回调
                virtual void OnLBSIPInfoRetNotify(const MSDKLBSIPInfoRet &ipInfoRet) {};

                // 基础回调：清除位置信息回调
                virtual void OnLBSBaseRetNotify(const MSDKBaseRet &baseRet) {};
            };

            class MSDKLBSObserverAdapter : public MSDK::MSDKLBSObserver {
            public:
                // 获取位置信息回调
                void OnLBSLocationRetNotify(const MSDK::MSDKLBSLocationRet &locationRet);

                // 获取附近的人回调
                void OnLBSRelationRetNotify(const MSDK::MSDKLBSRelationRet &relationRet);

                // 获取 IP 信息回调
                void OnLBSIPInfoRetNotify(const MSDK::MSDKLBSIPInfoRet &ipInfoRet);

                // 基础回调：清除位置信息回调
                void OnLBSBaseRetNotify(const MSDK::MSDKBaseRet &baseRet);

                MSDKSpace::NoSTL::MSDKLBSObserver *mObserver = NULL;
            };

            class MSDK_EXPORT MSDKLBS {
            private:
                static MSDKLBSObserverAdapter mLBSObserverAdapter;
            public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
                MSDK_EXPORT_UE static void SetLBSObserver(MSDKLBSObserver *lbsObserver);
#else

                static void SetLBSObserver(MSDKLBSObserver *lbsObserver) {
                    if (!lbsObserver) {
                        MSDKPIX_LOG_ERROR("", "MSDKLBSObserver can not be null");
                    } else {
                        mLBSObserverAdapter.mObserver = lbsObserver;
                        MSDK::MSDKLBS::SetLBSObserver(&mLBSObserverAdapter);
                    }
                }

#endif

                /**
                 * setLocation
                 * 获取用户定位并设置位置信息
                 * 通过回调 OnLBSLocationRetNotify 返回
                 */
                MSDK_EXPORT_UE static void GetLocation();

                /**
                 * ClearLocation
                 * 清除位置信息
                 * 通过回调 OnLBSBaseRetNotify 返回
                 */
                MSDK_EXPORT_UE static void ClearLocation();

                /**
                 * GetNearby
                 * 获取用户的附近好友
                 * 通过回调 OnLBSRelationRetNotify 返回
                 */
                MSDK_EXPORT_UE static void GetNearby();

                /**
                 * IP2Country
                 * 查询 IP 对应的国家
                 * 通过回调 OnLBSIPInfoRetNotify 返回
                 */
                MSDK_EXPORT_UE static void GetIPInfo();
            };

NS_MSDK_SPACE_NO_STL_END


#endif //MSDK_LBS_H
