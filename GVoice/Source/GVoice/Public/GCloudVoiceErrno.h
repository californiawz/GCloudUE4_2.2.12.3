/*******************************************************************************\
 ** File: GCloudVoiceErrno.h
 ** Module: GVoice
 ** Version: 1.0
 ** Author: CZ
 \*******************************************************************************/

#ifndef _GCloud_GVoice_GCloudVoiceErrno_h
#define _GCloud_GVoice_GCloudVoiceErrno_h

#if defined(WIN32) || defined(_WIN32)
    #ifdef GCLOUD_VOICE_EXPORTS
        #define GCLOUD_VOICE_API __declspec(dllexport)
    #else
        #define GCLOUD_VOICE_API __declspec(dllimport)
    #endif
#else
    #if defined __ANDROID__
        #define GCLOUD_VOICE_API __attribute__ ((visibility ("default")))
    #else
        #define GCLOUD_VOICE_API
    #endif
#endif

namespace GCloud
{
    namespace GVoice
    {
        /**
         * Speech Translation languages
         */
        enum SpeechLanguageType
        {
            SPEECH_LANGUAGE_ZH = 0,     // Chinese
            SPEECH_LANGUAGE_EN = 1,     // English
            SPEECH_LANGUAGE_JA = 2,     // Japanese
            SPEECH_LANGUAGE_KO = 3,     // Korean
            SPEECH_LANGUAGE_DE = 4,     // German
            SPEECH_LANGUAGE_FR = 5,     // French
            SPEECH_LANGUAGE_ES = 6,     // Spanish
            SPEECH_LANGUAGE_IT = 7,     // Italian
            SPEECH_LANGUAGE_TR = 8,     // Turkish
            SPEECH_LANGUAGE_RU = 9,     // Russian
            SPEECH_LANGUAGE_PT = 10,    // Portuguese
            SPEECH_LANGUAGE_VI = 11,    // Vietnamese
            SPEECH_LANGUAGE_ID = 12,    // Indonesian
            SPEECH_LANGUAGE_MS = 13,    // Malaysian
            SPEECH_LANGUAGE_TH = 14,    // Thai
            SPEECH_LANGUAGE_ZH_TW = 15, // Traditional Chinese, Text Language Of TTS or STT
            SPEECH_LANGUAGE_AF = 16,    // Afrikaans
            SPEECH_LANGUAGE_SQ = 17,    // Albanian
            SPEECH_LANGUAGE_AM = 18,    // Amharic
            SPEECH_LANGUAGE_AR = 19,    // Arabic
            SPEECH_LANGUAGE_HY = 20,    // Armenian
            SPEECH_LANGUAGE_AZ = 21,    // Azerbaijani
            SPEECH_LANGUAGE_EU = 22,    // Basque
            SPEECH_LANGUAGE_BN = 23,    // Bengali
            SPEECH_LANGUAGE_BS = 24,    // Bosnian
            SPEECH_LANGUAGE_BG = 25,    // Bulgarian
            SPEECH_LANGUAGE_MY = 26,    // Burmese
            SPEECH_LANGUAGE_CA = 27,    // Catalan
            SPEECH_LANGUAGE_HR = 28,    // Croatian
            SPEECH_LANGUAGE_CS = 29,    // Czech
            SPEECH_LANGUAGE_DA = 30,    // Danish
            SPEECH_LANGUAGE_NL = 31,    // Dutch
            SPEECH_LANGUAGE_ET = 32,    // Estonian
            SPEECH_LANGUAGE_FIL = 33,   // Filipino
            SPEECH_LANGUAGE_FI = 34,    // Finnish
            SPEECH_LANGUAGE_GL = 35,    // Galician
            SPEECH_LANGUAGE_KA = 36,    // Georgian
            SPEECH_LANGUAGE_EL = 37,    // Greek
            SPEECH_LANGUAGE_GU = 38,    // Gujarati
            SPEECH_LANGUAGE_IW = 39,    // Hebrew
            SPEECH_LANGUAGE_HI = 40,    // Hindi
            SPEECH_LANGUAGE_HU = 41,    // Hungarian
            SPEECH_LANGUAGE_IS = 42,    // Icelandic
            SPEECH_LANGUAGE_JV = 43,    // Javanese
            SPEECH_LANGUAGE_KN = 44,    // Kannada
            SPEECH_LANGUAGE_KK = 45,    // Kazakh
            SPEECH_LANGUAGE_KM = 46,    // Cambodian
            SPEECH_LANGUAGE_LO = 47,    // Lao
            SPEECH_LANGUAGE_LV = 48,    // Latvian
            SPEECH_LANGUAGE_LT = 49,    // Lithuanian
            SPEECH_LANGUAGE_MK = 50,    // Macedonian
            SPEECH_LANGUAGE_ML = 51,    // Malayalam
            SPEECH_LANGUAGE_MR = 52,    // Marathi
            SPEECH_LANGUAGE_MN = 53,    // Mongolian
            SPEECH_LANGUAGE_NE = 54,    // Nepali
            SPEECH_LANGUAGE_NO = 55,    // Bokmal Norwegian
            SPEECH_LANGUAGE_FA = 56,    // Persian
            SPEECH_LANGUAGE_PL = 57,    // Polish
            SPEECH_LANGUAGE_PA = 58,    // Punjabi
            SPEECH_LANGUAGE_RO = 59,    // Romanian
            SPEECH_LANGUAGE_SR = 60,    // Serbian
            SPEECH_LANGUAGE_SI = 61,    // Sinhala
            SPEECH_LANGUAGE_SK = 62,    // Slovak
            SPEECH_LANGUAGE_SL = 63,    // Slovenian
            SPEECH_LANGUAGE_SU = 64,    // Sundanese
            SPEECH_LANGUAGE_SW = 65,    // Swahili
            SPEECH_LANGUAGE_SV = 66,    // Swedish
            SPEECH_LANGUAGE_TA = 67,    // Tamil
            SPEECH_LANGUAGE_TE = 68,    // Telugu
            SPEECH_LANGUAGE_UK = 69,    // Ukrainian
            SPEECH_LANGUAGE_UR = 70,    // Urdu
            SPEECH_LANGUAGE_UZ = 71,    // Uzbek
            SPEECH_LANGUAGE_ZU = 72,    // Zulu
            SPEECH_LANGUAGE_CNT,
        };
        
