#pragma once

class TcpServer;
class EventLoop;
class Poller;
class PollPoller;
class Acceptor;
class Connection;
class Channel;
class Socket;
class Buffer;
class ThreadPool;

// macros to disable copying and moving
// 删除拷贝构造函数
// 删除拷贝运算符
// warning: backslash-newline at end of file
// 最后加一个空行就好了
#define DISALLOW_COPY(cname)       \
    cname(const cname &) = delete; \
    cname &operator=(const cname &) = delete;

#define DISALLOW_MOVE(cname)  \
    cname(cname &&) = delete; \
    cname &operator=(cname &&) = delete;

#define DISALLOW_COPY_AND_MOVE(cname) \
    DISALLOW_COPY(cname);             \
    DISALLOW_MOVE(cname);
