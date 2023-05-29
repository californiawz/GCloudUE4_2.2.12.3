/**************************************************

**** @file:     hf_loadlib.h

**** @brief:

**** @author:   tianzelei

**** @date:     2020/05/28

**** @group:    PixUI

**** @copyright: Copyright 2020 PixUI. All Rights Reserved.

***************************************************/

#pragma once

//template header file version
#define DF_PX_LIB_TEMPLATE_VERSION  "0.1.6"

#define PXLIB_PLATFORM_WINDOWS	0 //Windows
#define PXLIB_PLATFORM_ANDROID	0 //Android
#define PXLIB_PLATFORM_LINUX	0 //Linux
#define PXLIB_PLATFORM_IOS		0 //iOS
#define PXLIB_PLATFORM_MAC		0 //Mac
#define PXLIB_PLATFORM_UNKNOWN	0

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#undef  PXLIB_PLATFORM_WINDOWS
#define PXLIB_PLATFORM_WINDOWS	1 //Windows
#elif defined(ANDROID) || defined(_ANDROID_)
#undef  PXLIB_PLATFORM_ANDROID
#define PXLIB_PLATFORM_ANDROID	1 //Android
#elif defined(__linux__)
#undef  PXLIB_PLATFORM_LINUX
#define PXLIB_PLATFORM_LINUX	1 //Linux
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
	#undef  PXLIB_PLATFORM_IOS
	#define PXLIB_PLATFORM_IOS	1 //iOS
#elif TARGET_OS_MAC
	#undef  PXLIB_PLATFORM_MAC
	#define PXLIB_PLATFORM_MAC	1 //Mac
#endif //TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#else
#undef  PXLIB_PLATFORM_UNKNOWN
#define PXLIB_PLATFORM_UNKNOWN	1 //unknown
#endif //defined(WIN32)


#if PXLIB_PLATFORM_IOS
//ios use shared load process
#if !defined(PX_LIB_STATIC_LOADER)
#import <Foundation/Foundation.h>
#endif //!defined(PX_LIB_STATIC_LOADER)

#endif //PXLIB_PLATFORM_IOS

//  *.dll  *.so  *.dylib  *.framework

//define for export
#if PXLIB_PLATFORM_WINDOWS
#define PX_LIB_API __declspec(dllexport)
#else
#if __GNUC__ >= 4
#define PX_LIB_API __attribute__((visibility("default")))
#else
#define PX_LIB_API
#endif //__GNUC__ >= 4
#endif //PXLIB_PLATFORM_WINDOWS


#ifdef __cplusplus
#define PXLIB_API extern "C" PX_LIB_API
#else
#define PXLIB_API PX_LIB_API
#endif	//__cplusplus

#include "hf_loadlib.h"

#include <iostream>



#if defined(PX_LIB_STATIC_LOADER)
/*
	pixui_register_lib just for .lib *.a static library, dynamic library do not call this function!!!!

	@ PxLibInfor:

	@ return: true register success
*/
#if PXLIB_PLATFORM_WINDOWS
extern "C" __declspec(dllimport) bool pixui_register_static_lib(const char* psz_name, pixui::PxLibInfor* p_lib_infor);
#else
PXLIB_API bool pixui_register_static_lib(const char* psz_name, pixui::PxLibInfor* p_lib_infor);
#endif //PXLIB_PLATFORM_WINDOWS

#endif //defined(PX_LIB_STATIC_LOADER)


namespace pixui
{
	//delegate type
	struct PxLibCDelegate {
		PxLibCDelegate()
		{
			un_context_ = 0;
			pfun_delegate_ = nullptr;
		}
		PxLibCDelegate(unsigned int un_context, PFun_PxLib_Delegate pfun)
		{
			un_context_ = un_context;
			pfun_delegate_ = pfun;
		}
		unsigned int un_context_;
		PFun_PxLib_Delegate pfun_delegate_;
	};

	//pixui lib template
	template<typename T>
	static void PxLibPopVal(T& out_val, PxLibParams& val, int nIndex)
	{
		val.Get(nIndex, out_val);
	}

