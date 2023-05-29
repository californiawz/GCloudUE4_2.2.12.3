/*******************************************************************************\
** File: IGCloudVoiceEngineNotify.h
** Module: GVoice
** Version: 1.0
** Author: CZ
\*******************************************************************************/

#ifndef _GCloud_GVoice_IGCloudVoiceNotify_h
#define _GCloud_GVoice_IGCloudVoiceNotify_h

#include "GCloudVoiceErrno.h"

namespace GCloud
{
    namespace GVoice
    {
        /**
         * IGCloudVoiceNotify is a notify for voice engine. You should implemtation it to get the message.
         */
        class GCLOUD_VOICE_API IGCloudVoiceNotify
        {
        public:
            virtual ~IGCloudVoiceNotify() {};
            
        public:
            /*************************************************************
             *                  Real-Time Voice Callbacks
             *************************************************************/
            /**
             * Callback after you called JoinXxxRoom, you can get the result of JoinXxxRoom from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param roomName: Name of the room which you joined, it is the one you set in JoinXxxRoom method.
             * @param memberID: If success, returns the player's ID in this room.
             * @see JoinTeamRoom, JoinNationalRoom, JoinRangeRoom
             * @see CompleteCode
             */
            virtual void OnJoinRoom(CompleteCode code, const char *roomName, int memberID) = 0;
            
            /**
             * Callback when someone in the same room changes saying status, such as begining saying from silence or stopping saying.
             *
             * @param members: An int array composed of [memberid_0, status, memberid_1, status ... memberid_2*count, status],
             * here, status could be 0, 1, 2. 0 means being silence from saying, 1 means begining saying from silence
             * and 2 means continue saying.
             * @param count: The count of members who's status has changed.
             */
            virtual void OnMemberVoice(const unsigned int *members, int count) = 0;
            
            /**
             * Callback when someone in the same room changes saying status, such as begining saying from silence or stopping saying.
             *
             * @param roomName: Name of the room which you joined.
             * @param member: The ID of the member who's status has changed.
             * @param status : Status could be 0, 1, 2. 0 means being silence from saying, 1 means begining saying from silence
             * and 2 means continue saying.
             */
            virtual void OnMemberVoice (const char *roomName, unsigned int member, int status) = 0;
            
			/**
			* Callback when someone in the same room changes saying status, such as begining saying from silence or stopping saying.
			* !!!Only work for Team\Range room, do not work for national room.
			* @param roomName: Name of the room which you joined.
			* @param openid: The ID of the user who's status has changed.
			* @param member: The ID of the room member who's status has changed.
			* @param status : Status could be 0, 1, 2. 0 means being silence from saying, 1 means begining saying from silence
			* and 2 means continue saying.
			*/
			virtual void OnMemberVoice(const char *roomName, const char* openid, unsigned int member, int status) = 0;

            /**
             * Callback after you called ChangeRole, you can get the result of ChangeRole from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param roomName: Name of the room which the member joined.
             * @param memberID: The ID of the member who changed role.
             * @param role: Current role of the member, Anchor or Audience.
             * @see ChangeRole
             * @see CompleteCode
             */
            virtual void OnRoleChanged(CompleteCode code, const char *roomName, int memberID, int role) = 0;
            
            /**
             * Callback when dropped from the room. When a member be offline more than 1min, he will be dropped from the room.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param roomName: Name of the room which the member joined.
             * @param memberID: If success, return the ID of the mermber who has been dropped from the room.
             * @see CompleteCode
             */
            virtual void OnStatusUpdate(CompleteCode status, const char *roomName, int memberID) = 0;
            
            /**
             * Callback after you called QuitRoom, you can get the result of QuitRoom from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param roomName: Name of the room which you quited.
             * @see QuitRoom
             * @see CompleteCode
             */
            virtual void OnQuitRoom(CompleteCode code, const char *roomName) = 0;
            
            
            /*************************************************************
             *                  Voice Messages Callbacks
             *************************************************************/
            /**
             * Callback after you called ApplyMessageKey, you can get the result of ApplyMessageKey from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @see ApplyMessageKey
             * @see CompleteCode
             */
            virtual void OnApplyMessageKey(CompleteCode code) = 0;
            
            /**
             * Callback when client is using microphone recording audio.
             *
             * @param pAudioData: Audio data pointer.
             * @param nDataLength: Audio data length.
             */
            virtual void OnRecording(const unsigned char* audioData, unsigned int dataLength) = 0;

