//
// Created by aaronyan on 2018/11/13.
//

#ifndef ANDROID_AS_COSUPLOADTASK_H
#define ANDROID_AS_COSUPLOADTASK_H
class COSCUploadTask
{
public:
    class Listener
    {
    public:
        virtual void OnFinished(COSCUploadTask* task, int error) = 0;
    };

public:
    virtual ~COSCUploadTask();
    virtual void Upload(const char* uploadid, const char* filePath, long long partSize, const char* url) = 0;
    virtual const char* GetUploadid() = 0;
    virtual const char* GetUploadFilePath() = 0;
    virtual void SetCredentialInfo(const char* comParams) = 0;
    virtual void SetListener(COSCUploadTask::Listener* listener) = 0;
};
#endif //ANDROID_AS_COSUPLOADTASK_H