        /**
         * Speech Translation type, pip nodes: Source Speech -> Source Text -> Target Text -> Target Speech
         */
        enum SpeechTranslateType
        {
            SPEECH_TRANSLATE_STST = 0,    //Source Speech -> Source Text
            SPEECH_TRANSLATE_STTT = 1,    //Source Speech -> Source Text -> Target Text
            SPEECH_TRANSLATE_STTS = 2,    //Source Speech -> Source Text -> Target Text -> Target Speech
        };
    
        /**
        * realtime voice translate type
        */
        enum RealTimeTranslateType
        {
            RT_TRANSLATE_TEXT = 1,            // my speech to text
            RT_TRANSLATE_SPEECH = 2,          // my speech to other language speech
            RT_TRANSLATE_SPEECH_AND_TEXT = 3, // 
        };

        /**
         * The URLs can be changed by functiion SetServerUrl.
         */
        enum UrlType {
            GV_URL_TRANSLATE     = 1,  // URL used in the translate function
            GV_URL_REMOTE_CONFIG = 2,  // The remote config URL
            GV_URL_LOG_REPORT    = 3,  // The log report URL
            GV_URL_VOICE_REPORT  = 4,  // URL used in the voice report function
            GV_URL_FLQ           = 5,  // URL used in the FLQ function
            GV_URL_DATA_REPORT   = 6,  // The data report URL
        };

        enum SoundTag {
            GVST_kNone        = 0,  // 关闭

            GVST_kLow         = 1,  // 低沉
            GVST_kBright      = 2,  // 明亮
            GVST_kMagnetic    = 3,  // 磁性
            GVST_kSoft        = 4,  // 柔和
            GVST_kComposed    = 5,  // 沉稳
            GVST_kSweet       = 6,  // 甜美
            GVST_kRecord      = 7,  // 老唱片 有效值：0.0，1.0，2.0对应新式，标准，老式唱片 

            GVST_kLolita      = 8,  // 超级萝莉
            GVST_kUncle       = 9,  // 大叔 有效范围：[0,100]值越小，越接近原声 
            GVST_kMinions     = 10, // 小黄人
            GVST_kSweetLolita = 11, // 甜美萝莉 有效范围：[0，100]值越⼩，越接近原声 

