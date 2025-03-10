#pragma once
#include <functional>

class Epoll;
class Channel;
class EventLoop
{
private:
    Epoll *ep;
    // quit的作用？
    // 目前没啥用，始终是false
    bool quit;

public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel *);
};