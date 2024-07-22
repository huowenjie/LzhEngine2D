cmake_minimum_required(VERSION 3.22.1)

project(LzhEngine2D LANGUAGES C CXX)

# 指定静态库目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定动态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定可执行文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 添加调试选项
add_definitions("-Wall -g -O0")

# 指定编码
add_compile_options(-finput-charset=gb18030)
add_compile_options(-fexec-charset=utf-8)

# 指定子项目
add_subdirectory(lzhcore)
add_subdirectory(lzhtank)
