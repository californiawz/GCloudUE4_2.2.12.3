#ifndef GCloud_Inner_Define_h
#define GCloud_Inner_Define_h

#define JNI_CLASS_GSDK_GCLOUD_GCLOUD "com/tencent/gcloud/GCloud"
#define JNI_CLASS_GSDK_GCLOUD_NETINTERFACE_HELPER "com/tencent/gcloud/netinterface/NetInterfaceHelper"
#define JNI_CLASS_GSDK_GCLOUD_NETINTERFACE_MSGWORK "com/tencent/gcloud/netinterface/MsgWorker"
#define JNI_CLASS_GSDK_GCLOUD_QR_QRCODEAPI "com/tencent/gcloud/qr/QRCodeAPI"
#define JNI_CLASS_GSDK_GCLOUD_DOLPHIN_CUIIPSMOBILE "com/tencent/gcloud/dolphin/CuIIPSMobile"
#define JNI_CLASS_GSDK_GCLOUD_APKCHANNEL_APKCHANNELUTIL "com/tencent/gcloud/apkchannel/ApkChannelUtil"
#define JNI_CLASS_GSDK_GCLOUD_V3_APKCHANNEL_APKCHANNELUTIL "com/tencent/gcloud/newapkchannel/ApkChannelUtil"
#define MAC_GSDK_GCLOUD_TDM_BUNDLE_ID "com.tencent.TDataMaster"
#define MAC_GSDK_GCLOUDCORE_BUNDLE_ID "com.cros.gcloud.GCloudCore"

namespace GCloud {
    namespace Conn
    {
        enum
        {
            kChannelNone = 0,
            kChannelTWChat = 1,
            kChannelTQChat = 2,
            kChannelWechat = kChannelTWChat,
            kChannelQQ = kChannelTQChat,
            kChannelGuest = 3,
            kChannelFacebook,
            kChannelGameCenter,
            kChannelGooglePlay,
            kChannelTwitter = 9,
            kChannelGarena = 10,
            kChannelLine = 14,
            kChannelApple = 15,
        };
        typedef int ChannelType;

        enum EncryptMethod {
            kEncryptNone = 0,
            kEncryptTea  = 1,
            kEncryptTQCHAT   = 2,
            kEncryptQQ   = kEncryptTQCHAT,
            kEncryptAes  = 3,
            kEncryptAes2 = 4,
        };
    }
    enum
    {
        kChannelNone = 0,
        kChannelTWChat = 1,
        kChannelTQChat = 2,
        kChannelWechat = kChannelTWChat,
        kChannelQQ = kChannelTQChat,
        kChannelGuest = 3,
        kChannelFacebook,
        kChannelGameCenter,
        kChannelGooglePlay,
        kChannelTwitter = 9,
        kChannelGarena = 10,
        kChannelLine = 14,
        kChannelApple = 15,
    };
    typedef int ChannelType;
}
#endif
