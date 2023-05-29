/* This file is generated by tdr. */
/* No manual modification is permitted. */

/* creation time: Mon Jan 19 10:51:53 2015 */
/* tdr version: 2.7.4, build at 20150113 */

#ifndef ABASE_TDR_PAL_H_
#define ABASE_TDR_PAL_H_

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <sys/types.h>

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

    #if _WIN32_WINNT >= 0x0400
        #include <windows.h>
    #else
        #include <windows.h>
        #include <Ws2tcpip.h>
    #endif

    #pragma comment(lib, "Ws2_32.lib")
#else
    #include <unistd.h>
    //#include <endian.h>

    #include <stdint.h>
    #include <inttypes.h>

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

#ifdef ANDROID
#include <sys/endian.h>
#endif

#ifndef TDR_CUSTOM_C_TYPES
#define TDR_CUSTOM_C_TYPES
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

typedef int64_t tdr_longlong;
typedef uint64_t tdr_ulonglong;
typedef uint16_t tdr_wchar_t;
typedef uint32_t tdr_date_t;
typedef uint32_t tdr_time_t;
typedef uint64_t tdr_datetime_t;
typedef uint32_t tdr_ip_t;

#endif

#if defined(_WIN32) || defined(_WIN64)
    #if defined (LITTLEENDIAN) && (LITTLEENDIAN > 0)
        #define TDR_CPP_OS_LITTLEENDIAN
        #if defined (TDR_CPP_OS_BIGENDIAN)
            #undef TDR_CPP_OS_BIGENDIAN
        #endif
    #else
        #define TDR_CPP_OS_BIGENDIAN
        #if defined (TOS_LITTLEENDIAN)
            #undef TDR_CPP_OS_LITTLEENDIAN
        #endif
    #endif
#else
    #if ((defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) || \
        (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN))

        #define TDR_CPP_OS_LITTLEENDIAN

        #if defined (TDR_CPP_OS_BIGENDIAN)
            #undef TDR_CPP_OS_BIGENDIAN
        #endif
    #else
        #define TDR_CPP_OS_BIGENDIAN
        #if defined (TDR_CPP_OS_LITTLEENDIAN)
            #undef TDR_CPP_OS_LITTLEENDIAN
        #endif
    #endif
#endif

#if (defined(_WIN32) || defined(_WIN64))
    #define TDR_CPP_OS_SWAP64(x) \
        ( (((x) & (uint64_t)0xff00000000000000) >> 56)  \
        | (((x) & (uint64_t)0x00ff000000000000) >> 40)  \
        | (((x) & (uint64_t)0x0000ff0000000000) >> 24)  \
        | (((x) & (uint64_t)0x000000ff00000000) >>  8)  \
        | (((x) & (uint64_t)0x00000000ff000000) <<  8)  \
        | (((x) & (uint64_t)0x0000000000ff0000) << 24)  \
        | (((x) & (uint64_t)0x000000000000ff00) << 40)  \
        | (((x) & (uint64_t)0x00000000000000ff) << 56))
#else
    #define TDR_CPP_OS_SWAP64(x) \
        ( (((x) & (uint64_t)0xff00000000000000LL) >> 56)  \
        | (((x) & (uint64_t)0x00ff000000000000LL) >> 40)  \
        | (((x) & (uint64_t)0x0000ff0000000000LL) >> 24)  \
        | (((x) & (uint64_t)0x000000ff00000000LL) >>  8)  \
        | (((x) & (uint64_t)0x00000000ff000000LL) <<  8)  \
        | (((x) & (uint64_t)0x0000000000ff0000LL) << 24)  \
        | (((x) & (uint64_t)0x000000000000ff00LL) << 40)  \
        | (((x) & (uint64_t)0x00000000000000ffLL) << 56))
#endif /* #if (defined(_WIN32) || defined(_WIN64)) */

#define TDR_CPP_OS_SWAP32(x) \
    ( (((x) & 0xff000000) >> 24)  \
    | (((x) & 0x00ff0000) >>  8)  \
    | (((x) & 0x0000ff00) <<  8)  \
    | (((x) & 0x000000ff) << 24))

