/*******************************************************************************************\
 **
 ** GVoice(Game Voice) is a voice service that covers diverse game scenes.
 ** GVoice supports multiple voice modes, such as RealTime mode, Messages Mode,
 ** Translation mode and RSTT mode.
 **
 ** This file includes the extension APIs in GVoice SDK, which supplies the additional functions
 ** in GVoice, such as playing background music, setting the voice effect mode and so on.
 **
 \*******************************************************************************************/


#ifndef _GCloud_GVoice_IGCloudVoiceExtension_h
#define _GCloud_GVoice_IGCloudVoiceExtension_h

#include "GCloudVoiceErrno.h"

typedef void (*GVoiceLogFunc) (const char *str);

namespace GCloud
{
    namespace GVoice
    {
#define OPENID_LEN_MAX 128
        
#pragma pack(push,1)
        struct RoomMembers
        {
            int memberid ;
            char openid[OPENID_LEN_MAX];
        };
    
        typedef struct GVoice3DVector
        {
            float x;
            float y;
            float z;
        }GVoiceVector;

        enum EVoiceChatAttenuationModel
        {
            /** No attenuation is applied. The audio will drop to 0 at MaxDistance */
            None,
            /** The attenuation increases in inverse proportion to the distance. The Rolloff is the inverse of the slope of the attenuation curve. */
            InverseByDistance,
            /** The attenuation increases in inverse proportion to the distance raised to the power of the Rolloff. */
            ExponentialByDistance
        };

        typedef struct GVoice3DDistProperties
        {
            /** The model used to determine how loud audio is at different distances */
            EVoiceChatAttenuationModel AttenuationModel;
            /** The distance at which the sound will start to attenuate 
            * setmin distance d_r，0.2 <= d_r <= 100
            * if fRefDist < 0.2，d_r = 0.2
            * if fRefDist > 100，d_r = 100
            */
            float MinDistance;
            /** The distance at which sound will no longer be audible
            * Setmaxdistance d_m，1 <= d_m <= 500
            * fMaxDist < 1，d_m = 1
            * fMaxDist > 500，d_m = 500
            */
            float MaxDistance;
            /** How fast the sound attenuates with distance
            * fRollFactor r_f，0.1 <= r_f <= 100
            * if fRollFactor < 0.1, r_f = 0.1
            * if fRollFactor > 100, r_f = 100
            */
            float Rolloff;
        }GVoice3DDistProperties;
#pragma pack(pop)
        
        class IGCloudVoiceEngine;
        
        
        /**
         * Extension API for voice engine
         */
        class IGCloudVoiceEngineExtension
        {
        public:
            /**
             * Member's role for National Room.
             */
            enum MemberRole
            {
                kMemberRoleAnchor   = 1,   // member who can open microphone and say
                kMemberRoleAudience = 2,   // member who can only hear anchor's voice
            };
            
            /**
             * Mode of voice effects.
             */
            enum SoundEffects
            {
                kSoundEffectsRevbChurch     = 0,
                kSoundEffectsRevbTheater    = 1,
                kSoundEffectsHell           = 2,
                kSoundEffectsRobot1         = 3,
                kSoundEffectsMaleToFemale   = 4,
                kSoundEffectsFemaleToMale   = 5,
                kSoundEffectsDrunk          = 6,
                kSoundEffectsPapiJiang      = 7,
                kSoundEffectsSquirrel       = 8,
                kSoundEffectsNoEffect       = 9,
            };
            
            /*************************************************************************
            *                       Scene room related APIs                          *
            **************************************************************************/
        public:
            /**
            * Join in a team room.
            * Team room function allows no more than 20 members join in the same room to communicate freely.
            *
            * JoinTeamRoom method should be called after you have set the engine mode to RealTime.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->JoinTeamRoom
            * -->.....-->QuitRoom
            *
            * The result of joining room successful or not can be obtained by the callback method OnJoinRoom.
            * @see OnJoinRoom
            *
            * @param scenesName: The scene of entering the room, Used to classify rooms,
            *    one scene can only enter one room, will quit the previous room in the same scene automatically,
            *    one room can only be associated with one scene, will fail to join room with anothor scenes,
            *    limit 127 bytes.
            * @param roomName: The name of The room to join, it should be a string composed by 0-9A-Za-Z._- and less than 127 bytes.
            * @param msTimeout: The length of the timeout for joining, it is a micro second, value range[5000, 60000].
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo JoinTeamRoom_Scenes(const char *scenesName, const char *roomName, int msTimeout = 10000) = 0;

            /**
            * Join in a LBS room.
            * RangeRoom function allows user to join a LBS room.
            * After joined a RangeRoom, the member can hear the members' voice within a specific range.
            *
            * JoinRangeRoom method should be called after you have set the engine mode to RealTime.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->JoinRangeRoom
            * -->.....-->QuitRoom
            *
            * The result of joining room successful or not can be obtained by the callback method OnJoinRoom.
            * @see OnJoinRoom
            *
            * @param scenesName: The scene of entering the room, Used to classify rooms,
            *    one scene can only enter one room, will quit the previous room in the same scene automatically,
            *    one room can only be associated with one scene, will fail to join room with anothor scenes,
            *    limit 127 bytes.
            * @param roomName: The name of The room to join, it should be composed by 0-9A-Za-Z._- and less than 127 bytes.
            * @param msTimeout: The length of the timeout for joining, it is a micro second, value range[5000, 60000].
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo JoinRangeRoom_Scenes(const char *scenesName, const char *roomName, int msTimeout = 10000) = 0;

            /**
            * Join in a national room.
            * National room function allows more 20 members to join in the same room, and they can choose two different roles to be.
            * The Anchor role can open microphone to speak and open speaker to listen.
            * The Audience role can only open the speaker to listen.
            *
            * JoinNationalRoom method should be called after you have set the engine mode to RealTime.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->JoinNationalRoom
            * -->.....-->QuitRoom
            *
            * The result of joining room successful or not can be obtained by the callback method OnJoinRoom.
            * @see OnJoinRoom
            *
            * @param scenesName: The scene of entering the room, Used to classify rooms,
            *    one scene can only enter one room, will quit the previous room in the same scene automatically,
            *    one room can only be associated with one scene, will fail to join room with anothor scenes,
            *    limit 127 bytes.
            * @param roomName: The name of The room to join, it should be composed by 0-9A-Za-Z._- and less than 127 bytes.
            * @param role: A GCloudVoiceMemberRole value illustrates wheather the player can send voice data or not.
            * @param msTimeout: The length of the timeout for joining, it is a micro second, value range[5000, 60000].
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo JoinNationalRoom_Scenes(const char *scenesName, const char *roomName, MemberRole role, int msTimeout = 10000) = 0;

            /**
            * Quit the voice room.
            *
            * QuitRoom method should be called after the member has joined a voice room successfully.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->JoinXxxRoom
            * -->.....-->QuitRoom
            *
            * The result of quiting room successful or not can be obtained by the callback method OnQuitRoom
            * @see OnQuitRoom
            *
            * @param scenesName: The scene of entering the room
            * @param msTimeout: The length of the timeout for quiting, it is a micro second, value range[5000, 60000].
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo QuitRoom_Scenes(const char *scenesName, int msTimeout = 10000) = 0;
            /******************** End of scene room related APIs ********************/            
            
