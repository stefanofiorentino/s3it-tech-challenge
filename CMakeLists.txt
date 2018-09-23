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

add_library(fioreTIFF
        src/etls/tiff/tiff_decoder.cpp
        src/etls/tiff/tiff_decoder.h
        )

add_library(solutions
        src/solutions/calculate_channel_mean.cpp
        )

target_link_libraries(fioreTIFF tiff)

add_executable(
        s3it-tech-challenge
        src/main.cpp
)

target_link_libraries(s3it-tech-challenge lodePNG fioreTIFF solutions boost_program_options)

find_package(Catch2 REQUIRED)
add_executable(s3it-tech-challenge-tester test/tests.cpp)
target_link_libraries(s3it-tech-challenge-tester Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(s3it-tech-challenge-tester)