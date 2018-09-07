#include <iostream>
#include <tinytiffreader.h>

int main(int argc, char *argv[])
{
    std::string const& filename = "../data/images/E-cadherin(Er167Di).tiff";
    uint16_t* image = nullptr;

    TinyTIFFReaderFile* tiffr=TinyTIFFReader_open(filename.c_str());

    if (!tiffr) {
        std::cout<<"    ERROR reading (not existent, not accessible or no TIFF file)\n";
    } else {
        if (TinyTIFFReader_wasError(tiffr)) std::cout<<"   ERROR:"<<TinyTIFFReader_getLastError(tiffr)<<"\n";
        std::cout<<"    ImageDescription:\n"<< TinyTIFFReader_getImageDescription(tiffr) <<"\n";
        uint32_t frames=TinyTIFFReader_countFrames(tiffr);
        std::cout<<"    frames: "<<frames<<"\n";
        if (TinyTIFFReader_wasError(tiffr)) std::cout<<"   ERROR:"<<TinyTIFFReader_getLastError(tiffr)<<"\n";
        uint32_t frame=0;
        do {
            uint32_t width=TinyTIFFReader_getWidth(tiffr);
            uint32_t height=TinyTIFFReader_getHeight(tiffr);
            bool ok=true;
            if (width>0 && height>0) std::cout<<"    size of frame "<<frame<<": "<<width<<"x"<<height<<"\n";
            else { std::cout<<"    ERROR IN FRAME "<<frame<<": size too small "<<width<<"x"<<height<<"\n"; ok=false; }
            if (ok) {
                frame++;
                image=(uint16_t*)calloc(width*height, sizeof(uint16_t));
                TinyTIFFReader_getSampleData(tiffr, image, 0);
                if (TinyTIFFReader_wasError(tiffr)) { ok=false; std::cout<<"   ERROR:"<<TinyTIFFReader_getLastError(tiffr)<<"\n"; }

                ///////////////////////////////////////////////////////////////////
                // HERE WE CAN DO SOMETHING WITH THE IMAGE IN image (ROW-MAJOR!)
                ///////////////////////////////////////////////////////////////////

                free(image);
            }
        } while (TinyTIFFReader_readNext(tiffr)); // iterate over all frames
        std::cout<<"    read "<<frame<<" frames\n";
    }
    TinyTIFFReader_close(tiffr);
}