
#ifndef _ABASE_PAL_H_
#define _ABASE_PAL_H_

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable:4005)
#pragma warning(disable:4668)
#endif

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <sys/types.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
//_GCLOUDCORE_UE defined in GCloudCore.Build.cs
#if defined(_GCLOUDCORE_UE) && (_GCLOUDCORE_UE > 0)
#include "Windows/AllowWindowsPlatformAtomics.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <tchar.h>
#include <winsock2.h>
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#else
#include <tchar.h>
#include <winsock2.h>
#endif

#else
#include <unistd.h>

#include <stdint.h>
#include <inttypes.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#ifdef ANDROID
#include <sys/endian.h>
#endif


//////////////////////////////////////////////////////////////////////////////////////////
//                            System Macros
//////////////////////////////////////////////////////////////////////////////////////////
//iOS: _IOS
//Apple: APPLE
//Android: ANDROID
//WINDOWS: _WIN
//Win32: __WIN32
//Win64: __WIN64
//Linux: LINUX
//Mac: _MAC
#if defined(_WIN32) || defined(_WIN64)
	#define __WINDOWS__
	#define _WIN
	#define WIN
#elif defined(__APPLE__)
	#include "TargetConditionals.h"
	#if TARGET_OS_IOS || TARGET_OS_IPHONE
        #ifndef _IOS
		#define _IOS
        #endif
	#else
		#define _MAC
	#endif
#elif defined(__ANDROID__)
	#define _AOS
#endif


#if defined(_IOS)
#include <endian.h>
#endif
//////////////////////////////////////////////////////////////////////////////////////////
//                             Base Types
//////////////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(_WIN64)
typedef  signed char  int8_t;
typedef  short int16_t;
typedef  int   int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
#endif

typedef int64_t a_longlong;
typedef uint64_t a_ulonglong;
typedef uint16_t a_wchar_t;
typedef uint32_t a_date_t;
typedef uint32_t a_time_t;
typedef uint64_t a_datetime_t;
typedef uint32_t a_ip_t;

typedef bool a_bool;
typedef int8_t a_int8;
typedef uint8_t a_uint8;
typedef uint8_t a_byte;
typedef int16_t a_int16;
typedef uint16_t a_uint16;
typedef int32_t a_int32;
typedef uint32_t a_uint32;
typedef int64_t a_int64;
typedef uint64_t a_uint64;

//#define NULL 0



//////////////////////////////////////////////////////////////////////////////////////////
//                            Endian & net-host covert
//////////////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(_WIN64)
    #if defined (LITTLEENDIAN) && (LITTLEENDIAN > 0)
        #define A_OS_LITTLEENDIAN
        #if defined (A_OS_BIGENDIAN)
            #undef A_OS_BIGENDIAN
        #endif
    #else
        #define A_OS_BIGENDIAN
        #if defined (A_OS_LITTLEENDIAN)
            #undef A_OS_LITTLEENDIAN
        #endif
    #endif
#else
    #if ((defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) || \
        (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN))
		
        #define A_OS_LITTLEENDIAN

        #if defined (A_OS_BIGENDIAN)
            #undef A_OS_BIGENDIAN
        #endif
    #else
        #define A_OS_BIGENDIAN
        #if defined (A_OS_LITTLEENDIAN)
            #undef A_OS_LITTLEENDIAN
        #endif
    #endif
#endif

#if (defined(_WIN32) || defined(_WIN64))
#define A_OS_SWAP64(x) \
( (((x) & (uint64_t)0xff00000000000000) >> 56)  \
 | (((x) & (uint64_t)0x00ff000000000000) >> 40)  \
 | (((x) & (uint64_t)0x0000ff0000000000) >> 24)  \
 | (((x) & (uint64_t)0x000000ff00000000) >>  8)  \
 | (((x) & (uint64_t)0x00000000ff000000) <<  8)  \
 | (((x) & (uint64_t)0x0000000000ff0000) << 24)  \
 | (((x) & (uint64_t)0x000000000000ff00) << 40)  \
 | (((x) & (uint64_t)0x00000000000000ff) << 56))
#else
#define A_OS_SWAP64(x) \
( (((x) & (uint64_t)0xff00000000000000LL) >> 56)  \
 | (((x) & (uint64_t)0x00ff000000000000LL) >> 40)  \
 | (((x) & (uint64_t)0x0000ff0000000000LL) >> 24)  \
 | (((x) & (uint64_t)0x000000ff00000000LL) >>  8)  \
 | (((x) & (uint64_t)0x00000000ff000000LL) <<  8)  \
 | (((x) & (uint64_t)0x0000000000ff0000LL) << 24)  \
 | (((x) & (uint64_t)0x000000000000ff00LL) << 40)  \
 | (((x) & (uint64_t)0x00000000000000ffLL) << 56))
