aux_source_directory(. greendot_src)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(greendot STATIC ${greendot_src})

#opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(greendot ${OpenCV_LIBS})