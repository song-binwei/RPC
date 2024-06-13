#pragma once

#include <string>
#include <unordered_map>


// 读取配置文件 rpcserverip rpcserverport zookeeperip zookeeperport
class RpcConfig 
{
public:
    void LoadConfigFile(const std::string config_file);
    std::string Load(const std::string &key);
private:
    std::unordered_map<std::string, std::string> m_config;
    void Trim(std::string &str_buf);
};