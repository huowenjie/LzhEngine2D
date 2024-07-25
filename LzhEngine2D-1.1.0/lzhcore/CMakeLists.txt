cmake_minimum_required(VERSION 3.22.1)

project(lzhcore LANGUAGES C CXX VERSION ${LZH_ENGINE_VERSION_MAJOR}.${LZH_ENGINE_VERSION_MINOR})

# 指定静态库目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定动态库文件目录
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定可执行文件目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

# 指定源文件 
aux_source_directory(. SRCFILE)
aux_source_directory(component SRCFILE)
aux_source_directory(container SRCFILE)
aux_source_directory(log SRCFILE)
aux_source_directory(math SRCFILE)
aux_source_directory(mem SRCFILE)
aux_source_directory(scene SRCFILE)
aux_source_directory(tool SRCFILE)
aux_source_directory(object SRCFILE)
aux_source_directory(engine SRCFILE)
aux_source_directory(graphic SRCFILE)
aux_source_directory(graphic/glad SRCFILE)
aux_source_directory(box2d SRCFILE)
aux_source_directory(box2d/collision SRCFILE)
aux_source_directory(box2d/common SRCFILE)
aux_source_directory(box2d/dynamics SRCFILE)
aux_source_directory(box2d/rope SRCFILE)

# 指定生成共享库
add_library(lzhcore SHARED ${SRCFILE})

# 生成位置无关代码
set_property(TARGET lzhcore PROPERTY POSITION_INDEPENDENT_CODE ON)

# 生成 soname 版本号
set_target_properties(lzhcore PROPERTIES VERSION ${LZH_ENGINE_VERSION_MAJOR}.${LZH_ENGINE_VERSION_MINOR} SOVERSION ${LZH_ENGINE_VERSION_MAJOR})

# 指定头文件目录
target_include_directories(lzhcore PUBLIC ${CMAKE_PROJECT_ROOT}/include)
target_include_directories(lzhcore PRIVATE ${PROJECT_SOURCE_DIR}/.)
target_include_directories(lzhcore PRIVATE ${CMAKE_PROJECT_ROOT}/../freetype)
target_include_directories(lzhcore PRIVATE ${CMAKE_PROJECT_ROOT}/../sdl2)

# 指定依赖库
target_link_libraries(lzhcore PRIVATE SDL2)
target_link_libraries(lzhcore PRIVATE freetype)
