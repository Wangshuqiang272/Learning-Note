cmake_minimum_required(VERSION 3.23.0)

project(STEP2)

add_executable(Launcher main.c)

option(USE_MANAGER_COMMON_LIB "whether or not use manager common lib" ON)

if (USE_MANAGER_COMMON_LIB)

add_subdirectory(libDemo)
target_link_libraries(Launcher managerCommonLib)

endif (USE_MANAGER_COMMON_LIB)

configure_file("${PROJECT_SOURCE_DIR}/Config.h.in"
               "${PROJECT_BINARY_DIR}/config.h"
)
