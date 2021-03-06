cmake_minimum_required(VERSION 3.2.2)
project(s3it-tech-challenge)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -fprofile-arcs -ftest-coverage --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ./
        ./src
)

add_library(lodePNG
        src/libs/lodepng/lodepng.cpp
        src/etls/png/png_decoder.cpp
        src/etls/png/png_decoder.h
        )

add_subdirectory(src/solutions)
add_subdirectory(src/etls/tiff)
add_subdirectory(src/etls/png)


add_executable(
        s3it-tech-challenge
        src/main.cpp
)

target_link_libraries(s3it-tech-challenge lodePNG fioreTIFF solutions boost_program_options)

add_subdirectory(test)