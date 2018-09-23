#define CATCH_CONFIG_MAIN

#include "libs/Catch2/single_include/catch2/catch.hpp"


SCENARIO("first scenario ever created")
{
    GIVEN("a string")
    {
        REQUIRE(true);
    }
}

SCENARIO("load a TIFF")
{
    GIVEN("a TIFF single layer")
    {
        WHEN("the read utility is called")
        {
            THEN("the dimensions matches")
            {

            }
        }
    }
}
