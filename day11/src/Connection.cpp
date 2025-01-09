#include "Connection.h"
#include "Socket.h"
#include "Channel.h"
#include "util.h"
#include "Buffer.h"
#include <unistd.h>
#include <string.h>
#include <iostream>

Connection::Connection(EventLoop *_loop, Socket *_sock) : loop(_loop), sock(_sock), channel(nullptr), inBuffer(new std::string()), readBuffer(nullptr)
{
    channel = new Channel(loop, sock->getFd());
    channel->enableRead();
    channel->useET();
    std::function<void()> cb = std::bind(&Connection::echo, this, sock->getFd());
    channel->setReadCallback(cb);
    channel->setUseThreadPool(true);
    // 原来在这里设置读和et，改到上面了
    // channel->enableReading();
    // 新增
    readBuffer = new Buffer();
}

Connection::~Connection()
{
    delete channel;
    delete sock;
    delete readBuffer;
}

void Connection::setDeleteConnectionCallback(std::function<void(int)> _cb)
{
    deleteConnectionCallback = _cb;
}
void Connection::echo(int sockfd)
{
    char buf[1024]; // 这个buf无所谓，和设备tcp缓冲区的大小有关
    while (true)
    {
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if (bytes_read > 0)
        {
            readBuffer->append(buf, bytes_read);
        }
        else if (bytes_read == -1 && errno == EINTR) // 客户端正常中断，继续读取
        {
            printf("continue reading");
            continue;
        }
        else if (bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) // 数据全部读取完毕
        {
            printf("finish reading once\n");
            printf("message from client fd %d: %s\n", sockfd, readBuffer->c_str());
            // 什么意思，不echo了吗？
            // errif(write(sockfd, readBuffer->c_str(), readBuffer->size()) == -1, "socket write error");
            send(sockfd);
            readBuffer->clear();
            break;
        }
        else if (bytes_read == 0)
        {
            printf("EOF, client fd %d disconnected\n", sockfd);
            // 调用的删除连接函数在Server中实现
            deleteConnectionCallback(sockfd);
            break;
        }
        else
        {
            printf("Connection reset by peer\n");
            deleteConnectionCallback(sockfd);
            break;
        }
    }
}

void Connection::send(int sockfd)
{
    char buf[readBuffer->size()];
    strcpy(buf, readBuffer->c_str());
    int data_size = readBuffer->size();
    int data_left = data_size;
    while (data_left > 0)
    {
        // 每次写的字节大小不知道，写完才知道
        // 写完减掉这些，再写上一轮没写掉的
        ssize_t bytes_write = write(sockfd, buf + data_size - data_left, data_left);
        if (bytes_write == -1 && errno == EAGAIN)
        {
            break;
        }
        data_left -= bytes_write;
    }
}