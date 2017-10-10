cmake_minimum_required(VERSION 2.6)
project( jpeg_testbench )

include_directories("../inc")
link_directories( ${CMAKE_CURRENT_BINARY_DIR}/../lib )

add_executable( jpeg_testbench ../src/main.c)
target_link_libraries (jpeg_testbench jpeg m)

## Setting build flags
set(CMAKE_BUILD_TYPE Debug)

## Setting compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O1")        ## Optimize
endif()
