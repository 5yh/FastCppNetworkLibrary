#pragma once

#include <functional>
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
    EventLoop *main_reactor_;
    Acceptor *acceptor_;
    std::map<int, Connection *> connections_;
    std::vector<EventLoop *> sub_reactors_;
    ThreadPool *thread_pool_;
    std::function<void(Connection *)> on_connect_callback_;

public:
    // 只有一个参数的构造函数禁止参数的隐式类型转换
    explicit Server(EventLoop *loop);
    ~Server();
    void NewConnection(Socket *sock);
    // 现在又改回Socket对象删除了
    void DeleteConnection(Socket *sock);
    // 作用？
    void OnConnect(std::function<void(Connection *)> fn);
};