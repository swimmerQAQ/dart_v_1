
aux_source_directory(. serialPort_src)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(serialPort STATIC ${serialPort_src})
#opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(serialPort ${OpenCV_LIBS})