			/**
			 * Callback when playing audio.
			 *
			 * @param buf: Audio data pointer.
			 * @param nLen: Audio data length.
			 */
			virtual void OnPlayingData(const unsigned char* buf, const int nLen) = 0;
            
            /**
             * Callback after you called UploadRecordedFile, you can get the result of UploadRecordedFile from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param filePath: The path of the voice file uploaded.
             * @param fileID: If success, return the ID of the file.
             * @see UploadRecordedFile
             * @see CompleteCode
             */
            virtual void OnUploadFile(CompleteCode code, const char *filePath, const char *fileID) = 0;
            
            /**
             * Callback after you called DownloadRecordedFile, you can get the result of DownloadRecordedFile from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param filePath: The path of the file which the voice download to.
             * @param fileID: If success,return the ID of the file.
             * @see DownloadRecordedFile
             * @see CompleteCode
             */
            virtual void OnDownloadFile(CompleteCode code, const char *filePath, const char *fileID) = 0;
            
            /**
             * Callback after you called PlayRecordedFile and the voice file has been played to the end, you can get the result of PlayRecordedFile from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param filePath: The path of the file which had been played.
             * @see PlayRecordedFile
             * @see CompleteCode
             */
            virtual void OnPlayRecordedFile(CompleteCode code,const char *filePath) = 0;
            
            
            /*************************************************************
             *                  Translation Callbacks
             *************************************************************/
            /**
             * Callback after you called SpeechToText, you can get the result of SpeechToText from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param fileID: The ID of the file which had been translated.
             * @param result: If success, return the translation result, which is a piece of text in a specific language.
             * @see SpeechToText
             * @see CompleteCode
             */
            virtual void OnSpeechToText(CompleteCode code, const char *fileID, const char *result) = 0;
            
            /**
             * Callback after you called StopRecording in RSTT mode, you can get the result of stream speech to text from the parameters.
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param error: An error code for internal use, you can ignore it.
             * @param result: If success, return the translation result, which is a piece of text in a specific language.
             * @param voicePath: The path of the voice file.
             * @see CompleteCode
             */
            virtual void OnStreamSpeechToText(CompleteCode code, int error, const char *result, const char *voicePath) = 0;
            
            
            /*************************************************************
             *                  Other Callbacks
             *************************************************************/
            /**
             * Event Callback. e.g. the device connect Event, the device disconcet Event
             * @see GCloudVoiceEvent
             */
            virtual void OnEvent(Event event, const char * info) = 0;
            
            /**
             * Callback after you called CheckDeviceMuteState, you can get the result of CheckDeviceMuteState from the parameters.
             *
             * @param nState: Mute state flag. Non-zero means mute state.
             * @see ErrorNo IGCloudVoiceEngine::CheckDeviceMuteState()
             **/
            virtual void OnMuteSwitchResult(int nState) = 0;
            
            /**
             * Callback after you called ReportPlayer.
             *
             * @param nCode: the reported result, 0 means server receive your reporter succ, @see CompleteCode
             * @param cszInfo: the infomation got from server
             * @see: CompleteCode
             **/
            virtual void OnReportPlayer(CompleteCode nCode, const char* cszInfo) = 0;
            
            /**
             * Callback for LGame.
             * Callback when rec and upload the fileindex for LGameVideo Voice.
             **/
            virtual void OnSaveRecFileIndex(CompleteCode code, const char *fileid, int fileindex) = 0;
            
            /**
             * Callback when member join in room or quit room.
             *
             * @param nCode: GV_ON_ROOM_MEMBER_INROOM/GV_ON_ROOM_MEMBER_OUTROOM, @see CompleteCode
             * @param roomNam: roomName
             * @param memid : room memberid
             * @param openID : openid
             *
             * @see: CompleteCode
             **/
            virtual void OnRoomMemberInfo(CompleteCode code, const char* roomName, int memid, const char* openID) = 0;
            
            /**
             * Callback function for voice message translate.
             *
             * @param nCode: this operation's result, @see CompleteCode
             * @param srcText: text that the source speech file translate to
             * @param targetText: target text that translated from source text
             * @param targetFileID: ID of the target speech file
             * @param duration of the source speech file, the unit is milliseconds
             *
             * @see: CompleteCode
             **/
            virtual void OnSpeechTranslate(CompleteCode nCode, const char* srcText, const char* targetText, const char* targetFileID, int srcFileDuration) = 0;
            
