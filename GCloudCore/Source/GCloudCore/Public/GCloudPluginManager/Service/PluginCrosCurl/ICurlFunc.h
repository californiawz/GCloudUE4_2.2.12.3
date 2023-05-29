//
//  ICurlFunc.h
//  CrosCurl
//  Define CurlFunc
//
//  Created by kiddpeng on 2022/5/19.
//  Copyright © 2022年 gcloud. All rights reserved.
//

#ifndef PLUGINCROSCURL_SOURCE_ICURLFUNC_H_
#define PLUGINCROSCURL_SOURCE_ICURLFUNC_H_

#include "crosCurlDefine.h"

namespace GCloud {
namespace Plugin {
const int kCurlVersionStrLen = 16;
struct CurlFuncs {
  char version[kCurlVersionStrLen];
  int size;
  void (*cros_curl_slist_free_all)(struct cros_curl_slist *cros_curl_slist);
  crosCURLMcode (*cros_curl_multi_add_handle)(crosCURLM *multi, crosCURL *data);
  const char *(*cros_curl_multi_strerror)(crosCURLMcode error);
  crosCURLMcode (*cros_curl_multi_wait)(crosCURLM *multi, struct cros_curl_waitfd extra_fds[], unsigned int extra_nfds,
                                        int timeout_ms, int *ret);
  const char *(*cros_curl_easy_strerror)(crosCURLcode error);
  crosCURLMcode (*cros_curl_multi_remove_handle)(crosCURLM *multi, crosCURL *data);
  crosCURLcode (*cros_curl_easy_getinfo)(crosCURL *data, crosCURLINFO info, ...);
  crosCURLMcode (*cros_curl_multi_perform)(crosCURLM *multi, int *running_handles);
  void (*cros_curl_easy_cleanup)(crosCURL *data);
  struct cros_curl_slist *(*cros_curl_slist_append)(struct cros_curl_slist *list, const char *data);
  crosCURLMcode (*cros_curl_multi_cleanup)(crosCURLM *multi);
  crosCURLcode (*cros_curl_easy_perform)(crosCURL *curl);
  void (*cros_curl_global_cleanup)(void);
  crosCURLcode (*cros_curl_global_init)(long flags);
  crosCURLM *(*cros_curl_multi_init)(void);
  crosCURL *(*cros_curl_easy_init)(void);
  crosCURLMsg *(*cros_curl_multi_info_read)(crosCURLM *multi, int *msgs_in_queue);
  crosCURLMcode (*cros_curl_multi_setopt)(crosCURLM *multi_handle, crosCURLMoption option, ...);
  crosCURLcode (*cros_curl_easy_setopt)(crosCURL *data, crosCURLoption tag, ...);
  void (*cros_curl_easy_reset)(crosCURL *curl);
  crosCURLMcode (*cros_curl_multi_timeout)(crosCURLM *multi_handle, long *milliseconds);
};

struct CurlFuncs_V1 {
  char version[kCurlVersionStrLen];
  int size;
  void (*cros_curl_slist_free_all)(struct cros_curl_slist *cros_curl_slist);
  crosCURLMcode (*cros_curl_multi_add_handle)(crosCURLM *multi, crosCURL *data);
  const char *(*cros_curl_multi_strerror)(crosCURLMcode error);
  crosCURLMcode (*cros_curl_multi_wait)(crosCURLM *multi, struct cros_curl_waitfd extra_fds[], unsigned int extra_nfds,
                                        int timeout_ms, int *ret);
  const char *(*cros_curl_easy_strerror)(crosCURLcode error);
  crosCURLMcode (*cros_curl_multi_remove_handle)(crosCURLM *multi, crosCURL *data);
  crosCURLcode (*cros_curl_easy_getinfo)(crosCURL *data, crosCURLINFO info, ...);
  crosCURLMcode (*cros_curl_multi_perform)(crosCURLM *multi, int *running_handles);
  void (*cros_curl_easy_cleanup)(crosCURL *data);
  struct cros_curl_slist *(*cros_curl_slist_append)(struct cros_curl_slist *list, const char *data);
  crosCURLMcode (*cros_curl_multi_cleanup)(crosCURLM *multi);
  crosCURLcode (*cros_curl_easy_perform)(crosCURL *curl);
  void (*cros_curl_global_cleanup)(void);
  crosCURLcode (*cros_curl_global_init)(long flags);
  crosCURLM *(*cros_curl_multi_init)(void);
  crosCURL *(*cros_curl_easy_init)(void);
  crosCURLMsg *(*cros_curl_multi_info_read)(crosCURLM *multi, int *msgs_in_queue);
  crosCURLMcode (*cros_curl_multi_setopt)(crosCURLM *multi_handle, crosCURLMoption option, ...);
  crosCURLcode (*cros_curl_easy_setopt)(crosCURL *data, crosCURLoption tag, ...);
  void (*cros_curl_easy_reset)(crosCURL *curl);
  crosCURLMcode (*cros_curl_multi_timeout)(crosCURLM *multi_handle, long *milliseconds);
  crosCURLSH *(*cros_curl_share_init)(void);
  crosCURLSHcode (*cros_curl_share_setopt)(crosCURLSH *sh, crosCURLSHoption option, ...);
  crosCURLSHcode (*cros_curl_share_cleanup)(crosCURLSH *sh);
  void (*cros_curl_free)(void *p);
};
}  // namespace Plugin
}  // namespace GCloud

#endif  // PLUGINCROSCURL_SOURCE_ICURLFUNC_H_
