#include "util_zookeeper.h"
#include "rpc_application.h"
#include <iostream>
#include <string>

// 全局的watcher观察器，zkserver给zkclient的通知
void globalWatcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx) 
{
    if (type == ZOO_SESSION_EVENT) { 
        if (state == ZOO_CONNECTED_STATE) {  // zkclient和zkserver连接成功
            sem_t *sem = (sem_t*)zoo_get_context(zh);
            sem_post(sem);
        }
    }
}

ZkClient::ZkClient() : m_zhandle(nullptr)
{

}
ZkClient::~ZkClient()
{
    if (m_zhandle != nullptr) 
    {
        zookeeper_close(m_zhandle);   // 关闭句柄释放资源
    }
}
// zkclient启动连接zkserver
void ZkClient::Start()
{
    std::string host = RpcApplication::GetInstance().GetConfig().Load("zookeeperip");
    std::string port = RpcApplication::GetInstance().GetConfig().Load("zookeeperport");
    std::string connstr = host + ":" + port;
    
    /*
    zookeeper_mt ： 多线程版本
    API客户端一共有3个线程：
    1、API调用线程
    2、网络I/O线程      pthread_create poll
    3、watcher回调线程  pthread_create
    */
    m_zhandle = zookeeper_init(connstr.c_str(), globalWatcher, 30000, nullptr, nullptr, 0);
    if (m_zhandle == nullptr)
    {
        std::cout << "zookeeper_init error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(m_zhandle, &sem);

    sem_wait(&sem);
    std::cout << "zookeeper_init success !" << std::endl;
}
// 在zkserver上根据指定的path创建znode节点
void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    char path_buf[128];
    int buf_len = sizeof(path_buf);

    int ret = zoo_exists(m_zhandle, path, 0, nullptr);

    if (ret == ZNONODE) 
    {
        ret = zoo_create(m_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, path_buf, buf_len);
        if (ret == ZOK)
        {
            std::cout << "znode create success... path : " << path << std::endl;
        }
        else
        {
            std::cout << "ret : " << ret << std::endl;
            std::cout << "znode create error... path : " << path << std::endl;
            exit(EXIT_FAILURE);
        }

    }
}
// 根据参数指定的znode节点路径，获取znode节点的值
std::string ZkClient::GetData(const char *path)
{
    char buf[128];
    int buf_len = sizeof(buf);
    std::cout << "GetData path : " << path << std::endl;
    int ret = zoo_get(m_zhandle, path, 0, buf, &buf_len, nullptr);
    if (ret != ZOK) 
    {
        std::cout << "get znode error... path : " << path << std::endl;
        return "";
    }
    else 
    {
        return buf;
    }
}