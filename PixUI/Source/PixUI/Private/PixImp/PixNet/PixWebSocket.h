/**************************************************

**** @file:     PixWebSocket.h

**** @brief:    PixUI websocket implementation

**** @author:   tianzelei

**** @date:     2020/12/16

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "CoreMinimal.h"
#include "IWebSocket.h"

#include "PixNetObjBase.h"

//#include "hf_inetcreator.h"



class PixWebSocket : public PixNetObjBase // , public pixui::net::WebSocketClient
{
public:
    PixWebSocket(/*const pixui::net::WebSocketCreatorInfo& WsInfo*/);

    virtual ~PixWebSocket();

public:
    /************************************************************************/
    //~ Begin IWebSocketClient Interface
    virtual void Close();
    virtual void Close(int n_Code, const char* psz_Reason); // reason by the terminating null-character
    virtual void CloseAsync();
	virtual void Ping();
    virtual void Connect();
    virtual void ConnectAsync(/*pixui::net::OnOpen fun_OnOpenCall*/);
    virtual void Send(char* pData, int n_Len, bool b_IsBinary);
	virtual void SendAsync(char* pData, int n_Len, bool b_IsBinary
		/*,pixui::net::OnSendCompleted fun_OnSendCompletedCall*/);

    virtual void SetCredentials(const char* psz_UserName, const char* psz_Password, bool b_PreAuth);
    virtual void SetProxy(const char* psz_Url, const char* psz_UserName, const char* psz_Password);

    virtual bool IsConnectionClosed(); // used for gc mark to free this object;
    //~ End IWebSocketClient Interface
    /************************************************************************/

public:
    /************************************************************************/
    //~ Begin PixNetObjBase Interface
    virtual void Destroy() override;
    //~ End pPixNetObjBase Interface
    /************************************************************************/

public:
    void BindWebEvent();
    void UnBindWebEvent();

    /* Handlers for websocket events */
    void OnWebsocketConnected();
    void OnWebsocketConnectionError(const FString& fstr_Error);
    void OnWebsocketClosed(int32 n_StatusCode, const FString& fstr_Reason, bool b_WasClean);
    void OnRawMessage(const void* p_Data, SIZE_T l_Size, SIZE_T l_BytesRemaining);
    void OnMessage(const FString& fstr_Message);

public:
    bool IsConnected() {
        return EWS_Status::e_connected == e_status_;
    }

    bool IsConnecting() {
        return EWS_Status::e_connecting == e_status_;
    }

    bool BeCanClose() {
        return IsConnected();
    }

    bool BeCanConnected() {
        return IsClosed();
    }

    bool IsClosed() {
        return EWS_Status::e_closed == e_status_;
    }

    bool IsCloseing() {
        return EWS_Status::e_closeing == e_status_;
    }

    bool IsDisconnect() {
        return BeCanConnected();
    }

private:
    //websocket connect url
    FString fstr_Url_;

    //open event delegate
    //pixui::net::OnOpen       delegate_OnOpen_;

    //message event delegate
    //pixui::net::OnMessage    delegate_OnMessage_;

    //error event delegate
    //pixui::net::OnError      delegate_OnError_;

    //close event delegate
    //pixui::net::OnClose      delegate_OnClose_;

    //IWebSocket
    TSharedPtr<IWebSocket> WebSocket_;

    //websocekt status
    enum class EWS_Status
    {
        e_closed,
        e_connecting,
        e_connected,
        e_closeing,
    };

    //current websocekt status
    EWS_Status e_status_;

    //receive buffer for store complete data
    TArray<uint8> ReceiveBuffer_;
};

