#pragma once
#include <functional>
#include <string>
class EventLoop;
class Socket;
class Channel;
class Buffer;

class Connection // tcp连接抽象出的类
{
private:
    EventLoop *loop; // 事件循环抽象出的类
    Socket *sock;
    Channel *channel;
    // 返回值改为了int？
    std::function<void(int)> deleteConnectionCallback;
    Buffer *readBuffer;

public:
    Connection(EventLoop *_loop, Socket *_sock);
    ~Connection();
    void echo(int sockfd);
    void setDeleteConnectionCallback(std::function<void(int)>);
    // 什么作用？
    void send(int sockfd);
};