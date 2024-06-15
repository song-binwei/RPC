#include "rpc_provider.h"
#include "rpc_application.h"
#include "rpc_header.pb.h"
#include "util_zookeeper.h"

// 发布RPC方法的函数接口

/*
server_name -> server信息
                        -> server对象的指针
                        -> 方法的集合。

*/

void RpcProvider::NotifyService(google::protobuf::Service *service) {

    ServiceInfo service_info;
    // 服务对象的描述信息
    const google::protobuf::ServiceDescriptor *serviceDes = service->GetDescriptor();
    // 服务对象的名字
    std::string server_name = serviceDes->name();
    // 服务对象拥有的方法总数
    int methodCnt = serviceDes->method_count();
    std::cout << "server name : " << server_name << std::endl;
    // 遍历方法
    for (int i = 0; i < methodCnt; i++) {
        // 方法对象的描述
        const google::protobuf::MethodDescriptor *methodDes = serviceDes->method(i);
        // 方法对象的名字
        std::string method_name = methodDes->name();
        service_info.m_methodMap.insert({method_name, methodDes});
        std::cout << "method name : " << method_name << std::endl;
    }
    service_info.m_service = service;
    m_serviceMap.insert({server_name, service_info});

}

// 启动RPC服务节点，开始提供RPC远程网络调用服务
void RpcProvider::Run() {
    std::string ip = RpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(RpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress address(ip, port);

    // 创建TcpServer对象
    muduo::net::TcpServer server(&m_eventLoop, address, "RpcProvider");
    // 绑定连接的回调和消息的回调，分离网络和业务的代码
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection, this, std::placeholders::_1));
    server.setMessageCallback(std::bind(&RpcProvider::OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置muduo库线程数量
    server.setThreadNum(4);

    // 把当前RPC节点上要发布的服务全部注册到zk上面，让rpc client可以从zk上发现服务
    // session timeout   30s     zkclient 网络I/O线程  1/3 * timeout 时间发送ping消息
    ZkClient zkCli;
    zkCli.Start();
    // 注册service_name为永久性节点    method_name为临时性节点
    for (auto &service_point : m_serviceMap) 
    {
        // /service_name   /UserServiceRpc
        std::string service_path = "/" + service_point.first;
        zkCli.Create(service_path.c_str(), nullptr, 0);
        for (auto &method_point : service_point.second.m_methodMap)
        {
            // /service_name/method_name   /UserServiceRpc/Login 存储当前这个rpc服务节点主机的ip和port
            std::string method_path = service_path + "/" + method_point.first;
            char method_data[128] = {0};
            sprintf(method_data, "%s:%d", ip.c_str(), port);
            zkCli.Create(method_path.c_str(), method_data, strlen(method_data), ZOO_EPHEMERAL);
        } 
    }
    
    // 启动服务
    server.start();
    std::cout << "RpcProvider start " << "ip : " << ip << " port : " << port << std::endl;
    // 等待连接
    m_eventLoop.loop();

}

// 新的socket连接的回调函数
void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr &conn) {
    // 如果断开连接，关闭文件描述符
    if (!conn->connected()) {
        conn->shutdown();
    }
}
// 在框架中RpcProvider和RpcConsumer协商protobuf数据类型
// service_name method_name args

// 有用户的读写事件的回调函数
void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr &conn, 
                            muduo::net::Buffer *buf,
                            muduo::Timestamp timestamp) {
    // 远程RPC调用的字符数据 Login args 方法名和参数都要有
    std::string recv_buf = buf->retrieveAllAsString();
    // 从字符流中读取前4个字节的首部长度
    uint32_t header_size = 0;
    recv_buf.copy((char*)&header_size, 4, 0);

    // 截取原始的首部字符串
    std::string header_str = recv_buf.substr(4, header_size);
    rpc::RpcHeader rpcHeader;
    // 反序列化首部的字符串
    std::string service_name;
    std::string method_name;
    uint32_t args_size;
    if (rpcHeader.ParseFromString(header_str)) {
        // 反序列化成功
        service_name = rpcHeader.service_name();
        method_name = rpcHeader.method_name();
        args_size = rpcHeader.args_size();
    } else {
        std::cout << "rpc header : " << header_str << "parse error!" << std::endl;
        return;
    }
    // 获取方法的参数原始字符串
    std::string args_str = recv_buf.substr(4 + header_size, args_size);

    // 打印调试信息
    std::cout << "====================rpc provider====================" << std::endl;
    std::cout << "header_size : " << header_size << std::endl;
    std::cout << "service_name : " << service_name << std::endl;
    std::cout << "method_name : " << method_name << std::endl;
    std::cout << "args_size : " << args_size << std::endl;
    std::cout << "args_str : " << args_str << std::endl;
    std::cout << "====================================================" << std::endl;

    // 获取service对象和Method对象
    auto service_item = m_serviceMap.find(service_name);
    if (service_item == m_serviceMap.end()) {
        std::cout << service_name << " is not exist !" << std::endl;
        return;
    }
    
    auto method_item = service_item->second.m_methodMap.find(method_name);
    if (method_item == service_item->second.m_methodMap.end()) {
        std::cout << service_name << ":" << method_name << " is not exist !" << std::endl;
        return;
    }
    google::protobuf::Service *service = service_item->second.m_service; // 获取service对象
    const google::protobuf::MethodDescriptor *method = method_item->second; // 获取method对象

    // 生成rpc调用的请求request和响应response参数
    google::protobuf::Message *request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(args_str)) {
        std::cout << "args_str : " << args_str << " parse error !" << std::endl;
        return;
    }
    google::protobuf::Message *response = service->GetResponsePrototype(method).New();
    
    // 给下面的method方法的调用，绑定一个Closure的回调函数
    google::protobuf::Closure *done = google::protobuf::NewCallback<RpcProvider,
                                                                    const muduo::net::TcpConnectionPtr&,
                                                                    google::protobuf::Message*>
                                                                    (this,
                                                                    &RpcProvider::SendRpcResponse, 
                                                                    conn,
                                                                    response);
    // 在框架上根据远端的请求，调用相应的方法处理
    // void Login(controller, request, response, done)
    service->CallMethod(method, nullptr, request, response, done);
}

void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message* response) {
    std::string response_str;
    // response的序列化
    if (response->SerializeToString(&response_str)) {
        // 序列化成功后，通过网络将rpc方法的结果发送给对方
        conn->send(response_str);
    } else {
        std::cout << "serialize response_str error !" << std::endl;
    }
    // 关闭连接，模拟HTTP短连接
    conn->shutdown();
}