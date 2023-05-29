1. GCloudSDK导入本地工程的详细步骤参见以下地址：

【GCloudSDK产品使用说明>接入指引】http://sdk.gcloud.oa.com/documents

如有任何疑问，欢迎咨询企业微信服务号： GCloud人工服务


2. 各个组件简单介绍

GCloudCore : GCloudSDK的核心，负责所有组件管理、以及App生命周期管理
GCloud : Connect, Maple, Dolphin, LockStep，Puffer等组件的集合，他们的底层都一样，已经合成一个。
APM : 手游客户端性能管理,手游用户体验监测工具
GEM : 游戏体验管理SDK
GVoice : 是一款支持多样玩法、全面覆盖游戏应用场景的语音服务SDK。
HttpDNS(DNS_OneSDK) : 智营解析,使用http协议代替传统解析域名
MidasLocal: 移动支付平台(国内版)
MidasOversea : 移动支付平台(海外版)
TDM: 组件内部数据上报通道。
TGPA: 腾讯游戏官方性能技术解决方案
GPM(TRI) :游戏体验管理大师 （Game Performance Master）,致力于提供一站式用户体验优化解决方案。(APM、GEM、TGPA三合一的组件)
TssSDKLocal: 手游安全SDK（国内版），致力于为游戏提供全面的安全防护
TssSDKOversea : 手游安全SDK（海外版）
GameBot(GRobot) : 游戏智能AI伴侣，以玩家伴侣身份在游戏各个阶段向玩家提供多场景、个性化的游戏陪伴服务。
MSDKCore : 是为游戏提供公共组件和服务库的平台，旨在加快游戏接入各公共组件和海外开放平台。
MSDKAdjust : MSDK子组件，主要用于海外数据上报Adjust平台
MSDKAppsFlyer : MSDK子组件，主要用于海外数据上报AppsFlyer平台
MSDKBeacon : MSDK子组件，主要用于数据上报灯塔平台
MSDKBugly : MSDK子组件，crash数据上报
MSDKFacebook : MSDK子组件，用于Facebook渠道相关功能
MSDKGameCenter : MSDK子组件，用于iOS gamecenter渠道登录等相关功能
MSDKGoogle : MSDK子组件，用于Google渠道相关功能
MSDKLBS : MSDK子组件，用于LBS定位服务相关功能
MSDKQQ : MSDK子组件，用于QQ渠道相关功能
MSDKTDM : MSDK子组件，主要用于数据上报TDM平台
MSDKTwitter : MSDK子组件，主要用于Twitter渠道相关功能
MSDKFirebase : MSDK子组件，主要用于Firebase推送和数据上报相关功能
MSDKGarena : MSDK子组件，主要用于Garena渠道相关登录、好友、以及其他扩展功能
MSDKWeChat : MSDK子组件，主要用于微信渠道相关功能
MSDKWebView : MSDK子组件，内置浏览器功能
MSDKXG : MSDK子组件，主要用于信鸽推送和数据上报
MSDKXGFCM : MSDK子组件，主要用于海外信鸽推送和数据上报
VideoRecord : 屏幕录制VideoRecord是一款稳定且具有高品质的录屏应用，玩家可在游戏中自由录制流畅清晰的视频， 并截取所需素材保存在本地。
GMall : 游戏商城 GMall 是一个连接前端和道聚城后台的轻量化框架，提供数据请求、响应、管理以及道具获取和购买等基础功能，提供商城管理以及道具获取和购买等服务。
KingCard : 王卡组件用于识别当前用户使用的上网卡是否为王卡。识别后给王卡用户以相应的免流状态提示和王卡身份感知。


====================集成信息====================
Package Time : 2023-05-29 14:16:00

GCloudSDK大版本号:  V2.2.12.3

PluginsVersion(各组件版本号):
GCloud              : 2.12.01.201744
GCloudCore          : 1.5.01.3201
GVoice              : 3.7.00.1479
MSDKPIXBeacon       : 5.30.101.2609
MSDKPIXBugly        : 5.30.101.2609
MSDKPIXCore         : 5.30.101.2614
MSDKPIXLBS          : 5.30.101.2609
MSDKPIXQQ           : 5.30.101.2609
MSDKPIXSystem       : 5.30.101.2609
MSDKPIXTDM          : 5.30.101.2609
MSDKPIXWeChat       : 5.30.101.2609
MSDKPIXWebView      : 5.30.101.2609
MSDKPIXXG           : 5.30.101.2609
PixUI               : 1.0.000.1108
PluginCrosCurl      : 1.0.000.1023
TDM                 : 1.28.005.2077
UnionAdapter        : 5.30.001.7178

PackageParam:{
    "AndroidLibType": "libscpp", 
    "AndroidSupportArchitecture": [
        "armeabi-v7a", 
        "x86", 
        "arm64-v8a", 
        "x86_64"
    ], 
    "AndroidSupportLib": "AndroidX", 
    "BuildSystem": "Gradle", 
    "Config": {
        "{ADJUST_APP_TOKEN_ANDROID}": "{ADJUST_APP_TOKEN_ANDROID}", 
        "{ADJUST_APP_TOKEN_IOS}": "{ADJUST_APP_TOKEN_IOS}", 
        "{APPSFLYER_APPID}": "{APPSFLYER_APPID}", 
        "{APPSFLYER_APP_KEY_ANDROID}": "{APPSFLYER_APP_KEY_ANDROID}", 
        "{APPSFLYER_APP_KEY_IOS}": "{APPSFLYER_APP_KEY_IOS}", 
        "{BEACON_APP_KEY_ANDROID}": "ANDROID1112219381", 
        "{BEACON_APP_KEY_IOS}": "IOS1112219381", 
        "{BUGLY_APP_ID_ANDROID}": "1112219381", 
        "{BUGLY_APP_ID_IOS}": "i1112219381", 
        "{BUNDLE_ID}": "com.sixjoy.letsgo", 
        "{FACEBOOK_APPID}": "624009219651454", 
        "{FACEBOOK_DISPLAYNAME}": "{FACEBOOK_DISPLAYNAME}", 
        "{FIREBASE_SENDER_ID}": "{FIREBASE_SENDER_ID}", 
        "{GAME_ID}": "745065090", 
        "{GAME_KEY}": "bc66f98c11c67ffda74e9cbb4dee5459", 
        "{GOOGLE_APPID}": "{GOOGLE_APPID}", 
        "{GOOGLE_CLIENT_KEY}": "{GOOGLE_CLIENT_KEY}", 
        "{HW_APPID}": "{HW_APPID}", 
        "{KWAI_APP_ID}": "{KWAI_APP_ID}", 
        "{MAIN_ACTIVITY}": "MainActivity", 
        "{MSDK_GAME_ID}": "28045", 
        "{MSDK_GAME_KEY}": "c853b36c7d626eef3720cfdbe2158a82", 
        "{QQ_APPID}": "1112219381", 
        "{TDM_APPID}": "745065090", 
        "{TDM_SECRET_KEY}": "{TDM_SECRET_KEY}", 
        "{TDM_SOURCE_ID}": "{TDM_SOURCE_ID}", 
        "{TDM_SRC_ID}": "745065090", 
        "{TWITTER_KEY_ANDROID}": "{TWITTER_KEY_ANDROID}", 
        "{TWITTER_KEY_IOS}": "{TWITTER_KEY_IOS}", 
        "{TWITTER_KEY}": "{TWITTER_KEY}", 
        "{TWITTER_SECRET_ANDROID}": "{TWITTER_SECRET_ANDROID}", 
        "{TWITTER_SECRET_IOS}": "{TWITTER_SECRET_IOS}", 
        "{TWITTER_SECRET}": "{TWITTER_SECRET}", 
        "{WX_APPID}": "wx4e7fd29bf29f3e79", 
        "{XG_ACCESS_ID_ANDROID}": "{XG_ACCESS_ID_ANDROID}", 
        "{XG_ACCESS_KEY_ANDROID}": "G7aNfd3ODOaoJKSw", 
        "{XG_APPID}": "{XG_APPID}", 
        "{XG_APPKEY}": "G7aNfd3ODOaoJKSw", 
        "{XG_FCM_ENABLE}": "0", 
        "{XG_FLYME_APP_ID}": "{XG_FLYME_APP_ID}", 
        "{XG_FLYME_APP_KEY}": "{XG_FLYME_APP_KEY}", 
        "{XG_OTHER_ENABLE}": "1", 
        "{XG_XIAOMI_APP_ID}": "{XG_XIAOMI_APP_ID}", 
        "{XG_XIAOMI_APP_KEY}": "{XG_XIAOMI_APP_KEY}", 
        "{XY_GAME_ID}": "{XY_GAME_ID}"
    }, 
    "CppVersion": "C11", 
    "Dynamic": "YES", 
    "Engine": "UE4", 
    "GCloudSDKVersion": "2.2.12.3", 
    "ITOPSubplugins": [], 
    "InputPlugins": {
        "GCloud": "/data1/gcloud_plugins/release_plugins/2.2.12hotfix/GCloud/2.12.01.201744", 
        "GCloudCore": "/data1/gcloud_plugins/release_plugins/master/GCloudCore/1.5.01.3201", 
        "GVoice": "/data1/gcloud_plugins/release_plugins/master/GVoice/3.7.00.1479", 
        "MSDKPIXBeacon": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXBeacon/5.30.101.2609", 
        "MSDKPIXBugly": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXBugly/5.30.101.2609", 
        "MSDKPIXCore": "/data1/gcloud_plugins/release_plugins/2.2.12.2hotfix/MSDKPIXCore/5.30.101.2614", 
        "MSDKPIXLBS": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXLBS/5.30.101.2609", 
        "MSDKPIXQQ": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXQQ/5.30.101.2609", 
        "MSDKPIXSystem": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXSystem/5.30.101.2609", 
        "MSDKPIXTDM": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXTDM/5.30.101.2609", 
        "MSDKPIXWeChat": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXWeChat/5.30.101.2609", 
        "MSDKPIXWebView": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXWebView/5.30.101.2609", 
        "MSDKPIXXG": "/data1/gcloud_plugins/release_plugins/master/MSDKPIXXG/5.30.101.2609", 
        "PixUI": "/data1/gcloud_plugins/release_plugins/master/PixUI/1.0.000.1108", 
        "PluginCrosCurl": "/data1/gcloud_plugins/release_plugins/master/PluginCrosCurl/1.0.000.1023", 
        "TDM": "/data1/gcloud_plugins/release_plugins/master/TDM/1.28.005.2077", 
        "UnionAdapter": "/data1/gcloud_plugins/release_plugins/master/UnionAdapter/5.30.001.7178"
    }, 
    "OutputDir": "/data1/tmp/sdkcompress/880495ecbf2287710c9791610114cdbb", 
    "PluginVersion": "2.2.12.3", 
    "Plugins": [
        "GCloud", 
        "GCloudCore", 
        "GVoice", 
        "MSDKPIXBeacon", 
        "MSDKPIXBugly", 
        "MSDKPIXCore", 
        "MSDKPIXLBS", 
        "MSDKPIXQQ", 
        "MSDKPIXSystem", 
        "MSDKPIXTDM", 
        "MSDKPIXWeChat", 
        "MSDKPIXWebView", 
        "MSDKPIXXG", 
        "PixUI", 
        "PluginCrosCurl", 
        "TDM", 
        "UnionAdapter"
    ], 
    "SDKVersions": {
        "GCloudCore": "2.2.12.3", 
        "GVoice": "2.2.12.3", 
        "MSDKPIXBeacon": "2.2.12.3", 
        "MSDKPIXBugly": "2.2.12.3", 
        "MSDKPIXCore": "2.2.12.3", 
        "MSDKPIXLBS": "2.2.12.3", 
        "MSDKPIXQQ": "2.2.12.3", 
        "MSDKPIXSystem": "2.2.12.3", 
        "MSDKPIXTDM": "2.2.12.3", 
        "MSDKPIXWeChat": "2.2.12.3", 
        "MSDKPIXWebView": "2.2.12.3", 
        "MSDKPIXXG": "2.2.12.3", 
        "PixUI": "2.2.12.3", 
        "PluginCrosCurl": "2.2.12.3", 
        "TDM": "2.2.12.3", 
        "UnionAdapter": "2.2.12.3", 
        "connector": "2.2.12.3"
    }, 
    "SupportPlatform": [
        "iOS", 
        "Android", 
        "Win", 
        "Mac"
    ], 
    "TDMType": "local", 
    "UnityVersion": ""
}

