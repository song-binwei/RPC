#pragma once

#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class LockQueue {
public:
    void Push(const T &data);
    T& Pop();

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
};