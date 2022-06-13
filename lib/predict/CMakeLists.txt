
aux_source_directory(. predict_src)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(predict STATIC ${predict_src})

#opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(predict ${OpenCV_LIBS} serialPort)