#顶层目录设定cmake版本
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "-fsanitize=address -g")
#设定工程名字
project(raspberry2)
#索引工程子目录
add_subdirectory(src)
add_subdirectory(lib)