            /** 
             * Callback function for speech translate
             *
             * @param nCode, this operation's result @enum CompleteCode.
             * @param srcText, text that the source speech file translate to.
             * @param targetText, target text that translated from source text.
             * @param filePath, target speech file.
             * @param srcFileDuration, duration of the source speech file, the unit is milliseconds.
             */ 
            virtual void OnSpeechFileTranslate(CompleteCode nCode, const char* srcText, const char* targetText, const char* filePath, int srcFileDuration) = 0;


            /** 
             * Callback function for speech translate
             *
             * @param nCode, this operation's result @enum CompleteCode.
             * @param srcText, text that the source speech file translate to.
             * @param targetText, target text that translated from source text.
             * @param srcFileDuration, duration of the source speech file, the unit is milliseconds.
             */ 
            virtual void OnSpeechFileToText(CompleteCode nCode, const char* srcText, const char* targetText, int srcFileDuration) = 0;
            
            /**
             * Callback function for real-time voice message translate.
             *
             * @param nCode: this operation's result, @see CompleteCode
             * @param srcLang: speech language associated with fileID.
             * @param targetLang: target language that we want to translate to.
             * @param srcText: text that the source speech file translate to.
             * @param targetText: target text that translated from source text.
             * @param targetFileID: ID of the target speech file.
             * @param srcFileDuration: duration of the source speech file, the unit is milliseconds.
             * @param recordFilePath, The path of the file of recorded voice data, the filePath should like:"your_dir/your_file_name" or "" witch means no need to save.
             */
            virtual void OnRSTS(CompleteCode nCode, SpeechLanguageType srcLang, SpeechLanguageType targetLang, const char* srcText, const char* targetText, const char* targetFileID, int srcFileDuration, const char* recordFilePath) = 0;

            /**
             * Callback function for RSTSSpeechToSpeech
             * 
             * @param nCode, this operation's result @enum CompleteCode.
             * @param srcLang, speech language associated with fileID.
             * @param targetLang, target language that we want to translate to.
             * @param srcText, text that the source speech file translate to.
             * @param targetText, target text that translated from source text.
             * @param filePath, target speech file.
             * @param srcFileDuration, duration of the source speech file, the unit is milliseconds.
			 * @param recordFilePath, The path of the file of recorded voice data, the filePath should like:"your_dir/your_file_name" or "" witch means no need to save.
             */ 
            virtual void OnRSTSSpeechToSpeech(CompleteCode nCode, SpeechLanguageType srcLang, SpeechLanguageType targetLang, const char* srcText, const char* targetText, const char* filePath, int srcFileDuration, const char* recordFilePath) = 0;

            /**
             * Callback function for RSTSSpeechToText
             *
             * @param nCode, this operation's result @enum CompleteCode.
             * @param srcLang, speech language.
             * @param targetLang, target language that we want to translate to.
             * @param srcText, text that the source speech file translate to.
             * @param targetText, target text that translated from source text.
             * @param srcFileDuration, duration of the source speech file, the unit is milliseconds.
			 * @param recordFilePath, The path of the file of recorded voice data, the filePath should like:"your_dir/your_file_name" or "" witch means no need to save.
             */ 
            virtual void OnRSTSSpeechToText(CompleteCode nCode, SpeechLanguageType srcLang, SpeechLanguageType targetLang, const char* srcText, const char* targetText, int srcFileDuration, const char* recordFilePath) = 0;

            /**
             * Callback function for real-time speech translate.
             *
             * @param code, this operation's result @enum CompleteCode.
             * @param roomName, name of the room .
             * @param enable, refer to EnableTranslate.
             *
             * @see: CompleteCode
             **/
            virtual void OnEnableTranslate(CompleteCode code, const char *roomName, RealTimeTranslateType transType) = 0;
            
            /**
             * After call EnableTranslate function to enable realtime voice STT, we can get realtime translated text by this callback
             *
             * @param sessionID, ID of the Session for one sentence.
             * @param seq, The sequence of each segment in a sentence
             * @param roomID, ID of the room which a player joined in.
             * @param memberID, the player's ID in this room.
             * @param text, the result of realtime voice stt, utf-8.
             */ 
            virtual void OnRealTimeTranslateText(const char *roomName, unsigned int memberID, const char* sessionID, unsigned int seq, const char* text) = 0;
            
