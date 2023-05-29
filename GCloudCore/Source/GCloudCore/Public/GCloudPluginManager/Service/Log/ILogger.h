//
// Created by aaronyan on 2019/9/25.
//

#ifndef ILOGGER_H
#define ILOGGER_H

#define GCLOUD_LOG_MODE "LogMode"
#define GCLOUD_LOG_SINGLE_SIZE_LIMIT "LogSingleSizeLimit"
#define GCLOUD_LOG_EXCEED_OP "LogExceedOp"
#define GCLOUD_LOG_CONSOLE_OUTPUT "LogConsoleOutput"

namespace GCloud {

    typedef enum
    {
        kLogDebug,
        kLogInfo,
        kLogWarning,
        kLogEvent,
        kLogError,
        kLogNone,
    }ALogPriority;

    enum TLogMode
    {
        kNoCompressNoEncryt = 0,
        kCompressNoEncryt = 1,
        kCompressEncryt = 2
    };


    enum LogExceedOp
    {
        kFileDelete = 0,
        kNoAppend = 1
    };

    enum IntelliDevStage
    {
        kIntelliDevStageStart = 0,
        kIntelliDevStageProcessing = 1,
        kIntelliDevStageFinish = 2,
    };
    
    enum IntelliDevStatus
    {
        kIntelliDevStatusSuccess = 0,
        kIntelliDevStatusFail = 1,
        kIntelliDevStatusError = 2,
        kIntelliDevStatusUnknown = 3,
    };


    typedef void (*LogCallback)(ALogPriority pri, const char* msg);

    class ILogger
    {
    public:
        virtual int GetVersion() = 0;

        //LogMode, LogSingleSizeLimit, LogExceedOp
        virtual void SetOption(const char* key, int value) = 0;

        //reserve
        virtual void SetOption(const char* key, const char* value) = 0;

        virtual void SetCallback(LogCallback callback) = 0;

        virtual void SetLogLevel(ALogPriority pri) = 0;

        virtual void Init() = 0;

        virtual void Log(ALogPriority pri, const char *file, unsigned int line, const char *function, const char* tag, const char* log) = 0;
        
        //intelliDevLog
        virtual void XLogDetail(GCloud::ALogPriority pri,const char *file, unsigned int line, const char *function,const char *module, const char *session,GCloud::IntelliDevStage stage, GCloud::IntelliDevStatus status, int errCode, int errCode2,const char *errorMsg,const char *userInfo,const char *resv, const char *log) = 0;
        
        virtual ALogPriority GetLogLevel() = 0;

        virtual void RemoveOldLog(int hoursAgo, int logFileNumLimit) = 0;

        //reserve
        virtual void Perform(int opt) = 0;

    };
}


#endif //ILOGGER_H
