#pragma once

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>


class RpcChannelMethod : public google::protobuf::RpcChannel {
public:
    // 所有通过Stub代理对象的方法，最后都在这里进行调用，统一做序列化和网络发送
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                    google::protobuf::RpcController* controller,
                    const google::protobuf::Message* request,
                    google::protobuf::Message* response, 
                    google::protobuf::Closure* done);

};