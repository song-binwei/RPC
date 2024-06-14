# pragma once
#include <string>
#include "rpc_lockqueue.h"

// RPC 框架的日志系统

enum LogLevel {
    INFO,
    ERROR,
};

class Logger {
public:
    void setLogLevel(LogLevel level);
    void Log(std::string message);
    

private:
    int m_logLevel;  // 设置日志级别
    LockQueue<std::string> m_lockQueue;   // 设置日子的缓冲队列
    Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
};