            /*************************************************************************
            *                        Multiroom related APIs                          *
            *                                                                        *
            * Multiroom allows a member to join                                      *
            * 1~16 room(s) at the same time.                                         *
            *                                                                        *
            * The workflow of the Multiroom function:                                *
            * GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->               *
            * EnableMultiRoom-->JoinTeamRoom/JoinRangeRoom-->EnableRoomMicrophone/   *
            * EnableRoomSpeaker-->...-->QuitRoom                                     *
            **************************************************************************/  
        public:
            /**
            * Enable a member to join in multi rooms. Notice that this may cause higher bitrate.
            *
            * EnableMultiRoom method should be called after you have set the mode to RealTime
            * and before you call the JoinXxxRoom method.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->EnableMultiRoom
            * -->JoinXxxRoom-->.....-->QuitRoom
            *
            * @param enable: Enable joining in multi rooms if it is ture, disable joining in multi rooms if it is false.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableMultiRoom(bool enable) = 0;
            
            /**
            * Open or close the microphone in a specific room in MultiRoom mode.
            *
            * EnableRoomMicrophone method should be called after the member has joined a voice room in MultiRoom mode successfully.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->EnableMultiRoom(true)
            * -->JoinXxxRoom-->EnableRoomMicrophone-->.....-->QuitRoom
            *
            * @param roomName: The name of The room to enable microphone, it should be an exist room name.
            * @param enable: Open the microphone in The room if it is true, and close the microphone if it is false.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableRoomMicrophone(const char *roomName, bool enable) = 0;
            
            /**
            * Open or Close the speaker in a specific room in MultiRoom mode.
            *
            * EnableRoomSpeaker method should be called after the member has joined a voice room in MultiRoom mode successfully.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->EnableMultiRoom(true)
            * -->JoinXxxRoom-->EnableRoomMicrophone-->.....-->QuitRoom
            *
            * @param roomName: The name of The room to enable speaker, it should be an exist room name.
            * @param enable: Open the speaker in The room if it is true, and close the speaker if it is false.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableRoomSpeaker(const char *roomName, bool enable) = 0;

            /**
            * Set room member's volume, used for multi-room
            *
            * @param playerid: the room member's playerid who you want to set his volume
            * @param pVol: the member's volume
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetPlayerVolume(const char* playerid, unsigned int nVol) = 0;

            /**
            * Get room member's volume, used for multi room
            *
            * @param playerid: the room member's playerid who you want to get his volume
            * @param pVol: the member's volume, default is 100
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo GetPlayerVolume(const char* playerid, unsigned int* pVol) = 0;
            /************************ End of multiroom related APIs *****************/       
            
            /*************************************************************************
             *                  BGM related APIs                                     *
             *                                                                       *
             * GVoice supports mp3 format background music.                          *
             * The workflow of the BGM function:                                     *
             * GetVoiceEngine-->SetAppInfo-->Init-->EnableNativeBGMPlay-->SetBGMPath *
             * -->StartBGMPlay-->PauseBGMPlay-->ResumeBGMPlay-->StopBGMPlay          *
             *************************************************************************/
        public:
            /**
            * Set The path to a BGM file.
            * SetBGMPath method should be called after you have initialized the voice engine.
            *
            * @param pPath: The path to the BGM file.
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetBGMPath(const char * path) = 0;
            
            /**
            * Enable or disable the native play mode.
            * EnableNativeBGMPlay method should be called after you have initialized the voice engine.
            *
            * @param bEnable: Enable the native play mode if it is true, and disable the native play mode if it is false.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableNativeBGMPlay(bool enable) = 0;
            
            /**
            * Start playing the BGM.
            * StartBGMPlay method should be called after you have set The path of the BGM file by SetBGMPath method.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo StartBGMPlay() = 0;
            
            /**
            * Set the play volume of the BGM.
            * SetBGMVol method should be called after you have initialized the voice engine.
            *
            * @param nvol: The play volume of the BGM, which should be an integer between 0~800.
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * 
            * @see ErrorNo
            */
            virtual ErrorNo SetBGMVol(int volume) = 0;
            
            /**
            * Pause the BGM.
            * When you want to pause the playing of BGM or when the application paused, you can call PauseBGMPlay
            * method to pause the BGM.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo PauseBGMPlay() = 0;
            
            /**
            * Resume the BGM.
            * When you want to resume the playing of BGM after paused it or when the application resumed, you can call
            * ResumeBGMPlay method to resume the BGM.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo ResumeBGMPlay() = 0;
            
            /**
            * Get the state of the BGM.
            * If you want to get the playing state of the BGM, you can call GetBGMPlayState method.
            * GetBGMPlayState method should be called after you have initialized the voice engine.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */            
            virtual int GetBGMPlayState() = 0;
            
