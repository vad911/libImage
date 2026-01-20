#pragma once

#include <imageReader/threadPool.h>
#include <thread>

namespace mylibImageReader
{

class ImageContext
{
public:
    static ImageContext& instance()
    {
        static ImageContext ctx;
        return ctx;
    }

    ThreadPool& threadPool() noexcept
    {
        return m_threadPool;
    }

    int threadCount() const noexcept
    {
        return m_threadPool.threadCount();
    }

private:
    ImageContext()
        : m_threadPool(std::thread::hardware_concurrency())
    {
    }

    ~ImageContext() = default;

    ImageContext(const ImageContext&) = delete;
    ImageContext& operator=(const ImageContext&) = delete;

private:
    ThreadPool m_threadPool;
};

} // namespace mylibImageReader
