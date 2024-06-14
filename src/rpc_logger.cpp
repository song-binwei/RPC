#include "rpc_logger.h"
#include <thread>
#include <time.h>
#include <iostream>

Logger& Logger::GetInstance() {
    static Logger logger;
    return logger;
};

// 构造函数
Logger::Logger() {
    // 启动写日志的线程
    std::thread writeLogTask([&]() {
        while (true) 
        {
            // 获取当前的日期，写入日志中
            time_t now = time(nullptr);
            tm *nowtm = localtime(&now);
            
            // 设置日志文件的名称
            char file_name[128];
            sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year + 1900, nowtm->tm_mon + 1, nowtm->tm_mday);

            // 打开该日志文件并写入
            FILE *pf = fopen(file_name, "a+");

            // 如果打不开，就直接退出
            if (pf == nullptr) {
                std::cout << "logger file : " << file_name << " open error !" << std::endl;
                exit(EXIT_FAILURE);
            }
            // 从队列中取出一条消息
            auto log_element = m_lockQueue.Pop();
            LogLevel level = log_element.first;
            std::string msg = log_element.second;

            char time_buf[128] = {0};
            std::cout << "m_logLevel : " << level << std::endl;
            sprintf(time_buf, "%d:%d:%d => [%s] ", 
                                    nowtm->tm_hour, 
                                    nowtm->tm_min, 
                                    nowtm->tm_sec, 
                                    (level == LogLevel::INFO ? "info" : "error"));

            msg.insert(0, time_buf);
            msg.append("\n");

            fputs(msg.c_str(), pf);
            fclose(pf);
        }
    });
    // 设置分离线程，守护线程
    writeLogTask.detach();

}


// 写日志
void Logger::Log(LogLevel level, std::string message) {
    m_lockQueue.Push(std::make_pair(level, message));
};