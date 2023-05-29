/*!
 * @Module MSDK
 *
 * @Header  MSDKGameManager.h
 * @Author  developer
 * @date 2018/3/20
 * @abstract
 * 应用崩溃上报声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_CRASH_H
#define MSDK_CRASH_H

#include "MSDKDefine.h"

NS_MSDK_BEGIN


class MSDK_EXPORT MSDKCrashRet : public MSDKBaseRet
{
public:
    int maxDataLen;
    char *data;

	AutoParser("com.itop.gcloud.msdk.api.crash.MSDKCrashRet", A(thirdCode, "ret"),
		A(thirdMsg, "msg"), A(extraJson, "extra"), O(retCode, retMsg, methodNameID),
		O(methodNameID));

};


class MSDK_EXPORT MSDKCrashObserver
{
public:
    //新增一个虚析构函数 不然 UE4 报错
    virtual ~MSDKCrashObserver(){};

    virtual long OnCrashExtraDataNotify(MSDKCrashRet &crashRet){
        return 0;
    };

    virtual const char* OnCrashExtraMessageNotify(){
        return NULL;
    };
};


class MSDK_EXPORT MSDKCrash
{
    
private :
    static void CrashDataObserver(const InnerCrashRet &crashRet, const char *seqID)
    {
        MSDKPIX_LOG_DEBUG(seqID, "CrashDataObserver");
        MSDKCrashRet ret;
        ret.maxDataLen = crashRet.maxDataLen;
        if (mCrashObserver)
        {
            long numberOfData = mCrashObserver->OnCrashExtraDataNotify(ret);
            int copyDataLen = 0;
            if (numberOfData == 0) {
                memcpy((void *)(crashRet.dataLen), &copyDataLen, sizeof(int));
                return;
            }
            copyDataLen = numberOfData < crashRet.maxDataLen ? (int)numberOfData : crashRet.maxDataLen;
            memcpy((void *)crashRet.data, ret.data, copyDataLen);
            memcpy((void *)(crashRet.dataLen), &copyDataLen, sizeof(int));
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "CrashDataObserver observer is null");
        }
    };
    static void CrashMessageObserver(const InnerCrashRet &crashRet, const char *seqID)
    {
        MSDKPIX_LOG_DEBUG(seqID, "CrashMessageObserver");
        if (mCrashObserver)
        {
            const char *message = mCrashObserver->OnCrashExtraMessageNotify();
            if (message == NULL) return;
            long dataLen = strlen(message) < crashRet.maxDataLen ? strlen(message) : crashRet.maxDataLen;
            if (dataLen == 0) {
                return;
            }
            memcpy((void *)crashRet.data, message, dataLen);
        }
        else
        {
            MSDKPIX_LOG_ERROR(seqID, "CrashMessageObserver observer is null");
        }
    };
    static MSDKCrashObserver *mCrashObserver;
    
    ~MSDKCrash();
    
	static void SetPRVCrashObserver(T<InnerCrashRet>::InnerRetCallback crashObserver);
	static void SetExtraMessageCrashObserver(T<InnerCrashRet>::InnerRetCallback crashObserver);
	MSDK_EXPORT_UE static void ReportExceptionPRV(int type, const String &exceptionName, const String &exceptionMsg, const String &exceptionStack, Vector<KVPair> &extInfo);

public:
    
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
	MSDK_EXPORT_UE static void SetCrashObserver(MSDKCrashObserver *crashObserver);
#else
	static void SetCrashObserver(MSDKCrashObserver *crashObserver)
    {
        if (!crashObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKCrashObserver cant not be NULL");
        }
        else
        {
            mCrashObserver = crashObserver;
            SetPRVCrashObserver(CrashDataObserver);
            SetExtraMessageCrashObserver(CrashMessageObserver);
        }
    }
#endif

    /**
     *  自定义日志打印接口,用于记录一些关键的业务调试信息, 可以更全面地反应APP发生崩溃或异常的上下文环境.
     *
     *  @param level  日志级别，0-silent, 1-error,2-warning，3-inifo，4-debug，5-verbose
     *  @param tag    日志模块分类
     *  @param log 日志内容
     */
	MSDK_EXPORT_UE static void LogInfo(int level, const String &tag, const String &log);

    /**
     * 设置关键数据，随崩溃信息上报
     * @param key 键值
     * @param value 键值对
     */
	MSDK_EXPORT_UE static void SetUserValue(const String &key, const String &value);

    /**
     * 设置用户 ID
     * @param userId   用户ID
     */
	MSDK_EXPORT_UE static void SetUserId(const String &userId);
    
    /**
     * 设置MSDK的上报异常堆栈
     * @param type 3-cocoa 4-c# 5-JS 6-Lua
     * @param exceptionName 异常名称
     * @param exceptionMsg 异常消息
     * @param exceptionStack 异常堆栈内容
     * @param extInfo 异常的附加额外信息
     */
	MSDK_EXPORT_UE static void ReportException(int type, const String &exceptionName, const String &exceptionMsg, const String &exceptionStack, std::map<std::string, std::string> &extInfo)
    {
	    MSDKPIX_LOG_DEBUG("", "ReportException, type:%d, exceptionName:%s, exceptionMsg:%s, exceptionStack:%s",
                          type, exceptionName.c_str(), exceptionMsg.c_str(), exceptionStack.c_str());
        Vector<KVPair> tmp;
        std::map<std::string, std::string>::iterator it = extInfo.begin();
        for (; it != extInfo.end(); it++)
        {
            KVPair kvPair;
            kvPair.key = (*it).first;
            kvPair.value = (*it).second;
            tmp.push_back(kvPair);
        }
        
        ReportExceptionPRV(type, exceptionName, exceptionMsg, exceptionStack, tmp);
    }
    
    /**
     * 动态关闭Bugly上报功能
     * 注意: iOS上有些是杀进程的时候的发生的crash，这些都不想上报
     */
    MSDK_EXPORT_UE static void CloseCrashReport();
};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

