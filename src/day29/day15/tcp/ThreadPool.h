#pragma once
#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include "common.h"
class ThreadPool
{
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex tasks_mtx;
    std::condition_variable cv;
    std::atomic<bool> stop_{false};

public:
    ThreadPool(int size = std::thread::hardware_concurrency());
    ~ThreadPool();
    // void add(std::function<void()>);
    // 最逆天的来了！
    // 为了添加事件更快，写一大堆模板和右值绑定
    // 两个引用是完美转发使用的，可以做到左值传完还是左值，右值传完还是右值
    // std::forward完美转发
    template <class F, class... Args>
    // future用于异步操作，可以之后取值
    // typename一大堆用于返回值
    auto add(F &&f, Args &&...args)
        -> std::future<typename std::result_of<F(Args...)>::type>;
};
// add函数的实现不能放在cpp，因为模板不能分离编译

template <class F, class... Args>
auto ThreadPool::add(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>
{
    // typename用来强制指定后面的东西一定是一个类型，而不是同名的一个成员变量
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);
        if (stop_) // 听了不给加
        {
            throw std::runtime_error("enqueue on a stopped ThreadPool");
        }
        // sb语法：方括号task代表在lambda函数里用到这个参数,lambda表达式的捕获列表
        // 捕获了task智能指针保证任务在执行时仍然有效
        // 第一个()表示不接受参数哈
        // (*task)解引用智能指针得到packaged_task对象
        // ()表示执行，实际上是运算符重载，packaged_task重载了括号
        // 你无敌了
        tasks.emplace([task]()
                      { (*task)(); });
    }
    cv.notify_one();
    // 返回的是future对象，允许异步获取task算出来的结果
    return res;
}
