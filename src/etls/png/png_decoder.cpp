#include "png_decoder.h"

#include <iostream>

#include "libs/lodepng/lodepng.h"


void prepareForPNGEncoder(std::vector<unsigned char> &image, std::vector<std::vector<uint16_t>> const &images,
                          uint16_t width, uint16_t height, std::vector<uint16_t> const &channel_max,
                          std::vector<uint16_t> const &channel_min)
{
    for (unsigned y = 0; y < height; y++)
    {
        for (unsigned x = 0; x < width; x++)
        {
            image[4 * width * y + 4 * x + 0] = static_cast<uint8_t >(
                    (images.at(0).at(width * y + x) - channel_min.at(0)) / static_cast<float>(channel_max.at(0)) * 255);
            image[4 * width * y + 4 * x + 1] = static_cast<uint8_t >(
                    (images.at(1).at(width * y + x) - channel_min.at(1)) / static_cast<float>(channel_max.at(1)) * 255);
            image[4 * width * y + 4 * x + 2] = static_cast<uint8_t >(
                    (images.at(2).at(width * y + x) - channel_min.at(2)) / static_cast<float>(channel_max.at(2)) * 255);
            image[4 * width * y + 4 * x + 3] = 255;
        }
    }
}

void encodeOneStep(std::string const& filename, std::vector<unsigned char> &image, unsigned width, unsigned height)
{
    unsigned error = lodepng::encode(filename, image, width, height);

    if (error)
    {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}

void decodeOneStep(std::string const& filename, std::vector<unsigned char> &image, unsigned &width, unsigned &height)
{
    unsigned error = lodepng::decode(image, width, height, filename);

    if(error)
    {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}