class MSDK_EXPORT MSDKCrashRet : public MSDKBaseRet
{
public:
    int maxDataLen;
    char *data;
    
    MSDKCrashRet(const MSDK::MSDKCrashRet &crashRet) : MSDKBaseRet(crashRet) {
        maxDataLen = crashRet.maxDataLen;
        data = crashRet.data;
    }
    
    AutoParser("com.itop.gcloud.msdk.api.crash.MSDKCrashRet", A(thirdCode, "ret"),
               A(thirdMsg, "msg"), A(extraJson, "extra"), O(retCode, retMsg, methodNameID),
               O(methodNameID));
    
};


class MSDK_EXPORT MSDKCrashObserver
{
public:
    //新增一个虚析构函数 不然 UE4 报错
    virtual ~MSDKCrashObserver(){};
    
    virtual long OnCrashExtraDataNotify(MSDKCrashRet &crashRet){
        return 0;
    };
    
    virtual const char* OnCrashExtraMessageNotify(){
        return NULL;
    };
};

class MSDKCrashObserverAdapter : public MSDK::MSDKCrashObserver {
public:
    long OnCrashExtraDataNotify(MSDK::MSDKCrashRet &crashRet);
    const char* OnCrashExtraMessageNotify();
    
    MSDKSpace::NoSTL::MSDKCrashObserver *mObserver = NULL;
};

class MSDK_EXPORT MSDKCrash
{
private:
    static MSDKCrashObserverAdapter mCrashObserverAdapter;

public:
    
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
    MSDK_EXPORT_UE static void SetCrashObserver(MSDKCrashObserver *crashObserver);
#else
    static void SetCrashObserver(MSDKCrashObserver *crashObserver)
    {
        if (!crashObserver)
        {
            MSDKPIX_LOG_ERROR("", "MSDKCrashObserver cant not be NULL");
        }
        else
        {
            mCrashObserverAdapter.mObserver = crashObserver;
            MSDK::MSDKCrash::SetCrashObserver(&mCrashObserverAdapter);
        }
    }
#endif
    
    /**
     *  自定义日志打印接口,用于记录一些关键的业务调试信息, 可以更全面地反应APP发生崩溃或异常的上下文环境.
     *
     *  @param level  日志级别，0-silent, 1-error,2-warning，3-inifo，4-debug，5-verbose
     *  @param tag    日志模块分类
     *  @param log 日志内容
     */
    MSDK_EXPORT_UE static void LogInfo(int level, const String &tag, const String &log);
    
    /**
     * 设置关键数据，随崩溃信息上报
     * @param key 键值
     * @param value 键值对
     */
    MSDK_EXPORT_UE static void SetUserValue(const String &key, const String &value);
    
    /**
     * 设置用户 ID
     * @param userId   用户ID
     */
    MSDK_EXPORT_UE static void SetUserId(const String &userId);
    
    /**
     * 设置MSDK的上报异常堆栈
     * @param type 3-cocoa 4-c# 5-JS 6-Lua
     * @param exceptionName 异常名称
     * @param exceptionMsg 异常消息
     * @param exceptionStack 异常堆栈内容
     * @param extInfo 异常的附加额外信息
     */
    MSDK_EXPORT_UE static void ReportException(int type, const String &exceptionName, const String &exceptionMsg, const String &exceptionStack, const StringMap &extInfo);
    
    /**
     * 动态关闭Bugly上报功能
     * 注意: iOS上有些是杀进程的时候的发生的crash，这些都不想上报
     */
    MSDK_EXPORT_UE static void CloseCrashReport();
};

NS_MSDK_SPACE_NO_STL_END

#if MSDK_PLATFORM_WINDOWS
#else
#include "MSDKRename.h"
#endif
#endif /* MSDK_CRASH_H */

