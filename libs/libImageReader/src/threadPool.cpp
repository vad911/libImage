#include  <imageReader/threadPool.h>

namespace mylibImageReader
{

ThreadPool::ThreadPool(int threads)
{
    if (threads <= 0)
        threads = std::thread::hardware_concurrency();

    if (threads <= 0)
        threads = 1;

    m_threadCount = threads;

    for (int i = 0; i < m_threadCount; ++i)
    {
        m_workers.emplace_back([this]()
        {
            workerLoop();
        });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard lock(m_mutex);
        m_stop = true;
    }

    m_cvTask.notify_all();

    for (auto& t : m_workers)
        t.join();
}

void ThreadPool::parallelFor(
    int begin,
    int end,
    int grainSize,
    const std::function<void(int, int)>& fn
)
{
    if (begin >= end)
        return;

    if (m_threadCount <= 1 || (end - begin) <= grainSize)
    {
        fn(begin, end);
        return;
    }

    {
        std::lock_guard lock(m_mutex);

        for (int i = begin; i < end; i += grainSize)
        {
            Task task;
            task.begin = i;
            task.end   = std::min(i + grainSize, end);
            task.fn    = fn;

            m_tasks.push_back(task);
            m_activeTasks.fetch_add(1, std::memory_order_relaxed);
        }
    }

    m_cvTask.notify_all();

    std::unique_lock lock(m_mutex);
    m_cvDone.wait(lock, [&]()
    {
        return m_activeTasks.load(std::memory_order_relaxed) == 0;
    });
}

void ThreadPool::workerLoop()
{
    while (true)
    {
        Task task;

        {
            std::unique_lock lock(m_mutex);
            m_cvTask.wait(lock, [&]()
            {
                return m_stop || !m_tasks.empty();
            });

            if (m_stop && m_tasks.empty())
                return;

            task = std::move(m_tasks.front());
            m_tasks.pop_front();
        }

        task.fn(task.begin, task.end);

        if (m_activeTasks.fetch_sub(1, std::memory_order_relaxed) == 1)
        {
            std::lock_guard lock(m_mutex);
            m_cvDone.notify_one();
        }
    }
}

} // namespace mylibImageReader
