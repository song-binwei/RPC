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



## 目录树

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
│   │   ├── rpc_config.h         解析配置文件模块
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

## 项目代码交互过程

RPC服务提供方：

1、初始化服务，读取配置文件init.conf，获取的RPC服务发布的IP和Port（远程方法将要发布的地址和端口），ZooKeeper的IP和Port。

2、维护一个unordered_map表存储存储注册成功的服务名字和服务的信息。

3、通过util_zookeeper中相关方法，向ZooKeeper注册服务和方法发布的IP和Port。

4、使用muduo网络库创建4个线程，一个I/O线程等待连接，3个工作线程处理请求并返回，绑定回调函数，启动服务节点。

5、等待接收远程的请求。

6、如果有请求过来，反序列化请求参数，根据参数调用具体方法，得到返回，再次序列化响应，网络发送给服务调用方。

RPC服务调用方：

1、初始化，读取配置文件init.conf，获取ZooKeeper的IP和Port

2、创建远程服务对象，定义RPC请求参数和响应参数

3、发起RPC的调用，同步的调用 wait结果，调用服务对象的具体方法。

4、进入RpcChannelMethod::CallMethod方法（通过Stub代理对象的方法，最后都在这里进行调用，统一做序列化和网络发送）

5、返回RPC响应，关闭连接

交互过程如图所示：

![](https://github.com/song-binwei/RPC/blob/main/img/RPC%E9%A1%B9%E7%9B%AE%E4%BB%A3%E7%A0%81%E4%BA%A4%E4%BA%92%E5%9B%BE.png)