            GVST_kOldman      = 12, // 老男人
            GVST_kAlien       = 13, // 外星人 config[0]: ⾳效开始时间config[1]: ⾳效过渡时⻓单位: 秒 

            GVST_kRobot       = 14, // 机器人
            GVST_kGiantRobot  = 15, // 巨型机器人 有效范围：[0，100]值越大，越浑浊 
            GVST_kAstronaut   = 16, // 宇航员

            GVST_kVocalE      = 17, // 人声增强 有效值: 1.0，2.0，3.0对应低，中，⾼程度的增强 

            GVST_kChurch      = 18, // 教堂
            GVST_kGlass       = 19, // 玻璃
            GVST_kHall        = 20, // 大厅
            GVST_kStudy       = 21, // 自习
            GVST_kTheater     = 22, // 剧场
            GVST_kLecture     = 23, // 演讲
            GVST_kStereo      = 24, // 立体
            GVST_kDynamic3D   = 25, // 动感3D 有效范围：[0，100]值越⼤，3D转速越快  

            GVST_kFlanger     = 26, // 镶边
            GVST_kVibrato     = 27, // 颤音
            GVST_kChrous      = 28, // 合唱

            GVST_kChangeTempo = 29, // 变速不变调 有效值: 0.1~5.0⼩于1代表降速，⼤于1代表升速 
            GVST_kChangePitch = 30, // 变调不变速 有效值: 0.1~5.0⼩于1代表降调，⼤于1代表升调 
            GVST_kChangeRate  = 31, // 变调又变速 有效值: 0.1~10.0 

            GVST_kUserEQ      = 32, // 供用户调节的均衡器 gains[0]: 低⾳增益gains[1]: ⾼⾳增益单位: dB，有效范围: [-15,15] 
            GVST_kBoy         = 33, // 男童
            GVST_kGirl        = 34, // 女童
        };
        
        enum ErrorNo
        {
            kErrorNoSucc                    = 0,                       // 0, no error
            
            //common base err
            kErrorParseJSON                 = 0x1000,                  // 4096, parse JSON error
            kErrorNoParamNULL               = 0x1001,                  // 4097, some param is null
            kErrorNoNeedSetAppInfo          = 0x1002,                  // 4098, you should call SetAppInfo first before call other api
            kErrorNoInitErr                 = 0x1003,                  // 4099, Init Erro
            kErrorNoRecordingErr            = 0x1004,                  // 4100, now is recording, can't do other operator
            kErrorNoPollBuffErr             = 0x1005,                  // 4101, poll buffer is not enough or null
            kErrorNoModeStateErr            = 0x1006,                  // 4102, call some api, but the mode is not correct, maybe you shoud call SetMode first and correct
            kErrorNoParamInvalid            = 0x1007,                  // 4103, some param is null or value is invalid for our request, used right param and make sure is value range is correct by our comment
            kErrorNoOpenFileErr             = 0x1008,                  // 4104, open a file err
            kErrorNoNeedInit                = 0x1009,                  // 4105, you should call Init before do this operator
            kErrorNoEngineErr               = 0x100A,                  // 4106, you have not get engine instance, this common in use c# api, but not get gcloudvoice instance first
            kErrorNoPollMsgParseErr         = 0x100B,                  // 4107, this common in c# api, parse poll msg err
            kErrorNoPollMsgNo               = 0x100C,                  // 4108, poll, no msg to update
            kErrorNoModeErr                 = 0x100D,                  // 4109, The mode is not support
            kErrorNoFunctionNotSupport      = 0x100E,                  // 4110, the function is not support
			kErrorNoParseConfigErr          = 0x100F,                  // 4111, parse config.json error
			GCLOUD_VOICE_POLL_MSG_MORE      = 0x1010,                  // 4112, poll. have more msg
            
