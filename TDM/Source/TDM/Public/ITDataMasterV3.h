
#ifndef ITDataMasterV3_h
#define ITDataMasterV3_h

#include "ITDataMasterV2.h"
_TDM_Name_Space
{
    class ITDMUploadFileObserver
    {
    public:
        ITDMUploadFileObserver(){}
        virtual ~ITDMUploadFileObserver(){}

    public:
        virtual int GetVersion() { return 1; }
        /**
        * 上传COS云服务器结果回调
        * @param srcID     事件ID
        * @param eventName 事件名称
        * @param fileName  保存到COS云服务器名称
        * @param result    上报结果。0为成功，其它为失败
        */
        virtual void OnFileNoify(int srcID, const char *eventName, const char *fileName, int result) = 0;
    };

    class ITDataMasterV3 : public ITDataMasterV2
    {
    protected:
        ITDataMasterV3(){}
        virtual ~ITDataMasterV3(){}

    public:
        static PUBLIC_API ITDataMasterV3* GetInstance();
        virtual int GetVersion() { return 3; }

        /**
        * 根据路径上传文件到COS云服务器
        * @param srcID     事件ID
        * @param eventName 事件名称
        * @param fileName  保存到COS云服务器名称
        * @param filePath  文件路径
        * @param observer  回调对象
        * @return int      返回值：-1失败, 0成功
        */
        virtual PUBLIC_API int UploadFileByCOS(int srcID, const char* eventName, const char* fileName,
                                    const char* filePath, ITDMUploadFileObserver *observer) = 0;
        /**
        * 内部Binary上传到COS云服务器
        * @param srcID      事件ID
        * @param eventName  事件名称
        * @param fileName   保存到COS云服务器名称
        * @param fileData   Binary内容
        * @param fileLength Binary长度
        * @param observer   回调对象
        * @return int       返回值：-1失败, 0成功
        */
        virtual PUBLIC_API int UploadBinaryByCOS(int srcID, const char* eventName, const char* fileName,
                const unsigned char* fileData, long fileLength, ITDMUploadFileObserver *observer) = 0;
    };
}

#endif /* ITDataMasterV3_h */
