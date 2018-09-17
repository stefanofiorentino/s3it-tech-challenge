#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

#include <boost/program_options.hpp>

#include <etls/tiff/tiff_decoder.h>
#include <etls/png/png_decoder.h>
#include <fstream>

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

    std::string out_filename = "test.png";

    std::vector<unsigned char> image;
    image.resize(width * height * 4);

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

    encodeOneStep(out_filename.c_str(), image, width, height);

#ifdef __NODEF__
    std::vector<unsigned char> expected_image;
    unsigned expected_width, expected_height;
    decodeOneStep("../test/expected_results/1.png", expected_image, expected_width, expected_height);
#endif

//#######################################################  2

    const char *single_cell_mask_filename = "../data/single-cell-mask/single_cell_mask.tiff";

    std::vector<uint8_t> single_cell_mask;
    unsigned single_cell_mask_width, single_cell_mask_height, n_cells;
    readSingleChannelMask(single_cell_mask_filename, single_cell_mask, single_cell_mask_width, single_cell_mask_height);

    if (width == single_cell_mask_width && height == single_cell_mask_height)
    {
        std::cout << "import matplotlib.pyplot as plt" << std::endl;
        std::cout << "import numpy as np" << std::endl;
        std::cout << "img = np.array([";
        for (unsigned y = 0; y < height; y++)
        {
            std::cout << "[";
            for (unsigned x = 0; x < width; x++)
            {
                std::cout << (int) single_cell_mask.at(width * y + x) << ", ";
                if (single_cell_mask.at(width * y + x))
                {
                    image[4 * width * y + 4 * x + 3] = 255;
                }
                else
                {
                    image[4 * width * y + 4 * x + 3] = 0;
                }
            }
            std::cout << "]," << std::endl;
        }
        std::cout << "], dtype='uint8')" << std::endl;
        std::cout << "plt.imshow(img)" << std::endl;
        std::cout << "plt.show()" << std::endl;
        std::string single_cell_mask_output_filename("test2.png");
        encodeOneStep(single_cell_mask_output_filename, image, width, height);
    }

    //#######################################################  3
    // get how many valid mask values are there
    unsigned n_sample_mask = 0u;
    std::vector<double> mean(3, 0.0);

    for (unsigned y = 0; y < height; y++)
    {
        for (unsigned x = 0; x < width; x++)
        {
            if (255 == image[4 * width * y + 4 * x + 3])
            {
                n_sample_mask++;
                auto a = mean[0];
                auto b = image[4 * width * y + 4 * x + 0];
                if (a > 0 && b > std::numeric_limits<uint64_t>::max() - a)
                {
                    std::cout << "overflow";
                }
                mean[0] += image[4 * width * y + 4 * x + 0];

                a = mean[1];
                b = image[4 * width * y + 4 * x + 1];
                if (a > 0 && b > std::numeric_limits<uint64_t>::max() - a)
                {
                    std::cout << "overflow";
                }
                mean[1] += image[4 * width * y + 4 * x + 1];

                a = mean[0];
                b = image[4 * width * y + 4 * x + 2];
                if (a > 0 && b > std::numeric_limits<uint64_t>::max() - a)
                {
                    std::cout << "overflow";
                }
                mean[2] += image[4 * width * y + 4 * x + 2];
            }
        }
    }

    double mean_d[3];
    for (unsigned k = 0; k < 3; k++)
    {
        mean_d[k] = 1.0 * mean[k] / n_sample_mask;
    }

    std::ofstream out("test.csv");
    out << "Cell_id\t" << "channel#1\t" << "channel#2\t" << "channel#3" << std::endl;
    for (unsigned channel = 0; channel < 3; channel++)
    {
        out << channel << "\t" << mean_d[0] << "\t" << mean_d[1] << "\t" << mean_d[2] << std::endl;
    }
    out.close();
}
