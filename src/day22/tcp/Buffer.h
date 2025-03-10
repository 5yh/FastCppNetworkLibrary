#pragma once

#include <memory.h>
#include <string>
#include "common.h"

class Buffer
{
public:
    DISALLOW_COPY_AND_MOVE(Buffer);
    Buffer() = default;
    ~Buffer() = default;

    // 后面的const表示不能修改所属对象的状态
    // 不能调用类的成员变量或调用其他非const成员函数
    // 前面的const表示返回的时常量引用或指针
    const std::string &buf() const;
    const char *c_str() const;

    void set_buf(const char *buf);

    size_t Size() const;
    void Append(const char *_str, int _size);
    void Clear();

private:
    std::string buf_;
};