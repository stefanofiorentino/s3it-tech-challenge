
#ifndef S3IT_TECH_CHALLENGE_CALCULATE_CHANNEL_MEAN_H
#define S3IT_TECH_CHALLENGE_CALCULATE_CHANNEL_MEAN_H

#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

namespace solutions
{
    void calculate_channel_mean(std::map<std::string, std::map<uint16_t, double> > &mean_by_color_by_cell_id,
                                std::vector<unsigned char> const &image, std::vector<uint16_t> &cell_id,
                                std::vector<uint16_t> const &cells_mask, uint16_t const &height, uint16_t const &width);
}
#endif //S3IT_TECH_CHALLENGE_CALCULATE_CHANNEL_MEAN_H
