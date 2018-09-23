#define CATCH_CONFIG_MAIN

#include <src/etls/tiff/tiff_decoder.h>
#include <src/include/Error.hpp>
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
                auto const &filename = "../../data/images/E-cadherin(Er167Di).tiff";
                std::vector<uint16_t> image_out;
                uint32_t width = -1, height = -1;
                Error error = readTIFF(filename, image_out, width, height);

                REQUIRE(error.getError_code() >= 0);
                REQUIRE(error.getError_message().empty());

                REQUIRE(width == 400);
                REQUIRE(height == 395);
            }
        }
    }

    GIVEN("a wrong filename (empty string)")
    {
        WHEN("the read utility is called")
        {
            THEN("TIFF wrong format error is returned")
            {
                auto const &filename = "";
                std::vector<uint16_t> image_out;
                uint32_t width = -1, height = -1;
                Error error = readTIFF(filename, image_out, width, height);

                REQUIRE(error.getError_code() < 0);
                REQUIRE(!error.getError_message().empty());

                REQUIRE(error.getError_code() == -32001);
                REQUIRE(error.getError_message() == "TIFF wrong format");

                REQUIRE(width == std::numeric_limits<uint32_t>::max());
                REQUIRE(height == std::numeric_limits<uint32_t>::max());
            }
        }
    }
}

SCENARIO("more and mode scenario are needed here...")
{}
