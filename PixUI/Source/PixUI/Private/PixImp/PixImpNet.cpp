/**************************************************

**** @file:     PixImpNet.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixImpNet.h"

#include "PixUILog.h"

#include "PixNet/PixWebSocket.h"
#include "PixNet/PixXmlRequest.h"




PixImpNet::PixImpNet()
    : PixImpBase(TEXT("PixImpNet"))
{

}


PixImpNet::~PixImpNet()
{

}


void PixImpNet::OnStartup()
{
    // do something stuff when OnStartup
}


void PixImpNet::OnTick(const float f_DeltaTime)
{
    // do something stuff when tick
}


void PixImpNet::OnClear()
{
	//do something stuff
}


void PixImpNet::OnShutdown()
{
    //for each net object
    for (auto netObj : NetObjs())
    {
        netObj->Destroy();
    }

    NetObjs().Empty();
}

/*

PixWebSocket* PixImpNet::CreateWebSocket(const pixui::net::WebSocketCreatorInfo& WsInfo)
{
    if (!Get())
    {
        PxLog_Error("PixImpNet::CreateWebSocket PixImpNet do not startup!!!!!");
        return nullptr;
    }

#if WITH_WEBSOCKETS //ue4 macro
    TSharedPtr<PixWebSocket> p_TmpWebSocket = MakeShareable(new PixWebSocket(WsInfo));
    Get()->NetObjs().Add(p_TmpWebSocket);
    return p_TmpWebSocket.Get();
#else
    PxLog_Error("Game Do not support websockets!!!!! WITH_WEBSOCKETS do not open");
    return nullptr;
#endif //WITH_WEBSOCKETS
}


bool PixImpNet::DestroyWebSocket(PixWebSocket* p_WebSocket)
{
    if (!Get())
    {
        PxLog_Error("PixImpNet::DestroyWebSocket PixImpNet do not startup!!!!!");
        return false;
    }

    bool b_Find = Get()->RemoveNetObj(p_WebSocket);
    if (!b_Find)
    {
        PxLog_Error("PixNetMgr::DestroyWebSocket Error,can not found websocket %p", p_WebSocket);
    }
    return b_Find;
}


PixXmlRequest* PixImpNet::CreateXMLHttpRequest(pixui::net::XHRCallbacks& fun_XhrCall)
{
    if (!Get())
    {
        PxLog_Error("PixImpNet::CreateXMLHttpRequest PixImpNet do not startup!!!!!");
        return false;
    }

    TSharedPtr<PixXmlRequest> p_TmpXmlRequest = MakeShareable(new PixXmlRequest(fun_XhrCall));
    Get()->NetObjs().Add(p_TmpXmlRequest);
    return p_TmpXmlRequest.Get();
}


bool PixImpNet::DestroyXMLHttpRequest(PixXmlRequest* p_XMLHttpRequest)
{
    if (!Get())
    {
        PxLog_Error("PixImpNet::CreateXMLHttpRequest PixImpNet do not startup!!!!!");
        return false;
    }

    bool b_find = Get()->RemoveNetObj(p_XMLHttpRequest);
    if (!b_find)
    {
        PxLog_Error("PixNetMgr::DestroyXMLHttpRequest Error,can not found XMLHttpRequest %p", p_XMLHttpRequest);
    }
    return b_find;
}
*/

TSharedPtr<PixNetObjBase> PixImpNet::FindNetObj(PixNetObjBase* p_NetObj)
{
    TSharedPtr<PixNetObjBase> sptr_NetObj = nullptr;
    for (auto ptr : NetObjs())
    {
        if (ptr.Get() == p_NetObj)
        {
            sptr_NetObj = ptr;
            break;
        }
    }
    return sptr_NetObj;
}


bool PixImpNet::RemoveNetObj(PixNetObjBase* p_NetObj)
{
    bool b_find = false;
    auto sptr_NetObj = FindNetObj(p_NetObj);
    if (sptr_NetObj.IsValid())
    {
        b_find = true;
        sptr_NetObj->Destroy();
        NetObjs().Remove(sptr_NetObj);
    }
    return b_find;
}