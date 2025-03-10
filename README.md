[中文README](./READMECN.md)

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

1. Copy the `LogFiles` folder, `files` folder, and `static` folder from the parent directory to the current `build` directory:
    ```bash
    cp -r LogFiles build/
    cp -r files build/
    cp -r static build/
    ```

2. Run the HTTP server:
    ```bash
    ./bin/http_server
    ```

3. After the server starts, you can send HTTP requests for testing through a browser or tools like curl:
    ```bash
    curl http://localhost:1234
    ```

## Project Structure

- `http/`: HTTP server related code
  - `HttpServer.h`: HTTP server header file
  - `HttpServer.cpp`: HTTP server implementation file
  - `HttpRequest.h`: HTTP request header file
  - `HttpRequest.cpp`: HTTP request implementation file
  - `HttpResponse.h`: HTTP response header file
  - `HttpResponse.cpp`: HTTP response implementation file
  - `HttpContext.h`: HTTP context header file
  - `HttpContext.cpp`: HTTP context implementation file
- `tcp/`: TCP server related code
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
- `log/`: Logging system related code
  - `Logging.h`: Logging system header file
  - `Logging.cpp`: Logging system implementation file
  - `LogStream.h`: Log stream header file
  - `LogStream.cpp`: Log stream implementation file
  - `AsyncLogging.h`: Asynchronous logging header file
  - `AsyncLogging.cpp`: Asynchronous logging implementation file
  - `LogFile.h`: Log file header file
  - `LogFile.cpp`: Log file implementation file
- `timer/`: Timer related code
  - `Timer.h`: Timer header file
  - `Timer.cpp`: Timer implementation file
  - `TimerQueue.h`: Timer queue header file
  - `TimerQueue.cpp`: Timer queue implementation file
  - `TimeStamp.h`: Timestamp header file
  - `TimeStamp.cpp`: Timestamp implementation file
- `base/`: Infrastructure code
  - `common.h`: Common macro definitions
  - `CurrentThread.h`: Current thread utility header file
  - `CurrentThread.cpp`: Current thread utility implementation file
  - `Latch.h`: Synchronization utility header file
- `static/`: Static files directory
  - `index.html`: Homepage HTML file
  - `fileserver.html`: File server HTML file
- `test/`: Test code directory
  - `http_server.cpp`: HTTP server test file
  - `echo_server.cpp`: Echo server test file
  - `test_logstream.cpp`: Log stream test file
  - `test_httpcontext.cpp`: HTTP context test file
- `files/`: File upload directory
  - `a.txt`: Example file
  - `b.txt`: Example file
  - `c.txt`: Example file
- `CMakeLists.txt`: CMake build script
- `README.md`: Project description file