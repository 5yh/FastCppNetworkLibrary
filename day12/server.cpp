#include "src/EventLoop.h"
#include "src/Server.h"

int main()
{
    // 启动监听事件
    EventLoop *loop = new EventLoop();
    Server *server = new Server(loop);
    // 开始循环提取epoll中的事件
    loop->loop();
    // delete server;
    // delete loop;
    return 0;
}