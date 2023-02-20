#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void sobel_edge();

int main(void)
{
    sobel_edge();

    waitKey();
    destroyAllWindows();

    return 0;
}

/// Function Definitions
void sobel_edge()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dx, dy;
    Sobel(src, dx, CV_32FC1, 1, 0);
    Sobel(src, dy, CV_32FC1, 0, 1);

    Mat fmag, mag;
    magnitude(dx, dy, fmag);
    fmag.convertTo(mag, CV_8UC1);

    Mat edge = mag > 150;

    imshow("src", src);
    imshow("mag", mag);
    imshow("edge", edge);
}
