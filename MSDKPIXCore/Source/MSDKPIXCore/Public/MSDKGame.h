/*!
 * @Module MSDK
 *
 * @Header  MSDKGame.h
 * @Author  developer
 * @date 2018/4/16
 * @abstract
 * 游戏排行榜，用于展示游戏进度、成就排行榜以及设置分数
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_GAME_H
#define MSDK_GAME_H

#include <stdio.h>
#include "MSDKDefine.h"

#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif
NS_MSDK_BEGIN

class MSDK_EXPORT MSDKGameObserver
{
public:
    virtual ~MSDKGameObserver() {};
    virtual void OnBaseRetNotify(const MSDKBaseRet &baseRet) {};
};

class MSDK_EXPORT MSDKGame
{
private:

    static void BaseRetObserver(const InnerBaseRet &baseRet, const char *seqID)
    {
        MSDKBaseRet *pRet = new MSDKBaseRet();
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet start");
        MSDKCompatManager::compatConvert(*pRet, baseRet);
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerBaseRet to MSDKBaseRet finish then will notify user");
        if (mGameObserver)
        {
#if MSDK_ENGINE_UE4
            AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 Game BaseRetObserver");
                mGameObserver->OnBaseRetNotify(*pRet);
                delete pRet;
            });
#else
            mGameObserver->OnBaseRetNotify(*pRet);
            delete pRet;
#endif
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "game observer is null");
            delete pRet;
        }

    }

    static MSDKGameObserver *mGameObserver;

    ~MSDKGame();

    static void SetPRVGameObserver(
            typename T<InnerBaseRet>::InnerRetCallback baseRetObserver);

public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
	MSDK_EXPORT_UE static void SetGameObserver(MSDKGameObserver *gameObserver);
#else
	static void SetGameObserver(MSDKGameObserver *gameObserver)
    {
        if (!gameObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKGameObserver can not be NULL");
        }
        else
        {
            mGameObserver = gameObserver;
            SetPRVGameObserver(BaseRetObserver);
        }
    }
#endif

    /**
     * 初始化排行榜功能
     * 
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void Setup(const String &channel = "", const String &extraJson = "");

    /**
     * 展示成就界面
     *
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void ShowAchievement(const String &channel = "", const String &extraJson = "");

    /**
     * 展示排行榜界面
     *
     * @param board   对应后台创建的排行榜信息
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void ShowLeaderBoard(const String &board, const String &channel = "",
                                const String &extraJson = "");

    /**
     * 设置分数
     *
     * @param board  对应后台创建的排行榜信息
     * @param score  需要设置的分数
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void SetScore(const String &board, int score, const String &channel = "",
                         const String &extraJson = "");

    /**
     * 解锁指定的成就
     *
     * @param achieve 成就名称
     * @param count 数值
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
	MSDK_EXPORT_UE static void UnlockAchievement(const String &achieve, double count, const String &channel = "",
                                  const String &extraJson = "");

};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

class MSDK_EXPORT MSDKGameObserver
{
public:
    virtual ~MSDKGameObserver() {};
    virtual void OnBaseRetNotify(const MSDKBaseRet &baseRet) {};
};

class MSDKGameObserverAdapter : public MSDK::MSDKGameObserver
{
public:
    void OnBaseRetNotify(const MSDK::MSDKBaseRet &baseRet);
    MSDKSpace::NoSTL::MSDKGameObserver *mObserver = NULL;
};

class MSDK_EXPORT MSDKGame
{
private:
    static MSDKGameObserverAdapter mGameObserverAdapter;
public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    MSDK_EXPORT_UE static void SetGameObserver(MSDKGameObserver *gameObserver);
#else
    static void SetGameObserver(MSDKGameObserver *gameObserver)
    {
        if (!gameObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKGameObserver can not be NULL");
        }
        else
        {
            mGameObserverAdapter.mObserver = gameObserver;
            MSDK::MSDKGame::SetGameObserver(&mGameObserverAdapter);
        }
    }
#endif
    
    /**
     * 初始化排行榜功能
     *
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void Setup(const String &channel = "", const String &extraJson = "");
    
    /**
     * 展示成就界面
     *
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void ShowAchievement(const String &channel = "", const String &extraJson = "");
    
    /**
     * 展示排行榜界面
     *
     * @param board   对应后台创建的排行榜信息
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void ShowLeaderBoard(const String &board, const String &channel = "",
                                               const String &extraJson = "");
    
    /**
     * 设置分数
     *
     * @param board  对应后台创建的排行榜信息
     * @param score  需要设置的分数
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void SetScore(const String &board, int score, const String &channel = "",
                                        const String &extraJson = "");
    
    /**
     * 解锁指定的成就
     *
     * @param achieve 成就名称
     * @param count 数值
     * @param channel 渠道信息，比如 “Google”
     * @param extraJson 扩展字段，默认为空
     */
    MSDK_EXPORT_UE static void UnlockAchievement(const String &achieve, double count, const String &channel = "",
                                                 const String &extraJson = "");


};

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif //MSDK_GAME_H
