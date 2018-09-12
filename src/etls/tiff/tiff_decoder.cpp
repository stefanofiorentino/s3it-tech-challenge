#include "tiff_decoder.h"

#include <tiffio.h>
#include <cstring>
#include <vector>

void readTIFF(std::string const &filename, std::vector<uint16_t> &image_out, uint32_t &width, uint32_t &height)
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
            printf("The source image must be a 16bit single layer image.\n");
            exit(1);
        }

        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

        auto slSize = TIFFScanlineSize(tif);

        auto buf = static_cast<unsigned char *>(_TIFFmalloc(slSize));

        int row;
        for (row = 0; row < height; row++)
        {
            TIFFReadScanline(tif, buf, row, 0);
            int col;
            for (col = 0; col < width; col++)
            {
                uint16_t val = 0;
                val |= buf[2*col];
                val |= (((uint16_t)buf[2*col+1])<<8)&0xff00;
                    image_out.emplace_back(val);
            }
        }
        _TIFFfree(buf);

        TIFFClose(tif);
    }
}