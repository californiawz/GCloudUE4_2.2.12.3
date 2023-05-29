#ifndef G6ConnectorPublicDefine_h
#define G6ConnectorPublicDefine_h

#include "ApolloBuffer.h"
#include "ADictionary.h"
#include <stdio.h>
//#include "IConnector.h"
#include "ConnectorPublicDefine.h"

#if defined(_WIN32) || defined(_WIN64)
#define snprintf _snprintf
#pragma warning(push)
#pragma warning(disable:4996)
#endif

// uint64_max
#ifndef UINT64_MAX
#define UINT64_MAX 18446744073709551615ULL
#endif


#define G6_SEND_MSG_DEFAULT_VERSION 1

namespace GCloud {
namespace G6Client {

typedef enum {
    // Common
    kG6ErrorNone = 0,
    kG6ErrorInnerError = 1,
    kG6ErrorNetworkException = 2,
    kG6ErrorTimeout = 3,
    kG6ErrorInvalidArgument = 4,
    kG6ErrorLengthError = 5,
    kG6ErrorUnknown = 6,
    kG6ErrorEmpty = 7,

    kG6ErrorNotInitialized = 9,
    kG6ErrorNotSupported = 10,
    kG6ErrorNotInstalled = 11,
    kG6ErrorSystemError = 12,
    kG6ErrorNoPermission = 13,
    kG6ErrorInvalidGameId = 14,

    // Connector, from 200
    kG6ErrorNoConnection = 200,
    kG6ErrorConnectFailed = 201,
    kG6ErrorIsConnecting,
    kG6ErrorG6APIError,
    kG6ErrorPeerCloseConnection,
    kG6ErrorPeerStopSession,
    kG6ErrorPkgNotCompleted,
    kG6ErrorSendError,
    kG6ErrorRecvError,
    kG6ErrorStayInQueue,
    kG6ErrorSvrIsFull,
    kG6ErrorTokenSvrError,
    kG6ErrorAuthFailed,
    kG6ErrorOverflow,
    kG6ErrorDNS,
} EErrorCode;

struct EXPORT_CLASS G6Result : public GCloud::ApolloBufferBase {
    int ErrorCode;
    int64_t Extend;
    GCloud::AString ErrorMsg;

public:

    G6Result()
    : ErrorCode(kG6ErrorNone), Extend(0) {

    }

    G6Result(EErrorCode
             errorCode)
    :

    ErrorCode(errorCode), Extend(0) {

    }

    G6Result(EErrorCode
             errorCode,
             const char* msg
    )
    :

    ErrorCode(errorCode), Extend(0), ErrorMsg(msg) {

    }

    G6Result(EErrorCode
             errorCode,
             int ext,
             const char* msg
    )
    :

    ErrorCode(errorCode), Extend(ext), ErrorMsg(msg) {

    }

    G6Result(const G6Result& r) {
        ErrorCode = r.ErrorCode;
        ErrorMsg = r.ErrorMsg;
        Extend = r.Extend;
    }

public:

    void Reset(EErrorCode error, const char* msg = "") {
        ErrorCode = error;
        Extend = 0;
        ErrorMsg = msg;

    }

    void Reset(EErrorCode error, int ext, const char* msg = "") {
        ErrorCode = error;
        Extend = ext;
        ErrorMsg = msg;
    }

    bool IsSuccess() const {
        return ErrorCode == kG6ErrorNone;
    }

    GCloud::AString ToString() const;

    bool operator==(EErrorCode errorCode) const {
        return ErrorCode == errorCode;
    }

    bool operator!=(EErrorCode errorCode) const {
        return ErrorCode != errorCode;
    }

    G6Result& operator=(const G6Result& cRet) {
        ErrorCode = cRet.ErrorCode;
        ErrorMsg = cRet.ErrorMsg;
        Extend = cRet.Extend;
        return *this;
    }

public:

