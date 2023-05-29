// Copyright 2022 GCloud Inc. All rights reserved.
//
// Author: kiddpeng
//
// crosCurl Header
// ...

#ifndef CROS_CURL_CROSCURL_CROSCURLDEFINE_H_
#define CROS_CURL_CROSCURL_CROSCURLDEFINE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* long may be 32 or 64 bits, but we should never depend on anything else
   but 32 */
#define CROS_CURLOPTTYPE_LONG 0
#define CROS_CURLOPTTYPE_OBJECTPOINT 10000
#define CROS_CURLOPTTYPE_FUNCTIONPOINT 20000
#define CROS_CURLOPTTYPE_OFF_T 30000
#define CROS_CURLOPTTYPE_BLOB 40000

#define CROS_CURLOPT(na, t, nu) na = t + nu

/* 'char *' argument to a string with a trailing zero */
#define CROS_CURLOPTTYPE_STRINGPOINT CROS_CURLOPTTYPE_OBJECTPOINT

/* 'struct curl_slist *' argument */
#define CROS_CURLOPTTYPE_SLISTPOINT CROS_CURLOPTTYPE_OBJECTPOINT

/* 'void *' argument passed untouched to callback */
#define CROS_CURLOPTTYPE_CBPOINT CROS_CURLOPTTYPE_OBJECTPOINT

/* 'long' argument with a set of values/bitmask */
#define CROS_CURLOPTTYPE_VALUES CROS_CURLOPTTYPE_LONG

/* Provide defines for really old option names */
#define CROS_CURLOPT_FILE CROS_CURLOPT_WRITEDATA  /* name changed in 7.9.7 */
#define CROS_CURLOPT_INFILE CROS_CURLOPT_READDATA /* name changed in 7.9.7 */
#define CROS_CURLOPT_WRITEHEADER CROS_CURLOPT_HEADERDATA

// redefine class and struct
typedef void crosCURLM;
typedef void crosCURL;
typedef void crosCURLSH;

// typedef int crosCURLMcode;
typedef int crosCURLcode;
typedef int crosCURLINFO;
// typedef void crosCURLMsg;
// typedef int crosCURLoption;

/* linked-list structure for the CURLOPT_QUOTE option (and other) */
struct cros_curl_slist {
  char *data;
  struct cros_curl_slist *next;
};

#if defined(WIN32) && !defined(__LWIP_OPT_H__)
typedef unsigned __int64 cros_curl_socket_t;
#else
typedef int cros_curl_socket_t;
#endif

struct cros_curl_waitfd {
  cros_curl_socket_t fd;
  short events;
  short revents; /* not supported yet */
};

typedef enum {
  CROS_CURLINFO_TEXT = 0,
  CROS_CURLINFO_HEADER_IN,    /* 1 */
  CROS_CURLINFO_HEADER_OUT,   /* 2 */
  CROS_CURLINFO_DATA_IN,      /* 3 */
  CROS_CURLINFO_DATA_OUT,     /* 4 */
  CROS_CURLINFO_SSL_DATA_IN,  /* 5 */
  CROS_CURLINFO_SSL_DATA_OUT, /* 6 */
  CROS_CURLINFO_END
} cros_curl_infotype;

#define CROS_CURLINFO_STRING 0x100000
#define CROS_CURLINFO_LONG 0x200000
#define CROS_CURLINFO_DOUBLE 0x300000
#define CROS_CURLINFO_SLIST 0x400000
#define CROS_CURLINFO_PTR 0x400000 /* same as SLIST */
#define CROS_CURLINFO_SOCKET 0x500000
#define CROS_CURLINFO_OFF_T 0x600000
#define CROS_CURLINFO_MASK 0x0fffff
#define CROS_CURLINFO_TYPEMASK 0xf00000

#define CROS_CURL_GLOBAL_SSL (1 << 0) /* no purpose since since 7.57.0 */
#define CROS_CURL_GLOBAL_WIN32 (1 << 1)
#define CROS_CURL_GLOBAL_ALL (CROS_CURL_GLOBAL_SSL | CROS_CURL_GLOBAL_WIN32)
#define CROS_CURL_GLOBAL_NOTHING 0
#define CROS_CURL_GLOBAL_DEFAULT CROS_CURL_GLOBAL_ALL
#define CROS_CURL_GLOBAL_ACK_EINTR (1 << 2)

typedef enum {
  CROS_CURLINFO_NONE, /* first, never use this */
  CROS_CURLINFO_EFFECTIVE_URL = CROS_CURLINFO_STRING + 1,
  CROS_CURLINFO_RESPONSE_CODE = CROS_CURLINFO_LONG + 2,
  CROS_CURLINFO_TOTAL_TIME = CROS_CURLINFO_DOUBLE + 3,
  CROS_CURLINFO_NAMELOOKUP_TIME = CROS_CURLINFO_DOUBLE + 4,
  CROS_CURLINFO_CONNECT_TIME = CROS_CURLINFO_DOUBLE + 5,
  CROS_CURLINFO_PRETRANSFER_TIME = CROS_CURLINFO_DOUBLE + 6,
  CROS_CURLINFO_SIZE_UPLOAD = CROS_CURLINFO_DOUBLE + 7,
  CROS_CURLINFO_SIZE_UPLOAD_T = CROS_CURLINFO_OFF_T + 7,
  CROS_CURLINFO_SIZE_DOWNLOAD = CROS_CURLINFO_DOUBLE + 8,
  CROS_CURLINFO_SIZE_DOWNLOAD_T = CROS_CURLINFO_OFF_T + 8,
  CROS_CURLINFO_SPEED_DOWNLOAD = CROS_CURLINFO_DOUBLE + 9,
  CROS_CURLINFO_SPEED_DOWNLOAD_T = CROS_CURLINFO_OFF_T + 9,
  CROS_CURLINFO_SPEED_UPLOAD = CROS_CURLINFO_DOUBLE + 10,
  CROS_CURLINFO_SPEED_UPLOAD_T = CROS_CURLINFO_OFF_T + 10,
  CROS_CURLINFO_HEADER_SIZE = CROS_CURLINFO_LONG + 11,
  CROS_CURLINFO_REQUEST_SIZE = CROS_CURLINFO_LONG + 12,
  CROS_CURLINFO_SSL_VERIFYRESULT = CROS_CURLINFO_LONG + 13,
  CROS_CURLINFO_FILETIME = CROS_CURLINFO_LONG + 14,
  CROS_CURLINFO_FILETIME_T = CROS_CURLINFO_OFF_T + 14,
  CROS_CURLINFO_CONTENT_LENGTH_DOWNLOAD = CROS_CURLINFO_DOUBLE + 15,
  CROS_CURLINFO_CONTENT_LENGTH_DOWNLOAD_T = CROS_CURLINFO_OFF_T + 15,
  CROS_CURLINFO_CONTENT_LENGTH_UPLOAD = CROS_CURLINFO_DOUBLE + 16,
  CROS_CURLINFO_CONTENT_LENGTH_UPLOAD_T = CROS_CURLINFO_OFF_T + 16,
  CROS_CURLINFO_STARTTRANSFER_TIME = CROS_CURLINFO_DOUBLE + 17,
  CROS_CURLINFO_CONTENT_TYPE = CROS_CURLINFO_STRING + 18,
  CROS_CURLINFO_REDIRECT_TIME = CROS_CURLINFO_DOUBLE + 19,
  CROS_CURLINFO_REDIRECT_COUNT = CROS_CURLINFO_LONG + 20,
  CROS_CURLINFO_PRIVATE = CROS_CURLINFO_STRING + 21,
  CROS_CURLINFO_HTTP_CONNECTCODE = CROS_CURLINFO_LONG + 22,
  CROS_CURLINFO_HTTPAUTH_AVAIL = CROS_CURLINFO_LONG + 23,
  CROS_CURLINFO_PROXYAUTH_AVAIL = CROS_CURLINFO_LONG + 24,
  CROS_CURLINFO_OS_ERRNO = CROS_CURLINFO_LONG + 25,
  CROS_CURLINFO_NUM_CONNECTS = CROS_CURLINFO_LONG + 26,
  CROS_CURLINFO_SSL_ENGINES = CROS_CURLINFO_SLIST + 27,
  CROS_CURLINFO_COOKIELIST = CROS_CURLINFO_SLIST + 28,
  CROS_CURLINFO_LASTSOCKET = CROS_CURLINFO_LONG + 29,
  CROS_CURLINFO_FTP_ENTRY_PATH = CROS_CURLINFO_STRING + 30,
  CROS_CURLINFO_REDIRECT_URL = CROS_CURLINFO_STRING + 31,
  CROS_CURLINFO_PRIMARY_IP = CROS_CURLINFO_STRING + 32,
  CROS_CURLINFO_APPCONNECT_TIME = CROS_CURLINFO_DOUBLE + 33,
  CROS_CURLINFO_CERTINFO = CROS_CURLINFO_PTR + 34,
  CROS_CURLINFO_CONDITION_UNMET = CROS_CURLINFO_LONG + 35,
  CROS_CURLINFO_RTSP_SESSION_ID = CROS_CURLINFO_STRING + 36,
  CROS_CURLINFO_RTSP_CLIENT_CSEQ = CROS_CURLINFO_LONG + 37,
  CROS_CURLINFO_RTSP_SERVER_CSEQ = CROS_CURLINFO_LONG + 38,
  CROS_CURLINFO_RTSP_CSEQ_RECV = CROS_CURLINFO_LONG + 39,
  CROS_CURLINFO_PRIMARY_PORT = CROS_CURLINFO_LONG + 40,
  CROS_CURLINFO_LOCAL_IP = CROS_CURLINFO_STRING + 41,
  CROS_CURLINFO_LOCAL_PORT = CROS_CURLINFO_LONG + 42,
  CROS_CURLINFO_TLS_SESSION = CROS_CURLINFO_PTR + 43,
  CROS_CURLINFO_ACTIVESOCKET = CROS_CURLINFO_SOCKET + 44,
  CROS_CURLINFO_TLS_SSL_PTR = CROS_CURLINFO_PTR + 45,
  CROS_CURLINFO_HTTP_VERSION = CROS_CURLINFO_LONG + 46,
  CROS_CURLINFO_PROXY_SSL_VERIFYRESULT = CROS_CURLINFO_LONG + 47,
  CROS_CURLINFO_PROTOCOL = CROS_CURLINFO_LONG + 48,
  CROS_CURLINFO_SCHEME = CROS_CURLINFO_STRING + 49,
  CROS_CURLINFO_TOTAL_TIME_T = CROS_CURLINFO_OFF_T + 50,
  CROS_CURLINFO_NAMELOOKUP_TIME_T = CROS_CURLINFO_OFF_T + 51,
  CROS_CURLINFO_CONNECT_TIME_T = CROS_CURLINFO_OFF_T + 52,
  CROS_CURLINFO_PRETRANSFER_TIME_T = CROS_CURLINFO_OFF_T + 53,
  CROS_CURLINFO_STARTTRANSFER_TIME_T = CROS_CURLINFO_OFF_T + 54,
  CROS_CURLINFO_REDIRECT_TIME_T = CROS_CURLINFO_OFF_T + 55,
  CROS_CURLINFO_APPCONNECT_TIME_T = CROS_CURLINFO_OFF_T + 56,
  CROS_CURLINFO_RETRY_AFTER = CROS_CURLINFO_OFF_T + 57,
  CROS_CURLINFO_EFFECTIVE_METHOD = CROS_CURLINFO_STRING + 58,
  CROS_CURLINFO_PROXY_ERROR = CROS_CURLINFO_LONG + 59,

  CROS_CURLINFO_LASTONE = 59
} CROS_CURLINFO;

typedef enum {
  CROS_CURL_HTTP_VERSION_NONE,              /* setting this means we don't care, and that we'd
                                          like the library to choose the best possible
                                          for us! */
  CROS_CURL_HTTP_VERSION_1_0,               /* please use HTTP 1.0 in the request */
  CROS_CURL_HTTP_VERSION_1_1,               /* please use HTTP 1.1 in the request */
  CROS_CURL_HTTP_VERSION_2_0,               /* please use HTTP 2 in the request */
  CROS_CURL_HTTP_VERSION_2TLS,              /* use version 2 for HTTPS, version 1.1 for HTTP */
  CROS_CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE, /* please use HTTP 2 without HTTP/1.1
                                         Upgrade */
  CROS_CURL_HTTP_VERSION_3 = 30,            /* Makes use of explicit HTTP/3 without fallback.
                                          Use CURLOPT_ALTSVC to enable HTTP/3 upgrade */
  CROS_CURL_HTTP_VERSION_LAST               /* *ILLEGAL* http version */
} CROS_CURL_HTTP_VERSION_TYPE;

