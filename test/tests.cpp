#define CATCH_CONFIG_MAIN

#include "libs/Catch2/single_include/catch2/catch.hpp"


SCENARIO("first scenario ever created")
{
    GIVEN("a string")
    {
        REQUIRE(true);
    }
}


SCENARIO("this test is here to check continuous integration fails on make test failure")
{
    GIVEN("a false requirement")
    {
        REQUIRE(false);
    }
}