	struct PxLibArgOperator
	{
		template<typename T>
		static typename std::enable_if<std::is_enum<T>::value, T>::type readArg(PxLibParams& val, int nIndex)
		{
			T out_val = 0;
			PxLibPopVal<T>(out_val, val, nIndex);
			return out_val;
		}

		template<typename T>
		static typename std::enable_if<!std::is_enum<T>::value, T>::type readArg(PxLibParams& val, int nIndex)
		{
			T out_val = 0;
			PxLibPopVal<T>(out_val, val, nIndex);
			return out_val;
		}

		template<typename T>
		static typename std::enable_if<std::is_enum<T>::value, T>::type getArgType(PxLibFunc* p_fun_infor, int nIndex)
		{
			T in_val = 0;
			p_fun_infor->SetParams<T>(nIndex, in_val);
			return in_val;
		}

		template<typename T>
		static typename std::enable_if<!std::is_enum<T>::value, T>::type getArgType(PxLibFunc* p_fun_infor, int nIndex)
		{
			T in_val = 0;
			p_fun_infor->SetParams<T>(nIndex, in_val);
			return in_val;
		}
	};

	template<int...>
	struct PxLibIntList {
	};

	template<typename L, typename R>
	struct PxLibConcat;

	template<int... TL, int... TR>
	struct PxLibConcat<PxLibIntList<TL...>, PxLibIntList<TR...>> {
		typedef PxLibIntList<TL..., TR...> type;
	};

	template<int n>
	struct PxLibMakeIntList_t {
		typedef typename PxLibConcat<typename PxLibMakeIntList_t<n - 1>::type, PxLibIntList<n - 1>>::type type;
	};

	template<>
	struct PxLibMakeIntList_t<0> {
		typedef PxLibIntList<> type;
	};

	template<int n>
	using PxLibMakeIntList = typename PxLibMakeIntList_t<n>::type;


	template<typename T>
	struct PxLibremove_cr {
		typedef T type;
	};

	template<typename T>
	struct PxLibremove_cr<const T &> {
		typedef typename PxLibremove_cr<T>::type type;
	};

	template<typename T>
	struct PxLibremove_cr<T &> {
		typedef typename PxLibremove_cr<T>::type type;
	};

	template<typename T>
	struct PxLibremove_cr<T &&> {
		typedef typename PxLibremove_cr<T>::type type;
	};

	template<typename T, T>
	struct PxLibFunctionBind;

	template<typename... Args, void(*Func)(Args...)>
	struct PxLibFunctionBind<void(*)(Args...), Func>
	{
		template<typename T>
		struct PxLibFunctor;

		template<int... index>
		struct PxLibFunctor<PxLibIntList<index...>>
		{
			static void CallNative(PxLibParams& val)
			{
				Func(PxLibArgOperator::readArg<typename PxLibremove_cr<Args>::type>(val, index)...);
			}

			static void RegisterFun(PxLibFunc* p_fun_infor)
			{
				p_fun_infor->Push(PxLibArgOperator::getArgType<typename PxLibremove_cr<Args>::type>(p_fun_infor, index)...);
			}
		};

		static PxLibValue Call(PxLibParams& val)
		{
			using I = PxLibMakeIntList<sizeof...(Args)>;
			PxLibFunctor<I>::CallNative(val);
			return PxLibValue();
		}

		static void RegisterFun(PxLibFunc* p_fun_infor)
		{
			using I = PxLibMakeIntList<sizeof...(Args)>;
			p_fun_infor->ResetParamCount(sizeof...(Args));
			PxLibFunctor<I>::RegisterFun(p_fun_infor);
		}
	};

	template<typename R, typename... Args, R(*Func)(Args...)>
	struct PxLibFunctionBind<R(*)(Args...), Func>
	{
		template<typename T>
		struct PxLibFunctor;

		template<int... index>
		struct PxLibFunctor<PxLibIntList<index...>>
		{
			static R CallNative(PxLibParams& val)
			{
				return Func(PxLibArgOperator::readArg<typename PxLibremove_cr<Args>::type>(val, index)...);
			}

