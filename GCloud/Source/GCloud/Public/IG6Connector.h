#ifndef GCloud_IG6Connector_h
#define GCloud_IG6Connector_h

#include "G6ConnectorDefine.h"
#include "AString.h"

namespace GCloud {
namespace G6Client {

class G6ConnectorObserver;

class EXPORT_CLASS IG6Connector {
protected:
    IG6Connector() {};

    virtual ~IG6Connector() {};

public:
    /// @brief 初始化
    /// @param initInfo 初始化的信息
    virtual void Initialize(const TSF4G2InitializeInfo& initInfo) = 0;

    /// @brief 连接Gate
    /// @param urlList 连接的地址
    /// @param clear 是否清理未发送的消息
    /// @return true - 操作成功，结果等待G6ConnectorObserver::OnConnected通知；
    ///         false - 操作失败，通常为目前已经在连接中或已经建立好了连接，或网络不可用
    /// @note 如果上层需要强制断开底层网络的链接后重新建立网络链接而不销毁当前通讯的会话，则使用RelayConnect接口
    ///       如果上层需要重新建立通信会话(例如切换服务器等场景)，则先调用Disconnect断开后再调用Connect接口
    virtual bool Connect(const char* url, bool clear = true) = 0;

    /// @brief 连接Gate
    /// @param urlList 连接的地址
    /// @param clear 是否清理未发送的消息
    /// @return true - 操作成功，结果等待G6ConnectorObserver::OnConnected通知；
    ///         false - 操作失败，通常为目前已经在连接中或已经建立好了连接，或网络不可用
    /// @note 如果上层需要强制断开底层网络的链接后重新建立网络链接而不销毁当前通讯的会话，则使用RelayConnect接口
    ///       如果上层需要重新建立通信会话(例如切换服务器等场景)，则先调用Disconnect断开后再调用Connect接口
    virtual bool Connect(const AArray& urlList, bool clear = true) = 0;

    /// @brief 重连Gate
    /// @param url 重连的地址，为空时重连Connect成功建立会话的地址
    /// @param force 是否断开目前的网络层链接后重连，当目前链路还有效时必须指定为true才会重连
    /// @param clear 是否清理未发送的消息
    /// @return true - 操作成功，结果等待G6ConnectorObserver::OnRelayConnectedProc通知；
    ///         false - 操作失败，通常为目前已经在连接中或已经建立好了连接，或网络不可用
    /// @note 重连前可以调用CanReconnect接口确认是否可以重连
    ///       当服务器主动踢下线时或本地缓存的会话已经过期时不能重连，只能重新鉴权后重新调用Connect
    virtual bool RelayConnect(const char* url = NULL, bool force = false, bool clear = false) = 0;

    /// @brief 断开Gate连接
    /// @return true - 操作成功，结果等待G6ConnectorObserver::OnDisconnectProc通知；
    ///         false - 操作失败，通常为本地网络层链路断开导致
    /// @note 服务的会定时清理不活跃的会话，如果需要保证会话一定断开，则失败时需要先重连恢复网络层链路后再发起
    virtual bool Disconnect() = 0;

    /// @brief 简易版收消息接口
    /// @param buffer 接收消息的buff
    /// @return true - 收消息成功；
    ///         false - 收消息失败
    virtual bool Read(GCloud::AString& buffer) = 0;

    /// @brief 收消息完整接口
    /// @param msg 接收到的消息 
    /// @return true - 收消息成功；
    ///         false - 收消息失败
    virtual bool Read(G6RecvMessage& msg) = 0;

    /// @brief 发消息
    /// @param msg 待发送的消息
    /// @param routeInfo 发送消息的路由信息
    /// return true - 将消息加入到待发送队列成功，消息将在Update驱动中发送
    ///        false - 将消息加入到待发送队列失败，通常为本地会话没有建立或当前会话异常了
    virtual bool Write(const G6SendMessage& msg, const G6RouteInfo* routeInfo = NULL) = 0;

    // 以下三个为高级版本gate通信接口
    virtual bool RegisterPlugin(void* updatePlugin, void* msgPlugin) = 0;

    /// @brief  发送ping
    virtual int SendPing() = 0;

    /// @brief 主动驱动
    virtual bool Update() = 0;

    /// @brief 获取当前底层网络链接的Server信息
    /// @note 底层网络链路同GateServer建立，此处返回的为GateServer的信息
    virtual bool GetConnectedInfo(Conn::ConnectedInfo* connectedInfo) = 0;

