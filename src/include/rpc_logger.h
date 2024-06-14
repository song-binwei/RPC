# pragma once
#include <string>
#include <mutex>
#include "rpc_lockqueue.hpp"

// RPC 框架的日志系统

enum LogLevel {
    INFO,  // 普通信息
    ERROR, // 错误信息
};

class Logger {
public:
    static Logger& GetInstance();
    void Log(LogLevel, std::string message);


private:
    LockQueue<std::pair<LogLevel, std::string>> m_lockQueue;   // 设置日志的缓冲队列 包含日志的级别和日志信息
    Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
};

// 定义宏
#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(LogLevel::INFO, c); \
    } while(0);

#define LOG_ERR(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(LogLevel::ERROR, c); \
    } while(0);
