#include "ThreadPool.h"

ThreadPool::ThreadPool(int size) : stop(false)
{
    for (int i = 0; i < size; i++)
    {
        // 使用lambda定义每个工作线程的工作函数
        threads.emplace_back(std::thread([this]()
                                         {
            while(true){
                // 每个工作线程取任务
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(tasks_mtx);
                    // 这样会导致假唤醒
                    // cv.wait(lock);
                    // bool 的谓词(predicate)函数
                    // True如果线程池停止了或任务队列不为空则唤醒
                    // False反之，如果任务队列为空了且线程池没停止，说明目前不需要子线程运行，所以继续等
                    cv.wait(lock,[this](){
                        return stop||!tasks.empty();
                    });
                    // 已经结束来
                    // 注意如果结束但还有任务则继续运行直到结束
                    if(stop&&tasks.empty()) return;
                    // 取一个任务
                    task=tasks.front();
                    tasks.pop();
                }
                task();
            } }));
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);
        stop = true;
    }
    // 唤醒全部
    cv.notify_all();
    for (std::thread &th : threads)
    {
        // 查看线程是否仍在运行，如果是就等
        // 是一个可加入的线程
        if (th.joinable())
            th.join();
    }
}
