#include <iostream>
#include <vector>
#include <tinytiffreader.h>


class error_code
{
    int code;
    std::string message;
public:
    error_code(int code, std::string message) :
        code(code), message(std::move(message))
    {}

    int getCode() const
    {
        return code;
    }

    void setCode(int code)
    {
        error_code::code = code;
    }

    const std::string &getMessage() const
    {
        return message;
    }

    void setMessage(const std::string &message)
    {
        error_code::message = message;
    }
};

void readTIFF(std::string const &filename, uint16_t** image_out)
{
    uint32_t frames = 0u;
    TinyTIFFReaderFile *tiffr = TinyTIFFReader_open(filename.c_str());

    if (!tiffr)
    {
        std::cout << "    ERROR reading (not existent, not accessible or no TIFF file)\n";
    }
    else
    {
        if (TinyTIFFReader_wasError(tiffr))
        { std::cout << "   ERROR:" << TinyTIFFReader_getLastError(tiffr) << "\n"; }
        std::cout << "    ImageDescription:\n" << TinyTIFFReader_getImageDescription(tiffr) << "\n";
        frames = TinyTIFFReader_countFrames(tiffr);
        std::cout << "    frames: " << frames << "\n";
        if (TinyTIFFReader_wasError(tiffr))
        { std::cout << "   ERROR:" << TinyTIFFReader_getLastError(tiffr) << "\n"; }
        uint32_t frame = 0;
        do
        {
            uint32_t width = TinyTIFFReader_getWidth(tiffr);
            uint32_t height = TinyTIFFReader_getHeight(tiffr);
            bool ok = true;
            if (width > 0 && height > 0)
            {
                std::cout << "    size of frame " << frame << ": " << width << "x" << height << "\n";
            }
            else
            {
                std::cout << "    ERROR IN FRAME " << frame << ": size too small " << width << "x" << height << "\n";
                ok = false;
            }
            if (ok)
            {
                *image_out = (uint16_t *) calloc(width * height, sizeof(uint16_t));
                TinyTIFFReader_getSampleData(tiffr, *image_out, 0);
                frame++;
                if (TinyTIFFReader_wasError(tiffr))
                {
                    ok = false;
                    std::cout << "   ERROR:" << TinyTIFFReader_getLastError(tiffr) << "\n";
                }
            }
        } while (TinyTIFFReader_readNext(tiffr)); // iterate over all frames
        std::cout << "    read " << frame << " frames\n";
    }

    TinyTIFFReader_close(tiffr);
}

int main(int argc, char *argv[])
{
    std::vector<std::string> const &filename = {
            "../data/images/HistoneH3(Yb176Di).tiff",
            "../data/images/E-cadherin(Er167Di).tiff",
            "../data/images/Fibronectin(Dy163Di).tiff"
    };
    uint16_t *images[3] = {nullptr, nullptr, nullptr};

    for (auto frame = 0u; frame < 3; ++frame)
    {
        readTIFF(filename.at(frame), &images[frame]);

        // logic goes here

        free(images[frame]);
        images[frame]=nullptr;
    }
}