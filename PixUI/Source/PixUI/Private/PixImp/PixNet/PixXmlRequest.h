/**************************************************

**** @file:     PixXmlRequest.h

**** @brief:    PixUI XML requset implementation

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "PixUIDef.h"
#include "Http.h"

#include <string>

#include "PixNetObjBase.h"

//#include "hf_ihttpxml.h"


class PixXmlRequest : public PixNetObjBase //, public pixui::net::XMLHttpRequestBase
{
public:
    PixXmlRequest(/*pixui::net::XHRCallbacks& XhrFunCalls*/);

    virtual ~PixXmlRequest();

public:
    /************************************************************************/
    //~ Begin IXMLHttpRequest Interface
    virtual void Open(/*pixui::net::RequestMessage& requestMsg*/);
    virtual void Send(void* p_Data, size_t l_Len);
    virtual void GetResponse(char** ppsz_OutRes, int* pn_OutLen);
    virtual int GetHttpStatusCode();
    virtual const char* GetAllResponseHeader();
    virtual const char* GetResponseHeader(const char* psz_HeaderName, int n_Len);
    virtual const char* GetResponseUrl();
    virtual void TerminateRequest();
    virtual void SetReuqestHeader(const char* psz_HeaderName, int n_NameLen,
        const char* psz_HeaderValue, int n_ValueLen);
    virtual void SetTimeout(long long ll_Timeout);
    virtual const char* GetErrorMsg();
    //~ End IXMLHttpRequest Interface
    /************************************************************************/

public:
    /************************************************************************/
    //~ Begin PixNetObjBase Interface
    virtual void Destroy() override;
    //~ End pPixNetObjBase Interface
    /************************************************************************/

public:
    void SetStateUnset() {
        //e_RequestState_ = pixui::net::REQUEST_UNSET;
    }

    void SetStateOpened() {
        //e_RequestState_ = pixui::net::REQUEST_OPENED;
    }

    void SetStateHearderRecved() {
        //e_RequestState_ = pixui::net::REQUEST_HEADER_RECEIVED;
    }

    void SetStateLoading() {
        //e_RequestState_ = pixui::net::REQUEST_LOADING;
    }

    void SetStateDone() {
        //e_RequestState_ = pixui::net::REQUEST_DONE;
    }

public:
    static void ClearStaticValue();

protected:
    //FHttpModule::Get() timeout set for global
    static void SetGlobalTimeOut(float f_TimeOutInSec);

    //Restore the default timeout
    static void RestoreDefaultTimeOut(PixXmlRequest* pRequset);

    static std::string& StorageStaticStrRef();

    //for keep default timeout
    static float f_TimeOutOld_s;

    //current timeout
    static float f_TimeOutNew_s;

    //timeout set counts for PixXmlRequest
    static uint32 un_SetTimeOutCount_s;

private:
    //xml delegate information
    //pixui::net::XHRCallbacks XhrFunCalls_;

    //Is or not timeout set
    bool b_SetTimeOut_;

    //request status
    //pixui::net::RequestState e_RequestState_;

#if ENGINE_MAJOR_VERSION < 5

	/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION >= 26
	//request http object
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> sptr_HttpReuest_;
#else
	TSharedPtr<IHttpRequest> sptr_HttpReuest_;
#endif //ENGINE_MINOR_VERSION >= 26
	/////////////////////////////////////////////////////////////////////for ue4

#else

	/////////////////////////////////////////////////////////////////////for ue5
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> sptr_HttpReuest_;
	/////////////////////////////////////////////////////////////////////for ue5

#endif  //ENGINE_MAJOR_VERSION < 5

    //last error information
    FString fstr_error_;
};

