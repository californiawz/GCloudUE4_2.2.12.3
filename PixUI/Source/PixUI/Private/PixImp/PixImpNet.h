/**************************************************

**** @file:     PixImpNet.h

**** @brief:    pixui net manager implementation

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#pragma once
#include "CoreMinimal.h"

#include "PixImpBase.h"
#include "PixNet/PixWebSocket.h"
#include "PixNet/PixXmlRequest.h"

class PixImgBrush;

class PixImpNet : public PixImpBase
{
    //register imp
    DF_REG_PX_IMP(PixImpNet)

protected:
    PixImpNet();

public:
    virtual ~PixImpNet();

protected:
    /************************************************************************/
    /** PixImpBase implementation */
    virtual void OnStartup() override;
    virtual void OnTick(const float f_DeltaTime) override;
	virtual void OnClear() override;
    virtual void OnShutdown() override;
    /** PixImpBase implementation */
    /************************************************************************/

public:
	/*
    //for web socket       Obsolete interface 
    static PixWebSocket* CreateWebSocket(const pixui::net::WebSocketCreatorInfo& WsInfo);
    static bool DestroyWebSocket(PixWebSocket* p_WebSocket);

    //for xml http request             Obsolete interface 
    static PixXmlRequest* CreateXMLHttpRequest(pixui::net::XHRCallbacks& fun_XhrCall);
    static bool DestroyXMLHttpRequest(PixXmlRequest* p_XMLHttpRequest);
	*/

protected:
    //manager net object
    TSharedPtr<PixNetObjBase> FindNetObj(PixNetObjBase* p_NetObj);
    bool RemoveNetObj(PixNetObjBase* p_NetObj);

    TArray<TSharedPtr<PixNetObjBase>>& NetObjs() {
        return ary_PixNetObj_;
    }

private:
    TArray<TSharedPtr<PixNetObjBase>> ary_PixNetObj_;

};