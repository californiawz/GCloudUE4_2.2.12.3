/**************************************************

**** @file:     PixImpFileLoad.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#include "PixImpFileLoad.h"

//#include "Runtime/Core/Public/HAL/ThreadingBase.h"
#include "HAL/ThreadingBase.h"
#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#else
#include "Engine/GameEngine.h"
#endif

#include "Core.h"
#include "Http.h"

#include "PixUILog.h"
#include "PixUIBPLibrary.h"
#include "PixUILibMgr.h"


PixImpFileLoad::PixImpFileLoad()
    : PixImpBase(TEXT("PixImpFileLoad"))
{

}


PixImpFileLoad::~PixImpFileLoad()
{

}


void PixImpFileLoad::OnStartup()
{
    //do something stuff
}


void PixImpFileLoad::OnTick(const float f_DeltaTime)
{
    //do something stuff
}


void PixImpFileLoad::OnClear()
{
	//do something stuff
}


void PixImpFileLoad::OnShutdown()
{
    //clear all load request
	int n_loop_count = 0;
	while (LoadingMaps().Num() > 0)
    {
        auto Itera = LoadingMaps().CreateIterator();
        StopLoadFile(Itera->Key);
		if (++n_loop_count > 10000)
		{
			PxLog_Warning("PixImpFileLoad::OnShutdown error, loading count over 10000!!!!!!!");
			LoadingMaps().Reset();
			break;
		}
    }
}


bool PixImpFileLoad::StartLoadFile(const FString& fstr_Url, PFun_FileLoad_Delegate fun_LoadCall)
{
	if (fstr_Url.StartsWith(TEXT("http")))
	{//url file loaded by pixui core,so there did not need
		return false;
	}

    bool b_Ret = false;
    if (IsInGameThread())
    {
        if (!PixImpFileLoad::Get())
        {
            PxLog_Error("PixImpFileLoad::StartLoadFile Error ,Do Not Startup!!!!");
            return b_Ret;
        }

        if (IsLoading(fstr_Url))
        {//was in loading
            PxLog_Warning("PixImpFileLoad::StartLoadFile was in Loading........:%S",TCHAR_TO_UTF8(*fstr_Url));
            return b_Ret;
        }

		AddLoading(fstr_Url, fun_LoadCall);

        //try to load external
        if (ExternalLoad() != nullptr)
        {
            b_Ret = PixImpFileLoad::ExternalLoad()(fstr_Url, [=](const TArray<uint8>& array_Data) {
                
                //make sure the url was in load array
                if (PixImpFileLoad::Get() && IsLoading(fstr_Url))
                {
                    if (fun_LoadCall)
                    {
                        fun_LoadCall(array_Data);
                    }

					EndLoading(fstr_Url);
                    PxLog_Trace("PixImpFileLoad::StartLoadFile ExternalLoad() url:%s  ", TCHAR_TO_UTF8(*fstr_Url));
                }
                else
                {
                    PxLog_Warning("PixImpFileLoad::StartLoadFile ExternalLoad call was shutdown or not in loading   url:%s  Do not CallBack", TCHAR_TO_UTF8(*fstr_Url));
                }
            });
        }

        if (b_Ret) //loaded by ExternalLoad
            return b_Ret;

        PxLog_Trace("PixImpFileLoad::LoadFile start load file in Game thread: %s", TCHAR_TO_UTF8(*fstr_Url));
        if (!fstr_Url.StartsWith(TEXT("http")))
        {
            //local file
            TArray<uint8> array_FileData;
            if (FFileHelper::LoadFileToArray(array_FileData, *fstr_Url))
            {//load file by local file path
                /*
                UWorld* World = PixUtil::GameWorld();
                if (World)
                {
                    //can not make sure this is call in game thread,can not call SetTimerForNextTick
                    World->GetTimerManager().SetTimerForNextTick([=]() {

                        if (funDelegate)
                        {
                            funDelegate(TCHAR_TO_UTF8(*strFilePath), aryFileData.GetData(), aryFileData.Num());
                        }
                    });
                }
                else
                {
                    UE_LOG(PixUI_Module, Error, TEXT("StartLoadFile World nill"));
                }
                */

                PxLog_Log("PixImpFileLoad::LoadFile success pFilePath:%s", TCHAR_TO_UTF8(*fstr_Url));
                b_Ret = true;
                if (fun_LoadCall)
                {
                    fun_LoadCall(array_FileData);
                }
            }
            else
            {
				//try to load by asset data
				FString fstr_asset_file_path = FPaths::ProjectContentDir() + fstr_Url;
				if (FFileHelper::LoadFileToArray(array_FileData, *fstr_asset_file_path))
				{//load by local asset file path
					PxLog_Log("PixImpFileLoad::LoadFile success by game asset path pFilePath:%s", TCHAR_TO_UTF8(*fstr_asset_file_path));
					b_Ret = true;
					if (fun_LoadCall)
					{
						fun_LoadCall(array_FileData);
					}
				}
				else
				{
					//do not process call back
					PxLog_Error("PixImpFileLoad::LoadFile Failed to load file: %s", TCHAR_TO_UTF8(*fstr_Url));
				}
            }
			EndLoading(fstr_Url);
        }
        else
        {
            PxLog_Trace("PixImpFileLoad::LoadFile start load http file file: %s", TCHAR_TO_UTF8(*fstr_Url));

            //load http or https file
#if ENGINE_MAJOR_VERSION < 5

/////////////////////////////////////////////////////////////////////for ue4
#if ENGINE_MINOR_VERSION >= 26
            TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpReuest = FHttpModule::Get().CreateRequest();
#else
            TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
#endif //ENGINE_MINOR_VERSION >= 26
            /////////////////////////////////////////////////////////////////////for ue4

#else

/////////////////////////////////////////////////////////////////////for ue5
            TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpReuest = FHttpModule::Get().CreateRequest();
            /////////////////////////////////////////////////////////////////////for ue5

#endif  //ENGINE_MAJOR_VERSION < 5

            HttpReuest->SetURL(fstr_Url);
            HttpReuest->SetVerb(TEXT("GET"));
            //HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
            HttpReuest->OnProcessRequestComplete().BindLambda([=](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {

                //make sure the url was in load array
                if (PixImpFileLoad::Get() && IsLoading(fstr_Url))
                {
                    if (HttpResponse.IsValid())
                    {
                        if (fun_LoadCall)
                        {
                            fun_LoadCall(HttpResponse->GetContent());
                        }
                    }
                    else
                    {
                        if (fun_LoadCall)
                        {
                            TArray<uint8> ary_Data;
                            fun_LoadCall(ary_Data);
                        }
                    }
					EndLoading(fstr_Url);
                    PxLog_Trace("PixImpFileLoad::LoadFile http besuccess:%d url:%s  ", bSucceeded, TCHAR_TO_UTF8(*fstr_Url));
                }
                else
                {
                    PxLog_Warning("PixImpFileLoad::LoadFile was shutdown or not in loading http besuccess:%d url:%s  Dot not CallBack", bSucceeded, TCHAR_TO_UTF8(*fstr_Url));
                }
                
            });

            HttpReuest->OnRequestProgress().BindLambda([](FHttpRequestPtr HttpRequest, int32 BytesSent, int32 BytesReceived) {
                PxLog_Trace("PixImpFileLoad::LoadFile OnRequestProgress process BytesSent:%d requestContentLen:%d  BytesReceived:%d Total_Recv_Size_1:%d otal_Recv_Size_2:%d  http url:%s  ",
                    BytesSent, HttpRequest->GetContentLength(), BytesReceived,
                    (HttpRequest->GetResponse().IsValid() ? HttpRequest->GetResponse()->GetContentLength() : 0),
                    (HttpRequest->GetResponse().IsValid() ? HttpRequest->GetResponse()->GetContent().Num() : 0),
                    TCHAR_TO_UTF8(*(HttpRequest->GetURL())));
            });
            b_Ret = HttpReuest->ProcessRequest();
        }
    }
    else
    {
        //put in load array and will be load in next game thread tick
        b_Ret = true;

        PxLog_Trace("PixImpFileLoad::LoadFile start not in Game Thread tp load file: %s", TCHAR_TO_UTF8(*fstr_Url));
        ////call in game thread
        AsyncTask(ENamedThreads::GameThread, [=]()
            {
               bool b_RetTmp  = StartLoadFile(fstr_Url, fun_LoadCall);
               if (!b_RetTmp)
               {//load file error,
                   //Due to the return true in the asynchronous thread,when StartLoadFile error need to deal with fun_LoadCall
                   if (fun_LoadCall)
                   {
                       TArray<uint8> ary_Data;
                       fun_LoadCall(ary_Data);
                   }
               }
            });
    }

    return b_Ret;
}