            //realtime err
            kErrorNoRealtimeStateErr        = 0x2001,                  // 8193, call some realtime api, but state err, such as OpenMic but you have not Join Room first
            kErrorNoJoinErr                 = 0x2002,                  // 8194, join room failed
            kErrorNoQuitRoomNameErr         = 0x2003,                  // 8195, quit room err, the quit roomname not equal join roomname
            kErrorNoOpenMicNotAnchorErr     = 0x2004,                  // 8196, open mic in bigroom,but not anchor role
            kErrorNoCreateRoomErr           = 0x2005,                  // 8197, create room error
            kErrorNoNoRoom                  = 0x2006,                  // 8198, no such room
            kErrorNoQuitRoomErr             = 0x2007,                  // 8199, quit room error
            kErrorNoAlreadyInTheRoom        = 0x2008,                  // 8200, already in the room which in JoinXxxxRoom
            
            //message err
            kErrorNoAuthKeyErr              = 0x3001,                  // 12289, apply authkey api error
            kErrorNoPathAccessErr           = 0x3002,                  // 12290, the path can not access ,may be path file not exists or deny to access
            kErrorNoPermissionMicErr        = 0x3003,                  // 12291, you have not right to access micphone in android
            kErrorNoNeedAuthKey             = 0x3004,                  // 12292,you have not get authkey, call ApplyMessageKey first
            kErrorNoUploadErr               = 0x3005,                  // 12293, upload file err
            kErrorNoHttpBusy                = 0x3006,                  // 12294, http is busy,maybe the last upload/download not finish.
            kErrorNoDownloadErr             = 0x3007,                  // 12295, download file err
            kErrorNoSpeakerErr              = 0x3008,                  // 12296, open or close speaker tve error
            kErrorNoTVEPlaySoundErr         = 0x3009,                  // 12297, tve play file error
            kErrorNoAuthing                 = 0x300a,                  // 12298, Already in applying auth key processing
            kErrorNoLimit                   = 0x300b,                  // 12299, upload limit
            kErrorNoNothingToReport         = 0x300c,                  // 12300, no sound to report
            
            kErrorNoInternalTVEErr          = 0x5001,                  // 20481, internal TVE err, our used
            kErrorNoInternalVisitErr        = 0x5002,                  // 20482, internal Not TVE err, out used
            kErrorNoInternalUsed            = 0x5003,                  // 20483, internal used, you should not get this err num
            
            kErrorNoBadServer               = 0x06001,                  // 24577, bad server address,should be "udp://capi.xxx.xxx.com"
            
            kErrorNoSTTing                  =  0x07001,                 // 28673, Already in speach to text processing
            
            kErrorNoChangeRole              = 0x08001,                  // 32769, change role error
            kErrorNoChangingRole            = 0x08002,                  // 32770, is in changing role
            kErrorNoNotInRoom               = 0x08003,                  // 32771, no in room
            kErrorNoCoordinate              = 0x09001,                  // 36865, sync coordinate error
            kErrorNoSmallRoomName           = 0x09002,                  // 36866, query with a small roomname
            kErrorNoCoordinateRoomNameError = 0x09003,                  // 36867, update coordinate in a non-exist room
            
            kErrorSaveDataDownloading       = 0x0A001,                  // 40961, dowloading file for lgame save voice data, need no nothing, just let userinterface know.
            kErrorSaveDataIndexNotFound     = 0x0A002,                  // 40962, this file index not found in file map ,may not set ,have not in this video
            kErrorDeviceTveErr              = 0x0C001,                  // 49153, device internal error
            kErrorErrorUrlType              = 0x0C002,                  // 49154, wrong url type, you should give the url according to the enum UrlType
        };
    
