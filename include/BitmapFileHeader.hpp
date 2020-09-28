#pragma once
#include <cstdint>

using namespace std;

//To AVOID padding in the struct
//the struct will be kept in memory exactly
//No optimization(e.g. padding) will be done
#pragma pack(push, 2)

namespace caveofprogramming {
    struct BitmapFileHeader {
        char header[2]{'B', 'M'}; //'B' and 'M' is the numeric representation of bmp file type
        //OR
        //uint16_t file_type{0x4D42};
        int32_t filesize; //32 bit will ensure portability,
        //int32_t will guarante that variable is 32 bit
        int32_t reserved{0};//C++11 syntax for init
        int32_t dataOffset;
    };

 #pragma pack(pop)

}