typedef enum {
  CROS_CURLE_OK = 0,
  CROS_CURLE_UNSUPPORTED_PROTOCOL,  /* 1 */
  CROS_CURLE_FAILED_INIT,           /* 2 */
  CROS_CURLE_URL_MALFORMAT,         /* 3 */
  CROS_CURLE_NOT_BUILT_IN,          /* 4 - [was obsoleted in August 2007 for
                                  7.17.0, reused in April 2011 for 7.21.5] */
  CROS_CURLE_COULDNT_RESOLVE_PROXY, /* 5 */
  CROS_CURLE_COULDNT_RESOLVE_HOST,  /* 6 */
  CROS_CURLE_COULDNT_CONNECT,       /* 7 */
  CROS_CURLE_WEIRD_SERVER_REPLY,    /* 8 */
  CROS_CURLE_REMOTE_ACCESS_DENIED,  /* 9 a service was denied by the server
                                  due to lack of access - when login fails
                                  this is not returned. */
  CROS_CURLE_FTP_ACCEPT_FAILED,     /* 10 - [was obsoleted in April 2006 for
                                  7.15.4, reused in Dec 2011 for 7.24.0]*/
  CROS_CURLE_FTP_WEIRD_PASS_REPLY,  /* 11 */
  CROS_CURLE_FTP_ACCEPT_TIMEOUT,    /* 12 - timeout occurred accepting server
                                  [was obsoleted in August 2007 for 7.17.0,
                                  reused in Dec 2011 for 7.24.0]*/
  CROS_CURLE_FTP_WEIRD_PASV_REPLY,  /* 13 */
  CROS_CURLE_FTP_WEIRD_227_FORMAT,  /* 14 */
  CROS_CURLE_FTP_CANT_GET_HOST,     /* 15 */
  CROS_CURLE_HTTP2,                 /* 16 - A problem in the http2 framing layer.
                                  [was obsoleted in August 2007 for 7.17.0,
                                  reused in July 2014 for 7.38.0] */
  CROS_CURLE_FTP_COULDNT_SET_TYPE,  /* 17 */
  CROS_CURLE_PARTIAL_FILE,          /* 18 */
  CROS_CURLE_FTP_COULDNT_RETR_FILE, /* 19 */
  CROS_CURLE_OBSOLETE20,            /* 20 - NOT USED */
  CROS_CURLE_QUOTE_ERROR,           /* 21 - quote command failure */
  CROS_CURLE_HTTP_RETURNED_ERROR,   /* 22 */
  CROS_CURLE_WRITE_ERROR,           /* 23 */
  CROS_CURLE_OBSOLETE24,            /* 24 - NOT USED */
  CROS_CURLE_UPLOAD_FAILED,         /* 25 - failed upload "command" */
  CROS_CURLE_READ_ERROR,            /* 26 - couldn't open/read from file */
  CROS_CURLE_OUT_OF_MEMORY,         /* 27 */
  /* Note: CURLE_OUT_OF_MEMORY may sometimes indicate a conversion error
           instead of a memory allocation error if CURL_DOES_CONVERSIONS
           is defined
  */
  CROS_CURLE_OPERATION_TIMEDOUT,       /* 28 - the timeout time was reached */
  CROS_CURLE_OBSOLETE29,               /* 29 - NOT USED */
  CROS_CURLE_FTP_PORT_FAILED,          /* 30 - FTP PORT operation failed */
  CROS_CURLE_FTP_COULDNT_USE_REST,     /* 31 - the REST command failed */
  CROS_CURLE_OBSOLETE32,               /* 32 - NOT USED */
  CROS_CURLE_RANGE_ERROR,              /* 33 - RANGE "command" didn't work */
  CROS_CURLE_HTTP_POST_ERROR,          /* 34 */
  CROS_CURLE_SSL_CONNECT_ERROR,        /* 35 - wrong when connecting with SSL */
  CROS_CURLE_BAD_DOWNLOAD_RESUME,      /* 36 - couldn't resume download */
  CROS_CURLE_FILE_COULDNT_READ_FILE,   /* 37 */
  CROS_CURLE_LDAP_CANNOT_BIND,         /* 38 */
  CROS_CURLE_LDAP_SEARCH_FAILED,       /* 39 */
  CROS_CURLE_OBSOLETE40,               /* 40 - NOT USED */
  CROS_CURLE_FUNCTION_NOT_FOUND,       /* 41 - NOT USED starting with 7.53.0 */
  CROS_CURLE_ABORTED_BY_CALLBACK,      /* 42 */
  CROS_CURLE_BAD_FUNCTION_ARGUMENT,    /* 43 */
  CROS_CURLE_OBSOLETE44,               /* 44 - NOT USED */
  CROS_CURLE_INTERFACE_FAILED,         /* 45 - CURLOPT_INTERFACE failed */
  CROS_CURLE_OBSOLETE46,               /* 46 - NOT USED */
  CROS_CURLE_TOO_MANY_REDIRECTS,       /* 47 - catch endless re-direct loops */
  CROS_CURLE_UNKNOWN_OPTION,           /* 48 - User specified an unknown option */
  CROS_CURLE_TELNET_OPTION_SYNTAX,     /* 49 - Malformed telnet option */
  CROS_CURLE_OBSOLETE50,               /* 50 - NOT USED */
  CROS_CURLE_OBSOLETE51,               /* 51 - NOT USED */
  CROS_CURLE_GOT_NOTHING,              /* 52 - when this is a specific error */
  CROS_CURLE_SSL_ENGINE_NOTFOUND,      /* 53 - SSL crypto engine not found */
  CROS_CURLE_SSL_ENGINE_SETFAILED,     /* 54 - can not set SSL crypto engine as
                                     default */
  CROS_CURLE_SEND_ERROR,               /* 55 - failed sending network data */
  CROS_CURLE_RECV_ERROR,               /* 56 - failure in receiving network data */
  CROS_CURLE_OBSOLETE57,               /* 57 - NOT IN USE */
  CROS_CURLE_SSL_CERTPROBLEM,          /* 58 - problem with the local certificate */
  CROS_CURLE_SSL_CIPHER,               /* 59 - couldn't use specified cipher */
  CROS_CURLE_PEER_FAILED_VERIFICATION, /* 60 - peer's certificate or fingerprint
                                     wasn't verified fine */
  CROS_CURLE_BAD_CONTENT_ENCODING,     /* 61 - Unrecognized/bad encoding */
  CROS_CURLE_LDAP_INVALID_URL,         /* 62 - Invalid LDAP URL */
  CROS_CURLE_FILESIZE_EXCEEDED,        /* 63 - Maximum file size exceeded */
  CROS_CURLE_USE_SSL_FAILED,           /* 64 - Requested FTP SSL level failed */
  CROS_CURLE_SEND_FAIL_REWIND,         /* 65 - Sending the data requires a rewind
                                     that failed */
  CROS_CURLE_SSL_ENGINE_INITFAILED,    /* 66 - failed to initialise ENGINE */
  CROS_CURLE_LOGIN_DENIED,             /* 67 - user, password or similar was not
                                     accepted and we failed to login */
  CROS_CURLE_TFTP_NOTFOUND,            /* 68 - file not found on server */
  CROS_CURLE_TFTP_PERM,                /* 69 - permission problem on server */
  CROS_CURLE_REMOTE_DISK_FULL,         /* 70 - out of disk space on server */
  CROS_CURLE_TFTP_ILLEGAL,             /* 71 - Illegal TFTP operation */
  CROS_CURLE_TFTP_UNKNOWNID,           /* 72 - Unknown transfer ID */
  CROS_CURLE_REMOTE_FILE_EXISTS,       /* 73 - File already exists */
  CROS_CURLE_TFTP_NOSUCHUSER,          /* 74 - No such user */
  CROS_CURLE_CONV_FAILED,              /* 75 - conversion failed */
  CROS_CURLE_CONV_REQD,                /* 76 - caller must register conversion
                                     callbacks using curl_easy_setopt options
                                     CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                                     CURLOPT_CONV_TO_NETWORK_FUNCTION, and
                                     CURLOPT_CONV_FROM_UTF8_FUNCTION */
  CROS_CURLE_SSL_CACERT_BADFILE,       /* 77 - could not load CACERT file, missing
                                     or wrong format */
  CROS_CURLE_REMOTE_FILE_NOT_FOUND,    /* 78 - remote file not found */
  CROS_CURLE_SSH,                      /* 79 - error from the SSH layer, somewhat
                                     generic so the error message will be of
                                     interest when this has happened */

  CROS_CURLE_SSL_SHUTDOWN_FAILED,      /* 80 - Failed to shut down the SSL
                                     connection */
  CROS_CURLE_AGAIN,                    /* 81 - socket is not ready for send/recv,
                                     wait till it's ready and try again (Added
                                     in 7.18.2) */
  CROS_CURLE_SSL_CRL_BADFILE,          /* 82 - could not load CRL file, missing or
                                     wrong format (Added in 7.19.0) */
  CROS_CURLE_SSL_ISSUER_ERROR,         /* 83 - Issuer check failed.  (Added in
                                     7.19.0) */
  CROS_CURLE_FTP_PRET_FAILED,          /* 84 - a PRET command failed */
  CROS_CURLE_RTSP_CSEQ_ERROR,          /* 85 - mismatch of RTSP CSeq numbers */
  CROS_CURLE_RTSP_SESSION_ERROR,       /* 86 - mismatch of RTSP Session Ids */
  CROS_CURLE_FTP_BAD_FILE_LIST,        /* 87 - unable to parse FTP file list */
  CROS_CURLE_CHUNK_FAILED,             /* 88 - chunk callback reported error */
  CROS_CURLE_NO_CONNECTION_AVAILABLE,  /* 89 - No connection available, the
                                     session will be queued */
  CROS_CURLE_SSL_PINNEDPUBKEYNOTMATCH, /* 90 - specified pinned public key did not
                                     match */
  CROS_CURLE_SSL_INVALIDCERTSTATUS,    /* 91 - invalid certificate status */
  CROS_CURLE_HTTP2_STREAM,             /* 92 - stream error in HTTP/2 framing layer
                                        */
  CROS_CURLE_RECURSIVE_API_CALL,       /* 93 - an api function was called from
                                     inside a callback */
  CROS_CURLE_AUTH_ERROR,               /* 94 - an authentication function returned an
                                     error */
  CROS_CURLE_HTTP3,                    /* 95 - An HTTP/3 layer problem */
  CROS_CURLE_QUIC_CONNECT_ERROR,       /* 96 - QUIC connection error */
  CROS_CURLE_PROXY,                    /* 97 - proxy handshake error */
  CROS_CURLE_WS_SHAKE_ERROR,           /* 98 - websocket handshake error */
  CROS_CURL_LAST                       /* never use! */
} CROS_CURLcode;

typedef enum {
  CROS_CURLM_CALL_MULTI_PERFORM = -1, /* please call curl_multi_perform() or
                                    curl_multi_socket*() soon */
  CROS_CURLM_OK,
  CROS_CURLM_BAD_HANDLE,            /* the passed-in handle is not a valid CROS_CURLM handle */
  CROS_CURLM_BAD_EASY_HANDLE,       /* an easy handle was not good/valid */
  CROS_CURLM_OUT_OF_MEMORY,         /* if you ever get this, you're in deep sh*t */
  CROS_CURLM_INTERNAL_ERROR,        /* this is a libcurl bug */
  CROS_CURLM_BAD_SOCKET,            /* the passed in socket argument did not match */
  CROS_CURLM_UNKNOWN_OPTION,        /* curl_multi_setopt() with unsupported option */
  CROS_CURLM_ADDED_ALREADY,         /* an easy handle already added to a multi handle was
                                  attempted to get added - again */
  CROS_CURLM_RECURSIVE_API_CALL,    /* an api function was called from inside a
                                  callback */
  CROS_CURLM_WAKEUP_FAILURE,        /* wakeup is unavailable or failed */
  CROS_CURLM_BAD_FUNCTION_ARGUMENT, /* function called with a bad parameter */
  CROS_CURLM_LAST
} crosCURLMcode;

typedef enum {
  CROS_CURLMSG_NONE, /* first, not used */
  CROS_CURLMSG_DONE, /* This easy handle has completed. 'result' contains
                   the CURLcode of the transfer */
  CROS_CURLMSG_LAST  /* last, not used */
} crosCURLMSG;

