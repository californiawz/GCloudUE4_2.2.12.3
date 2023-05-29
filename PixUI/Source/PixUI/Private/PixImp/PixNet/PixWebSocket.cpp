/**************************************************

**** @file:     PixWebSocket.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/16

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixWebSocket.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#include "TimerManager.h"
#endif
#include "WebSocketsModule.h"

#include "PixUILog.h"
#include "PixUtil.h"


//Constructor
PixWebSocket::PixWebSocket(/*const pixui::net::WebSocketCreatorInfo& WsInfo*/) //: delegate_OnOpen_(nullptr), e_status_(EWS_Status::e_closed)
{
//     fstr_Url_           = WsInfo.pszUrl ? UTF8_TO_TCHAR(WsInfo.pszUrl) : TEXT("");
//     delegate_OnMessage_ = WsInfo.funMsg;
//     delegate_OnError_   = WsInfo.funError;
//     delegate_OnClose_   = WsInfo.funClose;

    TArray<FString> Protocols;
    Protocols.Add(TEXT("pixui"));

#if WITH_WEBSOCKETS  //ue4 engine macro
    WebSocket_ = FWebSocketsModule::Get().CreateWebSocket(fstr_Url_, Protocols);
#else
    WebSocket_ = nullptr;
#endif //WITH_WEBSOCKETS
}


//Destructor
PixWebSocket::~PixWebSocket()
{
    UnBindWebEvent();
    Close();
}


//default close
void PixWebSocket::Close()
{
    //default Close code 1000
    Close(1000, "");
}


//close with code and reason information
void PixWebSocket::Close(int n_Code, const char* psz_Reason)  // reason by the terminating null-character
{
    PxLog_Trace("Close code:%d reason:%s", n_Code, psz_Reason);
    if (!WebSocket_.IsValid())
    {
        PxLog_Error("PixWebSocket::Close WebSocket_ Is Invalid;make sure WITH_WEBSOCKETS is open!!!");
        return;
    }

    if (BeCanClose())
    {
        e_status_ = EWS_Status::e_closeing;
        FString fstr_Reason = UTF8_TO_TCHAR(psz_Reason);
        WebSocket_->Close(n_Code, fstr_Reason);
    }
    else
    {
        if (!IsClosed())
        {
            PxLog_Error("PixWebSocket::Close error,current status can not be Close :%d", (int)e_status_);
        }
    }
}


//async close
void PixWebSocket::CloseAsync()
{
    Close();
}


//send ping information
void PixWebSocket::Ping()
{
    //do not support
    ////opcode
    //uint8_t ucOpcode = frameData[0] & 0x0f; //WS_FrameType

    PxLog_Warning("PixWebSocket::Ping do not support");
}


//connect websocket sync
void PixWebSocket::Connect()
{
    PxLog_Trace("Connect %s",TCHAR_TO_UTF8(*fstr_Url_));

    if (!WebSocket_.IsValid())
    {
        PxLog_Error("PixWebSocket::Connect WebSocket_ Is Invalid;make sure WITH_WEBSOCKETS is open!!!");
        return;
    }

    if (BeCanConnected())
    {
        BindWebEvent();
        e_status_ = EWS_Status::e_connecting;
        WebSocket_->Connect();
    }
    else
    {
        PxLog_Error("PixWebSocket::Connect error,current status can not be connet :%d",(int)e_status_);
    }
    
}


//connect websocket async
void PixWebSocket::ConnectAsync(/*pixui::net::OnOpen fun_OnOpenCall*/)
{
    PxLog_Trace("ConnectAsync");
    //delegate_OnOpen_ = fun_OnOpenCall;
    Connect();
}


//send data
void PixWebSocket::Send(char* pData, int n_Len, bool b_IsBinary)
{
    if (!WebSocket_.IsValid())
    {
        PxLog_Error("PixWebSocket::Send WebSocket_ Is Invalid;make sure WITH_WEBSOCKETS is open!!!");
        return;
    }

    if (IsConnected())
    {
        PxLog_Trace("Send    len:%d", n_Len);
        WebSocket_->Send(pData, n_Len, b_IsBinary);
    }
    else
    {
        PxLog_Error("PixWebSocket::Send error,current status can not be send status:%d", (int)e_status_);
    }
}