        enum CompleteCode
        {
            // common code
            kCompleteCodeOk                      = 0x1000,              // 4096, ok.
            kCompleteCodeNetErr                  = 0x1001,              // 4097, network error, maybe can't connect to ne
            kCompleteCodeUnknown                 = 0x1002,              // 4098
            kCompleteCodeInternalErr             = 0x1003,              // 4099, this error needs log for problem location
            kCompleteCodeBusinessNotFound        = 0x1004,              // 4100, the business not found, maybe you do not open the service
            kCompleteCodeFail                    = 0x1005,              // 4101, fail.
            kCompleteCodeShouldOneRoomOneScenes  = 0x1006,              // 4102, a room can only be associated with one scene.
            
            
            // realtime code
            kCompleteCodeJoinRoomSucc       = 0x2001,                    // 8193, join room success
            kCompleteCodeJoinRoomTimeout    = 0x2002,                    // 8194, join room timeout
            kCompleteCodeJoinRoomSVRErr     = 0x2003,                    // 8195, communication with svr meets some error, such as wrong data received from svr
            kCompleteCodeJoinRoomUnknown    = 0x2004,                    // 8196, reserved, GVoice internal unknown error
            kCompleteCodeJoinRoomRetryFail  = 0x2005,                    // 8197, join room try again fail
            kCompleteCodeQuitRoomSucc       = 0x2006,                    // 8198, quitroom success, if you have joined room success first, quit room will alway return success
            kCompleteCodeRoomOffline        = 0x2007,                    // 8199, dropped from the room
            kCompleteCodeRoleSucc           = 0x2008,                    // 8200, change role success
            kCompleteCodeRoleTimeout        = 0x2009,                    // 8201, change role timeout
            kCompleteCodeRoleMaxAnchor      = 0x2010,                    // 8202, too many anchors, no more than 5 anchors in the same time are allowed in a national room
            kCompleteCodeRoleNoChange       = 0x2011,                    // 8203, the same role as before
            kCompleteCodeRoleSvrErr         = 0x2012,                    // 8204, server's error in change role
            
            // message mode
            kCompleteCodeMessageKeyAppliedSucc    = 0x3001,              // 12289, apply message authkey succ
            kCompleteCodeMessageKeyAppliedTimeout = 0x3002,              // 12290, apply message authkey timeout
            kCompleteCodeMessageKeyAppliedSVRErr  = 0x3003,              // 12291, communication with svr meets some error, such as wrong data received
            kCompleteCodeMessageKeyAppliedUnknown = 0x3004,              // 12292, reserved, GVoice internal unknown error
            
            kCompleteCodeUploadRecordDone         = 0x3005,              // 12293, upload record file success
            kCompleteCodeUploadRecordError        = 0x3006,              // 12294, upload record file meets some error
            kCompleteCodeDownloadRecordDone       = 0x3007,              // 12295, download record file success
            kCompleteCodeDownloadRecordError      = 0x3008,              // 12296, download record file meets some error
            kCompleteCodePlayFileDone             = 0x3009,              // 12297, the record file have played to the end
            
            // translate mode
            kCompleteCodeSTTSucc                  = 0x4001,              // 16385, speech to text success
            kCompleteCodeSTTTimeout               = 0x4002,              // 16386, speech to text timeout
            kCompleteCodeSTTAPIErr                = 0x4003,              // 16387, server's error
            
            // rstt mode
            kCompleteCodeRSTTSucc                 = 0x5001,              // 20481, stream speech to text success
            kCompleteCodeRSTTTimeout              = 0x5002,              // 20482, stream speech to text timeout
            kCompleteCodeRSTTAPIErr               = 0x5003,              // 20483, server's error in stream speech to text
            kCompleteCodeRSTTRetry                = 0x5004,              // 20484, need retry stt
            kCompleteCodeRSTTShort                = 0x5005,              // 20485，speak time is too short
            
            // voice report
            kCompleteCodeReportSucc               = 0x6001,              // 24577, report other player succ
            kCompleteCodeDataError                = 0x6002,              // 24578, receive illegal or invalid data from serve
            kCompleteCodePunished                 = 0x6003,              // 24579, the player is punished because of being reported
            kCompleteCodeNotPunished              = 0x6004,              // 24580, the player
            kCompleteCodeKeyDeleted               = 0x6005,              // 24581
            kCompleteCodeReportSuccSelf           = 0x6006,
            // for LGame
            kCompleteCodeSaveDataSucc             = 0x7001,              // 28673, LGAME Save RecData
            kCompleteCodeKaraokeDone              = 0x7002,
            kCompleteCodeKaraokeCancel            = 0x7003,
            
            // member synchornize
            kCompleteCodeRoomMemberInRoom         = 0x8001,              // 32769, member join or in room
            kCompleteCodeRoomMemberOutRoom        = 0x8002,              // 32770, member out of room
            kCompleteCodeRoomMemberMicOpen        = 0x8003,              // 32771, member mic is open
            kCompleteCodeRoomMemberMicClose       = 0x8004,              // 32772, member mic is close
            kCompleteCodeDeviceEventAdd           = 0x8101,              // 33025, device event notify
            kCompleteCodeDeviceEventUnusable      = 0x8102,              // 33026, device unusable event
            kCompleteCodeDeviceEventDefaultChange = 0x8103,              // 33027, default event changed
            
