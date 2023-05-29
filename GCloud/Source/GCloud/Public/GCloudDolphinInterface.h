#ifndef GCLOUD_DOLPHINE_INTERFACE_H
#define GCLOUD_DOLPHINE_INTERFACE_H
#include "GCloudPal.h"
#define DOLPHIN_VERDESCRITIONLENGTH 256
#define DOLPHIN_USERDEFINESTRLENGTH 1024
#define DOLPHIN_UPDATEURLLENGTH 512
#define DOLPHIN_VEESIONURLLENGTH 1024
#define DOLPHIN_USERIDLENGTH 128
#define DOLPHIN_WORLDIDLENGTH 128
#define DOLPHIN_PATHLENGTH 256
#define DOLPHIN_VERSIONLENGTH 64
#define DOLPHIN_USERDATALENGTH 256
#define DOLPHIN_FUNC_DICT_LENGTH 512

#ifdef CU_OS_WIN32
#define DOLPHINEXPORTAPI __declspec(dllexport)
#else
#define DOLPHINEXPORTAPI
#endif

namespace GCloud
{
    //--------------------------------  new version information  --------------------------------//
    typedef struct dolphinVersionInfo
    {
        bool        isAppUpdating;
        bool        isNeedUpdating;
        bool        isForcedUpdating; //Whether to force to update
        cu_uint16   versionNumberOne; //versionNumberOne
        cu_uint16   versionNumberTwo; //versionNumberTwo
        cu_uint16   versionNumberThree; //versionNumberThree
        cu_uint16   versionNumberFour; //versionNumberFour
        cu_uint64   needDownloadSize; //Need to download size
        char versionDescrition[DOLPHIN_VERDESCRITIONLENGTH]; //version descrition
        char userDefineStr[DOLPHIN_USERDEFINESTRLENGTH];//User-defined string on GCloud Server
		bool        isAuditVersion; // is audit version
		bool        isGrayVersion;  // is gray version
		bool        isNormalVersion;// is normal version

        dolphinVersionInfo()
        {
            isAppUpdating = false;
            isNeedUpdating = false;
            isForcedUpdating = false;
            needDownloadSize = 0;
            versionNumberOne = 0;
            versionNumberTwo = 0;
            versionNumberThree = 0;
            versionNumberFour = 0;
            memset(versionDescrition, 0, DOLPHIN_VERDESCRITIONLENGTH);
            memset(userDefineStr, 0, DOLPHIN_USERDEFINESTRLENGTH);
			isAuditVersion = false;
			isGrayVersion = false;
			isNormalVersion = false;
        }
    }DOLPHINVERSIONINFO;


    //--------------------------------  stages of the update process  --------------------------------//
    typedef enum dolphinUpdateStage
    {
        VS_Start = 0,
		VS_DiffUpdate=8,
        VS_FullUpdate=9,
        VS_FirstExtract = 10,
		VS_FullUpdate_Extract,	// 11
        VS_FullUpdate_GetFileList, // 12
        VS_FullUpdate_GetMetaFile, // 13
        VS_FullUpdate_CompareMetaFile,//14
        VS_DownApkConfig,  // 15
        VS_CreateApk,  //16
        VS_CheckApkMd5, //17
        VS_FullUpdate_CreateTask=18, 
		VS_Filelist_Check = 31,
		VS_Dolphin_Version = 69,
        VS_ApkUpdate = 70,
        VS_ApkUpdateDownConfig,
        VS_ApkUpdateDownDiffFile,
        VS_ApkUpdateDownFullApk,
        VS_ApkUpdateCheckCompletedApk,
        VS_ApkUpdateCheckLocalApk,
        VS_ApkUpdateCheckConfig,
        VS_ApkUpdateCheckDiff,
        VS_ApkUpdateMergeDiff,
        VS_ApkUpdateCheckFull,
		VS_ApkUpdateCheckPredownloadApk,
        VS_SourceUpdateCures = 90,
        VS_SourceUpdateDownloadList,
        VS_SourcePrepareUpdate,
        VS_SourceAnalyseDiff,
        VS_SourceDownload,
        VS_SourceExtract,
        VS_SourceDownload4IOSBGDownload,
		VS_SourceCheckPredownloadPatch,
		VS_SourceExtractPredownloadPatch,
        VS_Success = 99,
        VS_Fail = 100,
    }DOLPHINUPDATESTAGE;

