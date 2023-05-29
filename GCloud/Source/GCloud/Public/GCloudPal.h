
#ifndef _GCloud_PAL_H_
#define _GCloud_PAL_H_

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable:4005)
#pragma warning(disable:4668)
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//                            System Macros
//////////////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(_WIN64)
  #define __WINDOWS__
  #define _WIN
  #define WIN
  #if defined(_XBOX_ONE) || defined(_GAMING_XBOX)
    #define _XBOX
  #endif
#elif defined(__APPLE__)
  #include "TargetConditionals.h"
  #if TARGET_OS_IOS || TARGET_OS_IPHONE
    #define _IOS
  #else
    #ifndef _MAC
        #define _MAC
    #endif
  #endif
#elif defined(__ANDROID__)
  #define _AOS
#elif defined(__ORBIS__) || defined(__PROSPERO__)
  #define _PS
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

//_GCLOUD_UE_ defined in GCloud.Build.cs
#if defined(_GCLOUD_UE_) && (_GCLOUD_UE_ > 0)
#include "Windows/AllowWindowsPlatformAtomics.h"
#include "Windows/AllowWindowsPlatformTypes.h"
# include <tchar.h>
# include <winsock2.h>
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#else
# include <tchar.h>
# include <winsock2.h>
#endif

#else
# include <unistd.h>
# include <stdint.h>
# include <inttypes.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
#endif

#ifdef _AOS
#include <sys/endian.h>
#endif

#if defined(_IOS)
#include <endian.h>
#endif

//************************************************
//          Base Types
//************************************************
#if defined(_WIN32) || defined(_WIN64)
typedef signed char  int8_t;
typedef short int16_t;
typedef int   int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
#endif

typedef unsigned char cu_uint8;
typedef signed char cu_int8;
typedef unsigned short cu_uint16;
typedef signed short cu_int16;
typedef unsigned int cu_uint32;
typedef signed int cu_int32;
typedef unsigned long long cu_uint64;
typedef signed long long cu_int64;

#define cu_min(a, b) (((a) < (b)) ? (a) : (b))
#define cu_max(a, b) (((a) > (b)) ? (a) : (b))

//************************************************
//          Endian
//************************************************
#if defined(_WIN32) || defined(_WIN64)
    #if defined (LITTLEENDIAN) && (LITTLEENDIAN > 0)
        #define G_OS_LITTLEENDIAN
        #if defined (G_OS_BIGENDIAN)
            #undef G_OS_BIGENDIAN
        #endif
    #else
        #define G_OS_BIGENDIAN
        #if defined (G_OS_LITTLEENDIAN)
            #undef G_OS_LITTLEENDIAN
        #endif
    #endif
#else
    #if ((defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) || \
        (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN))
        
        #define G_OS_LITTLEENDIAN

        #if defined (G_OS_BIGENDIAN)
            #undef G_OS_BIGENDIAN
        #endif
    #else
        #define G_OS_BIGENDIAN
        #if defined (G_OS_LITTLEENDIAN)
            #undef G_OS_LITTLEENDIAN
        #endif
    #endif
#endif

#if (defined(_WIN32) || defined(_WIN64))
#define G_OS_SWAP64(x) \
( (((x) & (uint64_t)0xff00000000000000) >> 56)  \
 | (((x) & (uint64_t)0x00ff000000000000) >> 40)  \
 | (((x) & (uint64_t)0x0000ff0000000000) >> 24)  \
 | (((x) & (uint64_t)0x000000ff00000000) >>  8)  \
 | (((x) & (uint64_t)0x00000000ff000000) <<  8)  \
 | (((x) & (uint64_t)0x0000000000ff0000) << 24)  \
 | (((x) & (uint64_t)0x000000000000ff00) << 40)  \
 | (((x) & (uint64_t)0x00000000000000ff) << 56))