            /**
            * Stop the BGM.
            * StopBGMPlay method should be called after you have initialized the voice engine.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo StopBGMPlay() = 0;
            
            /**
            * Initial version: GCloud 2.2.6
            */
            virtual int GetBGMFileTime() = 0;
            
            /**
            * Initial version: GCloud 2.2.6
            */
            virtual int GetBGMLevel()=0;
            
            /**
            * Initial version: GCloud 2.2.6
            */
            virtual int GetBGMPlayTime() = 0;

            /**
            * Initial version: GCloud 2.2.6
            */
            virtual int SetBGMPlayTime(int time) = 0;
            
            /****************** End of BGM related APIs ******************/
            
            /**************************************************************
            *                Microphone or speaker related APIs           *
            ***************************************************************/
        public:
            /**
            * Open or close the speaker.
            * EnableSpeakerOn method should be called after you have initialized the voice engine.
            *
            * @param bEnable: Open the speaker if it is true and close the speaker if it is false.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableSpeakerOn(bool enable) = 0;
            
            /**
            * Set the volume of microphone.
            * SetMicVolume method should be called after you have initialized the voice engine.
            *
            * @param vol: The volume to set, for windows platform, the vol should in -1000～1000,
            * and in other platforms, the vol should in -150～150.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetMicVolume(int volume) = 0;
            
            /**
            * Set the sepaker's volume.
            * SetSpeakerVolume method should be called after you have initialized the voice engine.
            *
            * @param vol: The volume to set, for windows platform, the vol should in 0～100,
            * and in other platforms, the vol should in 0～150, the real volume is equals to (the vol / 100 * the original voice volume).
            * If you set the vol to 120, then the real vol is (1.2*the original voice volume).
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetSpeakerVolume(int volume) = 0;
            
            /**
            * Get the microphone's volume.
            * GetMicLevel method should be called after you have initialized the voice engine.
            *
            * @return the microphone's volume, if return value>0, means you have said something captured by microphone.
            */
            virtual int GetMicLevel(bool fadeOut=true) = 0;
            
            /**
            * Get the speaker's volume.
            * GetSpeakerLevel method should be called after you have initialized the voice engine.
            *
            * @return the speaker's volume, the value is equal to the param when you call SetSpeakerVolume method.
            */
            virtual int GetSpeakerLevel() = 0;
            
            /**
            * Get the microphone's state, open microphone success, failed or be occupied.
            *
            * @return: The microphone's state. -1: microphone is closed; 0: open microphone failed;
            *          1: open microphone success; 2: microphone has been occupied.
            */
            virtual int GetMicState() = 0;
            
            /**
            * Get the speaker's state, open speaker success, failed or be occupied.
            *
            * @return: The speaker's state. -1: speaker is closed; 0: open speaker failed;
            *          1: open speaker success; 2: speaker has been occupied.
            */
            virtual int GetSpeakerState() = 0;
            
            /**
            * Test wheather the microphone is available or not.
            * Before you want to open microphone, call TestMic method to check whether the microphone is available or not.
            * TestMic method should be called after you have initialized the voice engine.
            *
            * @return If microphone device is available, returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo TestMic() = 0;
            
            /**
            * Detect whether the member is speaking or just keep microphone opened.
            * IsSpeaking method should be called after you have initialized the voice engine.
            *
            * @return If the member is speaking, returns true, otherwise returns false.
            */
            virtual bool IsSpeaking()const = 0;
                      
            /**
            * Set the state of the headset, if there is a headset connected or not.
            *
            * @param bState: there is a headset connected if it is true, and there is a headset disconnected if it is false.
            */
            virtual void SetHeadSetState(bool state) = 0;
                       
            /**
            * Set the state of the bluetooth, if there is a bluetooth connected or not.
            *
            * @param bState: there is a bluetooth connected if it is true, or there is a bluetooth disconnected if it is false.
            */
            virtual void SetBluetoothState(bool state) = 0;
            
            /**
            * Enable or disable the bluetooth SCO mode. When you want to capture the voice via bluetooth, you can call EnableBluetoothSCO(true).
            * EnableBluetoothSCO method should be called after you have initialized the voice engine.
            *
            * @param enable: Enable the bluetooth SCO mode if it is true, and disable the bluetooth SCO mode if it is false.
            */
            virtual void EnableBluetoothSCO(bool enable) = 0;
            
            // TODO
            virtual void DeviceEventNotify(int eventId, const char *info) = 0;
            
            /**
            * Identify that whether there is any device connected or not.
            *
            * @return: 0: no audio device connected; 1: a wiredheadset device connected; 2: a bluetooth device connected.
            * @see GCloudVoiceDeviceState
            */
            virtual DeviceState GetAudioDeviceConnectionState() = 0;
            
            /**
            * Check mute switch state; iPhone is valiable; iOS simulator and android will return non-mute.
            *
            * @return: If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            * @see void IGCloudVoiceNotify::OnMuteSwitchResult(int nState);
            **/
            virtual ErrorNo CheckDeviceMuteState() = 0;
            
            /**
            * Get the mute state of the device.
            *
            * @return: The device is muted or not. non-zero:mute state; 0: not in mute state; -1:error.
            */
            virtual int GetMuteResult() = 0;
            /******** End of microphone or speaker related APIs *********/
                    