			static void RegisterFun(PxLibFunc* p_fun_infor)
			{
				p_fun_infor->Push(PxLibArgOperator::getArgType<typename PxLibremove_cr<Args>::type>(p_fun_infor, index)...);
			}
		};

		static PxLibValue Call(PxLibParams& val)
		{
			using I = PxLibMakeIntList<sizeof...(Args)>;
			R r = PxLibFunctor<I>::CallNative(val);
			return PxLibValue(r);
		}

		static void RegisterFun(PxLibFunc* p_fun_infor)
		{
			using I = PxLibMakeIntList<sizeof...(Args)>;
			p_fun_infor->ResetParamCount(sizeof...(Args));
			PxLibFunctor<I>::RegisterFun(p_fun_infor);
		}
	};

	template<typename T, T>
	struct PxLibFunction;

	template<typename R, typename... Args, R(*Func)(Args...)>
	struct PxLibFunction<R(*)(Args...), Func>
	{
		static R NativeCall(Args &&...args)
		{
			return Func(std::forward<Args>(args)...);
		}

		static R RegisterFun(Args &&...args)
		{
			R out_val = 0;
			return out_val;
		}

		static PxLibValue PxCall(PxLibParams& val)
		{
			using f = PxLibFunctionBind<decltype(&NativeCall), NativeCall>;
			return f::Call(val);
		}

		static void Register(PxLibFunc* p_fun_infor)
		{
			using f = PxLibFunctionBind<decltype(&RegisterFun), RegisterFun>;
			f::RegisterFun(p_fun_infor);
		}
	};

	template<typename... Args, void(*Func)(Args...)>
	struct PxLibFunction<void(*)(Args...), Func>
	{
		static void NativeCall(Args &&...args)
		{
			Func(std::forward<Args>(args)...);
		}


		static void RegisterFun(Args &&...args)
		{
			//Func(std::forward<ARG>(args)...);
		}

		static PxLibValue PxCall(PxLibParams& val)
		{
			using f = PxLibFunctionBind<decltype(&NativeCall), NativeCall>;
			f::Call(val);
			return PxLibValue();
		}

		static void Register(PxLibFunc* p_fun_infor)
		{
			using f = PxLibFunctionBind<decltype(&RegisterFun), RegisterFun>;
			f::RegisterFun(p_fun_infor);
		}
	};

	typedef pixui::PxLibValue PxLibCall(pixui::PxLibParams& val);
	typedef void Register(PxLibFunc* p_fun_infor);

	using PxLibCFunction = PxLibCall*;
	using PxLibCFunctionReg = Register*;

	#define PixLibMakeFunction(M)		PxLibFunction<decltype(M), M>::PxCall
	#define PixLibRegisterFunction(M)	PxLibFunction<decltype(M), M>::Register


	struct PxStr
	{
#define DF_PX_LIB_STR_CPY(dst_ ,src_, len_) dst_ = new char[len_ + 1];	\
		dst_[len_] = 0;													\
		memcpy(dst_, src_, len_);
		PxStr()
		{
			p_buff_ = nullptr;
			l_len_ = 0;
		}
		PxStr(const char* sz_val)
			:PxStr()
		{
			if (sz_val && strlen(sz_val) > 0)
			{
				l_len_ = strlen(sz_val);
				DF_PX_LIB_STR_CPY(p_buff_, sz_val, l_len_);
			}
		}
		PxStr(const char* sz_val, size_t l_len)
			:PxStr()
		{
			if (sz_val && l_len > 0)
			{
				l_len_ = l_len;
				DF_PX_LIB_STR_CPY(p_buff_, sz_val, l_len_);
			}
		}

		PxStr(const PxStr& str_val)
			:PxStr()
		{
			l_len_ = str_val.l_len_;
			if (l_len_ > 0 && str_val.p_buff_)
			{
				DF_PX_LIB_STR_CPY(p_buff_, str_val.p_buff_, l_len_);
			}
		}

		PxStr& operator=(const char* sz_val)
		{
			Free();
			if (sz_val && strlen(sz_val) > 0)
			{
				l_len_ = strlen(sz_val);
				DF_PX_LIB_STR_CPY(p_buff_, sz_val, l_len_);
			}
			return *this;
		}