typedef struct {
  crosCURLMSG msg;       /* what this message means */
  crosCURL *easy_handle; /* the handle it concerns */
  union {
    void *whatever;      /* message-specific data */
    crosCURLcode result; /* return code for transfer */
  } data;
} crosCURLMsg;

typedef enum {
  /* This is the FILE * or void * the regular output should be written to. */
  CROS_CURLOPT(CROS_CURLOPT_WRITEDATA, CROS_CURLOPTTYPE_CBPOINT, 1),

  /* The full URL to get/put */
  CROS_CURLOPT(CROS_CURLOPT_URL, CROS_CURLOPTTYPE_STRINGPOINT, 2),

  /* Port number to connect to, if other than default. */
  CROS_CURLOPT(CROS_CURLOPT_PORT, CROS_CURLOPTTYPE_LONG, 3),

  /* Name of proxy to use. */
  CROS_CURLOPT(CROS_CURLOPT_PROXY, CROS_CURLOPTTYPE_STRINGPOINT, 4),

  /* "user:password;options" to use when fetching. */
  CROS_CURLOPT(CROS_CURLOPT_USERPWD, CROS_CURLOPTTYPE_STRINGPOINT, 5),

  /* "user:password" to use with proxy. */
  CROS_CURLOPT(CROS_CURLOPT_PROXYUSERPWD, CROS_CURLOPTTYPE_STRINGPOINT, 6),

  /* Range to get, specified as an ASCII string. */
  CROS_CURLOPT(CROS_CURLOPT_RANGE, CROS_CURLOPTTYPE_STRINGPOINT, 7),

  /* not used */

  /* Specified file stream to upload from (use as input): */
  CROS_CURLOPT(CROS_CURLOPT_READDATA, CROS_CURLOPTTYPE_CBPOINT, 9),

  /* Buffer to receive error messages in, must be at least CURL_ERROR_SIZE
   * bytes big. */
  CROS_CURLOPT(CROS_CURLOPT_ERRORBUFFER, CROS_CURLOPTTYPE_OBJECTPOINT, 10),

  /* Function that will be called to store the output (instead of fwrite). The
   * parameters will use fwrite() syntax, make sure to follow them. */
  CROS_CURLOPT(CROS_CURLOPT_WRITEFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 11),

  /* Function that will be called to read the input (instead of fread). The
   * parameters will use fread() syntax, make sure to follow them. */
  CROS_CURLOPT(CROS_CURLOPT_READFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 12),

  /* Time-out the read operation after this amount of seconds */
  CROS_CURLOPT(CROS_CURLOPT_TIMEOUT, CROS_CURLOPTTYPE_LONG, 13),

  /* If the CROS_CURLOPT_INFILE is used, this can be used to inform libcurl about
   * how large the file being sent really is. That allows better error
   * checking and better verifies that the upload was successful. -1 means
   * unknown size.
   *
   * For large file support, there is also a _LARGE version of the key
   * which takes an off_t type, allowing platforms with larger off_t
   * sizes to handle larger files.  See below for INFILESIZE_LARGE.
   */
  CROS_CURLOPT(CROS_CURLOPT_INFILESIZE, CROS_CURLOPTTYPE_LONG, 14),

  /* POST static input fields. */
  CROS_CURLOPT(CROS_CURLOPT_POSTFIELDS, CROS_CURLOPTTYPE_OBJECTPOINT, 15),

  /* Set the referrer page (needed by some CGIs) */
  CROS_CURLOPT(CROS_CURLOPT_REFERER, CROS_CURLOPTTYPE_STRINGPOINT, 16),

  /* Set the FTP PORT string (interface name, named or numerical IP address)
     Use i.e '-' to use default address. */
  CROS_CURLOPT(CROS_CURLOPT_FTPPORT, CROS_CURLOPTTYPE_STRINGPOINT, 17),

  /* Set the User-Agent string (examined by some CGIs) */
  CROS_CURLOPT(CROS_CURLOPT_USERAGENT, CROS_CURLOPTTYPE_STRINGPOINT, 18),

  /* If the download receives less than "low speed limit" bytes/second
   * during "low speed time" seconds, the operations is aborted.
   * You could i.e if you have a pretty high speed connection, abort if
   * it is less than 2000 bytes/sec during 20 seconds.
   */

  /* Set the "low speed limit" */
  CROS_CURLOPT(CROS_CURLOPT_LOW_SPEED_LIMIT, CROS_CURLOPTTYPE_LONG, 19),

  /* Set the "low speed time" */
  CROS_CURLOPT(CROS_CURLOPT_LOW_SPEED_TIME, CROS_CURLOPTTYPE_LONG, 20),

  /* Set the continuation offset.
   *
   * Note there is also a _LARGE version of this key which uses
   * off_t types, allowing for large file offsets on platforms which
   * use larger-than-32-bit off_t's.  Look below for RESUME_FROM_LARGE.
   */
  CROS_CURLOPT(CROS_CURLOPT_RESUME_FROM, CROS_CURLOPTTYPE_LONG, 21),

  /* Set cookie in request: */
  CROS_CURLOPT(CROS_CURLOPT_COOKIE, CROS_CURLOPTTYPE_STRINGPOINT, 22),

  /* This points to a linked list of headers, struct curl_slist kind. This
     list is also used for RTSP (in spite of its name) */
  CROS_CURLOPT(CROS_CURLOPT_HTTPHEADER, CROS_CURLOPTTYPE_SLISTPOINT, 23),

  /* This points to a linked list of post entries, struct curl_httppost */
  CROS_CURLOPT(CROS_CURLOPT_HTTPPOST, CROS_CURLOPTTYPE_OBJECTPOINT, 24),

  /* name of the file keeping your private SSL-certificate */
  CROS_CURLOPT(CROS_CURLOPT_SSLCERT, CROS_CURLOPTTYPE_STRINGPOINT, 25),

  /* password for the SSL or SSH private key */
  CROS_CURLOPT(CROS_CURLOPT_KEYPASSWD, CROS_CURLOPTTYPE_STRINGPOINT, 26),

  /* send TYPE parameter? */
  CROS_CURLOPT(CROS_CURLOPT_CRLF, CROS_CURLOPTTYPE_LONG, 27),

  /* send linked-list of QUOTE commands */
  CROS_CURLOPT(CROS_CURLOPT_QUOTE, CROS_CURLOPTTYPE_SLISTPOINT, 28),

  /* send FILE * or void * to store headers to, if you use a callback it
     is simply passed to the callback unmodified */
  CROS_CURLOPT(CROS_CURLOPT_HEADERDATA, CROS_CURLOPTTYPE_CBPOINT, 29),

  /* point to a file to read the initial cookies from, also enables
     "cookie awareness" */
  CROS_CURLOPT(CROS_CURLOPT_COOKIEFILE, CROS_CURLOPTTYPE_STRINGPOINT, 31),

  /* What version to specifically try to use.
     See CURL_SSLVERSION defines below. */
  CROS_CURLOPT(CROS_CURLOPT_SSLVERSION, CROS_CURLOPTTYPE_VALUES, 32),

  /* What kind of HTTP time condition to use, see defines */
  CROS_CURLOPT(CROS_CURLOPT_TIMECONDITION, CROS_CURLOPTTYPE_VALUES, 33),

  /* Time to use with the above condition. Specified in number of seconds
     since 1 Jan 1970 */
  CROS_CURLOPT(CROS_CURLOPT_TIMEVALUE, CROS_CURLOPTTYPE_LONG, 34),

  /* 35 = OBSOLETE */

  /* Custom request, for customizing the get command like
     HTTP: DELETE, TRACE and others
     FTP: to use a different list command
     */
  CROS_CURLOPT(CROS_CURLOPT_CUSTOMREQUEST, CROS_CURLOPTTYPE_STRINGPOINT, 36),

  /* FILE handle to use instead of stderr */
  CROS_CURLOPT(CROS_CURLOPT_STDERR, CROS_CURLOPTTYPE_OBJECTPOINT, 37),

  /* 38 is not used */

  /* send linked-list of post-transfer QUOTE commands */
  CROS_CURLOPT(CROS_CURLOPT_POSTQUOTE, CROS_CURLOPTTYPE_SLISTPOINT, 39),

  /* OBSOLETE, do not use! */
  CROS_CURLOPT(CROS_CURLOPT_OBSOLETE40, CROS_CURLOPTTYPE_OBJECTPOINT, 40),

  /* talk a lot */
  CROS_CURLOPT(CROS_CURLOPT_VERBOSE, CROS_CURLOPTTYPE_LONG, 41),

  /* throw the header out too */
  CROS_CURLOPT(CROS_CURLOPT_HEADER, CROS_CURLOPTTYPE_LONG, 42),

  /* shut off the progress meter */
  CROS_CURLOPT(CROS_CURLOPT_NOPROGRESS, CROS_CURLOPTTYPE_LONG, 43),

  /* use HEAD to get http document */
  CROS_CURLOPT(CROS_CURLOPT_NOBODY, CROS_CURLOPTTYPE_LONG, 44),

  /* no output on http error codes >= 400 */
  CROS_CURLOPT(CROS_CURLOPT_FAILONERROR, CROS_CURLOPTTYPE_LONG, 45),

  /* this is an upload */
  CROS_CURLOPT(CROS_CURLOPT_UPLOAD, CROS_CURLOPTTYPE_LONG, 46),

  /* HTTP POST method */
  CROS_CURLOPT(CROS_CURLOPT_POST, CROS_CURLOPTTYPE_LONG, 47),

  /* bare names when listing directories */
  CROS_CURLOPT(CROS_CURLOPT_DIRLISTONLY, CROS_CURLOPTTYPE_LONG, 48),

  /* Append instead of overwrite on upload! */
  CROS_CURLOPT(CROS_CURLOPT_APPEND, CROS_CURLOPTTYPE_LONG, 50),

  /* Specify whether to read the user+password from the .netrc or the URL.
   * This must be one of the CURL_NETRC_* enums below. */
  CROS_CURLOPT(CROS_CURLOPT_NETRC, CROS_CURLOPTTYPE_VALUES, 51),

  /* use Location: Luke! */
  CROS_CURLOPT(CROS_CURLOPT_FOLLOWLOCATION, CROS_CURLOPTTYPE_LONG, 52),

  /* transfer data in text/ASCII format */
  CROS_CURLOPT(CROS_CURLOPT_TRANSFERTEXT, CROS_CURLOPTTYPE_LONG, 53),

  /* HTTP PUT */
  CROS_CURLOPT(CROS_CURLOPT_PUT, CROS_CURLOPTTYPE_LONG, 54),

  /* 55 = OBSOLETE */

  /* DEPRECATED
   * Function that will be called instead of the internal progress display
   * function. This function should be defined as the curl_progress_callback
   * prototype defines. */
  CROS_CURLOPT(CROS_CURLOPT_PROGRESSFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 56),

  /* Data passed to the CROS_CURLOPT_PROGRESSFUNCTION and CROS_CURLOPT_XFERINFOFUNCTION
     callbacks */
  CROS_CURLOPT(CROS_CURLOPT_XFERINFODATA, CROS_CURLOPTTYPE_CBPOINT, 57),
#define CROS_CURLOPT_PROGRESSDATA CROS_CURLOPT_XFERINFODATA

  /* We want the referrer field set automatically when following locations */
  CROS_CURLOPT(CROS_CURLOPT_AUTOREFERER, CROS_CURLOPTTYPE_LONG, 58),

  /* Port of the proxy, can be set in the proxy string as well with:
     "[host]:[port]" */
  CROS_CURLOPT(CROS_CURLOPT_PROXYPORT, CROS_CURLOPTTYPE_LONG, 59),

  /* size of the POST input data, if strlen() is not good to use */
  CROS_CURLOPT(CROS_CURLOPT_POSTFIELDSIZE, CROS_CURLOPTTYPE_LONG, 60),

  /* tunnel non-http operations through a HTTP proxy */
  CROS_CURLOPT(CROS_CURLOPT_HTTPPROXYTUNNEL, CROS_CURLOPTTYPE_LONG, 61),

  /* Set the interface string to use as outgoing network interface */
  CROS_CURLOPT(CROS_CURLOPT_INTERFACE, CROS_CURLOPTTYPE_STRINGPOINT, 62),

  /* Set the krb4/5 security level, this also enables krb4/5 awareness.  This
   * is a string, 'clear', 'safe', 'confidential' or 'private'.  If the string
   * is set but doesn't match one of these, 'private' will be used.  */
  CROS_CURLOPT(CROS_CURLOPT_KRBLEVEL, CROS_CURLOPTTYPE_STRINGPOINT, 63),

  /* Set if we should verify the peer in ssl handshake, set 1 to verify. */
  CROS_CURLOPT(CROS_CURLOPT_SSL_VERIFYPEER, CROS_CURLOPTTYPE_LONG, 64),

  /* The CApath or CAfile used to validate the peer certificate
     this option is used only if SSL_VERIFYPEER is true */
  CROS_CURLOPT(CROS_CURLOPT_CAINFO, CROS_CURLOPTTYPE_STRINGPOINT, 65),

  /* 66 = OBSOLETE */
  /* 67 = OBSOLETE */

  /* Maximum number of http redirects to follow */
  CROS_CURLOPT(CROS_CURLOPT_MAXREDIRS, CROS_CURLOPTTYPE_LONG, 68),

  /* Pass a long set to 1 to get the date of the requested document (if
     possible)! Pass a zero to shut it off. */
  CROS_CURLOPT(CROS_CURLOPT_FILETIME, CROS_CURLOPTTYPE_LONG, 69),

  /* This points to a linked list of telnet options */
  CROS_CURLOPT(CROS_CURLOPT_TELNETOPTIONS, CROS_CURLOPTTYPE_SLISTPOINT, 70),

  /* Max amount of cached alive connections */
  CROS_CURLOPT(CROS_CURLOPT_MAXCONNECTS, CROS_CURLOPTTYPE_LONG, 71),

  /* OBSOLETE, do not use! */
  CROS_CURLOPT(CROS_CURLOPT_OBSOLETE72, CROS_CURLOPTTYPE_LONG, 72),

  /* 73 = OBSOLETE */

  /* Set to explicitly use a new connection for the upcoming transfer.
     Do not use this unless you're absolutely sure of this, as it makes the
     operation slower and is less friendly for the network. */
  CROS_CURLOPT(CROS_CURLOPT_FRESH_CONNECT, CROS_CURLOPTTYPE_LONG, 74),

  /* Set to explicitly forbid the upcoming transfer's connection to be re-used
     when done. Do not use this unless you're absolutely sure of this, as it
     makes the operation slower and is less friendly for the network. */
  CROS_CURLOPT(CROS_CURLOPT_FORBID_REUSE, CROS_CURLOPTTYPE_LONG, 75),

  /* Set to a file name that contains random data for libcurl to use to
     seed the random engine when doing SSL connects. */
  CROS_CURLOPT(CROS_CURLOPT_RANDOM_FILE, CROS_CURLOPTTYPE_STRINGPOINT, 76),

  /* Set to the Entropy Gathering Daemon socket pathname */
  CROS_CURLOPT(CROS_CURLOPT_EGDSOCKET, CROS_CURLOPTTYPE_STRINGPOINT, 77),

  /* Time-out connect operations after this amount of seconds, if connects are
     OK within this time, then fine... This only aborts the connect phase. */
  CROS_CURLOPT(CROS_CURLOPT_CONNECTTIMEOUT, CROS_CURLOPTTYPE_LONG, 78),

  /* Function that will be called to store headers (instead of fwrite). The
   * parameters will use fwrite() syntax, make sure to follow them. */
  CROS_CURLOPT(CROS_CURLOPT_HEADERFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 79),

  /* Set this to force the HTTP request to get back to GET. Only really usable
     if POST, PUT or a custom request have been used first.
   */
  CROS_CURLOPT(CROS_CURLOPT_HTTPGET, CROS_CURLOPTTYPE_LONG, 80),

  /* Set if we should verify the Common name from the peer certificate in ssl
   * handshake, set 1 to check existence, 2 to ensure that it matches the
   * provided hostname. */
  CROS_CURLOPT(CROS_CURLOPT_SSL_VERIFYHOST, CROS_CURLOPTTYPE_LONG, 81),

  /* Specify which file name to write all known cookies in after completed
     operation. Set file name to "-" (dash) to make it go to stdout. */
  CROS_CURLOPT(CROS_CURLOPT_COOKIEJAR, CROS_CURLOPTTYPE_STRINGPOINT, 82),

  /* Specify which SSL ciphers to use */
  CROS_CURLOPT(CROS_CURLOPT_SSL_CIPHER_LIST, CROS_CURLOPTTYPE_STRINGPOINT, 83),

  /* Specify which HTTP version to use! This must be set to one of the
     CURL_HTTP_VERSION* enums set below. */
  CROS_CURLOPT(CROS_CURLOPT_HTTP_VERSION, CROS_CURLOPTTYPE_VALUES, 84),

  /* Specifically switch on or off the FTP engine's use of the EPSV command. By
     default, that one will always be attempted before the more traditional
     PASV command. */
  CROS_CURLOPT(CROS_CURLOPT_FTP_USE_EPSV, CROS_CURLOPTTYPE_LONG, 85),

  /* type of the file keeping your SSL-certificate ("DER", "PEM", "ENG") */
  CROS_CURLOPT(CROS_CURLOPT_SSLCERTTYPE, CROS_CURLOPTTYPE_STRINGPOINT, 86),

  /* name of the file keeping your private SSL-key */
  CROS_CURLOPT(CROS_CURLOPT_SSLKEY, CROS_CURLOPTTYPE_STRINGPOINT, 87),

  /* type of the file keeping your private SSL-key ("DER", "PEM", "ENG") */
  CROS_CURLOPT(CROS_CURLOPT_SSLKEYTYPE, CROS_CURLOPTTYPE_STRINGPOINT, 88),

  /* crypto engine for the SSL-sub system */
  CROS_CURLOPT(CROS_CURLOPT_SSLENGINE, CROS_CURLOPTTYPE_STRINGPOINT, 89),

  /* set the crypto engine for the SSL-sub system as default
     the param has no meaning...
   */
  CROS_CURLOPT(CROS_CURLOPT_SSLENGINE_DEFAULT, CROS_CURLOPTTYPE_LONG, 90),

  /* Non-zero value means to use the global dns cache */
  /* DEPRECATED, do not use! */
  CROS_CURLOPT(CROS_CURLOPT_DNS_USE_GLOBAL_CACHE, CROS_CURLOPTTYPE_LONG, 91),

  /* DNS cache timeout */
  CROS_CURLOPT(CROS_CURLOPT_DNS_CACHE_TIMEOUT, CROS_CURLOPTTYPE_LONG, 92),

  /* send linked-list of pre-transfer QUOTE commands */
  CROS_CURLOPT(CROS_CURLOPT_PREQUOTE, CROS_CURLOPTTYPE_SLISTPOINT, 93),

  /* set the debug function */
  CROS_CURLOPT(CROS_CURLOPT_DEBUGFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 94),

  /* set the data for the debug function */
  CROS_CURLOPT(CROS_CURLOPT_DEBUGDATA, CROS_CURLOPTTYPE_CBPOINT, 95),

  /* mark this as start of a cookie session */
  CROS_CURLOPT(CROS_CURLOPT_COOKIESESSION, CROS_CURLOPTTYPE_LONG, 96),

  /* The CApath directory used to validate the peer certificate
     this option is used only if SSL_VERIFYPEER is true */
  CROS_CURLOPT(CROS_CURLOPT_CAPATH, CROS_CURLOPTTYPE_STRINGPOINT, 97),

  /* Instruct libcurl to use a smaller receive buffer */
  CROS_CURLOPT(CROS_CURLOPT_BUFFERSIZE, CROS_CURLOPTTYPE_LONG, 98),

  /* Instruct libcurl to not use any signal/alarm handlers, even when using
     timeouts. This option is useful for multi-threaded applications.
     See libcurl-the-guide for more background information. */
  CROS_CURLOPT(CROS_CURLOPT_NOSIGNAL, CROS_CURLOPTTYPE_LONG, 99),

  /* Provide a CURLShare for mutexing non-ts data */
  CROS_CURLOPT(CROS_CURLOPT_SHARE, CROS_CURLOPTTYPE_OBJECTPOINT, 100),

  /* indicates type of proxy. accepted values are CURLPROXY_HTTP (default),
     CURLPROXY_HTTPS, CURLPROXY_SOCKS4, CURLPROXY_SOCKS4A and
     CURLPROXY_SOCKS5. */
  CROS_CURLOPT(CROS_CURLOPT_PROXYTYPE, CROS_CURLOPTTYPE_VALUES, 101),

  /* Set the Accept-Encoding string. Use this to tell a server you would like
     the response to be compressed. Before 7.21.6, this was known as
     CROS_CURLOPT_ENCODING */
  CROS_CURLOPT(CROS_CURLOPT_ACCEPT_ENCODING, CROS_CURLOPTTYPE_STRINGPOINT, 102),

  /* Set pointer to private data */
  CROS_CURLOPT(CROS_CURLOPT_PRIVATE, CROS_CURLOPTTYPE_OBJECTPOINT, 103),

  /* Set aliases for HTTP 200 in the HTTP Response header */
  CROS_CURLOPT(CROS_CURLOPT_HTTP200ALIASES, CROS_CURLOPTTYPE_SLISTPOINT, 104),

  /* Continue to send authentication (user+password) when following locations,
     even when hostname changed. This can potentially send off the name
     and password to whatever host the server decides. */
  CROS_CURLOPT(CROS_CURLOPT_UNRESTRICTED_AUTH, CROS_CURLOPTTYPE_LONG, 105),

  /* Specifically switch on or off the FTP engine's use of the EPRT command (
     it also disables the LPRT attempt). By default, those ones will always be
     attempted before the good old traditional PORT command. */
  CROS_CURLOPT(CROS_CURLOPT_FTP_USE_EPRT, CROS_CURLOPTTYPE_LONG, 106),

  /* Set this to a bitmask value to enable the particular authentications
     methods you like. Use this in combination with CROS_CURLOPT_USERPWD.
     Note that setting multiple bits may cause extra network round-trips. */
  CROS_CURLOPT(CROS_CURLOPT_HTTPAUTH, CROS_CURLOPTTYPE_VALUES, 107),

  /* Set the ssl context callback function, currently only for OpenSSL or
     WolfSSL ssl_ctx, or mbedTLS mbedtls_ssl_config in the second argument.
     The function must match the curl_ssl_ctx_callback prototype. */
  CROS_CURLOPT(CROS_CURLOPT_SSL_CTX_FUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 108),

  /* Set the userdata for the ssl context callback function's third
     argument */
  CROS_CURLOPT(CROS_CURLOPT_SSL_CTX_DATA, CROS_CURLOPTTYPE_CBPOINT, 109),

  /* FTP Option that causes missing dirs to be created on the remote server.
     In 7.19.4 we introduced the convenience enums for this option using the
     CURLFTP_CREATE_DIR prefix.
  */
  CROS_CURLOPT(CROS_CURLOPT_FTP_CREATE_MISSING_DIRS, CROS_CURLOPTTYPE_LONG, 110),

  /* Set this to a bitmask value to enable the particular authentications
     methods you like. Use this in combination with CROS_CURLOPT_PROXYUSERPWD.
     Note that setting multiple bits may cause extra network round-trips. */
  CROS_CURLOPT(CROS_CURLOPT_PROXYAUTH, CROS_CURLOPTTYPE_VALUES, 111),

  /* FTP option that changes the timeout, in seconds, associated with
     getting a response.  This is different from transfer timeout time and
     essentially places a demand on the FTP server to acknowledge commands
     in a timely manner. */
  CROS_CURLOPT(CROS_CURLOPT_FTP_RESPONSE_TIMEOUT, CROS_CURLOPTTYPE_LONG, 112),
#define CROS_CURLOPT_SERVER_RESPONSE_TIMEOUT CROS_CURLOPT_FTP_RESPONSE_TIMEOUT

  /* Set this option to one of the CURL_IPRESOLVE_* defines (see below) to
     tell libcurl to resolve names to those IP versions only. This only has
     affect on systems with support for more than one, i.e IPv4 _and_ IPv6. */
  CROS_CURLOPT(CROS_CURLOPT_IPRESOLVE, CROS_CURLOPTTYPE_VALUES, 113),

  /* Set this option to limit the size of a file that will be downloaded from
     an HTTP or FTP server.

     Note there is also _LARGE version which adds large file support for
     platforms which have larger off_t sizes.  See MAXFILESIZE_LARGE below. */
  CROS_CURLOPT(CROS_CURLOPT_MAXFILESIZE, CROS_CURLOPTTYPE_LONG, 114),

  /* See the comment for INFILESIZE above, but in short, specifies
   * the size of the file being uploaded.  -1 means unknown.
   */
  CROS_CURLOPT(CROS_CURLOPT_INFILESIZE_LARGE, CROS_CURLOPTTYPE_OFF_T, 115),

  /* Sets the continuation offset.  There is also a CROS_CURLOPTTYPE_LONG version
   * of this; look above for RESUME_FROM.
   */
  CROS_CURLOPT(CROS_CURLOPT_RESUME_FROM_LARGE, CROS_CURLOPTTYPE_OFF_T, 116),

  /* Sets the maximum size of data that will be downloaded from
   * an HTTP or FTP server.  See MAXFILESIZE above for the LONG version.
   */
  CROS_CURLOPT(CROS_CURLOPT_MAXFILESIZE_LARGE, CROS_CURLOPTTYPE_OFF_T, 117),

  /* Set this option to the file name of your .netrc file you want libcurl
     to parse (using the CROS_CURLOPT_NETRC option). If not set, libcurl will do
     a poor attempt to find the user's home directory and check for a .netrc
     file in there. */
  CROS_CURLOPT(CROS_CURLOPT_NETRC_FILE, CROS_CURLOPTTYPE_STRINGPOINT, 118),

  /* Enable SSL/TLS for FTP, pick one of:
     CURLUSESSL_TRY     - try using SSL, proceed anyway otherwise
     CURLUSESSL_CONTROL - SSL for the control connection or fail
     CURLUSESSL_ALL     - SSL for all communication or fail
  */
  CROS_CURLOPT(CROS_CURLOPT_USE_SSL, CROS_CURLOPTTYPE_VALUES, 119),

  /* The _LARGE version of the standard POSTFIELDSIZE option */
  CROS_CURLOPT(CROS_CURLOPT_POSTFIELDSIZE_LARGE, CROS_CURLOPTTYPE_OFF_T, 120),

  /* Enable/disable the TCP Nagle algorithm */
  CROS_CURLOPT(CROS_CURLOPT_TCP_NODELAY, CROS_CURLOPTTYPE_LONG, 121),

  /* 122 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
  /* 123 OBSOLETE. Gone in 7.16.0 */
  /* 124 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
  /* 125 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
  /* 126 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
  /* 127 OBSOLETE. Gone in 7.16.0 */
  /* 128 OBSOLETE. Gone in 7.16.0 */

  /* When FTP over SSL/TLS is selected (with CROS_CURLOPT_USE_SSL), this option
     can be used to change libcurl's default action which is to first try
     "AUTH SSL" and then "AUTH TLS" in this order, and proceed when a OK
     response has been received.

     Available parameters are:
     CURLFTPAUTH_DEFAULT - let libcurl decide
     CURLFTPAUTH_SSL     - try "AUTH SSL" first, then TLS
     CURLFTPAUTH_TLS     - try "AUTH TLS" first, then SSL
  */
  CROS_CURLOPT(CROS_CURLOPT_FTPSSLAUTH, CROS_CURLOPTTYPE_VALUES, 129),

  CROS_CURLOPT(CROS_CURLOPT_IOCTLFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 130),
  CROS_CURLOPT(CROS_CURLOPT_IOCTLDATA, CROS_CURLOPTTYPE_CBPOINT, 131),

  /* 132 OBSOLETE. Gone in 7.16.0 */
  /* 133 OBSOLETE. Gone in 7.16.0 */

  /* null-terminated string for pass on to the FTP server when asked for
     "account" info */
  CROS_CURLOPT(CROS_CURLOPT_FTP_ACCOUNT, CROS_CURLOPTTYPE_STRINGPOINT, 134),

  /* feed cookie into cookie engine */
  CROS_CURLOPT(CROS_CURLOPT_COOKIELIST, CROS_CURLOPTTYPE_STRINGPOINT, 135),

  /* ignore Content-Length */
  CROS_CURLOPT(CROS_CURLOPT_IGNORE_CONTENT_LENGTH, CROS_CURLOPTTYPE_LONG, 136),

  /* Set to non-zero to skip the IP address received in a 227 PASV FTP server
     response. Typically used for FTP-SSL purposes but is not restricted to
     that. libcurl will then instead use the same IP address it used for the
     control connection. */
  CROS_CURLOPT(CROS_CURLOPT_FTP_SKIP_PASV_IP, CROS_CURLOPTTYPE_LONG, 137),

  /* Select "file method" to use when doing FTP, see the curl_ftpmethod
     above. */
  CROS_CURLOPT(CROS_CURLOPT_FTP_FILEMETHOD, CROS_CURLOPTTYPE_VALUES, 138),

  /* Local port number to bind the socket to */
  CROS_CURLOPT(CROS_CURLOPT_LOCALPORT, CROS_CURLOPTTYPE_LONG, 139),

  /* Number of ports to try, including the first one set with LOCALPORT.
     Thus, setting it to 1 will make no additional attempts but the first.
  */
  CROS_CURLOPT(CROS_CURLOPT_LOCALPORTRANGE, CROS_CURLOPTTYPE_LONG, 140),

  /* no transfer, set up connection and let application use the socket by
     extracting it with CURLINFO_LASTSOCKET */
  CROS_CURLOPT(CROS_CURLOPT_CONNECT_ONLY, CROS_CURLOPTTYPE_LONG, 141),

  /* Function that will be called to convert from the
     network encoding (instead of using the iconv calls in libcurl) */
  CROS_CURLOPT(CROS_CURLOPT_CONV_FROM_NETWORK_FUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 142),

  /* Function that will be called to convert to the
     network encoding (instead of using the iconv calls in libcurl) */
  CROS_CURLOPT(CROS_CURLOPT_CONV_TO_NETWORK_FUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 143),

  /* Function that will be called to convert from UTF8
     (instead of using the iconv calls in libcurl)
     Note that this is used only for SSL certificate processing */
  CROS_CURLOPT(CROS_CURLOPT_CONV_FROM_UTF8_FUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 144),

  /* if the connection proceeds too quickly then need to slow it down */
  /* limit-rate: maximum number of bytes per second to send or receive */
  CROS_CURLOPT(CROS_CURLOPT_MAX_SEND_SPEED_LARGE, CROS_CURLOPTTYPE_OFF_T, 145),
  CROS_CURLOPT(CROS_CURLOPT_MAX_RECV_SPEED_LARGE, CROS_CURLOPTTYPE_OFF_T, 146),

  /* Pointer to command string to send if USER/PASS fails. */
  CROS_CURLOPT(CROS_CURLOPT_FTP_ALTERNATIVE_TO_USER, CROS_CURLOPTTYPE_STRINGPOINT, 147),

  /* callback function for setting socket options */
  CROS_CURLOPT(CROS_CURLOPT_SOCKOPTFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 148),
  CROS_CURLOPT(CROS_CURLOPT_SOCKOPTDATA, CROS_CURLOPTTYPE_CBPOINT, 149),

  /* set to 0 to disable session ID re-use for this transfer, default is
     enabled (== 1) */
  CROS_CURLOPT(CROS_CURLOPT_SSL_SESSIONID_CACHE, CROS_CURLOPTTYPE_LONG, 150),

  /* allowed SSH authentication methods */
  CROS_CURLOPT(CROS_CURLOPT_SSH_AUTH_TYPES, CROS_CURLOPTTYPE_VALUES, 151),

  /* Used by scp/sftp to do public/private key authentication */
  CROS_CURLOPT(CROS_CURLOPT_SSH_PUBLIC_KEYFILE, CROS_CURLOPTTYPE_STRINGPOINT, 152),
  CROS_CURLOPT(CROS_CURLOPT_SSH_PRIVATE_KEYFILE, CROS_CURLOPTTYPE_STRINGPOINT, 153),

  /* Send CCC (Clear Command Channel) after authentication */
  CROS_CURLOPT(CROS_CURLOPT_FTP_SSL_CCC, CROS_CURLOPTTYPE_LONG, 154),

  /* Same as TIMEOUT and CONNECTTIMEOUT, but with ms resolution */
  CROS_CURLOPT(CROS_CURLOPT_TIMEOUT_MS, CROS_CURLOPTTYPE_LONG, 155),
  CROS_CURLOPT(CROS_CURLOPT_CONNECTTIMEOUT_MS, CROS_CURLOPTTYPE_LONG, 156),

  /* set to zero to disable the libcurl's decoding and thus pass the raw body
     data to the application even when it is encoded/compressed */
  CROS_CURLOPT(CROS_CURLOPT_HTTP_TRANSFER_DECODING, CROS_CURLOPTTYPE_LONG, 157),
  CROS_CURLOPT(CROS_CURLOPT_HTTP_CONTENT_DECODING, CROS_CURLOPTTYPE_LONG, 158),

  /* Permission used when creating new files and directories on the remote
     server for protocols that support it, SFTP/SCP/FILE */
  CROS_CURLOPT(CROS_CURLOPT_NEW_FILE_PERMS, CROS_CURLOPTTYPE_LONG, 159),
  CROS_CURLOPT(CROS_CURLOPT_NEW_DIRECTORY_PERMS, CROS_CURLOPTTYPE_LONG, 160),

  /* Set the behaviour of POST when redirecting. Values must be set to one
     of CURL_REDIR* defines below. This used to be called CROS_CURLOPT_POST301 */
  CROS_CURLOPT(CROS_CURLOPT_POSTREDIR, CROS_CURLOPTTYPE_VALUES, 161),

  /* used by scp/sftp to verify the host's public key */
  CROS_CURLOPT(CROS_CURLOPT_SSH_HOST_PUBLIC_KEY_MD5, CROS_CURLOPTTYPE_STRINGPOINT, 162),

  /* Callback function for opening socket (instead of socket(2)). Optionally,
     callback is able change the address or refuse to connect returning
     CURL_SOCKET_BAD.  The callback should have type
     curl_opensocket_callback */
  CROS_CURLOPT(CROS_CURLOPT_OPENSOCKETFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 163),
  CROS_CURLOPT(CROS_CURLOPT_OPENSOCKETDATA, CROS_CURLOPTTYPE_CBPOINT, 164),

  /* POST volatile input fields. */
  CROS_CURLOPT(CROS_CURLOPT_COPYPOSTFIELDS, CROS_CURLOPTTYPE_OBJECTPOINT, 165),

  /* set transfer mode (;type=<a|i>) when doing FTP via an HTTP proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_TRANSFER_MODE, CROS_CURLOPTTYPE_LONG, 166),

  /* Callback function for seeking in the input stream */
  CROS_CURLOPT(CROS_CURLOPT_SEEKFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 167),
  CROS_CURLOPT(CROS_CURLOPT_SEEKDATA, CROS_CURLOPTTYPE_CBPOINT, 168),

  /* CRL file */
  CROS_CURLOPT(CROS_CURLOPT_CRLFILE, CROS_CURLOPTTYPE_STRINGPOINT, 169),

  /* Issuer certificate */
  CROS_CURLOPT(CROS_CURLOPT_ISSUERCERT, CROS_CURLOPTTYPE_STRINGPOINT, 170),

  /* (IPv6) Address scope */
  CROS_CURLOPT(CROS_CURLOPT_ADDRESS_SCOPE, CROS_CURLOPTTYPE_LONG, 171),

  /* Collect certificate chain info and allow it to get retrievable with
     CURLINFO_CERTINFO after the transfer is complete. */
  CROS_CURLOPT(CROS_CURLOPT_CERTINFO, CROS_CURLOPTTYPE_LONG, 172),

  /* "name" and "pwd" to use when fetching. */
  CROS_CURLOPT(CROS_CURLOPT_USERNAME, CROS_CURLOPTTYPE_STRINGPOINT, 173),
  CROS_CURLOPT(CROS_CURLOPT_PASSWORD, CROS_CURLOPTTYPE_STRINGPOINT, 174),

  /* "name" and "pwd" to use with Proxy when fetching. */
  CROS_CURLOPT(CROS_CURLOPT_PROXYUSERNAME, CROS_CURLOPTTYPE_STRINGPOINT, 175),
  CROS_CURLOPT(CROS_CURLOPT_PROXYPASSWORD, CROS_CURLOPTTYPE_STRINGPOINT, 176),

  /* Comma separated list of hostnames defining no-proxy zones. These should
     match both hostnames directly, and hostnames within a domain. For
     example, local.com will match local.com and www.local.com, but NOT
     notlocal.com or www.notlocal.com. For compatibility with other
     implementations of this, .local.com will be considered to be the same as
     local.com. A single * is the only valid wildcard, and effectively
     disables the use of proxy. */
  CROS_CURLOPT(CROS_CURLOPT_NOPROXY, CROS_CURLOPTTYPE_STRINGPOINT, 177),

  /* block size for TFTP transfers */
  CROS_CURLOPT(CROS_CURLOPT_TFTP_BLKSIZE, CROS_CURLOPTTYPE_LONG, 178),

  /* Socks Service */
  /* DEPRECATED, do not use! */
  CROS_CURLOPT(CROS_CURLOPT_SOCKS5_GSSAPI_SERVICE, CROS_CURLOPTTYPE_STRINGPOINT, 179),

  /* Socks Service */
  CROS_CURLOPT(CROS_CURLOPT_SOCKS5_GSSAPI_NEC, CROS_CURLOPTTYPE_LONG, 180),

  /* set the bitmask for the protocols that are allowed to be used for the
     transfer, which thus helps the app which takes URLs from users or other
     external inputs and want to restrict what protocol(s) to deal
     with. Defaults to CURLPROTO_ALL. */
  CROS_CURLOPT(CROS_CURLOPT_PROTOCOLS, CROS_CURLOPTTYPE_LONG, 181),

  /* set the bitmask for the protocols that libcurl is allowed to follow to,
     as a subset of the CROS_CURLOPT_PROTOCOLS ones. That means the protocol needs
     to be set in both bitmasks to be allowed to get redirected to. */
  CROS_CURLOPT(CROS_CURLOPT_REDIR_PROTOCOLS, CROS_CURLOPTTYPE_LONG, 182),

  /* set the SSH knownhost file name to use */
  CROS_CURLOPT(CROS_CURLOPT_SSH_KNOWNHOSTS, CROS_CURLOPTTYPE_STRINGPOINT, 183),

  /* set the SSH host key callback, must point to a curl_sshkeycallback
     function */
  CROS_CURLOPT(CROS_CURLOPT_SSH_KEYFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 184),

  /* set the SSH host key callback custom pointer */
  CROS_CURLOPT(CROS_CURLOPT_SSH_KEYDATA, CROS_CURLOPTTYPE_CBPOINT, 185),

  /* set the SMTP mail originator */
  CROS_CURLOPT(CROS_CURLOPT_MAIL_FROM, CROS_CURLOPTTYPE_STRINGPOINT, 186),

  /* set the list of SMTP mail receiver(s) */
  CROS_CURLOPT(CROS_CURLOPT_MAIL_RCPT, CROS_CURLOPTTYPE_SLISTPOINT, 187),

  /* FTP: send PRET before PASV */
  CROS_CURLOPT(CROS_CURLOPT_FTP_USE_PRET, CROS_CURLOPTTYPE_LONG, 188),

  /* RTSP request method (OPTIONS, SETUP, PLAY, etc...) */
  CROS_CURLOPT(CROS_CURLOPT_RTSP_REQUEST, CROS_CURLOPTTYPE_VALUES, 189),

  /* The RTSP session identifier */
  CROS_CURLOPT(CROS_CURLOPT_RTSP_SESSION_ID, CROS_CURLOPTTYPE_STRINGPOINT, 190),

  /* The RTSP stream URI */
  CROS_CURLOPT(CROS_CURLOPT_RTSP_STREAM_URI, CROS_CURLOPTTYPE_STRINGPOINT, 191),

  /* The Transport: header to use in RTSP requests */
  CROS_CURLOPT(CROS_CURLOPT_RTSP_TRANSPORT, CROS_CURLOPTTYPE_STRINGPOINT, 192),

  /* Manually initialize the client RTSP CSeq for this handle */
  CROS_CURLOPT(CROS_CURLOPT_RTSP_CLIENT_CSEQ, CROS_CURLOPTTYPE_LONG, 193),

  /* Manually initialize the server RTSP CSeq for this handle */
  CROS_CURLOPT(CROS_CURLOPT_RTSP_SERVER_CSEQ, CROS_CURLOPTTYPE_LONG, 194),

  /* The stream to pass to INTERLEAVEFUNCTION. */
  CROS_CURLOPT(CROS_CURLOPT_INTERLEAVEDATA, CROS_CURLOPTTYPE_CBPOINT, 195),

  /* Let the application define a custom write method for RTP data */
  CROS_CURLOPT(CROS_CURLOPT_INTERLEAVEFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 196),

  /* Turn on wildcard matching */
  CROS_CURLOPT(CROS_CURLOPT_WILDCARDMATCH, CROS_CURLOPTTYPE_LONG, 197),

  /* Directory matching callback called before downloading of an
     individual file (chunk) started */
  CROS_CURLOPT(CROS_CURLOPT_CHUNK_BGN_FUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 198),

  /* Directory matching callback called after the file (chunk)
     was downloaded, or skipped */
  CROS_CURLOPT(CROS_CURLOPT_CHUNK_END_FUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 199),

  /* Change match (fnmatch-like) callback for wildcard matching */
  CROS_CURLOPT(CROS_CURLOPT_FNMATCH_FUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 200),

  /* Let the application define custom chunk data pointer */
  CROS_CURLOPT(CROS_CURLOPT_CHUNK_DATA, CROS_CURLOPTTYPE_CBPOINT, 201),

  /* FNMATCH_FUNCTION user pointer */
  CROS_CURLOPT(CROS_CURLOPT_FNMATCH_DATA, CROS_CURLOPTTYPE_CBPOINT, 202),

  /* send linked-list of name:port:address sets */
  CROS_CURLOPT(CROS_CURLOPT_RESOLVE, CROS_CURLOPTTYPE_SLISTPOINT, 203),

  /* Set a username for authenticated TLS */
  CROS_CURLOPT(CROS_CURLOPT_TLSAUTH_USERNAME, CROS_CURLOPTTYPE_STRINGPOINT, 204),

  /* Set a password for authenticated TLS */
  CROS_CURLOPT(CROS_CURLOPT_TLSAUTH_PASSWORD, CROS_CURLOPTTYPE_STRINGPOINT, 205),

  /* Set authentication type for authenticated TLS */
  CROS_CURLOPT(CROS_CURLOPT_TLSAUTH_TYPE, CROS_CURLOPTTYPE_STRINGPOINT, 206),

  /* Set to 1 to enable the "TE:" header in HTTP requests to ask for
     compressed transfer-encoded responses. Set to 0 to disable the use of TE:
     in outgoing requests. The current default is 0, but it might change in a
     future libcurl release.

     libcurl will ask for the compressed methods it knows of, and if that
     isn't any, it will not ask for transfer-encoding at all even if this
     option is set to 1.

  */
  CROS_CURLOPT(CROS_CURLOPT_TRANSFER_ENCODING, CROS_CURLOPTTYPE_LONG, 207),

  /* Callback function for closing socket (instead of close(2)). The callback
     should have type curl_closesocket_callback */
  CROS_CURLOPT(CROS_CURLOPT_CLOSESOCKETFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 208),
  CROS_CURLOPT(CROS_CURLOPT_CLOSESOCKETDATA, CROS_CURLOPTTYPE_CBPOINT, 209),

  /* allow GSSAPI credential delegation */
  CROS_CURLOPT(CROS_CURLOPT_GSSAPI_DELEGATION, CROS_CURLOPTTYPE_VALUES, 210),

  /* Set the name servers to use for DNS resolution */
  CROS_CURLOPT(CROS_CURLOPT_DNS_SERVERS, CROS_CURLOPTTYPE_STRINGPOINT, 211),

  /* Time-out accept operations (currently for FTP only) after this amount
     of milliseconds. */
  CROS_CURLOPT(CROS_CURLOPT_ACCEPTTIMEOUT_MS, CROS_CURLOPTTYPE_LONG, 212),

  /* Set TCP keepalive */
  CROS_CURLOPT(CROS_CURLOPT_TCP_KEEPALIVE, CROS_CURLOPTTYPE_LONG, 213),

  /* non-universal keepalive knobs (Linux, AIX, HP-UX, more) */
  CROS_CURLOPT(CROS_CURLOPT_TCP_KEEPIDLE, CROS_CURLOPTTYPE_LONG, 214),
  CROS_CURLOPT(CROS_CURLOPT_TCP_KEEPINTVL, CROS_CURLOPTTYPE_LONG, 215),

  /* Enable/disable specific SSL features with a bitmask, see CURLSSLOPT_* */
  CROS_CURLOPT(CROS_CURLOPT_SSL_OPTIONS, CROS_CURLOPTTYPE_VALUES, 216),

  /* Set the SMTP auth originator */
  CROS_CURLOPT(CROS_CURLOPT_MAIL_AUTH, CROS_CURLOPTTYPE_STRINGPOINT, 217),

  /* Enable/disable SASL initial response */
  CROS_CURLOPT(CROS_CURLOPT_SASL_IR, CROS_CURLOPTTYPE_LONG, 218),

  /* Function that will be called instead of the internal progress display
   * function. This function should be defined as the curl_xferinfo_callback
   * prototype defines. (Deprecates CROS_CURLOPT_PROGRESSFUNCTION) */
  CROS_CURLOPT(CROS_CURLOPT_XFERINFOFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 219),

  /* The XOAUTH2 bearer token */
  CROS_CURLOPT(CROS_CURLOPT_XOAUTH2_BEARER, CROS_CURLOPTTYPE_STRINGPOINT, 220),

  /* Set the interface string to use as outgoing network
   * interface for DNS requests.
   * Only supported by the c-ares DNS backend */
  CROS_CURLOPT(CROS_CURLOPT_DNS_INTERFACE, CROS_CURLOPTTYPE_STRINGPOINT, 221),

  /* Set the local IPv4 address to use for outgoing DNS requests.
   * Only supported by the c-ares DNS backend */
  CROS_CURLOPT(CROS_CURLOPT_DNS_LOCAL_IP4, CROS_CURLOPTTYPE_STRINGPOINT, 222),

  /* Set the local IPv6 address to use for outgoing DNS requests.
   * Only supported by the c-ares DNS backend */
  CROS_CURLOPT(CROS_CURLOPT_DNS_LOCAL_IP6, CROS_CURLOPTTYPE_STRINGPOINT, 223),

  /* Set authentication options directly */
  CROS_CURLOPT(CROS_CURLOPT_LOGIN_OPTIONS, CROS_CURLOPTTYPE_STRINGPOINT, 224),

  /* Enable/disable TLS NPN extension (http2 over ssl might fail without) */
  CROS_CURLOPT(CROS_CURLOPT_SSL_ENABLE_NPN, CROS_CURLOPTTYPE_LONG, 225),

  /* Enable/disable TLS ALPN extension (http2 over ssl might fail without) */
  CROS_CURLOPT(CROS_CURLOPT_SSL_ENABLE_ALPN, CROS_CURLOPTTYPE_LONG, 226),

  /* Time to wait for a response to a HTTP request containing an
   * Expect: 100-continue header before sending the data anyway. */
  CROS_CURLOPT(CROS_CURLOPT_EXPECT_100_TIMEOUT_MS, CROS_CURLOPTTYPE_LONG, 227),

  /* This points to a linked list of headers used for proxy requests only,
     struct curl_slist kind */
  CROS_CURLOPT(CROS_CURLOPT_PROXYHEADER, CROS_CURLOPTTYPE_SLISTPOINT, 228),

  /* Pass in a bitmask of "header options" */
  CROS_CURLOPT(CROS_CURLOPT_HEADEROPT, CROS_CURLOPTTYPE_VALUES, 229),

  /* The public key in DER form used to validate the peer public key
     this option is used only if SSL_VERIFYPEER is true */
  CROS_CURLOPT(CROS_CURLOPT_PINNEDPUBLICKEY, CROS_CURLOPTTYPE_STRINGPOINT, 230),

  /* Path to Unix domain socket */
  CROS_CURLOPT(CROS_CURLOPT_UNIX_SOCKET_PATH, CROS_CURLOPTTYPE_STRINGPOINT, 231),

  /* Set if we should verify the certificate status. */
  CROS_CURLOPT(CROS_CURLOPT_SSL_VERIFYSTATUS, CROS_CURLOPTTYPE_LONG, 232),

  /* Set if we should enable TLS false start. */
  CROS_CURLOPT(CROS_CURLOPT_SSL_FALSESTART, CROS_CURLOPTTYPE_LONG, 233),

  /* Do not squash dot-dot sequences */
  CROS_CURLOPT(CROS_CURLOPT_PATH_AS_IS, CROS_CURLOPTTYPE_LONG, 234),

  /* Proxy Service Name */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SERVICE_NAME, CROS_CURLOPTTYPE_STRINGPOINT, 235),

  /* Service Name */
  CROS_CURLOPT(CROS_CURLOPT_SERVICE_NAME, CROS_CURLOPTTYPE_STRINGPOINT, 236),

  /* Wait/don't wait for pipe/mutex to clarify */
  CROS_CURLOPT(CROS_CURLOPT_PIPEWAIT, CROS_CURLOPTTYPE_LONG, 237),

  /* Set the protocol used when curl is given a URL without a protocol */
  CROS_CURLOPT(CROS_CURLOPT_DEFAULT_PROTOCOL, CROS_CURLOPTTYPE_STRINGPOINT, 238),

  /* Set stream weight, 1 - 256 (default is 16) */
  CROS_CURLOPT(CROS_CURLOPT_STREAM_WEIGHT, CROS_CURLOPTTYPE_LONG, 239),

  /* Set stream dependency on another CURL handle */
  CROS_CURLOPT(CROS_CURLOPT_STREAM_DEPENDS, CROS_CURLOPTTYPE_OBJECTPOINT, 240),

  /* Set E-xclusive stream dependency on another CURL handle */
  CROS_CURLOPT(CROS_CURLOPT_STREAM_DEPENDS_E, CROS_CURLOPTTYPE_OBJECTPOINT, 241),

  /* Do not send any tftp option requests to the server */
  CROS_CURLOPT(CROS_CURLOPT_TFTP_NO_OPTIONS, CROS_CURLOPTTYPE_LONG, 242),

  /* Linked-list of host:port:connect-to-host:connect-to-port,
     overrides the URL's host:port (only for the network layer) */
  CROS_CURLOPT(CROS_CURLOPT_CONNECT_TO, CROS_CURLOPTTYPE_SLISTPOINT, 243),

  /* Set TCP Fast Open */
  CROS_CURLOPT(CROS_CURLOPT_TCP_FASTOPEN, CROS_CURLOPTTYPE_LONG, 244),

  /* Continue to send data if the server responds early with an
   * HTTP status code >= 300 */
  CROS_CURLOPT(CROS_CURLOPT_KEEP_SENDING_ON_ERROR, CROS_CURLOPTTYPE_LONG, 245),

  /* The CApath or CAfile used to validate the proxy certificate
     this option is used only if PROXY_SSL_VERIFYPEER is true */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_CAINFO, CROS_CURLOPTTYPE_STRINGPOINT, 246),

  /* The CApath directory used to validate the proxy certificate
     this option is used only if PROXY_SSL_VERIFYPEER is true */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_CAPATH, CROS_CURLOPTTYPE_STRINGPOINT, 247),

  /* Set if we should verify the proxy in ssl handshake,
     set 1 to verify. */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSL_VERIFYPEER, CROS_CURLOPTTYPE_LONG, 248),

  /* Set if we should verify the Common name from the proxy certificate in ssl
   * handshake, set 1 to check existence, 2 to ensure that it matches
   * the provided hostname. */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSL_VERIFYHOST, CROS_CURLOPTTYPE_LONG, 249),

  /* What version to specifically try to use for proxy.
     See CURL_SSLVERSION defines below. */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSLVERSION, CROS_CURLOPTTYPE_VALUES, 250),

  /* Set a username for authenticated TLS for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_TLSAUTH_USERNAME, CROS_CURLOPTTYPE_STRINGPOINT, 251),

  /* Set a password for authenticated TLS for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_TLSAUTH_PASSWORD, CROS_CURLOPTTYPE_STRINGPOINT, 252),

  /* Set authentication type for authenticated TLS for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_TLSAUTH_TYPE, CROS_CURLOPTTYPE_STRINGPOINT, 253),

  /* name of the file keeping your private SSL-certificate for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSLCERT, CROS_CURLOPTTYPE_STRINGPOINT, 254),

  /* type of the file keeping your SSL-certificate ("DER", "PEM", "ENG") for
     proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSLCERTTYPE, CROS_CURLOPTTYPE_STRINGPOINT, 255),

  /* name of the file keeping your private SSL-key for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSLKEY, CROS_CURLOPTTYPE_STRINGPOINT, 256),

  /* type of the file keeping your private SSL-key ("DER", "PEM", "ENG") for
     proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSLKEYTYPE, CROS_CURLOPTTYPE_STRINGPOINT, 257),

  /* password for the SSL private key for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_KEYPASSWD, CROS_CURLOPTTYPE_STRINGPOINT, 258),

  /* Specify which SSL ciphers to use for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSL_CIPHER_LIST, CROS_CURLOPTTYPE_STRINGPOINT, 259),

  /* CRL file for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_CRLFILE, CROS_CURLOPTTYPE_STRINGPOINT, 260),

  /* Enable/disable specific SSL features with a bitmask for proxy, see
     CURLSSLOPT_* */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSL_OPTIONS, CROS_CURLOPTTYPE_LONG, 261),

  /* Name of pre proxy to use. */
  CROS_CURLOPT(CROS_CURLOPT_PRE_PROXY, CROS_CURLOPTTYPE_STRINGPOINT, 262),

  /* The public key in DER form used to validate the proxy public key
     this option is used only if PROXY_SSL_VERIFYPEER is true */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_PINNEDPUBLICKEY, CROS_CURLOPTTYPE_STRINGPOINT, 263),

  /* Path to an abstract Unix domain socket */
  CROS_CURLOPT(CROS_CURLOPT_ABSTRACT_UNIX_SOCKET, CROS_CURLOPTTYPE_STRINGPOINT, 264),

  /* Suppress proxy CONNECT response headers from user callbacks */
  CROS_CURLOPT(CROS_CURLOPT_SUPPRESS_CONNECT_HEADERS, CROS_CURLOPTTYPE_LONG, 265),

  /* The request target, instead of extracted from the URL */
  CROS_CURLOPT(CROS_CURLOPT_REQUEST_TARGET, CROS_CURLOPTTYPE_STRINGPOINT, 266),

  /* bitmask of allowed auth methods for connections to SOCKS5 proxies */
  CROS_CURLOPT(CROS_CURLOPT_SOCKS5_AUTH, CROS_CURLOPTTYPE_LONG, 267),

  /* Enable/disable SSH compression */
  CROS_CURLOPT(CROS_CURLOPT_SSH_COMPRESSION, CROS_CURLOPTTYPE_LONG, 268),

  /* Post MIME data. */
  CROS_CURLOPT(CROS_CURLOPT_MIMEPOST, CROS_CURLOPTTYPE_OBJECTPOINT, 269),

  /* Time to use with the CURLOPT_TIMECONDITION. Specified in number of
     seconds since 1 Jan 1970. */
  CROS_CURLOPT(CROS_CURLOPT_TIMEVALUE_LARGE, CROS_CURLOPTTYPE_OFF_T, 270),

  /* Head start in milliseconds to give happy eyeballs. */
  CROS_CURLOPT(CROS_CURLOPT_HAPPY_EYEBALLS_TIMEOUT_MS, CROS_CURLOPTTYPE_LONG, 271),

  /* Function that will be called before a resolver request is made */
  CROS_CURLOPT(CROS_CURLOPT_RESOLVER_START_FUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 272),

  /* User data to pass to the resolver start callback. */
  CROS_CURLOPT(CROS_CURLOPT_RESOLVER_START_DATA, CROS_CURLOPTTYPE_CBPOINT, 273),

  /* send HAProxy PROXY protocol header? */
  CROS_CURLOPT(CROS_CURLOPT_HAPROXYPROTOCOL, CROS_CURLOPTTYPE_LONG, 274),

  /* shuffle addresses before use when DNS returns multiple */
  CROS_CURLOPT(CROS_CURLOPT_DNS_SHUFFLE_ADDRESSES, CROS_CURLOPTTYPE_LONG, 275),

  /* Specify which TLS 1.3 ciphers suites to use */
  CROS_CURLOPT(CROS_CURLOPT_TLS13_CIPHERS, CROS_CURLOPTTYPE_STRINGPOINT, 276),
  CROS_CURLOPT(CROS_CURLOPT_PROXY_TLS13_CIPHERS, CROS_CURLOPTTYPE_STRINGPOINT, 277),

  /* Disallow specifying username/login in URL. */
  CROS_CURLOPT(CROS_CURLOPT_DISALLOW_USERNAME_IN_URL, CROS_CURLOPTTYPE_LONG, 278),

  /* DNS-over-HTTPS URL */
  CROS_CURLOPT(CROS_CURLOPT_DOH_URL, CROS_CURLOPTTYPE_STRINGPOINT, 279),

  /* Preferred buffer size to use for uploads */
  CROS_CURLOPT(CROS_CURLOPT_UPLOAD_BUFFERSIZE, CROS_CURLOPTTYPE_LONG, 280),

  /* Time in ms between connection upkeep calls for long-lived connections. */
  CROS_CURLOPT(CROS_CURLOPT_UPKEEP_INTERVAL_MS, CROS_CURLOPTTYPE_LONG, 281),

  /* Specify URL using CURL URL API. */
  CROS_CURLOPT(CROS_CURLOPT_CURLU, CROS_CURLOPTTYPE_OBJECTPOINT, 282),

  /* add trailing data just after no more data is available */
  CROS_CURLOPT(CROS_CURLOPT_TRAILERFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 283),

  /* pointer to be passed to HTTP_TRAILER_FUNCTION */
  CROS_CURLOPT(CROS_CURLOPT_TRAILERDATA, CROS_CURLOPTTYPE_CBPOINT, 284),

  /* set this to 1L to allow HTTP/0.9 responses or 0L to disallow */
  CROS_CURLOPT(CROS_CURLOPT_HTTP09_ALLOWED, CROS_CURLOPTTYPE_LONG, 285),

  /* alt-svc control bitmask */
  CROS_CURLOPT(CROS_CURLOPT_ALTSVC_CTRL, CROS_CURLOPTTYPE_LONG, 286),

  /* alt-svc cache file name to possibly read from/write to */
  CROS_CURLOPT(CROS_CURLOPT_ALTSVC, CROS_CURLOPTTYPE_STRINGPOINT, 287),

  /* maximum age of a connection to consider it for reuse (in seconds) */
  CROS_CURLOPT(CROS_CURLOPT_MAXAGE_CONN, CROS_CURLOPTTYPE_LONG, 288),

  /* SASL authorisation identity */
  CROS_CURLOPT(CROS_CURLOPT_SASL_AUTHZID, CROS_CURLOPTTYPE_STRINGPOINT, 289),

  /* allow RCPT TO command to fail for some recipients */
  CROS_CURLOPT(CROS_CURLOPT_MAIL_RCPT_ALLLOWFAILS, CROS_CURLOPTTYPE_LONG, 290),

  /* the private SSL-certificate as a "blob" */
  CROS_CURLOPT(CROS_CURLOPT_SSLCERT_BLOB, CROS_CURLOPTTYPE_BLOB, 291),
  CROS_CURLOPT(CROS_CURLOPT_SSLKEY_BLOB, CROS_CURLOPTTYPE_BLOB, 292),
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSLCERT_BLOB, CROS_CURLOPTTYPE_BLOB, 293),
  CROS_CURLOPT(CROS_CURLOPT_PROXY_SSLKEY_BLOB, CROS_CURLOPTTYPE_BLOB, 294),
  CROS_CURLOPT(CROS_CURLOPT_ISSUERCERT_BLOB, CROS_CURLOPTTYPE_BLOB, 295),

  /* Issuer certificate for proxy */
  CROS_CURLOPT(CROS_CURLOPT_PROXY_ISSUERCERT, CROS_CURLOPTTYPE_STRINGPOINT, 296),
  CROS_CURLOPT(CROS_CURLOPT_PROXY_ISSUERCERT_BLOB, CROS_CURLOPTTYPE_BLOB, 297),

  /* the EC curves requested by the TLS client (RFC 8422, 5.1);
   * OpenSSL support via 'set_groups'/'set_curves':
   * https://www.openssl.org/docs/manmaster/man3/SSL_CTX_set1_groups.html
   */
  CROS_CURLOPT(CROS_CURLOPT_SSL_EC_CURVES, CROS_CURLOPTTYPE_STRINGPOINT, 298),

  /* HSTS bitmask */
  CROS_CURLOPT(CROS_CURLOPT_HSTS_CTRL, CROS_CURLOPTTYPE_LONG, 299),
  /* HSTS file name */
  CROS_CURLOPT(CROS_CURLOPT_HSTS, CROS_CURLOPTTYPE_STRINGPOINT, 300),

  /* HSTS read callback */
  CROS_CURLOPT(CROS_CURLOPT_HSTSREADFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 301),
  CROS_CURLOPT(CROS_CURLOPT_HSTSREADDATA, CROS_CURLOPTTYPE_CBPOINT, 302),

  /* HSTS write callback */
  CROS_CURLOPT(CROS_CURLOPT_HSTSWRITEFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 303),
  CROS_CURLOPT(CROS_CURLOPT_HSTSWRITEDATA, CROS_CURLOPTTYPE_CBPOINT, 304),

  /* WebSocket Header Item */
  CROS_CURLOPT(CROS_CURLOPT_WS_SEC_PROTOCOL, CROS_CURLOPTTYPE_STRINGPOINT, 305),

  /* WebSocket Close Flag */
  CROS_CURLOPT(CROS_CURLOPT_WS_CLOSE_FLAG, CROS_CURLOPTTYPE_LONG, 306),

  CROS_CURLOPT_LASTENTRY /* the last unused */
} crosCURLoption;

