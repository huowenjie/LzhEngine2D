cmake_minimum_required(VERSION 3.22.1)

project(lzhtank LANGUAGES C CXX)

# 指定静态库目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定动态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定可执行文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定源文件 
aux_source_directory(. SRCFILE)

# 设置编译时的链接库目录
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# 指定生成可执行程序
add_executable(lzhtank ${SRCFILE})

# 生成位置无关代码
set_property(TARGET lzhtank PROPERTY POSITION_INDEPENDENT_CODE ON)

# 设置 RPATH
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
 
#设置 RPATH路径
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/.")

# 指定头文件目录
include_directories(lzhtank PRIVATE ${PROJECT_SOURCE_DIR}/../include)
include_directories(lzhtank PRIVATE ${PROJECT_SOURCE_DIR}/../glm)
include_directories(lzhtank PRIVATE ${PROJECT_SOURCE_DIR}/.)

# 指定依赖库
target_link_libraries(lzhtank lzhcore)
