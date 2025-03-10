#include <iostream>
#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "EventLoop.h"
#include "Logging.h"
#include "AsyncLogging.h"
#include <string>
#include <memory>

const std::string html = R"_HTML(<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>HTML Example</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #f4f4f4;
            padding: 20px;
        }
        .container {
            background: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            display: inline-block;
        }
        .red-text {
            color: red;
            font-size: 24px;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <p class="red-text">This is HTML!</p>
        <p>这是一个更丰富的 HTML 示例。</p>
        <button onclick="alert('按钮被111点击了！')">点击我</button>
    </div>
</body>
</html>)_HTML";

void HttpResponseCallback(const HttpRequest &request, HttpResponse *response)
{
    if (request.method() != HttpRequest::Method::kGet)
    {
        response->SetStatusCode(HttpResponse::HttpStatusCode::k400BadRequest);
        response->SetStatusMessage("Bad Request");
        response->SetCloseConnection(true);
    }

    {
        std::string url = request.url();
        if (url == "/")
        {
            response->SetStatusCode(HttpResponse::HttpStatusCode::k200K);
            response->SetBody(html);
            response->SetContentType("text/html");
        }
        else if (url == "/hello")
        {
            response->SetStatusCode(HttpResponse::HttpStatusCode::k200K);
            response->SetBody("hello world\n");
            response->SetContentType("text/plain");
        }
        else if (url == "/favicon.ico")
        {
            response->SetStatusCode(HttpResponse::HttpStatusCode::k200K);
        }
        else
        {
            response->SetStatusCode(HttpResponse::HttpStatusCode::k404NotFound);
            response->SetStatusMessage("Not Found");
            response->SetBody("Sorry Not Found\n");
            response->SetCloseConnection(true);
        }
    }
    return;
}

std::unique_ptr<AsyncLogging> asynclog;
void AsyncOutputFunc(const char *data, int len)
{
    asynclog->Append(data, len);
}

void AsyncFlushFunc()
{
    asynclog->Flush();
}

int main(int argc, char *argv[])
{
    int port;
    if (argc <= 1)
    {
        port = 1234;
    }
    else if (argc == 2)
    {
        port = atoi(argv[1]);
    }
    else
    {
        printf("error");
        exit(0);
    }

    asynclog = std::make_unique<AsyncLogging>();
    Logger::setOutput(AsyncOutputFunc);
    Logger::setFlush(AsyncFlushFunc);

    asynclog->Start();

    int size = std::thread::hardware_concurrency() - 1;
    EventLoop *loop = new EventLoop();
    HttpServer *server = new HttpServer(loop, "127.0.0.1", port, true);
    server->SetHttpCallback(HttpResponseCallback);
    server->SetThreadNums(size);
    server->start();

    // delete loop;
    // delete server;
    return 0;
}