cmake_minimum_required(VERSION 3.23.0)

project(dataStruct)

add_definitions("-Wall -g")

add_executable(launcher main.c)

# 列举项目所有库作为target_link_libraries命令参数
set(subLib listlib arrayLib)

include_directories("base.h")

add_subdirectory(Array)
add_subdirectory(LinkList)


target_link_libraries(launcher ${subLib})