#define TDR_CPP_OS_SWAP16(x) \
    ( (((x) & 0xff00) >> 8)  \
    | (((x) & 0x00ff) << 8))

#define TDR_CPP_OS_CAST_SWAP64(dst, src)             \
    do {                                         \
        ((char *)dst)[0] = ((const char *)src)[7];   \
        ((char *)dst)[1] = ((const char *)src)[6];   \
        ((char *)dst)[2] = ((const char *)src)[5];   \
        ((char *)dst)[3] = ((const char *)src)[4];   \
        ((char *)dst)[4] = ((const char *)src)[3];   \
        ((char *)dst)[5] = ((const char *)src)[2];   \
        ((char *)dst)[6] = ((const char *)src)[1];   \
        ((char *)dst)[7] = ((const char *)src)[0];   \
    } while(0)

#define TDR_CPP_OS_CAST_SWAP32(dst, src)          \
    do {                                         \
        ((char *)dst)[0] = ((const char *)src)[3];   \
        ((char *)dst)[1] = ((const char *)src)[2];   \
        ((char *)dst)[2] = ((const char *)src)[1];   \
        ((char *)dst)[3] = ((const char *)src)[0];   \
    } while(0)

#define TDR_CPP_OS_CAST_SWAP16(dst, src)       \
    do {                                         \
        ((char *)dst)[0] = ((const char *)src)[1];   \
        ((char *)dst)[1] = ((const char *)src)[0];   \
    } while(0)

#define TDR_CPP_OS_CAST_64(dst, src)           \
    do {                                             \
        ((char *)dst)[0] = ((const char *)src)[0];   \
        ((char *)dst)[1] = ((const char *)src)[1];   \
        ((char *)dst)[2] = ((const char *)src)[2];   \
        ((char *)dst)[3] = ((const char *)src)[3];   \
        ((char *)dst)[4] = ((const char *)src)[4];   \
        ((char *)dst)[5] = ((const char *)src)[5];   \
        ((char *)dst)[6] = ((const char *)src)[6];   \
        ((char *)dst)[7] = ((const char *)src)[7];   \
    } while(0)

#define TDR_CPP_OS_CAST_32(dst, src)           \
    do {                                             \
        ((char *)dst)[0] = ((const char *)src)[0];   \
        ((char *)dst)[1] = ((const char *)src)[1];   \
        ((char *)dst)[2] = ((const char *)src)[2];   \
        ((char *)dst)[3] = ((const char *)src)[3];   \
    } while(0)

#define TDR_CPP_OS_CAST_16(dst, src)           \
    do {                                             \
        ((char *)dst)[0] = ((const char *)src)[0];   \
        ((char *)dst)[1] = ((const char *)src)[1];   \
    } while(0)

// used for inner only
// base 128 varints
#define TDR_CPP_ENCODE_VARINT(type_casted, src, buf, size, used, ret)\
    do {                                                             \
        size_t i = 0;                                                \
        for (i= 0; i<(size); ++i) {                                  \
            unsigned char ch = (((unsigned char*)&(src))[0] & 0x7f); \
            (src) = ((type_casted)(src) >> 7);                       \
            ((src) != 0) && (ch |= 0x80);                            \
            (buf)[i] = ch;                                           \
            if (0 == (src)) break;                                   \
        }                                                            \
        if ((src) != 0 || 0 == (size)) {                             \
            (ret) = -1;                                              \
            (used) = 0;                                              \
        } else {                                                     \
            (ret) = 0;                                               \
            (used) = i + 1;                                          \
        }                                                            \
    } while (0)

#define TDR_CPP_ENCODE_16_VARINT(src, buf, size, used, ret)  TDR_CPP_ENCODE_VARINT(uint16_t, src, buf, size, used, ret)
#define TDR_CPP_ENCODE_32_VARINT(src, buf, size, used, ret)  TDR_CPP_ENCODE_VARINT(uint32_t, src, buf, size, used, ret)
#define TDR_CPP_ENCODE_64_VARINT(src, buf, size, used, ret)  TDR_CPP_ENCODE_VARINT(uint64_t, src, buf, size, used, ret)

