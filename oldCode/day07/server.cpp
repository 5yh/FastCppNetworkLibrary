#include "src/EventLoop.h"
#include "src/Server.h"

int main()
{
    EventLoop *loop = new EventLoop(); // main reactor
    Server *server = new Server(loop);
    loop->loop();
    return 0;
}