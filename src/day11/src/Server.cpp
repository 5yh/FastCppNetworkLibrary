#include "Server.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"
#include <unistd.h>
#include <functional>

Server::Server(EventLoop *_loop) : loop(_loop), acceptor(nullptr)
{
    acceptor = new Acceptor(loop);
    std::function<void(Socket *)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);
}

Server::~Server()
{
    delete acceptor;
}

void Server::newConnection(Socket *sock)
{
    Connection *conn = new Connection(loop, sock);
    // 因为从传Socket对象删改为了传sockfd删。所以函数绑定的返回值也改了
    std::function<void(int)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    conn->setDeleteConnectionCallback(cb);
    connections[sock->getFd()] = conn;
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