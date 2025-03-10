// 简单处理的非阻塞式和阻塞式
// client和server放在一起
#include "Socket.h"
#include "util.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

Socket::Socket() : fd(-1)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(fd == -1, "socket create error");
}
Socket::Socket(int _fd) : fd(_fd)
{
    errif(fd == -1, "socket create error");
}

Socket::~Socket()
{
    if (fd != -1)
    {
        close(fd);
        fd = -1;
    }
}

void Socket::bind(InetAddress *_addr)
{
    struct sockaddr_in addr = _addr->getAddr();
    errif(::bind(fd, (sockaddr *)&addr, sizeof(addr)) == -1, "socket bind error");
}

void Socket::listen()
{
    errif(::listen(fd, SOMAXCONN) == -1, "socket listen error");
}
void Socket::setnonblocking()
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress *_addr)
{
    // server
    int clnt_sockfd = -1;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    socklen_t addr_len = sizeof(addr);
    if (fcntl(fd, F_GETFL) & O_NONBLOCK) //  非阻塞模式
    {
        while (true)
        {
            clnt_sockfd = ::accept(fd, (sockaddr *)&addr, &addr_len);
            if (clnt_sockfd == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
            { // currently no connection
                continue;
            }
            else if (clnt_sockfd == -1)
            {
                errif(true, "socket accept error");
            }
            else // accept成功
            {
                break;
            }
        }
    }
    else // 阻塞模式
    {
        clnt_sockfd = ::accept(fd, (sockaddr *)&addr, &addr_len);
        errif(clnt_sockfd == -1, "socket accept error");
    }

    _addr->setInetAddr(addr);
    return clnt_sockfd;
}
void Socket::connect(InetAddress *_addr)
{
    // for client socket
    struct sockaddr_in addr = _addr->getAddr();
    if (fcntl(fd, F_GETFL) & O_NONBLOCK)
    {
        while (true)
        {
            int ret = ::connect(fd, (sockaddr *)&addr, sizeof(addr));
            if (ret == 0) // 连接成功
            {
                break;
            }
            else if (ret == -1 && (errno == EINPROGRESS))
            {
                // 当一个非阻塞操作已经启动但尚未完成时
                // 当试图在一个非阻塞socket上建立连接时，连接尚未建立完成
                continue;
            }
            else if (ret == -1)
            {
                errif(true, "socket connect error");
            }
        }
    }
    else
    {
        errif(::connect(fd, (sockaddr *)&addr, sizeof(addr)) == -1, "socket connect error");
    }
}
int Socket::getFd()
{
    return fd;
}

InetAddress::InetAddress()
{
    bzero(&addr, sizeof(addr));
}
InetAddress::InetAddress(const char *_ip, uint16_t _port)
{
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(_ip);
    addr.sin_port = htons(_port);
}

InetAddress::~InetAddress()
{
}

void InetAddress::setInetAddr(sockaddr_in _addr)
{
    addr = _addr;
}

sockaddr_in InetAddress::getAddr()
{
    return addr;
}

char *InetAddress::getIp()
{
    return inet_ntoa(addr.sin_addr);
}

uint16_t InetAddress::getPort()
{
    return ntohs(addr.sin_port);
}