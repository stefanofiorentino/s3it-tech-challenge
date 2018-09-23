#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <numeric>
#include <limits>

#include <boost/program_options.hpp>

#include <etls/tiff/tiff_decoder.h>
#include <etls/png/png_decoder.h>

#include "solutions/calculate_channel_mean/calculate_channel_mean.h"

int main(int argc, char *argv[])
{
    using namespace boost::program_options;

    std::vector<std::string> input_filename;
    std::string single_cell_mask_filename;
    std::string cells_mask_filename;

    try
    {
        options_description desc{"Options"};
        desc.add_options()("help,h", "Help screen")("rChannel", value<std::string>()->default_value(
                "../data/images/E-cadherin(Er167Di).tiff"), "../data/images/E-cadherin(Er167Di).tiff")("gChannel",
                                                                                                       value<std::string>()->default_value(
                                                                                                               "../data/images/Fibronectin(Dy163Di).tiff"),
                                                                                                       "../data/images/Fibronectin(Dy163Di).tiff")(
                "bChannel", value<std::string>()->default_value("../data/images/HistoneH3(Yb176Di).tiff"),
                "../data/images/HistoneH3(Yb176Di).tiff")("single_cell_mask", value<std::string>()->default_value(
                "../data/single-cell-mask/single_cell_mask.tiff"), "../data/single-cell-mask/single_cell_mask.tiff")(
                "cells_mask", value<std::string>()->default_value("../data/cells-mask/cells_mask.tiff"),
                "../data/cells-mask/cells_mask.tiff");
        variables_map vm;

        store(parse_command_line(argc, argv, desc), vm);

        if (vm.count("help"))
        {
            std::cout << desc << '\n';
            exit(1);
        }
        if (vm.count("rChannel"))
        {
            std::cout << "rChannel: " << vm["rChannel"].as<std::string>() << '\n';
        }
        if (vm.count("gChannel"))
        {
            std::cout << "gChannel: " << vm["gChannel"].as<std::string>() << '\n';
        }
        if (vm.count("bChannel"))
        {
            std::cout << "bChannel: " << vm["bChannel"].as<std::string>() << '\n';
        }
        if (vm.count("bChannel"))
        {
            std::cout << "bChannel: " << vm["bChannel"].as<std::string>() << '\n';
        }
        if (vm.count("single_cell_mask"))
        {
            std::cout << "single_cell_mask: " << vm["single_cell_mask"].as<std::string>() << '\n';
        }
        if (vm.count("cells_mask"))
        {
            std::cout << "cells_mask: " << vm["cells_mask"].as<std::string>() << '\n';
        }

        input_filename.emplace_back(vm["rChannel"].as<std::string>());
        input_filename.emplace_back(vm["gChannel"].as<std::string>());
        input_filename.emplace_back(vm["bChannel"].as<std::string>());
        single_cell_mask_filename = vm["single_cell_mask"].as<std::string>();
        cells_mask_filename = vm["cells_mask"].as<std::string>();
    }
    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
        exit(1);
    }

    /**
     * 1. Implement a channel overlay.
     * Overlay the 3 channels in a single RGB image where each color R,G,B, corresponds to the intensity of each single
     * channel.
     * Save the overlay image in .png format on a local filesystem.
     * Input
     * input data are found in ./data/images
     *      HistoneH3(Yb176Di).tiff
     *      E-cadherin(Er167Di).tiff
     *      Fibronectin(Dy163Di).tiff
     */

    std::vector<std::vector<uint16_t>> tiff_layers;

    uint32_t width, height;
    for (auto frame = 0u; frame < 3u; ++frame)
    {
        tiff_layers.emplace_back(std::vector<uint16_t>());
        readTIFF(input_filename.at(frame), tiff_layers[frame], width, height);
    }

    std::vector<uint16_t> channel_max;
    channel_max.resize(3);
    std::vector<uint16_t> channel_min;
    channel_min.resize(3);
    for (unsigned frame = 0; frame < 3; frame++)
    {
        channel_max[frame] = *std::max_element(tiff_layers.at(frame).cbegin(), tiff_layers.at(frame).cend());
        channel_min[frame] = *std::min_element(tiff_layers.at(frame).cbegin(), tiff_layers.at(frame).cend());
    }

    std::string out_filename = "1_output.png";

    std::vector<unsigned char> out_image_for_png;
    out_image_for_png.resize(width * height * 4);

    prepareForPNGEncoder(out_image_for_png, tiff_layers, width, height, channel_max, channel_min);

    encodeOneStep(out_filename, out_image_for_png, width, height);

