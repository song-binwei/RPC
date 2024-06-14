#pragma once
#include <google/protobuf/service.h>
#include <string>

class RpcController : public google::protobuf::RpcController
{
public:
    RpcController();
    void Reset();
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string& reason);

    // 目前为实现功能
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure* callback);

private:
    bool m_failed;            // RPC方法执行过程中的状态
    std::string m_errorText;  // RPC方法执行过程中的错误消息
};