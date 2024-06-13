#include <iostream>
#include "rpc_application.h"
#include "user.pb.h"
#include "rpc_channel.h"

int main(int argc, char** argv) {

    // 程序启动首先需要初始化，调用框架的初始化函数
    RpcApplication::Init(argc, argv);
    
    // 调用远程发布的方法
    fixbug::UserServiceRPC_Stub stub(new RpcChannelMethod());

    // rpc请求参数和响应参数定义
    fixbug::LoginRequest request;
    request.set_name("song binwei");
    request.set_pwd("123456");
    fixbug::LoginResponse response;

    // 发起RPC的调用，同步的调用 wait结果
    stub.Login(nullptr, &request, &response, nullptr);

    // 一次RPC调用成功，读取结果
    if (response.result().errcode() == 0) {
        std::cout << "RPC login response success : " << response.success() << std::endl;
    } else {
        std::cout << "RPC login response error : " << response.result().errcode() << std::endl;
        std::cout << "RPC login response errmsg : " << response.result().errmsg() << std::endl;
    }


    return 0;
}