typedef enum {
  /* This is the socket callback function pointer */
  CROS_CURLOPT(CROS_CURLMOPT_SOCKETFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 1),

  /* This is the argument passed to the socket callback */
  CROS_CURLOPT(CROS_CURLMOPT_SOCKETDATA, CROS_CURLOPTTYPE_OBJECTPOINT, 2),

  /* set to 1 to enable pipelining for this multi handle */
  CROS_CURLOPT(CROS_CURLMOPT_PIPELINING, CROS_CURLOPTTYPE_LONG, 3),

  /* This is the timer callback function pointer */
  CROS_CURLOPT(CROS_CURLMOPT_TIMERFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 4),

  /* This is the argument passed to the timer callback */
  CROS_CURLOPT(CROS_CURLMOPT_TIMERDATA, CROS_CURLOPTTYPE_OBJECTPOINT, 5),

  /* maximum number of entries in the connection cache */
  CROS_CURLOPT(CROS_CURLMOPT_MAXCONNECTS, CROS_CURLOPTTYPE_LONG, 6),

  /* maximum number of (pipelining) connections to one host */
  CROS_CURLOPT(CROS_CURLMOPT_MAX_HOST_CONNECTIONS, CROS_CURLOPTTYPE_LONG, 7),

  /* maximum number of requests in a pipeline */
  CROS_CURLOPT(CROS_CURLMOPT_MAX_PIPELINE_LENGTH, CROS_CURLOPTTYPE_LONG, 8),

  /* a connection with a content-length longer than this
     will not be considered for pipelining */
  CROS_CURLOPT(CROS_CURLMOPT_CONTENT_LENGTH_PENALTY_SIZE, CROS_CURLOPTTYPE_OFF_T, 9),

  /* a connection with a chunk length longer than this
     will not be considered for pipelining */
  CROS_CURLOPT(CROS_CURLMOPT_CHUNK_LENGTH_PENALTY_SIZE, CROS_CURLOPTTYPE_OFF_T, 10),

  /* a list of site names(+port) that are blocked from pipelining */
  CROS_CURLOPT(CROS_CURLMOPT_PIPELINING_SITE_BL, CROS_CURLOPTTYPE_OBJECTPOINT, 11),

  /* a list of server types that are blocked from pipelining */
  CROS_CURLOPT(CROS_CURLMOPT_PIPELINING_SERVER_BL, CROS_CURLOPTTYPE_OBJECTPOINT, 12),

  /* maximum number of open connections in total */
  CROS_CURLOPT(CROS_CURLMOPT_MAX_TOTAL_CONNECTIONS, CROS_CURLOPTTYPE_LONG, 13),

  /* This is the server push callback function pointer */
  CROS_CURLOPT(CROS_CURLMOPT_PUSHFUNCTION, CROS_CURLOPTTYPE_FUNCTIONPOINT, 14),

  /* This is the argument passed to the server push callback */
  CROS_CURLOPT(CROS_CURLMOPT_PUSHDATA, CROS_CURLOPTTYPE_OBJECTPOINT, 15),

  /* maximum number of concurrent streams to support on a connection */
  CROS_CURLOPT(CROS_CURLMOPT_MAX_CONCURRENT_STREAMS, CROS_CURLOPTTYPE_LONG, 16),

  CROS_CURLMOPT_LASTENTRY /* the last unused */
} crosCURLMoption;

