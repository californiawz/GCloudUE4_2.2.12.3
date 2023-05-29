#ifndef GCLOUD_PUFFER_INTERFACE_H
#define GCLOUD_PUFFER_INTERFACE_H

#include "GCloudPal.h"

#ifdef CU_OS_WIN32
#define PUFFEREXPORTAPI __declspec(dllexport)
#else
#define PUFFEREXPORTAPI
#endif

#define PUFFER_INITSTRINGLENGTH 256
#define PUFFER_FUNC_DICT_LENGTH 512

namespace GCloud
{
	typedef enum PufferInitStage
	{
		PIS_Start = 0,
		PIS_DownResSnapshot,
		PIS_UpdateFileList,
		PIS_GetResURL,
		PIS_GETFILELIST,
		PIS_DownloadQTCVFSDB,
		PIS_UpdateQTCVFSDB,
	}PUFFERINITSTAGE;
	
	typedef enum pufferUpdateInitType
	{
		Puffer_UpdateInitType_SeparateRes = 0,//As the default type, the behavior is equivalent to the old protocol, that is, only the latest unassociated puffer version is obtained.
		Puffer_UpdateInitType_Res4DolphinApp,//Get the corresponding version of the puffer associated with the Dolphin app version line
		Puffer_UpdateInitType_Res4DolphinRes//Get the corresponding version of the puffer associated with the Dolphin res version line
	}PUFFERUPDATEINITTYPE;

    typedef enum PufferRestoreStage
    {
        PIS_StartRestore = 0,
        PIS_LoadLocalFilelist,
        PIS_CheckFilelistMd5,
        PIS_RestoreEnd,
        PIS_DownloadBrokenFile,
    }PUFFERRESTORESTAGE;

	typedef enum PufferBatchDownloadType
	{
		PBT_BatchTask = 0,	//Indicates that the batch download task callback
		PBT_FileTask,		//Indicates that a single file download task callback in a batch download task
		PBT_FileTask_Retry	//Indicates that the download of a single task in the batch download task fails. You need to try to download again. The progress callback of the batch download may be rolled back. You can prompt the user accordingly.
	}PUFFERBATCHDOWNLOADTYPE;

	typedef enum ShowCurrentFileListType
	{
		Puffer_ShowCurrentFileList_None = 0, //As the default type, the behavior is equivalent to the old protocol, that is, do not show current puffer file list
		Puffer_ShowCurrentFileList_DEL = 1,  //Show deleted files, These files are in old puffer .eifs file, but not in the current new .eifs file
		Puffer_ShowCurrentFileList_ALL = 2,  //In the process of puffer initialization, show all puffer file list (for example, normal/updated/new added/deleted files)
	}SHOWCURRENTFILELISTTYPE;

	typedef enum PufferFileListStatus
	{
		Puffer_FileListStatus_Normal = 0,  //Normal file.
		Puffer_FileListStatus_Update = 1,  //Updated file. Can find it in both old and current puffer filelist, but it's md5 has changed.
		Puffer_FileListStatus_Delete = 2,  //Deleted file. Can find it in old version puffer filelist, but cannot find it in current version puffer filelist.
		Puffer_FileListStatus_Add = 3,	   //New Added file. Cannot find it in old version puffer filelist, but can be find in the current puffer filelist; And if there is no old puffer filelist, then it would be Puffer_FileListStatus_Normal instead.
	}PUFFERFILELISTSTATUS;

  typedef enum PufferVersionType
  {
    PufferVersionType_NORMAL = 0,
    PufferVersionType_GRAY,
    PufferVersionType_SPECIAL,
  }PUFFERVERSIONTYPE;