            /*************************************************************
            *                  Voice algorithm related APIs              *
            **************************************************************/
        public:
            /**
            * This method supports setting sound effect mode.
            * SetVoiceEffects method should be called after you have initialized the voice engine.
            *
            * @param mode: The sound effect to set, @see SoundEffects
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetVoiceEffects(SoundEffects mode) = 0;
            
            /**
            * This method supports enabling sound reverb function.
            * EnableReverb method should be called after you have initialized the voice engine.
            *
            * @param bEnable: Enable the sound reverb if it is true, and disable the sound reverb if it is false.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual int EnableReverb(bool enable) = 0;
            
            /**
            * This method supports setting sound reverb mode.
            * SetReverbMode method should be called after you have initialized the voice engine.
            *
            * @param mode: The reverb mode which you want to set, the value should in 0~5, and default is 0.
            *        0: strong vocal; 1: vocal; 2: small room; 3: large room; 4: church; 5: theater
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual int SetReverbMode(int mode) = 0;
            
            /**
            * Identify the type of the voice.
            * GetVoiceIdentify method should be called after you have initialized the voice engine.
            *
            * @return 0: boy's sound; 1: girl's sound; 2: non human sound; -1: error.
            */
            virtual int GetVoiceIdentify() = 0;
            /*********** End of voice algorithm related APIs ************/
                                 
            /*************************************************************
            *                  Voice report related APIs
            **************************************************************/
        public:
            /**
            * Set the buffered voice size in GVoice when use voice report function, the default value is 20s.
            *
            * @param nTimeSec: How many seconds you want GVoice to buffer
            */
            virtual void SetReportBufferTime(unsigned int nTimeSec) = 0;
            
            /**
            * Set the players information that maybe reported in your game.
            *
            * @param cszOpenID: All players openid you may report
            * @param nMemberID: All players memberid you may report
            * @param nCount: The count of members you may report, it should be equals to the length of cszOpenID and nMemberID
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetReportedPlayerInfo(const char* cszOpenID[], unsigned int nMemberID[], unsigned int nCount) = 0;
            
            /**
            * Report uncivilized players in your game.
            *
            * @param cszOpenID: All players openid you may report, null will report all the players you set @see SetReportedPlayerInfo
            * @param nCount: Element count in array, 0 will report all the players you set @see SetReportedPlayerInfo
            * @param cszInfo: Information will be send to server
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo ReportPlayer(const char* cszOpenID[], unsigned int nCount, const char* cszInfo) = 0;

            /**
            * Enable civilization voice detect.
            *
            * @param enable: Enable detect if it is true, and disable if it is false.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual int EnableCivilVoice(bool bEnable) = 0;

            /**
            * Set civil voice source file path
            *
            * param pPath: bin absolutive path
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetCivilBinPath(const char* pPath) = 0;

            /**
            * Set transparent information for report judge.
            * Initial version: GCloud 2.2.0
            *
            * @param secInfo: the information you want to give to the server.
            */
            virtual void SetTransSecInfo(const char* secInfo) = 0;

            /**
            * Report all players.
            * Initial version: GCloud 2.2.0
            *
            * @param bEnable: true: report all players, false: don't report all players
            */
            virtual int EnableReportALL(bool bEnable) = 0;

            /**
            * Report all players for abord.
            * Initial version: GCloud 2.2.0
            *
            * @param bEnable: true: report all players, false: don't report all players
            */
            virtual int EnableReportALLAbroad(bool bEnable) = 0;

            /**
            * Enable civilize voice detect for file.
            * Initial version: GCloud 2.2.0
            *
            * @param enable: enable detect if it is true, and disable if it is false.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual int EnableCivilFile(bool bEnable) = 0;
            
            /**
            * Set players information for abord.
            *
            * @param szopenID: all players openid you may report.
            * @param nMemberID: all players memberid you may report.
            * @param pLang: Every players voice country.
            * @param nCount: Element count in array.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual int SetPlayerInfoAbroad(const char* szopenID[], int nMemberID[], SpeechLanguageType pLang[], unsigned int nCount) = 0;
            
            /**
            * Initial version: GCloud 2.2.6
            */
            virtual int AddInfoForReport(const char *buf) = 0;

			/**
			* Enable report player itself for abroad.
			* Initial version: GCloud 2.2.8
			*
			* @param bEnable: true:enable. false:disable.
			* @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
			*/
			virtual ErrorNo EnableReportForAbroad(bool bEnable) = 0;

			/**
			* Set report player itself start.
			* Initial version: GCloud 2.2.8
			*
			* @param filepath: The voice file will be save on the filepath and it won't be save while filepath is NULL.
			* @param bTranslate: true: The voice will be translate to text and callback the result, false: the whole function won't work.
			* @param bChangeVoice: true: Change voice before save it on the filepath, false: Save on the filepath directly.
			* @param time: The interval to translate, Default translate once every 60s.
			*
			* @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
			*/
			virtual ErrorNo ReportFileForAbroad(const char *filepath, bool bTranslate, bool bChangeVoice, int time = 60) = 0;
            /************* End of voice report related APIs *************/
            
            /*************************************************************
            *                  LGame rec related APIs                    *
            **************************************************************/
        public:
            /**
            * For LGame Rec Interface
            */
            virtual ErrorNo StartSaveVoice() = 0;
            
            /**
            * For LGame Rec Interface
            */
            virtual ErrorNo StopSaveVoice() = 0;
            
            /**
            * For LGame Rec Interface
            */
            virtual ErrorNo SetRecSaveTs(int ts) = 0;
            
            /**
            * For LGame Rec Interface
            */
            virtual ErrorNo SetPlayFileIndex(const char* fileid, int fileindex) = 0;
            
            /**
            * For LGame Rec Interface
            */
            virtual ErrorNo StartPlaySaveVoiceTs(int ts) = 0;
            
            /**
            * For LGame Rec Interface
            */
            virtual ErrorNo StopPlaySaveVoice() = 0;
            
            /**
            * For LGame Rec Interface
            */
            virtual ErrorNo DelAllSaveVoiceFile(const char* fileid, int fileindex) = 0;
            /*************** End of LGame rec related APIs **************/
   
