
#include "calculate_channel_mean.h"

namespace solutions
{
    void calculate_channel_mean(std::map<std::string, std::map<uint16_t, double> > &mean_by_color_by_cell_id,
                                std::vector<unsigned char> const &image, std::vector<uint16_t> &cell_id,
                                std::vector<uint16_t> const &cells_mask, uint16_t const &height, uint16_t const &width)
    {
        for (unsigned y = 0; y < height; y++)
        {
            for (unsigned x = 0; x < width; x++)
            {
                auto cell_id_at_current_position = cells_mask.at(width * y + x);
                if (cell_id_at_current_position > 0)
                {
                    if (std::find(cell_id.cbegin(), cell_id.cend(), cell_id_at_current_position) ==
                        cell_id.cend()) // cells_id doesn't contain cells_mask value
                    {
                        // add cell_id to vector to avoid duplicates
                        cell_id.emplace_back(cell_id_at_current_position);

                        // create rChannel vector belonging to this cell_id
                        std::vector<uint16_t> rChannel_by_cell_id;
                        std::vector<uint16_t> gChannel_by_cell_id;
                        std::vector<uint16_t> bChannel_by_cell_id;
                        for (unsigned y1 = 0; y1 < height; y1++)
                        {
                            for (unsigned x1 = 0; x1 < width; x1++)
                            {
                                if (cells_mask.at(width * y1 + x1) == cell_id_at_current_position)
                                {
#ifdef __NODEF__
                                    std::cout << "x: " << x << ", y: " << y << ", x1: " << x1 << ", y1: " << y1
                                              << std::endl;
#endif
                                    rChannel_by_cell_id.emplace_back(image[4 * width * y1 + 4 * x1 + 0]);
                                    gChannel_by_cell_id.emplace_back(image[4 * width * y1 + 4 * x1 + 1]);
                                    bChannel_by_cell_id.emplace_back(image[4 * width * y1 + 4 * x1 + 2]);
                                }
                            }
                        }
                        mean_by_color_by_cell_id["R"][cell_id_at_current_position] =
                                std::accumulate(rChannel_by_cell_id.cbegin(), rChannel_by_cell_id.cend(), 0.0) /
                                rChannel_by_cell_id.size();
                        mean_by_color_by_cell_id["G"][cell_id_at_current_position] =
                                std::accumulate(gChannel_by_cell_id.cbegin(), gChannel_by_cell_id.cend(), 0.0) /
                                gChannel_by_cell_id.size();
                        mean_by_color_by_cell_id["B"][cell_id_at_current_position] =
                                std::accumulate(bChannel_by_cell_id.cbegin(), bChannel_by_cell_id.cend(), 0.0) /
                                bChannel_by_cell_id.size();
                    }
                }

            }
        }
    }
}
