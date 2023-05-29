//
//  WWW.h
//  WWW
//
//  Created by vforkk on 11/15/16.
//  Copyright © 2016 vforkk. All rights reserved.
//

#ifndef ABase_WWW_hpp
#define ABase_WWW_hpp

#include "ABasePal.h"
#include "COSUploadTask.h"


namespace ABase {
    enum WWWErrorCode
    {
        kSuccess        = 0,
        kFailed         = 1,
        kTimeout        = 2,
        kUnknownHost    = 3,
        kUnsupportedUrl   = 4,
        kNetworkException =5,
        kIOException    = 6,
		kSecurityException = 7,
    };

	class WWWTask
    {
    public:
        virtual ~WWWTask(){}
        
    public:
        virtual void SetHttpHeader(const char* name, const char* value) = 0;
        virtual void SetUrl(const char* url) = 0;
        virtual const char* GetUrl() = 0;
        
    public:
        virtual void Cancel() = 0;
    };
    
    class DataTask : virtual public WWWTask
    {
    public:
        virtual ~DataTask(){}
    public:
        class Listener
        {
            public:
                virtual void OnDataTaskFinished(DataTask* task, WWWErrorCode error, int httpStatus, const char* data, long long totalSize) = 0;
        };
        
    public:
        virtual void Get() = 0;
        virtual void Post(const char* postData, int postLength) = 0;

    public:
        virtual void SetListener(DataTask::Listener* listener) = 0;
        virtual void RemoveListener(DataTask::Listener* listener) = 0;
        
    };
    
	class DownloadFileTask : virtual public WWWTask
    {
    public:
        virtual ~DownloadFileTask(){}
    public:
        class Listener
        {
            public:
                virtual void OnDownloadFileBegan(DownloadFileTask* task, long long  totalSize) = 0;
                virtual void OnDownloadFileProgress(DownloadFileTask* task, long long  currentSize, long long  totalSize) = 0;
                virtual void OnDownloadFileFinished(DownloadFileTask* task, WWWErrorCode error, long long  totalSize) = 0;
        };
    
    public:
        virtual void Pause() = 0;
        virtual void Resume() = 0;
        
    public:
        virtual void SetListener(DownloadFileTask::Listener* listener)=0;
        virtual void RemoveListener(DownloadFileTask::Listener* listener)=0;
        
    public:
        virtual const char* GetLocalFilePath() = 0;
    };

    
    class EXPORT_CLASS WWW
    {
    public:
        
        static DataTask* Request(const char* url);
        
        static DownloadFileTask* DownloadFile(const char* url, const char* saveFilePath);

        static COSCUploadTask* GetCOSUploadTask();
        
        static void Destroy(DataTask* task);
        static void Destroy(DownloadFileTask* task);
        
    };
    
    
    class UrlResponse
    {
    public:
        virtual ~UrlResponse(){}
    public:
        
        virtual const char *Header(const char *key) const = 0;
        
        virtual const char *Url() const = 0;
        
        virtual const char *Version() const = 0;
        
        virtual int Status() const = 0;
        
        virtual const char *Message()const = 0;
        
        virtual const void *Body() const = 0;
        
        virtual int BodyLength() const = 0;
    };
}

#endif /* WWW_hpp */