#ifdef __NODEF__
    std::vector<unsigned char> expected_image;
    unsigned expected_width, expected_height;
    decodeOneStep("../test/expected_results/1.png", expected_image, expected_width, expected_height);
#endif


    /**
     * Highlight single cells
     * Given a single cell segmentation mask image, overlay it to the output image produced at previous step, and highlight the
     * individual cells.
     * Input
     * Output of the step 1
     * Single cell segmentation mask is found in ./data/single-cell-mask/single_cell_mask.tiff
     * Output
     * Output a single image in .png format with the highlighted cells
     */

    std::vector<uint8_t> single_cell_mask;
    unsigned single_cell_mask_width, single_cell_mask_height;
    readSingleChannelMask(single_cell_mask_filename, single_cell_mask, single_cell_mask_width, single_cell_mask_height);

    if (width == single_cell_mask_width && height == single_cell_mask_height)
    {
#ifdef __NODEF__
        std::cout << "import matplotlib.pyplot as plt" << std::endl;
        std::cout << "import numpy as np" << std::endl;
        std::cout << "img = np.array([";
#endif
        for (unsigned y = 0; y < height; y++)
        {
#ifdef __NODEF__
            std::cout << "[";
#endif
            for (unsigned x = 0; x < width; x++)
            {
#ifdef __NODEF__
                std::cout << (int) single_cell_mask.at(width * y + x) << ", ";
#endif
                if (single_cell_mask.at(width * y + x))
                {
                    out_image_for_png[4 * width * y + 4 * x + 3] = 255;
                }
                else
                {
                    out_image_for_png[4 * width * y + 4 * x + 3] = 0;
                }
            }
#ifdef __NODEF__
            std::cout << "]," << std::endl;
#endif
        }
#ifdef __NODEF__
        std::cout << "], dtype='uint8')" << std::endl;
        std::cout << "plt.imshow(img)" << std::endl;
        std::cout << "plt.show()" << std::endl;
#endif
        std::string single_cell_mask_output_filename("2_output.png");
        encodeOneStep(single_cell_mask_output_filename, out_image_for_png, width, height);
    }

    /**
     * 3. Compute the mean of each channel
     * For each cell indentified in step 2, compute the mean of each channel R,G,B.
     * Input
     * Output of step 2
     * Output
     * Output a .csv file. Each row should contains: Cell_id - from the single cell mask -, channel#1 mean value, channel#2
     * mean value, channel#3 mean value
     */
    std::map<std::string, std::map<uint16_t, double> > mean_by_color_by_cell_id;
    std::vector<uint16_t> cells_mask;

    readTIFF(cells_mask_filename, cells_mask, width, height);

    std::vector<uint16_t> cell_id;
    ::solutions::calculate_channel_mean(mean_by_color_by_cell_id, out_image_for_png, cell_id, cells_mask, height,
                                        width);

    std::ofstream out("3_output.csv");
    out << "Cell_id\t" << "channel#1\t" << "channel#2\t" << "channel#3" << std::endl;
    if (cell_id.size() != mean_by_color_by_cell_id["R"].size())
    {
        out << "Error: dimension mismatch." << std::endl;
        out.close();
        return 1;
    }

#ifdef __NODEF__
    std::cout << "Cell_id\t" << "channel#1\t" << "channel#2\t" << "channel#3" << std::endl;
#endif
    for (auto const &pair : mean_by_color_by_cell_id["R"])
    {
        auto const &cell = pair.first;
        out << cell << "\t" << mean_by_color_by_cell_id["R"].at(cell) << "\t" << mean_by_color_by_cell_id["G"].at(cell)
            << "\t" << mean_by_color_by_cell_id["B"].at(cell) << std::endl;
#ifdef __NODEF__
        std::cout << cell << "\t" << mean_by_color_by_cell_id["R"].at(cell) << "\t" << mean_by_color_by_cell_id["G"].at(cell)  << "\t" << mean_by_color_by_cell_id["B"].at(cell)  << std::endl;
#endif
    }
    out.close();
}


