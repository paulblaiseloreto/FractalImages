#include "FractalCreator.hpp"
#include "ZoomList.hpp"
#include "Mandelbrot.hpp"
#include <iostream>
#include <cassert>

namespace caveofprogramming {

void FractalCreator::addRange(double rangeEnd, const RGB& rgb) {
    m_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
    m_colors.push_back(rgb);

    if(m_bGotFirstRange) {
        m_rangeTotals.push_back(0.0);               
    }

    m_bGotFirstRange = true;

}

int FractalCreator::getRange(int iterations) const {
    int range = 0;

    for(int i = 1; i < (int)m_ranges.size(); i++) {
        range = i;

        if((int)m_ranges[i] > iterations) {
            break;
        }
    }

    range--;
    assert(range > -1);
    assert(range < (int)m_ranges.size());

    return range;

}

void FractalCreator::addZoom(const Zoom& zoom) {
     m_zoomList.add(zoom);

}

void FractalCreator::run (string name) {
    
    calculagteIteration();
    calculateTotalIterations();
    calculateRangeTotals();
    drawFractal();
    //then do the write
    writeBitmap(name);

}

FractalCreator::FractalCreator(int width, int height): 
    m_width(width), m_height(height), m_histogram(
        new int[Mandelbrot::MAX_ITERATIONS] { 0 }), m_fractal(
        new int[m_width * m_height] { 0 }), 
        m_bitmap(m_width, m_height),
        m_zoomList(m_width, m_height) {

        m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));

}

FractalCreator::~FractalCreator() {

}

 void FractalCreator::calculagteIteration() {
    //set pixel first
    //putting data
     for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
   
            pair < double, double> coords = m_zoomList.doZoom(x, y);

            int iterations = Mandelbrot::getIteration(coords.first, coords.second);

            m_fractal[y * m_width + x] = iterations;
            
            if(iterations != Mandelbrot::MAX_ITERATIONS) {
                m_histogram[iterations]++;
            }

        }   
    } 

 }

void FractalCreator::drawFractal() {

    RGB startColor(0, 0, 0);
    RGB endColor(0, 0, 255);
    //RGB colorDiff = endColor - startColor;

     for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {

            int iterations = m_fractal[y * m_width + x];
            int range = getRange(iterations);

            int rangeTotal = m_rangeTotals[range];
            int rangeStart = m_ranges[range];

            RGB& startColor = m_colors[range];
            RGB& endColor = m_colors[range + 1];
            RGB colorDiff = endColor - startColor;

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue=0;

            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                int totalPixels = 0;
                //increasing the color
                 //calculates color for a group of pixels
                for (int i = rangeStart; i <= iterations; i++) {
                    totalPixels += m_histogram[i];
                }
                //255 to the power of hue
                red = startColor.r 
                        + colorDiff.r * (double)totalPixels/rangeTotal;
                green = startColor.g 
                        + colorDiff.g * (double)totalPixels/rangeTotal;
                blue = startColor.b 
                        + colorDiff.b * (double)totalPixels/rangeTotal;
            }
            //sets black pixels otherwise
            m_bitmap.setPixel(x, y, red, green, blue);

        }
    }

}

void FractalCreator::calculateRangeTotals() {

    int rangeIndex {0};

    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        int pixels = m_histogram[i];

        if (i >= m_ranges[rangeIndex + 1]) {
            rangeIndex++;
        }
        m_rangeTotals[rangeIndex] += pixels;
    }

    int overallTotal = 0;
    for (int value: m_rangeTotals) {
        cout << "Range Total: " << value << endl;
        overallTotal += value;
    }
    cout << "Overall Total: " << overallTotal << endl;

}


void FractalCreator::calculateTotalIterations() {
     //calculates total number of iterations

    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        m_total += m_histogram[i];
    }
}

void FractalCreator::writeBitmap(string name) {
    m_bitmap.write(name);

}

}

