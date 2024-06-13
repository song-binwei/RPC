#include <iostream>
#include "rpc_application.h"
#include "user.pb.h"
#include "friend.pb.h"
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

    // rpc请求参数和响应参数定义
    fixbug::RegistRequest regist_request;
    regist_request.set_id(1000);
    regist_request.set_name("RPC");
    regist_request.set_pwd("666666");
    fixbug::RegistResponse regist_response;

    // 发起RPC的调用，同步的调用 wait结果
    stub.Regist(nullptr, &regist_request, &regist_response, nullptr);

    // 一次RPC调用成功，读取结果
    if (regist_response.result().errcode() == 0) {
        std::cout << "RPC regist response success : " << regist_response.success() << std::endl;
    } else {
        std::cout << "RPC regist response error : " << regist_response.result().errcode() << std::endl;
        std::cout << "RPC regist response errmsg : " << regist_response.result().errmsg() << std::endl;
    }

    // 调用远程发布的方法
    fixbug::GetFriendsListServiceRPC_Stub stub_frieds(new RpcChannelMethod());

    // rpc请求参数和响应参数定义
    fixbug::GetFriendsListRequest friends_request;
    friends_request.set_id(3007);
    fixbug::GetFriendsListResponse friends_response;

    // 发起RPC的调用，同步的调用 wait结果
    stub_frieds.GetFriendsList(nullptr, &friends_request, &friends_response, nullptr);

    // 一次RPC调用成功，读取结果
    if (friends_response.success() == 1) {
        std::cout << "RPC friends response success : " << friends_response.success() << std::endl;
        int cnt = friends_response.frieds_size();
        for (int i = 0; i < cnt; i++) {
            std::cout << i + 1 << " name : " << friends_response.frieds(i) << std::endl;
        }
    } else {
        std::cout << "RPC friends response error : " << friends_response.success() << std::endl;
    }



    return 0;
}