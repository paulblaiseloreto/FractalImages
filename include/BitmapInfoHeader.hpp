#pragma once

#include <cstdint> //need to include for 32 bit

using namespace std;

//REMOVE C++ PADDING within struct
#pragma pack(2)
namespace caveofprogramming {
    //struct default members are PUBLIC
    struct BitmapInfoHeader {
        int32_t headerSize{40}; //C++11 init syntax
        int32_t width;
        int32_t height;
        int16_t planes{1};
        int16_t bitsPerPixel{24};
        int32_t compression{0};
        int32_t dataSize{0};
        int32_t horizontalResolution{2400};//bits per pixel
        int32_t verticalResolution{2400};
        int32_t colors{0};
        int32_t importantColors{0};

    };
}

