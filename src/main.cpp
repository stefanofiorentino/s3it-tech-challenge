#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

#include <boost/program_options.hpp>

#include <etls/tiff/tiff_decoder.h>
#include <etls/png/png_decoder.h>

using namespace boost::program_options;

void on_age(int age)
{
    std::cout << "On age: " << age << '\n';
}

int main(int argc, char *argv[])
{
    try
    {
        options_description desc{"Options"};
        desc.add_options()("help,h", "Help screen")("pi", value<float>()->default_value(3.14f), "Pi")("age",
                                                                                                      value<int>()->notifier(
                                                                                                              on_age),
                                                                                                      "Age");

        variables_map vm;

        if (vm.count("help"))
        {
            std::cout << desc << '\n';
        }
        else if (vm.count("age"))
        {
            std::cout << "Age: " << vm["age"].as<int>() << '\n';
        }
        else if (vm.count("pi"))
        {
            std::cout << "Pi: " << vm["pi"].as<float>() << '\n';
        }
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);
    }
    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
    }

    std::vector<std::string> const &input_filename = {"../data/images/E-cadherin(Er167Di).tiff",
                                                      "../data/images/Fibronectin(Dy163Di).tiff",
                                                      "../data/images/HistoneH3(Yb176Di).tiff"};

    std::vector<std::vector<uint16_t>> images;

    uint32_t width, height;
    for (auto frame = 0u; frame < 3u; ++frame)
    {
        images.emplace_back(std::vector<uint16_t>());
        readTIFF(input_filename.at(frame), images[frame], width, height);
    }

    std::vector<uint16_t> channel_max;
    channel_max.resize(3);
    std::vector<uint16_t> channel_min;
    channel_min.resize(3);
    for (unsigned frame = 0; frame < 3; frame++)
    {
        channel_max[frame] = 0;
        channel_min[frame] = std::numeric_limits<uint16_t>::max();
        std::cout << "--------------------------------------------------------------------------" << std::endl;
        for (unsigned y = 0; y < height; y++)
        {
            for (unsigned x = 0; x < width; x++)
            {
                if (images.at(frame).at(width * y + x) > channel_max.at(frame))
                {
                    channel_max[frame] = images.at(frame).at(width * y + x);
                }
                if (images.at(frame).at(width * y + x) < channel_min.at(frame))
                {
                    channel_min[frame] = images.at(frame).at(width * y + x);
                }
                std::cout << images.at(frame).at(width * y + x) << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    auto const &out_filename = "test.png";

    std::vector<unsigned char> image;
    image.resize(width * height * 4);

    for (unsigned y = 0; y < height; y++)
    {
        for (unsigned x = 0; x < width; x++)
        {
            image[4 * width * y + 4 * x + 0] = static_cast<uint8_t >(
                    (images.at(0).at(width * y + x) - channel_min.at(0)) / static_cast<float>(channel_max.at(0) / 10) *
                    255);
            image[4 * width * y + 4 * x + 1] = static_cast<uint8_t >(
                    (images.at(1).at(width * y + x) - channel_min.at(1)) / static_cast<float>(channel_max.at(1) / 10) *
                    255);
            image[4 * width * y + 4 * x + 2] = static_cast<uint8_t >(
                    (images.at(2).at(width * y + x) - channel_min.at(2)) / static_cast<float>(channel_max.at(2) / 10) *
                    255);
            image[4 * width * y + 4 * x + 3] = 255;
        }
    }

    encodeOneStep(out_filename, image, width, height);

#ifdef __NODEF__
    std::vector<unsigned char> expected_image;
    unsigned expected_width, expected_height;
    decodeOneStep("../test/expected_results/1.png", expected_image, expected_width, expected_height);
#endif
}