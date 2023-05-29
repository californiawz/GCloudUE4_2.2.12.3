/**************************************************

**** @file:     PixXmlRequest.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixXmlRequest.h"

#include "PixUILog.h"


//Static member variable initialization
float PixXmlRequest::f_TimeOutOld_s = 0.0f;
float PixXmlRequest::f_TimeOutNew_s = 0.0f;
uint32 PixXmlRequest::un_SetTimeOutCount_s = 0;


//Constructor
PixXmlRequest::PixXmlRequest(/*pixui::net::XHRCallbacks& XhrFunCalls*/): //XhrFunCalls_(XhrFunCalls), 
	b_SetTimeOut_(false)
{
    SetStateUnset();
    sptr_HttpReuest_ = FHttpModule::Get().CreateRequest();
}

//Destructor
PixXmlRequest::~PixXmlRequest()
{
    Destroy();
}


//request url
void PixXmlRequest::Open(/*pixui::net::RequestMessage &requestMsg*/)
{
	FString fstr_url;// = UTF8_TO_TCHAR(requestMsg.url);
	FString fstr_verb;// = UTF8_TO_TCHAR(requestMsg.method);

    sptr_HttpReuest_->SetURL(fstr_url);
    sptr_HttpReuest_->SetVerb(fstr_verb);


    TWeakPtr<PixNetObjBase> pweek_self = AsShared();

    sptr_HttpReuest_->OnProcessRequestComplete().BindLambda([=](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
        PxLog_Trace("PixXmlRequest::OnProcessRequestComplete http url:%s  besuccess:%d", TCHAR_TO_UTF8(*fstr_url), bSucceeded);
        if (pweek_self.IsValid())
        {
            PixXmlRequest* pSelf = (PixXmlRequest*)(pweek_self.Pin().Get());
            pSelf->SetStateDone();
        }
    });

    sptr_HttpReuest_->OnRequestProgress().BindLambda([=](FHttpRequestPtr HttpRequest, int32 BytesSent, int32 BytesReceived) {
        //libcurl check Progress first then check header received
        PxLog_Trace("PixXmlRequest::OnRequestProgress http url:%s  process BytesSent:%d requestContentLen:%d  BytesReceived:%d Total_Recv_Size_1:%d otal_Recv_Size_2:%d", 
            TCHAR_TO_UTF8(*(HttpRequest->GetURL())), BytesSent,HttpRequest->GetContentLength(), BytesReceived, 
            (HttpRequest->GetResponse().IsValid() ? HttpRequest->GetResponse()->GetContentLength() : 0),
            (HttpRequest->GetResponse().IsValid() ? HttpRequest->GetResponse()->GetContent().Num() : 0));
            
        if (pweek_self.IsValid())
        {
            PixXmlRequest* pSelf = (PixXmlRequest*)(pweek_self.Pin().Get());
            pSelf->SetStateLoading();
        }
    });

#if ENGINE_MAJOR_VERSION < 5

	/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION > 19  //before major_Version 4.19,do not support OnHeaderReceived

	sptr_HttpReuest_->OnHeaderReceived().BindLambda([=](FHttpRequestPtr HttpRequest, const FString& HeaderName, const FString& NewHeaderValue) {
		//libcurl check Progress first then check header received
		PxLog_Trace("PixXmlRequest::OnHeaderReceived http url:%s  HeaderName:%s  NewHeaderValue:%s", TCHAR_TO_UTF8(*(HttpRequest->GetURL())), TCHAR_TO_UTF8(*HeaderName), TCHAR_TO_UTF8(*NewHeaderValue));

		if (pweek_self.IsValid())
		{
			PixXmlRequest* pSelf = (PixXmlRequest*)(pweek_self.Pin().Get());

			pSelf->SetStateHearderRecved();
}
	});

#endif //ENGINE_MINOR_VERSION > 19
	/////////////////////////////////////////////////////////////////////for ue4
#else
	/////////////////////////////////////////////////////////////////////for ue5
	sptr_HttpReuest_->OnHeaderReceived().BindLambda([=](FHttpRequestPtr HttpRequest, const FString& HeaderName, const FString& NewHeaderValue) {
		//libcurl check Progress first then check header received
		PxLog_Trace("PixXmlRequest::OnHeaderReceived http url:%s  HeaderName:%s  NewHeaderValue:%s", TCHAR_TO_UTF8(*(HttpRequest->GetURL())), TCHAR_TO_UTF8(*HeaderName), TCHAR_TO_UTF8(*NewHeaderValue));

		if (pweek_self.IsValid())
		{
			PixXmlRequest* pSelf = (PixXmlRequest*)(pweek_self.Pin().Get());

			pSelf->SetStateHearderRecved();
		}
		});
	/////////////////////////////////////////////////////////////////////for ue5
#endif //ENGINE_MAJOR_VERSION < 5
}