//send data Async
void PixWebSocket::SendAsync(char* pData, int n_Len, bool b_IsBinary/*, pixui::net::OnSendCompleted fun_OnSendCompletedCall*/)
{
    if (!WebSocket_.IsValid())
    {
        PxLog_Error("PixWebSocket::SendAsync WebSocket_ Is Invalid;make sure WITH_WEBSOCKETS is open!!!");

        UWorld* World = PixUtil::GameWorld();
        if (World)
        {
            //call SetTimerForNextTick
            TWeakPtr<PixNetObjBase> pweek_self = AsShared();
            World->GetTimerManager().SetTimerForNextTick([=]() {
                PxLog_Trace("PixWebSocket::SendAsync call");
                if (pweek_self.IsValid())
                {
                    auto pSelf = (PixWebSocket*)(pweek_self.Pin().Get());
//                     if (fun_OnSendCompletedCall)
//                     {
//                         fun_OnSendCompletedCall(pSelf, false);
//                     }
                }
            });
        }
        else
        {
            PxLog_Error("PixWebSocket::Send PixUtil::GameWorld nill error");
//             if (fun_OnSendCompletedCall)
//             {
//                 fun_OnSendCompletedCall(this, false);
//             }
        }
        return;
    }

    if (IsConnected())
    {
        PxLog_Trace("SendAsync    len:%d", n_Len);

        WebSocket_->Send(pData, n_Len, b_IsBinary);

        UWorld* World = PixUtil::GameWorld();
        if (World)
        {
            //call SetTimerForNextTick
            TWeakPtr<PixNetObjBase> pweek_self = AsShared();
            World->GetTimerManager().SetTimerForNextTick([=]() {
                    PxLog_Trace("PixWebSocket::SendAsync call");
                    if (pweek_self.IsValid())
                    {
                        auto pSelf = (PixWebSocket*)(pweek_self.Pin().Get());
//                         if (fun_OnSendCompletedCall)
//                         {
//                             fun_OnSendCompletedCall(pSelf, pSelf->IsConnected());
//                         }
                    }
            });
        }
        else
        {
            PxLog_Error("PixWebSocket::Send error, PixUtil::GameWorld nill");
//             if (fun_OnSendCompletedCall)
//             {
//                 fun_OnSendCompletedCall(this, false);
//             }
        }
    }
    else
    {
        PxLog_Error("PixWebSocket::Send error,current status can not be send status:%d", (int)e_status_);
//         if (fun_OnSendCompletedCall)
//         {
//             fun_OnSendCompletedCall(this, false);
//         }
    }
}


//current do not support SetCredentials
void PixWebSocket::SetCredentials(const char* psz_UserName, const char* psz_Password, bool b_PreAuth)
{
    PxLog_Warning("PixWebSocket::SetCredentials do not support");
}


//current do not support SetProxy
void PixWebSocket::SetProxy(const char* psz_Url, const char* psz_UserName, const char* psz_Password)
{
    PxLog_Warning("PixWebSocket::SetProxy do not support");
}


bool PixWebSocket::IsConnectionClosed()
{
    return IsDisconnect();
}


void PixWebSocket::Destroy()
{
    Close();
}


//bind all web delegate
void PixWebSocket::BindWebEvent()
{
    if (!WebSocket_.IsValid())
    {
        PxLog_Error("PixWebSocket::BindWebEvent WebSocket_ Is Invalid;make sure WITH_WEBSOCKETS is open!!!");
        return;
    }

    UnBindWebEvent();

    //bind all web delegate
    WebSocket_->OnConnected().AddSP(this, &PixWebSocket::OnWebsocketConnected);
    WebSocket_->OnConnectionError().AddSP(this, &PixWebSocket::OnWebsocketConnectionError);
    WebSocket_->OnClosed().AddSP(this, &PixWebSocket::OnWebsocketClosed);
    WebSocket_->OnRawMessage().AddSP(this, &PixWebSocket::OnRawMessage);
    WebSocket_->OnMessage().AddSP(this, &PixWebSocket::OnMessage);
}


