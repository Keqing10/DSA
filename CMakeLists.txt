cmake_minimum_required(VERSION 3.10)
project(DSA-Test)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(include test)

# 查找所有源文件和头文件
file(GLOB TEST_SOURCES "test/*.cpp")
file(GLOB TEST_HEADERS "test/*.h")
file(GLOB INCLUDE_HEADERS "include/*")

# 测试项目
add_executable(DSA-Test ${TEST_SOURCES} ${TEST_HEADERS} ${INCLUDE_HEADERS})

# 在Visual Studio中组织文件
source_group("Header Files\\Test" FILES ${TEST_HEADERS})
source_group("Header Files\\DSA" FILES ${INCLUDE_HEADERS})
source_group("Source Files" FILES ${TEST_SOURCES})