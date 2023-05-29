/*!
 * @Module MSDK
 *
 * @Header  MSDKLifeCycleAble.h
 * @Author  developer
 * @Date 2018/4/11
 * @Abstract
 * 继承此类就可以实现监控应用生命周期管理的声明，一般监控应用退出到后台，打开等事件
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_LIFECYCLE_ABLE_H
#define MSDK_LIFECYCLE_ABLE_H

#include "MSDKMacros.h"
#include "MSDKLifeCycleManager.h"
#include "MSDKObserverManager.h"
NS_MSDK_BEGIN

#define LIFE_CYCLE_CREATE "onCreate"
#define LIFE_CYCLE_RESUME "onResume"
#define LIFE_CYCLE_START  "onStart"
#define LIFE_CYCLE_PAUSE  "onPause"
#define LIFE_CYCLE_STOP   "onStop"

class MSDKLifeCycleAble : public IObserver
{
public:

    MSDKLifeCycleAble();

    virtual ~MSDKLifeCycleAble();

    virtual void OnCreate();

    virtual void OnStart();

    virtual void OnResume() = 0;

    virtual void OnPause() = 0;

    virtual void OnStop();

    virtual void Change(const std::string &tag);

};

NS_MSDK_END
#endif //MSDK_LIFECYCLE_ABLE_H