	typedef struct PufferInitConfig
	{
		PufferInitConfig()
		{
			uMaxDownloadSpeed = 10*1024*1024;
			uMaxDownTask = 3;
			uMaxDownloadsPerTask= 3;
			uPufferProductId = 0;
			uNeedCheck = false;
			needFileRestore = false;
            removeOldWhenUpdate = true;
			memset(strSourceDir, 0, PUFFER_INITSTRINGLENGTH);
			memset(strPufferServerUrl, 0, PUFFER_INITSTRINGLENGTH);
			memset(strPufferGroupMarkId, 0, PUFFER_INITSTRINGLENGTH);
			memset(strUserId, 0, PUFFER_INITSTRINGLENGTH);
			nPufferGameId = 0;
			uPufferUpdateType = 0;
			uPufferDolphinProductId = 0;
			memset(strDolphinAppVersion, 0, PUFFER_INITSTRINGLENGTH);
			memset(strDolphinResVersion, 0, PUFFER_INITSTRINGLENGTH);
			uEnableIOSBGDownload = false;
			uShowFileList = 0;
			uEnableSNI = false;
            uUseNewQTCVFS = false;
			uPufferImpType = 0;
      uPufferVersionType = 0;
            connectorType = 1;
			memset(strPufferFuncDict, 0, PUFFER_FUNC_DICT_LENGTH);
			memset(strPufferDownloadFuncDict, 0, PUFFER_FUNC_DICT_LENGTH);
		}

		//Puffer maximum download speed, default is 10M/s
		cu_uint32 uMaxDownloadSpeed;

		//The maximum number of concurrent Puffer tasks. The default is 3.
		cu_uint32 uMaxDownTask;

		//Puffer single task maximum number of concurrent download links, the default is 3
		cu_uint32 uMaxDownloadsPerTask;

		//Puffer corresponding ProductId, the same as the puffer page configuration
		cu_uint32 uPufferProductId;

		//Check the file status ID, whether the file needs to be checked for status,>0 is on, <=0 is off
		cu_uint32 uNeedCheck;

		//Identify whether to repair the resource, != 0 for repair, 0 for no repair
		cu_uint32 needFileRestore;
        
        //Identify whether to remove old files when puffer files are modified and need to be update, >0 means remove old files, <=0 means remain old files and user need to remove them when necessary.
        cu_uint32 removeOldWhenUpdate;

		//The local resource directory downloaded by Puffer, the downloaded file will be saved in this path.
		char strSourceDir[PUFFER_INITSTRINGLENGTH];

		//Puffer download server address, the same as the puffer page configuration
		char strPufferServerUrl[PUFFER_INITSTRINGLENGTH];

		//(puffer does not need to set this parameter)
		char strPufferGroupMarkId[PUFFER_INITSTRINGLENGTH];

		//(puffer does not need to set this parameter)
		char strUserId[PUFFER_INITSTRINGLENGTH];

		//GameId corresponding to Puffer
		cu_int64  nPufferGameId;

        //Puffer download update type, supports three types of pufferUpdateInitType, 0、1、 2 correspond to Puffer_UpdateInitType_SeparateRes、 Puffer_UpdateInitType_Res4DolphinApp、 Puffer_UpdateInitType_Res4DolphinRes
		cu_uint32 uPufferUpdateType;

        //The Puffer multi-version line function parameter takes effect when the pufferUpdateType is Puffer_UpdateInitType_Res4DolphinApp or Puffer_UpdateInitType_Res4DolphinRes, and obtains the puffer version information associated with the Dolphin productId.
		cu_uint32 uPufferDolphinProductId;

        //The Puffer multi-version line function parameter takes effect when the pufferUpdateType is Puffer_UpdateInitType_Res4DolphinApp or Puffer_UpdateInitType_Res4DolphinRes, and is used together with the dolphinProductId parameter to obtain the puffer version information of the app version in the puffer version associated with the specific Dolphin productId.       
		char strDolphinAppVersion[PUFFER_INITSTRINGLENGTH];

        //The Puffer multi-version line function parameter takes effect when the pufferUpdateType is Puffer_UpdateInitType_Res4DolphinRes. It is used together with the dolphinProductId and dolphinAppVersion parameters to obtain the puffer version information of the app version and the res version in the puffer version associated with the specific Dolphin productId.
		char strDolphinResVersion[PUFFER_INITSTRINGLENGTH];

		//Identify whether to enable ios background download when updating, >0 means enable ios background download, <=0 means disable.
		cu_uint32 uEnableIOSBGDownload;

		//Show puffer file list when initialize, 0/1/2 correspond to Puffer_ShowCurrentFileList_None/Puffer_ShowCurrentFileList_DEL/Puffer_ShowCurrentFileList_ALL
		cu_uint32 uShowFileList;
		// Identify whether to enable SNI when updating, > 0 means enable ios background download, <= 0 means disable.
		cu_uint32 uEnableSNI;
        //  > 0 means use the new logic of qtcvfs, <= 0 means use the old logic of qtcvfs
        cu_uint32 uUseNewQTCVFS;

		// 0 - kNormalPuffer, 1 - kCustomizePuffer_QTCVFS
		cu_uint32 uPufferImpType;

    //Puffer update version type, support three types of PufferVersionType, 0/1/2 correspond to PufferVersionType_NORMAL, PufferVersionType_GRAY, PufferVersionType_SPECIAL
    cu_uint32 uPufferVersionType;
        
        //1 : pebble,2 : UAP
        cu_int32 connectorType;

		// func dict json string
		char strPufferFuncDict[PUFFER_FUNC_DICT_LENGTH];

		char strPufferDownloadFuncDict[PUFFER_FUNC_DICT_LENGTH];

	}PUFFERINITCONFIG;