bool PixImpFileLoad::StopLoadFile(const FString& fstr_Url)
{
    auto p_LoadingFile = LoadingMaps().Find(fstr_Url);
    if (p_LoadingFile)
    {
        if (Get())
        {
            //stop load file need to deal with loaded call back delegate
            if ((*p_LoadingFile))
            {
                TArray<uint8> array_FileData;
                (*p_LoadingFile)(array_FileData);
            }
            PxLog_Trace("PixImpFileLoad::StopLoadFile %s",TCHAR_TO_UTF8(*fstr_Url));
        }
        else
        {
            PxLog_Trace("PixImpFileLoad::StopLoadFile Was Shutdown!!! %s Do not Call", TCHAR_TO_UTF8(*fstr_Url));
        }
		EndLoading(fstr_Url);
        return true;
    }
    return false;
}


bool PixImpFileLoad::SaveFileToPath(const FString& fstr_FilePath, const TArray<uint8>& ary_Data, bool b_Overwrite /*= false*/)
{
    bool b_Ret = false;
    if (!(FPaths::FileExists(fstr_FilePath) && !b_Overwrite))
    {
        //IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        //PlatformFile.OpenWrite()

        b_Ret = FFileHelper::SaveArrayToFile(ary_Data, *fstr_FilePath);
        if (!b_Ret)
        {
            PxLog_Error("PixImpFileLoad::SaveFileToPath Error,path:%s", TCHAR_TO_UTF8(*fstr_FilePath));
        }
        /*
        IFileHandle* p_Handle = IPlatformFile::GetPlatformPhysical().OpenWrite(*fstr_FilePath, false, false);
        if (!p_Handle)
        {
            PxLog_Error("PixImpFileLoad::SaveFileToPath Failed to create file: %s", TCHAR_TO_UTF8(*fstr_FilePath));
        }
        else
        {
            p_Handle->Write(arry_Data.GetData(), arry_Data.Num());
            p_Handle->Flush();

            delete p_Handle;
            p_Handle = nullptr;


            PxLog_Log("PixImpFileLoad::SaveFileToPath Save file:%s",TCHAR_TO_UTF8(*fstr_FilePath));
            b_ret = true;
        }
        */
    }
    else
    {
        PxLog_Error("File Exists and can not overwrite path:%s", TCHAR_TO_UTF8(*fstr_FilePath));
    }

    return b_Ret;
}


