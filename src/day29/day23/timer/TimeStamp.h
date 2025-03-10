#pragma once
#include <stdio.h>
#include <sys/time.h>

#include <string>
// 微秒到秒
const int kMicrosecond2Second = 1000 * 1000;

class TimeStamp
{
public:
    TimeStamp() : micro_seconds_(0) {};
    explicit TimeStamp(int64_t micro_sceond) : micro_seconds_(micro_sceond) {};
    int64_t microseconds() const { return micro_seconds_; };
    bool operator<(const TimeStamp &rhs) const
    {
        return micro_seconds_ < rhs.microseconds();
    }
    bool operator==(const TimeStamp &rhs) const
    {
        return micro_seconds_ == rhs.microseconds();
    }
    std::string ToFormattedString() const
    {
        char buf[64] = {0};
        // 类型转换运算符，显式转换更安全
        // int64_t time_t`
        time_t seconds = static_cast<time_t>(micro_seconds_ / kMicrosecond2Second);

        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&seconds));
        return std::string(buf);
    }
    static TimeStamp Now();
    static TimeStamp AddTime(TimeStamp timestamp, double add_seconds);

private:
    int64_t micro_seconds_;
};
inline TimeStamp TimeStamp::Now()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return TimeStamp(time.tv_sec * kMicrosecond2Second + time.tv_usec);
};

inline TimeStamp TimeStamp::AddTime(TimeStamp timestamp, double add_seconds)
{
    int64_t add_microseconds = static_cast<int64_t>(add_seconds) * kMicrosecond2Second;
    return TimeStamp(timestamp.microseconds() + add_microseconds);
};