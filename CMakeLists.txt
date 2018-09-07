cmake_minimum_required(VERSION 3.2.2)
project(s3it-tech-challenge)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -fprofile-arcs -ftest-coverage --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 11)

add_library(lodePNG
        lodepng/lodepng.cpp)

add_library(TinyTIFF
        ./TinyTIFF/tinytiffreader.cpp
        ./TinyTIFF/tinytiffwriter.cpp)

include_directories(
        ./
        ./TinyTIFF
)
add_executable(s3it-tech-challenge src/main.cpp)
target_link_libraries(s3it-tech-challenge TinyTIFF lodePNG)
