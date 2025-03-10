#pragma once

#include "Epoller.h"
#include "common.h"
#include <memory>

class Epoller;
// 再把epoller包起来
// 提供更高层次的抽象，可以管理epoller的生命周期
// epoller中取ch
// eventloop中处理取出来的事件
class EventLoop
{
public:
    DISALLOW_COPY_AND_MOVE(EventLoop);
    EventLoop();
    ~EventLoop();

    void Loop() const;
    // 其实就是调用epoller的同名函数
    void UpdateChannel(Channel *ch) const;
    void DeleteChannel(Channel *ch) const;

private:
    std::unique_ptr<Epoller> poller_;
};