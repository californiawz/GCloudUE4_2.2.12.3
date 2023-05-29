//
//  IOpenSSLFunc.h
//  CrosCurl
//  Define OpenSSLFunc
//
//  Created by kiddpeng on 2022/5/19.
//  Copyright © 2022年 gcloud. All rights reserved.
//

#ifndef PLUGINCROSCURL_SOURCE_IOPENSSLFUNC_H_
#define PLUGINCROSCURL_SOURCE_IOPENSSLFUNC_H_

#include "crosCurl.h"
#include "crosCurlDefine.h"

namespace GCloud {
namespace Plugin {
const int kOpenSSLVersionStrLen = 16;
struct OpenSSLFuncs {
  char version[kOpenSSLVersionStrLen];
  int size;
  CROS_EVP_ENCODE_CTX *(*cros_EVP_ENCODE_CTX_new)(void);
  void (*cros_EVP_EncodeInit)(CROS_EVP_ENCODE_CTX *ctx);
  int (*cros_EVP_EncodeUpdate)(CROS_EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl, const unsigned char *in,
                               int inl);
  void (*cros_EVP_EncodeFinal)(CROS_EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl);
  void (*cros_EVP_ENCODE_CTX_free)(CROS_EVP_ENCODE_CTX *ctx);
  void (*cros_EVP_DecodeInit)(CROS_EVP_ENCODE_CTX *ctx);
  int (*cros_EVP_DecodeUpdate)(CROS_EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl, const unsigned char *in,
                               int inl);
  int (*cros_EVP_DecodeFinal)(CROS_EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl);
  void (*cros_CRYPTO_free)(void *str, const char *file, int line);
  void *(*cros_CRYPTO_malloc)(size_t num, const char *file, int line);
};
}  // namespace Plugin
}  // namespace GCloud

#endif  // PLUGINCROSCURL_SOURCE_IOPENSSLFUNC_H_
