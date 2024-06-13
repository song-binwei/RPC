#include "rpc_config.h"
#include <iostream>

void RpcConfig::LoadConfigFile(const std::string config_file) {
    // std::cout << config_file << std::endl;
    FILE *pf = fopen(config_file.c_str(), "r");
    if (pf == nullptr) {
        std::cout << config_file << " is not" << std::endl;
        exit(EXIT_FAILURE);
    }

    while(!feof(pf)) {
        char buf[512] = {0};
        fgets(buf, 512, pf);
        std::string read_buf(buf);
        Trim(read_buf);
        // 如果是注释或者是空行跳过处理
        if(read_buf[0] == '#' || read_buf[0] == '\n') {
            continue;
        }
        int idx = read_buf.find('=');
        if(idx == -1) {
            continue;
        }
        std::string key = read_buf.substr(0, idx);
        Trim(key);
        int endidx = read_buf.find('\n', idx);
        std::string value = read_buf.substr(idx + 1, endidx - idx - 1);
        Trim(value);
        // std::cout << "key = " << key << " value = " << value << std::endl;
        m_config.insert({key, value});
    }
};

std::string RpcConfig::Load(const std::string &key) {
    // 如果存在返回key对应的Value
    if(m_config.count(key)) return m_config[key];
    return "";
};

void RpcConfig::Trim(std::string &str_buf) {
    // 找到第一个不是空格的idx
    int idx = str_buf.find_first_not_of(' ');
    if(idx != -1) {
        str_buf = str_buf.substr(idx, str_buf.size() - idx);
    }

    // 找到倒数最后一个不是空格的idx
    idx = str_buf.find_last_not_of(' ');
    if(idx != -1) {
        str_buf = str_buf.substr(0, idx + 1);
    }
}