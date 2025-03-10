# FastCppWebServer

## Introduction

FastCppWebServer is a high-performance web server based on C++ that supports the HTTP protocol. It implements basic HTTP request handling, file upload and download, logging, and other functions. The project structure includes modules such as an HTTP server, TCP server, event loop, logging system, and timer.

## Features

- Handle HTTP GET and POST requests
- Support file upload and download
- Log information
- Support multithreading, handle concurrent requests through a thread pool
- Timer function for handling timed tasks

## Installation

1. Clone the project to your local machine:
    ```bash
    git clone https://github.com/5yh/FastCppWebServer.git
    cd FastCppWebServer
    ```

2. Build the project:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

## Usage

1. Copy the [LogFiles](http://_vscodecontentref_/0) folder, [files](http://_vscodecontentref_/1) folder, and [static](http://_vscodecontentref_/2) folder from the parent directory to the current `build` directory:

2. Run the HTTP server:
    ```bash
    ./bin/http_server
    ```

3. After the server starts, you can send HTTP requests for testing through a browser or tools like curl:
    ```bash
    curl http://localhost:1234
    ```

## Project Structure

- [http](http://_vscodecontentref_/3): HTTP server related code
  - `HttpServer.h`: HTTP server header file
  - `HttpServer.cpp`: HTTP server implementation file
  - `HttpRequest.h`: HTTP request header file
  - `HttpRequest.cpp`: HTTP request implementation file
  - `HttpResponse.h`: HTTP response header file
  - `HttpResponse.cpp`: HTTP response implementation file
  - `HttpContext.h`: HTTP context header file
  - `HttpContext.cpp`: HTTP context implementation file
- [tcp](http://_vscodecontentref_/4): TCP server related code
  - `TcpServer.h`: TCP server header file
  - `TcpServer.cpp`: TCP server implementation file
  - `TcpConnection.h`: TCP connection header file
  - `TcpConnection.cpp`: TCP connection implementation file
  - `Acceptor.h`: Acceptor header file
  - `Acceptor.cpp`: Acceptor implementation file
  - `EventLoop.h`: Event loop header file
  - `EventLoop.cpp`: Event loop implementation file
  - `EventLoopThread.h`: Event loop thread header file
  - `EventLoopThread.cpp`: Event loop thread implementation file
  - `EventLoopThreadPool.h`: Event loop thread pool header file
  - `EventLoopThreadPool.cpp`: Event loop thread pool implementation file
  - `Channel.h`: Channel header file
  - `Channel.cpp`: Channel implementation file
  - `Epoller.h`: Epoll wrapper header file
  - `Epoller.cpp`: Epoll wrapper implementation file
  - `Buffer.h`: Buffer header file
  - `Buffer.cpp`: Buffer implementation file
- [log](http://_vscodecontentref_/5): Logging system related code
  - `Logging.h`: Logging system header file
  - `Logging.cpp`: Logging system implementation file
  - `LogStream.h`: Log stream header file
  - `LogStream.cpp`: Log stream implementation file
  - `AsyncLogging.h`: Asynchronous logging header file
  - `AsyncLogging.cpp`: Asynchronous logging implementation file
  - `LogFile.h`: Log file header file
  - `LogFile.cpp`: Log file implementation file
- [timer](http://_vscodecontentref_/6): Timer related code
  - `Timer.h`: Timer header file
  - `Timer.cpp`: Timer implementation file
  - `TimerQueue.h`: Timer queue header file
  - `TimerQueue.cpp`: Timer queue implementation file
  - `TimeStamp.h`: Timestamp header file
  - `TimeStamp.cpp`: Timestamp implementation file
- [base](http://_vscodecontentref_/7): Infrastructure code
  - `common.h`: Common macro definitions
  - `CurrentThread.h`: Current thread utility header file
  - `CurrentThread.cpp`: Current thread utility implementation file
  - `Latch.h`: Synchronization utility header file
- [static](http://_vscodecontentref_/8): Static files directory
  - `index.html`: Homepage HTML file
  - `mhw.html`: Example HTML file
  - `fileserver.html`: File server HTML file
- [test](http://_vscodecontentref_/9): Test code directory
  - `http_server.cpp`: HTTP server test file
  - `echo_server.cpp`: Echo server test file
  - `test_logstream.cpp`: Log stream test file
  - `test_httpcontext.cpp`: HTTP context test file
- [files](http://_vscodecontentref_/10): File upload directory
  - `a.txt`: Example file
  - `b.txt`: Example file
  - `c.txt`: Example file
- [CMakeLists.txt](http://_vscodecontentref_/11): CMake build script
- [README.md](http://_vscodecontentref_/12): Project description file

## Network Library Features

- **Efficient Event Loop**: Uses epoll or other I/O multiplexing mechanisms for efficient event handling.
- **Multithreading Support**: Handles concurrent requests through a thread pool, improving the server's concurrency handling capability.
- **Timer Management**: Manages timeout events, such as connection timeout, request timeout, etc.
- **TCP Connection Management**: Manages underlying TCP connections, handling connection establishment and closure.
- **HTTP Protocol Handling**: Parses HTTP requests, generates HTTP responses, and supports GET and POST requests.

## Contribution

Contributions are welcome! Please submit a Pull Request or report issues.

## License

This project is licensed under the MIT License. For details, please refer to the LICENSE file.

For the Chinese version of the README, please refer to READMECN.md.