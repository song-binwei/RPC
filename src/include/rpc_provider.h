#pragma once

#include "google/protobuf/service.h"
#include <string>
#include <functional>
#include <muduo/net/TcpServer.h>
#include <google/protobuf/descriptor.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <unordered_map>

class RpcProvider
{
public:
    // 发布RPC方法的函数接口
    void NotifyService(google::protobuf::Service *service);

    // 启动RPC服务节点，开始提供RPC远程网络调用服务
    void Run();
private:
    muduo::net::EventLoop m_eventLoop;
    // service服务类型的信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service; // 保存服务的对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_methodMap; //保存服务的方法描述
    };
    // 存储注册成功的服务名字和服务的信息
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;
    // 新的socket连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    // 已建立连接用户的读写的回调
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp);
    // 框架发送返回的数据
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&, google::protobuf::Message*);
};