    //--------------------------------  UpdateInitType  --------------------------------//
    typedef enum dolphinUpdateInitType
    {
        //Program Update
        UpdateInitType_OnlyProgram = 1,
        //Resource Update
        UpdateInitType_OnlySource,
		UpdateInitType_SourceCheckAndSync,//find the files which is deleted or modified and then download it
		UpdateInitType_SourceCheckAndSync_Optimize_Full,//find the files which is deleted or modified and check the deleted file whether exist or newest in app' first ifs,Final decide to download the files or not. 
		UpdateInitType_SourceCheckAndSync_Optimize_Part,//use with the UpdateType_Only_FirstExtract_Part ,beside the above consituation,when the file is partly extracted,it's function is the same as  'UpdateType_SourceCheckAndSync'
        UpdateInitType_SourceCheckAndSync_Optimize_Full_Scatter,//if the resource in app is a scattered type,another word without IFS file.use this type can do the same as UpdateType_SourceCheckAndSync_Optimize_Full
		UpdateInitType_FirstExtract_All,//All file will be extracted
		UpdateInitType_FirstExtract_Part,//some files which specially delivered by user that the verbose 'mNeedExtractList' in the init strcut 'UpdateInitInfo' will be extracted
		UpdateInitType_FirstExtract_Fix,//Extract the files which is in app'ifs and which is the newest now to fill up the outside resource.
		UpdateInitType_Normal,
    }DOLPHINUPDATEINITTYPE;

	typedef enum VersionUpdateMode
	{
		kUpdateVersionConnectNormal = 1,
		kUpdateVersionConnectParallel =2,
		kUpdateVersionConnectMixAuto = 3,
		kUpdateVersionGetByCDN = 4,
	}VERSIONUPDATEMODE;
	typedef enum MergeFilelistType
	{
		kNormalNotMergeRes = 1,
		kMergeAppResIntoSDCARDRes,
		kModifyResInSDCARDRes,
	}MERGEFILELISTTYPE;

	typedef enum SystemParameterKey
    {
		HttpCurlSigleDownloadTimeout = 1,
		HttpCurlRecvBufferSize,
		
	}SYSTEMPARAMETERKEY;

	typedef enum DolphinImpType
	{
		kNormalDolphin,
		kCustomizeDolphin_QTCVFS,
	} DOLPHINIMPTYPE;

