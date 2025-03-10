cmake_minimum_required(VERSION 3.10)

# 设置项目名称和语言
project(ThreadExample CXX)

# 设置C++标准为C++11（因为使用了std::thread）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找线程库
find_package(Threads REQUIRED)

# 添加可执行文件
add_executable(thread_test testThread.cpp)

# 链接线程库
target_link_libraries(thread_test PRIVATE Threads::Threads)