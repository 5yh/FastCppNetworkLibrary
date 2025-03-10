#pragma once
#include <sys/epoll.h>
#include <vector>

class Channel;
class Epoll
{
private:
    int epfd;
    struct epoll_event *events;

public:
    Epoll();
    ~Epoll();

    void addFd(int fd, uint32_t op);
    void UpdateChannel(Channel *);
    // 返回活动的Channels既fd
    std::vector<Channel *> poll(int timeout = -1);
};
