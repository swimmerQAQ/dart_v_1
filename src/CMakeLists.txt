#设定可执行的二进制文件和工程建立的目录build
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#可执行文件
add_executable(raspberry2 main.cpp)
#链接库
target_link_libraries(raspberry2 detect)
