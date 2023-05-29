/*!
 * @Module MSDK
 *
 * @Header  MSDKLifeCycleManager.h
 * @Author  developer
 * @Date 2018/4/11
 * @Abstract
 * 生命周期的管理类声明，所有注册监控生命周期的类都被此 Manager 管理
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_LIFECYCLE_MANAGER_H
#define MSDK_LIFECYCLE_MANAGER_H

#include "MSDKMacros.h"
#include "MSDKSingleton.h"
#include "MSDKLifeCycleAble.h"
#include "MSDKObserverManager.h"


NS_MSDK_BEGIN

class MSDKLifeCycleAble;

class MSDKLifeCycleManager : public MSDKSingleton<MSDKLifeCycleManager>
{
private:
    static MSDKObserverManager mObserverManager;

public:
    static void AddLifeCycleObserver(MSDKLifeCycleAble *lifecycle);

    static void RemoveLifeCycleObserver(MSDKLifeCycleAble *lifecycle);

    static void ExecOnCreate();

    static void ExecOnStart();

    static void ExecOnResume();

    static void ExecOnPause();

    static void ExecOnStop();
};

NS_MSDK_END
#endif //MSDK_LIFECYCLE_MANAGER_H
