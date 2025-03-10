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
    std::function<void(Socket *)> deleteConnectionCallback;
    std::string *inBuffer;
    Buffer *readBuffer;

public:
    Connection(EventLoop *_loop, Socket *_sock);
    ~Connection();
    void echo(int sockfd);
    void setDeleteConnectionCallback(std::function<void(Socket *)>);
};