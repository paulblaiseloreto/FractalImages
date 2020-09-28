//Bitmap.hpp
#pragma once
#include <string>
#include <cstdint>
#include <memory>
using namespace std;

namespace caveofprogramming {

    class Bitmap {
    private:
        int m_width{0};
        int m_height{0};
        unique_ptr<uint8_t []> m_pPixels {nullptr};

    public:
        Bitmap(int width, int height);
        //uint8_t unsigned char
        void setPixel(int x, int y, uint8_t red, uint8_t gree, uint8_t blue);
        //void setBMColor(uint)
        bool write(string filename);
        virtual ~Bitmap();

    };

}

