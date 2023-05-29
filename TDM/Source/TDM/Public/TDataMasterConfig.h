//
//  TDataMasterConfig.h
//  TDataMaster
//
//  Created by Morris on 17/1/5.
//  Copyright © 2017年 TDataMaster. All rights reserved.
//

#ifndef TDataMasterConfig_h
#define TDataMasterConfig_h

#include "TDataMasterDefines.h"
#include "TDataMasterCommon.h"
#include "TMutex.h"
#include "TDMSingleton.h"

_TDM_Name_Space
{
    
#define CONFIG_KEY_IOS_14_IDFA_ENABLE   "iOS14IDFAEnable"
#define TDM_STARTUP_EVENT_DELAY_DEFAULT 5
    
// default key value
#define TDM_VALUE_NOT_SET   0
#define TDM_VALUE_ON        1
#define TDM_VALUE_OFF       -1
#define TDM_VALUE_DEFAULT   -2
    
// default local save key value
#define TDM_LOCAL_VALUE_ON       "1"
#define TDM_LOCAL_VALUE_OFF      "-1"
#define TDM_LOCAL_VALUE_NOT_SET  "0"
    

// KV default set
#define TDM_DEFAULT_KV_MAX_LOCAL_FILE_SIZE    262144  // KV max size  256KB
#define TDM_DEFAULT_KV_MAX_LOCAL_FILE_NUM     10      // KV max file size 10
#define TDM_DEFAULT_KV_REPORT_INTERVAL        5       // KV report gap time
#define TDM_DEFAULT_KV_CONNECT_TIMEOUT        3000    // KV connect out time
#define TDM_DEFAULT_KV_REQUEST_TIMEOUT        10000   // KV request out time
#define TDM_DEFAULT_KV_CLEAR_FILE_SIZE        4       // KV clear file size
    
// Bin default set
#define TDM_DEFAULT_BIN_MAX_LOCAL_FILE_SIZE   524288  // Bin max size 512KB
#define TDM_DEFAULT_BIN_MAX_INSTANT_FILE_SIZE 524288  // Bin max instant size 512KB
#define TDM_DEFAULT_BIN_MAX_LOCAL_FILE_NUM    80      // Bin max file size 10
#define TDM_DEFAULT_BIN_REPORT_INTERVAL       10      // Bin report gap time
#define TDM_DEFAULT_BIN_CONNECT_TIMEOUT       3000    // Bin connect out time
#define TDM_DEFAULT_BIN_REQUEST_TIMEOUT       20000   // Bin request out time
#define TDM_DEFAULT_BIN_CLEAR_FILE_SIZE       40      // Bin clear file size
#define TDM_DEFAULT_BIN_PRESIGN_SIZE          10485760// Bin cos file max size, default 10M
    
// report limits
#define Default_Block_Bytes     (1 << 15)           // size  32KB
#define DISK_CHECK_METHOD_DEFAULT   0   // method type 0

    class TDataMasterConfig : public TDMSingleton<TDataMasterConfig>
    {
        friend class TDMSingleton<TDataMasterConfig>;
    public:
        bool SetConfiguration(const void* data, int size);
        bool SetHTTPConfiguration(const String& respBody);

        uint32_t GetBlockSize();

        const char* GetSessionID();
        bool GetEnableReportDebug();
        int  GetEnableHTTPRreport();
        int  GetDeviceInfoSwitch();
        int  GetStartupEventDelay();
        int GetHttpRequestType();
        bool IsCompressReport();
        bool IsRouteRequestSuccess();
        bool IsEnableSingleThread();
        bool IsEnableJNIAttach();
        
        String GetHTTPKVUrl();
        String GetHTTPBinUrl();
        const char* GetHTTPPresignUrl();
        String GetHTTPToken();
        
        int GetAvailSpaceType();

        uint32_t GetKVMaxTotalSize();
        uint32_t GetKVMaxLocalFileNum();
        uint32_t GetKVMaxLocalFileSize();
        uint32_t GetKVMaxLocalFileNumAfterClear();
        uint32_t GetKVConTimeOut();
        uint32_t GetKVReqTimeOut();
        uint32_t GetKVReportInterval();
        
        uint32_t GetBinMaxTotalSize();
        uint32_t GetBinMaxLocalFileNum();
        uint32_t GetBinMaxLocalFileSize();
        uint32_t GetBinMaxInstantFileSize();
        uint32_t GetBinMaxLocalFileNumAfterClear();
        uint32_t GetBinConTimeOut();
        uint32_t GetBinReqTimeOut();
        uint32_t GetBinReportInterval();
        uint32_t GetBinCOSMaxSize();

        // mini type of KV/Bin report
        uint32_t GetConfigNetReportMinType(bool isBin);
        
        String GetRemoteConfig(const String &key);

        // checkout black eventName or srcID
        bool CheckBlackEventInfo(const char *eventName, int64_t srcID);
        // checkout white eventName or srcID
        bool CheckWhiteEventListInfo(const char *eventName, int64_t srcID);
        
        // http proxy
        String GetProxy();
        void   ReStartGetProxy();
        void   EnableProxy(bool isEnable);
        
    private:
        TDataMasterConfig();
        TDataMasterConfig(const TDataMasterConfig& t){}
        TDataMasterConfig& operator=(const TDataMasterConfig& t){return *this;}
        ~TDataMasterConfig();

        void SetRemoteConfig(const String &key, const String &value);
        bool GetProxyEnable();
        
        void StartRouteEnviorment();
        
    private:
        CMutex mMutex;
        String mSessinID;
        String mHTTPToken;
        String mHTTPKVUrl;
        String mHTTPBinUrl;
        char  mHTTPPresignUrl[1024];
        String mProxy;
        bool mEnableReport;
        bool mEnableReportDebug;
        bool mIsCompressReport;
        bool mRouteRequestSuccess;         // route is request success
        bool mEnableReportSingleThread;    // is enable signle thread report kv and bin. default value is true
        bool mEnableJNIAttach;             // is enable attach jni env on main thread, just for android
        
        int  mHttpReuqestType;       //http request type. default value is 0. 1: Lite Native, 2: GCloud Native, 3: libCurl
        int  mRemoteProxySwitch;    //remote proxy setting value
        int  mLocalProxySwitch;     //local proxy setting value
        int  mReportSwitch;
        int  mDeviceInfoSwitch;
        int  mStartupEventDelay;
        int  mAvailType;

        uint32_t mBlockSize;
        uint32_t mKVMaxLocalFileNum;
        uint32_t mKVMaxLocalFileSize;
        uint32_t mKVMaxLocalFileNumAfterClear;
        uint32_t mKVConTimeOut;
        uint32_t mKVReqTimeOut;
        uint32_t mKVReportInterval;
        uint32_t mKVNetTypeReport;

        uint32_t mBinMaxLocalFileNum;
        uint32_t mBinMaxLocalFileSize;
        uint32_t mBinMaxInstantFileSize;
        uint32_t mBinMaxLocalFileNumAfterClear;
        uint32_t mBinConTimeOut;
        uint32_t mBinReqTimeOut;
        uint32_t mBinReportInterval;
        uint32_t mBinNetTypeReport;
        uint32_t mBinCOSFileSize;
        
        TDM_STL::map<String,String> mCustomValues;
        TDM_STL::vector<String>     mEventSrcIDBlackList;
        TDM_STL::vector<String>     mEventNameBlackList;
        TDM_STL::vector<String>     mEventSrcIDWhiteList;
        TDM_STL::vector<String>     mEventNameWhiteList;
    };
}



#endif /* TDataMasterConfig_h */
