cmake_minimum_required(VERSION 3.10)
project(Console2048)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 告诉 CMake 头文件在哪
include_directories(include)

# 找到所有的源文件
file(GLOB SOURCES "src/*.cpp")

# 生成可执行文件
add_executable(2048 ${SOURCES})
