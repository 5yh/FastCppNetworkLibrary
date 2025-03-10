#include "EventLoop.h"
#include <vector>
#include "Channel.h"
#include "Epoller.h"

EventLoop::EventLoop()
{
    poller_ = std::make_unique<Epoller>();
}

EventLoop::~EventLoop() {}

void EventLoop::Loop() const
{
    while (true)
    {
        for (Channel *active_ch : poller_->Poll())
        {
            // 取出来事件调用绑定的函数
            active_ch->HandleEvent();
        }
    }
}
// 调用poller的函数
void EventLoop::UpdateChannel(Channel *ch) const { poller_->UpdateChannel(ch); }
void EventLoop::DeleteChannel(Channel *ch) const { poller_->DeleteChannel(ch); }