typedef enum {
  CROS_CURLSHE_OK,           /* all is fine */
  CROS_CURLSHE_BAD_OPTION,   /* 1 */
  CROS_CURLSHE_IN_USE,       /* 2 */
  CROS_CURLSHE_INVALID,      /* 3 */
  CROS_CURLSHE_NOMEM,        /* 4 out of memory */
  CROS_CURLSHE_NOT_BUILT_IN, /* 5 feature not present in lib */
  CROS_CURLSHE_LAST          /* never use */
} crosCURLSHcode;

typedef enum {
  CROS_CURLSHOPT_NONE,       /* don't use */
  CROS_CURLSHOPT_SHARE,      /* specify a data type to share */
  CROS_CURLSHOPT_UNSHARE,    /* specify which data type to stop sharing */
  CROS_CURLSHOPT_LOCKFUNC,   /* pass in a 'curl_lock_function' pointer */
  CROS_CURLSHOPT_UNLOCKFUNC, /* pass in a 'curl_unlock_function' pointer */
  CROS_CURLSHOPT_USERDATA,   /* pass in a user data pointer used in the lock/unlock
                           callback functions */
  CROS_CURLSHOPT_LAST        /* never use */
} crosCURLSHoption;

typedef enum {
  CROS_CURL_LOCK_DATA_NONE = 0,
  /*  CURL_LOCK_DATA_SHARE is used internally to say that
   *  the locking is just made to change the internal state of the share
   *  itself.
   */
  CROS_CURL_LOCK_DATA_SHARE,
  CROS_CURL_LOCK_DATA_COOKIE,
  CROS_CURL_LOCK_DATA_DNS,
  CROS_CURL_LOCK_DATA_SSL_SESSION,
  CROS_CURL_LOCK_DATA_CONNECT,
  CROS_CURL_LOCK_DATA_PSL,
  CROS_CURL_LOCK_DATA_LAST
} cros_curl_lock_data;