    //--------------------------------  UpdateInitInfo  --------------------------------//
    typedef struct dolphinInitInfo
    {
        cu_uint32 channelId;//Update channel ID      
        dolphinUpdateInitType updateType;//UpdateInitType
        bool isGrayUpdate;//gray update or not
		bool isCheckFileMd5;
        bool openDebugLog;
        bool openErrorLog;
		bool isCreateDiffFlist;//Whether create diff file list when updating the resource
		bool enableIOSBgDownload;
        bool enableCDNGetVersion;
		bool enableSNI;
        bool enableApkDiffUpdate; /* Whether enable apk diff update, if it's value is false, 
                                     then apk update will download the whole full .apk file any way. */
        bool enableNoticeExtract;
        bool getChannelConfig;// whether to get channel config
        bool getRegionid;// whether to get region id
		VERSIONUPDATEMODE versionGetMode;
		MERGEFILELISTTYPE mergeFilelistType;
        char updateUrl[DOLPHIN_UPDATEURLLENGTH];//GCloud server url
        char versionUrl[DOLPHIN_VEESIONURLLENGTH];//Reserved field, not ope, Ignorable
        char appVersion[DOLPHIN_VERSIONLENGTH];//app version
        char srcVersion[DOLPHIN_VERSIONLENGTH];//resource version
		char userData[DOLPHIN_USERDATALENGTH];
		char needExtractList[DOLPHIN_PATHLENGTH];//List of files that need to be extracted
		char sdCardPath[DOLPHIN_PATHLENGTH];
		char cdnVersionUrl[DOLPHIN_UPDATEURLLENGTH];
		DOLPHINIMPTYPE dolphinImpType;
		char dolphinFuncDict[DOLPHIN_FUNC_DICT_LENGTH]; // func dict json string
        char strDolphinDownloadFuncDict[DOLPHIN_FUNC_DICT_LENGTH];  // func dict json string
		cu_uint32 uMaxDLTask;
		cu_uint32 uMaxDLPerTask;
		cu_uint32 uMinDLGapSize;
        cu_int32  connectorType;
      bool use_qts_dolphin_;
      bool use_launcher_mode_;
        dolphinInitInfo()
        {
            channelId = 0;
            updateType = UpdateInitType_OnlyProgram;
            isGrayUpdate = false;
			isCheckFileMd5 = false;
            openDebugLog = true;
            openErrorLog = true;
			isCreateDiffFlist = false;
			enableIOSBgDownload = false;
            enableCDNGetVersion = false;
			enableSNI = false;
            enableApkDiffUpdate = true;
            enableNoticeExtract = false;
            getChannelConfig = false;
            getRegionid = false;
			versionGetMode = kUpdateVersionConnectNormal;
			mergeFilelistType = kNormalNotMergeRes;
            memset(updateUrl, 0, DOLPHIN_UPDATEURLLENGTH);
            memset(versionUrl, 0, DOLPHIN_VEESIONURLLENGTH);
            memset(appVersion, 0, DOLPHIN_VERSIONLENGTH);
            memset(srcVersion, 0, DOLPHIN_VERSIONLENGTH);
			memset(userData, 0, DOLPHIN_USERDATALENGTH);
			memset(needExtractList, 0, DOLPHIN_PATHLENGTH);
			memset(sdCardPath, 0, DOLPHIN_PATHLENGTH);
			memset(cdnVersionUrl, 0, DOLPHIN_UPDATEURLLENGTH);
			dolphinImpType = kNormalDolphin;
			memset(dolphinFuncDict, 0, DOLPHIN_FUNC_DICT_LENGTH);
            memset(strDolphinDownloadFuncDict, 0, DOLPHIN_FUNC_DICT_LENGTH);
			uMaxDLTask = 4;
			uMaxDLPerTask = 3;
			uMinDLGapSize = 256 * 1024;
            connectorType = 1;
          use_qts_dolphin_ = false;
          use_launcher_mode_ = false;
        }
    }DOLPHININITINFO;


    //--------------------------------  dolphin path info  --------------------------------//
    typedef struct dolphinPathInfo
    {
        char updatePath[DOLPHIN_PATHLENGTH];
        char dolphinPath[DOLPHIN_PATHLENGTH];
        char curApkPath[DOLPHIN_PATHLENGTH];
		char ifsPath[DOLPHIN_PATHLENGTH];
        
        dolphinPathInfo()
        {
            memset(updatePath, 0, DOLPHIN_PATHLENGTH);
            memset(dolphinPath, 0, DOLPHIN_PATHLENGTH);
            memset(curApkPath, 0, DOLPHIN_PATHLENGTH);
			    memset(ifsPath, 0, DOLPHIN_PATHLENGTH);
         
        }
    }DOLPHINPATHINFO;

    //--------------------------------  dolphin gray update info  --------------------------------//
    typedef struct dolphinGrayInfo
    {
        char userID[DOLPHIN_USERIDLENGTH];//user`s open ID , for gray update)
        char worldID[DOLPHIN_WORLDIDLENGTH];//user`s world id,for gray update
        dolphinGrayInfo()
        {
            memset(userID, 0, DOLPHIN_USERIDLENGTH);
            memset(worldID, 0, DOLPHIN_WORLDIDLENGTH);
        }
    }DOLPHINGRAYINFO;