	class EXPORT_CLASS IGcloudPufferCallBackOri
	{
	public:
		virtual ~IGcloudPufferCallBackOri(){}

		/// <summary>
        /// Initialization callback result, other Puffer operations must be called after the initialization callback is successful, that is, after isSuccess is true, otherwise all calls have no meaning;
        ///  </summary>
        /// <param name="isSuccess">Whether the initialization is successful</param>
        /// <param name="errorCode">Error code</param>
		virtual void OnInitReturn(bool isSuccess, cu_uint32 errorCode) = 0;

		/// <summary>
        /// Initialization progress callback
        /// </summary>
        /// <param name="stage">stage of Initialization</param>
        /// <param name="nowSize">Current updated new version of eifs file size</param>
        /// <param name="totalSize">Total size to update</param>
		virtual void OnInitProgress(PufferInitStage stage, cu_uint64 nowSize, cu_uint64 totalSize) = 0;

		/// <summary>
        /// The download task callback result .the callback result of the download single file task through the DownloadFile function.
        /// </summary>
        /// <param name="taskId">Task ID</param>
        /// <param name="fileid">File ID</param>
        /// <param name="isSuccess">Whether the download was successful</param>
        /// <param name="errorCode">Error code</param>
		virtual void OnDownloadReturn(cu_uint64 taskId, cu_uint64 fileid, bool isSuccess, cu_uint32 errorCode) = 0;
		
		/// <summary>
        /// Download task progress callback, which refers to the progress callback of downloading single file task through DownloadFile operation
        /// </summary>
        /// <param name="taskId">Task ID</param>
        /// <param name="nowSize">Current download size</param>
        /// <param name="totalSize">Total size to download</param>
		virtual void OnDownloadProgress(cu_uint64 taskId, cu_uint64 nowSize, cu_uint64 totalSize) = 0;

		/// <summary>
        /// The interface is temporarily reserved and will not be called. Checking whether the file needs to be repaired is completed in the initialization step, and the corresponding check result is callback to OnInitReturn.
        /// </summary>
        /// <param name="isSuccess">isSuccess</param>
        /// <param name="errorCode">Error code</param>
        virtual void OnRestoreReturn(bool isSuccess, cu_uint32 errorCode) = 0;

        /// <summary>
        /// The interface is temporarily reserved and will not be called. Checking whether the file needs to be repaired is completed in the initialization step, and the corresponding check progress callback is OnInitReturn.
        /// </summary>
        /// <param name="stage">Current file check status</param>
        /// <param name="nowSize">Current check size</param>
        /// <param name="totalSize">Total size to check</param>
        virtual void OnRestoreProgress(PufferRestoreStage stage, cu_uint64 nowSize, cu_uint64 totalSize) = 0;


        /// <summary>
        /// Download the task callback result, which refers to the callback result of downloading the multi-file task through the DownloadBatchDir/DownloadBatchList operation;
        /// </summary>
        /// <param name="batchTaskId">Task ID, download the task ID returned by multiple files through the DownloadBatchDir/DownloadBatchList interface</param>
        /// param fileid //File handle, when a specified file download fails during the multi-file download process, OnDownloadBatchReturn will return the error information corresponding to the fileid. The fileid is valid only when the batchType is PBT_FileTask = 1, and when the batchType is PBT_FileTask = 0, the file id is invalid.
        ///                When the batchType is PBT_FileTask = 2, it means that the file download failed, and the puffer tries to download the file again.
        /// <param name="isSuccess">whether succeed</param>
        /// <param name="errorCode">Error code</param>
        /// param batchType //callback type (PBT_BatchTask = 0 means that the callback result corresponds to the entire multi-file download task, and PBT_FileTask = 1 or PBT_FileTask = 2 means that the callback result corresponds to a specific specific file in the entire multi-file download task)
        /// param strRet //When batchType is 0, strRet returns a summary of the results of this multi-file download task, such as {"ret":true,"errcode":0,"sucs_num":50,"fail_num":0}
		virtual void OnDownloadBatchReturn(cu_uint64 batchTaskId, cu_uint64 fileid, bool isSuccess, cu_uint32 errorCode, PufferBatchDownloadType batchType, const char* strRet) = 0;
		