//Unbind all web delegate
void PixWebSocket::UnBindWebEvent()
{
    if (!WebSocket_.IsValid())
    {
        PxLog_Error("PixWebSocket::UnBindWebEvent WebSocket_ Is Invalid;make sure WITH_WEBSOCKETS is open!!!");
        return;
    }

    //Unbind all web delegate
    WebSocket_->OnConnected().RemoveAll(this);
    WebSocket_->OnConnectionError().RemoveAll(this);
    WebSocket_->OnClosed().RemoveAll(this);
    WebSocket_->OnMessage().RemoveAll(this);
    WebSocket_->OnRawMessage().RemoveAll(this);
}


void PixWebSocket::OnWebsocketConnected()
{
    PxLog_Trace("OnWebsocketConnected");
    e_status_ = EWS_Status::e_connected;
//     if (delegate_OnOpen_)
//     {
//         delegate_OnOpen_(this);
//     }
}


void PixWebSocket::OnWebsocketConnectionError(const FString& fstr_Error)
{
    PxLog_Trace("OnWebsocketConnectionError %s",TCHAR_TO_UTF8(*fstr_Error));
    e_status_ = EWS_Status::e_closed;
//     if (delegate_OnError_)
//     {
//         delegate_OnError_(this,TCHAR_TO_UTF8(*fstr_Error));
//     }
}


void PixWebSocket::OnWebsocketClosed(int32 n_StatusCode, const FString& fstr_Reason, bool b_WasClean)
{
    PxLog_Trace("OnWebsocketClosed n_StatusCode:%d fstr_Reason:%s b_WasClean:%d", n_StatusCode, TCHAR_TO_UTF8(*fstr_Reason), b_WasClean);
    e_status_ = EWS_Status::e_closed;
//     if (delegate_OnClose_)
//     {
//         delegate_OnClose_(this, n_StatusCode, TCHAR_TO_UTF8(*fstr_Reason), b_WasClean);
//     }
}


void PixWebSocket::OnRawMessage(const void* p_Data, SIZE_T l_Size, SIZE_T l_BytesRemaining)
{
    PxLog_Trace("OnRawMessage l_Size:%ld l_BytesRemaining:%ld", l_Size, l_BytesRemaining);
//     if (delegate_OnMessage_)
//     {
//         if (l_BytesRemaining == 0 && ReceiveBuffer_.Num() == 0)
//         {
//             pixui::net::ReceiveData data_Received;
//             data_Received.isText = false;
//             data_Received.bytes = (char *)p_Data;
//             data_Received.bytesLen = l_Size;
//             data_Received.isPing = false;
// 
//             delegate_OnMessage_(this, data_Received);
//         }
//         else
//         {
//             //
//             ReceiveBuffer_.Append((const uint8*)p_Data, l_Size);
//             if (l_BytesRemaining == 0)
//             {
//                 pixui::net::ReceiveData data_Received;
//                 data_Received.isText = false;
//                 data_Received.bytes = (char *)ReceiveBuffer_.GetData();
//                 data_Received.bytesLen = ReceiveBuffer_.Num();
//                 data_Received.isPing = false;
// 
//                 delegate_OnMessage_(this, data_Received);
// 
//                 ReceiveBuffer_.Empty();
//             }
//         }
//     }
}


void PixWebSocket::OnMessage(const FString& fstr_Message)
{
    PxLog_Trace("OnMessage    %s", TCHAR_TO_UTF8(*fstr_Message));
//     if (delegate_OnMessage_)
//     {
//         pixui::net::ReceiveData data_Received;
//         data_Received.isText = true;
//         TArray<uint8> ReceiveBuffer;
//         if (!fstr_Message.IsEmpty())
//         {
//             ReceiveBuffer.Append((const uint8*)(TCHAR_TO_UTF8(*fstr_Message)), fstr_Message.Len());
//         }
//         data_Received.bytes = (char*)ReceiveBuffer.GetData();
//         data_Received.bytesLen = ReceiveBuffer.Num();
//         data_Received.isPing = false;
//         delegate_OnMessage_(this, data_Received);
//         ReceiveBuffer.Empty();
//     }
}