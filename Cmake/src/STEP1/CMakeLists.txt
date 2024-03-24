cmake_minimum_required(VERSION 3.23.0)

project(cmakeDemo) 

string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

configure_file("${PROJECT_SOURCE_DIR}/Config.h.in"
                "${PROJECT_SOURCE_DIR}/Config.h"
)


add_executable(Launcher main.c)