#else
#define G_OS_SWAP64(x) \
( (((x) & (uint64_t)0xff00000000000000LL) >> 56)  \
 | (((x) & (uint64_t)0x00ff000000000000LL) >> 40)  \
 | (((x) & (uint64_t)0x0000ff0000000000LL) >> 24)  \
 | (((x) & (uint64_t)0x000000ff00000000LL) >>  8)  \
 | (((x) & (uint64_t)0x00000000ff000000LL) <<  8)  \
 | (((x) & (uint64_t)0x0000000000ff0000LL) << 24)  \
 | (((x) & (uint64_t)0x000000000000ff00LL) << 40)  \
 | (((x) & (uint64_t)0x00000000000000ffLL) << 56))
#endif /* #if (defined(_WIN32) || defined(_WIN64)) */

#define G_OS_SWAP32(x) \
( (((x) & 0xff000000) >> 24)  \
 | (((x) & 0x00ff0000) >>  8)  \
 | (((x) & 0x0000ff00) <<  8)  \
 | (((x) & 0x000000ff) << 24))

#define G_OS_SWAP16(x) \
( (((x) & 0xff00) >> 8)  \
 | (((x) & 0x00ff) << 8))

// ntoh & hton
#ifdef G_OS_LITTLEENDIAN
#define g_ntoh64(x)    G_OS_SWAP64(x)
#define g_hton64(x)    G_OS_SWAP64(x)
#define g_ntoh32(x)    G_OS_SWAP32(x)
#define g_hton32(x)    G_OS_SWAP32(x)
#define g_ntoh16(x)    G_OS_SWAP16(x)
#define g_hton16(x)    G_OS_SWAP16(x)
#else
#define g_ntoh64(x)    (x)
#define g_hton64(x)    (x)
#define g_ntoh32(x)    (x)
#define g_hton32(x)    (x)
#define g_ntoh16(x)    (x)
#define g_hton16(x)    (x)
#endif

//************************************************
//          strcasecmp
//************************************************
#if defined(_WIN32) || defined(_WIN64)
# define strcasecmp _stricmp
#endif

//************************************************
//          Int64 Format
//************************************************

#if (defined(_WIN32) || defined(_WIN64))
# define G_INT64_FORMAT     "%I64i"
# define G_UINT64_FORMAT    "%I64u"
# define G_UINT64HEX_FORMAT "0x%016I64x"
#else
# if defined(__x86_64__)
#  define G_INT64_FORMAT    "%ld"
#  define G_UINT64_FORMAT   "%lu"
#  define G_UINT64HEX_FORMAT "0x%016llx"
# else
#  define G_INT64_FORMAT    "%lld"
#  define G_UINT64_FORMAT   "%llu"
#  define G_UINT64HEX_FORMAT "0x%016llx"
# endif
#endif


//************************************************
//          DELETE
//************************************************

#define SAFE_DEL(p)         do{if( (p) != NULL ) { delete (p); (p) = NULL; }}while(0)
#define SAFE_DEL_ARRAY(p)   do{if( (p) != NULL ) { delete [](p); (p) = NULL; }}while(0)

//************************************************
//          EXTERN C
//************************************************

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

//************************************************
//          EXPORT
//************************************************

#if defined(_WIN32) || defined(_WIN64)
# define EXPORT_API EXTERN __declspec(dllexport)
# define EXPORT_CLASS __declspec(dllexport)
#else
# ifdef ANDROID
#  define EXPORT_API EXTERN __attribute__ ((visibility ("default")))
#  define EXPORT_CLASS __attribute__ ((visibility ("default")))
# elif defined(__ORBIS__) || defined(__PROSPERO__)
#  if defined(APOLLO_BUILDING)
#   define EXPORT_API __declspec(dllexport)
#   define EXPORT_CLASS __declspec(dllexport)
#  else
#   define EXPORT_API __declspec(dllimport)
#   define EXPORT_CLASS  __declspec(dllimport)
#  endif
# else
#  define EXPORT_API EXTERN
#  define EXPORT_CLASS
# endif
#endif


#if defined(_WIN32) || defined(_WIN64)
# pragma warning(pop)
#endif

#endif // _GCloud_PAL_H_
