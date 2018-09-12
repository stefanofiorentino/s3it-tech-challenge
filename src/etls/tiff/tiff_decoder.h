#ifndef S3IT_TECH_CHALLENGE_TIFF_DECODER_H
#define S3IT_TECH_CHALLENGE_TIFF_DECODER_H


#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

void readTIFF(std::string const &filename, std::vector<uint16_t> &image_out, uint32_t &width, uint32_t &height);

#ifdef __cplusplus
};
#endif

#endif //S3IT_TECH_CHALLENGE_TIFF_DECODER_H