/* Different lock access types */
typedef enum {
  CROS_CURL_LOCK_ACCESS_NONE = 0,   /* unspecified action */
  CROS_CURL_LOCK_ACCESS_SHARED = 1, /* for read perhaps */
  CROS_CURL_LOCK_ACCESS_SINGLE = 2, /* for write perhaps */
  CROS_CURL_LOCK_ACCESS_LAST        /* never use */
} cros_curl_lock_access;


/* define cros_curl_off_t */
#if defined(__DJGPP__) || defined(__GO32__)
#  if defined(__DJGPP__) && (__DJGPP__ > 1)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  else
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  endif

#elif defined(__SALFORDC__)
#  define CROS_CURL_TYPEOF_CURL_OFF_T     long

#elif defined(__BORLANDC__)
#  if (__BORLANDC__ < 0x520)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  else
#    define CROS_CURL_TYPEOF_CURL_OFF_T     __int64
#  endif

#elif defined(__TURBOC__)
#  define CROS_CURL_TYPEOF_CURL_OFF_T     long

#elif defined(__WATCOMC__)
#  if defined(__386__)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     __int64
#  else
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  endif

#elif defined(__POCC__)
#  if (__POCC__ < 280)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  elif defined(_MSC_VER)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     __int64
#  else
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  endif

