/**************************************************

**** @file:     PixDyLib.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/12/09

**** @group:    pandora

**** @copyright: Copyright 2019 pandora. All Rights Reserved.

***************************************************/



#include "PixDyLib.h"

#include "CoreMinimal.h"
#include "Projects.h"

#include "PixUILog.h"
#include "PixUIDef.h"

#include <string>
#include <list>

#if PLATFORM_ANDROID

#include <Android/AndroidApplication.h>
#include <Android/AndroidJava.h>
#include <Android/AndroidJNI.h>
#include <Android/AndroidJavaEnv.h>

#include <sys/syscall.h>
#include <dlfcn.h>

extern jobject AndroidJNI_GetJavaAssetManager();

#ifndef RTLD_NOLOAD
// RTLD_NOLOAD not defined for all platforms before NDK15
// not defined for NDK platform before 21
#define RTLD_NOLOAD   0x00004
#endif //RTLD_NOLOAD

extern JavaVM* GJavaVM;

#endif //PLATFORM_ANDROID

#if PLATFORM_WINDOWS

#include "Windows/AllowWindowsPlatformTypes.h"

#endif //PLATFORM_WINDOWS



#if defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
//definition pixui lib function


#if defined(PLATFORM_WINDOWS) && PLATFORM_WINDOWS
#include "windows.h"
#include <libloaderapi.h>
#elif defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
#include <sys/syscall.h>
#include <dlfcn.h>
#include <jni.h>
#elif defined(PLATFORM_MAC) && PLATFORM_MAC
#include <sys/syscall.h>
#include <dlfcn.h>
#elif defined(PLATFORM_IOS) && PLATFORM_IOS
//#include "PxIosLoader.h"
#endif

#endif //defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)


#if defined(PLATFORM_IOS) && PLATFORM_IOS
typedef void* (*PxIosLibLoader)(const char* strFuncName);

#import <Foundation/Foundation.h>

@interface PixDyLibFrameworkLoader : NSObject

@end

@implementation PixDyLibFrameworkLoader

+ (void*)loadFramework:(NSString*)frameworkName clsName : (NSString*)ns_class funcName : (NSString*)ns_func
{
	// Put setup code here. This method is called before the invocation of each test method in the class.
	NSLog(@"PixDyLibFrameworkLoader loadFramework frameworkName:%@  ns_class:%@", frameworkName, ns_class);
	void* p_ret = nullptr;
	//NSString * name_class = [NSString stringWithFormat:@"%@_fw_class",frameworkName];

	//for + function
	Class px_ocClass = NSClassFromString(ns_class);
	if (px_ocClass)
	{
		SEL px_selector = NSSelectorFromString(ns_func);

		//for + function
		IMP px_imp = nullptr;
		px_imp = [px_ocClass methodForSelector : px_selector];
		// so can not use respondsToSelector if (px_imp && [px_ocClass respondsToSelector:px_selector]) {
		if (px_imp)
		{
			//@try
			{
				void* (*funcPx)(Class, SEL) = (void* (*) (Class, SEL)) px_imp;
				p_ret = funcPx(px_ocClass, px_selector);
			}
//			@catch (NSException* e)
//			{
//				p_ret = nullptr;
//				NSLog(@"PixDyLibFrameworkLoader loadFramework Exception: %@", e);
//			}
//			@finally
//			{
//				NSLog(@"PixDyLibFrameworkLoader loadFramework finally");
//			}
		}
		else
		{
			NSLog(@"PixDyLibFrameworkLoader loadFramework %@ can not found selector getPxLibInfor", frameworkName);
		}
	}
	else
	{
		NSLog(@"PixDyLibFrameworkLoader loadFramework %@ can not found class:%@", frameworkName, ns_class);
	}
	return p_ret;
}

@end

void* LoadIosFrameworkPxPluginApi(const char* frameworkName)
{
	NSString* nstr_frameworkName = [NSString stringWithUTF8String : frameworkName];
	NSString* nstr_clsName = [nstr_frameworkName stringByAppendingString : @"_fw_class"];
	void* pInfor = [PixDyLibFrameworkLoader loadFramework : nstr_frameworkName clsName : nstr_clsName funcName : @"getPxPluginLibInfor"];
	return pInfor;
}
#endif //defined(PLATFORM_IOS) && PLATFORM_IOS


namespace px_plugin
{
	bool ue_dyCheckLibLoaded(const TCHAR* Filename)
	{
		bool b_ret = false;
#if PLATFORM_WINDOWS
		//GetModuleHandle(Filename),the system will be deal with it
#else
		//check lib loaded by others
		if (nullptr != dlopen(TCHAR_TO_ANSI(Filename), RTLD_NOLOAD | RTLD_LAZY | RTLD_LOCAL))
		{
			b_ret = true;
		}
#endif //PLATFORM_WINDOWS

		return b_ret;
	}

#if ENGINE_MAJOR_VERSION < 5

	/////////////////////////////////////////////////////////////////////for ue4

#if ENGINE_MINOR_VERSION <= 21 //4.21 do not support android FPlatformProcess

#if PLATFORM_ANDROID
	void* ue_dyopen_4_18(const TCHAR* Filename)
	{
		check(Filename);

		// Check if dylib is already loaded
		void* Handle = dlopen(TCHAR_TO_ANSI(Filename), RTLD_NOLOAD | RTLD_LAZY | RTLD_LOCAL);

		if (!Handle)
		{
			// Not loaded yet, so try to open it
			Handle = dlopen(TCHAR_TO_ANSI(Filename), RTLD_LAZY | RTLD_LOCAL);
		}
		if (!Handle)
		{
			PxLog_Error("dlopen failed: %s", dlerror());
		}
		return Handle;
	}

	bool  ue_dyfree_4_18(void* DllHandle)
	{
		check(DllHandle);
		return dlclose(DllHandle) == 0;
	}

	void* ue_dyfun_4_18(void* DllHandle, const TCHAR* ProcName)
	{
		check(DllHandle);
		check(ProcName);
		return dlsym(DllHandle, TCHAR_TO_ANSI(ProcName));
	}
#endif //PLATFORM_ANDROID

#endif  //ENGINE_MINOR_VERSION <= 21
	/////////////////////////////////////////////////////////////////////for ue4

#endif //ENGINE_MAJOR_VERSION < 5

	void* ue_dyopen(const TCHAR* Filename)
	{
#if ENGINE_MAJOR_VERSION < 5

		/////////////////////////////////////////////////////////////////////for ue4
#if PLATFORM_ANDROID && ENGINE_MINOR_VERSION <= 21
		return ue_dyopen_4_18(Filename);
#else

		return FPlatformProcess::GetDllHandle(Filename);
#endif //PLATFORM_ANDROID && ENGINE_MINOR_VERSION <= 21
		/////////////////////////////////////////////////////////////////////for ue4
#else
		/////////////////////////////////////////////////////////////////////for ue5
		return FPlatformProcess::GetDllHandle(Filename);
		/////////////////////////////////////////////////////////////////////for ue5
#endif  //ENGINE_MAJOR_VERSION < 5
	}