            /*************************************************************
            *                 Speech translate related APIs              *
            **************************************************************/
        public:
            /**
            *********************************************************************************************
		    * !!!This API is not recommended, SpeechFileTranslate/SpeechFileToText is recommended       *   
		    *********************************************************************************************
            * Translate speech from one language to another.
            *
            * @param fileID: ID of speech file which to be translated.
            * @param srcLang: speech language associated with fileID.
            * @param targetLang: target language that we want to translate to.
            * @param transType: if set SPEECH_TRANSLATE_STST, targetLang will be ignored.
            * @param nTimeoutMS: length of speech translate perform timeout, the unit is milliseconds, recommended >= 10000
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SpeechTranslate(const char *fileID, SpeechLanguageType srcLang, SpeechLanguageType targetLang, SpeechTranslateType transType, int nTimeoutMS = 10000) = 0;
            
            /**  
            * Translate speech file from one language to another, OnSpeechFileTranslate return translated speech file.
            * Initial version: GCloud 2.2.4
            *
            * @param filePath: sts local file path, should like:"your_dir/your_file_name"
            * @param srcLang: speech language associated with fileID.
            * @param targetLang: target language that we want to translate to
            * @param voiceType: 0:normal woman, 1:normal man
            * @param voiceRate: [0.25, 4.0], 1.0 for normal voice speed rate,0.25 for min speed, 4.0 for max speed 
            * @param volume: [-10.0,10.0], 0.0 for normal volume, -10.0 for min volume, 10.0 for max volume 
            * @param nTimeoutMS: length of speech translate perform timeout, the unit is milliseconds, recommended >= 10000
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SpeechFileTranslate(const char* filePath, SpeechLanguageType srcLang, SpeechLanguageType targetLang, int voiceType = 0, float voiceRate = 1.0f, float volume = 0.0f, int nTimeoutMS = 10000) = 0;

            /** 
            * Translate speech file to text, OnSpeechFileToText return translated text.
			* Initial version: GCloud 2.2.4
            * 
            * @param filePath: stt local file path, should like:"your_dir/your_file_name"
            * @param srcLang: speech language associated with fileID.
            * @param targetLang: target language that we want to translate to,If don't need language conversion, targetLang should set same as srcLang.
            * @param nTimeoutMS: length of speech translate perform timeout, the unit is milliseconds, recommended >= 10000
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SpeechFileToText(const char* filePath, SpeechLanguageType srcLang, SpeechLanguageType targetLang, int nTimeoutMS = 10000) = 0;

            /**
            * RSTT settings, for SGame.
            * Initial version: GCloud 2.2.4
            *
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RSTT)->SetRSTTServerInfo->StartRecording
            * -->.....-->StopRecording
            *
            * @param RSTTUrl: url of RSTT server.
            * @param httpDnsIPs: IPs obtained by HttpDns parsing RSTTUrl,if there are multiple IPs, separate with '|'.
            * @param wxAppID: appid of RSTT service.
            *
            * @return If success returns ErrorNo, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetRSTTServerInfo(const char* RSTTUrl, const char* httpDnsIPs, const char* wxAppID) = 0;

            /**
            *********************************************************************************************************
            * !!!This API is not recommended, RSTSSpeechToSpeech/RSTSSpeechToText is recommended
            *********************************************************************************************************
            * Start real-time speach to speach.
            * Notice: this method should be called in RSTS mode.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RSTS)-->ApplyMessageKey
            * -->RSTSStartRecording
            *
            * @param srcLang: the speech language of the recorder.
            * @param pTargetLangs: target languages that we want to translate to.
            * @param nTargetLangCnt: number of target languages that we want to translate to.
            * @param transType: if set SPEECH_TRANSLATE_STST, pTargetLangs and nTargetLangCnt will be ignored          
            * @param nTimeoutMS: length of RSTS perform timeout, the unit is milliseconds, recommended >= 3000
			* @param recordFilePath: The path of the file of recorded voice data, the filePath should like:"your_dir/your_file_name" or "" witch means no need to save.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo RSTSStartRecording(SpeechLanguageType srcLang, SpeechLanguageType pTargetLangs[], int nTargetLangCnt, SpeechTranslateType transType, int nTimeoutMS = 5000, const char* recordFilePath = "") = 0;
            
            /**
            * Stop real-time speech to speech.
            * Notice: this method should be called in RSTS mode.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RSTS)-->ApplyMessageKey
            * -->RSTSStartRecording-->RSTSStopRecording
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo RSTSStopRecording() = 0;

            /**
            * Recording voice in real time and converting it to other languages' Speech, finally save the translated Speech to file.
            * Initial version: GCloud 2.2.4
            *
            * Realization:Microphone->voice frame->translate->other language's voice frame->file
            *
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->RSTSSpeechToSpeech->RSTSStopRecording->OnRSTSSpeechToSpeech
            *
            * @param srcLang: the speech language of the recorder.
            * @param pTargetLangs: target languages that we want to translate to.
            * @param nTargetLangCnt: number of target languages that we want to translate to.
            * @param dirPath: the directory is used to save the translated voice files
            * @param voiceType: could be 0:normal woman, 1:normal man
            * @param voiceRate: [0.25, 4.0], 1.0 for normal voice speed rate,0.25 for min speed, 4.0 for max speed
            * @param volume: [-10.0,10.0], 0.0 for normal volume, -10.0 for min volume, 10.0 for max volume
            * @param nTimeoutMS: perform timeout, the unit is milliseconds, recommended >= 3000
			* @param recordFilePath: The path of the file of recorded voice data, the filePath should like:"your_dir/your_file_name" or "" witch means no need to save.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo RSTSSpeechToSpeech(SpeechLanguageType srcLang, SpeechLanguageType pTargetLangs[], int nTargetLangCnt, const char* dirPath, int voiceType = 0, float voiceRate = 1.0f, float volume = 0.0f, int nTimeoutMS = 5000, const char* recordFilePath = "") = 0;
            
            /**
            * Recording voice in real time and converting it to other languages's text, finally return the translated text.
            * Initial version: GCloud 2.2.4
            *
            * Realization:Microphone->voice frame->translate->other language's voice text
            *
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->RSTSSpeechToText->RSTSStopRecording->OnRSTSSpeechToText
            *
            * @param srcLang: the speech language of the recorder.
            * @param pTargetLangs: target languages that we want to translate to.If don't need language conversion, pTargetLangs should set NULL and nTargetLangCnt set 0.
            * @param nTargetLangCnt: number of target languages that we want to translate to.
            * @param nTimeoutMS: length of RSTS perform timeout, the unit is milliseconds, recommended >= 3000
			* @param recordFilePath: The path of the file of recorded voice data, the filePath should like:"your_dir/your_file_name" or "" witch means no need to save.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo RSTSSpeechToText(SpeechLanguageType srcLang, SpeechLanguageType pTargetLangs[], int nTargetLangCnt, int nTimeoutMS = 5000, const char* recordFilePath = "") = 0;
            
            /**
            * Enable or Disable real-time voice translate. for example, an American, a Chinese, and a German enter the same room and set their own language,
            * the background service will translate Chinese speech into English speech and German speech, and send to corresponding person , and so do others .
            *
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->JoinTeamRoom
            * -->EnableTranslate-->.....-->QuitRoom
            *
            * The result of EnableTranslate successful or not can be obtained by the callback method OnEnableTranslate.
            * @see OnEnableTranslate
            *
            * @param roomName: The name of The room to join, it should be a string composed by 0-9A-Za-Z._- and less than 127 bytes.
            * @param bEnable: true for enable translate, false for disable translate.
            * @param myLang: speaker language, refer to SpeechLanguageType.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableTranslate(const char *roomName, bool bEnable, SpeechLanguageType myLang, RealTimeTranslateType transType) = 0;
                         
            /**
            * Enable key words detect
            * 
            * param bEnable: true enable keywords detect, false: disable
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableKeyWordsDetect(bool bEnable) = 0;
            
            /**
            * Text to speech.
            *
            * @param text: utf-8, MAX 255 length
            * @param lang: text's language
            * @param voice type: voice type
            * @param nTimeoutMS: length of stt perform timeout, the unit is milliseconds, recommended >= 10000
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo TextToSpeech(const char *text, SpeechLanguageType lang, int voiceType, int nTimeoutMS = 10000) = 0;
            
            /**
            * Text to speech file, OnTextToSpeechFile return local file path.
            * Initial version: GCloud 2.2.4
            * 
            * @param text: utf-8, MAX 255 length
            * @param lang: text's language.
            * @param voiceType: 0:normal woman, 1:normal man
            * @param filePath: tts local file path, should like:"your_dir/your_file_name"
            * @param voiceRate: [0.25, 4.0], 1.0 for normal voice speed rate,0.25 for min speed, 4.0 for max speed 
            * @param volume: [-10.0,10.0], 0.0 for normal volume, -10.0 for min volume, 10.0 for max volume 
            * @param nTimeoutMS: tts perform timeout, the unit is milliseconds, recommended >= 10000
            * 
            * @return If success returns Succ, otherwise returns other errno.
            * @see ErrorNo
            */ 
            virtual ErrorNo TextToSpeechFile(const char* text, SpeechLanguageType lang, const char* filePath, int voiceType = 0, float voiceRate = 1.0f, float volume = 0.0f, int nTimeoutMS = 10000) = 0;

