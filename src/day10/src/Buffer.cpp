#include "Buffer.h"
#include <string.h>
#include <iostream>

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

// 一个个字节往里放
void Buffer::append(const char *_str, int _size)
{
    for (int i = 0; i < _size; i++)
    {
        if (_str[i] == '\0')
            break;
        buf.push_back(_str[i]);
    }
}

ssize_t Buffer::size()
{
    return buf.size();
}

const char *Buffer::c_str()
{
    return buf.c_str();
}

void Buffer::clear()
{
    buf.clear();
}
// 输入的函数
void Buffer::getline()
{
    buf.clear();
    std::getline(std::cin, buf);
}