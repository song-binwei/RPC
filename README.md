# RPC框架
## 应用技术
C++、protobuf、muduo、ZooKeeper

## 项目描述
本项目解决远程服务间的通信问题，核心功能是远程过程调用（RPC）、服务注册与发布、以及高效数据传输和网络通信。
## 主要功能
1. 实现Application、Provider、Channel三个核心模块，即框架初始化、服务注册与发布、服务调用；
2. 使用protobuf进行数据序列化和反序列化，以字节流进行数据传输，并设计包头+包体，防止粘包；
3. 使用muduo库进行网络通信，基于Reactor网络模型，实现epoll+线程池的高性能网络通信；
4. 使用ZooKeeper作为服务注册中心，服务调用方通过ZooKeeper发现服务提供方的主机和端口；
5. 封装标准库queue构建lockQueue模版类，由多个线程写日志队列，单个线程读，实现异步日志记录；

基本过程如下：

![](https://github.com/song-binwei/RPC/blob/main/img/RPC%E6%B5%81%E7%A8%8B%E5%9B%BE.png)

### 目录树

```
.
├── bin                          编译生成的example可执行文件 和 运行所需配置文件
│   ├── consumer
│   ├── init.conf
│   └── provider
├── CMakeLists.txt
├── example                      框架使用示例
│   ├── callee
│   │   ├── CMakeLists.txt
│   │   └── userservice.cpp
│   ├── caller
│   │   ├── callservice.cpp
│   │   └── CMakeLists.txt
│   ├── CMakeLists.txt
│   ├── friend.pb.cc
│   ├── friend.pb.h
│   ├── friend.proto
│   ├── user.pb.cc
│   ├── user.pb.h
│   └── user.proto
├── lib                          框架编译目标， 静态库
│   └── librpc.a
├── src                          框架源码
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── rpc_application.h    框架初始化模块
│   │   ├── rpc_channel.h        服务调用模块
│   │   ├── rpc_config.h		 解析配置文件模块
│   │   ├── rpc_controller.h     调用控制模块
│   │   ├── rpc_header.pb.h      框架请求头
│   │   ├── rpc_lockqueue.hpp    日志队列
│   │   ├── rpc_logger.h         日志模块
│   │   ├── rpc_provider.h       服务提供模块
│   │   └── util_zookeeper.h     ZooKeeper方法封装
│   ├── rpc_application.cpp
│   ├── rpc_channel.cpp
│   ├── rpc_config.cpp
│   ├── rpc_controller.cpp
│   ├── rpc_header.pb.cc
│   ├── rpc_header.proto
│   ├── rpc_logger.cpp
│   ├── rpc_provider.cpp
│   └── util_zookeeper.cpp
└── test
```