	bool  ue_dyFree(void* DllHandle)
	{
#if ENGINE_MAJOR_VERSION < 5

		/////////////////////////////////////////////////////////////////////for ue4
#if PLATFORM_ANDROID && ENGINE_MINOR_VERSION <= 21
		return ue_dyfree_4_18(DllHandle);
#else
		FPlatformProcess::FreeDllHandle(DllHandle);
#endif //PLATFORM_ANDROID && ENGINE_MINOR_VERSION <= 21
		/////////////////////////////////////////////////////////////////////for ue4

#else

		/////////////////////////////////////////////////////////////////////for ue5
		FPlatformProcess::FreeDllHandle(DllHandle);
		/////////////////////////////////////////////////////////////////////for ue5

#endif  //ENGINE_MAJOR_VERSION < 5
		return true;
	}

	void* ue_dyFun(void* DllHandle, const TCHAR* ProcName)
	{
#if ENGINE_MAJOR_VERSION < 5

		/////////////////////////////////////////////////////////////////////for ue4
#if PLATFORM_ANDROID && ENGINE_MINOR_VERSION <= 21
		return ue_dyfun_4_18(DllHandle, ProcName);
#else
		return FPlatformProcess::GetDllExport(DllHandle, ProcName);
#endif //PLATFORM_ANDROID && ENGINE_MINOR_VERSION <= 21
		/////////////////////////////////////////////////////////////////////for ue4

#else

		/////////////////////////////////////////////////////////////////////for ue5
		return FPlatformProcess::GetDllExport(DllHandle, ProcName);
		/////////////////////////////////////////////////////////////////////for ue5

#endif  //ENGINE_MAJOR_VERSION < 5
	}

    std::string ue_dyError()
    {
#if PLATFORM_ANDROID || PLATFORM_MAC
		return dlerror();
#elif PLATFORM_WINDOWS
        static char szErrorCode[20] = { 0 };
        memset(szErrorCode, 0, sizeof(char) * 20);
        sprintf_s(szErrorCode, "%ld", GetLastError());
		return szErrorCode;
#endif //PLATFORM_ANDROID || PLATFORM_MAC
        return "";
    }

    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Need to ensure the order of dependencies to ensure correct loading and release
    /*
    eg: 
        A.dll dependencies to B.dll (*.dll  *.so  *.dylib)
		The Load order
        TEXT("B.dll")
        TEXT("A.dll")
    */

#if PLATFORM_WINDOWS

#if PLATFORM_64BITS
    static FString fstr_DllPlatform = TEXT("Win64");
#else
    static FString fstr_DllPlatform = TEXT("Win32");
#endif	//PLATFORM_64BITS

#elif PLATFORM_MAC
    static FString fstr_DllPlatform = TEXT("Mac");
#elif PLATFORM_IOS
    static FString fstr_DllPlatform = TEXT("IOS");
#elif PLATFORM_ANDROID
    static FString fstr_DllPlatform = TEXT("");
#else
    static FString fstr_DllPlatform = TEXT("");
#endif //PLATFORM_WINDOWS

    FString GetDllDirectory()
    {
#if PLATFORM_ANDROID
        FString fstr_Dllpath;
#else
		//for windows and mac os,ios do not support dynamic loader
        FString fstr_RootPath = IPluginManager::Get().FindPlugin(TEXT("PixUI"))->GetBaseDir();

#if WITH_EDITOR
		//edit user source dir for run
		FString fstr_Dllpath = fstr_RootPath + TEXT("/Source/PixUI/ThirdParty/Libraries/") + fstr_DllPlatform + TEXT("/");
#else
		FString fstr_Dllpath = fstr_RootPath + TEXT("/Binaries/") + fstr_DllPlatform + TEXT("/");
#endif //WITH_EDITOR

        //FString fstrDllpath = strRootPath + TEXT("/Binaries/") + fstrDllPlatform + TEXT("/") + fstrDllName;
#endif //PLATFORM_ANDROID
        return fstr_Dllpath;
    }

	struct LibHandleInfor {
		LibHandleInfor()
		{
			p_handle_ = nullptr;
			b_loaded_ = false;
		}

		LibHandleInfor(void* p_handle, bool b_loaded)
		{
			p_handle_ = p_handle;
			b_loaded_ = b_loaded;
		}

		void empty()
		{
			p_handle_ = nullptr;
			b_loaded_ = false;
		}

		void* p_handle_;
		bool b_loaded_;
	};

	static std::list<LibHandleInfor> gListDependentDllHandles;
	static void* gHMainPluginLib = nullptr;
	static bool gBLoadedByOther = false;

#if PLATFORM_WINDOWS

#define DF_PX_PLUGIN_LIB_NAME "PxKit.dll"
	static std::string gStrDependentDlls[] = {
			""
	};

#elif PLATFORM_ANDROID

#define DF_PX_PLUGIN_LIB_NAME "libPxKit.so"

#if defined(DF_PX_PX_CURL) && DF_PX_PX_CURL
	static std::string gStrDependentDlls[] = {
			"libpixuiCurl.so"
	};
#else
	static std::string gStrDependentDlls[] = {};
#endif

#elif PLATFORM_IOS
	
#define DF_PX_PLUGIN_LIB_NAME "PxKit"
	static std::string gStrDependentDlls[] = {};

#elif PLATFORM_MAC
	
#define DF_PX_PLUGIN_LIB_NAME "libPxKit.dylib"
	static std::string gStrDependentDlls[] = {};

#else

#define DF_PX_PLUGIN_LIB_NAME "PxKit"
	static std::string gStrDependentDlls[] = {};

#endif


	void* dllOpen(const char* pszLibPath, bool& bLoadedByOther)
	{
		// Check if dylib is already loaded
#if defined(PLATFORM_WINDOWS) && PLATFORM_WINDOWS
		void* pHandle = (void*)LoadLibraryA(pszLibPath);
		if (!pHandle)
		{
			PxLog_Log("LoadLibraryA error %s code:%d", pszLibPath, ::GetLastError());
		}
		return pHandle;
#elif defined(PLATFORM_IOS) && PLATFORM_IOS
		void* libLoaderHandle = LoadIosFrameworkPxPluginApi(DF_PX_PLUGIN_LIB_NAME);
		return libLoaderHandle;
#else
		void* libHandle = dlopen(pszLibPath, RTLD_NOLOAD | RTLD_LAZY | RTLD_LOCAL);
		if (!libHandle)
		{
			bLoadedByOther = false;
			// Not loaded yet, so try to open it
			libHandle = dlopen(pszLibPath, RTLD_LAZY | RTLD_LOCAL);
		}
		else
		{
			bLoadedByOther = true;
		}
		if (!libHandle)
		{
			PxLog_Error("dlopen failed: %s", dlerror());
		}
		return libHandle;
#endif
	}

