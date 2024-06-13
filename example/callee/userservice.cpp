#include <iostream>
#include <string>
#include "user.pb.h"
#include "rpc_provider.h"
#include "rpc_application.h"

class UserService : public fixbug::UserServiceRPC
{
public:
    bool Login(std::string name, std::string pwd) {
        std::cout << "Locate Login : " << std::endl;
        std::cout << "name : " << name << " pwd : " << pwd << std::endl;
        return false;
    };
    /*
    重写UserServiceRPC基类的虚函数、下面这些方法在框架直接调用
    1. caller -> Login(LoginRequest) -> muduo -> callee
    2. callee -> Login(LoginRequest) -> 重写的Login方法上
    */
    // 重写框架的虚函数，实现获取数据、处理业务、装载数据、执行回调共计4个步骤
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 1、获取传递的参数
        std::string name = request->name();
        std::string pwd = request->pwd();
        
        // 2、做本地的业务
        bool login_res = Login(name, pwd);

        // 3、写入响应
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(1);
        code->set_errmsg("error !");
        response->set_success(login_res);

        // 4、执行回调操作，将响应的数据序列化后网络发送。
        done->Run();
    }
};

int main(int argc, char** argv) {
    
    // UserService us;
    // us.Login("xxx", "xxx");

    // RPC配置初始化 provider -i config.conf
    RpcApplication::Init(argc, argv);

    // provider是一个网络服务对象，发布UserService到一个RPC节点
    RpcProvider provider;
    provider.NotifyService(new UserService());

    // 启动RPC服务节点，阻塞等待RPC的请求
    provider.Run();

    return 0;
}