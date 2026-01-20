#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <deque>
#include <atomic>

namespace mylibImageReader
{

class ThreadPool
{
public:
    explicit ThreadPool(int threads = 0);
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    void parallelFor(
        int begin,
        int end,
        int grainSize,
        const std::function<void(int, int)>& fn
    );

    int threadCount() const noexcept { return m_threadCount; }

private:
    struct Task
    {
        int begin;
        int end;
        std::function<void(int, int)> fn;
    };

    void workerLoop();

private:
    std::vector<std::thread> m_workers;
    std::deque<Task>         m_tasks;

    std::mutex               m_mutex;
    std::condition_variable  m_cvTask;
    std::condition_variable  m_cvDone;

    std::atomic<int>         m_activeTasks{0};
    bool                     m_stop{false};
    int                      m_threadCount{0};
};

} // namespace mylibImageReader