root:[/data1/tmp/sdkcompress/880495ecbf2287710c9791610114cdbb/GCloudUE4_2.2.12.3]
+-AAInfo4Copy.txt(md5:d336a5f44405e88c9ab66f63eec769f1)
+-GCloud
|    +-GCloud.uplugin(md5:65c6a8d9994f9e32ff6e2e9570a32f88)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-GCloud
|    |    |    +-GCloud.Build.cs(md5:b92f09bb360eeb95442ede2ce7a90cba)
|    |    |    +-GCloudSDK_APL.xml(md5:ff27cab61654116ca23f403aeece6c8a)
|    |    |    +-Private
|    |    |    |    +-GCloudAppDelegate.cpp(md5:9395132acd0d48cffe586e2e053cf4fd)
|    |    |    |    +-GCloudAppDelegate.h(md5:7d811f07e6361b7b73c9b038c74c8297)
|    |    |    |    +-GCloudSDKModule.cpp(md5:f4efcd3823f0cf5e2e4ac4a583f3301e)
|    |    |    |    +-iOS
|    |    |    |    |    +-GCloudAppDelegate.mm(md5:665c47917b1c28b78a32b9ca060ee9d4)
|    |    |    +-Public
|    |    |    |    +-AArray.h(md5:2ba713c6705ae8375cf279f9df1be390)
|    |    |    |    +-AData.h(md5:cfe7e4422e1befebbce53989565d75a1)
|    |    |    |    +-ADictionary.h(md5:34bc1c225ba6b2b22228120d37edc806)
|    |    |    |    +-ANumber.h(md5:52bb63e29d138cf7e5a83213754738cf)
|    |    |    |    +-AObject.h(md5:877c9e02f9950b3a2ffe4d353102ae55)
|    |    |    |    +-AString.h(md5:c68521d16446cbc306720da425475024)
|    |    |    |    +-AValue.h(md5:fa68f2bc2481d553f363b0e9d2e89a86)
|    |    |    |    +-Access.h(md5:10102aecf451a952ec94cad69b71cd7c)
|    |    |    |    +-ApolloBuffer.h(md5:0b778d24248df038552f088ffd4c4e4b)
|    |    |    |    +-ApolloBufferReader.h(md5:21950e1ecaae74eb663d8212432f2a3d)
|    |    |    |    +-ApolloBufferWriter.h(md5:7c760422dca12121f42216305513e05f)
|    |    |    |    +-ConnectorPublicDefine.h(md5:f4bd1170da295f79186cf1f57661f2d7)
|    |    |    |    +-DolphinHelper.h(md5:4bebb7a73560c4d55a1339cf24ab9a2d)
|    |    |    |    +-G6ConnectorDefine.h(md5:132ffba30c03217ad6e615eab758bb16)
|    |    |    |    +-GCloudApplication.h(md5:7e0a3d71f3a02e59f3936d30f2416170)
|    |    |    |    +-GCloudDataIFSInterface.h(md5:ab08b583785d0aa2482d81d1728d88af)
|    |    |    |    +-GCloudDolphinInterface.h(md5:4c7ca53281ca53fb97e8b8ba8dda7875)
|    |    |    |    +-GCloudDolphinUtility.h(md5:2dc2ffb9740e233606548159994eb9bd)
|    |    |    |    +-GCloudInnerDefine.h(md5:008bcd27ffbfb45c0b307c92ca090ae3)
|    |    |    |    +-GCloudPal.h(md5:940539d4f05120e97f585bd572a780cd)
|    |    |    |    +-GCloudPublicDefine.h(md5:be04286b1181205a1966f4d063b2230b)
|    |    |    |    +-GCloudPufferInterface.h(md5:f7295babbb95fa43943364fbb0feb7e5)
|    |    |    |    +-GCloudSDKModule.h(md5:0ee3eeec8ca7f743160e8827cf777168)
|    |    |    |    +-GCloudVersion.h(md5:6517581b8a256d0876219b6c3aa72fad)
|    |    |    |    +-GFile.h(md5:6d915bd55fccdfbf10362aadc91e9d98)
|    |    |    |    +-GPath.h(md5:653fad32f2870655e6b8258d8de27ed7)
|    |    |    |    +-GTargetBase.h(md5:51b8549c8380874822047d047d953183)
|    |    |    |    +-IConnector.h(md5:736769f1c5f3bb0503c9b297363c326a)
|    |    |    |    +-IConnectorFactory.h(md5:2e9c33a289f680c7601715ca152d7b37)
|    |    |    |    +-IG6Connector.h(md5:051edba8ca923cc6c1a6be66def422dc)
|    |    |    |    +-IG6ConnectorFactory.h(md5:bdad663e543a13ba490ff186865befa2)
|    |    |    |    +-IGCloud.h(md5:e133a2bef6c84029e78951cc8fecabbf)
|    |    |    |    +-IGCloudExtend.h(md5:c0d8c524262330373d622c3f9fb21b86)
|    |    |    |    +-IGFMConnector.h(md5:779f67e259dd46fb4fc59a279ca65f12)
|    |    |    |    +-IGFMConnectorFactory.h(md5:64e8ad631d2890f786fc5b15c0fe5d73)
|    |    |    |    +-ILockStep.h(md5:06e598a3ff1f3e861817e2b7d754b681)
|    |    |    |    +-INameService.h(md5:b26ae7bf53dc1681e3ed996881de18cc)
|    |    |    |    +-INetwork.h(md5:11644a4fbde0713fc88a99ef29d6c437)
|    |    |    |    +-IQRCodeService.h(md5:00cca9a0a6c0e2a9c1e2bcbf39b52424)
|    |    |    |    +-IQueueService.h(md5:afef465dc482edceb5dd90e510477681)
|    |    |    |    +-IRPC.h(md5:742419db526497ce71a0e2e69924308b)
|    |    |    |    +-ITDir.h(md5:fa7979d2b5bd97c5f2bd7a615f0ba3c5)
|    |    |    |    +-LockStepPublicDefine.h(md5:c84b3327dc5c09b9fbb647298a206076)
|    |    |    |    +-QueuePublicDefine.h(md5:f898e3e8feb5a7bb80eab6ed19decfb3)
|    |    |    |    +-TDirPublicDefine.h(md5:ab0c13e7a9daae0c834b706ae657b6f4)
|    |    |    |    +-gcloud_dolphin_errorcode_check.h(md5:2e4b1bb7789d6f9dbc74abe471af33a8)
|    |    +-GCloudLib
|    |    |    +-Android
|    |    |    |    +-GCloud
|    |    |    |    |    +-AndroidManifest.xml(md5:40324e1319b463a92c2a385ede587ae5)
|    |    |    |    |    +-additions.gradle(md5:14c34fce6472c2c21b3409c705976f07)
|    |    |    |    |    +-libs
|    |    |    |    |    |    +-GCloud.jar(md5:a4e218e2e34fd9a9cb81f26f7d2ad577)
|    |    |    |    |    |    +-android-support-v4.jar(md5:a373357c77b3be76070d82bc0f5a503d)
|    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    +-libgcloud.so(md5:eb6112a14a74c09733a41cb353be303d)
|    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    +-libgcloud.so(md5:0aca580b853406bae194c783fdadcc66)
|    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    +-libgcloud.so(md5:733eedcf3e9e51725d343953a98a1d3e)
|    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    +-libgcloud.so(md5:99f303f2c8f237beef7630f5808531b0)
|    |    |    |    |    +-proguard-project.txt(md5:d03a51b7ea9362debee6d74f01305557)
|    |    |    |    |    +-project.properties(md5:bc20596d957d714759ee019b59304d1c)
|    |    |    |    |    +-res
|    |    |    |    |    |    +-xml
|    |    |    |    |    |    |    +-apollo_file_paths.xml(md5:01e9000ee398ea097f4510169e44ed7c)
|    |    |    +-Mac
|    |    |    |    +-libGCloud.dylib(md5:13ac2c9232d9f32cd8c4d94b21fdf83a)
|    |    |    +-Win
|    |    |    |    +-X86
|    |    |    |    |    +-GCloud.dll(md5:cc835e8e71dbad02d0c8a77d9a7d4095)
|    |    |    |    |    +-GCloud.lib(md5:1c87124e256d98f39832b560dbb5f9b3)
|    |    |    |    |    +-GCloud.pdb(md5:7d12cf288b020e4f7e264a406102f4dc)
|    |    |    |    +-X86_64
|    |    |    |    |    +-GCloud.dll(md5:caa0b6fc31a9d19232db2e826ce9139f)
|    |    |    |    |    +-GCloud.lib(md5:8d526001545e7256762e87c36305b1bd)
|    |    |    |    |    +-GCloud.pdb(md5:95799ea073309d8fcc689bdefaace7b2)
|    |    |    +-X64
|    |    |    |    +-GCloud_static.lib(md5:351663c5317d856bf0cb69d8fe1fa3a3)
|    |    |    |    +-atls.lib(md5:8290e7ec9ad8428ca79301d57b573a05)
|    |    |    +-iOS
|    |    |    |    +-GCloud.embeddedframework.zip(md5:98835e7a59046a075db6fcd7f625f1b3)
+-GCloudCore
|    +-GCloudCore.uplugin(md5:9ac3a083ad2bad8fcab3828798dc066f)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-GCloudCore
|    |    |    +-GCloudCore.Build.cs(md5:aae0167d8c5196fda67c96ba62c05b08)
|    |    |    +-GCloudCore_APL.xml(md5:c9b45a72933122d139b26142075ebe28)
|    |    |    +-Private
|    |    |    |    +-GCloudAppLifecycle.h(md5:682fc36cfa1ef43888d31758a7c2c9b1)
|    |    |    |    +-GCloudCoreAppDelegate.cpp(md5:6d871a58403beac6e1bc72887f99e8a9)
|    |    |    |    +-GCloudCoreAppDelegate.h(md5:90621eba5ffeb3c19142ce22a1e0e642)
|    |    |    |    +-GCloudCoreModule.cpp(md5:89e663343c4288171e814358375f9b51)
|    |    |    |    +-iOS
|    |    |    |    |    +-AllLifecycleRegister.h(md5:19c02bd81b2fcbd5b3dae25aa44c3394)
|    |    |    |    |    +-GCloudAppLifecycleListener.h(md5:de8c3606c58d43e1a2e8257279ffd279)
|    |    |    |    |    +-GCloudCoreAppDelegate.mm(md5:92996e28a4ee655ead384cbf15ed658a)
|    |    |    |    |    +-GPixUILifecycle.h(md5:4159a43a610ac89a1cea9cc7b9ce8dbb)
|    |    |    |    |    +-PluginCrosCurlLifecycle.h(md5:6f243dc1d69dbc0f5c78ea058c139c20)
|    |    |    |    |    +-PluginGVoiceLifecycle.h(md5:18e78fe67cd98b7bf078cd432641c294)
|    |    |    |    |    +-PluginMSDKLifecycle.h(md5:94403edd03dca0d42ff014dab0e186a5)
|    |    |    |    |    +-PluginReportLifecycle.h(md5:a88ae3ea54b6a725b85476ec36b6cd30)
|    |    |    +-Public
|    |    |    |    +-GCloudCore
|    |    |    |    |    +-AArray.h(md5:2959978bb0b2c7ac6e5eedcdd3ca7cd3)
|    |    |    |    |    +-AAtomic.h(md5:16518b17c00c8b7b75049cb7a5b03453)
|    |    |    |    |    +-ABase.h(md5:503782df1b444cf1017111ed5093f3fe)
|    |    |    |    |    +-ABaseApplication.h(md5:5726837da3ecd7798772c5ffff49ca74)
|    |    |    |    |    +-ABaseCommon.h(md5:d203cc8c00935f7a18affde3ff3858c2)
|    |    |    |    |    +-ABaseJVM.h(md5:b24145ea9b11250a04cbbaf099847876)
|    |    |    |    |    +-ABasePal.h(md5:f5008986ef997014cfee9c08c9b0aa70)
|    |    |    |    |    +-ACondition.h(md5:2d617ca2da4ee5e5035bd0b3c6093688)
|    |    |    |    |    +-ACritical.h(md5:85f64d857b4bd1298e25dea3798d0ea9)
|    |    |    |    |    +-AData.h(md5:818d150a2884a309ad576510b878c07c)
|    |    |    |    |    +-ADictionary.h(md5:55ba9067b316de4cad750ab9fd463ddc)
|    |    |    |    |    +-AEvent.h(md5:ecfb1e22d4182e38d4aa7ff24fc2734e)
|    |    |    |    |    +-AFile.h(md5:4200ab14f335fe028bcf31e609c7c5d3)
|    |    |    |    |    +-AJniTool.h(md5:336b4f69cb3e8410ce398acec06af277)
|    |    |    |    |    +-ALog.h(md5:6f325de0fcaba2c4c7c64c86391736ed)
|    |    |    |    |    +-AMutex.h(md5:7b1bebc7b7a675e28d0c4ac2c7444eac)
|    |    |    |    |    +-ANumber.h(md5:af919490161b82cedf682af8f7112099)
|    |    |    |    |    +-AObject.h(md5:b85ca4fe764b15ee69a915e2d1e252ed)
|    |    |    |    |    +-APath.h(md5:e8c101d4e678d1dc724713113c1d26a5)
|    |    |    |    |    +-ASelectorManager.h(md5:656201ab6e30b3882c726e854b690cdd)
|    |    |    |    |    +-ASocket.h(md5:b22c4a033567456e5507be1254d699b6)
|    |    |    |    |    +-AString.h(md5:907a756b5fdbef2933e068a1d41bb527)
|    |    |    |    |    +-AStringBuilder.h(md5:3d050043b5abe8fd1e720387d694f4e2)
|    |    |    |    |    +-ASystem.h(md5:f0acc34067fa188dcc8a6567171df1e8)
|    |    |    |    |    +-ATargetBase.h(md5:5004fafd43c4dc8888096cc675709937)
|    |    |    |    |    +-AThreadBase.h(md5:8abe5e6eb59525e4ae64b3cbc6c5511a)
|    |    |    |    |    +-ATime.h(md5:0ea2ae76dbc5e75bc4c4921c8bbec008)
|    |    |    |    |    +-ATimeWin.h(md5:efe4184349a325748258b27688747d59)
|    |    |    |    |    +-ATimer.h(md5:a277c26db74ac9c6fd4cac828167387c)
|    |    |    |    |    +-AValue.h(md5:233cb7f3414e46d63016e3108e717948)
|    |    |    |    |    +-ApolloBuffer.h(md5:a2108181a347fb578ac8470a206ac59a)
|    |    |    |    |    +-ApolloBufferReader.h(md5:3283f3998a99d0d55eb295e7bde8bdd5)
|    |    |    |    |    +-ApolloBufferWriter.h(md5:ab53f8546c61a97760783a22cd77f813)
|    |    |    |    |    +-Application.h(md5:b5c7b98a4c668ded615a976bcaa420ee)
|    |    |    |    |    +-Bundle.h(md5:288ee28860bccaf91c572141e81b222c)
|    |    |    |    |    +-BundleFactory.h(md5:3e8b75e10702cde7c6728ac5754d3874)
|    |    |    |    |    +-COSUploadTask.h(md5:438801d790680c06f3f341afd3e7a782)
|    |    |    |    |    +-Configure.h(md5:36e76e98f5ce8b75ab4eb5c02804e69b)
|    |    |    |    |    +-GCloudAppLifecycle.h(md5:dbe03e22d60700faa82888549952f8f4)
|    |    |    |    |    +-GCloudAppLifecycleObserver.h(md5:75a473029b4e0ca852d40c6d7cf2a589)
|    |    |    |    |    +-GCloudCoreVersion.h(md5:3dd967340b81cd54a21b9724edf22808)
|    |    |    |    |    +-IGCloudCore.h(md5:cff0554048fc8969cc360ebabe269a79)
|    |    |    |    |    +-INetwork.h(md5:111dd93d96a268db3e22bf4e4a104390)
|    |    |    |    |    +-INetworkChecker.h(md5:032d3a53e69b5715b6a05c7da2125226)
|    |    |    |    |    +-IOneTraceService.h(md5:62de211fa38ef4c62c63ce80fd403ad4)
|    |    |    |    |    +-IPlatformObject.h(md5:2b0749cdcd0684daaa5ba361939f1c12)
|    |    |    |    |    +-IPlatformObjectManager.h(md5:8f1bad1eceb02e231cbadce66a6124b1)
|    |    |    |    |    +-IniFile.h(md5:2e7b7ba9e174e8727dcf4878f3c4d4f2)
|    |    |    |    |    +-Operation.h(md5:4fe1f2195335c127bf1ad6ca81118e0e)
|    |    |    |    |    +-OperationQueue.h(md5:75d6fafe1eb70a3737238690713a6d07)
|    |    |    |    |    +-PlatformObject.h(md5:c1e13c859cc61cfd4e0ba239f3158bfa)
|    |    |    |    |    +-PlatformObjectManager.h(md5:3b2aedb5af5acef553736ca2b47735eb)
|    |    |    |    |    +-PlatformObjectRegister.h(md5:e29e58bd97b6bb5a86de261062dc8d85)
|    |    |    |    |    +-PlatformObjectWrapper.h(md5:3322533b878c371cf2b75f880abc3b74)
|    |    |    |    |    +-StatisticTools.h(md5:47726bb235fd7a6ccf100188f7d164f4)
|    |    |    |    |    +-TdrBuf.h(md5:2ad648989012d58191ae1aaf1baa8347)
|    |    |    |    |    +-TdrBufUtil.h(md5:6a9a016905dd70d0ca54de5ba0e7d57e)
|    |    |    |    |    +-TdrError.h(md5:b2aa0263bba154edf22a7daae70f96a4)
|    |    |    |    |    +-TdrIO.h(md5:c2cf654990e6c426996b9d96fe4da027)
|    |    |    |    |    +-TdrObject.h(md5:6f7dadab067eb8ad89720bd1350d906c)
|    |    |    |    |    +-TdrPal.h(md5:8c60dc0c89a8f58aadd24d5997fd67e8)
|    |    |    |    |    +-TdrParse.h(md5:81594d4503c8267636b23fa0c7a4c104)
|    |    |    |    |    +-TdrTLV.h(md5:3232177fd8267167618457a379dc70f4)
|    |    |    |    |    +-TdrTime.h(md5:abc9cb7df2dda6768de56979f373821b)
|    |    |    |    |    +-TdrTypeUtil.h(md5:787d5e7dd8d193f9837617a746701d46)
|    |    |    |    |    +-TdrXml.h(md5:59da83f18d40412f0a6a8dfae07cd60b)
|    |    |    |    |    +-WWW.h(md5:5237714f82401b3b4a03c65cfe36a43b)
|    |    |    |    |    +-ZipArchive.h(md5:79bd0600c82df211c27d0748b3cfd51a)
|    |    |    |    |    +-rapidxml.h(md5:ad61152262a182947c46329aa7d31b8f)
|    |    |    |    |    +-rapidxml_iterators.hpp(md5:15c0baba4b8afd604a83d49bf5e98003)
|    |    |    |    |    +-rapidxml_print.hpp(md5:b54ac3b7cc9e21ed653c646e64b2cefc)
|    |    |    |    |    +-rapidxml_utils.hpp(md5:6a25cd513fd85c5fb02bf9cfbbaf8085)
|    |    |    |    |    +-zconf.h(md5:38986959d2d56fe8430a3a17b182cbe8)
|    |    |    |    |    +-zlib.h(md5:317649926f3383a869c3532d49f9a8b2)
|    |    |    |    +-GCloudCoreModule.h(md5:f79f4cd9cb70dace276f54b29b9ae16f)
|    |    |    |    +-GCloudPluginManager
|    |    |    |    |    +-GCloudAppLifecycleObserver.h(md5:75a473029b4e0ca852d40c6d7cf2a589)
|    |    |    |    |    +-GCloudPluginPublicDefine.h(md5:d38def9208cd7f214b9cdaf87179985a)
|    |    |    |    |    +-IPlugin.h(md5:5120bc2f978f7b8119139ab0e58cbc94)
|    |    |    |    |    +-IPluginManager.h(md5:31b1da66b2f919e877854849d680ecf2)
|    |    |    |    |    +-IPluginService.h(md5:0bfc1a2b5a229169c4c93734b687832b)
|    |    |    |    |    +-IServiceManager.h(md5:f0aa3cdd5e90ec2eacd603bf596f11c1)
|    |    |    |    |    +-PluginBase
|    |    |    |    |    |    +-PluginBase.h(md5:5cde197366f5ed0ee980b4a246e73b3d)
|    |    |    |    |    |    +-PluginBase_Android.h(md5:62d62161f61f1b8e2eb6bb27ba5e807b)
|    |    |    |    |    |    +-PluginBase_iOS.h(md5:356956d39125fa005982c7be15f176f4)
|    |    |    |    |    |    +-PluginInnerDefine.h(md5:c8e2407ecc3d5aadeec079ff7ed6c77b)
|    |    |    |    |    +-Service
|    |    |    |    |    |    +-Account
|    |    |    |    |    |    |    +-AccountHelper.h(md5:bcafd9879f6987996be83dea3b7264d6)
|    |    |    |    |    |    |    +-IServiceAccount.h(md5:5524a01e659248a1b5799cf653aac460)
|    |    |    |    |    |    +-CSScript
|    |    |    |    |    |    |    +-ICSScript.h(md5:7d4c51517148441a54b61784e4c2f62a)
|    |    |    |    |    |    |    +-ICSScriptService.h(md5:327695598f7e3d67afdb8ff28faf44fe)
|    |    |    |    |    |    +-ConfigFile
|    |    |    |    |    |    |    +-IConfigFile.h(md5:e114d205e1a77ccf1fedf17b9f875832)
|    |    |    |    |    |    |    +-IConfigFileService.h(md5:c587ffcafe9da1d3d765f31375658efb)
|    |    |    |    |    |    +-Connector
|    |    |    |    |    |    |    +-IConnectorService.h(md5:9ed1450b6b396c34365935a841534f2d)
|    |    |    |    |    |    +-GTrace
|    |    |    |    |    |    |    +-GTraceClient.h(md5:aa845bcff85400e90fd6cae83b893b11)
|    |    |    |    |    |    |    +-ITraceService.h(md5:2f877a8be84160de31325ec1b58d7fbf)
|    |    |    |    |    |    +-GVoice
|    |    |    |    |    |    |    +-IGVoiceService.h(md5:fd37053cd5c9c2d24b1bfec33ae376b7)
|    |    |    |    |    |    +-Log
|    |    |    |    |    |    |    +-ILogService.h(md5:e5d431d8a5fc8d5de4fa0b31d38720fb)
|    |    |    |    |    |    |    +-ILogger.h(md5:22220adcf95c056af8d385ddfd99541b)
|    |    |    |    |    |    +-MKV
|    |    |    |    |    |    |    +-IKV.h(md5:0c0aedc2bff4333263fdff8b5381ea76)
|    |    |    |    |    |    +-PluginCrosCurl
|    |    |    |    |    |    |    +-ICurlFunc.h(md5:67b343f76a6555f7c6fd6130ead8ea44)
|    |    |    |    |    |    |    +-ICurlFuncQueryService.h(md5:849d5beae0dc0a65c5bef26b134df27d)
|    |    |    |    |    |    |    +-IOpenSSLFunc.h(md5:2cffccf733d32c8c61b961233ef54519)
|    |    |    |    |    |    |    +-IOpenSSLFuncQueryService.h(md5:13948a826f7d7ef4b85f672fbbb22c7a)
|    |    |    |    |    |    |    +-PluginCrosCurlLifecycle.h(md5:433a1079f9143f5408381ac538937a39)
|    |    |    |    |    |    |    +-crosCurl.h(md5:54ec327d84e5f4303934b454ee86d8e4)
|    |    |    |    |    |    |    +-crosCurlDefine.h(md5:ab9bc7834a4b8272d6d4207a3815612e)
|    |    |    |    |    |    +-RemoteConfig
|    |    |    |    |    |    |    +-IRemoteConfig.h(md5:329785cf074798ee3bb8682cecf5595b)
|    |    |    |    |    |    |    +-IRemoteConfigService.h(md5:8d7c21ad7b37a108846018b56153c86c)
|    |    |    |    |    |    +-Report
|    |    |    |    |    |    |    +-DeviceInfoDefine.h(md5:ab52fab8f85d60aacba850da828eeb3b)
|    |    |    |    |    |    |    +-GCloudCoreReporter.h(md5:f415fd2d5d89128ae844bdca7b5e1ac0)
|    |    |    |    |    |    |    +-IReportService.h(md5:7f585b21afe80750568c57a38f1f2043)
|    |    |    |    |    |    +-ThreadPool
|    |    |    |    |    |    |    +-IFdListener.h(md5:564c577ecd19cb5e546fcb4c9363794c)
|    |    |    |    |    |    |    +-IThreadPool.h(md5:0e0ba1ff38de329d8ecb68abd95640af)
|    |    |    |    |    |    |    +-IThreadPoolService.h(md5:15c990812913f84c5682a710e8b49bf8)
|    |    |    |    |    |    |    +-IThreadRunnable.h(md5:9b71d38479138f45dfd3a220747c4d89)
|    |    +-GCloudCoreLib
|    |    |    +-Android
|    |    |    |    +-GCloudCore
|    |    |    |    |    +-AndroidManifest.xml(md5:131503778178cb64683db943ac841c67)
|    |    |    |    |    +-additions.gradle(md5:93d3f09b3c2d1d41fd84672fb96124f0)
|    |    |    |    |    +-libs
|    |    |    |    |    |    +-GCloudCore.jar(md5:88e46da357dca0e24b191aabfc51198f)
|    |    |    |    |    |    +-android-support-v4.jar(md5:a373357c77b3be76070d82bc0f5a503d)
|    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    +-libgcloudcore.so(md5:5ae6d8f4b56c8402fd37087e8bec01c5)
|    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    +-libgcloudcore.so(md5:5f7e264d34acb81c7549be7e087d5072)
|    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    +-libgcloudcore.so(md5:e0a7b430d0467396ee994d50059c36ec)
|    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    +-libgcloudcore.so(md5:9477e4faf7f900458be8361ec8d19670)
|    |    |    |    |    +-proguard-project.txt(md5:a8c2b66e73339aa4fc2ab626d8af3af7)
|    |    |    |    |    +-project.properties(md5:bc20596d957d714759ee019b59304d1c)
|    |    |    |    |    +-res
|    |    |    |    |    |    +-values
|    |    |    |    |    |    |    +-string.xml(md5:d929a4e0fed3f155ddd7eb331e5afd42)
|    |    |    |    |    |    +-xml
|    |    |    |    |    |    |    +-network_security_config.xml(md5:030636eb2195aaa199fc452c43581b4a)
|    |    |    +-Mac
|    |    |    |    +-libGCloudCore.dylib(md5:4257bea27d1b9d8a00a3ba6bf6566c5b)
|    |    |    +-Win
|    |    |    |    +-X86
|    |    |    |    |    +-GCloudCore.dll(md5:cca654932215417d246562e08b917313)
|    |    |    |    |    +-GCloudCore.exp(md5:5e02acc4574a03aee58459ec48e3d6b2)
|    |    |    |    |    +-GCloudCore.lib(md5:8775101cfac92f2378c4f2964636c31d)
|    |    |    |    |    +-GCloudCore.pdb(md5:3c66e497d8e1e5acb796f527e4a26d55)
|    |    |    |    |    +-vc140.pdb(md5:c14a549c9f5c706ea32161f40bb7ed12)
|    |    |    |    +-X86_64
|    |    |    |    |    +-GCloudCore.dll(md5:e59d62dbfed4882ec401b51cf367631c)
|    |    |    |    |    +-GCloudCore.exp(md5:3de8b4bffa852d33e9d366d20d30d566)
|    |    |    |    |    +-GCloudCore.lib(md5:5f8bc7a0f9f9daa62f5db800531f371a)
|    |    |    |    |    +-GCloudCore.pdb(md5:2e94fb107b321a4cc1b96609821dec2a)
|    |    |    |    |    +-vc140.pdb(md5:d17478f7afd8a632bbd423fa6dded0d1)
|    |    |    +-X64
|    |    |    |    +-GCloudCore_static.lib(md5:44497e73b7ee9c2046447eced76a5915)
|    |    |    +-iOS
|    |    |    |    +-GCloudCore.embeddedframework.zip(md5:ecc58027896d6743bf1b6884d5d56559)
|    |    +-GCloudInfo(md5:f90e0c8324d1479592739fa49a039deb)
+-GVoice
|    +-GVoice.uplugin(md5:074dfe6ad9f106df6d7207989bb29612)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-GVoice
|    |    |    +-GVoice.Build.cs(md5:d2ce97c1de20eecc8de44d1641853413)
|    |    |    +-GVoice_APL.xml(md5:3d7d51fc8103ea2446723d78e3652a14)
|    |    |    +-Private
|    |    |    |    +-GVoice.cpp(md5:ab509d2e292a473c80792da52997bee2)
|    |    |    |    +-GVoiceAppDelegate.cpp(md5:a74ee60ab5ad68851df21b9e81b956fb)
|    |    |    |    +-GVoiceAppDelegate.h(md5:2c6ed1c8e692b84dc56f9aaf45293556)
|    |    |    |    +-iOS
|    |    |    |    |    +-GVoiceAppDelegate.mm(md5:7ebd802c1ca9073f44f268eeb0319741)
|    |    |    +-Public
|    |    |    |    +-GCloudVoiceErrno.h(md5:5f9163019d6735dd0cc9244e35b3d041)
|    |    |    |    +-GCloudVoiceVersion.h(md5:ee1fae139378942785463d3cb39730b2)
|    |    |    |    +-GVoice.h(md5:11b6175e503b2dc79f8c5086ac4ac582)
|    |    |    |    +-IGCloudVoiceEngine.h(md5:605429cb7988f5048974bd664368d414)
|    |    |    |    +-IGCloudVoiceEngineNotify.h(md5:6551068643b3e85105ae9d7ad5fedeec)
|    |    |    |    +-IGCloudVoiceExtension.h(md5:82cb7dc3f0fe054ae62bc4e3f1215b25)
|    |    |    +-additions.gradle(md5:14c34fce6472c2c21b3409c705976f07)
|    |    +-GVoiceLib
|    |    |    +-Android
|    |    |    |    +-assets
|    |    |    |    |    +-GCloudVoice
|    |    |    |    |    |    +-cldnn_spkvector.mnn(md5:c40dc24bb7b8f780906b84ffc8eb0672)
|    |    |    |    |    |    +-config.json(md5:6bd0a788a684dee567e247cb7b110827)
|    |    |    |    |    |    +-decoder_v4_small.nn(md5:23d4366963047bfb03941e23222aea50)
|    |    |    |    |    |    +-encoder_v4_small.nn(md5:73a2912df2386c79f4a680c753852a49)
|    |    |    |    |    |    +-libgvoicensmodel.bin(md5:3dd9e79d008513dfeb9369aa1845dcd7)
|    |    |    |    |    |    +-libwxvoiceembed.bin(md5:282b06afa1a0f5c07e73b87a0756fe95)
|    |    |    |    |    |    +-wave_3d_data.bin(md5:7746ba475230edbc56123ee36f7b9329)
|    |    |    |    |    |    +-wave_dafx_data.bin(md5:7746ba475230edbc56123ee36f7b9329)
|    |    |    |    +-libs
|    |    |    |    |    +-GVoice.jar(md5:0a683ee8e48354088c63ffe6cd2d1f4c)
|    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    +-libGVoice.so(md5:dbb82c779e95741ab551824a39d5fe00)
|    |    |    |    |    |    +-libGvoiceNN.so(md5:64d4d6934435c361419b1ebc34f3ae13)
|    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    +-libGVoice.so(md5:2e84a329d1326d75cabc47ff798b89b6)
|    |    |    |    |    |    +-libGvoiceNN.so(md5:c854f76396b0a8547e18c6e887f5c3f3)
|    |    |    |    |    +-wwise
|    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    +-libGVoicePlugin.so(md5:a626c96c4ea8adb5c11d36af7e8142a0)
|    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    +-libGVoicePlugin.so(md5:150d6ee952e94e64a61fb702fdd12763)
|    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    +-libGVoicePlugin.so(md5:4517cfd61ce17702750ffd67e36a3721)
|    |    |    |    |    +-x86
|    |    |    |    |    |    +-libGVoice.so(md5:f99ecfd74df9e8cc3d142b010374fc68)
|    |    |    |    |    +-x86_64
|    |    |    |    |    |    +-libGVoice.so(md5:c594ad5a1520954945ab8ea17c57a91f)
|    |    |    +-Mac
|    |    |    |    +-libGVoice.a(md5:e4374c5365da3ef8936baeeec75a8ba8)
|    |    |    +-Win
|    |    |    |    +-X86
|    |    |    |    |    +-GVoice.dll(md5:d02fa7d832762c987ccbf616b840edd7)
|    |    |    |    |    +-GVoice.lib(md5:4f2c24e55dff6a5260cbe72b801a1f35)
|    |    |    |    |    +-GVoice.pdb(md5:03a3a61d52a13973c816896b564e323a)
|    |    |    |    |    +-config.json(md5:02437dfad07fa562a738ce79337f5696)
|    |    |    |    |    +-gvoice_decoder.md(md5:a5667b3630270b3dcd62c19effe6a818)
|    |    |    |    |    +-gvoice_encoder.md(md5:8ae4a6690ab579fc91c9b66cf496a7e7)
|    |    |    |    |    +-libgvoicensmodel.bin(md5:3dd9e79d008513dfeb9369aa1845dcd7)
|    |    |    |    |    +-libwxvoiceembed.bin(md5:282b06afa1a0f5c07e73b87a0756fe95)
|    |    |    |    |    +-pthreadVC2.dll(md5:f15437966f35398921004fae059c59f2)
|    |    |    |    |    +-wave_3d_data.bin(md5:7746ba475230edbc56123ee36f7b9329)
|    |    |    |    |    +-wave_dafx_data.bin(md5:7746ba475230edbc56123ee36f7b9329)
|    |    |    |    +-X86_64
|    |    |    |    |    +-GVoice.dll(md5:1d779c8d2ecf141113fae52d42d42e0f)
|    |    |    |    |    +-GVoice.lib(md5:515c2e86540834c848042a5502fe4d6a)
|    |    |    |    |    +-GVoice.pdb(md5:089be67e4d2ab4b9dbd2e9a10a8ca020)
|    |    |    |    |    +-config.json(md5:02437dfad07fa562a738ce79337f5696)
|    |    |    |    |    +-gvoice_decoder.md(md5:a5667b3630270b3dcd62c19effe6a818)
|    |    |    |    |    +-gvoice_encoder.md(md5:8ae4a6690ab579fc91c9b66cf496a7e7)
|    |    |    |    |    +-libgvoicensmodel.bin(md5:3dd9e79d008513dfeb9369aa1845dcd7)
|    |    |    |    |    +-libwxvoiceembed.bin(md5:282b06afa1a0f5c07e73b87a0756fe95)
|    |    |    |    |    +-pthreadVC2.dll(md5:b131c071a3f3cb4865ebda1247c1c8c7)
|    |    |    |    |    +-wave_3d_data.bin(md5:7746ba475230edbc56123ee36f7b9329)
|    |    |    |    |    +-wave_dafx_data.bin(md5:7746ba475230edbc56123ee36f7b9329)
|    |    |    +-iOS
|    |    |    |    +-GVoice_dylib.embeddedframework.zip(md5:47a286967146f6abd2e7718824d5ba58)
|    |    |    |    +-wwise
|    |    |    |    |    +-GVoicePluginFactory.h(md5:ca56f2147ec266905d9b77ceaad19e58)
|    |    |    |    |    +-libGVoicePlugin.a(md5:14db700a5782deb0ea8c72af5c817a87)
+-MSDKPIXBeacon
|    +-MSDKPIXBeacon.uplugin(md5:06efe195dee02558df45f2367b5cc696)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXBeacon
|    |    |    +-MSDKPIXBeacon.Build.cs(md5:15712704f527e35431feae2be0834a80)
|    |    |    +-MSDKPIXBeacon_UPL.xml(md5:d0f645179194fd2480ef9c1fda6a8a22)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXBeacon.cpp(md5:f5f0406db92d3bb94c6fd115997612d8)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXBeacon.h(md5:276d7ac9ca4f0e790ea680d51d37d3b3)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-beacon
|    |    |    |    |    |    +-AndroidManifest.xml(md5:49b5213e513cccc9f48b9d4d1e565c13)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:8bad2a86b48484905c00f1d02f29baaa)
|    |    |    |    |    |    +-additions.gradle(md5:605788888ec0aa0827cd77caa5a4ffed)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    |    +-libqimei.so(md5:c170cabb696d21e1ef648bd6a991d201)
|    |    |    |    |    |    |    |    +-libqmp.so(md5:293e08d0772ec84691b167ff731d4652)
|    |    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    |    +-libqimei.so(md5:7cf96ce9928016cbcaf05a82ac383935)
|    |    |    |    |    |    |    |    +-libqmp.so(md5:d0e0cc86f86409d4b4100860c64ac06d)
|    |    |    |    |    |    |    +-beacon-android-release-4.2.84.3-official.jar(md5:8bc1c25079f18fc0aad30e1ddaf8f086)
|    |    |    |    |    |    |    +-msdkpix-beacon.jar(md5:c584f2fc5763f53921d81541802d8085)
|    |    |    |    |    |    |    +-qimei-1.2.17.2.jar(md5:ca78beee6167b61026c4981dcc66aef4)
|    |    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    |    +-libqimei.so(md5:4bd984fb5059897dbb7ba5becc3b8e16)
|    |    |    |    |    |    |    |    +-libqmp.so(md5:72e20c936a3f7b03a89bedf4ab2e31dd)
|    |    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    |    +-libqimei.so(md5:cc8ce80ee0daf218b99afcd0fc8d9ebb)
|    |    |    |    |    |    |    |    +-libqmp.so(md5:934127a6ff5f10906b036275ea219063)
|    |    |    |    |    |    +-project.properties(md5:404765ee5cc019975e97b7e6ba7afdf0)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXBeacon
|    |    |    |    |    |    +-MSDKPIXBeacon.embeddedframework.zip(md5:7d70ecd2180fa08cde569b380b190b68)
|    |    |    |    |    +-Third
|    |    |    |    |    |    +-MSDKPIXBeacon
|    |    |    |    |    |    |    +-BeaconAPI_Base.embeddedframework.zip(md5:a057134519a25456585cfc8aebbe69b6)
|    |    |    |    |    |    |    +-BeaconId.embeddedframework.zip(md5:b8cc9070cef07d0afa06a7d2ad9219e5)
|    |    |    |    |    |    |    +-QimeiSDK.embeddedframework.zip(md5:82d645e26eabd4105edf9530b0121126)
+-MSDKPIXBugly
|    +-MSDKPIXBugly.uplugin(md5:4f4590719e95a03d360c39fa8e77aaf7)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXBugly
|    |    |    +-MSDKPIXBugly.Build.cs(md5:ef1a356c7a082f6b3d832c8cb25fe400)
|    |    |    +-MSDKPIXBugly_UPL.xml(md5:c6bc96ffa6d2b406489f33c3c1ee8dfb)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXBugly.cpp(md5:a277af2c0fd69d0293b30db4fd6c20f2)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXBugly.h(md5:41966cbccab3c73316ab5bd30b3feb01)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-bugly
|    |    |    |    |    |    +-AndroidManifest.xml(md5:a4ab0248096683afbd0d56a8838fc5cc)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:8bad2a86b48484905c00f1d02f29baaa)
|    |    |    |    |    |    +-additions.gradle(md5:ffa49636af5c5b43c5fcd3c9ad27a9a8)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    |    +-libBugly_Native.so(md5:ccae725814f13635e8d443943711bdfa)
|    |    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    |    +-libBugly_Native.so(md5:c72a9d4249e7eac3e934850e09b2a6e3)
|    |    |    |    |    |    |    +-bugly_crash_release.jar(md5:05d6b87c03f7c45823c9f4106650edda)
|    |    |    |    |    |    |    +-bugly_game_agent_release.jar(md5:8aa92baaf54891f9ee46a18893c128ce)
|    |    |    |    |    |    |    +-msdkpix-bugly.jar(md5:4e031f63dcf6dae7ec98968348b40aff)
|    |    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    |    +-libBugly_Native.so(md5:aacc92e50091235b8fae9e5c47d47dda)
|    |    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    |    +-libBugly_Native.so(md5:6d1d14b2d6bb4e8e2bc02e6422b4c37a)
|    |    |    |    |    |    +-project.properties(md5:6047dbe71bdb53ab5cb4047da7608ef4)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXBugly
|    |    |    |    |    |    +-MSDKPIXBugly.embeddedframework.zip(md5:d29f666b0e3803592017a9245d284730)
|    |    |    |    |    +-Third
|    |    |    |    |    |    +-MSDKPIXBugly
|    |    |    |    |    |    |    +-Bugly.embeddedframework.zip(md5:96541d4ed0833ba1a17dd97fac296e26)
|    |    |    |    |    |    |    +-BuglyBridge
|    |    |    |    |    |    |    |    +-BuglyAgent.h(md5:c521d368bda5ac89eb1204531045f855)
|    |    |    |    |    |    |    |    +-BuglyAgentV2.h(md5:1125b92748acf860827cae64e8f62564)
|    |    |    |    |    |    |    |    +-BuglyBridge.h(md5:51b3abd3c51277b12be05bd5b3249f3d)
|    |    |    |    |    |    |    |    +-libBuglyBridge.a(md5:7b47ac8ffbbc7ef44469c1c3a3e8126e)
+-MSDKPIXCore
|    +-MSDKPIXCore.uplugin(md5:ddc5fcc6d18ef728a53b1e1a3ea23e00)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXCore
|    |    |    +-MSDKPIXCore.Build.cs(md5:8f3798851bb9da3bc1d5b08c4f3de1d8)
|    |    |    +-MSDKPIXCore_UPL.xml(md5:3be12c1de01a7d23d30e73a022ebaf33)
|    |    |    +-Private
|    |    |    |    +-.msdk_core(md5:f90dedece38170fdbafb21305cb9dfea)
|    |    |    |    +-MSDKAccount.cpp(md5:d5e48b680e083842e0b6e7e7d1a36709)
|    |    |    |    +-MSDKCrash.cpp(md5:d69595890bd1e71cee9b1035eef786f7)
|    |    |    |    +-MSDKDefine.cpp(md5:c5e7fe425c2eaf9c8ab288fcfac519dd)
|    |    |    |    +-MSDKExtend.cpp(md5:e8a7043d950e9e883c9c0b2faa0129b3)
|    |    |    |    +-MSDKFriend.cpp(md5:b327c5ba73fc6be67b48eb6c997bac9c)
|    |    |    |    +-MSDKGame.cpp(md5:a9b9d3d0a9cc88cd9d7da32194904375)
|    |    |    |    +-MSDKGroup.cpp(md5:d7a66fea57f3622c3f43c8104a017045)
|    |    |    |    +-MSDKLBS.cpp(md5:2a9be7fcc9838e0cbc4940fc4f6e952c)
|    |    |    |    +-MSDKLog.cpp(md5:fe6de901fe6085a4da52030254d7f942)
|    |    |    |    +-MSDKLogin.cpp(md5:49ee49d770894d2b4dc666bde8e516a5)
|    |    |    |    +-MSDKNotice.cpp(md5:e5add9317eda3d873fc41b96d0505c77)
|    |    |    |    +-MSDKPIXCore.cpp(md5:d25bdc1853323a0eabf12ba6a9da9a1f)
|    |    |    |    +-MSDKPush.cpp(md5:925e6eb8b37a6da3d20c0610746d0b5b)
|    |    |    |    +-MSDKReport.cpp(md5:b09d9427acbc33640bcbc9fd1de4f889)
|    |    |    |    +-MSDKWebView.cpp(md5:694e77cd71bea1116ff8cb14908cc26f)
|    |    |    |    +-iOS
|    |    |    |    |    +-IOSAppDelegate+MSDK.mm(md5:59aaf7759fe30154a13af5c43e8b885e)
|    |    |    +-Public
|    |    |    |    +-.msdk_pthread(md5:587bf4de0721b6e31a0a5f9be9ec7cd6)
|    |    |    |    +-.msdk_sched(md5:a288e2b1c1674b226da7e1663a8e4b66)
|    |    |    |    +-.msdk_semaphore(md5:055ca7bda23c3d3bcac4bf631e7ab5e6)
|    |    |    |    +-IServiceAccount.h(md5:608a4368b457feb5137fd539a00c52bc)
|    |    |    |    +-MSDK.h(md5:fcd6e2e9b456dd1d07c73fe1de13eb3e)
|    |    |    |    +-MSDKAccount.h(md5:548e7dc0bd55db5eae0a3d0a08790027)
|    |    |    |    +-MSDKCompatLayer.h(md5:ecb1eab633a166c9f7ae65768b3a5b88)
|    |    |    |    +-MSDKConfig.h(md5:939bc376a9e5c5d26b889bd2a32e1ac3)
|    |    |    |    +-MSDKCrash.h(md5:f0952f0a918f959540bd64aa66f42d0d)
|    |    |    |    +-MSDKDefine.h(md5:4f416b557963d9bd52f0448fdb4c51a1)
|    |    |    |    +-MSDKError.h(md5:8f50d5ed9f7b55f01b04e6eb4b4996a4)
|    |    |    |    +-MSDKExtend.h(md5:3613979b0fdcd39fd91646de49dc91dd)
|    |    |    |    +-MSDKFriend.h(md5:d5b1421102f17ab32106220da462e1a9)
|    |    |    |    +-MSDKGame.h(md5:75341557c0e17970dc8819d74ad195f5)
|    |    |    |    +-MSDKGroup.h(md5:58c7bdd883064dddbb2675565fc1ec06)
|    |    |    |    +-MSDKJsonManager.h(md5:312d3e3e11f91d237e4e442058a0f434)
|    |    |    |    +-MSDKJsonReader.h(md5:c588d65d1de01ce326a2aaa778ada8d5)
|    |    |    |    +-MSDKJsonWriter.h(md5:2b3e45a16e5d8021ba028d2ecaeb423a)
|    |    |    |    +-MSDKLBS.h(md5:e447bbe545379425c57ef370c3c72195)
|    |    |    |    +-MSDKLifeCycleAble.h(md5:2ad5a58056a955980fb22e54a28fea31)
|    |    |    |    +-MSDKLifeCycleManager.h(md5:84cb6e982343a7a821b4baae70372d39)
|    |    |    |    +-MSDKLog.h(md5:9b125af2b22784eb1d6abc4d04eb088f)
|    |    |    |    +-MSDKLogUtil.h(md5:c556f0eddc3f5d150bf7a4962a661924)
|    |    |    |    +-MSDKLogin.h(md5:f378f246152dd202cfc2bd68bf8bb74d)
|    |    |    |    +-MSDKMacroExpand.h(md5:a3387d7c29d22a3769408c820fa10e06)
|    |    |    |    +-MSDKMacros.h(md5:6ad1ae3540446044fa3611bb03f3d29f)
|    |    |    |    +-MSDKMutex.h(md5:d98ab35f20937ab88ffcdbac38a2329c)
|    |    |    |    +-MSDKNotice.h(md5:132f87fa4fc329a19ed1462f6d2b51a7)
|    |    |    |    +-MSDKObserverManager.h(md5:c1c5c1d16f0c1adacbc31b5f919b18dd)
|    |    |    |    +-MSDKPIXApplicationDelegate.h(md5:d167c70ee194bc85dd514eea16c909ac)
|    |    |    |    +-MSDKPIXCore.h(md5:aa99c0841f39cd24702bdfc394a9e02f)
|    |    |    |    +-MSDKPIXUtilsIOS.h(md5:baad371213613b2ffa5f5e2c0e3b2da8)
|    |    |    |    +-MSDKPush.h(md5:02401556f9cc3a6a8519e660b86cacb8)
|    |    |    |    +-MSDKRename.h(md5:1eb3611fbe15271104355dabcd3e1fcd)
|    |    |    |    +-MSDKReport.h(md5:682eb63af453452acb2003c97e7f7a21)
|    |    |    |    +-MSDKSensitive.h(md5:c54aee7f675d7c7b6f6d4623462f698b)
|    |    |    |    +-MSDKSensitivityDelegate.h(md5:d911d1692035ed22125a78c216e6d996)
|    |    |    |    +-MSDKSingleton.h(md5:0699f2c7dd6ec873ef2e419b8d2408e8)
|    |    |    |    +-MSDKTools.h(md5:4bf1fd38169aad895f9972c72b84b652)
|    |    |    |    +-MSDKUtils.h(md5:d380f82628f55a395d4caf3f8fbe4cf5)
|    |    |    |    +-MSDKWebView.h(md5:a16222014d467f70ed46bf7da32bfd93)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-assets
|    |    |    |    |    |    +-MSDKBuglyConfig.json(md5:b5b82f0a2ed7c2a60d005448c7c8e606)
|    |    |    |    |    |    +-MSDKConfig.ini(md5:90dd1c23475798dd419885076f35493a)
|    |    |    |    |    |    +-MSDKRetMsg.json(md5:7a97f04c5845c3c99577d5b6b76b6d1d)
|    |    |    |    |    +-msdkpix-core
|    |    |    |    |    |    +-AndroidManifest.xml(md5:768610316d07f72991e2ff54b6b2a5d3)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:8bad2a86b48484905c00f1d02f29baaa)
|    |    |    |    |    |    +-additions.gradle(md5:ffa49636af5c5b43c5fcd3c9ad27a9a8)
|    |    |    |    |    |    +-assets
|    |    |    |    |    |    |    +-msdk_permission_content.html(md5:7a020054dad3a6c6ac30aed7363ce7e2)
|    |    |    |    |    |    |    +-msdk_policy_content.html(md5:3b2c3d68805c04c1611ba1bf91c69741)
|    |    |    |    |    |    |    +-msdkpix
|    |    |    |    |    |    |    |    +-msdkpix(md5:bd98054dd0347885ef8f95744661d17e)
|    |    |    |    |    |    |    +-popup
|    |    |    |    |    |    |    |    +-MSDKPopupLocal.config(md5:6eccb05d613176b421e83e1859f72fb7)
|    |    |    |    |    |    |    |    +-MSDKPopup_0_2_2_0bba847357668ad690aef018a6771fa6.html(md5:0bba847357668ad690aef018a6771fa6)
|    |    |    |    |    |    |    |    +-MSDKPopup_0_2_2_f2e8f5050690e378955d1278b331cfb2.html(md5:f2e8f5050690e378955d1278b331cfb2)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-MSDKPIXTxAdapter.jar(md5:c12888b4acf59f2c45001415ec8ec2fe)
|    |    |    |    |    |    |    +-MSDKPopup.jar(md5:eefe108b8f08e1fa7fd74eae6ac077e6)
|    |    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    |    +-libMSDKPIXCore.so(md5:9f1e1cc81e780ec11629035b4ae95bda)
|    |    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    |    +-libMSDKPIXCore.so(md5:7dd5a16e23a296f803e38f797834ea41)
|    |    |    |    |    |    |    +-msdkpix-core.jar(md5:e2cb2ba458ca631feb4b669a227abc3a)
|    |    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    |    +-libMSDKPIXCore.so(md5:d013600f71fa242a2f3a09fbd633ebb2)
|    |    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    |    +-libMSDKPIXCore.so(md5:111d4532963e086daf451f52b674661a)
|    |    |    |    |    |    +-proguard-project.txt(md5:d41d8cd98f00b204e9800998ecf8427e)
|    |    |    |    |    |    +-project.properties(md5:404765ee5cc019975e97b7e6ba7afdf0)
|    |    |    |    |    |    +-res
|    |    |    |    |    |    |    +-anim
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_enter_anim.xml(md5:562af5dd9eb264dfdc2f49da270257eb)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_exit_anim.xml(md5:54c73dc72c73f30cade21050d7fdea62)
|    |    |    |    |    |    |    +-drawable
|    |    |    |    |    |    |    |    +-msdk_policy_bg.png(md5:66268dd5cfd7614afb903c799aa0e858)
|    |    |    |    |    |    |    |    +-msdk_policy_confirm_button_bg.xml(md5:086ed3b6dbcf01085da19361b7bae8a0)
|    |    |    |    |    |    |    |    +-msdk_policy_confirm_button_bg_pressed.xml(md5:3c49cd450593c41e60e4ea86f5f1780b)
|    |    |    |    |    |    |    |    +-msdk_policy_confirm_button_selector.xml(md5:13843ce67a8c53f3727707bc2c2a8508)
|    |    |    |    |    |    |    |    +-msdk_policy_dialog_bg.png(md5:66268dd5cfd7614afb903c799aa0e858)
|    |    |    |    |    |    |    |    +-msdk_policy_dialog_grey_bg.xml(md5:4030e3f729a3246d25f75cbde22f4652)
|    |    |    |    |    |    |    |    +-msdk_policy_grey_bg.xml(md5:26541b32aedda9a96b8aaa69497e3778)
|    |    |    |    |    |    |    |    +-msdk_policy_layout_button_group_bg.xml(md5:13c9f57876e65bd21f0f2c8693891333)
|    |    |    |    |    |    |    |    +-msdk_policy_layout_inner_window_bg.xml(md5:7458f9d58b35622af1d11a1edbb54208)
|    |    |    |    |    |    |    |    +-msdk_policy_other_button_bg.xml(md5:fed3d0e2b83b2ad0759717ea7e66a4c1)
|    |    |    |    |    |    |    |    +-msdk_policy_other_button_bg_pressed.xml(md5:9e517287f8bd78e3bb61d84f5278b733)
|    |    |    |    |    |    |    |    +-msdk_policy_other_button_selector.xml(md5:2beb31b799462568c06f54073f7373e6)
|    |    |    |    |    |    |    |    +-msdk_popup_back.png(md5:17dd081a7cb72b98a6007797c2d6d7b3)
|    |    |    |    |    |    |    |    +-msdk_popup_close.png(md5:f7d90894ad6e4054f9240780750c8536)
|    |    |    |    |    |    |    |    +-msdk_popup_refresh.png(md5:b11646bb18f4c5b88facee7d96a19b72)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_button_bg.xml(md5:0a1c31581bfe517e9bba47eb92014179)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_other_button_bg.xml(md5:7c3f76aaa17bea437ec2c0d1c9cccb35)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_window_write_bg.xml(md5:9a6b6490746e4196d6a715e23fb54f14)
|    |    |    |    |    |    |    +-drawable-land
|    |    |    |    |    |    |    |    +-msdk_policy_bg.png(md5:f4dd9b6f8f927ffb5fb69f2901871839)
|    |    |    |    |    |    |    +-layout
|    |    |    |    |    |    |    |    +-activity_msdk_policy.xml(md5:91ffa7a3e3afa12789fac1daf7542c9c)
|    |    |    |    |    |    |    |    +-activity_msdk_policy_v2.xml(md5:00030c07990c0ae0d6b675af6da7e17e)
|    |    |    |    |    |    |    |    +-msdk_permission_layout.xml(md5:4bd3122e0d3fd75448fc243614bac23c)
|    |    |    |    |    |    |    |    +-msdk_permission_layout_second.xml(md5:c614652b2ce9ad2ed1af855a3c699b22)
|    |    |    |    |    |    |    |    +-msdk_policy_layout.xml(md5:6edd5ae96e8d87cdfd3124faff6b8ca4)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_fragment_layout.xml(md5:109186b0c35fd3a4144773636f1b7d0e)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_policy_layout.xml(md5:35187cb0ce87a37143f899b3e1c5241e)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_richtext_layout.xml(md5:83840cb0c6e8c9cb09900c3e7684b401)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_webview_layout.xml(md5:0795d0264e1e89407db3753dabe01cf3)
|    |    |    |    |    |    |    +-layout-land
|    |    |    |    |    |    |    |    +-msdk_permission_layout.xml(md5:3dbbac7da732d3bba7f1c5a7c009bb22)
|    |    |    |    |    |    |    |    +-msdk_permission_layout_second.xml(md5:6ec6b6bdbb1a6360317eb8ae44697440)
|    |    |    |    |    |    |    |    +-msdk_policy_layout.xml(md5:e670d7b2599130eaec92d88a7b7dee51)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_policy_layout.xml(md5:01f72159d2ac918c0546bb2be7885471)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_richtext_layout.xml(md5:399063d206e038ee7017def8398f282e)
|    |    |    |    |    |    |    |    +-msdkpopup_dialog_webview_layout.xml(md5:0795d0264e1e89407db3753dabe01cf3)
|    |    |    |    |    |    |    +-values
|    |    |    |    |    |    |    |    +-values.xml(md5:68af79e17b10e6f2f45636ab6db66a96)
|    |    |    |    |    |    |    +-values-land
|    |    |    |    |    |    |    |    +-values-land.xml(md5:6acc353b6fb4a37b442583c64536275c)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXCore
|    |    |    |    |    |    +-MSDKPIXCore.embeddedframework.zip(md5:7b4eecf46e13ea1a8c1f74c1d36a6184)
|    |    |    |    |    |    +-MSDKPIXSensitivity.embeddedframework.zip(md5:fac77ff64db3a6e9422cbe9c06403f72)
|    |    |    |    |    +-Third
|    |    |    |    |    |    +-MSDKPIXCore
|    |    |    |    |    |    |    +-MSDKPolicy.embeddedframework.zip(md5:fae233cfbaa9f1b08991b815a241ee7b)
|    |    |    |    |    |    |    +-MSDKPopup.embeddedframework.zip(md5:d8354676b240fba3883de5a527b8d21a)
+-MSDKPIXLBS
|    +-MSDKPIXLBS.uplugin(md5:7babb133c3e0ca6abed3871b54a979b5)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXLBS
|    |    |    +-MSDKPIXLBS.Build.cs(md5:5a1cc859d9a7ac80f59f419e82e5967f)
|    |    |    +-MSDKPIXLBS_UPL.xml(md5:345b62ee279ad839757a534c3fb9e65b)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXLBS.cpp(md5:22f870b1a7c4d1eaccb9b78f7516ba19)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXLBS.h(md5:4a658f585ed2c7135966d9e5c2097d24)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-lbs
|    |    |    |    |    |    +-AndroidManifest.xml(md5:43ed763d5ce8b6fe4e9a3623ae3cb016)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:86037dac5038d89062843b61d5cfa615)
|    |    |    |    |    |    +-additions.gradle(md5:4a149f0a2f5fbf8eb12a6684979b0bd5)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-msdkpix-lbs.jar(md5:6f3b0e0861ea1673d5fac2e7a552d1b6)
|    |    |    |    |    |    +-project.properties(md5:06eb8ac23aa83301d2079053cb676fdd)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXLBS
|    |    |    |    |    |    +-MSDKPIXLBS.embeddedframework.zip(md5:ac7a6486256f358a7fd9516b13e7c8c6)
+-MSDKPIXQQ
|    +-MSDKPIXQQ.uplugin(md5:fda045cf3d360fe86808269481cd63dd)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXQQ
|    |    |    +-MSDKPIXQQ.Build.cs(md5:6d2dbe0b7ed452e8e52a7881d15dde0c)
|    |    |    +-MSDKPIXQQ_UPL.xml(md5:575e32964f8e245baabfabcdf98d1443)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXQQ.cpp(md5:7ef6fceb6f2899e2c8e7b37b614950a3)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXQQ.h(md5:ba742c3be3927aee5782dbc2ebfb723f)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-qq
|    |    |    |    |    |    +-AndroidManifest.xml(md5:b45257e02dc0550af22c0d03d7a52f58)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:d9a5f484e80d899d270b6be02af46eeb)
|    |    |    |    |    |    +-additions.gradle(md5:2a196b3b96b95feaede724b8422c3e82)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-msdkpix-qq.jar(md5:f2f84c186680ab29c894021b883d273a)
|    |    |    |    |    |    |    +-open_sdk_3.5.14.3_rc26220c.jar(md5:afc8a2ad4f15958b31f6c4527a55957e)
|    |    |    |    |    |    +-project.properties(md5:404765ee5cc019975e97b7e6ba7afdf0)
|    |    |    |    |    |    +-res
|    |    |    |    |    |    |    +-xml
|    |    |    |    |    |    |    |    +-file_paths.xml(md5:51924ebd1e22803055cccafb34a2606a)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXQQ
|    |    |    |    |    |    +-MSDKPIXQQ.embeddedframework.zip(md5:6bf87fca93cefb2d3b64eb068bb3a8d6)
|    |    |    |    |    +-Third
|    |    |    |    |    |    +-MSDKPIXQQ
|    |    |    |    |    |    |    +-TencentOpenAPI.embeddedframework.zip(md5:2c3420dfeeeffcb9998ad417e606d8a2)
+-MSDKPIXSystem
|    +-MSDKPIXSystem.uplugin(md5:d171c9b4cd6a6e313eac1c50b1c66b6f)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXSystem
|    |    |    +-MSDKPIXSystem.Build.cs(md5:276ce0ef28925208fe9d776c13548821)
|    |    |    +-MSDKPIXSystem_UPL.xml(md5:8923f12b9ef0077996acd087557089ad)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXSystem.cpp(md5:adc0c864155c9b275627557e51428268)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXSystem.h(md5:827c6b2787a6398716399adf0167b51f)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-system
|    |    |    |    |    |    +-AndroidManifest.xml(md5:be24e15dc8dcfb5ed58e5828a30b349b)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:c56e72b62ffb43fb111048b5cea45ed5)
|    |    |    |    |    |    +-additions.gradle(md5:4a149f0a2f5fbf8eb12a6684979b0bd5)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-msdkpix-system.jar(md5:c9943e7d18f5031a359d53cb7c0985cc)
|    |    |    |    |    |    +-project.properties(md5:06eb8ac23aa83301d2079053cb676fdd)
|    |    |    |    |    |    +-res
|    |    |    |    |    |    |    +-xml
|    |    |    |    |    |    |    |    +-system_share_storage.xml(md5:6fce2ccd1650cfd5d2beb1ca346e6e7c)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXSystem
|    |    |    |    |    |    +-MSDKPIXSystem.embeddedframework.zip(md5:72d9e0e4355d12df66cadbb854c5e832)
+-MSDKPIXTDM
|    +-MSDKPIXTDM.uplugin(md5:01d1e49bb1a8b7256145edf573bf2b2c)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXTDM
|    |    |    +-MSDKPIXTDM.Build.cs(md5:ecb67de2b11b1dc7d0ba622eeeaff6b2)
|    |    |    +-MSDKPIXTDM_UPL.xml(md5:8a3990530af3824186ce623f7b702333)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXTDM.cpp(md5:663cfc2408b722509d818a8f9362fe92)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXTDM.h(md5:fba0137893db61f5b104641b10545589)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-tdm
|    |    |    |    |    |    +-AndroidManifest.xml(md5:0ca0a284166f0233a7c9dbb9ce203684)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:8bad2a86b48484905c00f1d02f29baaa)
|    |    |    |    |    |    +-additions.gradle(md5:605788888ec0aa0827cd77caa5a4ffed)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-msdkpix-tdm.jar(md5:6f6459ce4aa616b80d4c80ebe7188c5c)
|    |    |    |    |    |    +-proguard-project.txt(md5:d41d8cd98f00b204e9800998ecf8427e)
|    |    |    |    |    |    +-project.properties(md5:404765ee5cc019975e97b7e6ba7afdf0)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXTDM
|    |    |    |    |    |    +-MSDKPIXTDM.embeddedframework.zip(md5:7def9316e91080798ff210d77e4d7b3d)
+-MSDKPIXWeChat
|    +-MSDKPIXWeChat.uplugin(md5:5f0f284f1ae1da58f7b1727b56be6072)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXWeChat
|    |    |    +-MSDKPIXWeChat.Build.cs(md5:4e4bb317fd19a2dedaeb0e6948242313)
|    |    |    +-MSDKPIXWeChat_UPL.xml(md5:421d5d7c9d8411532c405b96aceb5d57)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXWeChat.cpp(md5:8f8b311397fa3c5ca14fa16d4393ec62)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXWeChat.h(md5:553633e1f21cb3cebd4ba4bfbac12c3a)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-wechat
|    |    |    |    |    |    +-AndroidManifest.xml(md5:7196f94bdcce331a43f6358a8d24a8fe)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:995eea376f9c789ef6c8f6f15354ce1e)
|    |    |    |    |    |    +-additions.gradle(md5:507814e9c302469f4e299ce698dcca05)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-msdkpix-wechat.jar(md5:3ca2ff29c4e4ab6570e1459e5f9334b5)
|    |    |    |    |    |    +-project.properties(md5:def0d36f2f875cbad47ade986b36396a)
|    |    |    |    |    |    +-res
|    |    |    |    |    |    |    +-layout
|    |    |    |    |    |    |    |    +-com_tencent_msdkpix_qrcode_window.xml(md5:03d1dde5d1d501647ed60e0ed4baa4d3)
|    |    |    |    |    |    |    +-values
|    |    |    |    |    |    |    |    +-values.xml(md5:2c4875ef40c01dea6147447a8d2db176)
|    |    |    |    |    |    |    +-xml
|    |    |    |    |    |    |    |    +-file_provider_paths.xml(md5:100b4ee380a80e2259025aae78e46797)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXWeChat
|    |    |    |    |    |    +-MSDKPIXWeChat.embeddedframework.zip(md5:6a85a53d50b1f624c0534fc507fb3602)
|    |    |    |    |    +-Third
|    |    |    |    |    |    +-MSDKPIXWeChat
|    |    |    |    |    |    |    +-Private
|    |    |    |    |    |    |    |    +-WXApiObject+WMPF.h(md5:54ffe22c803e0179df85e0bfe98e6bd3)
|    |    |    |    |    |    |    +-WXApi+Private.h(md5:07702d57f39bdbfb9a2ab26f8ab60e0f)
|    |    |    |    |    |    |    +-WXApi.h(md5:cd4b4558278157fabc6d330ed7f873f4)
|    |    |    |    |    |    |    +-WXApiObject+Private.h(md5:ffdea46b239765cec9077ff283dedd57)
|    |    |    |    |    |    |    +-WXApiObject.h(md5:7b4a616576e0e41b4b20025db583a1c8)
|    |    |    |    |    |    |    +-WechatAuthSDK.h(md5:d69780ae3b7cf94fdf570d35b8e56242)
|    |    |    |    |    |    |    +-libWeChatSDK.a(md5:e86aff531cdd812d051fa85eee5971f7)
+-MSDKPIXWebView
|    +-MSDKPIXWebView.uplugin(md5:ecccbecadc49f0ef6eaa4ca14fc83df8)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXWebView
|    |    |    +-MSDKPIXWebView.Build.cs(md5:fc9b47de706ac1178eb15a08561e5d57)
|    |    |    +-MSDKPIXWebView_UPL.xml(md5:1a514ea4cbc3a3680109bb9c4a03207f)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXWebView.cpp(md5:d7a380acfb5b9722bd3fde50f2f1f7ea)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXWebView.h(md5:d82b0024b673db5c98089d01be6a4105)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-webview
|    |    |    |    |    |    +-AndroidManifest.xml(md5:25e6eca2ff993a144b75b1454be8838f)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:273d6bde0ac460237295ecc03cbb8b47)
|    |    |    |    |    |    +-additions.gradle(md5:4df5e313e759853d4ecaf247beb7353d)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-msdkpix-webview.jar(md5:9ef980fa6e708d296c147eb46ae0904a)
|    |    |    |    |    |    |    +-tbs_sdk_thirdapp_v4.3.0.343_44243.jar(md5:ce4cab44377f7656d721e5f9920076a0)
|    |    |    |    |    |    +-project.properties(md5:9180eecb49df3bbeac8b426dd285a91f)
|    |    |    |    |    |    +-res
|    |    |    |    |    |    |    +-anim
|    |    |    |    |    |    |    |    +-msdk_webview_anim_share_slide_in.xml(md5:670f6a9b7e87637148744e6e065b0590)
|    |    |    |    |    |    |    |    +-msdk_webview_anim_share_slide_out.xml(md5:cc2add70e054eb1fcc74f9e1fcd94115)
|    |    |    |    |    |    |    |    +-msdk_webview_anim_titlebar_hide.xml(md5:2955741abf0d9b9d9ab87b55ac5c0295)
|    |    |    |    |    |    |    |    +-msdk_webview_anim_titlebar_show.xml(md5:340b9b39526fe32c7faf800361e1feda)
|    |    |    |    |    |    |    |    +-msdk_webview_anim_toolbar_hide.xml(md5:9ee3c3e6b18dee6087ec28c7284b04ec)
|    |    |    |    |    |    |    |    +-msdk_webview_anim_toolbar_show.xml(md5:02aa0fc6b41b1fe6df35e467c5ab3734)
|    |    |    |    |    |    |    +-drawable
|    |    |    |    |    |    |    |    +-msdk_webview_sel_btn_bg.xml(md5:d282ee6dbaacffb7ee6c46005b7be02a)
|    |    |    |    |    |    |    |    +-msdk_webview_sel_btn_cancel_bg.xml(md5:385ca6f74a7be1aaa77eba2d4507f34c)
|    |    |    |    |    |    |    +-drawable-hdpi-v4
|    |    |    |    |    |    |    |    +-msdk_webview_btn_close.png(md5:da434e99ad1ab285b4228f19b8742fbc)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_left.png(md5:83c16fa7e5a28d32960595bad63121b3)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_left_disabled.png(md5:4b373a092615a57dfa1e0a7bd2fed5ae)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_more.png(md5:5693c0d4d98a523c217700ab1e9a9622)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_qqbrowser.png(md5:3b3fc20768b4defc866a9ac829fa017b)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_refresh.png(md5:b100ff84aa5e3776de92945732bd2187)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_right.png(md5:a4a2e3fd2082cbc9066cdaa533defe94)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_right_disabled.png(md5:967fe436115564605ca843ef1bbc7284)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_stop.png(md5:7a7786e89ff6c98207c4b50fa24fa29e)
|    |    |    |    |    |    |    +-drawable-xhdpi-v4
|    |    |    |    |    |    |    |    +-msdk_webview_btn_close.png(md5:a6f20c547061f8f8414f8a2a85456808)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_left.png(md5:f3e9e735381490dd674a9114be74d1cc)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_left_disabled.png(md5:306c01e21a1c59e2e92b9eabab2157bf)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_more.png(md5:5ca4c388bacf2670e83757c74076a2fa)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_qqbrowser.png(md5:b656d24008c016ca70e4d0ca8793f844)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_refresh.png(md5:592535e6f55cfc1e17d7aa2e1ac5f0a7)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_right.png(md5:b0f537cdfd1b618a9abf8bd79d32926c)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_right_disabled.png(md5:1955faa78131d990d55da5604f631c0f)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_stop.png(md5:b11ae6cfbcd4b6beff14018ee5a27bab)
|    |    |    |    |    |    |    +-drawable-xxhdpi-v4
|    |    |    |    |    |    |    |    +-msdk_webview_btn_close.png(md5:a361b9dc196be527ccc1f8042db97798)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_left.png(md5:d3b232db4f9b1da294f80503b01e981b)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_left_disabled.png(md5:a7d5e3f6911dc222f207a69c08baa393)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_more.png(md5:990c5a038bbb36d408763cf565ec8881)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_qqbrowser.png(md5:afe2167398320875e0d7b6a44fb8af81)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_refresh.png(md5:b3fc80b056d09f236a262f72ab56b1ae)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_right.png(md5:2fe96216efd3c780ccd67d7550311921)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_right_disabled.png(md5:880e40d83e731b4ddd2a29fb949b9155)
|    |    |    |    |    |    |    |    +-msdk_webview_btn_stop.png(md5:3c409a8ae5510b8f16423f5b0b2f6cf1)
|    |    |    |    |    |    |    |    +-msdk_webview_share_bg_toast.png(md5:89fdc96fd1f15531bc7e7f3a0e11b457)
|    |    |    |    |    |    |    |    +-msdk_webview_share_facebook.png(md5:f52ad78314dd8ddc69db55175cdd2e2c)
|    |    |    |    |    |    |    |    +-msdk_webview_share_moment.png(md5:d583634356317b45b7b0ee6fd3c78607)
|    |    |    |    |    |    |    |    +-msdk_webview_share_otherbrowser.png(md5:614b7ec9b71a111e53f040e1549451c8)
|    |    |    |    |    |    |    |    +-msdk_webview_share_qq.png(md5:6ae34718f18237ec092aacd7041c8c28)
|    |    |    |    |    |    |    |    +-msdk_webview_share_qqbrowser.png(md5:c56441394f0e04c00697464ebf5739f3)
|    |    |    |    |    |    |    |    +-msdk_webview_share_qzone.png(md5:40f50d2c13ea6301aa8ed2c7166976df)
|    |    |    |    |    |    |    |    +-msdk_webview_share_wechat.png(md5:b3a9c4d352bae038aab044bc36aa6c38)
|    |    |    |    |    |    |    +-layout
|    |    |    |    |    |    |    |    +-msdk_webvidw_share_toast.xml(md5:c923abd4281e3157474375b5e632d859)
|    |    |    |    |    |    |    |    +-msdk_webview_activity.xml(md5:a497a04f785f3cbba558bb1a3fb529b2)
|    |    |    |    |    |    |    |    +-msdk_webview_share_container.xml(md5:f9bd8bb0fe4847ec53b3d84708cd481d)
|    |    |    |    |    |    |    |    +-msdk_webview_share_dlg.xml(md5:d4c7414b63cd270c45f913200a6b104d)
|    |    |    |    |    |    |    |    +-msdk_webview_share_item.xml(md5:88cec1ad5e22dc04080c84c2ce588b3f)
|    |    |    |    |    |    |    +-values
|    |    |    |    |    |    |    |    +-values.xml(md5:534d3769fd0e9106f7b3fd0d1bf38ad8)
|    |    |    |    |    |    |    +-values-de
|    |    |    |    |    |    |    |    +-values-de.xml(md5:43bb47c8bd9fb1127050771b93d8ff91)
|    |    |    |    |    |    |    +-values-es
|    |    |    |    |    |    |    |    +-values-es.xml(md5:3f06bbb219ffbdda79fb0863c6160919)
|    |    |    |    |    |    |    +-values-fr
|    |    |    |    |    |    |    |    +-values-fr.xml(md5:67c27ce914085ac5c4fe071a30cc0eaa)
|    |    |    |    |    |    |    +-values-it
|    |    |    |    |    |    |    |    +-values-it.xml(md5:05095cf683b195ee19d252fe2b592003)
|    |    |    |    |    |    |    +-values-pt
|    |    |    |    |    |    |    |    +-values-pt.xml(md5:c305c0a8fb08fc1143208559b25e81c3)
|    |    |    |    |    |    |    +-values-ru
|    |    |    |    |    |    |    |    +-values-ru.xml(md5:c305c0a8fb08fc1143208559b25e81c3)
|    |    |    |    |    |    |    +-values-tr
|    |    |    |    |    |    |    |    +-values-tr.xml(md5:bdd5996993f900268889aa95a77ee9b6)
|    |    |    |    |    |    |    +-values-zh
|    |    |    |    |    |    |    |    +-values-zh.xml(md5:b8fbde5cf74c6dd67fbef3c35a24a346)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXWebView
|    |    |    |    |    |    +-MSDKPIXWebView.embeddedframework.zip(md5:107f5681a7e9f826fbbbf480d95ded8f)
+-MSDKPIXXG
|    +-MSDKPIXXG.uplugin(md5:8acb4fb9bdfc7df63b9a80ea98352572)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-MSDKPIXXG
|    |    |    +-MSDKPIXXG.Build.cs(md5:32786f97b4595776abfb839852eec289)
|    |    |    +-MSDKPIXXG_UPL.xml(md5:efef8d9372cb5945fc4c138f0a353048)
|    |    |    +-Private
|    |    |    |    +-MSDKPIXXG.cpp(md5:5809176ad6091e75e5a7fd36af9b9d1c)
|    |    |    +-Public
|    |    |    |    +-MSDKPIXXG.h(md5:6cc9230eb5406abc497c35378e84a43d)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-msdkpix-xg
|    |    |    |    |    |    +-AndroidManifest.xml(md5:7c641794805325513508a658b8aecb74)
|    |    |    |    |    |    +-META-INF
|    |    |    |    |    |    |    +-com
|    |    |    |    |    |    |    |    +-android
|    |    |    |    |    |    |    |    |    +-build
|    |    |    |    |    |    |    |    |    |    +-gradle
|    |    |    |    |    |    |    |    |    |    |    +-aar-metadata.properties(md5:043b7933ccbb96b71c1ef471e1b948cd)
|    |    |    |    |    |    +-R.txt(md5:26938bd38d557e814064e981dc164913)
|    |    |    |    |    |    +-additions.gradle(md5:3643872d9e14a12859062f31ec90aa82)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    |    +-libxgVipSecurity.so(md5:8ad1d785ec6e0f8d67974914e686c3e3)
|    |    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    |    +-libxgVipSecurity.so(md5:ac2c767806d57ac3dfe09904601eb45d)
|    |    |    |    |    |    |    +-jg-filter-sdk-1.1.jar(md5:be730511ea84ca3384c436face0e7504)
|    |    |    |    |    |    |    +-msdk_oppo_adapter.jar(md5:d79eb2d9394f565e795e82855afb4729)
|    |    |    |    |    |    |    +-msdkpix-xg.jar(md5:ee83d99614b0c1ebf90f90e14681d55e)
|    |    |    |    |    |    |    +-oppo-3.1.0-msdk.jar(md5:fb85000ac575f4dfc5db4243f913ac5c)
|    |    |    |    |    |    |    +-tpns-baseapi-sdk-1.3.9.0.jar(md5:7618ecdc409d09889a030c8944bc0ccc)
|    |    |    |    |    |    |    +-tpns-core-sdk-1.3.9.0.jar(md5:0dda1fe733904a617e9c2bce0a276c6f)
|    |    |    |    |    |    |    +-tpns-mqttchannel-sdk-1.3.9.0.jar(md5:34cea1bdbd4fc1473bb69c512e9dfcc1)
|    |    |    |    |    |    |    +-tpns-mqttv3-sdk-1.3.9.0.jar(md5:7ccd9a39a6fe544692d64fb52858e34b)
|    |    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    |    +-libxgVipSecurity.so(md5:068050273e56f5d99666fd73e929b50b)
|    |    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    |    +-libxgVipSecurity.so(md5:8e53e87b8ce7c7d05688683fea1a44fc)
|    |    |    |    |    |    +-proguard-project.txt(md5:f91849863073add1f51961e4723e1d58)
|    |    |    |    |    |    +-project.properties(md5:a4e5f595393e0d423fc795a372fa8502)
|    |    |    |    +-iOS
|    |    |    |    |    +-MSDKPIXXG
|    |    |    |    |    |    +-MSDKPIXXG.embeddedframework.zip(md5:d11660ea229adcac68c227a121a7514e)
|    |    |    |    |    +-Third
|    |    |    |    |    |    +-MSDKPIXXG
|    |    |    |    |    |    |    +-XGLocalNotification.h(md5:10de1d0b5ceb3a7db80e5d1386c73296)
|    |    |    |    |    |    |    +-XGMTACloud.embeddedframework.zip(md5:99875abdb75962966e56a0785836a17c)
|    |    |    |    |    |    |    +-XGPush.h(md5:d0b76ab88031ff91013727a10a611893)
|    |    |    |    |    |    |    +-XGPushPrivate.h(md5:02c05eb551cc6443060e8a995f1a0c3a)
|    |    |    |    |    |    |    +-libXG-SDK-Cloud.a(md5:1ed4b8c2b70776e0593cfc5a7c558a51)
+-PixUI
|    +-Content
|    |    +-mat
|    |    |    +-Mat_Pix_9_slice.uasset(md5:001ae710b4a1af59a069fa09df209220)
|    |    |    +-Mat_Pix_Border.uasset(md5:f0ed2a335feb11629997539dc2418ba3)
|    |    |    +-Mat_Pix_Border_Color.uasset(md5:e8ef18d922efe73db9bee17a7f29ab1d)
|    |    |    +-Mat_Pix_Border_Color_Radius.uasset(md5:f60e909ccf2431ec2137c1aca3780c58)
|    |    |    +-Mat_Pix_Border_Radius.uasset(md5:94bb65a1153abae1054e09db8cbcdbce)
|    |    |    +-Mat_Pix_Radius.uasset(md5:cdff83b1617dae76866c9f25857dbb62)
|    |    |    +-Mat_Pix_Radius_corner.uasset(md5:34c5b77e3b87d814082179a2ac3265ca)
|    |    |    +-Mat_Pix_Rect_Radius.uasset(md5:b30a4f2620575fe7a6ba926bb1ca67a9)
|    |    |    +-Mat_Pix_Rect_Radius_corner.uasset(md5:232ea91ec22c074d9d839e3a64bce43c)
|    |    |    +-es2
|    |    |    |    +-Mat_Pix_es2_9_slice.uasset(md5:31c5041faa6934d5425de785622d0108)
|    |    |    |    +-Mat_Pix_es2_Border.uasset(md5:ed6b6256ce98b59debc9b2216a6a848d)
|    |    |    |    +-Mat_Pix_es2_Border_Color.uasset(md5:c9e389604d98e232503670c772f5bb2f)
|    |    |    |    +-Mat_Pix_es2_Border_Color_Radius.uasset(md5:5c5aa10f7785ab6dfcb6b3b79cda2b15)
|    |    |    |    +-Mat_Pix_es2_Border_Radius.uasset(md5:3e4676cd5e8f1bc63624409004d11d70)
|    |    |    |    +-Mat_Pix_es2_Radius.uasset(md5:6da9c9cf688ef5e53f54f821991ddac6)
|    |    |    |    +-Mat_Pix_es2_Radius_corner.uasset(md5:d105e129aedf1cb9fc6d505d16a40e0f)
|    |    |    |    +-Mat_Pix_es2_Rect_Radius.uasset(md5:859a8a5dce24836a8d1d9af78eda15f7)
|    |    |    |    +-Mat_Pix_es2_Rect_Radius_corner.uasset(md5:0d6ced9b0df596a4444a4e0a141c594a)
|    +-PixUI.uplugin(md5:6279e9147f582635263d3c7ecf6968dd)
|    +-Resources
|    |    +-ButtonIcon_40x.png(md5:5b0c7437b4f4d23a3b0d71de1bbeb54a)
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-PixUI
|    |    |    +-PixUI.Build.cs(md5:94f6de0d92d2dfb639d4f2bacb90a6ab)
|    |    |    +-Private
|    |    |    |    +-PixExtBpCall
|    |    |    |    |    +-PixExtBpCall.cpp(md5:00359ed9dd270a55bec516c2b2e07715)
|    |    |    |    |    +-PixExtBpCall.h(md5:1509634fcd2fe8993a8e393f594d93a6)
|    |    |    |    |    +-hf_loadlib.h(md5:da695e866e4a523b32246ec382d3fc41)
|    |    |    |    |    +-hf_loadlib_template.h(md5:c8237b7ddabf8f8469bda97d3d57905d)
|    |    |    |    |    +-pixuilib_external_bp_call.cpp(md5:9ca340fcd880175a5265556ec68cdc5e)
|    |    |    |    +-PixImp
|    |    |    |    |    +-PixBrush
|    |    |    |    |    |    +-PixImgBrush.cpp(md5:47a4790377f33110aa60263e756a8b01)
|    |    |    |    |    |    +-PixImgBrush.h(md5:ccf88e174b5f6d80779ccf75b6812494)
|    |    |    |    |    |    +-PixMatBrush.cpp(md5:bd3204987e9ea7c80e2d0ab0cd05576b)
|    |    |    |    |    |    +-PixMatBrush.h(md5:ae9cabdae55a3876f499b03ca6f90cc3)
|    |    |    |    |    +-PixImpBase.cpp(md5:ea4885436525cfa0bf482854afd82e38)
|    |    |    |    |    +-PixImpBase.h(md5:c44bf20a8dbdf36e7ff9116b40726793)
|    |    |    |    |    +-PixImpFileLoad.cpp(md5:45e129e737eaf529e0ec4d198085faa3)
|    |    |    |    |    +-PixImpFileLoad.h(md5:d33b7ac27c7a882f12de1c80a90e99e8)
|    |    |    |    |    +-PixImpFont.cpp(md5:61be2c7b7b826eae348f642fa2cc33da)
|    |    |    |    |    +-PixImpFont.h(md5:b62559b8bfd465c752bc5421e8fc3a07)
|    |    |    |    |    +-PixImpImg.cpp(md5:534bed160438e39eef0d7851241707fc)
|    |    |    |    |    +-PixImpImg.h(md5:94960a4e6728936524f84219bb0becd8)
|    |    |    |    |    +-PixImpMat.cpp(md5:f2640df82606336aec193c38ea5613d3)
|    |    |    |    |    +-PixImpMat.h(md5:d56a716a479790370876fbcfb9c4ace4)
|    |    |    |    |    +-PixImpNet.cpp(md5:866576266de7ba2c3c0859df0d76412f)
|    |    |    |    |    +-PixImpNet.h(md5:80544c4bd2396743a4ac673b2beb0406)
|    |    |    |    |    +-PixImpSlot.cpp(md5:0e5279170df5dc3c1fc1131bb6217857)
|    |    |    |    |    +-PixImpSlot.h(md5:513798c184d200d5705f9cdfb5d9ed4f)
|    |    |    |    |    +-PixNet
|    |    |    |    |    |    +-PixNetObjBase.h(md5:cb69c6fb2f392757fa108fa0b2e165c8)
|    |    |    |    |    |    +-PixWebSocket.cpp(md5:c0c89ce318af1e9c4cf5d35d1a472878)
|    |    |    |    |    |    +-PixWebSocket.h(md5:c5219999b27f739a92ab6d99254ec663)
|    |    |    |    |    |    +-PixXmlRequest.cpp(md5:5428b601a39faa8983b83c87692fd28d)
|    |    |    |    |    |    +-PixXmlRequest.h(md5:17fbb146d2d159f84ab30279c82afe2a)
|    |    |    |    |    +-PixObject.h(md5:c04b505fd9613e761c79096a3c04fd9a)
|    |    |    |    +-PixImpMgr.cpp(md5:69b74c7c0896ef28d9b16e239a01eb05)
|    |    |    |    +-PixImpMgr.h(md5:17da80e0a8c97c39d5e4f44931bf96f6)
|    |    |    |    +-PixInputSystem
|    |    |    |    |    +-IPixInputSystem.cpp(md5:76afbc57484676ba887603b1b1bb8b68)
|    |    |    |    |    +-IPixInputSystem.h(md5:b78c9c679be5d3c9b8225707d31a995d)
|    |    |    |    +-PixLibEx
|    |    |    |    |    +-PixDyLib.cpp(md5:8193959a039c65604b3cc628d5e21da6)
|    |    |    |    |    +-PixDyLib.h(md5:4ed7f72d52207d732a06bd886a4556b5)
|    |    |    |    |    +-PixDyLibDebug.cpp(md5:14981f820dc53b38f5b3348e2ba151d3)
|    |    |    |    |    +-PixDyLibDebug.h(md5:239f3242355b7edcc959fa87eadc86d4)
|    |    |    |    +-PixUI.cpp(md5:f59b41fdd17cf4c787f6546f56491120)
|    |    |    |    +-PixUIBPLibrary.cpp(md5:dedd0164a21ffaaf29d5b24df7cc9091)
|    |    |    |    +-PixUIDrawItem
|    |    |    |    |    +-PixDrawItem.cpp(md5:ad9fa09ff1fddb92019927fd02fba1ec)
|    |    |    |    |    +-PixDrawItem.h(md5:681c91d4001a0cab659ee7556a2cd00c)
|    |    |    |    |    +-PixDrawItemDrawBorder.cpp(md5:0f90868474ff8d3240111a2fafc3a3cb)
|    |    |    |    |    +-PixDrawItemDrawBorder.h(md5:10c7581c08c97af7ac8c8c7eb8c187aa)
|    |    |    |    |    +-PixDrawItemDrawImage.cpp(md5:0861ef8aaa01f59d131e4ab37db3f090)
|    |    |    |    |    +-PixDrawItemDrawImage.h(md5:b1bdf012f0ed556bdcc719cbc3083b59)
|    |    |    |    |    +-PixDrawItemDrawLine.cpp(md5:2447c09308da12414313cea2303a18c8)
|    |    |    |    |    +-PixDrawItemDrawLine.h(md5:866f2d779789fe9328036c50f41c79db)
|    |    |    |    |    +-PixDrawItemDrawRect.cpp(md5:b2c617b960e44eac4fd6ec96ab98b099)
|    |    |    |    |    +-PixDrawItemDrawRect.h(md5:9c9d4363f53ddc69126f886cee18b2f6)
|    |    |    |    |    +-PixDrawItemDrawSlot.cpp(md5:8e9dcb1c47654adf9131f3e481ad216c)
|    |    |    |    |    +-PixDrawItemDrawSlot.h(md5:6b381513eb9d5749ef719247b88089c8)
|    |    |    |    |    +-PixDrawItemDrawText.cpp(md5:3714c60584074a61b1d346eb91b8b2de)
|    |    |    |    |    +-PixDrawItemDrawText.h(md5:5af9794df5a9b732dd06319a41c3b6e2)
|    |    |    |    |    +-PixDrawItemFillRect.cpp(md5:bdbc4f5e0bffd8b1f07f90ab78574882)
|    |    |    |    |    +-PixDrawItemFillRect.h(md5:a68f3c999f7e3dea9f4908eb7be72f10)
|    |    |    |    |    +-PixDrawItemPopClip.cpp(md5:75b9c158f3a980771f0e7c3e7bb9a07f)
|    |    |    |    |    +-PixDrawItemPopClip.h(md5:6e5d353f471bfb3e50202bba4fb4c459)
|    |    |    |    |    +-PixDrawItemPushClip.cpp(md5:c8ba976bad3d394524d8eb78c7ff082e)
|    |    |    |    |    +-PixDrawItemPushClip.h(md5:c381f1f49228c60d7c7a0923cde72ab1)
|    |    |    |    +-PixUIExInterface.cpp(md5:bed4805271f242fe47d438e8809f30ec)
|    |    |    |    +-PixUIInput.cpp(md5:abda894eb8ac0697bacc72a1c29d9ca8)
|    |    |    |    +-PixUILibMgr.cpp(md5:92830208f3ae713c919c59d8aebf172d)
|    |    |    |    +-PixUILibMgr.h(md5:6691cfb4fd619990dc257585f1374d4c)
|    |    |    |    +-PixUILog.cpp(md5:b8080511b3ba7f047e8a730ec46aabad)
|    |    |    |    +-PixUIProfiler
|    |    |    |    |    +-MemoryItem.cpp(md5:11c628372e45aed417fb0bd385ffff8d)
|    |    |    |    |    +-MemoryItem.h(md5:055a4de00a0bbbcd1934f0a468556bb8)
|    |    |    |    |    +-ProfilerCore.h(md5:055a4de00a0bbbcd1934f0a468556bb8)
|    |    |    |    |    +-PxPage.cpp(md5:71f0873a9aa012fb3b5f40b8261fed06)
|    |    |    |    |    +-PxPage.h(md5:35fa21ed9fb0c9780ffc8d0e09188fe8)
|    |    |    |    |    +-PxPageFrame.h(md5:fdb882450f48a4bee8982458a2818732)
|    |    |    |    |    +-PxProfilerMgr.cpp(md5:d869a5173f79a62d8a192de56a6664d2)
|    |    |    |    |    +-PxProfilerMgr.h(md5:bc05520d49f2a2ef2883fe700acb5fb9)
|    |    |    |    |    +-PxpResCount.cpp(md5:e78cb2235840821cc72c1a4ea1ac5a88)
|    |    |    |    |    +-PxpResCount.h(md5:cc90cbd02ad040f673152bd267ad9939)
|    |    |    |    |    +-PxpTickCount.cpp(md5:be0ab541364162842aafd71ff534ca2a)
|    |    |    |    |    +-PxpTickCount.h(md5:4110632f43b0fb55f0796dc5713db763)
|    |    |    |    +-PixUIViewPortWidget.cpp(md5:bc94508d52353da671cc2c23f55408f4)
|    |    |    |    +-PixUIWidget.cpp(md5:5f7b2b7656222df78bf9d38b36da35dd)
|    |    |    |    +-PixUIWidgetOld.cpp(md5:eb0a643aef29fdef601584d9b3f0d28b)
|    |    |    |    +-PixUtil.cpp(md5:ecec7d94a5f0e9ee1297793d744de694)
|    |    |    |    +-PixUtil.h(md5:31eae749eaf2838c0599665def46e0ca)
|    |    |    |    +-PixUtil_android.cpp(md5:ac28828508e5306d8263e5c5fcfc1108)
|    |    |    |    +-PixUtil_ios.cpp(md5:eabf99e157295f980183e066982343b5)
|    |    |    |    +-PixUtil_mac.cpp(md5:0b0e0dabc0d7c0e6ced5488308ab563d)
|    |    |    |    +-PixUtil_other.cpp(md5:7c37e00321161e98a8b61952480705fe)
|    |    |    |    +-PixUtil_win.cpp(md5:ed67af396538ec593137b82432938596)
|    |    |    |    +-PxSubCtrlWidget.cpp(md5:4de0a31ad60200a419aa7ce83fc7eb16)
|    |    |    |    +-PxSubCtrlWidget.h(md5:411bd92aa492b96321db61f4ae1f521f)
|    |    |    |    +-PxSubLayerWidget.cpp(md5:d94087c991693189388dbda58d8366e7)
|    |    |    |    +-PxSubLayerWidget.h(md5:d4d5c150bda76700572d4f052b213b47)
|    |    |    |    +-SPixPaintWidgetOld.cpp(md5:d48b84d445ee77d1d248662863b11646)
|    |    |    |    +-SPixPaintWidgetOld.h(md5:4033a4ff11061881ebf9aff4d808dff0)
|    |    |    |    +-SPxCtrlWidget.cpp(md5:a174ba4d612c087cff138a53118fe365)
|    |    |    |    +-SPxCtrlWidget.h(md5:8693f58118febe35f1d2e147b93ff485)
|    |    |    |    +-SPxPaintWidget.cpp(md5:400bd368166deb1ee825d0dbea7c2e4c)
|    |    |    |    +-SPxPaintWidget.h(md5:cdf4012f3d95d3011c9ef2fcef6c31f0)
|    |    |    +-Public
|    |    |    |    +-PixUI.h(md5:75e7076d5db363fa3e72007e4877fefa)
|    |    |    |    +-PixUIBPLibrary.h(md5:c353e79f330dc6b977fae42755845d70)
|    |    |    |    +-PixUIDef.h(md5:2e7b1bcb9df6b3cd9b9c4d446a895eb4)
|    |    |    |    +-PixUIExInterface.h(md5:89cf8cbf9d4b9493e57c03ec3e01c90b)
|    |    |    |    +-PixUIInput.h(md5:83aa25399c18308c49c06929856648bf)
|    |    |    |    +-PixUILog.h(md5:cdb31b7b76175c2574441fa205a13929)
|    |    |    |    +-PixUIViewPortWidget.h(md5:2046b9c818676149702449915116b73a)
|    |    |    |    +-PixUIWidget.h(md5:2eb2217fcd48956e1d742bf48f89173f)
|    |    |    |    +-PixUIWidgetOld.h(md5:84ed9a2dc27f6887df86e1c65716f9f7)
|    |    |    +-ThirdParty
|    |    |    |    +-Includes
|    |    |    |    |    +-GPixUI
|    |    |    |    |    |    +-IGPixUIService.h(md5:02682a11f9c35989490b524743e5c542)
|    |    |    |    |    |    +-PxUIView.h(md5:166db7707dd2f26635b3e7731d7b7ada)
|    |    |    |    |    +-hf.h(md5:0ffa2688bfed3c6850f07faf8678c99d)
|    |    |    |    |    +-hf_idraw.h(md5:50b6c545a5c54216aa63f8dbfe02692f)
|    |    |    |    |    +-hf_iwindow.h(md5:bd196e97bc363893de3443341f515b13)
|    |    |    |    |    +-hf_typedef.h(md5:33cf0f40bbf5a06c96dd3bc170571a27)
|    |    |    |    |    +-px_plugin.h(md5:cc111df4675a79611416d3538fe2307f)
|    |    |    |    |    +-px_plugindef.h(md5:ca582f5da9bf5bb7d1cd2e23e81d07e4)
|    |    |    |    +-Libraries
|    |    |    |    |    +-Android
|    |    |    |    |    |    +-PxEmbedded.jar(md5:19c02f3772c2436fdab46d1a04310637)
|    |    |    |    |    |    +-PxExtJava.jar(md5:3b1a229ea7c554d4131db2cf850e15f7)
|    |    |    |    |    |    +-additions.gradle(md5:a5aee16e52d3a0f1185b23ec2ba9f5a0)
|    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    +-libGPixUI.so(md5:eb10b3ef323ee8b31b5780c266bb7560)
|    |    |    |    |    |    |    +-libPixFFmpeg.so(md5:ba41a1e622dd424c6afbe1eb3eecb039)
|    |    |    |    |    |    |    +-libPixVideo.so(md5:2f8fea7f7e1d3bb718007576e5e95ab2)
|    |    |    |    |    |    |    +-libPxEmbedded.so(md5:0d00d1e685127b460e4e8c55f1d73cfd)
|    |    |    |    |    |    |    +-libPxExtFFi.so(md5:592c7d93e00388779d6151abb5b4cbd8)
|    |    |    |    |    |    |    +-libPxExtJava.so(md5:76bf3c0586b824f7c13504da7d49cd0f)
|    |    |    |    |    |    |    +-libPxKit.so(md5:fba93e20fee1a63d427e84112b973597)
|    |    |    |    |    |    |    +-libPxUnity.so(md5:2962320069561c258cb177d68d041403)
|    |    |    |    |    |    |    +-libvideotexture.so(md5:f5432948673fa4a3ca8a930ae91bf7f2)
|    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    +-libGPixUI.so(md5:93aa85e1a7a30425ccafd68e78f0aee8)
|    |    |    |    |    |    |    +-libPixFFmpeg.so(md5:b5695be7ee0ff5c9fdd65bcf679bf5fe)
|    |    |    |    |    |    |    +-libPixVideo.so(md5:2ddec4ee30e51a4f76a576dc31a8b59f)
|    |    |    |    |    |    |    +-libPxEmbedded.so(md5:de8904f0ad9c138bc0e34eaf82283e25)
|    |    |    |    |    |    |    +-libPxExtFFi.so(md5:4751630d43dc096b46119b80637d34f1)
|    |    |    |    |    |    |    +-libPxExtJava.so(md5:908a09abaca30a4ee2a3535e66235a99)
|    |    |    |    |    |    |    +-libPxKit.so(md5:2e5cb9a38b27ba929affbdaf48d79997)
|    |    |    |    |    |    |    +-libPxUnity.so(md5:6016206d3dadad1410c422a1adf810f1)
|    |    |    |    |    |    |    +-libvideotexture.so(md5:bd566cb33f93df3e22292279841f2966)
|    |    |    |    |    |    +-assets
|    |    |    |    |    |    |    +-metaJs
|    |    |    |    |    |    |    |    +-applet_loader_entrance(md5:16c50ac336074a32f7d8c07fb9c6cd28)
|    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    +-libGPixUI.so(md5:2fd124e32579613393237da636e06cc9)
|    |    |    |    |    |    |    +-libPixFFmpeg.so(md5:9173e5b5623aa7d89fa5535a2b865d2c)
|    |    |    |    |    |    |    +-libPixVideo.so(md5:c4a279f204c7c198f1e9bbd4cf6d59b7)
|    |    |    |    |    |    |    +-libPxEmbedded.so(md5:90b9ef7dbaac3019593625613ceda352)
|    |    |    |    |    |    |    +-libPxExtFFi.so(md5:55f5b6c9296d26d6269742ed248500a6)
|    |    |    |    |    |    |    +-libPxExtJava.so(md5:c29de6559e93e2b8dac82c47b74dfff1)
|    |    |    |    |    |    |    +-libPxKit.so(md5:701dfb04c67d72f9b326f642e00f8586)
|    |    |    |    |    |    |    +-libPxUnity.so(md5:93601226ee93c2307903c686b8bf6a65)
|    |    |    |    |    |    |    +-libvideotexture.so(md5:7c1dcc976bb59cad3e8d508fa074b8b0)
|    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    +-libGPixUI.so(md5:8ba4f07489a59a3304b7bc57f7a13c1b)
|    |    |    |    |    |    |    +-libPixFFmpeg.so(md5:529d6134d034f2924a839b550e6def3c)
|    |    |    |    |    |    |    +-libPixVideo.so(md5:959dbfa09d04882d8406349dfdfb97a7)
|    |    |    |    |    |    |    +-libPxEmbedded.so(md5:a62afafcb641ce1950a503b51fd90180)
|    |    |    |    |    |    |    +-libPxExtFFi.so(md5:10fb62d5e9bc93f4e3cd003c6b207b36)
|    |    |    |    |    |    |    +-libPxExtJava.so(md5:79b568e79de8f07de5f05890a606d0f9)
|    |    |    |    |    |    |    +-libPxKit.so(md5:0f261a0b27ed05d57058bd3753b0f8a9)
|    |    |    |    |    |    |    +-libPxUnity.so(md5:f45ce4e4d1604f8f17609a9e5deb63d4)
|    |    |    |    |    |    |    +-libvideotexture.so(md5:95f69804f9327b8f3350fbea46de300c)
|    |    |    |    |    +-Mac
|    |    |    |    |    |    +-PxUnity.bundle(md5:392a108cd53cf672eee279198c71b108)
|    |    |    |    |    |    +-libPixVideo.dylib(md5:8203e7133f7110b9c9cd3ab4e00809ea)
|    |    |    |    |    |    +-libPxExt.dylib(md5:6d65b3bfcea350bc252ead3d48e3cd24)
|    |    |    |    |    |    +-libPxExtFFi.dylib(md5:b6104250cf2230454fc07d4a375848e5)
|    |    |    |    |    |    +-libPxExtObjc.dylib(md5:dd38e4ae61a8f86ec7ce072db7174e15)
|    |    |    |    |    |    +-libPxKit.dylib(md5:3c6a162e225015a3946bd503c5948a66)
|    |    |    |    |    +-Win32
|    |    |    |    |    +-Win64
|    |    |    |    |    |    +-PixVideo.dll(md5:cdd7acb31ee303a902b2d3347cce6c47)
|    |    |    |    |    |    +-PxExt.dll(md5:d20ea3c5c3297e9deee872a0650d9603)
|    |    |    |    |    |    +-PxExtFFi.dll(md5:a66af2df4f80ffffb970fcd5e2ec564f)
|    |    |    |    |    |    +-PxKit.dll(md5:0d4d679ff48623aebd3f92d9eba239e5)
|    |    |    |    |    |    +-PxKit.pdb(md5:d06b6cb955d90b9e6b96adbb874157a5)
|    |    |    |    |    |    +-PxUnity.dll(md5:c614a09e6988755c5a4ae812038a0baa)
|    |    |    |    |    |    +-PxUnity.pdb(md5:50016345ee3adade25a648e4f81a1a48)
|    |    |    |    |    |    +-avcodec-57.dll(md5:80e1e134ee650407527929980c478414)
|    |    |    |    |    |    +-avdevice-57.dll(md5:95bd01b150d36e0dbae7c4b5e4bfb0b2)
|    |    |    |    |    |    +-avfilter-6.dll(md5:72373cc9058a30593b5577b618a55e25)
|    |    |    |    |    |    +-avformat-57.dll(md5:716f2bc4c1c8146d44cc290eaee445fe)
|    |    |    |    |    |    +-avutil-55.dll(md5:94ec552656478bf92356e58f3c368f2a)
|    |    |    |    |    |    +-libwinpthread-1.dll(md5:a89b000bf8d1a68ad8613424dd532679)
|    |    |    |    |    |    +-pthreadVC2.dll(md5:4a502706d149c2f5854131a7758a90e2)
|    |    |    |    |    |    +-swresample-2.dll(md5:1b92b646182a7d4a26512fad854ae3a7)
|    |    |    |    |    |    +-swscale-4.dll(md5:8676c72ac21d73316a9a8f1097163328)
|    |    |    |    |    |    +-xaudio2_9redist.dll(md5:6c5ccf6e0b963063a8af2712d92a5124)
|    |    |    |    |    +-iOS
|    |    |    |    |    |    +-GPixUI.embeddedframework.zip(md5:479df8c63cabfe9090371333fa8002ed)
|    |    |    |    |    |    +-PixVideo.embeddedframework.zip(md5:0fb3e5ec132516d8a12660c608209c9c)
|    |    |    |    |    |    +-PxEmbedded.embeddedframework.zip(md5:544b65bae2c6a1358c42a67207e25de8)
|    |    |    |    |    |    +-PxExtFFi.embeddedframework.zip(md5:18e22067a9aba0d116534809ea8879c5)
|    |    |    |    |    |    +-PxExtObjc.embeddedframework.zip(md5:19b4060cda97291629c031caa5ddd0e0)
|    |    |    |    |    |    +-PxKit.embeddedframework.zip(md5:047590594c874133feebb73d79770684)
|    |    |    |    +-PixUIPlugin_Android_APL.xml(md5:7e6804d69da690f4fa6b68f99564fe3e)
|    |    |    |    +-PixUIPlugin_Android_APL_Embedded_aar.xml(md5:1bd835f06021bcf60b75b4d65f113a12)
|    |    |    |    +-PixUIPlugin_Android_APL_Embedded_jar.xml(md5:7bbf6f4729f0c21201150ff5da8c2c63)
|    |    |    |    +-PixUIPlugin_Android_APL_ExtFFI.xml(md5:96cf4744632ce5ad43acbc43a5062a9a)
|    |    |    |    +-PixUIPlugin_Android_APL_ExtJava_aar.xml(md5:5ea0b4e24d69f8bf26599cab001ff2be)
|    |    |    |    +-PixUIPlugin_Android_APL_ExtJava_jar.xml(md5:11d25181663590705a65991f8ea5b6da)
|    |    |    |    +-PixUIPlugin_Android_APL_GPixUI.xml(md5:37e7071dd12790df3199ff107fac3196)
|    |    |    |    +-PixUIPlugin_Android_APL_crosCurl.xml(md5:47aa68d8ffc513b1138d67edab0ce786)
|    |    |    |    +-PixUIPlugin_Android_APL_pixuiCurl.xml(md5:e8802324faed468ef7bec71881e5a72b)
|    |    |    |    +-PixUIPlugin_Android_APL_video.xml(md5:9abd45ce7d8d7ad4cd24c75c8aa3db96)
|    |    |    |    +-PixUIPlugin_IOS_UPL_18_to_21_GPixUI.xml(md5:6f22f468337f8f5a0177e44d39f9ddf3)
|    |    |    |    +-PixUIPlugin_IOS_UPL_18_to_21_PixVideo.xml(md5:363770ff718d9a0b8ee1cc81c74c79f4)
|    |    |    |    +-PixUIPlugin_IOS_UPL_18_to_21_PxEmbedded.xml(md5:bfa6a067038f32d390e4024a5232da13)
|    |    |    |    +-PixUIPlugin_IOS_UPL_18_to_21_PxExtFFI.xml(md5:6c89fcd672062ca11cfaa4147b04c023)
|    |    |    |    +-PixUIPlugin_IOS_UPL_18_to_21_PxExtObjc.xml(md5:28a108d7efa89054be0d3fd535af1e6b)
|    |    |    |    +-PixUIPlugin_IOS_UPL_18_to_21_PxKit.xml(md5:10dcbf277eded60426e1cecfa97accc3)
|    |    |    |    +-PixUIPlugin_IOS_UPL_18_to_21_crosCurl.xml(md5:f83314b47cc3a4b74c8edb7dc5541ac4)
|    |    |    |    +-PixUIPlugin_IOS_UPL_18_to_21_pixuiCurl.xml(md5:fd8c5e0cfa5185fdc6307831cb78f94c)
|    |    |    |    +-PixUIPlugin_IOS_UPL_22_to_25_GPixUI.xml(md5:a92fdfceb344a79ce92e4b05e9e2be86)
|    |    |    |    +-PixUIPlugin_IOS_UPL_22_to_25_PixVideo.xml(md5:d41a9a9de62f769cc15359504279ae20)
|    |    |    |    +-PixUIPlugin_IOS_UPL_22_to_25_PxEmbedded.xml(md5:e9b8caae56dba5e31c47704835ec5e33)
|    |    |    |    +-PixUIPlugin_IOS_UPL_22_to_25_PxExtFFI.xml(md5:57b67bae1ddeea0518284225ceba8098)
|    |    |    |    +-PixUIPlugin_IOS_UPL_22_to_25_PxExtObjc.xml(md5:5b8c7ae212beedab0f857e34e06ba101)
|    |    |    |    +-PixUIPlugin_IOS_UPL_22_to_25_PxKit.xml(md5:1213e5e1080065024a7bfa8e05469826)
|    |    |    |    +-PixUIPlugin_IOS_UPL_22_to_25_crosCurl.xml(md5:be4ed5d8cae5b1b6ed7baa0cf9730a88)
|    |    |    |    +-PixUIPlugin_IOS_UPL_22_to_25_pixuiCurl.xml(md5:85366154d9eae35e1fb474a875217735)
|    |    +-PixUIEditor
|    |    |    +-PixUIEditor.Build.cs(md5:3127027540326d226d71ae2abd6a914a)
|    |    |    +-Private
|    |    |    |    +-PixUIAssetEditor
|    |    |    |    |    +-AssetTools
|    |    |    |    |    |    +-PixUIAsset.cpp(md5:9d4720eceac8f84710531ec0f0836ed3)
|    |    |    |    |    |    +-PixUIAsset.h(md5:5fa9f5c815de9637321cb1da59fffca5)
|    |    |    |    |    |    +-PixUIAssetActions.cpp(md5:96d3015a31d1cd56068bc1307165fdb6)
|    |    |    |    |    |    +-PixUIAssetActions.h(md5:bf7f1004937cc39fd8c61827008bce69)
|    |    |    |    |    +-Factories
|    |    |    |    |    |    +-PixUIAssetFactory.cpp(md5:899d9338963dc570a34f7e81b227f586)
|    |    |    |    |    |    +-PixUIAssetFactory.h(md5:33bc3cc8b4e48350130cb5c7c557f66a)
|    |    |    |    |    +-PixUIAssetEditor.cpp(md5:58ad4c6c721790ec1c992997e82530f4)
|    |    |    |    |    +-PixUIAssetEditor.h(md5:01ddf7be1b3617e0462baca3dbe70f6d)
|    |    |    |    |    +-Toolkits
|    |    |    |    |    |    +-PixUIAssetEditorToolkit.cpp(md5:d285e42335f64952e13408605d93ba65)
|    |    |    |    |    |    +-PixUIAssetEditorToolkit.h(md5:a233d9f7181d325cdaa7dfd61e420c00)
|    |    |    |    |    +-Widgets
|    |    |    |    |    |    +-SPixUIAssetEditor.cpp(md5:f2d2f7581193518f28cf996cc922f28b)
|    |    |    |    |    |    +-SPixUIAssetEditor.h(md5:242716e14194b00cdf00138d4e1d2c0f)
|    |    |    |    |    |    +-SPixUIWidgetEditor.cpp(md5:48cbad308332071d0d10fb933f9d4d0d)
|    |    |    |    |    |    +-SPixUIWidgetEditor.h(md5:62d3491cd15c4e34af83569ba0603d8a)
|    |    |    |    +-PixUIContentBrowserExtensions
|    |    |    |    |    +-PixUIContentBrowserExtensions.cpp(md5:b877c99de0f80b200ad51a7af779bfa4)
|    |    |    |    |    +-PixUIContentBrowserExtensions.h(md5:d2bb005d20769acde1cbf7c6d12fe739)
|    |    |    |    +-PixUIEditor.cpp(md5:0ff2ed5e8af7835f37a8d5e3bae31a37)
|    |    |    |    +-PixUIEditorMenuCommond
|    |    |    |    |    +-PixUIEditorMenuCommond.cpp(md5:07d0598eeac389dc6e2f9ce8ed7c620c)
|    |    |    |    |    +-PixUIEditorMenuCommond.h(md5:9d38efafa02388b32db35e2fa20c25d7)
|    |    |    |    +-PixUIEditorMgr.cpp(md5:de8fe3adfc9b5fe3fbd66905db40a097)
|    |    |    |    +-PixUIEditorMgr.h(md5:5aceabcd2ba089bde630d4ec88858c5c)
|    |    |    |    +-PixUIEditorSettings
|    |    |    |    |    +-PixUIEditorSettings.cpp(md5:a9f8e1fea2d77f5b2faa99ae7d2fe932)
|    |    |    |    |    +-PixUIEditorSettings.h(md5:7df3c65dce5ff22af235daa614867651)
|    |    |    |    +-SPixUIWidget.cpp(md5:406d8c26f792ab5a91680464bb26bf3e)
|    |    |    +-Public
|    |    |    |    +-PixUIEditor.h(md5:8a25ab4ac3fb62b30dfcecc5a3916dcd)
|    |    |    |    +-SPixUIWidget.h(md5:dcb86d594489e35f6c6a845f32d57d4f)
+-PluginCrosCurl
|    +-PluginCrosCurl.uplugin(md5:9271cfeb6072a3b41cb9af9e01a65503)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-PluginCrosCurl
|    |    |    +-PluginCrosCurl.Build.cs(md5:5634e89c4f4aee42ae4279a299e29288)
|    |    |    +-PluginCrosCurl_UPL.xml(md5:d0c829130210083155d906d3b1b9a1b6)
|    |    |    +-Private
|    |    |    |    +-PluginCrosCurlModule.cpp(md5:a3c6b46a96fc6cce39f76738bd3f9cc5)
|    |    |    +-Public
|    |    |    |    +-ICurlFunc.h(md5:67b343f76a6555f7c6fd6130ead8ea44)
|    |    |    |    +-ICurlFuncQueryService.h(md5:849d5beae0dc0a65c5bef26b134df27d)
|    |    |    |    +-IOpenSSLFunc.h(md5:2cffccf733d32c8c61b961233ef54519)
|    |    |    |    +-IOpenSSLFuncQueryService.h(md5:13948a826f7d7ef4b85f672fbbb22c7a)
|    |    |    |    +-PluginCrosCurlLifecycle.h(md5:433a1079f9143f5408381ac538937a39)
|    |    |    |    +-PluginCrosCurlModule.h(md5:71d17025dafce2c514a57b240b28daad)
|    |    |    |    +-crosCurl.h(md5:54ec327d84e5f4303934b454ee86d8e4)
|    |    |    |    +-crosCurlDefine.h(md5:ab9bc7834a4b8272d6d4207a3815612e)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-PluginCrosCurl
|    |    |    |    |    |    +-AndroidManifest.xml(md5:8a8296b026a73a2cca96bdc3286dbbc1)
|    |    |    |    |    |    +-additions.gradle(md5:a5aee16e52d3a0f1185b23ec2ba9f5a0)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    |    +-libPluginCrosCurl.so(md5:5b685a34a78d15cf25640b8e089c162e)
|    |    |    |    |    |    |    |    +-libcrosCurl.so(md5:d7c6f113ea9216e1a8c3f097ab7639f8)
|    |    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    |    +-libPluginCrosCurl.so(md5:51ad04c8f316d7a3a99a67c0c04d8650)
|    |    |    |    |    |    |    |    +-libcrosCurl.so(md5:fd4ccdb1bfe3b22f5620403e08474b86)
|    |    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    |    +-libPluginCrosCurl.so(md5:ec32ce1848d8a07dced9cf43ada6d899)
|    |    |    |    |    |    |    |    +-libcrosCurl.so(md5:bc2342d763ed56255ef03ce97dad1061)
|    |    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    |    +-libPluginCrosCurl.so(md5:393a02797e26884af369b9c0f5bd6721)
|    |    |    |    |    |    |    |    +-libcrosCurl.so(md5:f90eaa090fec69d411b5c46571ee4391)
|    |    |    |    |    |    +-proguard-project.txt(md5:d41d8cd98f00b204e9800998ecf8427e)
|    |    |    |    |    |    +-project.properties(md5:269b71902eb1ff0f8c098a12e9246a4d)
|    |    |    |    +-Mac
|    |    |    |    |    +-libcrosCurl.dylib(md5:a15ad3f903ad09eee196097ef71f3521)
|    |    |    |    +-Win32
|    |    |    |    |    +-libcrosCurl.dll(md5:bb76f5741239b5a25ff0a2abde6d152c)
|    |    |    |    |    +-libcrosCurl_imp.exp(md5:9649bfe57908935ec95c2905c41b4208)
|    |    |    |    |    +-libcrosCurl_imp.lib(md5:d567ffb8916656f0a3e9ffd9b3a1a646)
|    |    |    |    |    +-libcrypto-1_1.dll(md5:31fd103b4d9e01fd4863b23f5ff4dfd6)
|    |    |    |    |    +-libcrypto-1_1.pdb(md5:7e548b5037d7e3d7dbdefaeeb7c5e258)
|    |    |    |    |    +-libssl-1_1.dll(md5:1b874c92a2e3dd9396711da735384768)
|    |    |    |    |    +-libssl-1_1.pdb(md5:e6450fad835094f142cade14cc6994db)
|    |    |    |    +-Win64
|    |    |    |    |    +-libcrosCurl.dll(md5:bc4f82b9b5cec549545f403643fe6927)
|    |    |    |    |    +-libcrosCurl_imp.exp(md5:dbf07af1f0a2f267e1850ab3906f145e)
|    |    |    |    |    +-libcrosCurl_imp.lib(md5:d7268ad7465146a7d6b3a621d66dc34b)
|    |    |    |    |    +-libcrypto-1_1-x64.dll(md5:d349056dc60a9aa4c13d2e6f450b4090)
|    |    |    |    |    +-libcrypto-1_1-x64.pdb(md5:e16743713cb5b20787a6a5aab4935c78)
|    |    |    |    |    +-libssl-1_1-x64.dll(md5:66eea4e53d9cbe5a426fdb2b1ebea872)
|    |    |    |    |    +-libssl-1_1-x64.pdb(md5:30b9f642f770e7916d486d383619f9b6)
|    |    |    |    +-iOS
|    |    |    |    |    +-PluginCrosCurl
|    |    |    |    |    |    +-PluginCrosCurl.embeddedframework.zip(md5:ff1617ecb820e805509515001a1be200)
|    |    |    |    |    |    +-crosCurl.embeddedframework.zip(md5:88fe5170e0a8fb3b6856c3fe95d210b5)
+-TDM
|    +-Binaries
|    |    +-Win64
|    |    |    +-TDataMaster.dll(md5:51feed1a920dd05aaea487196ca6a857)
|    |    |    +-cacert.pem(md5:882db4f54c25b5157cef6c0d182e729e)
|    |    |    +-libcrypto-1_1.dll(md5:d38634f0b5d11fed982dd10e9ab06123)
|    |    |    +-libcurl.dll(md5:1efef1a288cbc48fe846d120a80c42f1)
|    |    |    +-libssh2.dll(md5:e9f2c86ae1d2233c0cfd820947a49719)
|    |    |    +-libssl-1_1.dll(md5:a0a250650713d0ba11cc8e6a62da33d5)
|    |    |    +-pthreadGC2.dll(md5:a8e566e3a09e9451c6d2c531758a5758)
|    |    |    +-pthreadVC2.dll(md5:4a502706d149c2f5854131a7758a90e2)
|    |    |    +-zlibwapi.dll(md5:e1dd4cdeef1651f21a80227c2db9623f)
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-TDM
|    |    |    +-Private
|    |    |    |    +-TDM.cpp(md5:3dfc430b5f95a4059a8662cd265f71a7)
|    |    |    +-Public
|    |    |    |    +-ITDataMaster.h(md5:cf88ec13694f6a9223c77792c1e85425)
|    |    |    |    +-ITDataMasterV2.h(md5:0b83ae9dbaa354bacb5a6fc5b2606784)
|    |    |    |    +-ITDataMasterV3.h(md5:96b8bf2f90ec59800bc3dff8cc061412)
|    |    |    |    +-ITDataMasterV4.h(md5:489557140cc00870f0ebf6ac8a0f94df)
|    |    |    |    +-ITDataMaster_GCloud.h(md5:b7752f8cde6a39c44caf67ee7f17227c)
|    |    |    |    +-TDM.h(md5:8aacbf37a569b12b4f943af196f6a293)
|    |    |    |    +-TDataMasterConfig.h(md5:f7e78a556dc0883888c04ade220697f0)
|    |    |    |    +-TDataMasterDefines.h(md5:eb5ac4a0ae5c2aadb7fc3de4487a7e00)
|    |    |    |    +-TDataMasterVersion.h(md5:e102c9a58df681c700ef7019de985ff7)
|    |    |    +-TDM.Build.cs(md5:8e80a2d5f51b0c011b62871643e54578)
|    |    |    +-TDM_APL.xml(md5:b21ce9934fd93a32fc9d6bfe1afc4b9c)
|    |    |    +-lib
|    |    |    |    +-Android
|    |    |    |    |    +-TDM
|    |    |    |    |    |    +-AndroidManifest.xml(md5:f40edf48b6102dbc37defbea4bf7e674)
|    |    |    |    |    |    +-additions.gradle(md5:b49cd1d70be26ae3c5541d5614f8713e)
|    |    |    |    |    |    +-libs
|    |    |    |    |    |    |    +-TDMBridge.jar(md5:31e078723cfaa0372b034aea12f32031)
|    |    |    |    |    |    |    +-TDMTencentAdapter.jar(md5:872177cea1e98e96930b2675e0146e0c)
|    |    |    |    |    |    |    +-TDataMaster.jar(md5:4c3503f4881ffa74c2c4e31f22bfe70d)
|    |    |    |    |    |    |    +-arm64-v8a
|    |    |    |    |    |    |    |    +-libTDataMaster.so(md5:8fb8b31e7f065865b5b2d2ec0f14b374)
|    |    |    |    |    |    |    |    +-libtdmbeaconid.so(md5:de35d1d4356949288e2d7bacfd5ed7b0)
|    |    |    |    |    |    |    +-armeabi-v7a
|    |    |    |    |    |    |    |    +-libTDataMaster.so(md5:5ac8883240fe96e552452183e6b5f5d0)
|    |    |    |    |    |    |    |    +-libtdmbeaconid.so(md5:3dd63058d139897767301e156dffb15f)
|    |    |    |    |    |    |    +-publish-fataar-tdm-release.jar(md5:790a52defc574557615c99ed07398d52)
|    |    |    |    |    |    |    +-x86
|    |    |    |    |    |    |    |    +-libTDataMaster.so(md5:327cf259a04e9517d7c12c3e41703936)
|    |    |    |    |    |    |    |    +-libtdmbeaconid.so(md5:f365806834748a143975b8d2e543c4f8)
|    |    |    |    |    |    |    +-x86_64
|    |    |    |    |    |    |    |    +-libTDataMaster.so(md5:3550d91b0bcb1733b8ad555cc2cdd22f)
|    |    |    |    |    |    |    |    +-libtdmbeaconid.so(md5:3500511b0f735e559c71a688a3485c08)
|    |    |    |    |    |    +-proguard-project.txt(md5:590be54a2e910fb665ad3fadb2f575fb)
|    |    |    |    |    |    +-project.properties(md5:269b71902eb1ff0f8c098a12e9246a4d)
|    |    |    |    +-MAC
|    |    |    |    |    +-libTDataMasterDylib.dylib(md5:bea2dd1b4af2c5e0e0a73dda63ae07c8)
|    |    |    |    +-Win64
|    |    |    |    |    +-TDataMaster.lib(md5:6dcdb0ef20ff8f2c553379e568206b25)
|    |    |    |    |    +-atls.lib(md5:8290e7ec9ad8428ca79301d57b573a05)
|    |    |    |    +-iOS
|    |    |    |    |    +-TDMASA.embeddedframework.zip(md5:6ebb16d672b4dce360ac752a72930a80)
|    |    |    |    |    +-TDMIDFA.embeddedframework.zip(md5:872b119578292f3b1ec8bdffe5b7e4f2)
|    |    |    |    |    +-TDMQimeiSDK.embeddedframework.zip(md5:f56f76a531c8d5a1d6c44f404a894280)
|    |    |    |    |    +-TDataMaster.embeddedframework.zip(md5:4206beca1eb8838f6811d7193a413d1a)
|    |    |    |    |    +-tgpasimple.embeddedframework.zip(md5:4ef208a442776da772ef7488e6c2fd96)
|    +-TDM.uplugin(md5:cb930a9f9d1da19619145facb9a82388)
+-UnionAdapter
|    +-Resources
|    |    +-Icon128.png(md5:7b15f15f14b3399e42fed1a64d9f0cb4)
|    +-Source
|    |    +-UnionAdapter
|    |    |    +-Private
|    |    |    |    +-MSDK
|    |    |    |    |    +-MSDKAccountService.cpp(md5:a4979ada5f85fb1cea28b05647cf658f)
|    |    |    |    |    +-MSDKCrashService.cpp(md5:7966a02f4a217e60558fec48c66d5003)
|    |    |    |    |    +-MSDKExtendService.cpp(md5:216d823bb3f4116469735a96e9e648e5)
|    |    |    |    |    +-MSDKFriendService.cpp(md5:69f6061d03bda9ac53103caacf548e92)
|    |    |    |    |    +-MSDKNoticeService.cpp(md5:8b5e73ecd2483e4ca4cdd3649798ee87)
|    |    |    |    |    +-MSDKPushService.cpp(md5:47ad81c09d1913f85966c36a5e079767)
|    |    |    |    |    +-MSDKReportService.cpp(md5:8b9a67284e4a23f2ba76626291a4da98)
|    |    |    |    |    +-MSDKStructUtility.cpp(md5:7fd17c1c88cb8a75e1cb3672224dca5e)
|    |    |    |    |    +-MSDKStructUtility.h(md5:a885e704616288e5da4d64066531a258)
|    |    |    |    |    +-MSDKToolsService.cpp(md5:eacc45cc41dd14e21646c179dd973e27)
|    |    |    |    |    +-MSDKWebviewService.cpp(md5:72e4efe28eac662ba3e64eac28b18288)
|    |    |    |    +-UnionAdapter.cpp(md5:ec8039fee5737550b144a41b0617a5e4)
|    |    |    +-Public
|    |    |    |    +-GUAAccountService.h(md5:ba9bbfdbe9ff6257387142b215440802)
|    |    |    |    +-GUACrashService.h(md5:b611aa45ec0fa40fe638df6cbd391239)
|    |    |    |    +-GUAErrorCode.h(md5:8b9e65c164ac2d1cb37777d0658331d5)
|    |    |    |    +-GUAExtendService.h(md5:839a66a0a2e8764854e4ef5a95e6ff80)
|    |    |    |    +-GUAFriendService.h(md5:d3e4f3d9b2cd7cb0deccf0a2e2b2a586)
|    |    |    |    +-GUANoticeService.h(md5:143cd1a5e45e69c21870b2ef15543981)
|    |    |    |    +-GUAPushService.h(md5:75c8f351fcbac8b3413d6755e59a5c5c)
|    |    |    |    +-GUAReportService.h(md5:c0e1cd5c4852823202c53a875ec743c7)
|    |    |    |    +-GUAToolsService.h(md5:c6641491c9600b9a809bfcfd12bd81ea)
|    |    |    |    +-GUAWebViewService.h(md5:8eb27b1a246a108b06fe258beea996dd)
|    |    |    |    +-UnionAdapter.h(md5:5e5dfaf2334fa205721b15bf74ebfe4f)
|    |    |    |    +-UnionAdapterDefine.h(md5:dd97497211b41cb121b10bb8d6f9ebd5)
|    |    |    +-UnionAdapter.Build.cs(md5:49bd50e8208d1f4822f9f60a231479b7)
|    +-UnionAdapter.uplugin(md5:7d1b98f27e2b7e856e35331eb36cf3ba)
+-readme.txt(md5:a37685bc4762b08b2301f0ba2c960dc8)