        /// <summary>
        /// Download task progress callback, which refers to the progress callback of downloading multi-file tasks through the DownloadBatchDir/DownloadBatchList operation;
        /// </summary>
        /// <param name="batchTaskId">Task ID, download the task ID returned by multiple files through the DownloadBatchDir/DownloadBatchList interface</param>
        /// <param name="nowSize">Current download size</param>
        /// <param name="totalSize">Total size to download</param>
		virtual void OnDownloadBatchProgress(cu_uint64 batchTaskId, cu_uint64 nowSize, cu_uint64 totalSize) = 0;

		/// <summary>
		/// Ios background download callback, which refers to the complete callback of ios background downloads
		/// </summary>
		virtual void OnDownloadIOSBackgroundDone() = 0;

		/// <summary>
		/// Puffer filelist callback, which is used to get current puffer file item status.
		/// </summary>
		/// <param name="fileName">Puffer file name</param>
		/// <param name="st">Puffer file status</param>
		virtual void OnPufferFileListItem(const char* fileName, PufferFileListStatus st) = 0;
	};

	class EXPORT_CLASS IGcloudPufferCallBack :public IGcloudPufferCallBackOri
	{
	public:
		virtual ~IGcloudPufferCallBack() {}
		virtual void OnInitReturn(bool isSuccess, cu_uint32 errorCode) {}
		virtual void OnInitProgress(PufferInitStage stage, cu_uint64 nowSize, cu_uint64 totalSize) {}
		virtual void OnDownloadReturn(cu_uint64 taskId, cu_uint64 fileid, bool isSuccess, cu_uint32 errorCode) {}
		virtual void OnDownloadProgress(cu_uint64 taskId, cu_uint64 nowSize, cu_uint64 totalSize) {}
		virtual void OnRestoreReturn(bool isSuccess, cu_uint32 errorCode) {}
		virtual void OnRestoreProgress(PufferRestoreStage stage, cu_uint64 nowSize, cu_uint64 totalSize) {}
		virtual void OnDownloadBatchReturn(cu_uint64 batchTaskId, cu_uint64 fileid, bool isSuccess, cu_uint32 errorCode, PufferBatchDownloadType batchType, const char* strRet) {}
		virtual void OnDownloadBatchProgress(cu_uint64 batchTaskId, cu_uint64 nowSize, cu_uint64 totalSize) {}
		virtual void OnDownloadIOSBackgroundDone() {}
		virtual void OnPufferFileListItem(const char* fileName, PufferFileListStatus st) {};
	};

	class EXPORT_CLASS IGcloudPufferInterface
	{
	public:
		virtual ~IGcloudPufferInterface(){}

		/// <summary>
        /// This process will be networked, and will automatically update the new version of eifs on the network (only the part that updates the log file information) to the local puffer_res.eifs. 
        /// After successful initialization, there will be a callback that is successfully initialized.
        /// </summary>
        /// <returns>whether succeed</returns>
        /// <param name="initConfig">Puffer Initial configuration</param>
        /// <param name="pCallBack">The object that implements the IPufferCallBack interface</param>
		virtual bool Init(const PufferInitConfig& initConfig,IGcloudPufferCallBackOri* pCallBack) = 0;

		/// <summary>
        /// Deinitialize, corresponding to InitResManager, release resources
        /// </summary>
		virtual void Uninit() = 0;

		/// <summary>
        /// Need to call this interface in every frame of the game Update()
        /// </summary>
		virtual void Update() = 0;

		/// <summary>
        /// Get the id of the file through the file path
        /// </summary>
        /// <returns>file ID</returns>
        /// <param name="filePath">file path</param>
		virtual cu_uint64 GetFileId(const char* filePath) = 0;

		/// <summary>
        /// Determine whether the file already exists by the id of the file.
        /// </summary>
        /// <returns>true:exist false:not exist</returns>
        /// <param name="fileID">File ID</param>
		virtual bool IsFileReady(cu_uint64 fileID) = 0;

