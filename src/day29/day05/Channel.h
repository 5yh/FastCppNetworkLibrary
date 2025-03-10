#pragma once
#include <sys/epoll.h>

class Epoll;
class Channel
{
private:
    Epoll *ep; // 每一个套接字对应一个epoll指针
    int fd;
    uint32_t events;
    uint32_t revents;
    bool inEpoll;

public:
    Channel(Epoll *ep, int _fd);
    ~Channel();
    void enableReading();

    int getFd();
    uint32_t getEvents();
    uint32_t getRevents();
    bool getInEpoll();
    void setInEpoll();

    void setRevents(uint32_t);
};
