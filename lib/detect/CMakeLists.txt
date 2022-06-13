
aux_source_directory(. detect_src)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(detect STATIC ${detect_src})

target_link_libraries(detect ${OpenCV_LIBS} invertimg lightbar greendot triangle log predict)