            // for civilized voice
            kCompleteCodeUploadReportInfoError    = 0x9001,              // 36865, civilized voice reporting error
            kCompleteCodeUploadReportInfoTimeout  = 0x9002,              // 36866, civilized voice reporting timeout
            
            // for speech translate
            kCompleteCodeStSucc                   = 0xA001,              // 40961, speech translate success
            kCompleteCodeStHttpError              = 0xA002,              // 40962, http failed
            kCompleteCodeStServerError            = 0xA003,              // 40963, server error
            kCompleteCodeStInvalidJson            = 0xA004,              // 40964, parse rsp json faild
			kCompleteCodeStAlreadyExist			  = 0xA005,    			 // 40965, doing already.
			kCompleteCodeStRcFailed				  = 0xA006,    			 // 40966, resource alloc failed.
		
            //for realtime translate
            kCompleteCodeTranslateSucc			  = 0xC001,	             // 49153, realtime enable translate ok
            kCompleteCodeTranslateServerErr		  = 0xC002,	             // 49154, realtime enable translate server error
            
            // for magic voice
            kCompleteCodeMagicVoiceSucc           = 0xD001,              // 53249, enable magic voice success in realtime mode
            kCompleteCodeMagicVoiceServerErr      = 0xD002,              // 53250, enable magic voice failed in realtime mode
            kCompleteCodeRecvMagicVoiceSucc       = 0xD003,              // 53251, enable recv magic voice success in realtime mode
            kCompleteCodeRecvMagicVoiceServerErr  = 0xD004,              // 53252, enable recv magic voice failed in realtime mode
            kCompleteCodeMagicVoiceFileSucc       = 0xD005,              // 53253, magic voice offline file upload succ
            kCompleteCodeMagicVoiceFileFail       = 0xD006,              // 53254, magic voice offline file record fail
        };
    
        /**
         * Event of GCloudVoice.
         *
         */
        enum Event
        {
            kEventNoDeviceConnected               = 0,                   // not any device is connected
            kEventHeadsetDisconnected             = 10,                  // a headset device is connected
            kEventHeadsetConnected                = 11,                  // a headset device is disconnected
            kEventBluetoothHeadsetDisconnected    = 20,                  // a bluetooth device is connected
            kEventBluetoothHeadsetConnected       = 21,                  // a bluetooth device is disconnected
            kEventMicStateOpenSucc                = 30,                  // open microphone
            kEventMicStateOpenErr                 = 31,                  // open microphone
            kEventMicStateNoOpen                  = 32,                  // close micrphone
            kEventMicStateOccupancy               = 33,                  // indicates the microphone has been occupancyed by others
            kEventSpeakerStateOpenSucc            = 40,                  // open speaker
            kEventSpeakerStateOpenErr             = 41,                  // open speaker error
            kEventSpeakerStateNoOpen              = 42,                  // close speaker
            kEventAudioInterruptBegin             = 50,                  // audio device begin to be interrupted
            kEventAudioInterruptEnd               = 51,                  // audio device end to be interrupted
            kEventAudioRecoderException           = 52,                  // indicates the recorder thread throws a exception, maybe you can resume the audio
            kEventAudioRenderException            = 53,                  // indicates the render thread throws a exception, maybe you can resume the audio
            kEventPhoneCallPickUp                 = 54,                  // indicates that you picked up the phone
            kEventPhoneCallHangUp                 = 55,                  // indicates that you hanged up the phone
        };
    
        /**
         * Event of GCloudVoice.
         *
         */
        enum DeviceState
        {
            kDeviceStateUnconnected               = 0,                   // not any audio device is connected
            kDeviceStateWriteHeadsetConnected     = 1,                   // have a wiredheadset device is connected
            kDeviceStateBluetoothConnected        = 2,                   // have a bluetooth device is disconnected
        };

        enum DeviceType {
            RENDER_DEVICE  = 0,
            CAPTURE_DEVICE = 1,
        };
        
    } // endof namespace GVoice
} // endof namespace GCloud

#endif /* _GCloud_GVoice_GCloudVoiceErrno_h */