            /**
             * @brief Callback function for tts
             *
             * @param nCode, this operation's result @enum CompleteCode.
             * @param text, source text, from request.
             * @param lang, source text language.
             * @param fileID, ID of the target speech file.
             */
            virtual void OnTextToSpeech(CompleteCode nCode, const char* text, SpeechLanguageType lang, const char* fileID) = 0;

            /** @brief Callback function for TextToSpeechFile
             *
             * @param nCode, this operation's result @enum CompleteCode.
             * @param text, source text, from request.
             * @param lang, source text language.
             * @param filePath, tts file.
             */
            virtual void OnTextToSpeechFile(CompleteCode nCode, const char* text, SpeechLanguageType lang, const char* filePath) = 0;
            
            /**
             * Callback method of EnableMagicVoice.
             * @see EnableMagicVoice
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param magicType: MagicVoice type the player want to translate to
             * @param enable: true for enable MagicVoice function, and false for disable MagicVoice function
             * @see CompleteCode
             */
            virtual void OnEnableMagicVoice(CompleteCode code, const char* magicType, bool enable) = 0;

            /**
             * Callback method of EnableRecvMagicVoice.
             * @see EnableRecvMagicVoice
             *
             * @param code: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param enable: true for enable RecvMagicVoice function, and false for disable RecvMagicVoice function
             * @see CompleteCode
             */
            virtual void OnEnableRecvMagicVoice(CompleteCode code, bool enable) = 0;
            
            /**
             * Callback function for stream tts
             *
             * @param nCode, GV_ON_OK when TTS succeed, else GV_ON_FAIL.
             * @param text, source text, from request.
             * @param error code, defail of fail.
             */ 
            virtual void OnTextToStreamSpeech(CompleteCode nCode, const char* text, int err) = 0;
            
            /** @brief Callback function for ttt
             *
             * @param nCode, this operation's result @enum CompleteCode.
             * @param srcLang, speech language associated with fileID.
             * @param srcText, text that the source speech file translate to.
             * @param targetLang, target language that we want to translate to.
             * @param targetText, text that the source text translate to.
             */ 
            virtual void OnTextTranslate(CompleteCode nCode, SpeechLanguageType srcLang, const char* srcText, SpeechLanguageType targetLang, const char* targetText) = 0;

			/** @brief Callback function for report speech translate
			 *
			 * @param nCode, this operation's result @enum CompleteCode.
			 * @param transText, translation text that translated from report speech.
			 * @param openID, ID of the reported player's openid.
             */ 
			virtual void OnSTTReport(CompleteCode nCode, const char* transText, const char* openID,const char *fileID) = 0;
            
            /**
             * Callback method of magic voice message function.
             *
             * @param nCode: A CompleteCode code. You should check this first the get the result of successful or not.
             * @param filePath: The filePath which the magic voice is stored, and the path is the same as the one you given on StartRecording method.
             * @see CompleteCode
             */
            virtual void OnMagicVoiceMsg(CompleteCode nCode, const char *filePath) = 0;
            
            /**
             * Callback method of security information to game client for forbiding/punishing user voice.
             *
             * @param nRet: security return code; 0: not forbide user talk, number bigger than zero: forbide/punish user voice
             * @param roomname: the information is from which room
             * @param sectransinfo: the information from security department.
             */
            virtual void OnRTSecInfo(int nRet, const char* roomname, const char* sectransinfo) = 0;
            
            /**
             * Callback function when the microphone's volumn has changed.
             * @param level: the microphone's current volumn
             */
            virtual void OnUpdateMicLevel(int level) = 0;

            /**
             * Callback function for recognition info to gameclient forbide / punish user voice ablitiy
             *
             * @param roomname, roomname
             * @param info, the info from security department.
             */ 
            virtual void OnAIRecognition(const char* roomName, const char* info) = 0;
			
            /**
             * After the karaoke recording is completed, notify the client through this callback function
             */
            virtual void OnRecordKaraokeDone(CompleteCode nCode) = 0;

            /**
             * When play BGM file is end,callback this function
             */
            virtual void OnPlayBGMEnd() = 0;

            /**
             * callback method of detect person is speaking for mic
             * if person is speaking, state is 1 else is 0
            */
            virtual void OnMicState(int state) = 0;
        };

    } // endof namespace GVoice
} // endof namespace GCloud
#endif /* _GCloud_GVoice_IGCloudVoiceNotify_h */