#define TDR_CPP_DECODE_16_VARINT(buf, size, used, dst, ret)          \
    do {                                                             \
        (dst) = 0;                                                   \
        (ret) = 0;                                                   \
        (used) = 0;                                                  \
        size_t i = 0;                                                \
        for (i=0; i<(size); ++i) {                                   \
            if (((buf)[i] & 0x7fu) > (0xffffu >> 7*i)) {             \
                (ret) = -1;                                          \
                break;                                               \
            }                                                        \
            (dst) |= ((uint16_t)((buf)[i] & 0x7f) << (i*7));         \
            if (!((buf)[i] & 0x80)) {                                \
                break;                                               \
            }                                                        \
        }                                                            \
        if (i == size) {                                             \
            (ret) = -1;                                              \
        } else if (0 == (ret) && (size) != 0) {                      \
            (used) = i + 1;                                          \
        }                                                            \
    } while (0)

#define TDR_CPP_DECODE_32_VARINT(buf, size, used, dst, ret)          \
    do {                                                             \
        (dst) = 0;                                                   \
        (ret) = 0;                                                   \
        (used) = 0;                                                  \
        size_t i = 0;                                                \
        for (i=0; i<(size); ++i) {                                   \
            if (((buf)[i] & 0x7fu) > (0xffffffffu >> 7*i)) {         \
                (ret) = -1;                                          \
                break;                                               \
            }                                                        \
            (dst) |= ((uint32_t)((buf)[i] & 0x7f) << (i*7));         \
            if (!((buf)[i] & 0x80)) {                                \
                break;                                               \
            }                                                        \
        }                                                            \
        if (i == size) {                                             \
            (ret) = -1;                                              \
        } else if (0 == (ret) && (size) != 0) {                      \
            (used) = i + 1;                                          \
        }                                                            \
    } while (0)

#define TDR_CPP_DECODE_64_VARINT(buf, size, used, dst, ret)          \
    do {                                                             \
        /*(dst) = 0;*/                                                   \
        (ret) = 0;                                                   \
        (used) = 0;                                                  \
        uint64_t dsttmp = 0;                                       \
        size_t i = 0;                                                \
        for (i=0; i<(size); ++i) {                                   \
            if (((buf)[i] & 0x7fu) > (0xffffffffffffffffull >> 7*i)){\
                (ret) = -1;                                          \
                break;                                               \
            }                                                        \
            (dsttmp) |= ((uint64_t)((buf)[i] & 0x7f) << (i*7));      \
            if (!((buf)[i] & 0x80)) {                                \
                break;                                               \
            }                                                        \
        }                                                            \
        memcpy((char*)&dst, &dsttmp, sizeof(dsttmp));                \
        if (i == size) {                                             \
            (ret) = -1;                                              \
        } else if (0 == (ret) && (size) != 0) {                      \
            (used) = i + 1;                                          \
        }                                                            \
    } while (0)



// signed int zigzag encode&decode
#define TDR_CPP_ZIGZAG_ENCODE_16(a)  (((a) << 1) ^ ((a) >> 15))
#define TDR_CPP_ZIGZAG_ENCODE_32(a)  (((a) << 1) ^ ((a) >> 31))
#define TDR_CPP_ZIGZAG_ENCODE_64(a)  (((a) << 1) ^ ((a) >> 63))

#define TDR_CPP_ZIGZAG_DECODE_16(a)                                                                   \
    do {                                                                                              \
        if (((a) & 0x1))                                                                              \
            (a) = ((((a) ^ 0xffff) >> 1) &~0x8000) | (((a) & 0x1) << 15);                             \
        else                                                                                          \
            (a) = (((a) >> 1) &~0x8000) | (((a) & 0x1) << 15);                                        \
    } while (0)

#define TDR_CPP_ZIGZAG_DECODE_32(a)                                                                   \
    do {                                                                                              \
        if (((a) & 0x1))                                                                              \
            (a) = ((((a) ^ 0xffffffff) >> 1) &~0x80000000) | (((a) & 0x1) << 31);                     \
        else                                                                                          \
            (a) = (((a) >> 1) &~0x80000000) | (((a) & 0x1) << 31);                                    \
    } while (0)

