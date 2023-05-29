//------------------------------------------------------------------------------
//
// File:    ILockStep
// Module:  LockStep
// Version: 1.0
// Author:  vforkk
//
//------------------------------------------------------------------------------

#ifndef _GCloud_LockStep_hpp
#define _GCloud_LockStep_hpp
#include "LockStepPublicDefine.h"

namespace GCloud
{
    
    namespace LockStep
    {
        class LockStepInitializeInfo;
        class FrameInfo;
        class LockStepObserver;
        class EXPORT_CLASS ILockStep
        {
            
        public:
            static ILockStep& GetInstance();
            
        public:
            virtual void AddObserver(LockStepObserver* observer) = 0;
            virtual void RemoveObserver(LockStepObserver* observer) = 0;
            
        public:
            
            /* Initialize
            */
            virtual bool Initialize(const LockStepInitializeInfo& initInfo) = 0;
            
            /* Log into the relay server
            */
            virtual void Login(const char* accessInfo, int len) = 0;
            
            /* tell relay server you've been ready, and can start playing game
            */
            virtual void Ready() = 0;
            
            /* set the start frameID, telling the sdk (LockStep)
            */
            virtual void SetStartFrame(int start) = 0;
            
            /* disconnect from server
            */
            virtual void Logout() = 0;
            
            /* Update
            */
            virtual void Update() = 0;
            
            /* if LockStep has logined to RelayServer, return true, else return false
            */
            virtual bool HasLogined() = 0;
            
            /* if Game(Relay Server) has started, return true, else return false
            */
            virtual bool HasStarted() = 0;
            
			/* get status
			*/
			virtual LockStepStatus GetStatus() = 0;

            /* When automatic reconnection fails, call this function to reconnect manually.
            */
            virtual bool ReconnectManually() = 0;
        public:
            /* Send operation data to lockstep server, which will push to lockstep client enclosed in a frame
               flag: combined with members of LockStepInputFlag
            */
            virtual bool Input(const char* data, int len, bool rawUdp = true, int flag = 0) = 0;
            
            /* return the next frame data from the cache
            */
            virtual FrameInfo* PeekFrame() = 0;
            
            virtual bool PeekFrameAndEncode(char* data, int* length, bool* hasFrame) = 0;

            /* PopFrame must be called after PeekFrame return unnull value
            */
            virtual void PopFrame() = 0;
            
        public:
            /* flag: combined with members of LockStepBroadcastFlag
            */
            virtual bool SendBroadcast(const char* data, int len, bool rawUdp = true, int flag = 0) = 0;
            
        public:
            virtual uint32_t GetRoomId() = 0;
            virtual uint32_t GetPlayerId() = 0;
            /* GetNetFrameId
            */
            virtual uint32_t GetCurrentMaxFrameId() = 0;
            /* zero is invalid id
            */
            virtual uint32_t GetLastInputSeqId() = 0;
        public:
            /* get current network speed(ms)
            */
            virtual void GetCurrentSpeed(int& udp, int& tcp) = 0;
            
            /* Only available after logout
            */
            virtual const LockStepFlowStaticInfo& GetStatic() = 0;
            
            /* get current network speed(ms) by accumulate
            */
            virtual void GetCurrentSpeedAcc(int& udp, int& tcp, uint32_t curFrameId) = 0;
            
            /* get frame interval(ms)
            */
            virtual int GetFrameIntervalMS() = 0;
            
            /* Profiling
            */
            virtual void EnableProfiling(bool enabled) = 0;
            
            virtual int GetMaxProfileFrameID() = 0;
            
            virtual bool GetFrameProfileData(uint32_t frameID, char* data, int* len) = 0;
            
            /* set network emulator config
            */
            virtual void SetNetworkEmulatorConfig(const NetworkEmulatorConfig& config) = 0;

            virtual void OnApplicationPause(bool pauseStatus) = 0;
        };
        
        class EXPORT_CLASS LockStepObserver
        {
        public:
            LockStepObserver();
            virtual ~LockStepObserver();
            
        public:
            virtual void OnLockStepLoginProc(const LockStepResult& result) = 0;
            virtual void OnLockStepLogoutProc(const LockStepResult& result) = 0;
            virtual void OnLockStepReadyProc(const LockStepResult& result) = 0;
            virtual void OnLockStepStateChangedProc(LockStepState state, const LockStepResult& result) = 0;
            
            virtual void OnLockStepRecvedFrameProc(int numberOfReceivedFrames) = 0;
            virtual void OnLockStepBroadcastProc(const FrameCollection* frames) = 0;
        };
        
// #if defined(_WIN32) || defined(_WIN64)
        // inline ILockStep* GetLockStepInstance(HMODULE hDll)
        // {
            // typedef ILockStep*( *CreateFunction)();
            // CreateFunction pFunc = NULL;
            // pFunc = (CreateFunction)GetProcAddress(hDll, "gcloud_lockstep_getinstance");
            // if(pFunc == NULL)
            // {
                // return NULL;
            // }
            // return pFunc();
        // }
// #endif
    }
}
#endif  // _GCloud_LockStep_hpp 