		/// <summary>
        /// Get the compressed size of the file by the id of the file
        /// </summary>
        /// <returns>File compressed size</returns>
        /// <param name="fileID">File ID</param>
		virtual cu_uint64 GetFileSizeCompressed(cu_uint64 fileID) = 0;

        /// <summary>
        /// Get the downloaded size of the file by the id of the file
        /// </summary>
        /// <returns>File downloaded size</returns>
        /// <param name="fileID">File ID</param>
        virtual cu_uint64 GetFileSizeDownloaded(cu_uint64 fileID) = 0;

		/// <summary>
        /// Download a single file by file id
        /// </summary>
        /// <returns>The id of the download task</returns>
        /// <param name="fileID">File ID</param>
        /// param forceDownload //Whether to force the update, if it is true, it will force the download. If it is false, it will check if it needs to be updated (equivalent to calling IsFileReady first), then decide whether to download.
        /// <param name="priority">Task priority</param>
		virtual cu_uint64 DownloadFile(cu_uint64 fileID, bool forceSync, cu_uint32 priority) = 0;

		/// <summary>
        /// Start performing resource repair
        /// </summary>
        /// <returns>Task ID</returns>
        /// <param name="priority">task priority</param>
		virtual cu_uint64 StartRestoreFiles(cu_uint32 priority) = 0;

		/// <summary>
        /// Remove the task. Starting the download file will get the task id to perform the operation, and then generally remove this task in the callback after downloading the file.
        /// </summary>
        /// <returns>whether succeed</returns>
        /// <param name="taskId">task id</param>
		virtual bool RemoveTask(cu_uint64 taskId) = 0;

		/// <summary>
        /// Dynamically set the maximum download speed in b/s
        /// </summary>
        /// <returns>whether succeed</returns>
        /// <param name="maxSpeed">Maximum speed in b/s</param>
		virtual bool SetImmDLMaxSpeed(cu_uint64 maxSpeed) = 0;

		/// <summary>
        /// Dynamically set the maximum number of download tasks
        /// </summary>
        /// <returns>whether succeed</returns>
        /// <param name="maxTask">Max task number</param>
        virtual bool SetImmDLMaxTask(cu_uint32 maxTask) = 0;


		virtual bool SetImmDLPollingTime(cu_uint32 pollingTime) = 0;
		/// <summary>
		/// Dynamically set the maximum downloads of pre download task
		/// </summary>
		/// <returns>whether succeed</returns>
		/// <param name="maxTask">Max task number</param>
		virtual bool SetImmDLMaxDownloadsPerTask(cu_uint32 maxDownloadsPerTask) = 0;

		/// <summary>
		/// Dynamically set the gapSize of download
		/// </summary>
		/// <returns>whether succeed</returns>
		/// <param name="gapSize">Gap Size</param>
		virtual bool SetImmDLGapSize(cu_uint32 gapSize) = 0;

        /// <summary>
        /// Dynamically adjust task priority
        /// </summary>
        /// <returns>whether succeed</returns>
        /// <param name="taskId">task ID</param>
        /// <param name="priority">task priority</param>
		virtual bool SetTaskPriority(cu_uint64 taskId, cu_uint32 priority) = 0;

		/// <summary>
        /// Get current download speed
        /// </summary>
        /// <returns>current speed</returns>
		virtual double GetCurrentSpeed() = 0;

		/// <summary>
        /// Get the number of files in the specified directory of eifs
        /// </summary>
        /// <returns>whether succeed</returns>
        /// <param name="dir">file directory</param>
        /// <param name="blSubDir">whether to traverse subdirectories</param>
        /// <param name="nTotal">total number of files obtained after executing this method</param>
		virtual bool GetBatchDirFileCount(const char* dir, bool blSubDir, cu_uint32& nTotal) = 0;

		/// <summary>
        /// Download the files in the specified directory
        /// </summary>
        /// <returns>download task ID</returns>
        /// <param name="dir">Specify the directory to download</param>
        /// <param name="blSubDir">whether to traverse subdirectories</param>
        /// param forceSync // Whether to force the update, if it is true, all files will be forced to download. If it is false, each file will check whether it needs to be updated before deciding whether to download.
        /// <param name="priority">task priority</param>
		virtual cu_uint64 DownloadBatchDir(const char* dir, bool blSubDir, bool forceSync, cu_uint32 priority) = 0;
		
