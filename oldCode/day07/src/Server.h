#pragma once

class EventLoop; // main reactor
class Socket;
class Acceptor; // 用于新建连接的类
// 但新建连接的逻辑仍在Server类中实现，Server类中的newConnection函数会调用Acceptor类中的newConnectionCallback函数，这样就实现了Acceptor类中的回调函数功能。
class Server
{
private:
    EventLoop *loop;    // main reactor
    Acceptor *acceptor; // 用于新建连接的类
public:
    Server(EventLoop *);
    ~Server();

    void handleReadEvent(int);             // 传fd
    void newConnection(Socket *serv_sock); // serv_sock记录了server的socket信息，包了套接字
};