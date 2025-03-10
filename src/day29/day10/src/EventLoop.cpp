#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include "ThreadPool.h"
#include <vector>

EventLoop::EventLoop() : ep(nullptr), threadPool(nullptr), quit(false)
{
    ep = new Epoll();
    threadPool = new ThreadPool();
}

EventLoop::~EventLoop()
{
    delete ep;
}

void EventLoop::loop()
{
    while (!quit)
    {
        std::vector<Channel *> chs;
        chs = ep->poll();
        for (auto it : chs)
        {
            it->handleEvent();
        }
        // for (auto it = chs.begin(); it != chs.end(); it++)
        // {
        //     // 先解引用迭代器，然后再调用元素的成员函数
        //     // 不加括号会直接调用迭代器对象的成员函数
        //     (*it)->handleEvent();
        // }
    }
}

void EventLoop::updateChannel(Channel *ch)
{
    ep->updateChannel(ch);
}

void EventLoop::addThread(std::function<void()> func)
{
    threadPool->add(func);
}