#pragma once

#include <map>
class EventLoop;
class Socket;
class Acceptor;
class Connection;
class Server
{
private:
    EventLoop *loop;
    Acceptor *acceptor;
    std::map<int, Connection *> connections;

public:
    Server(EventLoop *);
    ~Server();

    void handleReadEvent(int);
    void newConnection(Socket *sock);
    // 现在又改回使用sockfd删除了，不传socket对象
    void deleteConnection(int sockfd);
};
