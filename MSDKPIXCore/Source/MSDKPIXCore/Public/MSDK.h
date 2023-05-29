/*!
 * @Module MSDK
 *
 * @Header  MSDK.h
 * @Author  developer
 * @Date  2018/3/20
 * @Abstract
 * MSDK 平台C++ 初始化、 C++ 层通用的生命周期回调以及函数唯一标识符管理
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_PLATFORM_H
#define MSDK_PLATFORM_H

#include "MSDKLifeCycleAble.h"
#include "MSDKCompatLayer.h"
#include "MSDKDefine.h"

#define GCLOUD_VERSION_MSDK_CORE "GCLOUD_VERSION_MSDK_CORE_5.2.000"

#ifdef ANDROID
#include <jni.h>
#endif

NS_MSDK_BEGIN

typedef void (*OnHandleJSMessage)(int method, String args);

class MSDK_EXPORT MSDKInitObserver
{

public:
    //新增一个虚析构函数 不然 UE4 报错
    virtual ~MSDKInitObserver(){};

    // MSDK初始化回调
    virtual void OnInitCompleteNotify(const MSDKBaseRet &baseRet) {};
};

class MSDK_EXPORT MSDK : public MSDKLifeCycleAble, public MSDKSingleton<MSDK>
{
    friend class MSDKSingleton<MSDK>;

private:
    MSDK() {
        lastResumeTime = 0;
        logFileConditionCount = 0;
        isSDKInfoInit = false;
    };
    virtual ~MSDK();
    static std::string mSeqIdPrefix;
    static unsigned long mSeqIdPrimaryKey;
    static std::string mCurSeqId;
    static std::string mGameId;
    int64_t lastResumeTime;     // 上一次唤醒时间
    int logFileConditionCount;  // 满足条件的(3s内)前后台切换的次数计算
    void InitModule();     // 模块初始化
    void HandleLogFile(); // 调试日志文件处理
    void InitSDKInfos(); // Bugly 组件上报设置
    bool isSDKInfoInit; // 判断 Bugly 组件上报是否已经完成初始化
public:
//JavaVM 是Android JNI使用，iOS这里定义一个，保证编译通过
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
#define JavaVM void
#else
#ifdef __APPLE__
#define JavaVM void
#endif
#endif

    void Initialize(JavaVM *vm);

    virtual void OnCreate();

    virtual void OnResume();

    virtual void OnPause();

    static std::string CreateSequenceId();

    static void ShowTestInfoInAlert();   //SDK初始化时，如果是测试环境，则展示Alert提示

    static void CheckSequenceKeys();   //CheckSequenceKeys

    static void RegisterJSMessageReceivers(String module, OnHandleJSMessage handler);

    static void SetMSDKInitObserver(MSDKInitObserver *initObserver);
};

NS_MSDK_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif

#endif /* MSDK_PLATFORM_H */
