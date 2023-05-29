//
//  GUACrashService.h
//  GUASample
//
//  Created by tafflin on 2022/6/8.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "UnionAdapterDefine.h"

GUA_NAMESPACE_BEGIN

class GUA_EXTERN GUACrashRet : public GUABaseResult
{
    using GUABaseResult::GUABaseResult;
public:
    int max_data_len;
    char *data;

    GUACrashRet(){};

};

class GUA_EXTERN GUACrashObserver
{
public:
    virtual ~GUACrashObserver(){};

    virtual long OnCrashExtraDataNotify(const GUACrashRet &crash_ret){
        return 0;
    };

    virtual const char* OnCrashExtraMessageNotify(){
        return NULL;
    };
};

class GUA_EXTERN GUACrashService
{
// Commom API
public:
    /**
     * @brief Set Crash module observer
     *
     * @param crash_observer [required] object implements from CrashObserver
     */
    static void SetCrashObserver(GUACrashObserver *crash_observer);

    /**
     *  @brief Custom log info, using for logging some messages, it helps to review the context when crash happens
     *
     *  @param level  [required] log levelm 0:silent, 1:error, 2:warning, 3:inifo, 4:debug, 5:verbose
     *  @param tag    [required] log tag
     *  @param log    [required] log contents
     */
    static void LogInfo(int level, const std::string &tag, const std::string &log);

    /**
     * @brief Set some key user values, it will be reported when crash happens
     *
     * @param key   [required] key
     * @param value [required] value
     */
    static void SetUserValue(const std::string &key, const std::string &value);

    /**
     * @brief Set user ID
     *
     * @param user_id   [required] user ID
     */
    static void SetUserId(const std::string &user_id);

    /**
     * @brief report the exception stack of some languages
     *
     * @param type               [required] language type 3:cocoa 4:c# 5:JS 6:Lua
     * @param exception_name     [required] exception name
     * @param exception_msg      [required] exception message
     * @param exception_stack    [required] exception stack
     * @param ext_info           [required] extra info
     */
    static void ReportException(
        int type,
        const std::string &exception_name,
        const std::string &exception_msg,
        const std::string &exception_stack,
        const std::map<std::string, std::string> &ext_info);

//Common API End

//MSDK API
    /**
     * @brief [MSDK Only]Close crash report, attention: on iOS, 
     * some crashes occur during process killing. you don't want to report them
     */
    static void CloseCrashReport();

};
GUA_NAMESPACE_END
