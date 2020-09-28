#pragma once

namespace caveofprogramming {
class Mandelbrot {
public:
    static const int    MAX_ITERATIONS = 2000;
    

public:
    Mandelbrot();
    virtual ~Mandelbrot();

    static int getIteration(double x, double y);
};

}

