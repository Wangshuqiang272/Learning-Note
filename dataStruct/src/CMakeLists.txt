cmake_minimum_required(VERSION 3.23.0)

project(dataStruct)

add_definitions("-Wall -g")

add_executable(launcher main.c)

# 列举项目所有库作为target_link_libraries命令参数
set(subLib listlib arrayLib)

# # 设置可执行程序的输出位置,通过控制宏 EXECUTABLE_OUTPUT_PATH
# # set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
message(${SRC_LIST})
include_directories("base.h")

add_subdirectory(Array)
add_subdirectory(LinkList)


target_link_libraries(launcher ${subLib})