#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET ipv4
    // SOCK_STREAM 数据流格式，面向连接 用于tcp
    // 0 自动推导为tcp
    // 设置为IPPROTO_TCP和IPPTOTO_UDP，分别表示TCP和UDP
}