    virtual AObject* Clone() const {
        G6Result* clone = new G6Result();
        *clone = *this;
        return clone;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& write) const {
        write.Write(ErrorCode);
        write.Write(ErrorMsg);
        write.Write(Extend);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        int tmp;
        reader.Read(tmp);
        ErrorCode = (EErrorCode) tmp;
        reader.Read(ErrorMsg);
        reader.Read(Extend);
    }
};

/// @brief Channel，和MSDK的值保持一致
#if __cplusplus >= 201103L
enum G6Channel : int32_t {
#else // 适配当前GcloudSDK在mac/ios下还不是c11
typedef int32_t G6Channel;
enum {
#endif
    kChannelNone = 0,
    kChannelTWChat = 1,
    kChannelTQChat = 2,
    kChannelGuest = 3,
    kChannelFacebook = 4,
    kChannelGameCenter = 5,
    kChannelGooglePlay = 6,
    kChannelTwitter = 9,
    kChannelGarena = 10,
    kChannelLine = 14,
    kChannelApple = 15,
    kChannelKwai = 17,
    kChannelWeGame = 101,   // 非MSDK的channel，当G6AuthType为Wegame时务必设置为此值
};

/// @brief 鉴权类型
#if __cplusplus >= 201103L
enum G6AuthType : int32_t {
#else // 适配当前GcloudSDK在mac/ios下还不是c11
typedef int32_t G6AuthType;
enum {
#endif
    kG6Auth_None = 0,
    kG6Auth_MSDK = 1,       // MSDKv5，当前仅支持MSDKv5
    kG6Auth_DAW = 2,
    kG6Auth_Wegame = 3,
    kG6Auth_INTL = 4,       // IntlSDK
    kG6Auth_Plugin = 5,     // 自定义鉴权
};

/// @brief 平台类型
#if __cplusplus >= 201103L
enum G6PlatformType : int32_t {
#else // 适配当前GcloudSDK在mac/ios下还不是c11
typedef int32_t G6PlatformType;
enum {
#endif
    kInvaildPlatform = 0,
    kAndroid = 1,           ///< 安卓
    kIOS = 2,               ///< 苹果
    kWeb = 3,               ///< Web
    kLinux = 4,             ///< Linux
    kWindows = 5,           ///< Windows
    kSwitch = 6             ///< Nintendo switch
};

enum G6EncryptMethod {
    kG6Encrypt_Default = 0,
    kG6Encrypt_None = 1,
    kG6Encrypt_Aes = 2,
};

enum G6CompressionType {
    kG6Compression_Default = 0,
    kG6Compression_Plain = 0x01,
    kG6Compression_LZ4 = 0x02,
    kG6Compression_Count = 0x03,
};

enum G6ConnectionState {
    kConnectionState_Idle,
    kConnectionState_Connecting,
    kConnectionState_Connected,
    kConnectionState_StayInQueue,
    kConnectionState_Break,
};

enum G6WorkState {
    kWorkState_None,
    kWorkState_Running,
    kWorkState_Finish,
};

enum G6InfoType {
    kG6InfoType_Base,
    kG6InfoType_Init,

    kG6InfoType_Auth_Realm = 10,
    kG6InfoType_Auth_Gate = 11,

    kG6InfoType_Response_Auth = 50,
    kG6InfoType_Response_Dir = 51,
    kG6InfoType_Response_Dir_Tree = 52,
    kG6InfoType_Response_Dir_Leaf = 53,

    kG6InfoType_Request = 70,
};

enum G6RequstDirType {
    kG6RequestDirType_ALL = 1,
    kG6RequestDirType_TREE = 2,
    kG6RequestDirType_LEAF = 3,
};

enum G6RequestType {
    kG6RequestType_None,
    kG6RequestType_Auth,
    kG6RequestType_DIR_All,
    kG6RequestType_DIR_Tree,
    kG6RequestType_DIR_Leaf,

    kG6RequestType_AuthDIR,
};

enum G6Action {
    kG6Action_None,
    kG6Action_Connect,
    kG6Action_Reconnect,
    kG6Action_Disconnect,
    kG6Action_RefreshToken,
};

enum G6MsgType {
    kG6MsgTypeClient = 0x02,
    kG6MsgTypeIRPCReq = 0x03,
    kG6MsgTypeIRPCRsp = 0x04,
};

enum G6MsgSendFlag {
    // 消息是不可靠的，当网络采用UDP时，默认为可靠UDP模式，指定此字段后转为普通UDP发送
    kG6MsgSendUnReliable = 0x0001,
};

// TSF4G2基类
struct EXPORT_CLASS G6InfoBase : public GCloud::ApolloBufferBase {
public:
    GCloud::Conn::ConnectorResult Result;

protected:
    G6InfoType Type;

public:
    G6InfoBase() : Type(kG6InfoType_Base) {}

    G6InfoBase(G6InfoType type) : Type(type) {}

    virtual ~ G6InfoBase() {}

    G6InfoType GetType() const {
        return Type;
    }

