#pragma once

#include <map>
#include <vector>
class EventLoop;
class Socket;
class Acceptor;
class Connection;
class ThreadPool;
class Server
{
private:
    EventLoop *mainReactor;
    Acceptor *acceptor;
    std::map<int, Connection *> connections;
    std::vector<EventLoop *> subReactors;
    ThreadPool *thpool;

public:
    Server(EventLoop *);
    ~Server();

    void handleReadEvent(int);
    void newConnection(Socket *sock);
    // 现在又改回使用sockfd删除了，不传socket对象
    void deleteConnection(int sockfd);
};