#endif /* #if (defined(_WIN32) || defined(_WIN64)) */

#define A_OS_SWAP32(x) \
( (((x) & 0xff000000) >> 24)  \
 | (((x) & 0x00ff0000) >>  8)  \
 | (((x) & 0x0000ff00) <<  8)  \
 | (((x) & 0x000000ff) << 24))

#define A_OS_SWAP16(x) \
( (((x) & 0xff00) >> 8)  \
 | (((x) & 0x00ff) << 8))

// ntoh & hton
#ifdef A_OS_LITTLEENDIAN
#define a_ntoh64(x)    A_OS_SWAP64(x)
#define a_hton64(x)    A_OS_SWAP64(x)
#define a_ntoh32(x)    A_OS_SWAP32(x)
#define a_hton32(x)    A_OS_SWAP32(x)
#define a_ntoh16(x)    A_OS_SWAP16(x)
#define a_hton16(x)    A_OS_SWAP16(x)
#else
#define a_ntoh64(x)    (x)
#define a_hton64(x)    (x)
#define a_ntoh32(x)    (x)
#define a_hton32(x)    (x)
#define a_ntoh16(x)    (x)
#define a_hton16(x)    (x)
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//                            System api
//////////////////////////////////////////////////////////////////////////////////////////
// snprintf
#if defined(_WIN32) || defined(_WIN64)
#define asnprintf  _snprintf
#define avsnprintf  _vsnprintf
#ifndef snprintf
#define snprintf  _snprintf
#endif//snprintf

#else
#define asnprintf  snprintf
#define avsnprintf  vsnprintf
#endif

// A_INT64_FORMAT
#if (defined(_WIN32) || defined(_WIN64))
#define A_INT64_FORMAT "%I64i"
#define A_UINT64_FORMAT "%I64u"
#define A_UINT64HEX_FORMAT "0x%016I64x"
#else
#if defined(__x86_64__)
#define A_INT64_FORMAT "%ld"
#define A_UINT64_FORMAT "%lu"
#define A_UINT64HEX_FORMAT "0x%016llx"
#else
#define A_INT64_FORMAT "%lld"
#define A_UINT64_FORMAT "%llu"
#define A_UINT64HEX_FORMAT "0x%016llx"
#endif
#endif

// strtol & strtoll
#define astrtol  strtol
#if defined(_WIN32) || defined(_WIN64)
#if _MSC_VER >= 1300
#define astrtoll  _strtoi64
#define astrtoull  _strtoui64
#else
#define astrtoll  _need_at_least_VC7
#define astrtoull  _need_at_least_VC7
#endif

//strcasecmp
#define strcasecmp _stricmp
#else
#define astrtoll  strtoll
#define astrtoull  strtoull
#endif



//////////////////////////////////////////////////////////////////////////////////////////
//                            Others
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef OUT
#define OUT
#endif
#ifndef IN
#define IN
#endif

#define SAFE_DEL(p)         do{if( (p) != NULL ) { delete (p); (p) = NULL; }}while(0)
#define SAFE_DEL_ARRAY(p)   do{if( (p) != NULL ) { delete [](p); (p) = NULL; }}while(0)


#ifdef ANDROID
#ifndef LOG
#define LOG
#include <android/log.h>
#define _TAG     	"ABase"
#define LOG_D(...) __android_log_print(ANDROID_LOG_DEBUG, 	_TAG, __VA_ARGS__);
#define LOG_I(...) __android_log_print(ANDROID_LOG_INFO, 	_TAG, __VA_ARGS__);
#define LOG_W(...) __android_log_print(ANDROID_LOG_WARN,		_TAG, __VA_ARGS__);
#define LOG_E(...) __android_log_print(ANDROID_LOG_ERROR,	_TAG, __VA_ARGS__);
#define LOG_F(...) __android_log_print(ANDROID_LOG_FATAL,	_TAG, __VA_ARGS__);


#define LOGI LOG_I
#define LOGE LOG_E

#endif//#ifndef LOG

#endif//#ifdef ANDROID


#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif


#if defined(_WIN32) || defined(_WIN64)
#define EXPORT_API EXTERN __declspec(dllexport)
#define EXPORT_CLASS __declspec(dllexport)
#else
#ifdef ANDROID
#define EXPORT_API EXTERN __attribute__ ((visibility ("default")))
#define EXPORT_CLASS __attribute__ ((visibility ("default")))
#elif defined(__ORBIS__)
# if defined(APOLLO_BUILDING)
#  define EXPORT_API __declspec(dllexport)
#  define EXPORT_CLASS __declspec(dllexport) 	
# else
#  define EXPORT_API __declspec(dllimport)
#  define EXPORT_CLASS  __declspec(dllimport)
# endif


#else
#define EXPORT_API EXTERN
#define EXPORT_CLASS
#endif
#endif


#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif
