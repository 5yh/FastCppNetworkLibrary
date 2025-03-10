#pragma once
#include <functional>

class EventLoop;
class Socket;
class InetAddress;
class Channel;
class Acceptor
{
private:
    EventLoop *loop;
    Socket *sock;
    InetAddress *addr;
    Channel *acceptChannel;

public:
    Acceptor(EventLoop *_loop);
    ~Acceptor();
    void acceptConnection();
    // 实现函数回调，当有新连接时，调用newConnectionCallback
    std::function<void(Socket *)> newConnectionCallback;
    void setNewConnectionCallback(std::function<void(Socket *)>);
};