            /**
            * Start Text to stream speech, auto play, only support chinese speech, voice type support customization.
            *
            * @param text: utf-8, MAX 255 length
            * @param voiceType: as below:
            *                db1, General Sweet Girl Voice
            *                female0, General female voice
            *                femalen, emotional female voice
            *                kefu, Customer Service Voice
            *                male0, General male voice
            *                xdgz, emotional male voice
            *                txnews, news female voice
            *                wepay, payment dedicated female voice
            *                xiaowei, assistant female voice
            * @param nTimeoutMS: length of tts perform timeout, the unit is milliseconds, recommended >= 10000
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo TextToStreamSpeechStart(const char* text, const char* voiceType, int nTimeoutMS = 10000, const char* filePath = "") = 0;

            /**
            * Stop Text to stream speech.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo TextToStreamSpeechStop() = 0;

            /**
            * Text translate.
            *
            * @param text: utf-8, MAX 2000 length
            * @param srclang: text's language.
            * @param targetLang: target language that we want to translate to.
            * @param nTimeoutMS: length of text-translating perform timeout, the unit is milliseconds, recommended >= 10000
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo TextTranslate(const char* text, SpeechLanguageType srcLang, SpeechLanguageType targetLang, int nTimeoutMS = 10000) = 0;

            /*********** End of speech translate related APIs ***********/

            /*************************************************************
            *                  Magic voice related APIs                  *
            **************************************************************/
        public:
            /**
            * Enable or disable MagicVoice function in realtime voice room.
            * If a player enabled the MagicVoice function, then the player's voice will be translated to
            * another voice, which is specified by the magicType parameter, and send to other players.
            *
            * EnableMagicVoice method should be called at anytime after Init GVoice success.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->EnableMagicVoice-->......-->SetMode(RealTime)-->JoinTeamRoom(RangeRoom)-->.....-->QuitRoom
            *
            * EnableMagicVoice is an Asynchronous interface, the result of EnableMagicVoice should be obtained by the callback method OnEnableMagicVoice.
            * @see OnEnableMagicVoice
            *
            * @param magicType: MagicVoice type the player want to translate to
            * @param enable: true for enable MagicVoice function, and false for disable MagicVoice function
            * 
            * @return If success returns Succ, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableMagicVoice(const char* magicType, bool enable) = 0;
            
            /**
            * Enable or disable receive MagicVoice from other players.
            * If a player A enabled the RecvMagicVoice function, and anyone B in this room enabled MagicVoice function, then the play A will receive magic voice of B.
            * In default, a player A will receive magic voice from B, if B enabled MagicVoice function.
            *
            * EnableRecvMagicVoice method should be called at anytime after Init GVoice success.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->EnableRecvMagicVoice-->......-->SetMode(RealTime)-->JoinTeamRoom(RangeRoom)-->.....-->QuitRoom
            *
            * EnableRecvMagicVoice is an Asynchronous interface, the result of EnableRecvMagicVoice should be obtained by the callback method OnEnableRecvMagicVoice.
            * @see OnEnableRecvMagicVoice
            *
            * @param enable: true for enable RecvMagicVoice function, and false for disable RecvMagicVoice function
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableRecvMagicVoice(bool enable) = 0;

            /**
            * Set a specific magic voice type of the magic voice message function.
            * Initial version: GCloud 2.2.0
            *
            * @param magicType: the specific magic voice you want to recored
            *
            * @return If success returns 0, otherwise returns -1.
            */
            virtual int SetMagicVoiceMsgType(const char* magicType) = 0;

