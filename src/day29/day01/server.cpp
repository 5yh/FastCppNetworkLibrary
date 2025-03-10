#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    // 这是套接字，是文件描述符
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET ipv4
    // SOCK_STREAM 数据流格式，面向连接 用于tcp
    // 0 自动推导为tcp
    // 设置为IPPROTO_TCP和IPPTOTO_UDP，分别表示TCP和UDP
    // 这是服务器端地址
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);
    // 绑定套接字和地址
    bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr));
    // 监听socket，监听队列长度为128
    listen(sockfd, SOMAXCONN);
    // 这是client的地址
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_len = sizeof(clnt_addr);
    bzero(&clnt_addr, sizeof(clnt_addr));
    // 这里会阻塞
    int clnt_sockfd = accept(sockfd, (sockaddr *)&clnt_addr, &clnt_addr_len);
    printf("new client fd %d! IP:%s Port: %d\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
    return 0;
}