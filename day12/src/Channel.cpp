#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <stdio.h>

Channel::Channel(EventLoop *_loop, int _fd)
    : loop(_loop), fd(_fd), events(0), ready(0), inEpoll(false) {}

Channel::~Channel()
{
    if (fd != -1)
    {
        close(fd);
        fd = -1;
    }
}

// void Channel::handleEvent()
// {
//     // 现在不直接调用回调函数，改为往线程池里加任务
//     loop->addThread(callback);
//     // callback();
// }
void Channel::handleEvent()
{
    // 是普通读事件还是高优先级读事件
    if (ready & (EPOLLIN | EPOLLPRI))
    {
        readCallback();
    }
    if (ready & (EPOLLOUT))
    {
        writeCallback();
    }
}
void Channel::enableRead()
{
    events |= EPOLLIN | EPOLLPRI;
    loop->updateChannel(this);
}

// 边缘触发
void Channel::useET()
{
    events |= EPOLLET;
    loop->updateChannel(this);
}
int Channel::getFd()
{
    return fd;
}

uint32_t Channel::getEvents()
{
    return events;
}
uint32_t Channel::getReady()
{
    return ready;
}

bool Channel::getInEpoll()
{
    return inEpoll;
}
// 这个函数有什么用？
// 删除channel时传false,代表此channel已不在事件循环中
void Channel::setInEpoll(bool _in)
{
    inEpoll = _in;
}

// void Channel::setEvents(uint32_t _ev){
//     events = _ev;
// }

void Channel::setReady(uint32_t _ev)
{
    ready = _ev;
}

void Channel::setReadCallback(std::function<void()> _cb)
{
    readCallback = _cb;
}
