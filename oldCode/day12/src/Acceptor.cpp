#include "Acceptor.h"
#include "Socket.h"
#include "Channel.h"

Acceptor::Acceptor(EventLoop *_loop) : loop(_loop), sock(nullptr), acceptChannel(nullptr)
{
    sock = new Socket();
    InetAddress *addr = new InetAddress("127.0.0.1", 1234);
    sock->bind(addr);
    sock->listen();
    // sock->setnonblocking();
    acceptChannel = new Channel(loop, sock->getFd());
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
    // 感觉实际上应该叫做acceptCallback?
    acceptChannel->setReadCallback(cb);
    acceptChannel->enableRead();
    // main reactor的channel不需要线程池，一个线程就够了
    // acceptChannel->setUseThreadPool(false);
    delete addr;
}

Acceptor::~Acceptor()
{
    delete sock;
    delete acceptChannel;
}

void Acceptor::acceptConnection()
{
    InetAddress *clnt_addr = new InetAddress();
    Socket *clnt_sock = new Socket(sock->accept(clnt_addr));
    printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->getAddr().sin_addr), ntohs(clnt_addr->getAddr().sin_port));
    clnt_sock->setnonblocking();
    newConnectionCallback(clnt_sock);
    delete clnt_addr;
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket *)> _cb)
{
    newConnectionCallback = _cb;
}