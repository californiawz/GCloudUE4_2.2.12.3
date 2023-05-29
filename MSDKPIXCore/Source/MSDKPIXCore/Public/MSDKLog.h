/**
 * @file MSDKLog.h
 *
 * @date  2018/4/8
 * @author developer
 *
 * @section DESCRIPTION
 *
 * MSDK 日志入口类
 *
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_LOG_h
#define MSDK_LOG_h

#include "MSDKMacros.h"
#include "MSDKCompatLayer.h"

#ifndef ILOG_TAG
#define ILOG_TAG "[MSDK]"
#endif

#define MSDK_LOG_MAX_LENGTH 16*1024

#define __FILENAME1__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#define __FILENAME2__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1):__FILE__)
#define __FILENAME__ (strrchr(__FILE__, '/') ? (__FILENAME1__):(__FILENAME2__))

#ifdef NO_LOG_DEBUG
#define LOG_DEBUG(...)
#define LOG_ERROR(...)
#else
#define MSDKPIX_LOG_DEBUG(...)          GCloud::MSDK::MSDKLog(GCloud::MSDK::kLevelDebug, ILOG_TAG, __FILENAME__, __FUNCTION__, __LINE__).logging(__VA_ARGS__)
#define MSDKPIX_LOG_ERROR(...)          GCloud::MSDK::MSDKLog(GCloud::MSDK::kLevelError, ILOG_TAG, __FILENAME__, __FUNCTION__, __LINE__).logging(__VA_ARGS__)
#define LOG_DEBUG(...)                  MSDKPIX_LOG_DEBUG("", __VA_ARGS__)
#define LOG_ERROR(...)                  MSDKPIX_LOG_ERROR("", __VA_ARGS__)

NS_MSDK_BEGIN
        typedef enum {
            kLevelDebug = 1,
            kLevelInfo = 2,
            kLevelWarn = 3,
            kLevelError = 4,
            kLevelNone = 5
        } ILogLevel;

        typedef struct {
            ILogLevel level;
            int gameId;
            const char *tag;
            const char *file;
            const char *func;
            const char *seqID;
            int line;
            long long timestamp;
            long long pid;
            long long tid;
            bool usingGCloudLog;
        } ILogInfo;

        class MSDK_EXPORT MSDKLog {
        public:
            MSDK_EXPORT_UE MSDKLog(ILogLevel level, const char *tag, const char *fileName,
                                   const char *funcName, int line);

            MSDK_EXPORT_UE ~MSDKLog();

            MSDK_EXPORT_UE static void usingGCloud(bool useGCloudLog = false);

            MSDK_EXPORT_UE MSDKLog &logging(const char *seqID, const char *fmt, ...);

        private:
            ILogInfo info;
            String logMsg;
            static bool usingGCloudLog;
        };

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

            using MSDKLog = MSDK::MSDKLog;

NS_MSDK_SPACE_NO_STL_END

#endif
#endif
