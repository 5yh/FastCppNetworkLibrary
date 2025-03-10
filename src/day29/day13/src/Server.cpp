#include "Server.h"

#include <unistd.h>
#include <assert.h>
#include <functional>

#include "Acceptor.h"
#include "Connection.h"
#include "EventLoop.h"
#include "Socket.h"
#include "ThreadPool.h"

Server::Server(EventLoop *loop) : main_reactor_(loop), acceptor_(nullptr), thread_pool_(nullptr)
{
    acceptor_ = new Acceptor(main_reactor_);
    std::function<void(Socket *)> cb = std::bind(&Server::NewConnection, this, std::placeholders::_1);
    acceptor_->setNewConnectionCallback(cb);

    int size = static_cast<int>(std::thread::hardware_concurrency());
    thread_pool_ = new ThreadPool(size);
    for (int i = 0; i < size; ++i)
    {
        sub_reactors_.push_back(new EventLoop());
    }

    for (int i = 0; i < size; ++i)
    {
        std::function<void()> sub_loop = std::bind(&EventLoop::loop, sub_reactors_[i]);
        thread_pool_->add(std::move(sub_loop));
    }
}

Server::~Server()
{
    delete acceptor_;
    delete thread_pool_;
}

void Server::NewConnection(Socket *sock)
{
    assert(sock->getFd() != -1);
    uint64_t random = sock->getFd() % sub_reactors_.size();
    Connection *conn = new Connection(sub_reactors_[random], sock);
    std::function<void(Socket *)> cb = std::bind(&Server::DeleteConnection, this, std::placeholders::_1);
    conn->SetDeleteConnectionCallback(cb);
    // 新增的，这个callback是server.cpp传进来的lambda函数
    // 转移到conn中的callback里
    conn->SetOnConnectCallback(on_connect_callback_);
    connections_[sock->getFd()] = conn;
}

void Server::DeleteConnection(Socket *sock)
{
    int sockfd = sock->getFd();
    auto it = connections_.find(sockfd);
    if (it != connections_.end())
    {
        Connection *conn = connections_[sockfd];
        connections_.erase(sockfd);
        delete conn;
        conn = nullptr;
    }
}
// 给server.cpp用的，传一个labmda
// 这里要const吗？
// 可能因为move了所以不行
// 将fn转换成右值引用，所有权转移
void Server::OnConnect(std::function<void(Connection *)> fn)
{
    on_connect_callback_ = std::move(fn);
}