    typedef struct dolphinFirstExtractInfo
    {
        char ifsPath[DOLPHIN_PATHLENGTH]; // path of ifs file
		bool isAppendSourceUpdate; //whether update resource after First Extract
        dolphinFirstExtractInfo()
        {
        	isAppendSourceUpdate = true;
            memset(ifsPath, 0, DOLPHIN_PATHLENGTH);
        }
    }DOLPHINFIRSTEXTRACTINFO;

    //--------------------------------  GCloudDolphinCallBackOri  --------------------------------//
    class EXPORT_CLASS GCloudDolphinCallBackOri
    {
    public:
        virtual ~GCloudDolphinCallBackOri(){}
        /// <summary>
        /// After the new version information is obtained, the callback is triggered and the update process enters the wait phase.
        /// Need to implement the interface, manually call the mDolphin.Continue () interface to continue to perform the update, newVersionInfo is the new version information.
        /// </summary>
        /// <param name="newVersinInfo">New version information</param>
        virtual void OnDolphinVersionInfo(dolphinVersionInfo& newVersinInfo) = 0;

        /// <summary>
        /// Update process progress is obtained through this callback interface during the process of updating or repairing resources.
        /// </summary>
        /// <param name="curVersionStage">The stage at which the current version is upgraded</param>
        /// <param name="totalSize">Total size that needs to be downloaded</param>
        /// <param name="nowSize">Currently downloaded size</param>
        virtual void OnDolphinProgress(dolphinUpdateStage curVersionStage, cu_uint64 totalSize, cu_uint64 nowSize) = 0;
        
        /// <summary>
        /// Information in the process of updating or repairing resources. And the update process enters the waiting phase.
        /// </summary>
        /// <param name="curVersionStage">The stage at which the current version is upgraded</param>
        /// <param name="errorCode">Error code</param>
        virtual void OnDolphinError(dolphinUpdateStage curVersionStage, cu_uint32 errorCode) = 0;

        /// <summary>
        /// Tell the update or resource repair success with this callback
        /// </summary>
        virtual void OnDolphinSuccess() = 0;

        /// <summary>
        /// This callback interface informs the installation apk, after receiving this callback, the game can implement the apk installation logic.
        /// </summary>
        /// <param name="apkurl">Apk path</param>
        virtual void OnDolphinNoticeInstallApk(char* apkurl) = 0;

        /// <summary>
        /// Tell the First Extract success with this callback
        /// </summary>
        virtual void OnDolphinFirstExtractSuccess() = 0;

        /// <summary>
        /// After Dolphin Resource downloaded, OnNoticeSourceExtract callback will be triggered before extract resources. return 0 will return OnError, and return 1 will continue dolphin resource process.
        /// </summary>
        virtual bool OnNoticeExtract() = 0;

        /// <summary>
        /// get channel config from server
        /// </summary>
		virtual void OnDolphinServerCfgInfo(const char* config) = 0;

		/// <summary>
		/// After Dolphin IOS background download completed, OnDolphinIOSBGDownloadDone callback will be triggered to notify app.
		/// </summary>
		virtual void OnDolphinIOSBGDownloadDone() = 0;
		
        /// <summary>
        /// get action msg
        /// </summary>		
		virtual void OnActionMsgArrive(const char * msg) = 0;
    };

	class EXPORT_CLASS GCloudDolphinCallBack :public GCloudDolphinCallBackOri
	{
	public:
		virtual ~GCloudDolphinCallBack() {}
		virtual void OnDolphinVersionInfo(dolphinVersionInfo& newVersinInfo) {}
		virtual void OnDolphinProgress(dolphinUpdateStage curVersionStage, cu_uint64 totalSize, cu_uint64 nowSize) {}
		virtual void OnDolphinError(dolphinUpdateStage curVersionStage, cu_uint32 errorCode) {}
		virtual void OnDolphinSuccess() {}
		virtual void OnDolphinNoticeInstallApk(char* apkurl) {}
		virtual void OnDolphinFirstExtractSuccess() {}
		virtual bool OnNoticeExtract() {return true;}
		virtual void OnDolphinServerCfgInfo(const char* config) {}
		virtual void OnDolphinIOSBGDownloadDone() {}
		virtual void OnActionMsgArrive(const char * msg) {}
	};


