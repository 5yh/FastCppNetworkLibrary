#pragma once
#include <functional>
#include <stdio.h>
#include <errno.h>
class EventLoop;
class Socket;
class Channel;
class Connection
{
private:
    EventLoop *loop;
    Socket *sock;
    Channel *channel;
    std::function<void(Socket *)> deleteConnectionCallback;

public:
    Connection(EventLoop *_loop, Socket *_sock);
    ~Connection();
    // 回显给客户端的函数
    void echo(int sockfd);
    void setDeleteConnectionCallback(std::function<void(Socket *)>);
};