    virtual AObject* Clone() const {
        G6InfoBase* instance = new G6InfoBase();
        *instance = *this;
        return instance;
    }

protected:
    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        writer.Write(Type);
        Result.WriteTo(writer);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        int tmp = 0;
        reader.Read(tmp);
        Type = (G6InfoType) tmp;
        Result.ReadFrom(reader);
    }
};

struct EXPORT_CLASS G6RequestInfo : public G6InfoBase {
public:
    G6RequestType RequestType;

public:
    G6RequestInfo() : G6InfoBase(kG6InfoType_Request), RequestType(kG6RequestType_None) {}

    G6RequestInfo(G6RequestType r) : G6InfoBase(kG6InfoType_Request), RequestType(r) {}

    virtual ~ G6RequestInfo() {}

    void SetRequestType(G6RequestType ReqType) { RequestType = ReqType; }

    G6RequestType GetRequestType() const {
        return RequestType;
    }

    virtual GCloud::AString ToString() const {
        GCloud::AString tmp("G6RequestInfo clz:");
        tmp += int2str(RequestType);
        return tmp;
    }

public:
    virtual AObject* Clone() const {
        G6RequestInfo* clone = new G6RequestInfo();
        *clone = *this;
        return clone;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        G6InfoBase::WriteTo(writer);
        writer.Write(RequestType);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        G6InfoBase::ReadFrom(reader);
        int temp = 0;
        reader.Read(temp);
        RequestType = (G6RequestType)
        temp;
    }

};

struct EXPORT_CLASS G6RequestAuthInfo : public G6RequestInfo {
public:
    G6RequestAuthInfo() : G6RequestInfo(kG6RequestType_Auth) {}

    virtual ~ G6RequestAuthInfo() {}

    virtual GCloud::AString ToString() const {
        GCloud::AString tmp("G6RequestAuthInfo clz:");
        tmp += int2str(RequestType);
        return tmp;
    }

public:
    virtual AObject* Clone() const {
        G6RequestAuthInfo* clone = new G6RequestAuthInfo();
        *clone = *this;
        return clone;
    }
};

struct EXPORT_CLASS G6RequestAuthDirInfo : public G6RequestInfo {
public:
    G6RequestAuthDirInfo() : G6RequestInfo(kG6RequestType_AuthDIR) {}

    virtual ~ G6RequestAuthDirInfo() {}

    virtual GCloud::AString ToString() const {
        GCloud::AString tmp("G6RequestAuthDirInfo clz:");
        tmp += int2str(RequestType);
        return tmp;
    }

public:
    virtual AObject* Clone() const {
        G6RequestAuthDirInfo* clone = new G6RequestAuthDirInfo();
        *clone = *this;
        return clone;
    }
};

struct EXPORT_CLASS G6RequestDirInfo : public G6RequestInfo {
public:
    G6RequestDirInfo() : G6RequestInfo(kG6RequestType_DIR_All) {}

    virtual ~ G6RequestDirInfo() {}

    virtual GCloud::AString ToString() const {
        GCloud::AString tmp("G6RequestDirInfo clz:");
        tmp += int2str(RequestType);
        return tmp;
    }

public:
    virtual AObject* Clone() const {
        G6RequestDirInfo* clone = new G6RequestDirInfo();
        *clone = *this;
        return clone;
    }
};

struct EXPORT_CLASS G6RequestDirTreeInfo : public G6RequestInfo {
public:
    int PlatformId;

public:
    G6RequestDirTreeInfo() : G6RequestInfo(kG6RequestType_DIR_Tree), PlatformId(0) {}

    G6RequestDirTreeInfo(int p) : G6RequestInfo(kG6RequestType_DIR_Tree), PlatformId(p) {}

    virtual ~ G6RequestDirTreeInfo() {}

    virtual GCloud::AString ToString() const {
        GCloud::AString tmp("G6RequestDirTreeInfo clz:");
        tmp += int2str(RequestType);
        tmp += ", platform:";
        tmp += int2str(PlatformId);
        return tmp;
    }

public:
    void SetPlatFormId(int platformId) {
        this->PlatformId = platformId;
    }

    virtual AObject* Clone() const {
        G6RequestDirTreeInfo* clone = new G6RequestDirTreeInfo();
        *clone = *this;
        return clone;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        G6RequestInfo::WriteTo(writer);
        writer.Write(PlatformId);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        G6RequestInfo::ReadFrom(reader);
        reader.Read(PlatformId);
    }
};

struct EXPORT_CLASS G6RequestDirLeafInfo : public G6RequestInfo {
public:
    int PlatformId;
    int LeafId;

public:
    G6RequestDirLeafInfo() : G6RequestInfo(kG6RequestType_DIR_Leaf), PlatformId(0), LeafId(0) {}

