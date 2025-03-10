#pragma once
#include <functional>

class Epoll;
class Channel;
class ThreadPool;
class EventLoop
{
private:
    Epoll *ep;
    ThreadPool *threadPool;
    // quit的作用？
    // 目前没啥用，始终是false
    bool quit;

public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel *);
    void addThread(std::function<void()>);
};