		PxStr& operator=(const PxStr& str_val)
		{
			Free();
			l_len_ = str_val.l_len_;
			if (l_len_ > 0 && str_val.p_buff_)
			{
				DF_PX_LIB_STR_CPY(p_buff_, str_val.p_buff_, l_len_);
			}
			return *this;
		}
		bool operator==(const char* sz_val)
		{
			if (sz_val && strlen(sz_val) == l_len_)
			{
				if (strcmp(c_str(),sz_val) == 0)
				{
					return true;
				}
			}
			return false;
		}
		bool operator==(const PxStr& str_val)
		{
			if (str_val.l_len_ == l_len_)
			{
				if (strcmp(c_str(), str_val.c_str()) == 0)
				{
					return true;
				}
			}
			return false;
		}
		~PxStr()
		{
			Free();
		}
		const char* c_str() const
		{
			return p_buff_ ? p_buff_ : "";
		}
		size_t Len()
		{
			return l_len_;
		}
		void Free()
		{
			if (p_buff_)
			{
				delete p_buff_;
				p_buff_ = nullptr;
			}
			l_len_ = 0;
		}
	private:
		char * p_buff_;
		size_t l_len_;
	};

	template<typename Key,typename Val>
	struct PxMap
	{
		struct PxMapIter
		{
			PxMapIter(const Key& key, const Val& val)
			{
				first = key;
				second = val;
				next_ = nullptr;
			}
			Key first;
			Val second;
			PxMapIter* next_;
		};

		PxMap()
		{
			head_ = nullptr;
			end_ = nullptr;
			size_ = 0;
		}
		~PxMap()
		{
			PxMapIter* p_curret = head_;
			while (p_curret)
			{
				auto p_delete = p_curret;
				p_curret = p_curret->next_;
				delete p_delete;
			}
			head_ = nullptr;
			end_ = nullptr;
			size_ = 0;
		}

		PxMapIter* insert(const Key& key, const Val& val)
		{
			if (find(key))
			{
				return nullptr;
			}
			if (!head_)
			{
				head_ = new PxMapIter(key, val);
				end_ = head_;
			}
			else
			{
				end_->next_ = new PxMapIter(key, val);
				end_ = end_->next_;
			}
			return end_;
		}
		Val& operator[](const Key& key)
		{
			PxMapIter* p_tem = find(key);
			if (!p_tem)
			{
				Val tmp;
				p_tem = insert(key, tmp);
			}
			return p_tem->second;
		}

		PxMapIter* find(const Key& key)
		{
			PxMapIter* p_curret = head_;
			while (p_curret)
			{
				if (p_curret->first == key)
				{
					break;
				}
				p_curret = p_curret->next_;
			}
			return p_curret;
		}
		int erase(const Key& key)
		{
			PxMapIter* p_curret = head_;
			PxMapIter* p_previous = nullptr;
			while (p_curret)
			{
				if (p_curret->first == key)
				{
					if (p_previous)
					{
						p_previous->next_ = p_curret->next_;
					}
					delete p_curret;
					size_--;
					break;
				}
				p_previous = p_curret;
				p_curret = p_curret->next_;
			}
			return size_;
		}
		int size()
		{
			return size_;
		}
		PxMapIter* end()
		{
			return nullptr;
		}
	private:
		PxMapIter* head_;
		PxMapIter* end_;
		int size_;
	};
}// namespace pixui

