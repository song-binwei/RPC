#include "rpc_channel.h"
#include "rpc_header.pb.h"
#include "util_zookeeper.h"
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h> // 包含read、write和close函数
#include "rpc_controller.h"
/*
header_size + service_name method_name args_size + args
*/

// 所有通过Stub代理对象的方法，最后都在这里进行调用，统一做序列化和网络发送
void RpcChannelMethod::CallMethod(const google::protobuf::MethodDescriptor* method,
                            google::protobuf::RpcController* controller,
                            const google::protobuf::Message* request,
                            google::protobuf::Message* response, 
                            google::protobuf::Closure* done) {
    
    const google::protobuf::ServiceDescriptor* service = method->service();
    std::string service_name = service->name();   // 获取服务的名称
    std::string method_name = method->name();     // 获取方法的名称
    uint32_t args_size = 0;
    std::string args_str;

    if (request->SerializeToString(&args_str)) {
        args_size = args_str.size();
    } else {
        controller->SetFailed("serialize request error !");
        return;
    }

    // 定义RPC的请求header
    rpc::RpcHeader rpc_header;
    rpc_header.set_service_name(service_name);
    rpc_header.set_method_name(method_name);
    rpc_header.set_args_size(args_size);

    // 序列化请求头
    uint32_t header_size = 0;
    std::string rpc_header_str;
    if (rpc_header.SerializeToString(&rpc_header_str)) {
        header_size = rpc_header_str.size();
    } else {
        controller->SetFailed("serialize rpc_header error !");
        return;
    }

    // 组织待发送的字符串 header_size + service_name method_name args_size + args
    std::string send_rpc_str;
    send_rpc_str.insert(0, std::string((char*)&header_size, 4));  // 请求头的长度
    send_rpc_str += rpc_header_str; // 请求头的序列化
    send_rpc_str += args_str;       // 参数的序列化

    // 打印调试信息
    std::cout << "==================RPC Call==================" << std::endl;
    std::cout << "header_size : " << header_size << std::endl;
    std::cout << "service_name : " << service_name << std::endl;
    std::cout << "method_name : " << method_name << std::endl;
    std::cout << "args_size : " << args_size << std::endl;
    std::cout << "args_str : " << args_str << std::endl;
    std::cout << "============================================" << std::endl;

    int clientFd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFd == -1) {
        char errortxt[512] = {0};
        sprintf(errortxt, "socket create error! errno : %d", errno);
        controller->SetFailed(errortxt);
        return;
    }
    // 获取RPC服务的地址和端口
    // std::string ip = RpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    // uint16_t port = atoi(RpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    // 通过ZooKeeper获取
    ZkClient zkCli;
    zkCli.Start();
    std::string method_path = "/" + service_name + "/" + method_name;
    std::string host_data = zkCli.GetData(method_path.c_str());
    if (host_data == "") 
    {
        controller->SetFailed(method_path + " is not exist !");
        return;
    }
    int idx = host_data.find(":");
    if (idx == -1)
    {
        controller->SetFailed(method_path + " address is error !");
        return;
    }
    std::string ip = host_data.substr(0, idx);
    uint16_t port = atoi(host_data.substr(idx + 1, host_data.size() - idx).c_str());
 
    // 设置发起网络请求需要的port和address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    // 连接RPC服务的节点
    int ret = connect(clientFd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (ret == -1) {
        char errortxt[512] = {0};
        sprintf(errortxt, "rpc connect error ! errno : %d", errno);
        controller->SetFailed(errortxt);
        close(clientFd);
        return;
    }
    
    // 发送RPC的请求字符串
    ret = send(clientFd, send_rpc_str.c_str(), send_rpc_str.size(), 0);

    if (ret == -1) {
        close(clientFd);
        char errortxt[512] = {0};
        sprintf(errortxt, "rpc send error ! errno : %d", errno);
        controller->SetFailed(errortxt);
        return;
    }

    // 接收RPC的响应
    char recv_buf[1024] = {0};
    int recv_size = recv(clientFd, recv_buf, 1024, 0);
    if (recv_size == -1) {
        close(clientFd);
        char errortxt[512] = {0};
        sprintf(errortxt, "rpc recv error ! errno : %d", errno);
        controller->SetFailed(errortxt);
        return;
    }
    
    // 反序列化RPC服务返回的数据
    // std::string response_str(recv_buf, 0, recv_size); 出现错误

    if (!response->ParseFromArray(recv_buf, recv_size))  {
        close(clientFd);
        char errortxt[512] = {0};
        sprintf(errortxt, "rpc response error ! errno : %d", errno);
        controller->SetFailed(errortxt);
        return;
    }
    close(clientFd);    
}