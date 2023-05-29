
#ifndef GCloud_IRPC_h
#define GCloud_IRPC_h

// declare
namespace g6 {
    namespace irpc {
        class IRPCLite;
        class RPCService;
        class RPCClient;
    }
}

namespace GCloud {

    // declare
    namespace G6Client {
        class IG6Connector;
    }

    namespace G6 {

        class EXPORT_CLASS IRPC
        {
        protected:
            IRPC() {}
            virtual ~IRPC() {}
        public:
            /// @brief 创建IRPC实例
            static IRPC* NewIRPCInstance();

            /// @brief 销毁IRPC实例
            static void DeleteIRPCInstance(IRPC* inst);

            /// @brief 设置通迅的 G6Connector
            /// @param conn 传入的IG6Connector的指针
            /// @param manualUpdate 手动update
            ///                       true - RPC的响应或请求接口调用将会在手动执行Update的时候执行
            ///                       false - 当Connector在网络线程或Update中驱动收到RPC消息时，直接在网络线程或Update驱动中回调RPC响应或请求接口
            /// @note 当 G6Connector 销毁后重新创建时需要重新设置新的实例对象
            /// @note 当网络层使用者自己实现时可以不用设置
            virtual bool SetG6Connector(::GCloud::G6Client::IG6Connector* conn, bool manualUpdate = true) = 0;

            /// @brief 手动驱动IRPC
            /// @note 仅当 SetG6Connector 设置 manualUpdate 为false时，才需要调用此接口
            ///        IRPC的响应和请求后将在此接口中触发
            virtual bool Update() = 0;

        public:
            /// @brief 初始化 RPC Service
            virtual int InitRPCService(::g6::irpc::RPCService* service) = 0;

            /// @brief 初始化 RPC Client
            virtual int InitRPCClient(::g6::irpc::RPCClient* client) = 0;

            /// @brief 创建 RPC Client
            template<class RPCProtoClient>
            RPCProtoClient* NewRPCClient() {
                auto client = new RPCProtoClient;
                BindRPCClient(client);
                return client;
            }

            /// @brief 获取 IRPC lite 对象
            /// @note 用于需要定制修改irpc各层实现时
            virtual ::g6::irpc::IRPCLite* GetIRPCLite() = 0;
        };

    }
}

#endif // !GCloud_IRPC_h
