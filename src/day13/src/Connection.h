#pragma once
#include <functional>
#include <string>
class EventLoop;
class Socket;
class Channel;
class Buffer;

class Connection // tcp连接抽象出的类
{
public:
    enum State
    {
        Invalid = 1,
        Handshaking,
        Connected,
        Closed,
        Failed,
    };
    Connection(EventLoop *loop, Socket *sock);
    ~Connection();

    void Read();
    void Write();

    void SetDeleteConnectionCallback(std::function<void(Socket *)> const &callback);
    void SetOnConnectCallback(std::function<void(Connection *)> const &callback);
    State GetState();
    void Close();
    void SetSendBuffer(const char *str);
    // 没用到
    Buffer *GetReadBuffer();
    // 没用到
    const char *ReadBuffer();
    // 没用到
    Buffer *GetSendBuffer();
    // 没用到
    const char *SendBuffer();
    // 没用到
    void GetlineSendBuffer();
    Socket *GetSocket();

    void OnConnect(std::function<void()> fn);

private:
    EventLoop *loop_;
    Socket *sock_;
    Channel *channel_{nullptr};
    State state_{State::Invalid};
    Buffer *read_buffer_{nullptr};
    Buffer *send_buffer_{nullptr};
    // 这里要改
    std::function<void(Socket *)> delete_connection_callback_;

    std::function<void(Connection *)> on_connect_callback_;

    void ReadNonBlocking();
    void WriteNonBlocking();
    // 没实现
    void ReadBlocking();
    void WriteBlocking();
};