    /// @brief 设置回调
    /// @param observer 设置的回调接收者 
    virtual void SetObserver(G6ConnectorObserver* observer) = 0;

    /// @brief 清理回调
    virtual void ClearObserver() = 0;

    /// @brief 是否有会话连接
    /// @return true - 是；false - 否
    /// @note 仅当会话处于连接状态时才能正常的收发消息
    ///       如果当前会话不处于连接状态，可以调用CanReconnect判断当前需要Connect或RelayConnect
    virtual bool IsConnected() = 0;

    /// @brief 是否可以重连
    /// @return true - 可以重连
    ///         false - 不能重连
    virtual bool CanReconnect() = 0;

    /// @brief 是否需要手动更新
    /// @return true - 是；false - 否
    virtual bool IsManualUpdate() = 0;

    /// @brief 当前连接的url
    /// @return 当前连接的url或""
    virtual const char* GetUrl() = 0;

    /// @brief 当前网络链接的目标IP
    /// @return 当前网络链接的目标IP或""
    virtual const char* GetRealIP() = 0;

    /// @brief 刷新服务端的MSDK Token
    /// @param token 服务端需要更新的token
    /// @param expire 新的token的过期时间
    virtual void RefreshMSDKToken(const char* token, long long& expire) = 0;

    /// @brief 主动设置登陆信息
    /// @note 一般来说，业务不需要主动设置这个信息
    virtual void SetGateLoginInfo(const TSF4G2InitializeInfo& info) = 0;

    /// @brief 主动设置Realm鉴权信息
    /// @note 一般来说，业务不需要主动设置这个，通过
    virtual void SetRealmAuthInfo(const TSF4G2InitializeInfo& info) = 0;

    /// @brief 发送鉴权、获取区服请求
    /// @param requestInfo 鉴权或获取区服信息的请求
    /// @return true - 操作成功，结果等待G6ConnectorObserver::OnAuthProc或G6ConnectorObserver::OnDirRecvedProc通知；
    ///         false - 操作失败，通常为没有初始化或网络不可用
    virtual bool SendRequest(const G6RequestInfo& requestInfo) = 0;

    /// @brief 获取鉴权结果
    /// @param responseInfo 返回的鉴权信息
    /// @return true - 获取成功；false - 获取失败
    virtual bool RecvAuthResponse(G6AuthResponseInfo& responseInfo) = 0;

    /// @brief 获取区服信息
    /// @param responseInfo 返回的区服信息
    /// @return true - 获取成功；false - 获取失败
    virtual bool RecvDirResponse(G6DirResponseInfo& responseInfo) = 0;

    // 析构Connector
    virtual bool Finalize() = 0;

    /// @brief 获取最后一次操作失败的原因
    /// @note 接口类型为bool的调用返回false时，可以通过此接口获取详细信息
    virtual int32_t GetLastErrno() = 0;

    /// @brief 获取最后一次操作失败的原因
    /// @note 接口类型为bool的调用返回false时，可以通过此接口获取详细信息
    virtual const char* GetLastError() = 0;
};

class EXPORT_CLASS G6ConnectorObserver {
public:
    G6ConnectorObserver() {}

    virtual ~G6ConnectorObserver() {}

public:
    // =====G6特有回调=====
    /// @brief 鉴权结果回调
    /// @param connector 调用的IG6Connector对象指针
    /// @param result 鉴权的操作结果，目前result的ErrorCode的结果有下列情况：
    ///                  2 - kErrorNetworkException，网络层错误，通过Extend参考Curl的错误码，通常需要等待后再重试
    ///                  212 - kErrorAuthFailed 鉴权失败，通过Extend参考Realm鉴权失败错误码确认详细原因，通常需要等待后再重试
    /// @note 为了防止鉴权失败导致雪崩，客户端在多次鉴权失败后应该增加重试时间间隔
    virtual void OnAuthProc(IG6Connector* connector, const Conn::ConnectorResult& result) = 0;

    // 区服信息返回回调
    virtual void OnDirRecvedProc(IG6Connector* connector, const Conn::ConnectorResult& result) {}