#elif defined(__LCC__)
#  if defined(__e2k__) /* MCST eLbrus C Compiler */
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  else                /* Local (or Little) C Compiler */
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  endif

#elif defined(__SYMBIAN32__)
#  if defined(__EABI__) /* Treat all ARM compilers equally */
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  elif defined(__CW32__)
#    pragma longlong on
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  elif defined(__VC32__)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     __int64
#  endif

#elif defined(__MWERKS__)
#  define CROS_CURL_TYPEOF_CURL_OFF_T     long long

#elif defined(_WIN32_WCE)
#  define CROS_CURL_TYPEOF_CURL_OFF_T     __int64

#elif defined(__MINGW32__)
#  define CROS_CURL_TYPEOF_CURL_OFF_T     long long

#elif defined(__VMS)
#  if defined(__VAX)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  else
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  endif

#elif defined(__OS400__)
#  if defined(__ILEC400__)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  endif

#elif defined(__MVS__)
#  if defined(__IBMC__) || defined(__IBMCPP__)
#    if defined(_LONG_LONG)
#      define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#    elif defined(_LP64)
#      define CROS_CURL_TYPEOF_CURL_OFF_T     long
#    else
#      define CROS_CURL_TYPEOF_CURL_OFF_T     long
#    endif
#  endif