    //--------------------------------  GCloudDolphinInterface  --------------------------------//
    class EXPORT_CLASS GCloudDolphinInterface
    {
    public:
        virtual ~GCloudDolphinInterface(){}
        /// <summary>
        /// Initialize.program update, resource update, resource repair or first package decompression need to be initialized first, to inform the update related information.
        /// </summary>
        /// <returns>Whether the initialization was successful</returns>
        /// <param name="initInfo">Update related initialization information</param>
        /// <param name="pathInfo">Update related path</param>
        /// <param name="grayInfo">Gray update related information</param>
        /// <param name="feInfo">First Extract information</param>
        /// <param name="callBack">An object that implements the GCloudDolphinCallBack interface</param>
        virtual bool Init(const dolphinInitInfo* initInfo, const dolphinPathInfo* pathInfo,
            const dolphinGrayInfo* grayInfo, const dolphinFirstExtractInfo* feInfo, GCloudDolphinCallBackOri* callBack) = 0;
        
        /// <summary>
        /// Deinitialize, release resource
        /// </summary>
        /// <returns>Whether uninit successful</returns>
        virtual bool Uninit() = 0;

        /// <summary>
        /// When receiving some callbacks from GCloudDolphinCallBack, the update service will be blocked, and you need to call ContinueUpdate to continue the update.
        /// <param name="bContinue">Continue to the next update phase</param>
        /// </summary>
        virtual void ContinueUpdate(bool bContinue) = 0;

        /// <summary>
        /// Call this interface to start the update service, check if the upgrade is needed, and return the result in callback OnDolphinVersionInfo
        /// </summary>
        virtual void CheckAppUpdate() = 0;

        /// <summary>
        /// Call this interface to stops the update service.
        /// </summary>
        virtual void CancelUpdate() = 0;

        /// <summary>
        /// This interface is temporarily reserved and can be ignored
        /// </summary>
        /// <returns></returns>
        virtual cu_uint32 GetLastError() = 0;

        /// <summary>
        /// In the game frame loop Update(), you need to call PollCallback() every frame to refresh the update process.
        /// </summary>
        /// <returns>whether succeed</returns>
        virtual bool PollCallback() = 0;

        /// <summary>
        /// Set IOS background download Attributes
        /// </summary>
        /// <returns>void</returns>
        /// <param name="bEnableCellularAccess">Whether Cellular Access is enabled</param>
        /// <param name="bEnableResumeData">Reserved</param>
        /// <param name="nSessionTimeout">Reserved</param>
        /// <param name="nRetry">Retry times when ios background download task failed. If don't want tasks to retry when failed then set it to 0; otherwise it is recommended to set it to 2</param>
        virtual void SetIOSBGDownloadAttribute(bool bEnableCellularAccess, bool bEnableResumeData, unsigned int nSessionTimeout, unsigned int nRetry) = 0;
		
        /// <summary>
        /// adjust Dolphin system parameter,eg:download engine,file system
        /// </summary>
        /// <param name="key">the detail parameter type
        /// <param name="value">a protocol for the type,it can be a interger or a string.
        /// <returns>void</returns>

		virtual void DynamicAdjustDolphinSystemParameter(SystemParameterKey key,char* value) = 0;

		/// <summary>
		/// Get download progress detail
		/// This interface is used to retrieve progress detail info.
		/// </summary>
		/// <returns>whether succeed</returns>
		virtual bool GetProgressDetail(int* curStage, int* file_info, cu_uint64* totalSize, cu_uint64* nowSize) = 0;
	};

    EXPORT_API GCloudDolphinInterface* CreateDolphin();
    EXPORT_API void ReleaseDolphin(GCloudDolphinInterface** dolphin);
}
// for dll
#ifdef CU_OS_WIN32
extern "C" DOLPHINEXPORTAPI GCloud::GCloudDolphinInterface* CreateDllDolphin();
extern "C" DOLPHINEXPORTAPI void ReleaseDllDolphin(GCloud::GCloudDolphinInterface** dolphin);
#endif

#endif
