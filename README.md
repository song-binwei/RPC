# RPC框架
应用技术：C++、protobuf、muduo、ZooKeeper
项目描述：本项目解决远程服务间的通信问题，核心功能是远程过程调用（RPC）、服务注册与发布、以及高效数据传输和网络通信。
1、实现Application、Provider、Channel三个核心模块，即框架初始化、服务注册与发布、服务调用；
2、使用protobuf进行数据序列化和反序列化，以字节流进行数据传输，并设计包头+包体，防止粘包；
3、使用muduo库进行网络通信，基于Reactor网络模型，实现epoll+线程池的高性能网络通信；
4、使用ZooKeeper作为服务注册中心，服务调用方通过ZooKeeper发现服务提供方的主机和端口；