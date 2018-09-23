#include "tiff_decoder.h"

#include <tiffio.h>
#include <cstring>
#include <vector>
#include <iostream>

#include "include/Error.hpp"

Error readTIFF(std::string const &filename, std::vector<uint16_t> &image_out, uint32_t &width, uint32_t &height)
{
    TIFF *tif = TIFFOpen(filename.c_str(), "r");
    if (tif)
    {
        uint16_t bits;
        TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bits);
        uint16_t samples;
        TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samples);
        if (bits != 16 || samples != 1)
        {
            return TIFFWrongBitNumberError();
        }

        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

        auto slSize = TIFFScanlineSize(tif);

        auto buf = static_cast<unsigned char *>(_TIFFmalloc(slSize));

        for (auto row = 0u; row < height; row++)
        {
            TIFFReadScanline(tif, buf, row, 0);
            for (auto col = 0u; col < width; col++)
            {
                uint16_t val = 0;
                val |= buf[2 * col];
                val |= (((uint16_t) buf[2 * col + 1]) << 8) & 0xff00;
                image_out.emplace_back(val);
            }
        }
        _TIFFfree(buf);

        TIFFClose(tif);
        return Error();
    }
    else
    {
        return TIFFWrongFormatError();
    }
}

void
readSingleChannelMask(std::string const &filename, std::vector<uint8_t> &image_out, uint32_t &width, uint32_t &height)
{
    TIFF *tif = TIFFOpen(filename.c_str(), "r");
    if (tif)
    {
        uint16_t bits;
        TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bits);
        uint16_t samples;
        TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &samples);
        if (bits != 1 || samples != 1)
        {
            printf("The source image must be a 1-bit single layer image.\n");
            exit(1);
        }

        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

        auto slSize = TIFFScanlineSize(tif);

        auto buf = static_cast<unsigned char *>(_TIFFmalloc(slSize));

        for (auto row = 0u; row < height; row++)
        {
            TIFFReadScanline(tif, buf, row, 0);
            int col;
            for (col = 0; col < slSize; col++)
            {
                const auto args = buf[col];
                for (int nbit = 7; nbit >= 0; nbit--)
                {
                    const auto i = 0x1 << nbit;
                    const auto i1 = args & i;
                    if (i1)
                    {
                        image_out.emplace_back(0);
                    }
                    else
                    {
                        image_out.emplace_back(1);
                    }
                }
            }

        }

        const auto image_out_size = image_out.size();
        if (image_out_size != width * height)
        {
            printf("The source MASK image a been wrongly read.\n");
            exit(1);
        }
        _TIFFfree(buf);

        TIFFClose(tif);
    }
}