    G6RequestDirLeafInfo(int p, int l) : G6RequestInfo(kG6RequestType_DIR_Leaf), PlatformId(p), LeafId(l) {}

    virtual ~ G6RequestDirLeafInfo() {}

    virtual GCloud::AString ToString() const {
        GCloud::AString tmp("G6RequestDirLeafInfo clz:");
        tmp += int2str(RequestType);
        tmp += ", platform:";
        tmp += int2str(PlatformId);
        tmp += ", leaf:";
        tmp += int2str(LeafId);
        return tmp;
    }

public:
    void SetPlatFormId(int platformId) {
        this->PlatformId = platformId;
    }

    void SetLeafId(int leafId) {
        this->LeafId = leafId;
    }

    virtual AObject* Clone() const {
        G6RequestDirLeafInfo* clone = new G6RequestDirLeafInfo();
        *clone = *this;
        return clone;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        G6RequestInfo::WriteTo(writer);
        writer.Write(PlatformId);
        writer.Write(LeafId);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        G6RequestInfo::ReadFrom(reader);
        reader.Read(PlatformId);
        reader.Read(LeafId);
    }
};

/**
 * Gate发送消息的路由指定
 */
struct EXPORT_CLASS G6RouteInfo : public GCloud::ApolloBufferBase {
public:
    GCloud::AString ServiceName;
    uint64_t ServiceInstId;

    G6RouteInfo() : ServiceInstId(UINT64_MAX) {}

public:
    virtual AObject* Clone() const {
        G6RouteInfo* instance = new G6RouteInfo();
        *instance = *this;
        return instance;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        writer.Write(ServiceName);
        writer.Write(ServiceInstId);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        reader.Read(ServiceName);
        reader.Read(ServiceInstId);
    }
};

struct EXPORT_CLASS G6SendMessage : public GCloud::ApolloBufferBase {
public:
    // 消息数据
    GCloud::AString Payload;
    // 消息类型，取值参考G6MsgType，默认值为kG6MsgTypeClient
    G6MsgType MessageType;
    // 消息的flag标记，取值参考G6MsgSendFlag，默认值为0
    int32_t MessageFlag;
    // 消息的Metadata扩展部分
    GCloud::ADictionary MD;

    G6SendMessage() : MessageType(kG6MsgTypeClient), MessageFlag(0) {}

public:
    virtual AObject* Clone() const {
        G6SendMessage* instance = new G6SendMessage();
        *instance = *this;
        return instance;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        writer.Write(Payload);
        writer.Write((int) MessageType);
        writer.Write(MessageFlag);
        writer.Write(MD);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        reader.Read(Payload);
        int type;
        reader.Read(type);
        MessageType = (G6MsgType) type;
        reader.Read(MessageFlag);
        reader.Read<GCloud::AString, GCloud::AString>(MD);
    }
};

struct EXPORT_CLASS G6RecvMessage : public GCloud::ApolloBufferBase {
public:
    // 消息数据
    GCloud::AString Payload;
    // 消息类型，取值参考G6MsgType，默认值为kG6MsgTypeClient
    G6MsgType MessageType;
    // 消息来源的Server服务名
    GCloud::AString ServiceName;
    // 消息来源的Server实例ID
    uint64_t ServiceId;
    // 消息的Metadata扩展部分
    GCloud::ADictionary MD;

    G6RecvMessage() : MessageType(kG6MsgTypeClient), ServiceId(0) {}

public:
    virtual AObject* Clone() const {
        G6RecvMessage* instance = new G6RecvMessage();
        *instance = *this;
        return instance;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        writer.Write(Payload);
        writer.Write((int) MessageType);
        writer.Write(ServiceName);
        writer.Write(ServiceId);
        writer.Write(MD);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        reader.Read(Payload);
        int type;
        reader.Read(type);
        MessageType = (G6MsgType) (type);
        reader.Read(ServiceName);
        reader.Read(ServiceId);
        reader.Read<GCloud::AString, GCloud::AString>(MD);
    }
};

struct EXPORT_CLASS G6AuthResponseInfo : public G6InfoBase {
public:
    GCloud::AString Ticket;
    GCloud::AString Key;
    GCloud::ADictionary AuthMD;

    G6AuthResponseInfo() : G6InfoBase(kG6InfoType_Response_Auth) {}

public:

