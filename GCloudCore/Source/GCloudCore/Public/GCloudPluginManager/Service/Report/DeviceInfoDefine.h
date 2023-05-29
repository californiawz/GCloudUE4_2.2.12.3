//
// Created by lucasfan on 2019-09-12.
//



#ifndef TDM_DEVICEINFODEFINE_H
#define TDM_DEVICEINFODEFINE_H

#define COLLECT_DEVICE_INFO_ALL_STRING              "All"
#define COLLECT_DEVICE_INFO_ALL_SYN_STRING          "AllSyn"

#define COLLECT_DEVICE_INFO_ANDROID_ID_STRING       "AndroidID"
#define COLLECT_DEVICE_INFO_APP_VERSION_STRING      "AppVersion"
#define COLLECT_DEVICE_INFO_BRAND_STRING            "Brand"
#define COLLECT_DEVICE_INFO_BUNDLE_ID_STRING        "BundleId"
#define COLLECT_DEVICE_INFO_CPU_CORE_LONG           "CpuCore"
#define COLLECT_DEVICE_INFO_CPU_FREQ_LONG           "CpuFreq"
#define COLLECT_DEVICE_INFO_CPU_NAME_STRING         "CPUName"
#define COLLECT_DEVICE_INFO_DEVICE_ID_STRING        "DeviceID"
#define COLLECT_DEVICE_INFO_MAC_ADDR_STRING         "MacAddr"
#define COLLECT_DEVICE_INFO_MODEL_STRING            "Model"
#define COLLECT_DEVICE_INFO_SCREEN_HEIGHT_LONG      "ScreenHeight"
#define COLLECT_DEVICE_INFO_SCREEN_WIDTH_LONG       "ScreenWidth"
#define COLLECT_DEVICE_INFO_SYS_VERSION_STRING      "SysVersion"
#define COLLECT_DEVICE_INFO_TOTAL_MEM_LONG          "TotalMem"
#define COLLECT_DEVICE_INFO_TOTAL_SPACE_LONG        "TotalSpace"
#define COLLECT_DEVICE_INFO_UUID_STRING             "UUID"
#define COLLECT_DEVICE_INFO_QIMEI_STRING            "QIMEI"         // QIMEI 通过灯塔 SDK 的异步接口获取
#define COLLECT_DEVICE_INFO_QIMEI36_STRING          "QIMEI36"       // QIMEI36 通过灯塔 SDK 的同步接口获取
#define COLLECT_DEVICE_INFO_IDFA_STRING             "IDFA"
#define COLLECT_DEVICE_INFO_CAID_STRING             "CAID"          // TGPA 新增 CAID 支持
#define COLLECT_DEVICE_INFO_TURINGTICKET_STRING     "TuringTicket"  // 新增 AMS 图灵 ID 票据支持


// 注意 xid 和 OAID 信息为 TGPA 通过 SetDeviceInfo 设置的，因此并不是 TDM 标准的设备信息。不保证能获取到信息
#define COLLECT_DEVICE_INFO_OAID_STRING             "OAID"
#define COLLECT_DEVICE_INFO_XID_STRING              "xid"

namespace GCloud {
    namespace Plugin {

        typedef enum {
            kDeviceInfoStatusDefault = -1,              // default status of device info
            kDeviceInfoStatusSuccess = 0,               // device info is successfully obtain or set and it is not encrypted
            kDeviceInfoStatusEncrypted = 1,             // device info is successfully obtain and it is encrypted
            kDeviceInfoStatusNoPermission = 2,          // no collection permission for this field
            kDeviceInfoStatusDisabled = 3,              // the collection or set function of this device info is disabled
            kDeviceInfoStatusNoStart = 4,               // not yet started collecting
            kDeviceInfoStatusCollecting = 5,            // asynchronous device info are being acquired
            kDeviceInfoStatusParamError = 6,            // method parameter error
            kDeviceInfoStatusUnSupportSysVersion = 7,   // the user's system version does not support the collection of this field.
            kDeviceInfoStatusNotEnoughSpace = 8,        // user-specified string space is not enough
            kDeviceInfoStatusFieldExist = 9,            // this field of device info already exists

            kDeviceInfoExceptionOccur = 100,            // an exception occurred
        } DeviceInfoStatus;

        class IDeviceInfoObserver
        {
        public:
            virtual ~IDeviceInfoObserver(){};

            virtual void OnDeviceInfoNotify(DeviceInfoStatus deviceInfoStatus) = 0;
        };

    }
}

#endif //TDM_DEVICEINFODEFINE_H
