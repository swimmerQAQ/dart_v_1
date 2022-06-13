aux_source_directory(. lightbar_src)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(lightbar STATIC ${lightbar_src})

#opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(lightbar ${OpenCV_LIBS})