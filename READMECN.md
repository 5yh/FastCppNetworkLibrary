# FastCppWebServer

## 简介

FastCppWebServer是一个基于C++的高性能Web服务器，支持HTTP协议。它实现了基本的HTTP请求处理、文件上传和下载、日志记录等功能。项目结构包括HTTP服务器、TCP服务器、事件循环、日志系统和定时器等模块。

## 功能

- 处理HTTP GET和POST请求
- 支持文件上传和下载
- 记录日志信息
- 支持多线程，通过线程池处理并发请求
- 定时器功能，用于定时任务的处理

## 安装

1. 克隆项目到本地：
    ```bash
    git clone https://github.com/5yh/FastCppWebServer.git
    cd FastCppWebServer
    ```

2. 编译项目：
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

## 使用

## 使用

1. 将上级目录的`LogFiles`文件夹、`files`文件夹和`static`文件夹拷贝到当前的`build`目录中：

2. 运行HTTP服务器：
    ```bash
    ./bin/http_server
    ```

3. 服务器启动后，可以通过浏览器或工具（如curl）发送HTTP请求进行测试：
    ```bash
    curl http://localhost:1234
    ```

## 项目结构

- `http/`：HTTP服务器相关代码
  - `HttpServer.h`：HTTP服务器的头文件
  - `HttpServer.cpp`：HTTP服务器的实现文件
  - `HttpRequest.h`：HTTP请求的头文件
  - `HttpRequest.cpp`：HTTP请求的实现文件
  - `HttpResponse.h`：HTTP响应的头文件
  - `HttpResponse.cpp`：HTTP响应的实现文件
  - `HttpContext.h`：HTTP上下文的头文件
  - `HttpContext.cpp`：HTTP上下文的实现文件
- `tcp/`：TCP服务器相关代码
  - `TcpServer.h`：TCP服务器的头文件
  - `TcpServer.cpp`：TCP服务器的实现文件
  - `TcpConnection.h`：TCP连接的头文件
  - `TcpConnection.cpp`：TCP连接的实现文件
  - `Acceptor.h`：连接接受器的头文件
  - `Acceptor.cpp`：连接接受器的实现文件
  - `EventLoop.h`：事件循环的头文件
  - `EventLoop.cpp`：事件循环的实现文件
  - `EventLoopThread.h`：事件循环线程的头文件
  - `EventLoopThread.cpp`：事件循环线程的实现文件
  - `EventLoopThreadPool.h`：事件循环线程池的头文件
  - `EventLoopThreadPool.cpp`：事件循环线程池的实现文件
  - `Channel.h`：通道的头文件
  - `Channel.cpp`：通道的实现文件
  - `Epoller.h`：Epoll封装的头文件
  - `Epoller.cpp`：Epoll封装的实现文件
  - `Buffer.h`：缓冲区的头文件
  - `Buffer.cpp`：缓冲区的实现文件
- `log/`：日志系统相关代码
  - `Logging.h`：日志系统的头文件
  - `Logging.cpp`：日志系统的实现文件
  - `LogStream.h`：日志流的头文件
  - `LogStream.cpp`：日志流的实现文件
  - `AsyncLogging.h`：异步日志的头文件
  - `AsyncLogging.cpp`：异步日志的实现文件
  - `LogFile.h`：日志文件的头文件
  - `LogFile.cpp`：日志文件的实现文件
- `timer/`：定时器相关代码
  - `Timer.h`：定时器的头文件
  - `Timer.cpp`：定时器的实现文件
  - `TimerQueue.h`：定时器队列的头文件
  - `TimerQueue.cpp`：定时器队列的实现文件
  - `TimeStamp.h`：时间戳的头文件
  - `TimeStamp.cpp`：时间戳的实现文件
- `base/`：基础设施代码
  - `common.h`：通用宏定义
  - `CurrentThread.h`：当前线程工具的头文件
  - `CurrentThread.cpp`：当前线程工具的实现文件
  - `Latch.h`：同步工具的头文件
- `static/`：静态文件目录
  - `index.html`：主页HTML文件
  - `mhw.html`：示例HTML文件
  - `fileserver.html`：文件服务器HTML文件
- `test/`：测试代码目录
  - `http_server.cpp`：HTTP服务器测试文件
  - `echo_server.cpp`：回显服务器测试文件
  - `test_logstream.cpp`：日志流测试文件
  - `test_httpcontext.cpp`：HTTP上下文测试文件
- `files/`：文件上传目录
  - `a.txt`：示例文件
  - `b.txt`：示例文件
  - `c.txt`：示例文件
- `CMakeLists.txt`：CMake构建脚本
- `README.md`：项目说明文件

## 网络库特色功能

- **高效的事件循环**：使用epoll或其他I/O多路复用机制，实现高效的事件处理。
- **多线程支持**：通过线程池处理并发请求，提高服务器的并发处理能力。
- **定时器管理**：用于管理超时事件，例如连接超时、请求超时等。
- **TCP连接管理**：负责底层的TCP连接管理，处理连接的建立和关闭。
- **HTTP协议处理**：解析HTTP请求，生成HTTP响应，支持GET和POST请求。

## 贡献

欢迎贡献代码！请提交Pull Request或报告问题。

## 许可证

该项目使用MIT许可证。详情请参阅LICENSE文件。