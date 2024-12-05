#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include "util.h"

#define MAX_EVENTS 1024
#define READ_BUFFER 1024

void settnonblocking(int fd)
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}
// https://chatgpt.com/c/6751833f-6088-800f-8ff2-67a7c0d9b846
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sockfd == -1, "socket create error");

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    errif(bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error");

    errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error");

    int epfd = epoll_create1(0);
    errif(epfd == -1, "epoll create error");

    struct epoll_event events[MAX_EVENTS], ev;
    bzero(&events, sizeof(events));
    bzero(&ev, sizeof(ev));

    ev.data.fd = sockfd;
    ev.events = EPOLLIN | EPOLLET;
    // 设置成非阻塞套接字
    settnonblocking(sockfd);
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

    while (true)
    {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        errif(nfds == -1, "epoll wait error");
        for (int i = 0; i < nfds; i++)
        {
            // 请求连接的套接字
            if (events[i].data.fd == sockfd)
            {
                struct sockaddr_in clnt_addr;
                bzero(&clnt_addr, sizeof(clnt_addr));
                socklen_t clnt_addr_len = sizeof(clnt_addr);

                int clnt_sockfd = accept(sockfd, (sockaddr *)&clnt_addr, &clnt_addr_len);
                errif(clnt_sockfd == -1, "socket accept error");
                printf("new client fd %d! IP: %s Port: %d\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

                bzero(&ev, sizeof(ev));
                ev.data.fd = clnt_sockfd;
                ev.events = EPOLLIN | EPOLLET;
                settnonblocking(clnt_sockfd);
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sockfd, &ev);
            }
            // 读事件
            else if (events[i].events & EPOLLIN)
            {
                char buf[READ_BUFFER];
                while (true)
                {
                    // 非阻塞的读法不同，这里要注意
                    bzero(&buf, sizeof(buf));
                    ssize_t bytes_read = read(events->data.fd, buf, sizeof(buf));
                    if (bytes_read > 0)
                    {
                        printf("message from client fd %d: %s\n", events[i].data.fd, buf);
                        // 这里和前一个人改成epollout不一样，这里直接写回了
                        write(events[i].data.fd, buf, sizeof(buf));
                    }
                    // 当阻塞于某个慢系统调用的一个进程捕获某个信号且相应信号处理函数返回时，该系统调用可能返回一个EINTR错误
                    // 当一个线程正在执行阻塞的系统调用
                    // （如 read、write、accept、recv、send、poll、epoll_wait 等）时，
                    // 如果进程捕获了一个信号并进入了信号处理程序，
                    // 系统调用会被中断并返回 -1，同时设置 errno 为 EINTR。
                    else if (bytes_read == -1 && errno == EINTR)
                    {
                        printf("continue reading");
                        continue;
                    }
                    // 非阻塞IO，这个条件表示数据全部读取完毕
                    else if (bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
                    {
                        printf("finish reading once, errno: %d\n", errno);
                        break;
                    }
                    else if (bytes_read == 0)
                    {
                        // 客户端断开
                        printf("EOF, client fd %d disconnected\n", events[i].data.fd);
                        close(events[i].data.fd);
                        break;
                    }
                }
            }
            else
            { // 其他事件，以后再来探索吧
                printf("sth else happened\n");
            }
        }
    }
    close(sockfd);
    return 0;
}