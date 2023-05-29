// Copyright 2022 GCloud Inc. All rights reserved.
//
// Author: kiddpeng
//
// interface
// ...

#ifndef CROS_CURL_CROSCURL_CROSCURL_H_
#define CROS_CURL_CROSCURL_CROSCURL_H_

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

#define CROS_LIBCURL_VERSION_NUM 0x074a00
#define CROS_CURL_READFUNC_ABORT 0x10000000

#include "crosCurlDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT_API void
cros_curl_slist_free_all(struct cros_curl_slist *cros_curl_slist);

EXPORT_API crosCURLMcode cros_curl_multi_add_handle(crosCURLM *multi,
                                                    crosCURL *data);

EXPORT_API const char *cros_curl_multi_strerror(crosCURLMcode error);

EXPORT_API crosCURLMcode
cros_curl_multi_wait(crosCURLM *multi, struct cros_curl_waitfd extra_fds[],
                     unsigned int extra_nfds, int timeout_ms, int *ret);

EXPORT_API const char *cros_curl_easy_strerror(crosCURLcode error);

EXPORT_API crosCURLMcode cros_curl_multi_remove_handle(crosCURLM *multi,
                                                       crosCURL *data);

EXPORT_API crosCURLcode cros_curl_easy_getinfo(crosCURL *data,
                                               crosCURLINFO info, ...);

EXPORT_API crosCURLMcode cros_curl_multi_perform(crosCURLM *multi,
                                                 int *running_handles);

EXPORT_API void cros_curl_easy_cleanup(crosCURL *data);

EXPORT_API struct cros_curl_slist *
cros_curl_slist_append(struct cros_curl_slist *list, const char *data);

EXPORT_API crosCURLMcode cros_curl_multi_cleanup(crosCURLM *multi);

EXPORT_API crosCURLcode cros_curl_easy_perform(crosCURL *curl);

EXPORT_API void cros_curl_global_cleanup(void);

EXPORT_API crosCURLcode cros_curl_global_init(long flags);

EXPORT_API crosCURLM *cros_curl_multi_init(void);

EXPORT_API crosCURL *cros_curl_easy_init(void);

EXPORT_API crosCURLMsg *cros_curl_multi_info_read(crosCURLM *multi,
                                                  int *msgs_in_queue);

EXPORT_API crosCURLMcode cros_curl_multi_setopt(crosCURLM *multi_handle,
                                                crosCURLMoption option, ...);

EXPORT_API crosCURLcode cros_curl_easy_setopt(crosCURL *data,
                                              crosCURLoption tag, ...);

EXPORT_API void cros_curl_easy_reset(crosCURL *curl);

EXPORT_API crosCURLMcode cros_curl_multi_timeout(crosCURLM *multi_handle,
                                                 long *milliseconds);

EXPORT_API crosCURLSH *cros_curl_share_init(void);

EXPORT_API crosCURLSHcode cros_curl_share_setopt(crosCURLSH *sh,
                                                 crosCURLSHoption option, ...);

EXPORT_API crosCURLSHcode cros_curl_share_cleanup(crosCURLSH *sh);

EXPORT_API void cros_curl_free(void *p);

EXPORT_API crosCURLMcode cros_curl_multi_poll(
    crosCURLM *multi_handle, struct cros_curl_waitfd extra_fds[],
    unsigned int extra_nfds, int timeout_ms, int *ret);

////////////////////// cros openssl interface ////////////////////

typedef struct cros_evp_Encode_Ctx_st {
  /* number saved in a partial encode/decode */
  int num;
  /*
   * The length is either the output line length (in input bytes) or the
   * shortest input line length that is ok.  Once decoding begins, the
   * length is adjusted up each time a longer line is decoded
   */
  int length;
  /* data to encode */
  unsigned char enc_data[80];
  /* number read on current line */
  int line_num;
  unsigned int flags;
} CROS_EVP_ENCODE_CTX;

EXPORT_API CROS_EVP_ENCODE_CTX *cros_EVP_ENCODE_CTX_new(void);

EXPORT_API void cros_EVP_EncodeInit(CROS_EVP_ENCODE_CTX *ctx);

EXPORT_API int cros_EVP_EncodeUpdate(CROS_EVP_ENCODE_CTX *ctx,
                                     unsigned char *out, int *outl,
                                     const unsigned char *in, int inl);

EXPORT_API void cros_EVP_EncodeFinal(CROS_EVP_ENCODE_CTX *ctx,
                                     unsigned char *out, int *outl);

EXPORT_API void cros_EVP_ENCODE_CTX_free(CROS_EVP_ENCODE_CTX *ctx);

EXPORT_API void cros_EVP_DecodeInit(CROS_EVP_ENCODE_CTX *ctx);

EXPORT_API int cros_EVP_DecodeUpdate(CROS_EVP_ENCODE_CTX *ctx,
                                     unsigned char *out, int *outl,
                                     const unsigned char *in, int inl);

EXPORT_API int cros_EVP_DecodeFinal(CROS_EVP_ENCODE_CTX *ctx,
                                    unsigned char *out, int *outl);

EXPORT_API void cros_CRYPTO_free(void *str, const char *file, int line);

EXPORT_API void *cros_CRYPTO_malloc(size_t num, const char *file, int line);

#ifdef __cplusplus
}
#endif

#endif // CROS_CURL_CROSCURL_CROSCURL_H_
