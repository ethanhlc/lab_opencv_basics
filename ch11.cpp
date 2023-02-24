#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void threshold_trackbar();
void on_threshold(int pos, void *userdata);
void threshold_otsu();

int main(void)
{
    // threshold_trackbar();
    threshold_otsu();

    destroyAllWindows();

    return 0;
}

/// Function Definitions
void threshold_trackbar()
{
    Mat src = imread("img/neutrophils.png", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    namedWindow("dst");
    int pos = 0;
    createTrackbar("Threshold", "dst", &pos, 255, on_threshold, &src);
    // createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void *)&src);
    setTrackbarPos("Threshold", "dst", 128);

    waitKey();  // required to keep Mat src in memory
}

void on_threshold(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;

    Mat dst;
    threshold(src, dst, pos, 255, THRESH_BINARY);

    imshow("dst", dst);
}

void threshold_otsu()
{
    Mat src = imread("img/camera.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dst;
    cout << "otsu threshold: ";
    cout << threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU) << endl;

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
}
