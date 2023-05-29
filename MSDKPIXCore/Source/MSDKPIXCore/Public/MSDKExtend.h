/*!
 * @Module MSDK
 *
 * @Header  MSDKExtend.h
 * @Author  developer
 * @Version 5.0.0
 * @date 2019/3/8
 * @abstract
 * Extend模块对外接口声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_EXTEND_H
#define MSDK_EXTEND_H

#include "MSDKDefine.h"

#if MSDK_ENGINE_UE4
#include "Async/Async.h"
#endif

NS_MSDK_BEGIN

class MSDK_EXPORT MSDKExtendRet : public MSDKBaseRet
{
public:
    MSDKExtendRet()
    {
    }

    MSDKExtendRet(int retCode) : MSDKBaseRet(retCode)
    {

    }
    //标记是哪个渠道的回调
    std::string channel;
    //标记是Extend插件中哪个方法回调回来的
    std::string extendMethodName;


AutoParser("com.itop.gcloud.msdk.api.extend.MSDKExtendRet",
           A(extendMethodName, "extend_method_name"),
           A(thirdCode, "ret"), A(thirdMsg, "msg"),
           O(retCode, retMsg, methodNameID, extraJson, channel));

};

class MSDK_EXPORT MSDKExtendObserver
{
public:
    virtual ~MSDKExtendObserver() {};

    virtual void OnExtendNotify(const MSDKExtendRet &extendRet) {};
};


class MSDK_EXPORT MSDKExtend
{
private :
    static void ExtendRetObserver(const InnerExtendRet &extendRet, const char *seqID)
    {
        MSDKExtendRet *pRet = new MSDKExtendRet();
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerExtendRet to MSDKExtendRet start");
        MSDKCompatManager::compatConvert(*pRet, extendRet);
        MSDKPIX_LOG_DEBUG(seqID, "convert InnerExtendRet to MSDKExtendRet finish then will notify user");
        if (mExtendObserver)
        {
#if MSDK_ENGINE_UE4
            AsyncTask(ENamedThreads::GameThread, [pRet, seqID]() {
                MSDKPIX_LOG_DEBUG(seqID, "Async Task In UE4 ExtendRetObserver");
                mExtendObserver->OnExtendNotify(*pRet);
                delete pRet;
            });
#else
            mExtendObserver->OnExtendNotify(*pRet);
            delete pRet;
#endif
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "extend observer is null");
            delete pRet;
        }
    }

    static MSDKExtendObserver *mExtendObserver;

    ~MSDKExtend();

	static void SetPRVExtendObserver(
            typename T<InnerExtendRet>::InnerRetCallback baseRetObserver);

public:

#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
	MSDK_EXPORT_UE static void SetExtendObserver(MSDKExtendObserver *extendObserver);
#else
	static void SetExtendObserver(MSDKExtendObserver *extendObserver)
    {
        if (!extendObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKExtendObserver cant not be NULL");
        }
        else
        {
            mExtendObserver = extendObserver;
            SetPRVExtendObserver(ExtendRetObserver);
        }
    }
#endif

	MSDK_EXPORT_UE static String Invoke(const String& channel, const String& extendMethodName, const String& paramsJson);

};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

class MSDK_EXPORT MSDKExtendRet : public MSDKBaseRet
{
public:
    MSDKExtendRet()
    {
    }
    
    MSDKExtendRet(int retCode) : MSDKBaseRet(retCode)
    {
        
    }
    //标记是哪个渠道的回调
    String channel;
    //标记是Extend插件中哪个方法回调回来的
    String extendMethodName;
    
    MSDKExtendRet(const MSDK::MSDKExtendRet &extendRet) : MSDKBaseRet(extendRet) {
        channel = extendRet.channel;
        extendMethodName = extendRet.extendMethodName;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.extend.MSDKExtendRet",
               A(extendMethodName, "extend_method_name"),
               A(thirdCode, "ret"), A(thirdMsg, "msg"),
               O(retCode, retMsg, methodNameID, extraJson, channel));
};

class MSDK_EXPORT MSDKExtendObserver
{
public:
    virtual ~MSDKExtendObserver() {};
    
    virtual void OnExtendNotify(const MSDKExtendRet &extendRet) {};
};

class MSDKExtendObserverAdapter : public MSDK::MSDKExtendObserver {
public:
    void OnExtendNotify(const MSDK::MSDKExtendRet &extendRet);
    MSDKSpace::NoSTL::MSDKExtendObserver *mObserver = NULL;
};

class MSDK_EXPORT MSDKExtend
{
private:
    static MSDKExtendObserverAdapter mExtendObserverAdapter;
public:
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    MSDK_EXPORT_UE static void SetExtendObserver(MSDKExtendObserver *extendObserver);
#else
    static void SetExtendObserver(MSDKExtendObserver *extendObserver)
    {
        if (!extendObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKExtendObserver cant not be NULL");
        }
        else
        {
            mExtendObserverAdapter.mObserver = extendObserver;
            MSDK::MSDKExtend::SetExtendObserver(&mExtendObserverAdapter);
        }
    }
#endif
    
    MSDK_EXPORT_UE static String Invoke(const String& channel, const String& extendMethodName, const String& paramsJson);

};
    

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif //MSDK_EXTEND_H
