#pragma once
#include "common.h"

#include <vector>
#include <sys/epoll.h>

class Channel;
// 对epoll中的channel进行处理
class Epoller
{
public:
    DISALLOW_COPY_AND_MOVE(Epoller);

    Epoller();
    ~Epoller();
    // 更新监听的channel
    void UpdateChannel(Channel *ch) const;
    // 删除监听的通道
    void DeleteChannel(Channel *ch) const;

    // 返回调用完epoll_wait的通道事件
    // 这是什么？
    std::vector<Channel *> Poll(long timeout = -1) const;

private:
    int fd_;
    struct epoll_event *events_;
};