//send data
void PixXmlRequest::Send(void* p_Data, size_t l_Len)
{
    PxLog_Trace("PixXmlRequest::Send data:%p ,len:%ld", p_Data, l_Len);

    TArray<uint8> ary_send;
    ary_send.Append((uint8*)p_Data, l_Len);
    sptr_HttpReuest_->SetContent(ary_send);

#if UE_BUILD_DEBUG  //debug only
    //for trace out headers information
    auto ary_headers = sptr_HttpReuest_->GetAllHeaders();
    PxLog_Trace("PixXmlRequest::Send Header --->");
    for (auto header : ary_headers)
    {
        PxLog_Trace("%s",TCHAR_TO_UTF8(*header));
    }
    PxLog_Trace("PixXmlRequest::Send Header <---");

#endif //UE_BUILD_DEBUG

    if (!sptr_HttpReuest_->ProcessRequest())
    {
        //ProcessRequest error
        fstr_error_ = EHttpRequestStatus::ToString(sptr_HttpReuest_->GetStatus());
        PxLog_Error("PixXmlRequest::Send ProcessRequest error url:%s msg:%s", TCHAR_TO_UTF8(*(sptr_HttpReuest_->GetURL())), TCHAR_TO_UTF8(*fstr_error_));
    }
    else
    {
        PxLog_Trace("PixXmlRequest::Send ProcessRequest ----- %s",TCHAR_TO_UTF8(*(sptr_HttpReuest_->GetURL())));
        SetStateOpened();
    }
}


//get Response
void PixXmlRequest::GetResponse(char** ppsz_OutRes, int* pn_OutLen)
{
    FHttpResponsePtr ptr_response = sptr_HttpReuest_->GetResponse();
    if (ptr_response.IsValid())
    {
        auto resContent = ptr_response->GetContent();
        if (ppsz_OutRes)
        {
            *ppsz_OutRes = (char*)resContent.GetData();
            if (pn_OutLen)
            {
                *pn_OutLen = resContent.Num();
            }
            PxLog_Trace("PixXmlRequest::GetResponse n_OutLen:%d", resContent.Num());
        }
    }
}


//get Response Code
int PixXmlRequest::GetHttpStatusCode()
{
    int n_status_code = 0;
    FHttpResponsePtr ptr_response = sptr_HttpReuest_->GetResponse();
    if (ptr_response.IsValid())
    {
        n_status_code = ptr_response->GetResponseCode();
        PxLog_Trace("PixXmlRequest::GetHttpStatus GetResponseCode:%d", n_status_code);
    }
    return n_status_code;
}


//get all response header information
const char* PixXmlRequest::GetAllResponseHeader()
{
    //Local static string to storage header information,to make sure the return value safe
    StorageStaticStrRef() = "";

    FHttpResponsePtr ptr_response = sptr_HttpReuest_->GetResponse();
    if (ptr_response.IsValid())
    {
        FString fstr_split = UTF8_TO_TCHAR("\r\n");
        TArray<FString> array_header = ptr_response->GetAllHeaders();
        // header1:value1'\r'header1:value1....
        for (auto header:array_header)
        {
            if (StorageStaticStrRef().length() <= 0)
            {
                StorageStaticStrRef() = TCHAR_TO_UTF8(*header);
            }
            else
            {
                StorageStaticStrRef() += TCHAR_TO_UTF8(*fstr_split);
                StorageStaticStrRef() += TCHAR_TO_UTF8(*header);
            }
        }
    }

    PxLog_Trace("PixXmlRequest::GetAllResponseHeader -->  %s", StorageStaticStrRef().c_str());
    //FString TCHAR_TO_UTF8 as return value is not safe
    return StorageStaticStrRef().c_str();
}


