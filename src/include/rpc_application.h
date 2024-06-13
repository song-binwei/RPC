#pragma once

#include "rpc_config.h"

// 框架的基础类，用于提供初始化等操作
class RpcApplication 
{
public:
    static void Init(int argc, char** argv);
    static RpcApplication& GetInstance();
    static RpcConfig& GetConfig();
private:
    static RpcConfig rpc_config;
    RpcApplication(){};
    RpcApplication(const RpcApplication&) = delete;
    RpcApplication(RpcApplication&&) = delete;
};