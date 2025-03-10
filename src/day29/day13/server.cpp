#include "src/Server.h"
#include <iostream>
#include "src/Buffer.h"
#include "src/Connection.h"
#include "src/EventLoop.h"
#include "src/Socket.h"
int main()
{
    // 启动监听事件
    EventLoop *loop = new EventLoop();
    Server *server = new Server(loop);
    // 这个函数最终被传到channel的readCallback中
    // server->connection->channel->readCallback在处理事件中被调用
    server->OnConnect([](Connection *conn)
                      {
                          conn->Read();
                          if (conn->GetState() == Connection::State::Closed)
                          {
                              conn->Close();
                              return;
                          }
                          std::cout << "Message from client " << conn->GetSocket()->getFd() << ": " << conn->ReadBuffer() << std::endl;
                          conn->SetSendBuffer(conn->ReadBuffer());
                          conn->Write(); });

    // 开始循环提取epoll中的事件
    loop->loop();
    delete server;
    delete loop;
    return 0;
}