	void* DllExport(void* libHandle, const char* pszFunName)
	{
		if (libHandle && pszFunName)
		{
#if defined(PLATFORM_WINDOWS) && PLATFORM_WINDOWS
			return (void*)GetProcAddress((HMODULE)libHandle, pszFunName);
#elif defined(PLATFORM_IOS) && PLATFORM_IOS
			return ((PxIosLibLoader)libHandle)(pszFunName);
#else
			return dlsym(libHandle, pszFunName);
#endif
		}
		return nullptr;
	}

	bool dllClose(void* libHandle, bool bAlreadyLoaded, const char* strLibName = "")
	{
		if (libHandle)
		{
#if defined(PLATFORM_WINDOWS) && PLATFORM_WINDOWS
			auto bRet = FreeLibrary((HMODULE)libHandle);
			if (!bRet)
			{
				PxLog_Log("FreeLibrary error code:%d", ::GetLastError());
			}
			return bRet == TRUE;
#elif defined(PLATFORM_IOS) && PLATFORM_IOS
			return true;
#elif defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
			PxLog_Trace("dlclose start %s", strLibName);
			bool bRet = dlclose(libHandle) == 0;
			if (!bRet)
			{
				PxLog_Warning("dlclose Error %s code: %s", strLibName, dlerror());
			}
			if (bRet)
			{
				if (!bAlreadyLoaded)
				{
					/*
					 * ����Ƿ������Ŀ�����
					 */

					void* libHandleSub = dlopen(strLibName, RTLD_NOLOAD | RTLD_LAZY | RTLD_LOCAL);
					if (libHandleSub)
					{
						//������������;�����
						dlclose(libHandleSub);
						bRet = false;
					}

					/*
					bRet = false;
					int nLoopCount = 5;
					for (int i = 1; i <= nLoopCount; i++)
					{
						PxLog_Trace("dlclose %s retry %d time", strLibName, i);
						libHandleSub = dlopen(strLibName, RTLD_NOLOAD | RTLD_LAZY | RTLD_LOCAL);
						if (libHandleSub)
						{
							bool bTmpRet = dlclose(libHandleSub) == 0;
							if (!bTmpRet)
							{
								PxLog_Trace("dlclose %s time: %d", strLibName, i);
								break;
							}
							if (i == nLoopCount)
							{
								PxLog_Warning("dlclose Error %s Loop more than %d", strLibName, nLoopCount);
							}
						}
						else
						{
							bRet = true;
							PxLog_Log("dlclose %s time: %d  success!!!", strLibName, i);
							break;
						}
					}
					 */
				}
			}
			return bRet;
#else
			bool bRet = dlclose(libHandle) == 0;
			if (!bRet)
			{
				PxLog_Warning("dlclose Error %s", dlerror());
			}
			return bRet;
#endif
		}
		return true;
	}

	const char* fmtAndroidLibPath(const char* pszLibName)
	{
		return pszLibName;
	}

#if defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
	typedef jint(*JNI_OnLoadFun)(JavaVM* vm, void* reserved);
	typedef void (*JNI_OnUnloadFun)(JavaVM* vm, void* reserved);

	void Call_Jni_OnLoaded(void* hLibHandle, const char* pszLibName)
	{
		if (hLibHandle)
		{
			JNI_OnLoadFun onLoadFun = (JNI_OnLoadFun)DllExport(hLibHandle, "JNI_OnLoad");
			if (onLoadFun)
			{
				PxLog_Log("Call_Jni_OnLoaded so:%s Call JNI_OnLoad", pszLibName);

				//get vm
				onLoadFun(GJavaVM, nullptr);
			}
			else
			{
				PxLog_Error("Call_Jni_OnLoaded so:%s have no JNI_OnLoad function", pszLibName);
			}
		}
		else
		{
			PxLog_Error("Call_Jni_OnLoaded error hLibHandle invalid %s", pszLibName);
		}
	}

	void Call_Jni_UnOnLoaded(void* hLibHandle, const char* pszLibName)
	{
		if (hLibHandle)
		{
			JNI_OnUnloadFun onUnLoadFun = (JNI_OnUnloadFun)DllExport(hLibHandle, "JNI_OnUnload");
			if (onUnLoadFun)
			{
				PxLog_Log("Call_Jni_UnOnLoaded so:%s Call JNI_OnUnload", pszLibName);
				onUnLoadFun(GJavaVM, nullptr);
			}
			else
			{
				PxLog_Error("CallAndroidUnLoadJni so:%s have no JNI_OnUnload function", pszLibName);
			}
		}
		else
		{
			PxLog_Error("CallAndroidUnLoadJni error p_so_handle invalid %s", pszLibName);
		}
	}
#endif

	void freeDependentDll()
	{
		while (gListDependentDllHandles.size() > 0)
		{
			LibHandleInfor backItem = gListDependentDllHandles.back();
			int nIndex = gListDependentDllHandles.size() - 1;
#if defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
			if (!backItem.b_loaded_)
			{
				Call_Jni_UnOnLoaded(backItem.p_handle_, gStrDependentDlls[nIndex].c_str());
			}
#endif
			dllClose(backItem.p_handle_, backItem.b_loaded_, gStrDependentDlls[nIndex].c_str());
			gListDependentDllHandles.pop_back();
		}
	}

	bool loadDependentDll()
	{
		bool bRet = true;
		for (int i = 0; i < sizeof(gStrDependentDlls) / sizeof(std::string); i++)
		{
#if PLATFORM_WINDOWS
			if (gStrDependentDlls[i].length() > 0)
#endif//#if PLATFORM_WINDOWS
			{

				bool bLoadedByOther = false;
				void* pHandleDll = dllOpen(gStrDependentDlls[i].c_str(), bLoadedByOther);
				if (pHandleDll)
				{
					if (!bLoadedByOther)
					{
#if defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
						Call_Jni_OnLoaded(pHandleDll, gStrDependentDlls[i].c_str());
#endif
					}
					gListDependentDllHandles.push_back(LibHandleInfor(pHandleDll, bLoadedByOther));
				}
				else
				{
					PxLog_Warning("loadDependentDll error lib:%s", gStrDependentDlls[i].c_str());
					freeDependentDll();
					bRet = false;
					break;
				}
			}
		}
		return bRet;
	}

