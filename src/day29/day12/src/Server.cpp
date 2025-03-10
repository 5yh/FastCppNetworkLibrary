#include "Server.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"
#include "ThreadPool.h"
#include "EventLoop.h"
#include <unistd.h>
#include <functional>

Server::Server(EventLoop *_loop) : mainReactor(_loop), acceptor(nullptr)
{
    acceptor = new Acceptor(mainReactor);
    std::function<void(Socket *)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);

    int size = std::thread::hardware_concurrency();
    thpool = new ThreadPool(size);
    for (int i = 0; i < size; i++)
    {
        subReactors.emplace_back(new EventLoop());
    }
    for (int i = 0; i < size; i++)
    {
        std::function<void()> sub_loop = std::bind(&EventLoop::loop, subReactors[i]);
        thpool->add(sub_loop); // 开启所有线程的事件循环
    }
}

Server::~Server()
{
    delete acceptor;
    delete thpool;
}

void Server::newConnection(Socket *sock)
{
    if (sock->getFd() != -1)
    {
        int random = sock->getFd() % subReactors.size();
        Connection *conn = new Connection(subReactors[random], sock); // 传eventloop和socket,绑定这两个，抽象出的连接类
        std::function<void(int)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
        conn->setDeleteConnectionCallback(cb);
        connections[sock->getFd()] = conn;
    }
}

void Server::deleteConnection(int sockfd)
{
    if (sockfd != -1)
    {
        auto it = connections.find(sockfd);
        if (it != connections.end())
        {
            Connection *conn = connections[sockfd];
            connections.erase(sockfd);
            // 据说这样会段错误？要
            delete conn;
            conn = nullptr;
            // 这个delete已经调用了close sockfd
            // close(sockfd);
        }
    }
}