bool PixImpFileLoad::CreateRegFontDir(FString& fstr_OutDir)
{
    bool b_Ret = true;

    //file cache path
    fstr_OutDir = UPixUIBPLibrary::PixUI_GetCachePath();
    fstr_OutDir += TEXT("regfont/");

    if (!FPaths::DirectoryExists(fstr_OutDir))
    {
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        b_Ret = PlatformFile.CreateDirectory(*fstr_OutDir);
        if (!b_Ret)
        {
            b_Ret = false;
            PxLog_Error("PixImpFileLoad::CreateRegFontDir error dir:%s", TCHAR_TO_UTF8(*fstr_OutDir));
        }
    }

    return b_Ret;
}


bool PixImpFileLoad::DeleteCacheFile(const FString& fstr_FilePath)
{
    bool b_Ret = false;

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    b_Ret = PlatformFile.DeleteFile(*fstr_FilePath);

    return b_Ret;
}


void PixImpFileLoad::SetExternalFileLoadDelegate(PFun_PixFileLoad fun_FileLoad)
{
    ExternalLoad() = fun_FileLoad;
}


void PixImpFileLoad::ShowLoadFileInfor()
{
	PxLog_Log("PixImpFileLoad CurLoading file count:%d", LoadingMaps().Num());
	for (auto loading : LoadingMaps())
	{
		PxLog_Log("    PixImpFileLoad %s in loading...", TCHAR_TO_UTF8(*loading.Key));
	}
}


void PixImpFileLoad::AddLoading(const FString& fstr_Url, PFun_FileLoad_Delegate fun_LoadCall)
{
	PxLog_Log("PixImpFileLoad AdddLoading %s total count:%d", TCHAR_TO_UTF8(*fstr_Url), LoadingMaps().Num());
	LoadingMaps().Add(fstr_Url, fun_LoadCall);
}

void PixImpFileLoad::EndLoading(const FString& fstr_Url)
{
	PxLog_Log("PixImpFileLoad EndLoading %s total count:%d", TCHAR_TO_UTF8(*fstr_Url), LoadingMaps().Num());
	LoadingMaps().Remove(fstr_Url);
}


bool PixImpFileLoad::IsLoading(const FString& fstr_Url)
{
    return LoadingMaps().Find(fstr_Url) ? true : false;
}


TMap<FString, PFun_FileLoad_Delegate>& PixImpFileLoad::LoadingMaps()
{
    static TMap<FString, PFun_FileLoad_Delegate> map_Loading_S;
    return map_Loading_S;

}


PFun_PixFileLoad& PixImpFileLoad::ExternalLoad()
{
    static PFun_PixFileLoad fun_FileLoadExternal_s = nullptr;
    return fun_FileLoadExternal_s;
}