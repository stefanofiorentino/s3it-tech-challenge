find_package(Catch2 REQUIRED)
add_executable(s3it-tech-challenge-tester tests.cpp)
target_link_libraries(s3it-tech-challenge-tester Catch2::Catch2 solutions fioreTIFF)

include(CTest)
include(Catch)
catch_discover_tests(s3it-tech-challenge-tester)