#define TDR_CPP_ZIGZAG_DECODE_64(a)                                                                   \
    do {                                                                                              \
        if (((a) & 0x1))                                                                              \
            (a) = ((((a) ^ 0xffffffffffffffffll) >> 1) &~0x8000000000000000ll) | (((a) & 0x1) << 63); \
        else                                                                                          \
            (a) = (((a) >> 1) &~0x8000000000000000ll) | (((a) & 0x1) << 63);                          \
    } while (0)

#ifdef TDR_CPP_OS_LITTLEENDIAN
    #define tdr_cpp_ntoh64(x)    TDR_CPP_OS_SWAP64(x)
    #define tdr_cpp_hton64(x)    TDR_CPP_OS_SWAP64(x)
    #define tdr_cpp_ntoh32(x)    TDR_CPP_OS_SWAP32(x)
    #define tdr_cpp_hton32(x)    TDR_CPP_OS_SWAP32(x)
    #define tdr_cpp_ntoh16(x)    TDR_CPP_OS_SWAP16(x)
    #define tdr_cpp_hton16(x)    TDR_CPP_OS_SWAP16(x)

    #define tdr_cpp_cast_ntoh64(dst, src)    TDR_CPP_OS_CAST_SWAP64(dst, src)
    #define tdr_cpp_cast_hton64(dst, src)    TDR_CPP_OS_CAST_SWAP64(dst, src)
    #define tdr_cpp_cast_ntoh32(dst, src)    TDR_CPP_OS_CAST_SWAP32(dst, src)
    #define tdr_cpp_cast_hton32(dst, src)    TDR_CPP_OS_CAST_SWAP32(dst, src)
    #define tdr_cpp_cast_ntoh16(dst, src)    TDR_CPP_OS_CAST_SWAP16(dst, src)
    #define tdr_cpp_cast_hton16(dst, src)    TDR_CPP_OS_CAST_SWAP16(dst, src)

    #define tdr_cpp_varint_ntoh64(buf, size, used, dst, ret)  TDR_CPP_DECODE_64_VARINT(buf, size, used, dst, ret)
    #define tdr_cpp_varint_ntoh32(buf, size, used, dst, ret)  TDR_CPP_DECODE_32_VARINT(buf, size, used, dst, ret)
    #define tdr_cpp_varint_ntoh16(buf, size, used, dst, ret)  TDR_CPP_DECODE_16_VARINT(buf, size, used, dst, ret)
    #define tdr_cpp_varint_hton64(src, buf, size, used, ret)  TDR_CPP_ENCODE_64_VARINT(src, buf, size, used, ret)
    #define tdr_cpp_varint_hton32(src, buf, size, used, ret)  TDR_CPP_ENCODE_32_VARINT(src, buf, size, used, ret)
    #define tdr_cpp_varint_hton16(src, buf, size, used, ret)  TDR_CPP_ENCODE_16_VARINT(src, buf, size, used, ret)

    #define tdr_cpp_zigzag_varint_ntoh64(buf, size, used, dst, ret)       \
                    TDR_CPP_DECODE_64_VARINT(buf, size, used, dst, ret);  \
                    TDR_CPP_ZIGZAG_DECODE_64(dst);
    #define tdr_cpp_zigzag_varint_ntoh32(buf, size, used, dst, ret)       \
                    TDR_CPP_DECODE_32_VARINT(buf, size, used, dst, ret);  \
                    TDR_CPP_ZIGZAG_DECODE_32(dst);
    #define tdr_cpp_zigzag_varint_ntoh16(buf, size, used, dst, ret)       \
                    TDR_CPP_DECODE_16_VARINT(buf, size, used, dst, ret);  \
                    TDR_CPP_ZIGZAG_DECODE_16(dst);
    #define tdr_cpp_zigzag_varint_hton64(src, buf, size, used, ret)       \
                    (src) = TDR_CPP_ZIGZAG_ENCODE_64((src));              \
                    TDR_CPP_ENCODE_64_VARINT(src, buf, size, used, ret);
    #define tdr_cpp_zigzag_varint_hton32(src, buf, size, used, ret)       \
                    (src) = TDR_CPP_ZIGZAG_ENCODE_32((src));              \
                    TDR_CPP_ENCODE_32_VARINT(src, buf, size, used, ret);
    #define tdr_cpp_zigzag_varint_hton16(src, buf, size, used, ret)       \
                    (src) = TDR_CPP_ZIGZAG_ENCODE_16((src));              \
                    TDR_CPP_ENCODE_16_VARINT(src, buf, size, used, ret);