    virtual AObject* Clone() const {
        G6AuthResponseInfo* instance = new G6AuthResponseInfo();
        *instance = *this;
        return instance;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        G6InfoBase::WriteTo(writer);
        writer.Write(Ticket);
        writer.Write(Key);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        G6InfoBase::ReadFrom(reader);
        reader.Read(Ticket);
        reader.Read(Key);
    }

};

struct EXPORT_CLASS G6DirResponseInfo : public G6InfoBase {
public:
    GCloud::AString DirTree;
    int32_t DirPlatform;
    int32_t DirLeaf;

    G6DirResponseInfo() : G6InfoBase(kG6InfoType_Response_Dir), DirPlatform(0), DirLeaf(0) {}

public:

    virtual AObject* Clone() const {
        G6DirResponseInfo* instance = new G6DirResponseInfo();
        *instance = *this;
        return instance;
    }

    virtual void WriteTo(GCloud::CApolloBufferWriter& writer) const {
        G6InfoBase::WriteTo(writer);
        writer.Write(DirTree);
        writer.Write(DirPlatform);
        writer.Write(DirLeaf);
    }

    virtual void ReadFrom(GCloud::CApolloBufferReader& reader) {
        G6InfoBase::ReadFrom(reader);
        reader.Read(DirTree);
        reader.Read(DirPlatform);
        reader.Read(DirLeaf);
    }

    void SetType(G6InfoType type) {
        this->Type = type;
    }
};

// TSF4G2SDK初始化信息
class EXPORT_CLASS TSF4G2InitializeInfo {
public: // Common
    // 游戏的GCloudID
    uint64_t GameID;

    // 用户的UID
    uint64_t UID;

    // MSDK的OpenID
    // 用户调用SetAuthInfo后可以重设该字段
    GCloud::AString OpenID;

    // MSDK的token
    GCloud::AString Token;

    // MSDK的token有效期
    uint64_t TokenExpired;

    // Realm返回的LoginKey，用于Gate与Server通信，用户也可以手工设置
    // Realm鉴权返回成功报文后，会更新该字段
    GCloud::AString LoginKey;

    // Realm返回的G6Ticket，用于Gate与Server通信，用户也可以手工设置
    // Realm鉴权返回成功报文后，会更新该字段
    GCloud::AString LoginTicket;

public: // Realm Only
    // realm的url，必须设置
    GCloud::AString RealmURL;

    // 渠道，用于Realm鉴权
    G6Channel Channel;

    // 鉴权类型，用于Realm鉴权
    G6AuthType AuthType;

    // 平台类型，用于Realm鉴权
    G6PlatformType PlatformId;

    // CURL配置字段，对应是否开启SSL
    int32_t CurlSslVerifyPeer; // CURLOPT_SSL_VERIFYPEER, 1 - true; 0 - fale
    int32_t CurlSslVerifyHost; // CURLOPT_SSL_VERIFYHOST
    GCloud::AString CurlSslCaInfo;     // CURLOPT_CAINFO

    // CURL配置字段，对应是否开启CURL详细信息
    int32_t CurlVerbose;

    // 连接时的超时时间，单位ms
    int32_t Timeout;

    // 业务的扩展字段，透传给Realm到自定义鉴权插件里
    // 务必注意：key = AString, val = AString
    GCloud::ADictionary AuthMD;

   public:  // Gate Only
    // 登陆时透传给CSHead::service_name字段
    GCloud::AString LoginSerivceName;

    // 客户端本地的元数据，透传给Gate添加为链接的元数据
    // 务必注意：key = AString, val = AString
    GCloud::ADictionary ClientMD;

    // GateBuffer的大小，同时影响发送和接受区
    uint32_t MaxMessage;

    // Gate与Server通信的加密方式
    G6EncryptMethod EncMethod;

    // Gate与Server通信的压缩方式
    G6CompressionType CompressType;

public:
    TSF4G2InitializeInfo() {
        GameID = 0;
        UID = 0;
        TokenExpired = 0;
        Channel = kChannelNone;
        AuthType = kG6Auth_None;
        PlatformId = kInvaildPlatform;
        CurlSslVerifyPeer = 0;
        CurlSslVerifyHost = 2;
        CurlVerbose = 0;
        Timeout = 5000;
        MaxMessage = 524288;
        EncMethod = kG6Encrypt_Default;
        CompressType = kG6Compression_Default;
    }

    TSF4G2InitializeInfo* Clone() const {
        TSF4G2InitializeInfo* clone = new TSF4G2InitializeInfo();
        *clone = *this;
        return clone;
    }
};

}
}

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif /* ConnectorPublicDefine_h */