            /**
            * Audition file for specify magic type
            * Initial version: GCloud 2.2.0
            *
            * @param file: which file need play used specify magic type
            * @param magictype: specify magic type for play
            */
            virtual int AuditionFileForMagicType(const char* file, const char* magicType) = 0;

            // TODO
            virtual int IsSaveMagicFile(bool bSave) = 0;           
            /************* End of magic voice related APIs **************/ 
            
            /*************************************************************
            *                        3D Audio APIs                       *
            **************************************************************/
        public:
            /**
            * Enable 3d voice
            * Initial version: GCloud 2.2.0
            *
            * @param enable: enable detect if it is true, and disable  if it is false.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo Enable3DVoice(bool bEnable) = 0;
            
            /**
            * Set Listener(self) 3d position vector
            * Initial version: GCloud 2.2.0
            *
            * @param GVoice3DVector: x/y/z.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo Set3DPosition(GVoice3DVector pos) = 0;
            
            /**
            * Set Listener(self) face 3d position vector,default(0,1,0)
            * Initial version: GCloud 2.2.0
            *
            * @param GVoice3DVector: x/y/z.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo Set3DForward(GVoice3DVector forward) = 0;
            
            /**
            * Set Listener(self) head 3d position vector,default(0,0,1)
            * Initial version: GCloud 2.2.0
            *
            * @param GVoice3DVector: x/y/z.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo Set3DUpward(GVoice3DVector upward) = 0;
            
            /**
            * Set Distance-vol properties
            * Initial version: GCloud 2.2.0
            *
            * @param GVoice3DDistProperties: check the GVoice3DDistProperties define for more param detail.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo Set3DDistProperties(GVoice3DDistProperties g3dProperties) = 0;
            /****************** End of 3D Audio APIs ********************/
            
            /*************************************************************
            *                         Karaoke APIs                               *
            **************************************************************/
        public:
            /**
            * Start recording for karaoke, (accFile and oriFile must  match)
            * Initial version: GCloud 2.2.6
            *
            * @param dstFile: which save the recorded karaoke file.
            * @param accFile: which file is Accompaniment
            * @param oriFile: which file is normal music file
            *
            * @return: If success returns kErrorNoSucc, otherwise returns other errno, see ErrorNo
            */
            virtual ErrorNo StartKaraokeRecording(const char *dstFile,const char *accFile,const char *oriFile) = 0;
            
            /**
            * Stop recording for karaoke
            * Initial version: GCloud 2.2.6
            *
            * @return: If success returns kErrorNoSucc, otherwise returns other errno, see ErrorNo
            */
            virtual ErrorNo StopKaraokeRecording() = 0;
            
            /**
            * Get the total karaoke recording time
            * Initial version: GCloud 2.2.6
            *
            * return ms for total recording time
            */
            virtual int GetRecordKaraokeTotalTime() = 0;
            
            /**
            * Set record people voice volume for karaoke
            * Initial version: GCloud 2.2.6
            *
            * @param vol: the volume for people voice (0~400)
            * @return: If success returns kErrorNoSucc, otherwise returns other errno, see ErrorNo
            */
            virtual ErrorNo SetKaraokeVoiceVol(int vol) = 0;
            
            /**
            * Set record music volume for karaoke
            * Initial version: GCloud 2.2.6
            *
            * @param vol : the volume for music (0~400)
            * @return: If success returns kErrorNoSucc, otherwise returns other errno, see ErrorNo
            */
            virtual ErrorNo SetKaraokeAccVol(int vol) = 0;
            
            /**
            * Set the delay of recording vocals, align with the accompaniment
            * Initial version: GCloud 2.2.6
             
            * @param delay: which vocals delay for ms (-1000ms ~ 1000ms)
            * @return: If success returns kErrorNoSucc, otherwise returns other errno, see ErrorNo
            */
            virtual ErrorNo SetKaraokeVoiceDelay(int delay) = 0;
            
            /**
            * Pause karaoke recording
            * Initial version: GCloud 2.2.6
            *
            * @return: If success returns kErrorNoSucc, otherwise returns other errno, see ErrorNo
            */
            virtual ErrorNo PauseKaraoke() = 0;
            
            /**
            * Resume karaoke recording
            * Initial version: GCloud 2.2.6
            *
            * @return: If success returns kErrorNoSucc, otherwise returns other errno, see ErrorNo
            */
            virtual ErrorNo ResumeKaraoke() = 0;
            
            /**
            * Turn on the audition function after karaoke recording
            * Initial version: GCloud 2.2.6
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo StartPreview() = 0;
            
            /**
            * Turn off the audition function after karaoke recording
            * Initial version: GCloud 2.2.6
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo StopPreview() = 0;
            
            /**
            * Enable play for ear back
            * Initial version: GCloud 2.2.6
            *
            * @param bEnable: true: open ear back; false: close ear back
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableEarBack(bool bEnable) = 0;
            
            /**
            * Enable play for Accompaniment
            * Initial version: GCloud 2.2.6
            *
            * @param bEnable: true: play for Accompaniment, false: play for normal music
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableAccFilePlay(bool bEnable) = 0;
            
            /**
            * Set the playback time of the music file
            * Initial version: GCloud 2.2.6
            *
            * param ms: the time for begine play for music
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SeekTimeMsForAcc(int ms) = 0;
            
            /**
            * Get the total duration of music files
            * Initial version: GCloud 2.2.6
            *
            * return ms for music file
            */
            virtual int GetAccFileTotalTimeByMs() = 0;
            