#else
    #define tdr_cpp_ntoh64(x)    (x)
    #define tdr_cpp_hton64(x)    (x)
    #define tdr_cpp_ntoh32(x)    (x)
    #define tdr_cpp_hton32(x)    (x)
    #define tdr_cpp_ntoh16(x)    (x)
    #define tdr_cpp_hton16(x)    (x)

    #define tdr_cpp_cast_ntoh64(dst, src)    TDR_CPP_OS_CAST_64(dst, src)
    #define tdr_cpp_cast_hton64(dst, src)    TDR_CPP_OS_CAST_64(dst, src)
    #define tdr_cpp_cast_ntoh32(dst, src)    TDR_CPP_OS_CAST_32(dst, src)
    #define tdr_cpp_cast_hton32(dst, src)    TDR_CPP_OS_CAST_32(dst, src)
    #define tdr_cpp_cast_ntoh16(dst, src)    TDR_CPP_OS_CAST_16(dst, src)
    #define tdr_cpp_cast_hton16(dst, src)    TDR_CPP_OS_CAST_16(dst, src)

    #define tdr_cpp_varint_ntoh64(buf, size, used, dst, ret)                      \
            TDR_CPP_DECODE_64_VARINT(buf, size, used, dst, ret);                  \
            (dst = TDR_CPP_OS_SWAP64(dst));
    #define tdr_cpp_varint_ntoh32(buf, size, used, dst, ret)                      \
            TDR_CPP_DECODE_32_VARINT(buf, size, used, dst, ret);                  \
            (dst = TDR_CPP_OS_SWAP32(dst));
    #define tdr_cpp_varint_ntoh16(buf, size, used, dst, ret)                      \
            TDR_CPP_DECODE_16_VARINT(buf, size, used, dst, ret);                  \
            (dst = TDR_CPP_OS_SWAP16(dst));
    #define tdr_cpp_varint_hton64(src, buf, size, used, ret)                      \
            (src) = TDR_CPP_OS_SWAP64((src));                                     \
            TDR_CPP_ENCODE_64_VARINT(src, buf, size, used, ret);
    #define tdr_cpp_varint_hton32(src, buf, size, used, ret)                      \
            (src) = TDR_CPP_OS_SWAP32((src));                                     \
            TDR_CPP_ENCODE_32_VARINT(src, buf, size, used, ret);
    #define tdr_cpp_varint_hton16(src, buf, size, used, ret)                      \
            (src) = TDR_CPP_OS_SWAP16((src));                                     \
            TDR_CPP_ENCODE_16_VARINT(src, buf, size, used, ret);

    #define tdr_cpp_zigzag_varint_ntoh64(buf, size, used, dst, ret)       \
                    TDR_CPP_DECODE_64_VARINT(buf, size, used, dst, ret);  \
                    TDR_CPP_ZIGZAG_DECODE_64(dst);                \
                    (dst) = TDR_CPP_OS_SWAP64((dst));
    #define tdr_cpp_zigzag_varint_ntoh32(buf, size, used, dst, ret)       \
                    TDR_CPP_DECODE_32_VARINT(buf, size, used, dst, ret);  \
                    TDR_CPP_ZIGZAG_DECODE_32(dst);                \
                    (dst) = TDR_CPP_OS_SWAP32((dst));
    #define tdr_cpp_zigzag_varint_ntoh16(buf, size, used, dst, ret)       \
                    TDR_CPP_DECODE_16_VARINT(buf, size, used, dst, ret);  \
                    TDR_CPP_ZIGZAG_DECODE_16(dst);                \
                    (dst) = TDR_CPP_OS_SWAP16((dst));
    #define tdr_cpp_zigzag_varint_hton64(src, buf, size, used, ret)       \
                    (src) = TDR_CPP_OS_SWAP64((src));                     \
                    (src) = TDR_CPP_ZIGZAG_ENCODE_64((src));              \
                    TDR_CPP_ENCODE_64_VARINT(src, buf, size, used, ret);
    #define tdr_cpp_zigzag_varint_hton32(src, buf, size, used, ret)       \
                    (src) = TDR_CPP_OS_SWAP32((src));                     \
                    (src) = TDR_CPP_ZIGZAG_ENCODE_32((src));              \
                    TDR_CPP_ENCODE_32_VARINT(src, buf, size, used, ret);
    #define tdr_cpp_zigzag_varint_hton16(src, buf, size, used, ret)       \
                    (src) = TDR_CPP_OS_SWAP16((src));                     \
                    (src) = TDR_CPP_ZIGZAG_ENCODE_16((src));              \
                    TDR_CPP_ENCODE_16_VARINT(src, buf, size, used, ret);
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define tdr_cpp_snprintf  _snprintf
    #define tdr_cpp_vsnprintf  _vsnprintf
