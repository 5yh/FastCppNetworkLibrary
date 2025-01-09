#pragma once
#include <arpa/inet.h>

class InetAddress
{
private:
    struct sockaddr_in addr;
    // 用不上了，长度信息
    // socklen_t addr_len;
public:
    InetAddress();
    InetAddress(const char *_ip, uint16_t _port);
    ~InetAddress();
    void setInetAddr(sockaddr_in _addr);
    sockaddr_in getAddr();
    // socklen_t getAddr_len();
};