#elif defined(__370__)
#  if defined(__IBMC__) || defined(__IBMCPP__)
#    if defined(_LONG_LONG)
#      define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#    elif defined(_LP64)
#      define CROS_CURL_TYPEOF_CURL_OFF_T     long
#    else
#      define CROS_CURL_TYPEOF_CURL_OFF_T     long
#    endif
#  endif

#elif defined(TPF)
#  define CROS_CURL_TYPEOF_CURL_OFF_T     long

#elif defined(__TINYC__) /* also known as tcc */
#  define CROS_CURL_TYPEOF_CURL_OFF_T     long long

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC) /* Oracle Solaris Studio */
#  if !defined(__LP64) && (defined(__ILP32) ||                          \
                           defined(__i386) ||                           \
                           defined(__sparcv8) ||                        \
                           defined(__sparcv8plus))
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  elif defined(__LP64) || \
        defined(__amd64) || defined(__sparcv9)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  endif

#elif defined(__xlc__) /* IBM xlc compiler */
#  if !defined(_LP64)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  else
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  endif

/* ===================================== */
/*    KEEP MSVC THE PENULTIMATE ENTRY    */
/* ===================================== */

#elif defined(_MSC_VER)
#  if (_MSC_VER >= 900) && (_INTEGRAL_MAX_BITS >= 64)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     __int64
#  else
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  endif

/* ===================================== */
/*    KEEP GENERIC GCC THE LAST ENTRY    */
/* ===================================== */

#elif defined(__GNUC__) && !defined(_SCO_DS)
#  if !defined(__LP64__) &&                                             \
  (defined(__ILP32__) || defined(__i386__) || defined(__hppa__) ||      \
   defined(__ppc__) || defined(__powerpc__) || defined(__arm__) ||      \
   defined(__sparc__) || defined(__mips__) || defined(__sh__) ||        \
   defined(__XTENSA__) ||                                               \
   (defined(__SIZEOF_LONG__) && __SIZEOF_LONG__ == 4)  ||               \
   (defined(__LONG_MAX__) && __LONG_MAX__ == 2147483647L))
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long long
#  elif defined(__LP64__) || \
        defined(__x86_64__) || defined(__ppc64__) || defined(__sparc64__) || \
        defined(__e2k__) || \
        (defined(__SIZEOF_LONG__) && __SIZEOF_LONG__ == 8) || \
        (defined(__LONG_MAX__) && __LONG_MAX__ == 9223372036854775807L)
#    define CROS_CURL_TYPEOF_CURL_OFF_T     long
#  endif

#else
/* generic "safe guess" on old 32 bit style */
# define CROS_CURL_TYPEOF_CURL_OFF_T     long
#endif

#ifdef CROS_CURL_TYPEOF_CURL_OFF_T
  typedef CROS_CURL_TYPEOF_CURL_OFF_T cros_curl_off_t;
#endif

////////////////////// cros openssl define ////////////////////
#ifndef CROS_OPENSSL_FILE
#  ifdef CROS_OPENSSL_NO_FILENAMES
#    define CROS_OPENSSL_FILE ""
#    define CROS_OPENSSL_LINE 0
#  else
#    define CROS_OPENSSL_FILE __FILE__
#    define CROS_OPENSSL_LINE __LINE__
#  endif
#endif

#define CROS_OPENSSL_free(addr) cros_CRYPTO_free(addr, CROS_OPENSSL_FILE, CROS_OPENSSL_LINE)

#define CROS_CRYPTO_num_locks() (1)

#define CROS_CRYPTO_set_locking_callback(func)

#define CROS_CRYPTO_set_id_callback(func)

#define CROS_OPENSSL_malloc(num) cros_CRYPTO_malloc(num, CROS_OPENSSL_FILE, CROS_OPENSSL_LINE)

/*
 * These defines where used in combination with the old locking callbacks,
 * they are not called anymore, but old code that's not called might still
 * use them.
 */
#define CROS_CRYPTO_LOCK 1
#define CROS_CRYPTO_UNLOCK 2
#define CROS_CRYPTO_READ 4
#define CROS_CRYPTO_WRITE 8

#ifdef __cplusplus
}
#endif

#endif  // CROS_CURL_CROSCURL_CROSCURLDEFINE_H_