#else
    #define tdr_cpp_snprintf  snprintf
    #define tdr_cpp_vsnprintf  vsnprintf
#endif

#if (defined(_WIN32) || defined(_WIN64))
    #define TDR_CPP_INT64_FORMAT "%I64i"
    #define TDR_CPP_UINT64_FORMAT "%I64u"
    #define TDR_CPP_UINT64HEX_FORMAT "0x%016I64x"
#else
    #if defined(__x86_64__)
        #define TDR_CPP_INT64_FORMAT "%ld"
        #define TDR_CPP_UINT64_FORMAT "%lu"
        #define TDR_CPP_UINT64HEX_FORMAT "0x%016llx"
    #else
        #define TDR_CPP_INT64_FORMAT "%lld"
        #define TDR_CPP_UINT64_FORMAT "%llu"
        #define TDR_CPP_UINT64HEX_FORMAT "0x%016llx"
    #endif
#endif

#ifdef TSF4G_TDR_DEBUG
#define TSF4G_TDR_DEBUG_TRACE()\
    printf("TSF4G_TDR_TRACE... %s:%d\n", __FILE__, __LINE__);
#else
#define TSF4G_TDR_DEBUG_TRACE()
#endif

#define tdr_cpp_strtol  strtol
#if defined(_WIN32) || defined(_WIN64)
    #if _MSC_VER >= 1300
        #define tdr_cpp_strtoll  _strtoi64
        #define tdr_cpp_strtoull  _strtoui64
    #else
        #define tdr_cpp_strtoll  _need_at_least_VC7
        #define tdr_cpp_strtoull  _need_at_least_VC7
    #endif
#else
    #define tdr_cpp_strtoll  strtoll
    #define tdr_cpp_strtoull  strtoull
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define tdr_snprintf _snprintf
#else
    #define tdr_snprintf snprintf
#endif

#if defined(_WIN32) || defined(_WIN64)
    #if _MSC_VER >= 1400
        #define tdr_pal_strtok    strtok_s
    #else
        #define tdr_pal_strtok    ABase::tdr_strtok
    #endif
#else
    #define tdr_pal_strtok    strtok_r
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__ORBIS__)
    #define tdr_pal_strptime    ABase::tdr_strptime
#else
    #define tdr_pal_strptime    strptime
#endif


namespace ABase
{


#if defined(_WIN32) || defined(_WIN64)
    #if _MSC_VER < 1400
        char* tdr_strtok(char *s, const char *delim, char **context);
    #endif
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__ORBIS__) 
    char* tdr_strptime(const char* buf, const char* format, struct tm* timeptr);
#endif

enum TdrXmlFormat
{
    LIST_ENTRY,  /* non-array simple base-type members as nodes */
    ATTR_ENTRY,  /* non-array simple base-type members as attributes */
};

}

#endif
