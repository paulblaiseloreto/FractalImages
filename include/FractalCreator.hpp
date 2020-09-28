//FractalCreator.hpp
#pragma once
#include <string>
#include "Zoom.hpp"
#include "ZoomList.hpp"
#include "Bitmap.hpp"
#include "RGB.hpp"
#include <vector>

using namespace std;

    namespace caveofprogramming {
    class FractalCreator {
    private:
        int m_width{0};
        int m_height{0};
        unique_ptr<int []> m_histogram;
        unique_ptr<int []> m_fractal;
        Bitmap m_bitmap;
        ZoomList m_zoomList;
        int m_total{0};     

        vector<int> m_ranges;
        vector<RGB> m_colors;
        vector<int> m_rangeTotals;
        //vector<double> m_rangeTotalsPrint;

        bool m_bGotFirstRange {false};
        void calculateTotalIterations();
        void calculagteIteration();
        void calculateRangeTotals();
        void drawFractal();
        void writeBitmap(string name);
        

    public:
        FractalCreator(int width, int height);
        void addRange(double rangeEnd, const RGB& rgb);
        void addZoom(const Zoom& zoom);
        virtual ~FractalCreator();
        void run (string name);

        int getRange(int iterations) const;
};
    
}