            /**
            * Get music playback progress
            * Initial version: GCloud 2.2.6
            *
            * @return ms for music playback
            */
            virtual int GetAccPlayTimeByMs() = 0;
            
            /**
            * Whether to save the recorded karaoke file
            * Initial version: GCloud 2.2.6
            * param bComplete: true: save the recorded karaoke file, false:cancel the recorded karaoke file
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo IsRecordComplete(bool bComplete) = 0;
            
            /**
            * Get the playback progress under the audition
            * Initial version: GCloud 2.2.6
            *
            * return: Current playing time for ms
            */
            virtual int GetCurPlayTimeForPreview() = 0;
            
            /**
            * Set the playback time of the audition file
            * Initial version: GCloud 2.2.6
            * param ms: the time for begin play for audition
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SeekTimeMsForPreview(int ms) = 0;
            /************ End of Karaoke APIs ******************/
                                                                  
            /*************************************************************
            *                          Other APIs                        *
            **************************************************************/
        public:
            /**
            * Set the server's address, only needed for games which published in foreign contries, such as Korea, Europe...
            *
            * SetServerInfo method should be called before JoinXxxRoom in RealTime mode
            * or ApplyMessageKey in Messages, Translation and RSTT mode.
            *
            * @param URL: Url of server.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetServerInfo(const char* URL, const char* defaultipsvr = "") = 0;

            /**
            * Set the URLs used in GVoice, you can only set the URLs defined in UrlType enum.
            * Initial version: GCloud 2.2.4
            */
            virtual ErrorNo SetServerUrl(UrlType urlType, const char* url) = 0;

            /**
            * Set the bit rate of the voice code.
            * SetBitRate method should be called after you have initialized the voice engine.
            *
            * @param bitrate: The bit rate you want to set, it should be an integer between 8~256K.
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetBitRate(int bitrate) = 0;

            /**
            * Set if it is datafree.
            *
            * @param enable: Enable datafree if it is true, and disable datafree if it is false.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetDataFree(bool enable) = 0;

            // TODO
            virtual ErrorNo SetLogCallBack(GVoiceLogFunc logFunc) = 0;

            /**
            * Open Voice Engine's logcat.
            * EnableLog method should be called after you have initialized the voice engine.
            *
            * @param enable: Open logcat if it is true, and disable logcate if it is false.
            */
            virtual void EnableLog(bool enable) = 0;

            /**
            * Set the audience list who can hear, that is, members not in this list can not hear the voice from the members in the same room.
            *
            * @param members: The IDs of the members who can hear the voice.
            * @param count: Number of members to set.
            * @param roomName: The room to set the audience list.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetAudience(int* members, int count, const char* roomName = "") = 0;

            /**
            * Get room members openid-memberid info.
            *
            * @param roomName: of which rooms members info you want to get
            * @param RoomMembers: members info saved in here,if with value null, the function return value is room members count num
            * @param len: the members[] array lens, if len<=0, the function return value is the room members count num
            *
            * @return An integer result, the room members count num, otherwist -1 means some error.
            */
            virtual int GetRoomMembers(const char* roomName, RoomMembers members[], int len) = 0;

            /**
            * Don't play the member's voice.
            *
            * ForbidMemberVoice method should be called after the member has joined a voice room successfully.
            * e.g. GetVoiceEngine-->SetAppInfo-->Init-->SetNotify-->Poll-->SetMode(RealTime)-->JoinXxxRoom
            * -->ForbidMemberVoice-->.....-->QuitRoom
            *
            * @param member: The ID of the member who you want to forbid his voice.
            * @param bEnable: Forbid the member's voice if it is true, and listen the member's voice if it is false.
            * @param roomName: The name of The room to forbid member's voice, it should be an exist room name.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo ForbidMemberVoice(int member, bool enable, const char* roomName = "") = 0;

            /**
            * Get the voice message's file size and last time.
            *
            * @param filepath: The path of the voice file to get infomation, the filePath should like:"your_dir/your_file_name".
            * @param bytes: For returning the file's size.
            * @param seconds: For returning the voice's length.
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo GetFileParam(const char* filepath, unsigned int* bytes, float* seconds) = 0;

            /**
            * Room data channel, business can transfer private data.
            * Initial version: GCloud 2.2.0
            *
            * @param roomName: the room which you want to transfer private data.
            * @param content: the content of the room transmission, JSON format, utf-8, limit 1024 bytes
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo RoomGeneralDataChannel(const char* roomName, const char* content) = 0;

            /**
            * Report API call information for problem analysis.
            *
            * @param api, API that you want to trace.
            * @param callInfo: descriptive information of the API call, for example, in which scenario the API is called
            *
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo APITrace(const char* api, const char* callInfo) = 0;

            /**
            * It is not recommended to call this method.
            * If you want to use this, please contact with the GVoice team.
            */
            virtual int invoke(unsigned int cmd,unsigned int param1,  unsigned int param2, unsigned int* output ) = 0;

            /**
            * Set sound effect tag for user
            * Initial version: GCloud 2.2.4
            *
            * @param vtype: sound effect type tag, view define of SoundTag
            * @param pParam: some sound tag need param,if not use NULL
            * @param pParam: nParmLen, the num of pParam.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo SetSoundTag(SoundTag vtype, float* pParam, int nParmLen) = 0;
            
            /**
            * Enable DualLink
            * Initial version: GCloud 2.2.4
            *
            * @param enable: enable detect if it is true, and disable if it is false.
            * 
            * @return If success returns kErrorNoSucc, otherwise returns other errno.
            * @see ErrorNo
            */
            virtual ErrorNo EnableDualLink(bool enable) = 0;

            /** 
            * Private Method
            * Initial version: GCloud 2.2.4
            */
            virtual void AndroidInit() = 0;
            
            /**
            * Initial version: GCloud 2.2.6
            */
            virtual bool IsPause() = 0;
            /****************** End of other APIs ***********************/
        };
    } // end of GVoice
} // end of GCloud


#endif /* _GCloud_GVoice_IGCloudVoiceExtension_h */
