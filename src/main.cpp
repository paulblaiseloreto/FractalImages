//Fractal.cpp
#include <iostream>
#include "Bitmap.hpp"
#include <cstdint>
#include <memory>
#include <cmath>
#include <ZoomList.hpp>
#include "Mandelbrot.hpp"
#include "Zoom.hpp"
#include "FractalCreator.hpp"
#include "RGB.hpp"

using namespace std;
using namespace caveofprogramming;

int main() {

    FractalCreator fractalCreator(800, 600);

    fractalCreator.addRange(0.0, RGB(0, 0, 0));
    fractalCreator.addRange(0.3, RGB(255, 0, 0));
    fractalCreator.addRange(0.5, RGB(255, 255, 0));
    fractalCreator.addRange(1.0, RGB(255, 255, 255));

    cout << fractalCreator.getRange(999) << endl;

    fractalCreator.addZoom(Zoom(295, 202, 0.1));
    fractalCreator.addZoom(Zoom(312, 304, 0.1));

    fractalCreator.run("test.bmp");       
    cout << "Finished " << endl;
    
    return 0;
}