	bool loadPxPluginLib()
	{
		if (gHMainPluginLib)
			return true;

		if (!loadDependentDll())
		{
			PxLog_Warning("loadPxPluginLib error in loadDependentDll");
			return false;
		}

		FPlatformProcess::PushDllDirectory(*GetDllDirectory());

		gHMainPluginLib = dllOpen(fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME), gBLoadedByOther);
		if (gHMainPluginLib)
		{
			bool bRet = true;

			if (!gBLoadedByOther)
			{
#if defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
				Call_Jni_OnLoaded(gHMainPluginLib, fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
#endif
			}
			if (bRet)
			{
				PxLog_Log("loadPxPluginLib success loaded %s", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
			}
			else
			{
				PxLog_Warning("loadPxPluginLib failed loaded %s", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
			}

			return bRet;
		}
		else
		{
			freeDependentDll();
			PxLog_Warning("loadPxPluginLib error not loaded %s", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
		}
		return false;
	}

	bool unLoadPxPluginLib()
	{
		if (gHMainPluginLib)
		{
			if (!gBLoadedByOther)
			{
#if defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
				Call_Jni_UnOnLoaded(gHMainPluginLib, fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
#endif
			}

#if defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
			bool bClosed = dllClose(gHMainPluginLib, gBLoadedByOther, fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
			if (!gBLoadedByOther && !bClosed)
			{
				//��������Ǳ����������ˣ������ٴγ�ʼ��Jni_OnLoaded���Ͳ�ж�ش˿���
				//android 9.0 thread_local will keep the lib with NODELETE and can not dlclose the so

				PxLog_Error("DLL %s will keep loaded", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));

				//android 6.0 dlclose always return true, need dllOpen again
				gHMainPluginLib = dllOpen(fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME), gBLoadedByOther);
				Call_Jni_OnLoaded(gHMainPluginLib, fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));

				gHMainPluginLib = nullptr;
				gBLoadedByOther = false;

				//dependent keep dll
				int nIndex = 0;
				for (auto& item : gListDependentDllHandles)
				{
					PxLog_Error("ependentDll %s will keep loaded", gStrDependentDlls[nIndex].c_str());
					nIndex++;
				}
				gListDependentDllHandles.clear();

				PxLog_Error("unLoadPxPluginLib success keep dll loaded %s", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
			}
			else
			{
				gHMainPluginLib = nullptr;
				gBLoadedByOther = false;

				freeDependentDll();

				PxLog_Log("unLoadPxPluginLib success dll %s", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
			}
#else
			dllClose(gHMainPluginLib, gBLoadedByOther, fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
			gHMainPluginLib = nullptr;
			gBLoadedByOther = false;

			freeDependentDll();

			PxLog_Log("unLoadPxPluginLib finish dll %s", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME));
#endif

			FPlatformProcess::PopDllDirectory(*GetDllDirectory());
		}
		return true;
	}

#if defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
    //definition pixui lib function

	typedef const char* (*pxVersion_proc)();
	typedef const char* (*pxExternalAgent_proc)();
	typedef bool (*pxStartup_proc)(px_plugin::IPluginImp* pPluginImp, const char* pszWritePath, const char* externalAgent);
	typedef void (*pxSetCachePath_proc)(const char* pszCachePath);
	typedef void (*pxDebugPauseResume_proc)(const bool bPause);
	typedef void (*pxCatchDebugTrace_proc)(bool bCatch);
	typedef void (*pxTimeTick_proc)(float fDuration);
	typedef void (*pxEnterBackground_proc)();
	typedef void (*pxEnterForeground_proc)();
	typedef bool (*pxShutdown_proc)();

	typedef pixui::PxViewHandle(*pxViewCreate_proc)(uint32_t id);
	typedef void (*pxViewInit_proc)(pixui::PxViewHandle hView, pixui::IHostWindow* pIWinEvent, pixui::IHostDraw* pIWinDraw, const int nWidth, const int nHeight, const pixui::PxViewDeviceParam* pDeviceParam);
	typedef void* (*pxViewGetContext_proc)(pixui::PxViewHandle hView);
	typedef int (*pxViewLoadPageFromData_proc)(pixui::PxViewHandle hView, const unsigned char* pData, const unsigned int unDataSize, const char* pszBasePath);
	typedef int (*pxViewLoadPageFromUrl_proc)(pixui::PxViewHandle hView, const char* pszPageUrl);
	typedef bool (*pxViewHitTest_proc)(pixui::PxViewHandle hView, const int nXpos, const int nYpos);
	typedef bool (*pxViewMouseEvent_proc)(pixui::PxViewHandle hView, const int nXpos, const int nYpos, const int nZpos, const pixui::MouseButton emBtnEvent, const bool bDown);
	typedef bool (*pxViewTouchEvent_proc)(pixui::PxViewHandle hView, const int nXpos, const int nYpos, const pixui::int32 nTouchPoint, const pixui::ETouchPhase emTouchPhase);
	typedef bool (*pxViewKeyEvent_proc)(pixui::PxViewHandle hView, const pixui::EKeyCode emKey, const unsigned char ucModifiers, const bool bDown);
	typedef int (*pxViewKeyboardInput_proc)(pixui::PxViewHandle hView, const char* szInput, const bool bEndInput, const bool bLostFocus, const bool bReplace);
	typedef int (*pxViewWinSizeUpdate_proc)(pixui::PxViewHandle hView, const int nNewWidth, const int nNewHeight);
	typedef void (*pxViewResetRenderScale_proc)(pixui::PxViewHandle hView, float scale);
	typedef void (*pxViewScreenSizeUpdate_proc)(pixui::PxViewHandle hView, int screenWidth, int screenHeight);
	typedef bool (*pxViewTick_proc)(pixui::PxViewHandle hView);
	typedef int (*pxViewPaint_proc)(pixui::PxViewHandle hView, int nParam);
	typedef int (*pxViewRenderFrame_proc)(pixui::PxViewHandle hView);
	typedef int (*pxViewRenderReset_proc)(pixui::PxViewHandle hView, int nStatus, void* pParams);
	typedef int (*pxViewPostMessage_proc)(pixui::PxViewHandle hView, const char* pszMessage, const pixui::PxViewHandle h_src_view);
	typedef pixui::PxViewHandle(*pxViewGetScriptVM_proc)(pixui::PxViewHandle hView);
	typedef int (*pxViewClose_proc)(pixui::PxViewHandle hView);
	typedef int (*pxViewDestroy_proc)(pixui::PxViewHandle hView);

	typedef void (*pxSetEngineOpenPageDelegate_proc)(pixui::EngineOpenPageDelegate callback);
	typedef int (*pxExecuteEngineOpenPageDelegate_proc)(int winId, pixui::LoadPageArg* loadPageArg);
	typedef void (*pxSetEngineClosePageDelegate_proc)(pixui::EngineClosePageDelegate callback);
	typedef bool (*pxExecuteEngineClosePageDelegate_proc)(int winId);
	typedef void (*pxSetEnginePostMessageDelegate_proc)(pixui::EnginePostMessageDelegate callback);
	typedef bool (*pxExecuteEnginePostMessageDelegate_proc)(int winId, const char* message);
	typedef void (*pxSetNativePostMessageDelegate_proc)(pixui::NativePostMessageDelegate callback);
	typedef void (*pxExecuteNativePostMessageDelegate_proc)(int winId, int type, int code, const char* message);
	typedef const char* (*pxLoadAppletConfig_proc)(const char* appletAssetsPath, const char* appletName);

	typedef int (*pxInnerRenderSetSystemFontParam_proc)(bool beLoadSystemFonts, bool beAsyncLoadSystemFonts);
	typedef int (*pxInnerRenderCount_proc)();
	typedef const char* (*pxInnerRenderName_proc)(int nIndex);
	typedef int (*pxInnerRenderSetFontDefaultName_proc)(int nIndexRender, const char* pFontName);
	typedef const char* (*pxInnerRenderGetFontDefaultName_proc)(int nIndexRender);
	typedef int (*pxInnerRenderAddFontByBuffer_proc)(int nIndexRender, const char* pFontName, const char* pData, size_t nSize);
	typedef int (*pxInnerRenderAddFontByPath_proc)(int nIndexRender, const char* pFontName, const char* pszFontPath, const bool bAsset);

	typedef pixui::PxViewHandle(*pxsCreate_proc)(pixui::IHostWindow* pHostWindow, bool bWait);
	typedef void (*pxsDoBuffer_proc)(pixui::PxViewHandle vm, const void* buffer, size_t len, const char* name);
	typedef void (*pxsDoFile_proc)(pixui::PxViewHandle vm, const char* url);
	typedef void (*pxsDestroy_proc)(pixui::PxViewHandle vm, bool wait);
	typedef const char* (*pxsSendMessage_proc)(pixui::PxViewHandle vm, const char* msg, int waitMS);
	typedef void (*pxsFreeMessage_proc)(const char* msg);

	typedef void (*pxInitAndroid_proc)(pixui::uint_ptr jMainActivity, pixui::uint_ptr jAssetManager, pixui::uint_ptr jVm);

#define REG_PX_DY_FUN(_name) _name##_proc _name##_ex = nullptr;

	REG_PX_DY_FUN(pxVersion);
	REG_PX_DY_FUN(pxExternalAgent);
	REG_PX_DY_FUN(pxStartup);
	REG_PX_DY_FUN(pxSetCachePath);
	REG_PX_DY_FUN(pxDebugPauseResume);
	REG_PX_DY_FUN(pxCatchDebugTrace);
	REG_PX_DY_FUN(pxTimeTick);
	REG_PX_DY_FUN(pxEnterBackground);
	REG_PX_DY_FUN(pxEnterForeground);
	REG_PX_DY_FUN(pxShutdown);

	REG_PX_DY_FUN(pxViewCreate);
	REG_PX_DY_FUN(pxViewInit);
	REG_PX_DY_FUN(pxViewGetContext);
	REG_PX_DY_FUN(pxViewLoadPageFromData);
	REG_PX_DY_FUN(pxViewLoadPageFromUrl);
	REG_PX_DY_FUN(pxViewHitTest);
	REG_PX_DY_FUN(pxViewMouseEvent);
	REG_PX_DY_FUN(pxViewTouchEvent);
	REG_PX_DY_FUN(pxViewKeyEvent);
	REG_PX_DY_FUN(pxViewKeyboardInput);
	REG_PX_DY_FUN(pxViewWinSizeUpdate);
	REG_PX_DY_FUN(pxViewScreenSizeUpdate);
	REG_PX_DY_FUN(pxViewResetRenderScale);
	REG_PX_DY_FUN(pxViewTick);
	REG_PX_DY_FUN(pxViewPaint);
	REG_PX_DY_FUN(pxViewRenderFrame);
	REG_PX_DY_FUN(pxViewRenderReset);
	REG_PX_DY_FUN(pxViewPostMessage);
	REG_PX_DY_FUN(pxViewGetScriptVM);
	REG_PX_DY_FUN(pxViewClose);
	REG_PX_DY_FUN(pxViewDestroy);

	REG_PX_DY_FUN(pxSetEngineOpenPageDelegate);
	REG_PX_DY_FUN(pxExecuteEngineOpenPageDelegate);
	REG_PX_DY_FUN(pxSetEngineClosePageDelegate);
	REG_PX_DY_FUN(pxExecuteEngineClosePageDelegate);
	REG_PX_DY_FUN(pxSetEnginePostMessageDelegate);
	REG_PX_DY_FUN(pxExecuteEnginePostMessageDelegate);
	REG_PX_DY_FUN(pxSetNativePostMessageDelegate);
	REG_PX_DY_FUN(pxExecuteNativePostMessageDelegate);
	REG_PX_DY_FUN(pxLoadAppletConfig);

	REG_PX_DY_FUN(pxInnerRenderSetSystemFontParam);
	REG_PX_DY_FUN(pxInnerRenderCount);
	REG_PX_DY_FUN(pxInnerRenderName);
	REG_PX_DY_FUN(pxInnerRenderSetFontDefaultName);
	REG_PX_DY_FUN(pxInnerRenderGetFontDefaultName);
	REG_PX_DY_FUN(pxInnerRenderAddFontByBuffer);
	REG_PX_DY_FUN(pxInnerRenderAddFontByPath);

	REG_PX_DY_FUN(pxsCreate);
	REG_PX_DY_FUN(pxsDestroy);
	REG_PX_DY_FUN(pxsDoFile);
	REG_PX_DY_FUN(pxsDoBuffer);
	REG_PX_DY_FUN(pxsSendMessage);
	REG_PX_DY_FUN(pxsFreeMessage);

	REG_PX_DY_FUN(pxInitAndroid);

	bool loadPxLibFun()
	{
		bool bRet = true;
		if (gHMainPluginLib)
		{
#define LOAD_DY_FUN(_name)                                                                            \
	{                                                                                                 \
		_name##_ex = (_name##_proc) DllExport(gHMainPluginLib, #_name);                               \
		if (_name##_ex == nullptr)                                                                    \
		{                                                                                             \
			PxLog_Error("dll:%s load fun:%s error", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME), #_name); \
			bRet = false;                                                                             \
		}                                                                                             \
	}

#define LOAD_DY_FUN_TRY(_name)                                                                        \
	{                                                                                                 \
		_name##_ex = (_name##_proc) DllExport(gHMainPluginLib, #_name);                               \
		if (_name##_ex == nullptr)                                                                    \
		{                                                                                             \
			PxLog_Warning("dll:%s load fun:%s error", fmtAndroidLibPath(DF_PX_PLUGIN_LIB_NAME), #_name); \
		}                                                                                             \
	}

			LOAD_DY_FUN(pxVersion);
			LOAD_DY_FUN(pxExternalAgent);
			LOAD_DY_FUN(pxStartup);
			LOAD_DY_FUN(pxSetCachePath);
			LOAD_DY_FUN(pxDebugPauseResume);
			LOAD_DY_FUN(pxCatchDebugTrace);
			//LOAD_DY_FUN(pxTimeTick);  //removed
			LOAD_DY_FUN(pxEnterBackground);
			LOAD_DY_FUN(pxEnterForeground);
			LOAD_DY_FUN(pxShutdown);
			LOAD_DY_FUN(pxViewCreate);
			LOAD_DY_FUN(pxViewInit);
			LOAD_DY_FUN(pxViewGetContext);
			LOAD_DY_FUN(pxViewLoadPageFromData);
			LOAD_DY_FUN(pxViewLoadPageFromUrl);
			LOAD_DY_FUN(pxViewHitTest);
			LOAD_DY_FUN(pxViewMouseEvent);
			LOAD_DY_FUN(pxViewTouchEvent);
			LOAD_DY_FUN(pxViewKeyEvent);
			LOAD_DY_FUN(pxViewKeyboardInput);
			LOAD_DY_FUN(pxViewWinSizeUpdate);
			LOAD_DY_FUN(pxViewScreenSizeUpdate);
			LOAD_DY_FUN(pxViewResetRenderScale);
			LOAD_DY_FUN(pxViewTick);
			LOAD_DY_FUN(pxViewPaint);

			LOAD_DY_FUN_TRY(pxViewRenderFrame);
			LOAD_DY_FUN_TRY(pxViewRenderReset);

			LOAD_DY_FUN(pxViewPostMessage);
			LOAD_DY_FUN(pxViewGetScriptVM);
			LOAD_DY_FUN(pxViewClose);
			LOAD_DY_FUN(pxViewDestroy);

			LOAD_DY_FUN(pxSetEngineOpenPageDelegate);
			LOAD_DY_FUN(pxExecuteEngineOpenPageDelegate);
			LOAD_DY_FUN(pxSetEngineClosePageDelegate);
			LOAD_DY_FUN(pxExecuteEngineClosePageDelegate);
			LOAD_DY_FUN(pxSetEnginePostMessageDelegate);
			LOAD_DY_FUN(pxExecuteEnginePostMessageDelegate);
			LOAD_DY_FUN(pxSetNativePostMessageDelegate);
			LOAD_DY_FUN(pxExecuteNativePostMessageDelegate);
			LOAD_DY_FUN(pxLoadAppletConfig);

			LOAD_DY_FUN(pxInnerRenderSetSystemFontParam);
			LOAD_DY_FUN(pxInnerRenderCount);
			LOAD_DY_FUN(pxInnerRenderName);
			LOAD_DY_FUN(pxInnerRenderSetFontDefaultName);
			LOAD_DY_FUN(pxInnerRenderGetFontDefaultName);
			LOAD_DY_FUN(pxInnerRenderAddFontByBuffer);
			LOAD_DY_FUN(pxInnerRenderAddFontByPath);

			LOAD_DY_FUN(pxsCreate);
			LOAD_DY_FUN(pxsDestroy);
			LOAD_DY_FUN(pxsDoFile);
			LOAD_DY_FUN(pxsDoBuffer);
			LOAD_DY_FUN(pxsSendMessage);
			LOAD_DY_FUN(pxsFreeMessage);

			LOAD_DY_FUN(pxInitAndroid);
		}
		return bRet;
	}

	bool unloadPxLibFun()
	{
#define DY_FUN_NULL(_name) _name##_ex = nullptr;

		DY_FUN_NULL(pxVersion);
		DY_FUN_NULL(pxExternalAgent);
		DY_FUN_NULL(pxStartup);
		DY_FUN_NULL(pxSetCachePath);
		DY_FUN_NULL(pxDebugPauseResume);
		DY_FUN_NULL(pxCatchDebugTrace);
		DY_FUN_NULL(pxTimeTick);
		DY_FUN_NULL(pxEnterBackground);
		DY_FUN_NULL(pxEnterForeground);
		DY_FUN_NULL(pxShutdown);
		DY_FUN_NULL(pxViewCreate);
		DY_FUN_NULL(pxViewInit);
		DY_FUN_NULL(pxViewGetContext);
		DY_FUN_NULL(pxViewLoadPageFromData);
		DY_FUN_NULL(pxViewLoadPageFromUrl);
		DY_FUN_NULL(pxViewHitTest);
		DY_FUN_NULL(pxViewMouseEvent);
		DY_FUN_NULL(pxViewTouchEvent);
		DY_FUN_NULL(pxViewKeyEvent);
		DY_FUN_NULL(pxViewKeyboardInput);
		DY_FUN_NULL(pxViewWinSizeUpdate);
		DY_FUN_NULL(pxViewResetRenderScale);
		DY_FUN_NULL(pxViewScreenSizeUpdate);
		DY_FUN_NULL(pxViewTick);
		DY_FUN_NULL(pxViewPaint);
		DY_FUN_NULL(pxViewRenderFrame);
		DY_FUN_NULL(pxViewRenderReset);
		DY_FUN_NULL(pxViewPostMessage);
		DY_FUN_NULL(pxViewGetScriptVM);
		DY_FUN_NULL(pxViewClose);
		DY_FUN_NULL(pxViewDestroy);

		DY_FUN_NULL(pxSetEngineOpenPageDelegate);
		DY_FUN_NULL(pxExecuteEngineOpenPageDelegate);
		DY_FUN_NULL(pxSetEngineClosePageDelegate);
		DY_FUN_NULL(pxExecuteEngineClosePageDelegate);
		DY_FUN_NULL(pxSetEnginePostMessageDelegate);
		DY_FUN_NULL(pxExecuteEnginePostMessageDelegate);
		DY_FUN_NULL(pxSetNativePostMessageDelegate);
		DY_FUN_NULL(pxExecuteNativePostMessageDelegate);
		DY_FUN_NULL(pxLoadAppletConfig);

		DY_FUN_NULL(pxInnerRenderSetSystemFontParam);
		DY_FUN_NULL(pxInnerRenderCount);
		DY_FUN_NULL(pxInnerRenderName);
		DY_FUN_NULL(pxInnerRenderSetFontDefaultName);
		DY_FUN_NULL(pxInnerRenderGetFontDefaultName);
		DY_FUN_NULL(pxInnerRenderAddFontByBuffer);
		DY_FUN_NULL(pxInnerRenderAddFontByPath);

		DY_FUN_NULL(pxsCreate);
		DY_FUN_NULL(pxsDestroy);
		DY_FUN_NULL(pxsDoFile);
		DY_FUN_NULL(pxsDoBuffer);
		DY_FUN_NULL(pxsSendMessage);
		DY_FUN_NULL(pxsFreeMessage);

		DY_FUN_NULL(pxInitAndroid);

		return true;
	}

#define PX_LIB_FUN(funName_, ...)									\
	if (funName_##_ex != nullptr) { funName_##_ex(__VA_ARGS__); }	\
	else															\
	{																\
		PxLog_Log("%s null", #funName_);							\
	}

#define PX_LIB_FUN_RET(funName_, ...)										\
	if (funName_##_ex != nullptr) { return funName_##_ex(__VA_ARGS__); }	\
	else																	\
	{																		\
		PxLog_Log("%s null", #funName_);									\
	}

	const char* pxVersion()
	{
		PX_LIB_FUN_RET(pxVersion);
		return "";
	}

	const char* pxExternalAgent()
	{
		PX_LIB_FUN_RET(pxExternalAgent);
		return "";
	}

	bool pxStartup(px_plugin::IPluginImp* pPluginImp, const char* pszWritePath, const char* externalAgent)
	{
		PX_LIB_FUN_RET(pxStartup, pPluginImp, pszWritePath, externalAgent);
		return false;
	}

	void pxSetCachePath(const char* pszCachePath)
	{
		PX_LIB_FUN(pxSetCachePath, pszCachePath);
	}

	void pxDebugPauseResume(const bool bPause)
	{
		PX_LIB_FUN(pxDebugPauseResume, bPause);
	}

	void pxCatchDebugTrace(bool bCatch)
	{
		PX_LIB_FUN(pxCatchDebugTrace, bCatch);
	}

	void pxTimeTick(float fDuration)
	{
		PX_LIB_FUN(pxTimeTick, fDuration);
	}

	void pxEnterBackground()
	{
		PX_LIB_FUN(pxEnterBackground);
	}

	void pxEnterForeground()
	{
		PX_LIB_FUN(pxEnterForeground);
	}

	bool pxShutdown()
	{
		PX_LIB_FUN_RET(pxShutdown);
		return false;
	}

	pixui::PxViewHandle pxViewCreate(uint32_t id)
	{
		PX_LIB_FUN_RET(pxViewCreate, id);
		return 0;
	}

	void pxViewInit(pixui::PxViewHandle hView, pixui::IHostWindow* pIWinEvent, pixui::IHostDraw* pIWinDraw, const int nWidth, const int nHeight, const pixui::PxViewDeviceParam* pDeviceParam)
	{
		PX_LIB_FUN(pxViewInit, hView, pIWinEvent, pIWinDraw, nWidth, nHeight, pDeviceParam);
	}

	void* pxViewGetContext(pixui::PxViewHandle hView)
	{
		PX_LIB_FUN_RET(pxViewGetContext, hView);
		return nullptr;
	}

	int pxViewLoadPageFromData(pixui::PxViewHandle hView, const unsigned char* pData, const unsigned int unDataSize, const char* pszBasePath)
	{
		PX_LIB_FUN_RET(pxViewLoadPageFromData, hView, pData, unDataSize, pszBasePath);
		return 0;
	}

	int pxViewLoadPageFromUrl(pixui::PxViewHandle hView, const char* pszPageUrl)
	{
		PX_LIB_FUN_RET(pxViewLoadPageFromUrl, hView, pszPageUrl);
		return 0;
	}

	bool pxViewHitTest(pixui::PxViewHandle hView, const int nXpos, const int nYpos)
	{
		PX_LIB_FUN_RET(pxViewHitTest, hView, nXpos, nYpos);
		return false;
	}

	bool pxViewMouseEvent(pixui::PxViewHandle hView, const int nXpos, const int nYpos, const int nZpos, const pixui::MouseButton emBtnEvent, const bool bDown)
	{
		PX_LIB_FUN_RET(pxViewMouseEvent, hView, nXpos, nYpos, nZpos, emBtnEvent, bDown);
		return false;
	}

	bool pxViewTouchEvent(pixui::PxViewHandle hView, const int nXpos, const int nYpos, const pixui::int32 nTouchPoint, const pixui::ETouchPhase emTouchPhase)
	{
		PX_LIB_FUN_RET(pxViewTouchEvent, hView, nXpos, nYpos, nTouchPoint, emTouchPhase);
		return false;
	}

	bool pxViewKeyEvent(pixui::PxViewHandle hView, const pixui::EKeyCode emKey, const unsigned char ucModifiers, const bool bDown)
	{
		PX_LIB_FUN_RET(pxViewKeyEvent, hView, emKey, ucModifiers, bDown);
		return false;
	}

	int pxViewKeyboardInput(pixui::PxViewHandle hView, const char* szInput, const bool bEndInput, const bool bLostFocus, const bool bReplace)
	{
		PX_LIB_FUN_RET(pxViewKeyboardInput, hView, szInput, bEndInput, bLostFocus, bReplace);
		return 0;
	}

	int pxViewWinSizeUpdate(pixui::PxViewHandle hView, const int nNewWidth, const int nNewHeight)
	{
		PX_LIB_FUN_RET(pxViewWinSizeUpdate, hView, nNewWidth, nNewHeight);
		return 0;
	}

	void pxViewResetRenderScale(pixui::PxViewHandle hView, float scale)
	{
		PX_LIB_FUN(pxViewResetRenderScale, hView, scale);
	}

	void pxViewScreenSizeUpdate(pixui::PxViewHandle hView, int screenWidth, int screenHeight)
	{
		PX_LIB_FUN(pxViewScreenSizeUpdate, hView, screenWidth, screenHeight);
	}

	bool pxViewTick(pixui::PxViewHandle hView)
	{
		PX_LIB_FUN_RET(pxViewTick, hView);
		return false;
	}

	int pxViewPaint(pixui::PxViewHandle hView, int nParam)
	{
		PX_LIB_FUN_RET(pxViewPaint, hView, nParam);
		return 0;
	}

	int pxViewRenderFrame(pixui::PxViewHandle hView)
	{
		PX_LIB_FUN_RET(pxViewRenderFrame, hView);
		return 0;
	}

	int pxViewRenderReset(pixui::PxViewHandle hView, int nStatus, void* pParams)
	{
		PX_LIB_FUN_RET(pxViewRenderReset, hView, nStatus, pParams);
		return 0;
	}

	int pxViewPostMessage(pixui::PxViewHandle hView, const char* pszMessage, const pixui::PxViewHandle h_src_view)
	{
		PX_LIB_FUN_RET(pxViewPostMessage, hView, pszMessage, h_src_view);
		return 0;
	}

	pixui::PxViewHandle pxViewGetScriptVM(pixui::PxViewHandle hView)
	{
		PX_LIB_FUN_RET(pxViewGetScriptVM, hView);
		return 0;
	}

	int pxViewClose(pixui::PxViewHandle hView)
	{
		PX_LIB_FUN_RET(pxViewClose, hView);
		return 0;
	}

	int pxViewDestroy(pixui::PxViewHandle hView)
	{
		PX_LIB_FUN_RET(pxViewDestroy, hView);
		return 0;
	}

	void pxSetEngineOpenPageDelegate(pixui::EngineOpenPageDelegate callback)
	{
		PX_LIB_FUN(pxSetEngineOpenPageDelegate, callback);
	}

	int pxExecuteEngineOpenPageDelegate(int winId, pixui::LoadPageArg* loadPageArg)
	{
		PX_LIB_FUN_RET(pxExecuteEngineOpenPageDelegate, winId, loadPageArg);
		return 0;
	}

	void pxSetEngineClosePageDelegate(pixui::EngineClosePageDelegate callback)
	{
		PX_LIB_FUN(pxSetEngineClosePageDelegate, callback);
	}

	bool pxExecuteEngineClosePageDelegate(int winId)
	{
		PX_LIB_FUN_RET(pxExecuteEngineClosePageDelegate, winId);
		return false;
	}

	void pxSetEnginePostMessageDelegate(pixui::EnginePostMessageDelegate callback)
	{
		PX_LIB_FUN(pxSetEnginePostMessageDelegate, callback);
	}

	bool pxExecuteEnginePostMessageDelegate(int winId, const char* message)
	{
		PX_LIB_FUN_RET(pxExecuteEnginePostMessageDelegate, winId, message);
		return false;
	}

	void pxSetNativePostMessageDelegate(pixui::NativePostMessageDelegate callback)
	{
		PX_LIB_FUN(pxSetNativePostMessageDelegate, callback);
	}

	void pxExecuteNativePostMessageDelegate(int winId, int type, int code, const char* message)
	{
		PX_LIB_FUN(pxExecuteNativePostMessageDelegate, winId, type, code, message);
	}

	const char* pxLoadAppletConfig(const char* pszAppletAssetsPath, const char* pszAppletName)
	{
		PX_LIB_FUN_RET(pxLoadAppletConfig, pszAppletAssetsPath, pszAppletName);
		return "";
	}

	void pxInnerRenderSetSystemFontParam(bool beLoadSystemFonts, bool beAsyncLoadSystemFonts)
	{
		PX_LIB_FUN(pxInnerRenderSetSystemFontParam, beLoadSystemFonts, beAsyncLoadSystemFonts);
	}

	int pxInnerRenderCount()
	{
		PX_LIB_FUN_RET(pxInnerRenderCount);
		return 0;
	}

	const char* pxInnerRenderName(int nIndex)
	{
		PX_LIB_FUN_RET(pxInnerRenderName, nIndex);
		return "";
	}

	int pxInnerRenderSetFontDefaultName(int nIndexRende, const char* pFontName)
	{
		PX_LIB_FUN_RET(pxInnerRenderSetFontDefaultName, nIndexRende, pFontName);
		return 0;
	}

	const char* pxInnerRenderGetFontDefaultName(int nIndexRende)
	{
		PX_LIB_FUN_RET(pxInnerRenderGetFontDefaultName, nIndexRende);
		return "";
	}

	int pxInnerRenderAddFontByBuffer(int nIndexRender, const char* pFontName, const char* pData, size_t nSize)
	{
		PX_LIB_FUN_RET(pxInnerRenderAddFontByBuffer, nIndexRender, pFontName, pData, nSize);
		return 0;
	}

	int pxInnerRenderAddFontByPath(int nIndexRender, const char* pFontName, const char* pszFontPath, const bool bAsset)
	{
		PX_LIB_FUN_RET(pxInnerRenderAddFontByPath, nIndexRender, pFontName, pszFontPath, bAsset);
		return 0;
	}

	pixui::PxViewHandle pxsCreate(pixui::IHostWindow* pHostWindow, bool bWait)
	{
		PX_LIB_FUN_RET(pxsCreate, pHostWindow, bWait);
		return  0;
	}

	void pxsDestroy(pixui::PxViewHandle vm, bool wait)
	{
		PX_LIB_FUN(pxsDestroy, vm, wait);
	}

	void pxsDoFile(pixui::PxViewHandle vm, const char* url)
	{
		PX_LIB_FUN(pxsDoFile, vm, url);
	}

	void pxsDoBuffer(pixui::PxViewHandle vm, const void* buffer, size_t len, const char* name)
	{
		PX_LIB_FUN(pxsDoBuffer, vm, buffer, len, name);
	}

	const char* pxsSendMessage(pixui::PxViewHandle vm, const char* msg, int waitMS)
	{
		PX_LIB_FUN_RET(pxsSendMessage, vm, msg, waitMS);
		return "";
	}

	void pxsFreeMessage(const char* msg)
	{
		PX_LIB_FUN(pxsFreeMessage, msg);
	}

	void pxInitAndroid(pixui::uint_ptr jMainActivity, pixui::uint_ptr jAssetManager, pixui::uint_ptr jVm)
	{
		PX_LIB_FUN(pxInitAndroid, jMainActivity, jAssetManager, jVm);
	}

#endif //defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)


    bool PxDyLibLoad()
    {
        bool b_Ret = false;

        PxLog_Log("DyLibLoad start");

        if (loadPxPluginLib())
        {
#if defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
            b_Ret = loadPxLibFun();
#else
            b_Ret = true;
#endif //defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)

#if defined(PLATFORM_ANDROID) && PLATFORM_ANDROID
			if (b_Ret)
			{
				pxInitAndroid((pixui::uint_ptr)AndroidJavaEnv::GetGameActivityThis(), (pixui::uint_ptr)AndroidJNI_GetJavaAssetManager(), (pixui::uint_ptr)GJavaVM);
			}
#endif
        }

        PxLog_Log("DyLibLoad end %s", (b_Ret ? "success" : "failed"));

        return b_Ret;
    }


    bool PxDyLibUnLoad()
    {
        bool b_Ret = false;

        PxLog_Log("DyLibUnLoad start");

        if (unLoadPxPluginLib())
        {
#if defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
            b_Ret = unloadPxLibFun();
#else
            b_Ret = true;
#endif //defined(DF_DY_LOAD_PX) && (DF_DY_LOAD_PX)
        }

        PxLog_Log("DyLibUnLoad end %s", (b_Ret ? "success" : "failed"));

        return b_Ret;
    }
}