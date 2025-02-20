#include "EventLoopThread.h"
#include "EventLoop.h"
#include <mutex>
#include <thread>
#include <condition_variable>

EventLoopThread::EventLoopThread() : loop_(nullptr) {}

EventLoopThread::~EventLoopThread() {}

EventLoop *EventLoopThread::StartLoop()
{
    // 绑定当前线程的所执行的函数，并创建子线程
    // 在这个线程中创建EventLoop.

    // bind绑定对象和函数在一起，调用也一起调用
    // thread创建新线程执行了函数对象，这个函数
    // 对象中的函数调用的成员变量是之前绑定的this中的那些吗？
    thread_ = std::thread(std::bind(&EventLoopThread::ThreadFunc, this));
    EventLoop *loop = nullptr;
    {
        std::unique_lock<std::mutex> lock(mutex_);

        while (loop_ == NULL)
        {
            // 等待子线程传一个loop_回来
            cv_.wait(lock);
        }

        loop = loop_;
    }
    return loop;
}
// 看前面的注释
// 这个函数是函数对象绑定后调用的,所以里面的成员变量也都是当时绑定的this,主线程对象里的
void EventLoopThread::ThreadFunc()
{

    EventLoop loop; // 栈空间,但这个函数压根不会结束所以没事
    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;
        cv_.notify_one(); // 此时只有主线程在等待,所以环形的一定是主线程
    }
    loop_->Loop();
    // loop退出了才会到后面
    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = nullptr;
    }
}