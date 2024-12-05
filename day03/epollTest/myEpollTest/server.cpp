#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#define IPADDRESS "127.0.0.1"
#define PORT 8787
#define MAXSIZE 1024
#define LISTENQ 5 // listen能排队的队列个数
#define FDSIZE 1000
#define EPOLLEVENTS 100
static int socket_bind(const char *ip, int port);

static void do_epoll(int listenfd);
static void add_event(int epollfd, int fd, int state);
static void handle_accept(int epollfd, int listenfd);
static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf);
static void do_read(int epollfd, int fd, char *buf);
static void do_write(int epollfd, int fd, char *buf);
static void delete_event(int epollfd, int fd, int state);
static void modify_event(int epollfd, int fd, int state);
int main()
{
    int listenfd;
    listenfd = socket_bind(IPADDRESS, PORT);
    // 开始听，排队LISTENQ个，成功返回0，失败-1
    listen(listenfd, LISTENQ);
    do_epoll(listenfd);
    return 0;
}

static int socket_bind(const char *ip, int port)
{
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        perror("socket error:");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    // 或者用以下方法设置ip
    // inet_pton(AF_INET,ip,&servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    if (bind(listenfd, (sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind error: ");
        exit(1);
    }
    return listenfd;
}

static void do_epoll(int listenfd)
{
    int epollfd;
    // 创建一个epoll_events数组用于记录事件
    struct epoll_event events[EPOLLEVENTS];
    int ret;
    char buf[MAXSIZE];
    memset(buf, 0, MAXSIZE);
    // 指定最大文件描述符数量
    epollfd = epoll_create(FDSIZE);
    add_event(epollfd, listenfd, EPOLLIN);
    for (;;)
    {
        // 返回缓冲区中返回的触发事件数
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        handle_events(epollfd, events, ret, listenfd, buf);
    }
    // 这里好像有点问题，跑不到
    close(epollfd);
}

static void add_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void handle_accept(int epollfd, int listenfd)
{
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen = sizeof(cliaddr);
    clifd = accept(listenfd, (sockaddr *)&cliaddr, &cliaddrlen);
    if (clifd == -1)
    {
        perror("accept error:");
    }
    else
    {
        printf("accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        add_event(epollfd, clifd, EPOLLIN);
    }
}

static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf)
{
    int fd;
    for (int i = 0; i < num; i++)
    {
        fd = events[i].data.fd;
        if ((fd == listenfd) && (events[i].events & EPOLLIN))
        {
            handle_accept(epollfd, listenfd);
        }
        else if (events[i].events & EPOLLIN)
        {
            // doread
            do_read(epollfd, fd, buf);
            ;
        }
        else if (events[i].events & EPOLLOUT)
        {
            // dowrite
            do_write(epollfd, fd, buf);
            ;
        }
    }
}

static void do_read(int epollfd, int fd, char *buf)
{
    int nread;
    nread = read(fd, buf, MAXSIZE);
    if (nread == -1)
    {
        perror("read error:");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    else if (nread == 0)
    {
        fprintf(stderr, "client close.\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    else
    {
        printf("from fd: %d, read message is : %s", fd, buf);
        modify_event(epollfd, fd, EPOLLOUT);
    }
}

static void delete_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = state;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static void do_write(int epollfd, int fd, char *buf)
{
    int nwrite;
    nwrite = write(fd, buf, sizeof(buf));
    if (nwrite == -1)
    {
        perror("write error:");
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    }
    else
        modify_event(epollfd, fd, EPOLLIN);
    memset(buf, 0, MAXSIZE);
}