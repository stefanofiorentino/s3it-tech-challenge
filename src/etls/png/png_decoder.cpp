#include "png_decoder.h"

#include <iostream>

#include "libs/lodepng/lodepng.h"

//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(std::string const& filename, std::vector<unsigned char> &image, unsigned width, unsigned height)
{
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if (error)
    {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}

//Decode from disk to raw pixels with a single function call
void decodeOneStep(std::string const& filename, std::vector<unsigned char> &image, unsigned &width, unsigned &height)
{
    //decode
    unsigned error = lodepng::decode(image, width, height, filename);

    //if there's an error, display it
    if(error)
    {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}
