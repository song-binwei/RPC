#include "rpc_application.h"
#include "rpc_config.h"
#include <iostream>
#include <unistd.h>

RpcConfig RpcApplication::rpc_config;

void showArgHelp() {
    std::cout << "format : command -i <configfile>" << std::endl;
}

void RpcApplication::Init(int argc, char** argv) 
{
    if(argc < 2) {
        showArgHelp();
        exit(EXIT_FAILURE);
    }
    int c = 0;
    std::string config_file;
    while ((c = getopt(argc, argv, "i:")) != -1){
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            std::cout << "invalid args" << std::endl;
            showArgHelp();
            exit(EXIT_FAILURE);
        case ':':
            std::cout << "need <configfile>" << std::endl;
            showArgHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }
    rpc_config.LoadConfigFile(config_file);
    // std::cout << "rpcserverip = " << rpc_config.Load("rpcserverip") << std::endl;
    // std::cout << "rpcserverport = " << rpc_config.Load("rpcserverport") << std::endl;
    // std::cout << "zookeeperip = " << rpc_config.Load("zookeeperip") << std::endl;
    // std::cout << "zookeeperport = " << rpc_config.Load("zookeeperport") << std::endl;
}
RpcApplication&  RpcApplication::GetInstance() {
    static RpcApplication app;
    return app;
}
RpcConfig& RpcApplication::GetConfig() {
    return rpc_config;
}