    /// @brief 连接会话完成回调
    /// @param connector 调用的IG6Connector对象指针
    /// @param result 连接会话的操作结果，目前result的ErrorCode的结果有下列情况：
    ///                  0 - kSuccess 连接会话建立成功
    ///                  1 - kErrorInnerError 内部错误，此错误不常见，需要尝试重新创建IG6Connector对象
    ///                  4 - kErrorInvalidArgument 参数错误，没有初始化或地址为空
    ///                  100 - kErrorInvalidToken 校验token失败，需要重新客户端授权获取token
    ///                  105 - kErrorLoginFailed 服务端拒绝会话连接，可以通过result的Extend获取服务端返回的错误信息，使用者前后端之间协商处理方式
    ///                  201 - kErrorConnectFailed 网络层错误，可以通过result的Extend获取更多信息，可以重新发起Connect
    ///                  205 - kErrorPeerStopSession 在登录的流程中时被服务端踢下线了，可以重新发起Connect
    ///                  214 - kErrorDNS 地址为域名的情况下域名解析失败，可以尝试使用非域名重新发起Connect
    virtual void OnConnected(IG6Connector* connector, const Conn::ConnectorResult& result) = 0;

    /// @brief 会话重连完成回调
    /// @param connector 调用的IG6Connector对象指针
    /// @param result 连接会话的操作结果，目前result的ErrorCode的结果有下列情况：
    ///                  0 - kSuccess 连接会话建立成功
    ///                  1 - kErrorInnerError 内部错误，此错误不常见，需要尝试重新创建IG6Connector对象
    ///                  4 - kErrorInvalidArgument 参数错误，没有初始化或地址为空
    ///                  105 - kErrorLoginFailed 服务端拒绝会话连接，可以通过result的Extend获取服务端返回的错误信息，使用者前后端之间协商处理方式
    ///                  201 - kErrorConnectFailed 网络层错误，可以通过result的Extend获取更多信息，可以调用CanReconnect确认能重连后发起RelayConnect重连
    ///                  205 - kErrorPeerStopSession 在重连的流程中时被服务端踢下线了，不能再继续重连，可以重新发起Connect
    ///                  214 - kErrorDNS 地址为域名的情况下域名解析失败，可以尝试使用非域名重新发起Connect
    virtual void OnRelayConnectedProc(IG6Connector* connector, const Conn::ConnectorResult& result) = 0;

    /// @brief 连接会话断开回调
    /// @param connector 调用的IG6Connector对象指针
    /// @param result 断开会话的操作结果，目前result的ErrorCode的结果有下列情况：
    ///                  0 - kSuccess 主动断开会话成功
    ///                  205 - kErrorPeerStopSession 服务端断开会话，可以通过result的Extend获取服务端提供的信息，使用者前后端之间协商处理方式
    virtual void OnDisconnectProc(IG6Connector* connector, const Conn::ConnectorResult& result) = 0;

    /// @brief 状态变化回调
    /// @param connector 调用的IG6Connector对象指针
    /// @param state 当前的状态，目前主要有下列情况：
    ///                 3 - kConnectorStateStayInQueue 排队信息通知
    ///                 4 - kConnectorStateError 网络链路层异常通知
    /// @param result 当前状态变化通知的详细信息
    ///                 当state为3时，result的ErrorCode为0；Extend为排队预期剩余时间；Extend2为当前排队的位置；Extend3为当前排队的总人数
    ///                 当state为4时，客户端可以调用IG6Connector::CanReconnect判断能重连后调用RelayConnect恢复，否则调用Connect重新建立会话
    ///                        result的ErrorCode可能为
    ///                                204 - kErrorPeerCloseConnection，服务器主动断开了链路
    ///                                2 - kErrorNetworkException，底层网络层异常，通过result的Extend获取详细信息
    virtual void OnStateChangedProc(IG6Connector* connector, Conn::ConnectorState state, const Conn::ConnectorResult& result) = 0;

    /// @brief 收到消息回调
    /// @param connector 调用的IG6Connector对象指针
    /// @parem result 当前无意义
    /// @note 注意消息的通知不同于其他通知，为水平触发
    ///           只要当前队列中存在没有被收走的消息，每次Update驱动的时候都会触发一次通知
    ///           其他通知都是边缘触发，仅在变化的时候通知一次
    virtual void OnDataRecvedProc(IG6Connector* connector, const Conn::ConnectorResult& result) = 0;

    /// @brief G6还未使用到
    virtual void OnUDPDataRecvedProc(IG6Connector* connector, const Conn::ConnectorResult& result) {}

    /// @brief G6还未使用到
    virtual void OnRouteChangedProc(IG6Connector* connector, const Conn::ConnectorResult& result, unsigned long long serverID) {}

    /// @brief Ping 回调
    virtual void OnPingProc(IG6Connector* connector, int seq, unsigned long long rtt) {}
};
}
}

#endif /* IG6Connector_h */

