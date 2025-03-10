#pragma once
#include <sys/epoll.h>
#include <functional>
class Socket;
class EventLoop;
class Channel
{
private:
    EventLoop *loop;
    int fd;
    uint32_t events;
    uint32_t ready; // 当前准备好的事件
    bool inEpoll;
    bool useThreadPool;
    std::function<void()> readCallback;
    std::function<void()> writeCallback;

public:
    Channel(EventLoop *_loop, int _fd);
    ~Channel();

    void handleEvent();
    void enableRead();

    int getFd();
    uint32_t getEvents();
    uint32_t getReady();
    bool getInEpoll();
    // 这是什么？
    void setInEpoll(bool _in = true);
    void useET();

    // void setEvents(uint32_t);
    void setReady(uint32_t);
    void setReadCallback(std::function<void()>);
    void setUseThreadPool(bool use = true);
};
