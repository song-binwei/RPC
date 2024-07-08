#include <iostream>
#include <string>
#include <vector>
#include "user.pb.h" 
#include "friend.pb.h"
#include "rpc_provider.h"
#include "rpc_application.h"
#include "rpc_logger.h"

/*
发布本地的方法为远程的RPC方法
*/

// 本地的一个类UserService下有2个方法
// 1、登录方法Login()
// 2、注册方法Regist()
class UserService : public fixbug::UserServiceRPC
{
public:
    bool Login(std::string name, std::string pwd) {
        std::cout << "Locate Login : " << std::endl;
        std::cout << "name : " << name << " pwd : " << pwd << std::endl;
        return false;
    };

    bool Regist(int id, std::string name, std::string pwd) {
        std::cout << "Regist service run " << std::endl;
        std::cout << "id : " << id << std::endl;
        std::cout << "name : " << name << std::endl;
        std::cout << "pwd : " << pwd << std::endl;
        return true;
    }
    /*
    重写UserServiceRPC基类的虚函数、下面这些方法在框架直接调用
    1. caller -> Login(LoginRequest) -> muduo -> callee
    2. callee -> Login(LoginRequest) -> 重写的Login方法上
    */
    // 重写protobuf框架的中对应的虚函数，实现1、获取请求参数 2、做本地业务 3、写入返回参数 4、执行回调 共计4个步骤
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 1、获取请求参数 用户名 密码
        std::string name = request->name();
        std::string pwd = request->pwd();
        
        // 2、做本地业务
        bool login_ret = this->Login(name, pwd);

        // 3、写入返回参数
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("error !");
        response->set_success(login_ret);

        // 4、执行回调，将响应的数据序列化后网络发送。
        done->Run();
    }

    void Regist(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegistRequest* request,
                       ::fixbug::RegistResponse* response,
                       ::google::protobuf::Closure* done) 
    {
        int id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool ret = this->Regist(id, name, pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);

        done->Run();
    }
};


// 获取好友列表的类，继承自GetFriendsListServiceRPC，重写方法，提供服务
class FriendsList : public fixbug::GetFriendsListServiceRPC 
{
public:
    // 本地服务
    std::vector<std::string> GetFriendsList(int id) {
        std::cout << "GetFriendsList service run ! " << std::endl;
        std::vector<std::string> friends_list = {"song binwei", "deng wangtao", "zhaoyi", "pangbo"};
        return friends_list;
    }
    // 远程RPC服务
    void GetFriendsList(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendsListRequest* request,
                       ::fixbug::GetFriendsListResponse* response,
                       ::google::protobuf::Closure* done) 
    {
        int id = request->id();

        std::vector<std::string> friends_list = this->GetFriendsList(id);

        response->set_success(true);

        for (int i = 0; i < friends_list.size(); i++) {
            std::string *p = response->add_frieds();
            *p = friends_list[i];
        }
        
        done->Run();
    }


};

int main(int argc, char** argv) {

    // RPC服务端启动示例 provider -i init.conf
    LOG_INFO("RPC init!");
    RpcApplication::Init(argc, argv);

    // provider是一个网络服务对象，发布UserService到一个RPC节点
    RpcProvider provider;
    provider.NotifyService(new UserService());
    provider.NotifyService(new FriendsList());

    // 启动RPC服务节点，阻塞等待RPC的请求
    provider.Run();
    return 0;
}