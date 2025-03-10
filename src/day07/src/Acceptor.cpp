#include "Acceptor.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Server.h"

Acceptor::Acceptor(EventLoop *_loop) : loop(_loop)
{

    sock = new Socket();
    addr = new InetAddress("127.0.0.1", 8888);
    sock->bind(addr);
    sock->listen();
    sock->setnonblocking();
    // Channel类处理描述符和与其相关的处理函数
    acceptChannel = new Channel(loop, sock->getFd());
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
    // 绑定了一个回调函数
    acceptChannel->setCallback(cb);
    acceptChannel->enableReading();
}

Acceptor::~Acceptor()
{
    delete sock;
    delete addr;
    delete acceptChannel;
}

void Acceptor::acceptConnection()
{
    // 这里实际上就是调用回调函数了，传了一个参数，之前已经绑定过了
    newConnectionCallback(sock);
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket *)> _cb)
{
    newConnectionCallback = _cb;
}