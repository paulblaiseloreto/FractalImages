//Bitmap.cpp
#include <fstream>
#include "Bitmap.hpp"
#include "BitmapInfoHeader.hpp"
#include "BitmapFileHeader.hpp"
using namespace caveofprogramming;
using namespace std;

namespace caveofprogramming {
    
Bitmap::Bitmap(int width, int height): 
        m_width(width) , m_height(height), m_pPixels(
            new uint8_t[width * height *3] {}) { 

}

bool Bitmap::write(string filename) {
    BitmapInfoHeader infoHeader;
    BitmapFileHeader fileHeader;

    fileHeader.filesize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) 
            + m_width*m_height*3;
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    infoHeader.width = m_width;
    infoHeader.height = m_height;

    ofstream file;

    file.open(filename, ios::out|ios::binary);

    if(!file) {
        return false;
    }
    //write data to a file

    //cast to char, &address, size
    file.write((char *) &fileHeader, sizeof(fileHeader));
    file.write((char *) &infoHeader, sizeof(infoHeader));
    //no need address, 3 bytes per pixel
    //cannot cast unique pointer , that's why get () is used
    file.write((char *) m_pPixels.get(), m_width * m_height *3);

    file.close();
    
    //maybe not necessary
    if(!file) {
        return false;
    }

    return true;
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t *pPixel = m_pPixels.get();

    pPixel += (y * 3) * m_width + (x * 3);

    pPixel[0] = blue;
    pPixel[1] = green;
    pPixel[2] = red;

    //little endian  format you store the least significant byte, 
    //in the area of memory with the smallest memory address

}

Bitmap::~Bitmap() {

}

}