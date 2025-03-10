#pragma once

#include <map>
class EventLoop;
class Socket;
class Acceptor;
class Connection;
class Server
{
private:
    // main-reactor
    EventLoop *loop;
    // 对accept操作的抽象
    Acceptor *acceptor;
    std::map<int, Connection *> connections;

public:
    Server(EventLoop *);
    ~Server();

    void handleReadEvent(int);
    void newConnection(Socket *sock);
    void deleteConnection(Socket *sock);
};