//get Response Header by header name
const char* PixXmlRequest::GetResponseHeader(const char* psz_HeaderName, int n_Len)
{
    StorageStaticStrRef() = "";
    FHttpResponsePtr ptr_response = sptr_HttpReuest_->GetResponse();
    if (ptr_response.IsValid())
    {
        StorageStaticStrRef() = TCHAR_TO_UTF8(*(ptr_response->GetHeader(UTF8_TO_TCHAR(psz_HeaderName))));

        PxLog_Trace("PixXmlRequest::GetResponseHeader -->%s :  %s", psz_HeaderName, StorageStaticStrRef().c_str());
    }
    
    return StorageStaticStrRef().c_str();
}


const char* PixXmlRequest::GetResponseUrl()
{
    StorageStaticStrRef() = "";

    FHttpResponsePtr ptr_response = sptr_HttpReuest_->GetResponse();
    if (ptr_response.IsValid())
    {
        StorageStaticStrRef() = TCHAR_TO_UTF8(*(ptr_response->GetURL()));

        PxLog_Trace("PixXmlRequest::GetResponseUrl -->  %s", StorageStaticStrRef().c_str());
    }

    return StorageStaticStrRef().c_str();
}


void PixXmlRequest::TerminateRequest()
{
    PxLog_Trace("PixXmlRequest::TerminateRequest");

    sptr_HttpReuest_->CancelRequest();

    SetStateUnset();
}

void PixXmlRequest::SetReuqestHeader(const char* psz_HeaderName, int n_NameLen,
    const char* psz_HeaderValue, int n_ValueLe)
{
    PxLog_Trace("PixXmlRequest::SetReuqestHeader  %s:%s", psz_HeaderName, psz_HeaderValue);

    sptr_HttpReuest_->SetHeader(UTF8_TO_TCHAR(psz_HeaderName), UTF8_TO_TCHAR(psz_HeaderValue));
}



void PixXmlRequest::SetTimeout(long long ll_Timeout)
{
    PxLog_Trace("PixXmlRequest::SetTimeout  %ld", ll_Timeout);

    double lf_current_timeout = (double)ll_Timeout / 1000.0f;

    if ((float)lf_current_timeout != f_TimeOutNew_s)
    {
        f_TimeOutNew_s = (float)lf_current_timeout;

        b_SetTimeOut_ = true;

        SetGlobalTimeOut(f_TimeOutNew_s);
    }
}


const char* PixXmlRequest::GetErrorMsg()
{
    return TCHAR_TO_UTF8(*fstr_error_);
}


void PixXmlRequest::Destroy()
{
    RestoreDefaultTimeOut(this);

    if (sptr_HttpReuest_->GetStatus() == EHttpRequestStatus::Type::Processing)
    {
        sptr_HttpReuest_->CancelRequest();
    }
    ClearStaticValue();
}


void PixXmlRequest::ClearStaticValue()
{
    std::string str_Temp;
    StorageStaticStrRef().swap(str_Temp);
}


void PixXmlRequest::SetGlobalTimeOut(float f_TimeOutInSec)
{
    if (un_SetTimeOutCount_s <= 0)
    {
        f_TimeOutOld_s = FHttpModule::Get().GetHttpTimeout();
    }

    PxLog_Trace("PixXmlRequest::SetGlobalTimeOut old:%f  new:%f", f_TimeOutOld_s, f_TimeOutInSec);
    FHttpModule::Get().SetHttpTimeout(f_TimeOutInSec);
    un_SetTimeOutCount_s++;
}


void PixXmlRequest::RestoreDefaultTimeOut(PixXmlRequest* pRequset)
{
    if (pRequset->b_SetTimeOut_)
    {
        if (--un_SetTimeOutCount_s <= 0)
        {
            PxLog_Trace("PixXmlRequest::TimeOutInvalid old:%f  ", f_TimeOutOld_s);
            FHttpModule::Get().SetHttpTimeout(f_TimeOutOld_s);
        }
        pRequset->b_SetTimeOut_ = false;
    }
}



std::string& PixXmlRequest::StorageStaticStrRef()
{
    static std::string str_StorageStaticStr_s = "";
    return str_StorageStaticStr_s;
}