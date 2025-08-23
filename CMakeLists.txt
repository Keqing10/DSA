cmake_minimum_required(VERSION 3.10)
project(DSA)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 主库（头文件库）
add_library(DataStructure INTERFACE)
target_include_directories(DataStructure INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 测试项目
file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(DSA-Test ${TEST_SOURCES})

# 链接库
target_link_libraries(DSA-Test DataStructure)