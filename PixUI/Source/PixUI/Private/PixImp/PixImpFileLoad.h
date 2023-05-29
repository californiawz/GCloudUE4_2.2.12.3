/**************************************************

**** @file:     PixImpFileLoad.h

**** @brief:    pixui file load manager implementation

**** @author:   tianzelei

**** @date:     2020/12/08

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/


#pragma once
#include "CoreMinimal.h"

#include <functional>

#include "PixImpBase.h"
#include "PixUIExInterface.h"


typedef std::function<void(const TArray<uint8>& ary_Data)> PFun_FileLoad_Delegate;

class PixImpFileLoad : public PixImpBase
{
    //register imp
    DF_REG_PX_IMP(PixImpFileLoad)

protected:
    PixImpFileLoad();

public:
    ~PixImpFileLoad();

protected:
    /****************************************************************/
    /** PixImpBase implementation */
    virtual void OnStartup() override;
    virtual void OnTick(const float f_DeltaTime) override;
	virtual void OnClear() override;
    virtual void OnShutdown() override;
    /** PixImpBase implementation */
    /****************************************************************/

public:
    //load file by url
    static bool StartLoadFile(const FString& fstr_Url, PFun_FileLoad_Delegate fun_CallBack);

    //stop load file by url
    static bool StopLoadFile(const FString& fstr_Url);

    //save file to file path,ps:make sure the file path was correct
    static bool SaveFileToPath(const FString& fstr_FilePath, const TArray<uint8>& ary_Data, bool b_Overwrite = false);

    //create directory for url register font
    static bool CreateRegFontDir(FString& fstr_OutDir);

    //delete File
    static bool DeleteCacheFile(const FString& fstr_FilePath);

    //external file load delegate,for game module to load file itself
    static void SetExternalFileLoadDelegate(PFun_PixFileLoad fun_FileLoad);

	static void ShowLoadFileInfor();

protected:
	static void AddLoading(const FString& fstr_Url, PFun_FileLoad_Delegate fun_LoadCall);
	static void EndLoading(const FString& fstr_Url);

    static bool IsLoading(const FString& fstr_Url);

    static TMap<FString, PFun_FileLoad_Delegate>& LoadingMaps();

    static PFun_PixFileLoad& ExternalLoad();
};