        /// <summary>
        /// Downloads the batch list.
        /// </summary>
        /// <returns>download task ID</returns>
        /// <param name="lst">List of files to download</param>
        /// param forceSync // Whether to force the update, if it is true, all files will be forced to download. If it is false, each file will check whether it needs to be updated before deciding whether to download. 
        /// <param name="priority">task priority</param>
		virtual cu_uint64 DownloadBatchList(const char* lst, bool forceSync, cu_uint32 priority) = 0;

		/// <summary>
        /// Pause a download task
        /// </summary>
        /// <returns>whether succeed</returns>
        /// <param name="taskId">task ID</param>
		virtual bool PauseTask(cu_uint64 taskId) = 0;

		/// <summary>
        /// Resume a download task
        /// </summary>
        /// <returns>whether succeed</returns>
        /// <param name="taskId">task ID</param>
		virtual bool ResumeTask(cu_uint64 taskId) = 0;

		/// <summary>
		/// Set IOS background download Settings
		/// </summary>
		/// <returns>void</returns>
		/// <param name="bEnableCellularAccess">Identify whether cellular Access is enabled</param>
		/// <param name="bEnableResumeData">Reserved</param>
		/// <param name="nSessionTimeout">Reserved</param>
		/// <param name="nRetry">Retry times when ios background download task failed. If don't want tasks to retry when failed then set it to 0; otherwise it is recommended to set it to 2</param>
		/// <param name="nMinFileSize">Identify smallest file size that ios background download tasks enabled, so files will not be downloaded through ios background if file size is smaller. for example 15*1024*1024 means files smaller than 15M will not be downloaded through ios background.</param>		
		/// <param name="nMaxTasks">Identify how many tasks will be enabled in ios background download. It is recommended to less than 15, too many tasks may lead to long time when downloading.</param>		
		virtual void SetIOSBGDownloadPufferSettings(bool bEnableCellularAccess, bool bEnableResumeData, cu_uint32 nSessionTimeout, cu_uint32 nRetry, cu_uint32 nMinFileSize, cu_uint32 nMaxTasks) = 0;

		/// <summary>
		/// Get the compressed size of the specified dir
		/// </summary>
		/// <returns>File compressed size</returns>
		/// <param name="dir">file directory</param>
		/// <param name="blSubDir">whether to traverse subdirectories</param>
		virtual cu_uint64 GetBatchDirSizeCompressed(const char* dir, bool blSubDir) = 0;

        /// <summary>
        /// Get the downloaded size of the specified dir
        /// </summary>
        /// <returns>File downloaded size</returns>
        /// <param name="dir">file directory</param>
        /// <param name="blSubDir">whether to traverse subdirectories</param>
        virtual cu_uint64 GetBatchDirSizeDownloaded(const char* dir, bool blSubDir) = 0;

		/// <summary>
		/// Determine whether the specified dir already exists
		/// </summary>
		/// <returns>true:exist false:not exist</returns>
		/// <param name="dir">file directory</param>
		/// <param name="blSubDir">whether to traverse subdirectories</param>
		virtual bool IsBatchDirReady(const char* dir, bool blSubDir, cu_uint32& nTotal, cu_uint32& nReady, cu_uint32& nNotReady) = 0;

		/// <summary>
		/// Get file md5 by fileId
		/// </summary>
		/// <returns> File md5</returns>
		/// <param name="fileId">File ID</param>
		virtual bool GetFileMd5(cu_uint64 fileID, cu_uint32 bufferSize, char* md5Buffer) = 0;
		
		/// <summary>
		/// remove existing downloaded file or temp file
		/// </summary>
		/// <returns>whether succeed</returns>
		/// <param name="fileID">File ID</param>
		virtual bool RemoveFile(cu_uint64 fileID) = 0;
	};

	EXPORT_API  IGcloudPufferInterface* CreatePuffer();
	EXPORT_API void ReleasePuffer(IGcloudPufferInterface** puffer);
}

// for dll
#ifdef CU_OS_WIN32
extern "C" PUFFEREXPORTAPI GCloud::IGcloudPufferInterface* CreateDllPuffer();
extern "C" PUFFEREXPORTAPI void ReleaseDllPuffer(GCloud::IGcloudPufferInterface** puffer);
#endif

#endif//GCLOUD_PUFFER_INTERFACE_H
