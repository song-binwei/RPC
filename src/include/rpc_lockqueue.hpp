#pragma once

#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class LockQueue {
public:
    // 多个线程写日志queue
    void Push(const T &data) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_conditionVariable.notify_one();

    }

    // 一个线程负责读queue
    T Pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.empty())
        {
            m_conditionVariable.wait(lock);
        }
        T data = m_queue.front();
        m_queue.pop();
        return data;
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
};