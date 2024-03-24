cmake_minimum_required(VERSION 3.23.0)

project(dataStruct)

add_definitions("-Wall -g")

add_executable(launcher main.c)
# 列举所有的子目录作为add_subdirectory命令参数
set(subDirectory Array)
# 列举项目所有库作为target_link_libraries命令参数
set(subLib arrayLib)

include_directories("base.h")

add_subdirectory(Array ${subDirectory})

target_link_libraries(launcher ${subLib})