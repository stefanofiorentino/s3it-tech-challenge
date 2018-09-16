#ifndef S3IT_TECH_CHALLENGE_PNG_DECODER_H
#define S3IT_TECH_CHALLENGE_PNG_DECODER_H

#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

void encodeOneStep(std::string const& filename, std::vector<unsigned char> &image, unsigned width, unsigned height);
void decodeOneStep(std::string const& filename, std::vector<unsigned char> &image, unsigned &width, unsigned &height);

#ifdef __cplusplus
};
#endif

#endif //S3IT_TECH_CHALLENGE_PNG_DECODER_H
