#pragma once
class Epoll;
class Channel;
class EventLoop // 事件循环，我们添加需要监听的事务到这个事件循环内，每次有事件发生时就会通知（在程序中返回给我们Channel），然后根据不同的描述符、事件类型进行处理（以回调函数的方式）。
{
private:
    Epoll *ep;
    bool quit;

public:
    EventLoop();
    ~EventLoop();
    // loop开始事件驱动，实际上就是epoll_wait
    void loop();
    void updateChannel(Channel *);
};