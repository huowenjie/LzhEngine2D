cmake_minimum_required(VERSION 3.22.1)

project(LzhEngine2D LANGUAGES C CXX)

# 指定静态库目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定动态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定可执行文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定根目录
set(CMAKE_PROJECT_ROOT ${PROJECT_SOURCE_DIR}/)

# 指定版本号
set(LZH_ENGINE_VERSION_MAJOR 1)
set(LZH_ENGINE_VERSION_MINOR 1.0)

# 添加调试选项
add_definitions("-Wall -g -O0")

# 添加编译宏
add_compile_definitions(LZH_MEMORY_DEBUG)
add_compile_definitions(LZH_ENABLE_TRACE)

# windows 平台宏定义
if(CMAKE_HOST_WIN32)
add_compile_definitions(_WINDOWS)
endif()

# 指定编码
add_compile_options(-finput-charset=gb18030)
add_compile_options(-fexec-charset=utf-8)

# 指定子项目
add_subdirectory(lzhcore)
add_subdirectory(lzhphysics)