#define DF_PX_LIB_REG_FUN( fun_ ) pixui::PxStr str_##fun_ = (#fun_);									\
	map_fun_s.insert(str_##fun_ , pixui::PixLibMakeFunction(&fun_));									\
	auto p_##fun_ = LibInfor()->PushFun( #fun_ );														\
	pixui::PxLibCFunctionReg x2_##fun_ = pixui::PixLibRegisterFunction(&fun_);							\
	x2_##fun_(p_##fun_);

#define DF_PX_LIB_REG_DELEGATE( fun_ ) auto p_##fun_ = LibInfor()->PushDelegate( #fun_ );				\
	pixui::PxLibCFunctionReg p_reg_##fun_ = pixui::PixLibRegisterFunction(&fun_);						\
	p_reg_##fun_( p_##fun_ );


#define DF_PX_LIB_SET_DELEGATE_REG( delegate_) if (str_delegate_name == #delegate_ )					\
	{																									\
		auto iter = map_delegate_s.find(str_delegate_name);												\
		if (iter != map_delegate_s.end())																\
		{																								\
			map_delegate_s[str_delegate_name] = pixui::PxLibCDelegate(un_context, FunDelegate);			\
		}																								\
		else																							\
		{																								\
			map_delegate_s.insert(str_delegate_name, pixui::PxLibCDelegate(un_context, FunDelegate));	\
		}																								\
	}

#define DF_PX_LIB_SET_DELEGATE( delegate_, fun_, ...) if (str_delegate_name == #delegate_ )				\
	{																									\
		auto iter = map_delegate_s.find(str_delegate_name);												\
		if (iter != map_delegate_s.end())																\
		{																								\
			map_delegate_s[str_delegate_name] = pixui::PxLibCDelegate(un_context, FunDelegate);			\
		}																								\
		else																							\
		{																								\
			map_delegate_s.insert(str_delegate_name, pixui::PxLibCDelegate(un_context, FunDelegate));	\
		}																								\
		fun_( __VA_ARGS__ );																			\
	}

#define DF_PX_LIB_DELEGATE_CALL_RET(ret_type_, fun_, ...) ret_type_ ret = 0;							\
	auto iter = map_delegate_s.find( #fun_ );															\
	if (iter != map_delegate_s.end())																	\
	{																									\
		pixui::PxLibParams in_param;																	\
		in_param.PushArgs( __VA_ARGS__ );																\
		pixui::PxLibValue* ret_val = iter->second.pfun_delegate_(iter->second.un_context_, in_param);	\
		static pixui::PxLibValue ret_tmp;																\
		ret_tmp = ret;																					\
		if (ret_val)																					\
		{																								\
			pixui::PxLibValue::TryToValue(ret_tmp, *ret_val);											\
			ret_tmp.Get(ret);																			\
		}																								\
	}																									\
	return ret;

#define DF_PX_LIB_DELEGATE_CALL(fun_, ...) auto iter = map_delegate_s.find( #fun_ );					\
	if (iter != map_delegate_s.end())																	\
	{																									\
		pixui::PxLibParams in_param;																	\
		in_param.PushArgs( __VA_ARGS__ );																\
		iter->second.pfun_delegate_(iter->second.un_context_, in_param);								\
	}


#define DF_PX_LIB_VERSION(ver_) static const char* psz_pixui_lib_version_s = #ver_;


#define DF_PX_LIB_START_SUB(lib_name_) namespace lib_name_																\
{																														\
	pixui::PxLibInfor* LibInfor()																						\
	{																													\
		static pixui::PxLibInfor p_LibInfor_s;																			\
		return &p_LibInfor_s;																							\
	}																													\
	static pixui::PxMap<pixui::PxStr, pixui::PxLibCFunction> map_fun_s;													\
	static pixui::PxMap<pixui::PxStr, pixui::PxLibCDelegate> map_delegate_s;											\
	static pixui::PFun_PxLib_Listener s_fun_listener = nullptr;															\
	static unsigned int s_un_context = 0;																				\
	static bool b_register_s = false;																					\
	const char* PxLib_HD_Version();																						\
	const char* PxLib_Template_Version();																				\
	const char* PxLib_Version();																						\
	const char* PxLib_Name(){ return #lib_name_; }																		\
	const char* PxLib_CompileTimer();																					\
	pixui::PxLibInfor* Lib_Register();																					\
	pixui::PxLibValue* Lib_OnCallFun(const char *psz_FunName, pixui::PxLibParams &in_param);							\
	void Lib_OnSetDelegate(const char *psz_FunName, pixui::PFun_PxLib_Delegate FunDelegate, unsigned int un_context);	\
	void Lib_SetListener(pixui::PFun_PxLib_Listener FunListener, unsigned int un_context);								\
	void Lib_UnRegister();																								\
	void Lib_OnCtxGC(pixui::PxLibContextPtr ctx_);																		\
	PXLIB_API int PxLib_start_##lib_name_(){ PxLib_Name();return 0;}														\
	const char* reg(){ return PxLib_Name(); }																			\
	PXLIB_API pixui::PxLibInfor* reg_##lib_name_(){ return Lib_Register();}


#if PXLIB_PLATFORM_IOS && !defined(PX_LIB_STATIC_LOADER)
//ios use obj-c to dynamic load
#define DF_PX_LIB_START(lib_name_)  PXLIB_API pixui::PxLibInfor* reg_##lib_name_();					\
__attribute__((visibility("default")))																\
@interface lib_name_##_fw_class : NSObject															\
@end																								\
@implementation lib_name_##_fw_class																\
+ (void*)getPxLibInfor {																			\
	return reinterpret_cast<void*>(reg_##lib_name_());												\
}																									\
@end																								\
DF_PX_LIB_START_SUB(lib_name_)

#else

#if defined(PX_LIB_STATIC_LOADER)
#define DF_PX_LIB_START(lib_name_) DF_PX_LIB_START_SUB(lib_name_)									\
	struct PxStaticReg																				\
	{																								\
		PxStaticReg()																				\
		{																							\
			pixui_register_static_lib(PxLib_Name(), Lib_Register());								\
		}																							\
	};																								\
	static PxStaticReg static_reg_s;

#else
#define DF_PX_LIB_START(lib_name_) DF_PX_LIB_START_SUB(lib_name_)
#endif //defined(PX_LIB_STATIC_LOADER)

#endif //PXLIB_PLATFORM_IOS && !defined(PX_LIB_STATIC_LOADER)

#define DF_PX_LIB_INIT_START()  const char* PxLib_Template_Version(){						\
		return DF_PX_LIB_TEMPLATE_VERSION;													\
	}																						\
	const char* PxLib_HD_Version(){															\
		return DF_PXLIB_LOADLIB_VERSION;													\
	}																						\
	const char* PxLib_Version(){															\
		return psz_pixui_lib_version_s;														\
	}																						\
	static char sz_timer_s[40] = {0};														\
	static char s_count = 0;																\
	char PxCmpileTimer(char pBuffer[]) {													\
		auto size_date = strlen(__DATE__);													\
		auto size_time = strlen(__TIME__);													\
		memcpy(pBuffer, __DATE__, size_date);												\
		memcpy(pBuffer + size_date, "  ", 2);												\
		memcpy(pBuffer + size_date + 2, __TIME__, size_time);								\
		return 40;																			\
	}																						\
	const char* PxLib_CompileTimer(){														\
		s_count = PxCmpileTimer(sz_timer_s);												\
		return sz_timer_s;																	\
	}																						\
	void Lib_SetListener(pixui::PFun_PxLib_Listener FunListener, unsigned int un_context)	\
	{																						\
		s_fun_listener = FunListener;														\
		s_un_context = un_context;															\
	}																						\
	void PxPluginLibInit(){

#define DF_PX_LIB_INIT_END()	}



#define DF_PX_LIB_REG_STATIC()	struct PxStaticReg										\
	{																					\
		PxStaticReg()																	\
		{																				\
			pixui_register_static_lib(PxLib_Name(), Lib_Register());					\
		}																				\
	};																					\
	static PxStaticReg static_reg_s;

#define DF_PX_LIB_INFOR_REG_START() pixui::PxLibInfor* Lib_Register() {					\
	if(b_register_s)																	\
		return LibInfor();																\
	PxPluginLibInit();																	\
	LibInfor()->Free();

#define DF_PX_LIB_INFOR_REG_END()	LibInfor()->pfun_register_ = Lib_Register;					\
	LibInfor()->pfun_callfun_			= Lib_OnCallFun;										\
	LibInfor()->pfun_setdelegate_		= Lib_OnSetDelegate;									\
	LibInfor()->pfun_setListener_		= Lib_SetListener;										\
	LibInfor()->pfun_un_register_		= Lib_UnRegister;										\
	LibInfor()->pfun_hd_version_		= PxLib_HD_Version;										\
	LibInfor()->pfun_version_			= PxLib_Version;										\
	LibInfor()->pfun_tp_version_		= PxLib_Template_Version;								\
	LibInfor()->pfun_complime_timer_	= PxLib_CompileTimer;									\
	LibInfor()->pfun_lib_name_			= PxLib_Name;											\
	LibInfor()->pfun_onctx_gc_			= Lib_OnCtxGC;											\
	b_register_s = true;																		\
	return LibInfor();}																			\
pixui::PxLibValue* Lib_OnCallFun(const char *psz_FunName, pixui::PxLibParams &in_param)			\
{																								\
	static pixui::PxLibValue ret_value_s;														\
	ret_value_s.Free();																			\
	pixui::PxStr str_fun_name = psz_FunName;													\
	auto iter = map_fun_s.find(str_fun_name);													\
	if (iter != map_fun_s.end())																\
	{																							\
		ret_value_s = iter->second(in_param);													\
	}																							\
	return &ret_value_s;																		\
}



#define DF_PX_LIB_DELEGATE_PROCESS_START() template<typename... ARGS>					\
	void PxLib_DispathEvent(const char* psz_name, ARGS... args)							\
	{																					\
		pixui::PxLibParams in_param;													\
		in_param.PushArgs(args...);														\
		if (s_fun_listener)																\
		{																				\
			s_fun_listener(s_un_context, psz_name, in_param);							\
		}																				\
	}

#define DF_PX_LIB_DISPATCH_EVENT(lib_name ,name_, ...) {								\
		lib_name##::PxLib_DispathEvent(name_,##__VA_ARGS__);							\
	}																					

#define DF_PX_LIB_DISPATCH_DECLARE(_name_space)	namespace _name_space{					\
		template<typename... ARGS>														\
		void PxLib_DispathEvent(const char* psz_name, ARGS... args);					\
		}

#define DF_PX_LIB_DELEGATE_PROCESS_END()





#define DF_PX_LIB_DELEGATE_SET_START() void Lib_OnSetDelegate(const char *psz_FunName, pixui::PFun_PxLib_Delegate FunDelegate, unsigned int un_context)	\
{																																						\
	pixui::PxStr str_delegate_name = psz_FunName;						


#define DF_PX_LIB_DELEGATE_SET_END()	}


#define DF_PX_LIB_FREE_START() void Lib_UnRegister(){

#define DF_PX_LIB_FREE_END()	}


#define DF_PX_LIB_ON_CTX_GC_START( ctx_ ) void Lib_OnCtxGC(pixui::PxLibContextPtr ctx_) {

#define DF_PX_LIB_ON_CTX_GC_END() }


#define DF_PX_LIB_SLOT_START()	void OnContextInit(void* pContext);	\
	void OnContextDone(void* pContext);								\
	void OnContextTick();											\
	pixui::PxLibSlot* LibSlot()										\
	{																\
		static pixui::PxLibSlot p_Lib_slot_s;						\
		return &p_Lib_slot_s;										\
	}																\
	int SlointInit()												\
	{																\
		LibSlot()->pfOnScriptInit = OnContextInit;					\
		LibSlot()->pfOnScriptDone = OnContextDone;					\
		LibSlot()->pfOnTick = OnContextTick;						\
		LibInfor()->slot_ = LibSlot();								\
		return 0;													\
	}																\
	static int nSlot = SlointInit();


#define DF_PX_LIB_STOT_INIT_START( context_ )	void OnContextInit(void* context_){

#define DF_PX_LIB_STOT_INIT_END()	}


#define DF_PX_LIB_STOT_TICK_START()	void OnContextTick(){

#define DF_PX_LIB_STOT_TICK_END()	}


#define DF_PX_LIB_STOT_DONE_START( context_ )	void OnContextDone(void* context_){

#define DF_PX_LIB_STOT_DONE_END()	}



#define DF_PX_LIBG_END()	}
